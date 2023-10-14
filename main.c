#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define BOMBS 15 //amount of bombs to be placed

//function for placing 15 random bombs on the board

void placeBombs(char board[SIZE][SIZE]){
    srand(time(NULL));
    int current_bombs = 0; 

    while (current_bombs < BOMBS){
        int x = rand() % SIZE; //produces a number from 0-9
        int y = rand() % SIZE;

        
        if (board[x][y] != 'x'){
        board[x][y] = 'x';

        //current bombs only goes up if (x,y) is a new position
        //else it will not go up and the while loop resets

        current_bombs++;
                }
            }
        }
    
/*function for counting and outputing number
of adjacent bombs.

the call for this next function should be
in an 'if statement' that first checks if the given
coordinate has a bomb*/

int countAdjacentBombs(char board[SIZE][SIZE], int x, int y){
    int proximity = 0; //number of bombs nearby
    
    for(int i = x-1; i<=x+1 ; i++){
        for(int j = y-1 ; j<=y+1 ; j++){

            if((i < 0 || j < 0) || (i > 9 || j > 9)){
                continue;
            }

            /*the above segment is for edge pieces in the
            board which don't have 8 pieces surrounding them*/

            else if(board[i][j] == 'x'){
                proximity++;
            }
        }
    }
    return proximity;
}

/*a function for printing the board 
is useful since it will be updated many times*/

void printboard(char board[SIZE][SIZE]){
    printf("  0 1 2 3 4 5 6 7 8 9\n");

    for(int i=0 ; i<SIZE ; i++){
        printf("%d ",i);
        for(int j=0 ; j<SIZE ; j++){
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }

}

int main(void){
    char board[SIZE][SIZE];
    int gameover = 0;//boolean to assess failure
    int remainingCells = SIZE * SIZE - BOMBS;
    int revealed = 0;//# of cells revealed

//intializing an empty board...

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '-';
        }
    }
    placeBombs(board);

    char ui_board[SIZE][SIZE];//this board is shown to the user

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            ui_board[i][j] = '-';
        }
    }

    printf("Welcome to Minesweeper!\n\n");
    printboard(ui_board);
    
    while(revealed < remainingCells && !gameover){
    int x, y;//hold input from user
    int inputvalid = 0;//bool for correct user input

    while(!inputvalid){
        printf("Enter coordinates (x y): ");

        if (scanf("%d %d",&x ,&y) == 2){
            if (x >= 0 && x < SIZE && y >= 0 && y < SIZE){
                if (ui_board[x][y] == '-'){
                    inputvalid = 1;
                }
                else{
                    printf("\nInvalid Input:\nthis cell has already been revealed\n\n");
                }
            }
            else{
                printf("\nInvalid Input:\nenter coordinates between 1 & 9\n\n");
            }
        }
        else{
            printf("\nInvalid Input:\nenter two integers separated by a space\n\n");
            while (getchar() != '\n');//clears the input space
        }
    }


    
    

    //LOSE CONDITION
    if (board[x][y] == 'x'){

        printboard(board);

        printf("\nYou hit a bomb... GAME OVER\n");

        gameover = 1;
        break;
    }

    /*the below variable is how many bombs
    surround the given coordinate*/

    int coord_val = countAdjacentBombs(board, x, y);
    char ch = coord_val + '0';//converting int to char
    ui_board[x][y] = ch;
    
    printboard(ui_board);
    }
    
    /*WIN CONDITION
    
    if the player makes it out of the while loop
    without having hit a bomb (meaning they have revealed
    all possible safe cells. this statement checks for if gameover
    is false.)*/

    if(!gameover){
        printboard(board);
        printf("You cleared the mines... YOU WIN!");
    }
}

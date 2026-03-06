/*
Names of members:
 - Keith Buenaventura
 - Karl Kristoffer R. Camato
 - Maurienne Mojica

Sections: 
 - S-27
 - S-28

March 24 2025
C.C.D.S.T.R.U. M.P.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 4
#define UNO 'U'      
#define DOS 'D'
#define TRES 'T'
#define EMPTY '.'

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

#define RESET "\033[0m"

char board[SIZE][SIZE];  

// Display game instructions and rules
void displayRules() 
{
	 printf("\n" GREEN "   __  ___   ______" RESET "	" YELLOW " ____ _____  _____ " RESET " " RED "  __________  ___________" RESET " \n");
    printf("" GREEN "  / / / / | / / __ \\" RESET " " YELLOW "   / __ \\/ __ \\/ ___/ " RESET " " RED " /_  __/ __ \\/ ____/ ___/" RESET " \n");
    printf("" GREEN " / / / /  |/ / / / /" RESET " " YELLOW "  / / / / / / /\\__ \\ " RESET " " RED "  / / / /_/ / __/  \\__ \\" RESET "\n");
    printf("" GREEN "/ /_/ / /|  / /_/ /" RESET " " YELLOW "  / /_/ / /_/ /___/ / " RESET " " RED " / / / _  _/ /___ ___/ / " RESET "\n");
    printf("" GREEN "\\____/_/ |_|\\____/ " RESET " " YELLOW " /_____\\/____//____/  " RESET " " RED "/_/ /_/ |_/_____//____/  " RESET "\n");  
    printf("\n\nWelcome to the " GREEN "Uno" RESET "-" YELLOW "Dos" RESET "-" RED "Tres" RESET " Game!\n");
    printf("\nGame Rules:\n\n");
    printf("1. The game is played on a 4x4 grid by 3 PLAYERS.\n");
    printf("2. TRES, UNO and DOS take turns (the order is as stated):\n");
    printf("\t- TRES and UNO can place their markers (Tres = 'T', Uno = 'U').\n");
    printf("\t- DOS can remove either (UNO's or TRES') marker of their choice\n\n");
    printf("3. Only DOS can remove an opponent's marker but cannot choose an empty space otherwise.\n");
    printf("4. A player wins by completing one of the following patterns:\n");
    printf("\t- The top row\n");
    printf("\t- The bottom row\n");
    printf("\t- The anti-diagonal (/).\n\n");
    printf("5. If the board fills up with none of the listed patterns formed, Dos wins by default.\n\n");
    printf("Enter any letter to begin the game!\n\n");
    getchar();
    while (getchar() != '\n');
}

// Initialize the board with empty slots
void startBoard() 
{
    int i, j;
    for (i = 0; i < SIZE; i++) 
    {
        for (j = 0; j < SIZE; j++) 
        {
            board[i][j] = EMPTY;  
        }
    }
}

// Print the board
void printBoard() 
{
    int i, j;
    printf("\n  1 2 3 4\n");  
    for (i = 0; i < SIZE; i++) 
    {
        printf("%d ", i + 1);  
        for (j = 0; j < SIZE; j++) 
        {
            if (board[i][j] == UNO)
                printf(GREEN "%c " RESET, board[i][j]); // UNO in green
            else if (board[i][j] == TRES)
                printf(RED "%c " RESET, board[i][j]);   // TRES in red
            else
                printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Check if board is full
int FullBoard() 
{
    int i, j;
    for (i = 0; i < SIZE; i++) 
    {
        for (j = 0; j < SIZE; j++) 
        {
            if (board[i][j] == EMPTY)
            {
                return 0;   
            }
        }
    }
    return 1;
}

// Checks winning conditions 
int CheckWinner(char playerMarker) 
{
    int i,count;
    
    count = 0;
    for (i = 0; i < SIZE; i++)  //top horizontal
    {
        if (board[0][i] == playerMarker) 
        {
            count++;
        }
    }
    if (count == SIZE) 
    {
        return 1;
    }

    // bottom horizontal
    count = 0;
    for (i = 0; i < SIZE; i++) 
    {
        if (board[3][i] == playerMarker) 
            count++;
    }
    if (count == SIZE) 
    {
        return 1;
    }
        
    // Anti-Diagonal (/)
    count = 0;
    for (i = 0; i < SIZE; i++) 
    {
        if (board[i][SIZE - 1 - i] == playerMarker) 
        {
            count++;
        }
            
    }
    if (count == SIZE) 
    {
        return 1;
    }
    return 0; 
}

// Function to handle player moves
void playerMove(int *turn, int *go) 
{
    char currentPlayer;
    int row, col, validMove;
    char input[20];
    validMove = 1;

    if (*turn == 1 && *go == 0) 
    {
        currentPlayer = TRES;
        printf(RED "\nTRES' turn (T)" RESET);
    } 
    else if (*turn == 1 && *go == 1)
    {
        currentPlayer = UNO;
        printf(GREEN "\nUNO's turn (U)" RESET);
    }
    else if (*turn == 0)
    {
        currentPlayer = DOS;
        printf(YELLOW "\nDOS' turn (D)" RESET);
    }

    while (validMove) 
    {
        printf("\nEnter row and column (1-4): ");

        if (!fgets(input, sizeof(input), stdin)) 
        {
            printf("Input error. Try again.\n");
            continue;
        }

        if (sscanf(input, "%d %d", &row, &col) != 2) 
        {
            printf("Invalid input. Please enter two numbers (1-4).\n");
            continue;
        }

        if (row >= 1 && row <= SIZE && col >= 1 && col <= SIZE) 
        {
            // If TRES is playing
            if (currentPlayer == TRES)
            {
                if (board[row - 1][col - 1] == EMPTY) // TRES place mark
                {
                    board[row - 1][col - 1] = TRES;
                    *go = !(*go);
                    validMove = 0;
                }
                else
                {
                    printf("Invalid move. You cannot add a marker on an occupied space.\n");
                }
            }
            // If UNO is playing
            else if (currentPlayer == UNO)
            {
                if (board[row - 1][col - 1] == EMPTY) // UNO place mark
                {
                    board[row - 1][col - 1] = UNO;
                    *turn = !(*turn);
                    *go = !(*go);
                    validMove = 0;
                }
                else
                {
                    printf("Invalid move. You cannot add a marker on an occupied space.\n");
                }
            }
            // If DOS is playing
            else if(currentPlayer == DOS)
            {
                if (board[row - 1][col - 1] == UNO) // DOS can remove UNO
                {
                    board[row - 1][col - 1] = EMPTY;
                    *turn = !(*turn);
                    validMove = 0;
                }
                else if (board[row - 1][col - 1] == TRES)  // DOS can remove TRES
                {
                    board[row - 1][col - 1] = EMPTY;
                    *turn = !(*turn);
                    validMove = 0;
                }
                else
                {
                    printf("Invalid move. You can only remove existing markers on occupied spaces.\n");
                }
            }
        } 
        else 
        {
            printf("Invalid move. Try again.\n");
        }
    }
}

void restartGame(int *nTurn, int *nGo, int *GameOver) 
{
    char playAgain;
    while (1)
    {
        printf("\nDo you want to play again?\n");
        printf("Enter [y] if yes\n");
        printf("Enter [n] if otherwise\n");
        printf("\nEnter: ");
        scanf(" %c", &playAgain);
        while (getchar() != '\n'); 

        if (playAgain == 'Y' || playAgain == 'y') 
        {
            startBoard(); 
            *nTurn = 1; 
            *nGo = 0;
            *GameOver = 0;
            break;
        }
        else if (playAgain == 'N' || playAgain == 'n')
        {
            printf("\nThanks for playing!\n");
            exit(0); 
        }
        else
        {
            printf("Invalid input. Please enter [y] or [n]\n");
        }
    }
}

// Main function
int main() 
{
    int nTurn, nGo, GameOver;
    nTurn = 1;
    nGo = 0;
    GameOver = 0;
    
    displayRules();
    startBoard();

    while (GameOver == 0)
    {
        system("cls");
        printBoard();
        playerMove(&nTurn, &nGo);

        if (CheckWinner(UNO))
        {
            printBoard();
            printf(GREEN "\nUNO WINS!\n" RESET);
            GameOver = 1;
        }
        
        else if (CheckWinner(TRES))
        {
            printBoard();
            printf(RED "\nTRES WINS!\n" RESET);
            GameOver = 1;
        }
        
        else if (FullBoard()) 
        {
            printBoard();
            printf(YELLOW "\nDOS WINS!\n" RESET);
            GameOver = 1;
        }
        
        if (GameOver) 
        {
            restartGame(&nTurn, &nGo, &GameOver); 
        }
    }
    return 0;
}

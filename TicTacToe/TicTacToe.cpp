// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// system("cls"); - Clear Screen
// system("pause"); - "Press any Key to continue.. "

#include <iostream>

// Wincondition defines.
constexpr auto DRAW = 0;
constexpr auto P1_WIN = 1;
constexpr auto P2_WIN = 2;



// Class for the playing board.
class PlayingBoard
{
private:
    char board[3][3];   // The board as a 3x3 char array.
    
public:
    PlayingBoard(); // Constructor - Clears the board on initialisation.
    ~PlayingBoard();    // Destructor.
    void ClearBoard();  // 'Clears' the board. Fills each cell with a space (' ').
    bool PlacePiece(int x, int y, char piece);  // Places a character (piece) at x,y of the board array. Returns true if sucessful or false if the space is already occupied by anything other than a space (' '). Also returns false if the x,y co-ordinates are invalid.
    char GetPiece(int x, int y);    // Returns the char at x,y on the board. Returns 'E' if co-ordinates are invalid.
    void DisplayBoard();    // Displays the board to the console.
};

// Class for the main game.
class TicTacToe
{
public:

    PlayingBoard gameBoard;     // The playing board for the game.
    TicTacToe();
    ~TicTacToe();
    void InitialiseGame();      // Initialises the game variables and clears the board. Also used to reset the game.
    void ChoosePlayerPieces();  // Asks player 1 which piece they would like to be (O or X), and allocates player 2 the opposite piece.
    char GetPlayerOnePiece();   // Returns player 1's piece.
    char GetPlayerTwoPiece();   // Returns player 2's piece.
    void PlayerOneMove();       // Gets player 1's move from the user and places it on the board.
    void PlayerTwoMove();       // Gets player 2's move from the user and places it on the board.
    int CheckForWin();          // Checks the board for a winner or a draw and returns one of the following, -1 = No win or draw, 0 = draw, 1 = game won. NOTE: playerOneWon, playerTwoWon set by this function.
    void DeclareEndGame();      // Displays the winner or draw and concludes the game.

    bool MainMenu(); // Displays the main menu and retreives input about wheather to play or exit the game. Returns false if the user chooses to exit the game.
    bool ReturnMainMenu(); // Retreives input about wheather to return to the main menu or exit the game. Returns false if the user chooses to exit the game.
    bool PlayGame();    // Main game function, returns true if user wants to return to the main menu.

private:
    char playerOnePiece, playerTwoPiece;
    int m_WinCondition;
};

int main()
{
    TicTacToe game = TicTacToe();
    bool playGame = true;

    while (playGame == true)
    {
        playGame = game.MainMenu();

        if (!playGame)
            break;

        playGame = game.PlayGame();
    }

    std::cout << "Thank you for playing :)\n\n";
    system("pause");

    return 0;
}

void PlayingBoard::ClearBoard()
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            PlayingBoard::board[x][y] = ' ';
        }
    }
}

PlayingBoard::PlayingBoard()
{
    ClearBoard();
}

PlayingBoard::~PlayingBoard()
{
}

bool PlayingBoard::PlacePiece(int x, int y, char piece)
{
    if ((x >= 0 && x < 3) && (y >= 0 && y < 3))     // Checks if x,y are valid co-ordinates (between 0-2).
    {
        if (PlayingBoard::board[x][y] == ' ')   // Checks if the space on the board is already occupied.
        {
            PlayingBoard::board[x][y] = piece;  // Places piece at x,y.
            return true;
        }
        else
            return false;   // Space already occupied.
    }
    else
        return false;   // Co-ordinates invalid.
}

char PlayingBoard::GetPiece(int x, int y)
{
    if ((x >= 0 && x < 3) && (y >= 0 && y < 3))     // Checks if x,y are valid co-ordinates (between 0-2).
        return PlayingBoard::board[x][y];
    else
        return 'E';     // Co-ordiates invalid.
}

void PlayingBoard::DisplayBoard()
{
    std::cout << "   1 2 3\n";     // Top header.
    std::cout << "  -------\n";     // Top border.
    for (int x = 0; x < 3; x++)
    {
        std::cout << x + 1 << " ";     // Side header.
        for (int y = 0; y < 3; y++)
        {
            std::cout << "|" << PlayingBoard::board[y][x];
        }
        std::cout << "|\n  -------\n";   // Right border/separating line/bottom border.
    }
}

bool TicTacToe::MainMenu()
{
    char play;
    bool validOption = false;

    std::cout << "********************\nWelcome to TicTacToe\t\tCopyright (C) 2020 Andrew C Morgan\n********************\n\n";

    do
    {
        std::cout << "Would you like to play? (Y/N):";
        std::cin >> play;

        validOption = ((play == 'Y' || play == 'N') || (play == 'y' || play == 'n'));
    } while (validOption == false);

    system("cls");

    if (play == 'Y' || play == 'y')
        return true;
    else
        return false;
}

bool TicTacToe::ReturnMainMenu()
{
    char menu;
    bool validOption = false;

    do
    {
        std::cout << "Would you like to return to the menu? (Y/N):";
        std::cin >> menu;

        validOption = ((menu == 'Y' || menu == 'N') || (menu == 'y' || menu == 'n'));
    } while (validOption == false);

    system("cls");

    if (menu == 'Y' || menu == 'y')
        return true;
    else
        return false;
    return false;
}

bool TicTacToe::PlayGame()
{
    TicTacToe::InitialiseGame();
    TicTacToe::ChoosePlayerPieces();

    do
    {
        TicTacToe::PlayerOneMove();
        if (TicTacToe::CheckForWin() != -1)
            break;

        TicTacToe::PlayerTwoMove();
        if (TicTacToe::CheckForWin() != -1)
            break;

    } while (1);

    TicTacToe::DeclareEndGame();
    return TicTacToe::ReturnMainMenu();
}

TicTacToe::TicTacToe()
{
    TicTacToe::InitialiseGame();
}

TicTacToe::~TicTacToe()
{
}

void TicTacToe::InitialiseGame()
{
    TicTacToe::gameBoard = PlayingBoard();
    TicTacToe::playerOnePiece = TicTacToe::playerTwoPiece = 'N';
}

void TicTacToe::ChoosePlayerPieces()
{
    bool okayValid, p1valid, isOkay = false;
    char yesNo;

    do
    {
        // Get the piece for player 1.
        do
        {
            system("cls");
            std::cout << "Player 1, Choose your piece. (X or O):";
            std::cin >> TicTacToe::playerOnePiece;

            p1valid = ((TicTacToe::playerOnePiece == 'O' || TicTacToe::playerOnePiece == 'X') || (TicTacToe::playerOnePiece == 'o' || TicTacToe::playerOnePiece == 'x'));   // Check for valid input.

        } while (p1valid == false);

        // Set player 2 to remaining option.
        if (TicTacToe::playerOnePiece == 'O' || TicTacToe::playerOnePiece == 'o')
        {
            TicTacToe::playerOnePiece = 'O';
            TicTacToe::playerTwoPiece = 'X';
        }
        else
        {
            TicTacToe::playerOnePiece = 'X';
            TicTacToe::playerTwoPiece = 'O';
        }

        std::cout << "Player 1 is: '" << TicTacToe::playerOnePiece << "'\nPlayer 2 is '" << TicTacToe::playerTwoPiece << "'\n\n";

        // Confirm the choice is okay
        do
        {
            std::cout << "Is this okay? (Y/N):";
            std::cin >> yesNo;

            okayValid = ((char(yesNo) == 'Y'|| char(yesNo) == 'N') || (char(yesNo) == 'y' || char(yesNo) == 'n'));   // Check for valid input.
        } while (okayValid == false);

        if (char(yesNo) == 'Y' || char(yesNo) == 'y')
            isOkay = true;
        else
            isOkay = false;

        system("cls");

    } while (isOkay == false);

}

char TicTacToe::GetPlayerOnePiece()
{
    return TicTacToe::playerOnePiece;
}

char TicTacToe::GetPlayerTwoPiece()
{
    return TicTacToe::playerTwoPiece;
}

void TicTacToe::PlayerOneMove()
{
    char xChar, yChar;
    int xInt, yInt;
    bool validInput = false;

    do
    {
        system("cls");
        TicTacToe::gameBoard.DisplayBoard();

        std::cout << "Player 1, it's your turn:";
        std::cin >> xChar >> yChar;

        xInt = xChar - '0';     // Convert ASCII char number to int equivalent (Conversion works because ASCII '0' == 48, '1' == 49 etc, so '1' - '0' == 49 - 48 = 1.)
        yInt = yChar - '0';

        validInput = TicTacToe::gameBoard.PlacePiece(xInt - 1, yInt - 1, TicTacToe::GetPlayerOnePiece());     // Result has 1 taken away for readability to the user so 1 on the board is 0 in the array.

        if (!validInput)
        {
            if ( (xInt > -1 && xInt < 3) && (yInt > -1 && yInt < 3))    // If co-ordinates are within bounds, space must already be occupied.
            {
                std::cout << "This space is taken, please choose a different space.\n\n";
                system("pause");
            }
            else                                                        // Otherwise inpur is invalid.
            {
                std::cout << "Please enter values between 1 & 3, in the format 'x y'. 1 1 being the top left corner.\n\n";
                system("pause");
            }
        }
    } while (validInput == false);
}

void TicTacToe::PlayerTwoMove()
{
    char xChar, yChar;
    int xInt, yInt;
    bool validInput = false;

    do
    {
        system("cls");
        TicTacToe::gameBoard.DisplayBoard();

        std::cout << "Player 2, it's your turn:";
        std::cin >> xChar >> yChar;

        xInt = xChar - '0';     // Convert ASCII char number to int equivalent (Conversion works because ASCII '0' == 48, '1' == 49 etc, so '1' - '0' == 49 - 48 = 1.)
        yInt = yChar - '0';

        validInput = TicTacToe::gameBoard.PlacePiece(xInt - 1, yInt - 1, TicTacToe::GetPlayerTwoPiece());     // Result has 1 taken away for readability to the user so 1 on the board is 0 in the array.

        if (!validInput)
        {
            if ((xInt > -1 && xInt < 3) && (yInt > -1 && yInt < 3))    // If co-ordinates are within bounds, space must already be occupied.
            {
                std::cout << "This space is taken, please choose a different space.\n\n";
                system("pause");
            }
            else                                                        // Otherwise inpur is invalid.
            {
                std::cout << "Please enter values between 1 & 3, in the format 'x y'. 1 1 being the top left corner.\n\n";
                system("pause");
            }
        }
    } while (validInput == false);
}

int TicTacToe::CheckForWin()
{
    bool boardFull = true;

    // Check for full board.
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (TicTacToe::gameBoard.GetPiece(x, y) == ' ')
                boardFull = false;
        }
    }

    // Check lines 1-3.
    for (int y = 0; y < 3; y++)
    {
        if ((TicTacToe::gameBoard.GetPiece(0, y) == TicTacToe::gameBoard.GetPiece(1, y)) && (TicTacToe::gameBoard.GetPiece(1, y) == TicTacToe::gameBoard.GetPiece(2, y)))
        {
            if (TicTacToe::gameBoard.GetPiece(0, y) == TicTacToe::playerOnePiece)
            {
                TicTacToe::m_WinCondition = P1_WIN;
                return 1;
            }
            else if (TicTacToe::gameBoard.GetPiece(0, y) == TicTacToe::playerTwoPiece)
            {
            TicTacToe::m_WinCondition = P2_WIN;
                return 1;
            }
        }
    }

    // Check lines 4-6.
    for (int x = 0; x < 3; x++)
    {
        if ((TicTacToe::gameBoard.GetPiece(x, 0) == TicTacToe::gameBoard.GetPiece(x, 1)) && (TicTacToe::gameBoard.GetPiece(x, 1) == TicTacToe::gameBoard.GetPiece(x, 2)))
        {
            if (TicTacToe::gameBoard.GetPiece(x, 0) == TicTacToe::playerOnePiece)
            {
                TicTacToe::m_WinCondition = P1_WIN;
                return 1;
            }
            else if (TicTacToe::gameBoard.GetPiece(x, 0) == TicTacToe::playerTwoPiece)
            {
                TicTacToe::m_WinCondition = P2_WIN;
                return 1;
            }
        }
    }

    // Check line 7.
    if ((TicTacToe::gameBoard.GetPiece(0, 0) == TicTacToe::gameBoard.GetPiece(1, 1)) && (TicTacToe::gameBoard.GetPiece(1, 1) == TicTacToe::gameBoard.GetPiece(2, 2)))
    {
        if (TicTacToe::gameBoard.GetPiece(0, 0) == TicTacToe::playerOnePiece)
        {
            TicTacToe::m_WinCondition = P1_WIN;
            return 1;
        }
        else if (TicTacToe::gameBoard.GetPiece(0, 0) == TicTacToe::playerTwoPiece)
        {
            TicTacToe::m_WinCondition = P2_WIN;
            return 1;
        }
    }

    // Check line 8.
    if ((TicTacToe::gameBoard.GetPiece(2, 0) == TicTacToe::gameBoard.GetPiece(1, 1)) && (TicTacToe::gameBoard.GetPiece(1, 1) == TicTacToe::gameBoard.GetPiece(0, 2)))
    {
        if (TicTacToe::gameBoard.GetPiece(2, 0) == TicTacToe::playerOnePiece)
        {
            TicTacToe::m_WinCondition = P1_WIN;
            return 1;
        }
        else if (TicTacToe::gameBoard.GetPiece(2, 0) == TicTacToe::playerTwoPiece)
        {
            TicTacToe::m_WinCondition = P2_WIN;
            return 1;
        }
    }

    if (boardFull)
    {
        TicTacToe::m_WinCondition = DRAW;
        return 0;
    }
    else
        return -1;
}

void TicTacToe::DeclareEndGame()
{
    if (TicTacToe::m_WinCondition == DRAW)
    {
        system("cls");
        TicTacToe::gameBoard.DisplayBoard();
        std::cout << "It's a Draw!\n\n";
    }
    else
    {
        system("cls");
        TicTacToe::gameBoard.DisplayBoard();
        std::cout << "Player " << TicTacToe::m_WinCondition << " Has Won!\n\n";
    }
}

#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <conio.h>
#include "figures.h"
#include <string>
#include <algorithm>

// MOVE FIGURE POSITION
#define TOP -8
#define BOTTOM 8
#define LEFT -1
#define RIGHT 1
#define TOP_LEFT -9
#define TOP_RIGHT -7
#define BOTTOM_LEFT 7
#define BOTTOM_RIGHT 9

#define TOP_TOP -16
#define BOTTOM_BOTTOM 16

#define TOP_TOP_LEFT -17
#define TOP_TOP_RIGHT -15
#define BOTTOM_BOTTOM_LEFT 15
#define BOTTOM_BOTTOM_RIGHT 17
#define LEFT_LEFT_TOP -10
#define LEFT_LEFT_BOTTOM 6
#define RIGHT_RIGHT_TOP -6
#define RIGHT_RIGHT_BOTTOM -10

// BG COLOR
#define YELLOW 2
#define GREEN 3
#define RED 4
#define PURPLE 5
#define YELLOW_2 6

// FIGURE COLOR
#define EMPTY 69 // E
#define WHITE 87 // W
#define BLACK 66 // B

// FIGURES
#define PAWN 80   // P
#define KNIGHT 83 // S
#define BISHOP 71 // G
#define ROOK 87   // W
#define QUEEN 72  // H
#define KING 75   // K

//OTHER
#define EXIT 69     // E
#define PAUSE 80    // P
#define RESIGN 82   // R
#define DRAW 68     // D
#define PLAYER_1 49 // 1
#define PLAYER_2 50 // 2

using namespace std;

void mainMenu();
void newGame();
void resumeGame();
void rematch();
void howToPlay();
void loadScore();
bool yesNoChoice();

void gamePlay();
void resetActiveChoice(); // main menu
void resetArea();
void resetAreaColors();
void resetVirtualAreaColors();    // virtual
void resetVirtualAreaChecking();  // virtual
void resetVirtualAreaEnPassant(); // virtual
void resetCastling();
void refreshArea();
void refreshVirtualArea(); // virtual

void whiteKingCheck();
void blackKingCheck();
void isCheckMate();
void isDraw();
void saveScore();
void clearScore();

void checkingMoveFigures();
void moveFigures();
void moveFigures_VirtualArea(); // virtual
void whoWins();

// --------------- DEV TOOLS --------------- //

void devCommands();
void refreshAreaID();
void refreshAreaPosition();
void refreshAreaNR();
void showAreaStats();
void showBools();
void show();

// --------------- PAINT COLORS --------------- //

void paintAreaColors();
void paintAreaColorsPawn();   // pawn
void paintAreaColorsKnight(); // knight
void paintAreaColorsBishop(); // bishop
void paintAreaColorsRook();   // rook
void paintAreaColorsQueen();  // queen
void paintAreaColorsKing();   // king

void pawnTopSide();               // pawn top
void pawnTopTopSide();            // pawn top top
void pawnTopLeftSide();           // pawn top left
void pawnTopRigtSide();           // pawn top right
void pawnTopLeft_enPassant();     // pawn top left EN PASSANT
void pawnTopRight_enPassant();    // pawn top right EN PASSANT
void pawnBottomSide();            // pawn bottom
void pawnBottomBottomSide();      // pawn bottom bottom
void pawnBottomLeftSide();        // pawn bottom left
void pawnBottomRigtSide();        // pawn bottom right
void pawnBottomLeft_enPassant();  // pawn bottom left EN PASSANT
void pawnBottomRight_enPassant(); // pawn bottom right EN PASSANT

void topSide();         // top
void bottomSide();      // bottom
void leftSide();        // left
void rightSide();       // right
void topLeftSide();     // top left
void topRighttSide();   // top righ
void bottomLeftSide();  // bottom left
void bottomRightSide(); // bottom right

// --------------- VIRTUAL PAINT COLORS --------------- //

void paintVirtualAreaWhiteColors();
void paintVirtualAreaColorsWhitePawn();   // white pawn
void paintVirtualAreaColorsWhiteKnight(); // white knight
void paintVirtualAreaColorsWhiteBishop(); // white bishop
void paintVirtualAreaColorsWhiteRook();   // white rook
void paintVirtualAreaColorsWhiteQueen();  // white queen
void paintVirtualAreaColorsWhiteKing();   // white king

void paintVirtualAreaBlackColors();
void paintVirtualAreaColorsBlackPawn();   // black pawn
void paintVirtualAreaColorsBlackKnight(); // black knight
void paintVirtualAreaColorsBlackBishop(); // black bishop
void paintVirtualAreaColorsBlackRook();   // black rook
void paintVirtualAreaColorsBlackQueen();  // black queen
void paintVirtualAreaColorsBlackKing();   // black king

void virtualWhiteTopSide();         // top
void virtualWhiteBottomSide();      // bottom
void virtualWhiteLeftSide();        // left
void virtualWhiteRightSide();       // right
void virtualWhiteTopLeftSide();     // top left
void virtualWhiteTopRightSide();    // top right
void virtualWhiteBottomLeftSide();  // bottom left
void virtualWhiteBottomRightSide(); // bottom right

void virtualBlackTopSide();         // top
void virtualBlackBottomSide();      // bottom
void virtualBlackLeftSide();        // left
void virtualBlackRightSide();       // right
void virtualBlackTopLeftSide();     // top left
void virtualBlackTopRightSide();    // top right
void virtualBlackBottomLeftSide();  // bottom left
void virtualBlackBottomRightSide(); // bottom right

// --------------- TEXT AND BACKGROUND COLORS --------------- //

void textColorStandard();
void textColorBlue();
void textColorRed();
void textColorYellow();
void textColorGreen();

void bgColorAquaTextColorWhite();
void bgColorAquaTextColorBlack();
void bgColorBlueTextColorWhite();
void bgColorBlueTextColorBlack();

// --------------- GLOBAL VARIABLES --------------- //

bool active_choice[6]{
    true,
    false,
    false,
    false,
    false,
    false};

string player_1{""}, player_2{""};
int whith_player{0};

string old_position{""};
string new_position{""};
short old_position_object_nr{};
short new_position_object_nr{};
short virtual_position_object_nr{};

char winner{' '};
bool active_game{false};

bool active_white_left_castling(true);
bool active_white_right_castling(true);
bool active_black_left_castling(true);
bool active_black_right_castling(true);

bool white_left_rook_move{false};
bool white_right_rook_move{false};
bool black_left_rook_move{false};
bool black_right_rook_move{false};
bool white_king_move{false};
bool black_king_move{false};

bool white_king_check{false};
bool black_king_check{false};

string yes_no_choice_type{};
bool score_exist;

time_t cur_time;
struct tm *date;
char hour[80];

HANDLE hOut;

// --------------- GLOBAL OBJECTS --------------- //

Area area[64]{
    {"a8", 1, 1, 0, BLACK, ROOK, "blackLeftRook", 1},
    {"b8", 1, 2, 1, BLACK, KNIGHT, "blackLeftKnight", 2},
    {"c8", 1, 3, 0, BLACK, BISHOP, "blackDarkBishop", 3},
    {"d8", 1, 4, 1, BLACK, QUEEN, "blackQueen", 4},
    {"e8", 1, 5, 0, BLACK, KING, "blackKing", 5},
    {"f8", 1, 6, 1, BLACK, BISHOP, "blackLightBishop", 6},
    {"g8", 1, 7, 0, BLACK, KNIGHT, "blackRightKnight", 7},
    {"h8", 1, 8, 1, BLACK, ROOK, "blackRightRook", 8},
    {"a7", 2, 1, 1, BLACK, PAWN, "blackPawn1", 9},
    {"b7", 2, 2, 0, BLACK, PAWN, "blackPawn2", 10},
    {"c7", 2, 3, 1, BLACK, PAWN, "blackPawn3", 11},
    {"d7", 2, 4, 0, BLACK, PAWN, "blackPawn4", 12},
    {"e7", 2, 5, 1, BLACK, PAWN, "blackPawn5", 13},
    {"f7", 2, 6, 0, BLACK, PAWN, "blackPawn6", 14},
    {"g7", 2, 7, 1, BLACK, PAWN, "blackPawn7", 15},
    {"h7", 2, 8, 0, BLACK, PAWN, "blackPawn8", 16},
    {"a6", 3, 1, 0, EMPTY, ' ', "", 17},
    {"b6", 3, 2, 1, EMPTY, ' ', "", 18},
    {"c6", 3, 3, 0, EMPTY, ' ', "", 19},
    {"d6", 3, 4, 1, EMPTY, ' ', "", 20},
    {"e6", 3, 5, 0, EMPTY, ' ', "", 21},
    {"f6", 3, 6, 1, EMPTY, ' ', "", 22},
    {"g6", 3, 7, 0, EMPTY, ' ', "", 23},
    {"h6", 3, 8, 1, EMPTY, ' ', "", 24},
    {"a5", 4, 1, 1, EMPTY, ' ', "", 25},
    {"b5", 4, 2, 0, EMPTY, ' ', "", 26},
    {"c5", 4, 3, 1, EMPTY, ' ', "", 27},
    {"d5", 4, 4, 0, EMPTY, ' ', "", 28},
    {"e5", 4, 5, 1, EMPTY, ' ', "", 29},
    {"f5", 4, 6, 0, EMPTY, ' ', "", 30},
    {"g5", 4, 7, 1, EMPTY, ' ', "", 31},
    {"h5", 4, 8, 0, EMPTY, ' ', "", 32},
    {"a4", 5, 1, 0, EMPTY, ' ', "", 33},
    {"b4", 5, 2, 1, EMPTY, ' ', "", 34},
    {"c4", 5, 3, 0, EMPTY, ' ', "", 35},
    {"d4", 5, 4, 1, EMPTY, ' ', "", 36},
    {"e4", 5, 5, 0, EMPTY, ' ', "", 37},
    {"f4", 5, 6, 1, EMPTY, ' ', "", 38},
    {"g4", 5, 7, 0, EMPTY, ' ', "", 39},
    {"h4", 5, 8, 1, EMPTY, ' ', "", 40},
    {"a3", 6, 1, 1, EMPTY, ' ', "", 41},
    {"b3", 6, 2, 0, EMPTY, ' ', "", 42},
    {"c3", 6, 3, 1, EMPTY, ' ', "", 43},
    {"d3", 6, 4, 0, EMPTY, ' ', "", 44},
    {"e3", 6, 5, 1, EMPTY, ' ', "", 45},
    {"f3", 6, 6, 0, EMPTY, ' ', "", 46},
    {"g3", 6, 7, 1, EMPTY, ' ', "", 47},
    {"h3", 6, 8, 0, EMPTY, ' ', "", 48},
    {"a2", 7, 1, 0, WHITE, PAWN, "whitePawn1", 49},
    {"b2", 7, 2, 1, WHITE, PAWN, "whitePawn2", 50},
    {"c2", 7, 3, 0, WHITE, PAWN, "whitePawn3", 51},
    {"d2", 7, 4, 1, WHITE, PAWN, "whitePawn4", 52},
    {"e2", 7, 5, 0, WHITE, PAWN, "whitePawn5", 53},
    {"f2", 7, 6, 1, WHITE, PAWN, "whitePawn6", 54},
    {"g2", 7, 7, 0, WHITE, PAWN, "whitePawn7", 55},
    {"h2", 7, 8, 1, WHITE, PAWN, "whitePawn8", 56},
    {"a1", 8, 1, 1, WHITE, ROOK, "whiteLeftRook", 57},
    {"b1", 8, 2, 0, WHITE, KNIGHT, "whiteLeftKnight", 58},
    {"c1", 8, 3, 1, WHITE, BISHOP, "whiteLightBishop", 59},
    {"d1", 8, 4, 0, WHITE, QUEEN, "whiteQueen", 60},
    {"e1", 8, 5, 1, WHITE, KING, "whiteKing", 61},
    {"f1", 8, 6, 0, WHITE, BISHOP, "whiteDarkBishop", 62},
    {"g1", 8, 7, 1, WHITE, KNIGHT, "whiteRightKnight", 63},
    {"h1", 8, 8, 0, WHITE, ROOK, "whiteRightRook", 64}};

Area virtual_area[64]{
    {"a8", 1, 1, 0, BLACK, ROOK, "blackLeftRook", 1},
    {"b8", 1, 2, 1, BLACK, KNIGHT, "blackLeftKnight", 2},
    {"c8", 1, 3, 0, BLACK, BISHOP, "blackDarkBishop", 3},
    {"d8", 1, 4, 1, BLACK, QUEEN, "blackQueen", 4},
    {"e8", 1, 5, 0, BLACK, KING, "blackKing", 5},
    {"f8", 1, 6, 1, BLACK, BISHOP, "blackLightBishop", 6},
    {"g8", 1, 7, 0, BLACK, KNIGHT, "blackRightKnight", 7},
    {"h8", 1, 8, 1, BLACK, ROOK, "blackRightRook", 8},
    {"a7", 2, 1, 1, BLACK, PAWN, "blackPawn1", 9},
    {"b7", 2, 2, 0, BLACK, PAWN, "blackPawn2", 10},
    {"c7", 2, 3, 1, BLACK, PAWN, "blackPawn3", 11},
    {"d7", 2, 4, 0, BLACK, PAWN, "blackPawn4", 12},
    {"e7", 2, 5, 1, BLACK, PAWN, "blackPawn5", 13},
    {"f7", 2, 6, 0, BLACK, PAWN, "blackPawn6", 14},
    {"g7", 2, 7, 1, BLACK, PAWN, "blackPawn7", 15},
    {"h7", 2, 8, 0, BLACK, PAWN, "blackPawn8", 16},
    {"a6", 3, 1, 0, EMPTY, ' ', "", 17},
    {"b6", 3, 2, 1, EMPTY, ' ', "", 18},
    {"c6", 3, 3, 0, EMPTY, ' ', "", 19},
    {"d6", 3, 4, 1, EMPTY, ' ', "", 20},
    {"e6", 3, 5, 0, EMPTY, ' ', "", 21},
    {"f6", 3, 6, 1, EMPTY, ' ', "", 22},
    {"g6", 3, 7, 0, EMPTY, ' ', "", 23},
    {"h6", 3, 8, 1, EMPTY, ' ', "", 24},
    {"a5", 4, 1, 1, EMPTY, ' ', "", 25},
    {"b5", 4, 2, 0, EMPTY, ' ', "", 26},
    {"c5", 4, 3, 1, EMPTY, ' ', "", 27},
    {"d5", 4, 4, 0, EMPTY, ' ', "", 28},
    {"e5", 4, 5, 1, EMPTY, ' ', "", 29},
    {"f5", 4, 6, 0, EMPTY, ' ', "", 30},
    {"g5", 4, 7, 1, EMPTY, ' ', "", 31},
    {"h5", 4, 8, 0, EMPTY, ' ', "", 32},
    {"a4", 5, 1, 0, EMPTY, ' ', "", 33},
    {"b4", 5, 2, 1, EMPTY, ' ', "", 34},
    {"c4", 5, 3, 0, EMPTY, ' ', "", 35},
    {"d4", 5, 4, 1, EMPTY, ' ', "", 36},
    {"e4", 5, 5, 0, EMPTY, ' ', "", 37},
    {"f4", 5, 6, 1, EMPTY, ' ', "", 38},
    {"g4", 5, 7, 0, EMPTY, ' ', "", 39},
    {"h4", 5, 8, 1, EMPTY, ' ', "", 40},
    {"a3", 6, 1, 1, EMPTY, ' ', "", 41},
    {"b3", 6, 2, 0, EMPTY, ' ', "", 42},
    {"c3", 6, 3, 1, EMPTY, ' ', "", 43},
    {"d3", 6, 4, 0, EMPTY, ' ', "", 44},
    {"e3", 6, 5, 1, EMPTY, ' ', "", 45},
    {"f3", 6, 6, 0, EMPTY, ' ', "", 46},
    {"g3", 6, 7, 1, EMPTY, ' ', "", 47},
    {"h3", 6, 8, 0, EMPTY, ' ', "", 48},
    {"a2", 7, 1, 0, WHITE, PAWN, "whitePawn1", 49},
    {"b2", 7, 2, 1, WHITE, PAWN, "whitePawn2", 50},
    {"c2", 7, 3, 0, WHITE, PAWN, "whitePawn3", 51},
    {"d2", 7, 4, 1, WHITE, PAWN, "whitePawn4", 52},
    {"e2", 7, 5, 0, WHITE, PAWN, "whitePawn5", 53},
    {"f2", 7, 6, 1, WHITE, PAWN, "whitePawn6", 54},
    {"g2", 7, 7, 0, WHITE, PAWN, "whitePawn7", 55},
    {"h2", 7, 8, 1, WHITE, PAWN, "whitePawn8", 56},
    {"a1", 8, 1, 1, WHITE, ROOK, "whiteLeftRook", 57},
    {"b1", 8, 2, 0, WHITE, KNIGHT, "whiteLeftKnight", 58},
    {"c1", 8, 3, 1, WHITE, BISHOP, "whiteLightBishop", 59},
    {"d1", 8, 4, 0, WHITE, QUEEN, "whiteQueen", 60},
    {"e1", 8, 5, 1, WHITE, KING, "whiteKing", 61},
    {"f1", 8, 6, 0, WHITE, BISHOP, "whiteDarkBishop", 62},
    {"g1", 8, 7, 1, WHITE, KNIGHT, "whiteRightKnight", 63},
    {"h1", 8, 8, 0, WHITE, ROOK, "whiteRightRook", 64}};

int main()
{
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    mainMenu();
    return 0;
}

void mainMenu()
{
    short choice{0};
    bool push_active{false};
    bool push_exit(false);

    do
    {
        system("cls");

        fstream plik;
        plik.open("story.txt", ios::in);

        if (plik.good() == false)
            score_exist = false;
        else
        {
            score_exist = true;
            plik.close();
        }

        if (active_choice[0] == true)
        {
            bgColorBlueTextColorWhite();
            cout << "NOWA GRA\n";
            textColorStandard();
        }
        else
        {
            textColorStandard();
            cout << "NOWA GRA\n";
        }

        if (active_choice[1] == true)
        {
            if (winner == PAUSE)
            {
                bgColorBlueTextColorWhite();
                cout << "WZNOW GRE\n";
                textColorStandard();
            }
            else if (winner == PLAYER_1 || winner == PLAYER_2 || winner == DRAW || winner == EXIT)
            {
                bgColorBlueTextColorWhite();
                cout << "REWANZ\n";
                textColorStandard();
            }
        }
        else
        {
            if (winner == PAUSE)
            {
                textColorBlue();
                cout << "WZNOW GRE\n";
                textColorStandard();
            }
            else if (winner == PLAYER_1 || winner == PLAYER_2 || winner == DRAW || winner == EXIT)
            {
                textColorBlue();
                cout << "REWANZ\n";
                textColorStandard();
            }
            else
            {
                textColorRed();
                cout << "WZNOW GRE\n";
                textColorStandard();
            }
        }

        if (active_choice[2] == true)
        {
            bgColorBlueTextColorWhite();
            cout << "JAK GRAC\n";
            textColorStandard();
        }
        else
        {
            cout << "JAK GRAC\n";
        }

        if (active_choice[3] == true)
        {
            bgColorBlueTextColorWhite();
            cout << "HISTORIA GIER\n";
            textColorStandard();
        }
        else
        {
            if (score_exist == false)
            {
                textColorRed();
                cout << "HISTORIA GIER\n";
                textColorStandard();
            }
            else
            {
                cout << "HISTORIA GIER\n";
            }
        }

        if (active_choice[4] == true)
        {
            bgColorBlueTextColorWhite();
            cout << "WYCZYSC HISTORIE\n";
            textColorStandard();
        }
        else
        {
            if (score_exist == false)
            {
                textColorRed();
                cout << "WYCZYSC HISTORIE\n";
                textColorStandard();
            }
            else
            {
                cout << "WYCZYSC HISTORIE\n";
            }
        }

        if (active_choice[5] == true)
        {
            bgColorBlueTextColorWhite();
            cout << "WYJSCIE\n";
            textColorStandard();
        }
        else
        {
            cout << "WYJSCIE\n";
        }

        unsigned char sign = getch();
        switch (sign)
        {
        case 224:
            sign = getch();
            switch (sign)
            {
            case 72: // UP
            {
                for (int i = 0; i < 6; i++)
                {
                    if (active_choice[i] == true && i == 0)
                    {
                        active_choice[0] = false;
                        active_choice[5] = true;
                        break;
                    }
                    else if (active_choice[2] == true && i == 2 && winner == ' ')
                    {
                        active_choice[2] = false;
                        active_choice[0] = true;
                        break;
                    }
                    else if (active_choice[5] == true && i == 0 && score_exist == false)
                    {
                        active_choice[5] = false;
                        active_choice[2] = true;
                        break;
                    }
                    else if (active_choice[i] == true)
                    {
                        active_choice[i] = false;
                        active_choice[i - 1] = true;
                        break;
                    }
                }
                Sleep(50);
                break;
            }
            case 80: // DOWN
            {
                for (int i = 0; i < 6; i++)
                {
                    if (active_choice[i] == true && i == 5)
                    {
                        active_choice[5] = false;
                        active_choice[0] = true;
                        break;
                    }
                    else if (active_choice[0] == true && i == 0 && winner == ' ')
                    {
                        active_choice[0] = false;
                        active_choice[2] = true;
                        break;
                    }
                    else if (active_choice[2] == true && i == 0 && score_exist == false)
                    {
                        active_choice[2] = false;
                        active_choice[5] = true;
                        break;
                    }
                    else if (active_choice[i] == true)
                    {
                        active_choice[i] = false;
                        active_choice[i + 1] = true;
                        break;
                    }
                }
                Sleep(50);
                break;
            }
            }
            sign = 0;
            break;
        case 13: // ENTER
        {
            for (int i = 0; i < 6; i++)
            {
                if (active_choice[i] == true)
                    choice = i;
            }

            if (choice == 0)
            {
                newGame();
            }
            else if (choice == 1)
            {
                if (winner == PAUSE)
                    resumeGame();
                else if (winner == EXIT || winner == PLAYER_1 || winner == PLAYER_2 || winner == DRAW)
                    rematch();
                else
                {
                    textColorRed();
                    cout << "\nMusisz najpierw rozegrac gre by uzyc tej opcji . . .";
                    textColorStandard();
                    Sleep(1500);
                }
            }
            else if (choice == 2)
            {
                howToPlay();
            }
            else if (choice == 3)
            {
                loadScore();
            }

            else if (choice == 4)
            {
                yes_no_choice_type = "clear";
                if (yesNoChoice() == false)
                    clearScore();
                resetActiveChoice();
            }

            else if (choice == 5)
            {
                yes_no_choice_type = "exit";
                if (yesNoChoice() == false)
                {
                    push_exit = true;
                    break;
                }

                else
                    break;
            }
            break;
        }

        case 27: // ESC
        {
            yes_no_choice_type = "exit";
            if (yesNoChoice() == false)
            {
                push_exit = true;
                break;
            }

            else
                break;
        }
        }
    } while (push_exit != true);
}

void newGame()
{
    system("cls");
    cout << "Podaj nazwe 1 gracza: ";
    cin >> player_1;
    cout << "Podaj nazwe 2 gracza: ";
    cin >> player_2;
    resetArea();
    resetCastling();
    gamePlay();
}

void resumeGame()
{
    system("cls");
    gamePlay();
}

void rematch()
{
    string temp_player_1{};
    temp_player_1 = player_1;

    player_1 = player_2;
    player_2 = temp_player_1;
    winner = ' ';
    whith_player = 2;
    resetArea();
    resetCastling();
    gamePlay();
}
void howToPlay()
{
    system("cls");
    textColorYellow();
    cout << "Poruszanie sie figurami po szachownicy odbywa sie za pomoca komend slownych.\n\n";
    textColorStandard();
    cout << "W pozycji";
    textColorYellow();
    cout << " \"Ktora figure poruszyc\" ";
    textColorStandard();
    cout << "nalezy wpisac polozenie figury na szachownicy, ktora chcemy zlapac (np.";
    textColorRed();
    cout << " e2 ";
    textColorStandard();
    cout << ").\n\nNastepnie w pozycji";
    textColorYellow();
    cout << " \"Gdzie postawic figure\" ";
    textColorStandard();
    cout << "nalezy wpisac na ktore miejsce na szachownicy chcemy przesunac figure (np.";
    textColorRed();
    cout << " e4 ";
    textColorStandard();
    cout << ").\n\nAby zmienic juz wybrana figure na inna wpisz komende";
    textColorRed();
    cout << " powtorz ";
    textColorStandard();
    cout << ".";

    if (active_game == false)
    {
        textColorStandard();
        cout << "\n\n\nWcisnij ENTER by wrocic do Menu Glownego . . .";
        getchar();
    }
    else
    {
        textColorStandard();
        cout << "\n\n\nWcisnij ENTER by wrocic do gry . . .";
        getchar();
        getchar();
        gamePlay();
    }
}

bool yesNoChoice()
{
    bool ret{};
    bool push_exit = false;
    bool yes_no_active[2]{
        false,
        true,
    };

    if (yes_no_choice_type == "draw")
        whith_player++;

    while (push_exit == false)
    {
        system("cls");

        if (yes_no_choice_type == "exit")
            cout << "Czy napewno chcesz opuscic gre?\n";
        else if (yes_no_choice_type == "clear")
            cout << "Czy napewno chcesz wyczyscic historie gier?\n";
        else if (yes_no_choice_type == "draw")
        {
            refreshArea();
            textColorStandard();
            cout << "\n\nGracz ";
            if (whith_player % 2 == 0)
            {
                textColorBlue();
                cout << player_2;
                textColorStandard();
            }
            else
            {
                textColorBlue();
                cout << player_1;
                textColorStandard();
            }
            cout << " zaproponowal remis. Czy sie na to zgadzasz?\n";
        }
        else if (yes_no_choice_type == "resign")
        {
            refreshArea();
            cout << "\n\nCzy napewno chcesz sie poddac?\n";
        }
        else if (yes_no_choice_type == "abandon")
        {
            refreshArea();
            cout << "\n\nCzy napewno chcesz porzucic partie?\n";
        }
        if (yes_no_active[0] == false)
        {
            bgColorBlueTextColorWhite();
            cout << "NIE\n";
            textColorStandard();
            cout << "TAK\n";
        }
        else
        {
            textColorStandard();
            cout << "NIE\n";
            bgColorBlueTextColorWhite();
            cout << "TAK\n";
            textColorStandard();
        }

        unsigned char are_you_sure = getch();
        switch (are_you_sure)
        {
        case 224:
            are_you_sure = getch();
            switch (are_you_sure)
            {
            case 72: // UP
            {
                if (yes_no_active[0] == true)
                {
                    yes_no_active[0] = false;
                    yes_no_active[1] = true;
                }
                else
                {
                    yes_no_active[0] = true;
                    yes_no_active[1] = false;
                }
                Sleep(50);
                break;
            }
            case 80: // DOWN
            {
                if (yes_no_active[0] == true)
                {
                    yes_no_active[0] = false;
                    yes_no_active[1] = true;
                }
                else
                {
                    yes_no_active[0] = true;
                    yes_no_active[1] = false;
                }
                Sleep(50);
                break;
            }
            }
            break;

        case 13: // ENTER
        {
            if (yes_no_active[0] == true)
            {
                push_exit = true;
                ret = false;
                break;
            }

            else
            {
                push_exit = true;
                ret = true;
                break;
            }
        }
        case 27: // ESC
        {
            push_exit = true;
            ret = true;
            break;
        }
        }
    }

    if (yes_no_choice_type == "draw")
        whith_player--;

    if (ret == false)
        return false;

    else
        return true;
}

void gamePlay()
{
    winner = ' ';
    active_game = true;
    resetAreaColors();
    resetVirtualAreaColors();
    resetVirtualAreaEnPassant();

    refreshArea();

    while (winner == ' ')
    {
        resetVirtualAreaChecking();
        resetVirtualAreaColors();
        for (int j = 0; j < 64; j++)
        {
            if (whith_player % 2 == 1)
            {
                virtual_position_object_nr = j;
                paintVirtualAreaWhiteColors();
            }
            else
            {
                virtual_position_object_nr = j;
                paintVirtualAreaBlackColors();
            }
        }

        whiteKingCheck();
        blackKingCheck();

        isCheckMate();
        isDraw();
        whoWins();

        if (winner == PLAYER_1 || winner == PLAYER_2 || winner == DRAW)
            break;

        resetAreaColors();
        checkingMoveFigures();
        if (winner != EXIT && winner != PAUSE && winner != DRAW && winner != PLAYER_1 & winner != PLAYER_2)
        {
            moveFigures();
            moveFigures_VirtualArea();
        }
    }
}

void resetActiveChoice()
{
    for (int i = 0; i < 6; i++)
    {
        if (i == 0)
            active_choice[i] = true;
        else
            active_choice[i] = false;
    }
}

void resetArea()
{
    for (int i = 0; i < 64; i++)
    {
        area[i].resetFigures();
    }
    for (int i = 0; i < 64; i++)
    {
        virtual_area[i].resetFigures();
    }
}

void resetAreaColors()
{
    for (int i = 0; i < 64; i++)
    {
        area[i].resetBgColor();
    }
}

void resetVirtualAreaColors()
{
    for (int i = 0; i < 64; i++)
    {
        virtual_area[i].resetBgColor();
    }
}

void resetVirtualAreaChecking()
{
    for (int i = 0; i < 64; i++)
    {
        virtual_area[i].resetChecking();
    }
}

void resetVirtualAreaEnPassant()
{
    for (int i = 0; i < 64; i++)
    {
        virtual_area[i].resetEnPassant();
    }
}

void resetCastling()
{
    active_white_left_castling = true;
    active_white_right_castling = true;
    active_black_left_castling = true;
    active_black_right_castling = true;

    white_left_rook_move = false;
    white_right_rook_move = false;
    black_left_rook_move = false;
    black_right_rook_move = false;
    white_king_move = false;
    black_king_move = false;
    white_king_check = false;
    black_king_check = false;
}

void refreshArea()
{
    system("cls");

    int nr = 8;

    for (int i = 0; i < 64; i++)
    {

        if (whith_player % 2 == 1)
            bgColorBlueTextColorWhite();
        else
            textColorStandard();

        if (i == 0)
            cout << player_2 << endl;

        textColorBlue();

        if (i == 0)
            cout << "    a  b  c  d  e  f  g  h  " << endl;
        if (i % 8 == 0)
        {
            cout << " " << nr << " ";
        }

        area[i].drawArea();
        textColorBlue();

        if ((i + 1) % 8 == 0)
        {
            cout << " " << nr << " ";
            if (i == 15)
            {
                textColorYellow();
                cout << "\tP = Pionek";
            }
            if (i == 23)
            {
                textColorYellow();
                cout << "\tW = Wieza";
            }
            if (i == 31)
            {
                textColorYellow();
                cout << "\tS = Skoczek";
            }
            if (i == 39)
            {
                textColorYellow();
                cout << "\tG = Goniec";
            }
            if (i == 47)
            {
                textColorYellow();
                cout << "\tH = Hetman";
            }
            if (i == 55)
            {
                textColorYellow();
                cout << "\tK = Krol";
            }
        }

        if (i != 0 && (i + 1) % 8 == 0)
        {
            cout << endl;
            nr--;
        }
        if (i == 63)
            cout << "    a  b  c  d  e  f  g  h  " << endl;

        if (whith_player % 2 == 0)
            bgColorBlueTextColorWhite();
        else
            textColorStandard();

        if (i == 63)
            cout << "\t\t\t" << player_1;
    }

    textColorYellow();
    cout << "\n\nSPIS KOMEND: ";

    textColorRed();
    cout << "\njak";
    textColorStandard();
    cout << "\tjak grac?";

    textColorRed();
    cout << "\ndev";
    textColorStandard();
    cout << "\twyswietl komendy dla Dewelopera";

    textColorRed();
    cout << "\npowtorz";
    textColorStandard();
    cout << "\twybierz inna figure";

    textColorRed();
    cout << "\nstop";
    textColorStandard();
    cout << "\twstrzymaj gre";

    textColorRed();
    cout << "\nremis";
    textColorStandard();
    cout << "\tzaproponuj remis";

    textColorRed();
    cout << "\npoddaj";
    textColorStandard();
    cout << "\tpoddaj partie";

    textColorRed();
    cout << "\nwyjdz";
    textColorStandard();
    cout << "\tporzuc partie";
}

void refreshVirtualArea()
{
    cout << endl;

    int nr = 8;

    for (int i = 0; i < 64; i++)
    {

        if (whith_player % 2 == 1)
            bgColorBlueTextColorWhite();
        else
            textColorStandard();

        if (i == 0)
            cout << player_2 << endl;

        textColorBlue();

        if (i == 0)
            cout << "    a  b  c  d  e  f  g  h  " << endl;
        if (i % 8 == 0)
        {
            cout << " " << nr << " ";
        }

        virtual_area[i].drawArea();
        textColorBlue();

        if ((i + 1) % 8 == 0)
        {
            cout << " " << nr << " ";
        }

        if (i != 0 && (i + 1) % 8 == 0)
        {
            cout << endl;
            nr--;
        }
        if (i == 63)
            cout << "    a  b  c  d  e  f  g  h  " << endl;

        if (whith_player % 2 == 0)
            bgColorBlueTextColorWhite();
        else
            textColorStandard();

        if (i == 63)
            cout << "\t\t\t" << player_1;
    }
    textColorStandard();
}

void devCommands()
{
    textColorRed();
    cout << "show";
    textColorStandard();
    cout << "\tWyswietla zawartosc zmiennych w obiektach klasy ";
    textColorYellow();
    cout << "Area\n";

    textColorRed();
    cout << "showa";
    textColorStandard();
    cout << "\tWyswietla trzy pogladowe szachownice:\n"
         << "\t - Pierwsza uwidacznia zmienna ";
    textColorYellow();
    cout << "id\n";
    textColorStandard();

    cout << "\t - Druga uwidacznia zmienna ";
    textColorYellow();
    cout << "position\n";
    textColorStandard();

    cout << "\t - Trzecia uwidacznia zmienna row oraz column ";
    textColorYellow();
    cout << "row";
    textColorStandard();
    cout << " oraz ";
    textColorYellow();
    cout << "column\n";

    textColorRed();
    cout << "showb";
    textColorStandard();
    cout << "\tWyswietla zawartosc zmiennych globalnych typu bool\n";

    textColorRed();
    cout << "showv";
    textColorStandard();
    cout << "\tWyswietla podglad wirtualnej szachownicy\n\n";
}

void refreshAreaID()
{
    int nr = 1;
    textColorYellow();
    cout << "area[].id-1\n";
    for (int i = 0; i < 64; i++)
    {
        textColorBlue();

        if (i == 0)
            cout << "    1  2  3  4  5  6  7  8  " << endl;
        if (i % 8 == 0)
        {
            cout << " " << nr << " ";
        }

        area[i].drawAreaID();
        textColorBlue();

        if (i != 0 && (i + 1) % 8 == 0)
        {
            cout << endl;
            nr++;
        }
        if (i == 63)
            cout << "    1  2  3  4  5  6  7  8  " << endl;
    }
    textColorStandard();
}

void refreshAreaPosition()
{
    int nr = 8;
    textColorYellow();
    cout << "area[].position\n";
    for (int i = 0; i < 64; i++)
    {
        textColorBlue();

        if (i == 0)
            cout << "    a  b  c  d  e  f  g  h  " << endl;
        if (i % 8 == 0)
        {
            cout << " " << nr << " ";
        }

        area[i].drawAreaPosition();
        textColorBlue();

        if (i != 0 && (i + 1) % 8 == 0)
        {
            cout << endl;
            nr--;
        }
        if (i == 63)
            cout << "    a  b  c  d  e  f  g  h  " << endl;
    }
    textColorStandard();
}

void refreshAreaNR()
{
    int nr = 8;
    textColorYellow();
    cout << "area[].row && area[].column\n";
    for (int i = 0; i < 64; i++)
    {
        textColorBlue();

        if (i == 0)
            cout << "    a  b  c  d  e  f  g  h  " << endl;
        if (i % 8 == 0)
        {
            cout << " " << nr << " ";
        }

        area[i].drawAreaNR();
        textColorBlue();

        if (i != 0 && (i + 1) % 8 == 0)
        {
            cout << endl;
            nr--;
        }
        if (i == 63)
            cout << "    a  b  c  d  e  f  g  h  " << endl;
    }
    textColorStandard();
}

void whiteKingCheck()
{
    for (int j = 0; j < 64; j++)
    {
        if (virtual_area[j].big_figure == "whiteKing" && virtual_area[j].bg_color == GREEN)
        {
            white_king_check = true;
            break;
        }
        white_king_check = false;
    }
}

void blackKingCheck()
{
    for (int j = 0; j < 64; j++)
    {
        if (virtual_area[j].big_figure == "blackKing" && virtual_area[j].bg_color == GREEN)
        {
            black_king_check = true;
            break;
        }
        black_king_check = false;
    }
}

void isCheckMate()
{
    bool check_mate{true};

    if (black_king_check == true)
    {
        for (int i = 0; i < 64; i++)
        {
            old_position_object_nr = i;
            if (area[old_position_object_nr].figure_color == BLACK)
                paintAreaColors();
        }
        for (int j = 0; j < 64; j++)
        {
            if (area[j].bg_color == GREEN || area[j].bg_color == RED)
            {
                check_mate = false;
            }
        }
        if (check_mate == true)
            winner = PLAYER_1;
    }

    else if (white_king_check == true)
    {
        for (int i = 0; i < 64; i++)
        {
            old_position_object_nr = i;
            if (area[old_position_object_nr].figure_color == WHITE)
                paintAreaColors();

            for (int j = 0; j < 64; j++)
            {
                if (area[j].bg_color == GREEN || area[j].bg_color == RED)
                {
                    check_mate = false;
                    break;
                }
            }
        }
        if (check_mate == true)
            winner = PLAYER_2;
    }
}

void isDraw()
{
    bool is_draw;
    short figures_counter{0};

    for (int i = 0; i < 64; i++)
    {
        if (area[i].figure != ' ')
            figures_counter++;
    }
    if (figures_counter > 2)
        is_draw = false;

    if (figures_counter == 2)
        is_draw = true;
    else if (whith_player % 2 == 1 && black_king_check == false)
    {
        is_draw == true;
        for (int i = 0; i < 64; i++)
        {
            old_position_object_nr = i;
            if (area[old_position_object_nr].figure_color == BLACK)
                paintAreaColors();

            for (int j = 0; j < 64; j++)
            {
                if (area[j].bg_color == GREEN || area[j].bg_color == RED)
                {
                    is_draw = false;
                    break;
                }
            }
        }
        if (is_draw == true)
            winner = DRAW;
    }

    else if (whith_player % 2 == 0 && white_king_check == false)
    {
        is_draw == true;
        for (int i = 0; i < 64; i++)
        {
            old_position_object_nr = i;
            if (area[old_position_object_nr].figure_color == WHITE)
                paintAreaColors();

            for (int j = 0; j < 64; j++)
            {
                if (area[j].bg_color == GREEN || area[j].bg_color == RED)
                {
                    is_draw = false;
                    break;
                }
            }
        }
        if (is_draw == true)
            winner = DRAW;
    }
}

void saveScore()
{
    string who_win{};
    fstream file;
    file.open("story.txt", ios::out | ios::app);

    file << player_1 << endl;
    file << player_2 << endl;
    if (winner == PLAYER_1)
        who_win = "1";
    else if (winner == PLAYER_2)
        who_win = "2";
    else if (winner == DRAW)
        who_win = "R";
    file << who_win << endl;
    file << hour << endl;

    file.close();
}

void loadScore()
{
    string *p1;
    p1 = new string[1000];

    string *p2;
    p2 = new string[1000];

    string *t;
    t = new string[1000];

    int *ww;
    ww = new int[1000];

    for (int i = 0; i < 1000; i++)
    {
        ww[i] = 3;
    }

    fstream plik;
    plik.open("story.txt", ios::in);

    if (plik.good() == false)
    {
        textColorRed();
        cout << endl
             << "Nie ma jeszcze historii . . .";
        textColorStandard();
        Sleep(1500);
    }
    else
    {
        string line; //pamiec tymczasowa, ktora przechowuje aktualnie zczytywana linie tekstu z pliku
        int nr_switch = 1;

        int nr_tab = 0;
        while (getline(plik, line)) //wczytuje po kolei wszystkie linie z pliku tekstowego
        {

            switch (nr_switch)
            {
            case 1:
                p1[nr_tab] = line;
                break; //zapisuje zawartosc 1 linii w zmiennej p1
            case 2:
                p2[nr_tab] = line;
                break; //zapisuje zawartosc 1 linii w zmiennej p2
            case 3:
                ww[nr_tab] = atoi(line.c_str());
                break; //zapisuje zawartosc 1 linii w zmiennej ww
            case 4:
                t[nr_tab] = line;
                break; //zapisuje zawartosc 1 linii w zmiennej time
            }

            if (nr_switch % 4 == 0)
                nr_tab++;
            nr_switch++;
            if (nr_switch > 4)
                nr_switch = 1;
        }

        system("cls");

        for (int j = 0; j < 100; j++)
        {
            if (ww[j] == 3)
                break;
            cout << endl
                 << j + 1 << ". ";
            textColorYellow();
            cout << t[j];
            textColorStandard();
            cout << " | ";
            textColorGreen();
            cout << p1[j];
            textColorStandard();
            cout << " vs ";
            textColorRed();
            cout << p2[j];
            textColorStandard();
            cout << " | ";
            if (ww[j] == 1)
            {
                cout << "Wygral: ";
                bgColorBlueTextColorWhite();
                cout << p1[j] << endl;
                textColorStandard();
            }
            else if (ww[j] == 2)
            {
                cout << "Wygral: ";
                bgColorBlueTextColorWhite();
                cout << p2[j] << endl;
                textColorStandard();
            }
            else if (ww[j] == 0)
            {
                textColorBlue();
                cout << "REMIS" << endl;
                textColorStandard();
            }
        }

        plik.close();
        cout << endl
             << endl
             << "Nacisnij ENTER aby wrocic do menu glownego...";

        getchar();
    }
}

void clearScore()
{
    textColorRed();
    cout << endl
         << "Historia gier zostala wyczyszczona . . .";
    textColorStandard();
    Sleep(1000);
    remove("story.txt");
}

void checkingMoveFigures()
{
    string check{""};

    refreshArea();

    // CHECKING OLD POSITION

    do
    {
        textColorYellow();
        cout << "\n\nKtora figure poruszyc?: ";
        textColorRed();
        cin >> old_position;
        transform(old_position.begin(), old_position.end(), old_position.begin(), ::tolower);

        if (old_position == "p" || old_position == "pause" || old_position == "stop")
        {
            winner = PAUSE;
            check = "pause";
        }

        else if (old_position == "e" || old_position == "exit" || old_position == "w" || old_position == "wyjscie" || old_position == "wyjdz" || old_position == "abandon")
        {
            yes_no_choice_type = "abandon";
            if (yesNoChoice() == false)
            {
                winner = EXIT;
                check = "exit";
                active_game = false;
            }
            else
            {
                check = "again";
                refreshArea();
            }
        }

        else if (old_position == "a" || old_position == "again" || old_position == "powtorz")
        {
            check = "again";
            textColorRed();
            cout << "\nJeszcze nie wybrales figury!";
            textColorStandard();
            Sleep(1500);
            refreshArea();
        }

        else if (old_position == "j" || old_position == "jak" || old_position == "how")
        {
            winner = PAUSE;
            check = "how";
            howToPlay();
        }

        else if (old_position == "r" || old_position == "resign" || old_position == "poddaj")
        {
            yes_no_choice_type = "resign";
            if (yesNoChoice() == false)
            {
                winner = RESIGN;
                check = "resign";
                refreshArea();
                whoWins();
            }
            else
            {
                check = "again";
                refreshArea();
            }
        }
        else if (old_position == "remis")
        {
            yes_no_choice_type = "draw";
            if (yesNoChoice() == false)
            {
                winner = DRAW;
                check = "remis";
                refreshArea();
                whoWins();
            }
            else
            {
                check = "again";
                refreshArea();
            }
        }

        else if (old_position == "showb")
        {
            showBools();
            system("pause");
            refreshArea();
            check = "again";
        }

        else if (old_position == "showv")
        {
            system("cls");
            refreshVirtualArea();
            cout << endl;
            system("pause");
            refreshArea();
            check = "again";
        }
        else if (old_position == "showa")
        {
            system("cls");
            refreshAreaID();
            cout << endl;
            system("pause");
            system("cls");
            refreshAreaPosition();
            cout << endl;
            system("pause");
            system("cls");
            refreshAreaNR();
            cout << endl;
            system("pause");
            refreshArea();
            check = "again";
        }

        else if (old_position == "show")
        {
            show();
            system("pause");
            refreshArea();
            check = "again";
        }

        else if (old_position == "dev")
        {
            system("cls");
            devCommands();
            system("pause");
            refreshArea();
            check = "again";
        }

        else
        {
            for (int i = 0; i < 65; i++)
            {
                if (old_position == area[i].position)
                {
                    if (whith_player % 2 == 0 && area[i].figure_color == BLACK || whith_player % 2 == 1 && area[i].figure_color == WHITE)
                    {
                        check = "enemy_figure";
                        textColorRed();
                        cout << "\nTo nie jest figura Twojego koloru!";
                        textColorStandard();
                        Sleep(1500);
                        refreshArea();
                        break;
                    }
                    else if (area[i].figure == ' ')
                    {
                        check = "empty";
                        textColorRed();
                        cout << "\nWybrales puste pole!";
                        textColorStandard();
                        Sleep(1500);
                        refreshArea();
                        break;
                    }

                    else
                    {
                        /////////////////////////////////////// correctly selected figure ///////////////////////////////////////

                        old_position_object_nr = i;
                        paintAreaColors();
                        area[old_position_object_nr].bg_color = YELLOW;
                        refreshArea();
                        check = "pass";
                        break;
                    }
                }
                if (i == 64 && check != "enemy_figure")
                {
                    check = "bad_position";
                    cout << "Podales niepoprawna pozycje . . .";
                    Sleep(1500);
                    refreshArea();
                }
            }
        }
    } while (check == "bad_position" || check == "enemy_figure" || check == "again" || check == "empty");

    // CHECKING NEW POSITION

    do
    {
        if (old_position == "p" || old_position == "pause" || old_position == "stop" || old_position == "e" || old_position == "exit" || old_position == "w" || old_position == "wyjscie" || old_position == "wyjdz" || old_position == "j" || old_position == "jak" || old_position == "how" || old_position == "r" || old_position == "resign" || old_position == "poddaj" || old_position == "remis")
        {
            break;
        }
        else
        {
            textColorYellow();
            cout << "\n\nGdzie postawic figure? ";
            textColorRed();
            cin >> new_position;
            transform(new_position.begin(), new_position.end(), new_position.begin(), ::tolower);

            if (new_position == "a" || new_position == "again" || new_position == "powtorz")
            {
                resetAreaColors();
                checkingMoveFigures();
                check = "pass";
            }

            else if (new_position == "j" || new_position == "jak" || new_position == "how")
            {
                winner = PAUSE;
                check = "how";
                howToPlay();
            }

            else if (new_position == "p" || new_position == "pause" || new_position == "stop")
            {
                winner = PAUSE;
                check = "pause";
            }

            else if (new_position == "e" || new_position == "exit" || new_position == "w" || new_position == "wyjscie" || new_position == "wyjdz" || new_position == "abandon")
            {
                yes_no_choice_type = "abandon";
                if (yesNoChoice() == false)
                {
                    winner = EXIT;
                    check = "exit";
                    active_game = false;
                }
                else
                {
                    check = "again";
                    refreshArea();
                }
            }

            else if (new_position == "remis")
            {
                yes_no_choice_type = "draw";
                if (yesNoChoice() == false)
                {
                    winner = DRAW;
                    check = "remis";
                    refreshArea();
                    whoWins();
                }
                else
                {
                    check = "again";
                    refreshArea();
                }
            }

            else if (new_position == "r" || new_position == "resign" || new_position == "poddaj")
            {
                yes_no_choice_type = "resign";
                if (yesNoChoice() == false)
                {
                    winner = RESIGN;
                    check = "resign";
                    refreshArea();
                    whoWins();
                }
                else
                {
                    check = "again";
                    refreshArea();
                }
            }

            else if (new_position == "showb")
            {
                showBools();
                system("pause");
                refreshArea();
                check = "again";
            }

            else if (new_position == "showv")
            {
                system("cls");
                refreshVirtualArea();
                cout << endl;
                system("pause");
                refreshArea();
                check = "again";
            }
            else if (new_position == "showa")
            {
                cout << "\nKomenda \"showa\" jest aktywna tylko podczas wybierania figury.\n\n";
                textColorStandard();
                system("pause");
                refreshArea();
                check = "again";
            }

            else if (new_position == "show")
            {
                show();
                system("pause");
                refreshArea();
                check = "again";
            }

            else if (new_position == "dev")
            {
                system("cls");
                devCommands();
                system("pause");
                refreshArea();
                check = "again";
            }

            else
            {
                for (int i = 0; i < 65; i++)
                {
                    if (new_position == area[i].position)
                    {
                        if (whith_player % 2 == 0 && area[i].figure_color == WHITE || whith_player % 2 == 1 && area[i].figure_color == BLACK)
                        {
                            check = "friendly_figure";
                            textColorRed();
                            cout << "\nNie mozesz zbic wlasnej figury!";
                            textColorStandard();
                            Sleep(1500);
                            refreshArea();
                            break;
                        }
                        else
                        {
                            /////////////////////////////////////// correct selected new position ///////////////////////////////////////
                            new_position_object_nr = i;

                            if (area[i].bg_color == GREEN || area[i].bg_color == RED)
                            {
                                check = "pass";
                                resetAreaColors();
                                refreshArea();
                                break;
                            }
                            else
                            {
                                check = "bad_position";
                                cout << "Nie mozesz sie tutaj poruszyc . . .";
                                Sleep(1500);
                                refreshArea();
                                break;
                            }
                        }
                    }
                    if (i == 64)
                    {
                        check = "bad_position";
                        cout << "Podales niepoprawna pozycje . . .";
                        Sleep(1500);
                        refreshArea();
                    }
                }
            }
        }
    } while (check == "bad_position" || check == "friendly_figure" || check == "again");
    textColorStandard();
}

void moveFigures()
{
    string temp_big_figure{""};
    char temp_figure{' '};
    char temp_figure_color{EMPTY};

    // PROMOTION WHITE PAWNS
    if (area[old_position_object_nr].figure == PAWN && area[old_position_object_nr].figure_color == WHITE && area[new_position_object_nr].row == 1)
    {
        resetVirtualAreaEnPassant();

        area[old_position_object_nr].big_figure = "";
        area[old_position_object_nr].figure = ' ';
        area[old_position_object_nr].figure_color = EMPTY;
        area[new_position_object_nr].figure = '?';
        area[new_position_object_nr].figure_color = WHITE;
        area[new_position_object_nr].bg_color = YELLOW;

        bool white_promoted_choise = true;

        do
        {
            refreshArea();
            string promotion_figure{""};
            textColorYellow();
            cout << "\n\n Na jaka figure promowac Pionka?: ";
            textColorRed();
            cin >> promotion_figure;
            transform(promotion_figure.begin(), promotion_figure.end(), promotion_figure.begin(), ::toupper);
            textColorStandard();

            if (promotion_figure == "H" || promotion_figure == "HETMAN" || promotion_figure == "Q" || promotion_figure == "QUEEN" || promotion_figure == "D" || promotion_figure == "DAMA" || promotion_figure == "DAMKA")
            {
                area[new_position_object_nr].big_figure = "whitePromotedQueen";
                area[new_position_object_nr].figure = QUEEN;
                area[new_position_object_nr].figure_color = WHITE;
                white_promoted_choise = true;
            }

            else if (promotion_figure == "W" || promotion_figure == "WIEZA" || promotion_figure == "R" || promotion_figure == "ROOK")
            {
                area[new_position_object_nr].big_figure = "whitePromotedRook";
                area[new_position_object_nr].figure = WHITE;
                area[new_position_object_nr].figure_color = WHITE;
                white_promoted_choise = true;
            }

            else if (promotion_figure == "G" || promotion_figure == "GONIEC" || promotion_figure == "B" || promotion_figure == "BISHOP" || promotion_figure == "L" || promotion_figure == "LAUFER")
            {
                area[new_position_object_nr].big_figure = "whitePromotedBishop";
                area[new_position_object_nr].figure = BISHOP;
                area[new_position_object_nr].figure_color = WHITE;
                white_promoted_choise = true;
            }

            else if (promotion_figure == "S" || promotion_figure == "SKOCZEK" || promotion_figure == "K" || promotion_figure == "KNIGHT" || promotion_figure == "K" || promotion_figure == "KON" || promotion_figure == "KONIK")
            {
                area[new_position_object_nr].big_figure = "whitePromotedKnight";
                area[new_position_object_nr].figure = KNIGHT;
                area[new_position_object_nr].figure_color = WHITE;
                white_promoted_choise = true;
            }
            else
            {
                textColorRed();
                cout << "\n\n Podales bledna nazwe figury";
                Sleep(1500);
                textColorStandard();
                white_promoted_choise = false;
            }
        } while (white_promoted_choise == false);
        resetAreaColors();
    }

    // PROMOTION BLACK PAWNS
    else if (area[old_position_object_nr].figure == PAWN && area[old_position_object_nr].figure_color == BLACK && area[new_position_object_nr].row == 8)
    {
        resetVirtualAreaEnPassant();

        area[old_position_object_nr].big_figure = "";
        area[old_position_object_nr].figure = ' ';
        area[old_position_object_nr].figure_color = EMPTY;
        area[new_position_object_nr].figure = '?';
        area[new_position_object_nr].figure_color = BLACK;
        area[new_position_object_nr].bg_color = YELLOW;

        bool black_promoted_choise = true;

        do
        {
            refreshArea();
            string promotion_figure{""};
            textColorYellow();
            cout << "\n\n Na jaka figure promowac Pionka?: ";
            textColorRed();
            cin >> promotion_figure;
            textColorStandard();

            if (promotion_figure == "H" || promotion_figure == "HETMAN" || promotion_figure == "Q" || promotion_figure == "QUEEN" || promotion_figure == "D" || promotion_figure == "DAMA" || promotion_figure == "DAMKA")
            {
                area[new_position_object_nr].big_figure = "blackPromotedQueen";
                area[new_position_object_nr].figure = QUEEN;
                area[new_position_object_nr].figure_color = BLACK;
                black_promoted_choise = true;
            }

            else if (promotion_figure == "W" || promotion_figure == "WIEZA" || promotion_figure == "R" || promotion_figure == "ROOK")
            {
                area[new_position_object_nr].big_figure = "blackPromotedRook";
                area[new_position_object_nr].figure = WHITE;
                area[new_position_object_nr].figure_color = BLACK;
                black_promoted_choise = true;
            }

            else if (promotion_figure == "G" || promotion_figure == "GONIEC" || promotion_figure == "B" || promotion_figure == "BISHOP" || promotion_figure == "L" || promotion_figure == "LAUFER")
            {
                area[new_position_object_nr].big_figure = "blackPromotedBishop";
                area[new_position_object_nr].figure = BISHOP;
                area[new_position_object_nr].figure_color = BLACK;
                black_promoted_choise = true;
            }

            else if (promotion_figure == "S" || promotion_figure == "SKOCZEK" || promotion_figure == "K" || promotion_figure == "KNIGHT" || promotion_figure == "K" || promotion_figure == "KON" || promotion_figure == "KONIK")
            {
                area[new_position_object_nr].big_figure = "blackPromotedKnight";
                area[new_position_object_nr].figure = KNIGHT;
                area[new_position_object_nr].figure_color = BLACK;
                black_promoted_choise = true;
            }
            else
            {
                textColorRed();
                cout << "\n\n Podales bledna nazwe figury";
                Sleep(1500);
                textColorStandard();
                black_promoted_choise = false;
            }
        } while (black_promoted_choise == false);
        resetAreaColors();
    }

    // WHITE - QUEEN SIDE CASTLING
    else if (area[old_position_object_nr].big_figure == "whiteKing" && area[new_position_object_nr].position == "c1" && active_white_left_castling == true)
    {
        resetVirtualAreaEnPassant();

        area[58].big_figure = "whiteKing";
        area[58].figure = KING;
        area[58].figure_color = WHITE;
        area[60].big_figure = "";
        area[60].figure = ' ';
        area[60].figure_color = EMPTY;

        area[59].big_figure = "whiteLeftRook";
        area[59].figure = WHITE;
        area[59].figure_color = WHITE;
        area[56].big_figure = "";
        area[56].figure = ' ';
        area[56].figure_color = EMPTY;

        active_white_left_castling = false;
        active_white_right_castling = false;
    }

    // WHITE - KING SIDE CASTLING
    else if (area[old_position_object_nr].big_figure == "whiteKing" && area[new_position_object_nr].position == "g1" && active_white_right_castling == true)
    {
        resetVirtualAreaEnPassant();

        area[62].big_figure = "whiteKing";
        area[62].figure = KING;
        area[62].figure_color = WHITE;
        area[60].big_figure = "";
        area[60].figure = ' ';
        area[60].figure_color = EMPTY;

        area[61].big_figure = "whiteRightRook";
        area[61].figure = WHITE;
        area[61].figure_color = WHITE;
        area[63].big_figure = "";
        area[63].figure = ' ';
        area[63].figure_color = EMPTY;

        active_white_left_castling = false;
        active_white_right_castling = false;
    }

    // BLACK - QUEEN SIDE CASTLING
    else if (area[old_position_object_nr].big_figure == "blackKing" && area[new_position_object_nr].position == "c8" && active_black_left_castling == true)
    {
        resetVirtualAreaEnPassant();

        area[2].big_figure = "blackKing";
        area[2].figure = KING;
        area[2].figure_color = BLACK;
        area[4].big_figure = "";
        area[4].figure = ' ';
        area[4].figure_color = EMPTY;

        area[3].big_figure = "blackLeftRook";
        area[3].figure = WHITE;
        area[3].figure_color = BLACK;
        area[9].big_figure = "";
        area[9].figure = ' ';
        area[9].figure_color = EMPTY;

        active_black_left_castling = false;
        active_black_right_castling = false;
    }

    // BLACK - KING SIDE CASTLING
    else if (area[old_position_object_nr].big_figure == "blackKing" && area[new_position_object_nr].position == "g8" && active_black_right_castling == true)
    {
        resetVirtualAreaEnPassant();

        area[6].big_figure = "blackKing";
        area[6].figure = KING;
        area[6].figure_color = BLACK;
        area[4].big_figure = "";
        area[4].figure = ' ';
        area[4].figure_color = EMPTY;

        area[5].big_figure = "blackRightRook";
        area[5].figure = WHITE;
        area[5].figure_color = BLACK;
        area[7].big_figure = "";
        area[7].figure = ' ';
        area[7].figure_color = EMPTY;

        active_black_left_castling = false;
        active_black_right_castling = false;
    }

    // WHITE - EN PASSANT
    else if (area[old_position_object_nr].figure_color == WHITE && area[old_position_object_nr].figure == PAWN && virtual_area[new_position_object_nr + BOTTOM].en_passant == true)
    {
        temp_big_figure = area[old_position_object_nr].big_figure;
        temp_figure = area[old_position_object_nr].figure;
        temp_figure_color = area[old_position_object_nr].figure_color;
        area[old_position_object_nr].big_figure = "";
        area[old_position_object_nr].figure = ' ';
        area[old_position_object_nr].figure_color = EMPTY;

        area[new_position_object_nr].big_figure = temp_big_figure;
        area[new_position_object_nr].figure = temp_figure;
        area[new_position_object_nr].figure_color = temp_figure_color;

        area[new_position_object_nr + BOTTOM].big_figure = "";
        area[new_position_object_nr + BOTTOM].figure = ' ';
        area[new_position_object_nr + BOTTOM].figure_color = EMPTY;
        resetVirtualAreaEnPassant();
    }

    // BLACK - EN PASSANT
    else if (area[old_position_object_nr].figure_color == BLACK && area[old_position_object_nr].figure == PAWN && virtual_area[new_position_object_nr + TOP].en_passant == true)
    {
        temp_big_figure = area[old_position_object_nr].big_figure;
        temp_figure = area[old_position_object_nr].figure;
        temp_figure_color = area[old_position_object_nr].figure_color;
        area[old_position_object_nr].big_figure = "";
        area[old_position_object_nr].figure = ' ';
        area[old_position_object_nr].figure_color = EMPTY;

        area[new_position_object_nr].big_figure = temp_big_figure;
        area[new_position_object_nr].figure = temp_figure;
        area[new_position_object_nr].figure_color = temp_figure_color;

        area[new_position_object_nr + TOP].big_figure = "";
        area[new_position_object_nr + TOP].figure = ' ';
        area[new_position_object_nr + TOP].figure_color = EMPTY;
        resetVirtualAreaEnPassant();
    }

    else
    {
        resetVirtualAreaEnPassant();

        if (area[old_position_object_nr].big_figure == "whiteLeftRook" || area[new_position_object_nr].big_figure == "whiteLeftRook")
            white_left_rook_move = true;
        if (area[old_position_object_nr].big_figure == "whiteRightRook" || area[new_position_object_nr].big_figure == "whiteRightRook")
            white_right_rook_move = true;
        if (area[old_position_object_nr].big_figure == "blackLeftRook" || area[new_position_object_nr].big_figure == "blackLeftRook")
            black_left_rook_move = true;
        if (area[old_position_object_nr].big_figure == "blackRightRook" || area[new_position_object_nr].big_figure == "blackRightRook")
            black_right_rook_move = true;
        if (area[old_position_object_nr].big_figure == "whiteKing")
            white_king_move = true;
        if (area[old_position_object_nr].big_figure == "blackKing")
            black_king_move = true;

        if (area[old_position_object_nr].figure == PAWN && area[old_position_object_nr].row == 2 && area[new_position_object_nr].row == 4)
            virtual_area[new_position_object_nr].en_passant = true;
        if (area[old_position_object_nr].figure == PAWN && area[old_position_object_nr].row == 7 && area[new_position_object_nr].row == 5)
            virtual_area[new_position_object_nr].en_passant = true;

        temp_big_figure = area[old_position_object_nr].big_figure;
        temp_figure = area[old_position_object_nr].figure;
        temp_figure_color = area[old_position_object_nr].figure_color;
        area[old_position_object_nr].big_figure = "";
        area[old_position_object_nr].figure = ' ';
        area[old_position_object_nr].figure_color = EMPTY;

        area[new_position_object_nr].big_figure = temp_big_figure;
        area[new_position_object_nr].figure = temp_figure;
        area[new_position_object_nr].figure_color = temp_figure_color;
    }

    if (white_king_move == true)
    {
        active_white_left_castling = false;
        active_white_right_castling = false;
    }
    if (white_left_rook_move == true)
    {
        active_white_left_castling = false;
    }
    if (white_right_rook_move == true)
    {
        active_white_right_castling = false;
    }

    if (black_king_move == true)
    {
        active_black_left_castling = false;
        active_black_right_castling = false;
    }
    if (black_left_rook_move == true)
    {
        active_black_left_castling = false;
    }
    if (black_right_rook_move == true)
    {
        active_black_right_castling = false;
    }

    whith_player++;
    refreshArea();
}

void moveFigures_VirtualArea()
{
    for (int i = 0; i < 64; i++)
    {
        virtual_area[i].figure_color = area[i].figure_color;
        virtual_area[i].figure = area[i].figure;
        virtual_area[i].big_figure = area[i].big_figure;
    }
}

void whoWins()
{
    if (winner == RESIGN)
    {
        if (whith_player % 2 == 0)
            winner = PLAYER_2;
        else
            winner = PLAYER_1;
    }

    if (winner == PLAYER_1 || winner == PLAYER_2 || winner == DRAW)
    {
        time(&cur_time);
        date = localtime(&cur_time);
        strftime(hour, 80, "%x %H:%M:%S.", date);
        saveScore();
    }
    if (winner == PLAYER_1)
    {
        textColorYellow();
        cout << "\n\nWygral: ";
        bgColorBlueTextColorWhite();
        cout << player_1;
    }
    else if (winner == PLAYER_2)
    {
        textColorYellow();
        cout << "\n\nWygral: ";
        bgColorBlueTextColorWhite();
        cout << player_2;
    }
    else if (winner == DRAW)
    {
        textColorYellow();
        cout << "\n\nREMIS!";
    }

    if (winner == PLAYER_1 || winner == PLAYER_2 || winner == DRAW)
    {
        active_game = false;
        textColorStandard();
        cout << "\nWcisnij ENTER by wrocic do menu glownego . . .";
        getchar();
        getchar();
    }
}

void showAreaStats()
{
    for (int i = 0; i < 64; i++)
    {
        textColorStandard();
        area[i].show();
    }
}

void showBools()
{
    system("cls");
    textColorStandard();
    cout << "\nWhite King Check: " << white_king_check;
    cout << "\nBlack King Check: " << black_king_check;

    cout << "\n\nWhite King Move: " << white_king_move;
    cout << "\nBlack King Move: " << black_king_move;

    cout << "\n\nWhite Left Rook Move: " << white_left_rook_move;
    cout << "\nWhite Right Rook Move: " << white_right_rook_move;

    cout << "\nBlack Left Rook Move: " << black_left_rook_move;
    cout << "\nBlack Right Rook Move: " << black_right_rook_move;

    cout << "\n\nActive White Left Castling: " << active_white_left_castling;
    cout << "\nActive White Right Castling: " << active_white_right_castling;

    cout << "\nActive Black Left Castling: " << active_black_left_castling;
    cout << "\nActive Black Right Castling: " << active_black_right_castling << endl
         << endl;
}

void show()
{
    system("cls");
    textColorStandard();
    cout << "--- Area ---\n\n";
    textColorBlue();
    for (int i = 0; i < 64; i++)
    {
        area[i].show();
    }

    textColorStandard();
    cout << "\n\n\n--- Virtual Area ---\n\n";
    textColorGreen();
    for (int i = 0; i < 64; i++)
    {
        virtual_area[i].show();
    }
    textColorStandard();
}

void paintAreaColors()
{
    if (area[old_position_object_nr].figure == PAWN)
        paintAreaColorsPawn();
    if (area[old_position_object_nr].figure == KNIGHT)
        paintAreaColorsKnight();
    if (area[old_position_object_nr].figure == BISHOP)
        paintAreaColorsBishop();
    if (area[old_position_object_nr].figure == ROOK)
        paintAreaColorsRook();
    if (area[old_position_object_nr].figure == QUEEN)
        paintAreaColorsQueen();
    if (area[old_position_object_nr].figure == KING)
        paintAreaColorsKing();
}

void paintAreaColorsPawn()
{
    ///////////////// WHITE /////////////////
    if (area[old_position_object_nr].figure_color == WHITE)
    {
        if (area[old_position_object_nr].row == 7)
        {
            pawnTopSide();
            pawnTopTopSide();
            pawnTopLeftSide();
            pawnTopRigtSide();
            pawnTopLeft_enPassant();
            pawnTopRight_enPassant();
        }
        else
        {
            pawnTopSide();
            pawnTopLeftSide();
            pawnTopRigtSide();
            pawnTopLeft_enPassant();
            pawnTopRight_enPassant();
        }
    }

    ///////////////// BLACK /////////////////
    else
    {
        if (area[old_position_object_nr].row == 2)
        {
            pawnBottomSide();
            pawnBottomBottomSide();
            pawnBottomLeftSide();
            pawnBottomRigtSide();
            pawnBottomLeft_enPassant();
            pawnBottomRight_enPassant();
        }
        else
        {
            pawnBottomSide();
            pawnBottomLeftSide();
            pawnBottomRigtSide();
            pawnBottomLeft_enPassant();
            pawnBottomRight_enPassant();
        }
    }
}
void paintAreaColorsKnight()
{

    ///////////////// WHITE /////////////////
    if (area[old_position_object_nr].figure_color == WHITE)
    {

        // TOP TOP LEFT
        if (old_position_object_nr >= 17)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + TOP_TOP_LEFT].figure_color == BLACK && area[old_position_object_nr + TOP_TOP_LEFT].bg_color == GREEN || virtual_area[old_position_object_nr + TOP_TOP_LEFT].checking == true)
                        area[old_position_object_nr + TOP_TOP_LEFT].bg_color = RED;
                    else if (area[old_position_object_nr + TOP_TOP_LEFT].figure_color == EMPTY && area[old_position_object_nr + TOP_TOP_LEFT].bg_color == GREEN)
                        area[old_position_object_nr + TOP_TOP_LEFT].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + TOP_TOP_LEFT].figure_color == BLACK)
                        area[old_position_object_nr + TOP_TOP_LEFT].bg_color = RED;
                    else if (area[old_position_object_nr + TOP_TOP_LEFT].figure_color == EMPTY)
                        area[old_position_object_nr + TOP_TOP_LEFT].bg_color = GREEN;
                }
            }
        }

        // TOP TOP RIGHT
        if (old_position_object_nr >= 16)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + TOP_TOP_RIGHT].figure_color == BLACK && area[old_position_object_nr + TOP_TOP_RIGHT].bg_color == GREEN || virtual_area[old_position_object_nr + TOP_TOP_RIGHT].checking == true)
                        area[old_position_object_nr + TOP_TOP_RIGHT].bg_color = RED;
                    else if (area[old_position_object_nr + TOP_TOP_RIGHT].figure_color == EMPTY && area[old_position_object_nr + TOP_TOP_RIGHT].bg_color == GREEN)
                        area[old_position_object_nr + TOP_TOP_RIGHT].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 7)
                {
                    if (area[old_position_object_nr + TOP_TOP_RIGHT].figure_color == BLACK)
                        area[old_position_object_nr + TOP_TOP_RIGHT].bg_color = RED;
                    else if (area[old_position_object_nr + TOP_TOP_RIGHT].figure_color == EMPTY)
                        area[old_position_object_nr + TOP_TOP_RIGHT].bg_color = GREEN;
                }
            }
        }

        // BOTTOM BOTTOM LEFT
        if (old_position_object_nr <= 47)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].figure_color == BLACK && area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color == GREEN || virtual_area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].checking == true)
                        area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = RED;
                    else if (area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].figure_color == EMPTY && area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color == GREEN)
                        area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].figure_color == BLACK)
                        area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = RED;
                    else if (area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].figure_color == EMPTY)
                        area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = GREEN;
                }
            }
        }

        // BOTTOM BOTTOM RIGHT
        if (old_position_object_nr <= 46)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].figure_color == BLACK && area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color == GREEN || virtual_area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].checking == true)
                        area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = RED;
                    else if (area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].figure_color == EMPTY && area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color == GREEN)
                        area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 7)
                {
                    if (area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].figure_color == BLACK)
                        area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = RED;
                    else if (area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].figure_color == EMPTY)
                        area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = GREEN;
                }
            }
        }

        // LEFT LEFT TOP
        if (old_position_object_nr >= 10)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + LEFT_LEFT_TOP].figure_color == BLACK && area[old_position_object_nr + LEFT_LEFT_TOP].bg_color == GREEN || virtual_area[old_position_object_nr + LEFT_LEFT_TOP].checking == true)
                        area[old_position_object_nr + LEFT_LEFT_TOP].bg_color = RED;
                    else if (area[old_position_object_nr + LEFT_LEFT_TOP].figure_color == EMPTY && area[old_position_object_nr + LEFT_LEFT_TOP].bg_color == GREEN)
                        area[old_position_object_nr + LEFT_LEFT_TOP].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 3)
                {
                    if (area[old_position_object_nr + LEFT_LEFT_TOP].figure_color == BLACK)
                        area[old_position_object_nr + LEFT_LEFT_TOP].bg_color = RED;
                    else if (area[old_position_object_nr + LEFT_LEFT_TOP].figure_color == EMPTY)
                        area[old_position_object_nr + LEFT_LEFT_TOP].bg_color = GREEN;
                }
            }
        }

        // LEFT LEFT BOTTOM
        if (old_position_object_nr <= 55)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + LEFT_LEFT_BOTTOM].figure_color == BLACK && area[old_position_object_nr + LEFT_LEFT_BOTTOM].bg_color == GREEN || virtual_area[old_position_object_nr + LEFT_LEFT_BOTTOM].checking == true)
                        area[old_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = RED;
                    else if (area[old_position_object_nr + LEFT_LEFT_BOTTOM].figure_color == EMPTY && area[old_position_object_nr + LEFT_LEFT_BOTTOM].bg_color == GREEN)
                        area[old_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 3)
                {
                    if (area[old_position_object_nr + LEFT_LEFT_BOTTOM].figure_color == BLACK)
                        area[old_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = RED;
                    else if (area[old_position_object_nr + LEFT_LEFT_BOTTOM].figure_color == EMPTY)
                        area[old_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = GREEN;
                }
            }
        }

        // RIGH RIGHT TOP
        if (old_position_object_nr >= 8)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + RIGHT_RIGHT_TOP].figure_color == BLACK && area[old_position_object_nr + RIGHT_RIGHT_TOP].bg_color == GREEN || virtual_area[old_position_object_nr + RIGHT_RIGHT_TOP].checking == true)
                        area[old_position_object_nr + RIGHT_RIGHT_TOP].bg_color = RED;
                    else if (area[old_position_object_nr + RIGHT_RIGHT_TOP].figure_color == EMPTY && area[old_position_object_nr + RIGHT_RIGHT_TOP].bg_color == GREEN)
                        area[old_position_object_nr + RIGHT_RIGHT_TOP].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 6)
                {
                    if (area[old_position_object_nr + RIGHT_RIGHT_TOP].figure_color == BLACK)
                        area[old_position_object_nr + RIGHT_RIGHT_TOP].bg_color = RED;
                    else if (area[old_position_object_nr + RIGHT_RIGHT_TOP].figure_color == EMPTY)
                        area[old_position_object_nr + RIGHT_RIGHT_TOP].bg_color = GREEN;
                }
            }
        }

        // RIGH RIGHT BOTTOM
        if (old_position_object_nr <= 53)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].figure_color == BLACK && area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color == GREEN || virtual_area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].checking == true)
                        area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = RED;
                    else if (area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].figure_color == EMPTY && area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color == GREEN)
                        area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 6)
                {
                    if (area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].figure_color == BLACK)
                        area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = RED;
                    else if (area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].figure_color == EMPTY)
                        area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = GREEN;
                }
            }
        }
    }

    ///////////////// BLACK /////////////////
    if (area[old_position_object_nr].figure_color == BLACK)
    {
        // TOP TOP LEFT
        if (old_position_object_nr >= 17)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + TOP_TOP_LEFT].figure_color == WHITE && area[old_position_object_nr + TOP_TOP_LEFT].bg_color == GREEN || virtual_area[old_position_object_nr + TOP_TOP_LEFT].checking == true)
                        area[old_position_object_nr + TOP_TOP_LEFT].bg_color = RED;
                    else if (area[old_position_object_nr + TOP_TOP_LEFT].figure_color == EMPTY && area[old_position_object_nr + TOP_TOP_LEFT].bg_color == GREEN)
                        area[old_position_object_nr + TOP_TOP_LEFT].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + TOP_TOP_LEFT].figure_color == WHITE)
                        area[old_position_object_nr + TOP_TOP_LEFT].bg_color = RED;
                    else if (area[old_position_object_nr + TOP_TOP_LEFT].figure_color == EMPTY)
                        area[old_position_object_nr + TOP_TOP_LEFT].bg_color = GREEN;
                }
            }
        }

        // TOP TOP RIGHT
        if (old_position_object_nr >= 16)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + TOP_TOP_RIGHT].figure_color == WHITE && area[old_position_object_nr + TOP_TOP_RIGHT].bg_color == GREEN || virtual_area[old_position_object_nr + TOP_TOP_RIGHT].checking == true)
                        area[old_position_object_nr + TOP_TOP_RIGHT].bg_color = RED;
                    else if (area[old_position_object_nr + TOP_TOP_RIGHT].figure_color == EMPTY && area[old_position_object_nr + TOP_TOP_RIGHT].bg_color == GREEN)
                        area[old_position_object_nr + TOP_TOP_RIGHT].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 7)
                {
                    if (area[old_position_object_nr + TOP_TOP_RIGHT].figure_color == WHITE)
                        area[old_position_object_nr + TOP_TOP_RIGHT].bg_color = RED;
                    else if (area[old_position_object_nr + TOP_TOP_RIGHT].figure_color == EMPTY)
                        area[old_position_object_nr + TOP_TOP_RIGHT].bg_color = GREEN;
                }
            }
        }

        // BOTTOM BOTTOM LEFT
        if (old_position_object_nr <= 47)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].figure_color == WHITE && area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color == GREEN || virtual_area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].checking == true)
                        area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = RED;
                    else if (area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].figure_color == EMPTY && area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color == GREEN)
                        area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].figure_color == WHITE)
                        area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = RED;
                    else if (area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].figure_color == EMPTY)
                        area[old_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = GREEN;
                }
            }
        }

        // BOTTOM BOTTOM RIGHT
        if (old_position_object_nr <= 46)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].figure_color == WHITE && area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color == GREEN || virtual_area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].checking == true)
                        area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = RED;
                    else if (area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].figure_color == EMPTY && area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color == GREEN)
                        area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 7)
                {
                    if (area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].figure_color == WHITE)
                        area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = RED;
                    else if (area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].figure_color == EMPTY)
                        area[old_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = GREEN;
                }
            }
        }

        // LEFT LEFT TOP
        if (old_position_object_nr >= 10)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + LEFT_LEFT_TOP].figure_color == WHITE && area[old_position_object_nr + LEFT_LEFT_TOP].bg_color == GREEN || virtual_area[old_position_object_nr + LEFT_LEFT_TOP].checking == true)
                        area[old_position_object_nr + LEFT_LEFT_TOP].bg_color = RED;
                    else if (area[old_position_object_nr + LEFT_LEFT_TOP].figure_color == EMPTY && area[old_position_object_nr + LEFT_LEFT_TOP].bg_color == GREEN)
                        area[old_position_object_nr + LEFT_LEFT_TOP].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 3)
                {
                    if (area[old_position_object_nr + LEFT_LEFT_TOP].figure_color == WHITE)
                        area[old_position_object_nr + LEFT_LEFT_TOP].bg_color = RED;
                    else if (area[old_position_object_nr + LEFT_LEFT_TOP].figure_color == EMPTY)
                        area[old_position_object_nr + LEFT_LEFT_TOP].bg_color = GREEN;
                }
            }
        }

        // LEFT LEFT BOTTOM
        if (old_position_object_nr <= 55)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + LEFT_LEFT_BOTTOM].figure_color == WHITE && area[old_position_object_nr + LEFT_LEFT_BOTTOM].bg_color == GREEN || virtual_area[old_position_object_nr + LEFT_LEFT_BOTTOM].checking == true)
                        area[old_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = RED;
                    else if (area[old_position_object_nr + LEFT_LEFT_BOTTOM].figure_color == EMPTY && area[old_position_object_nr + LEFT_LEFT_BOTTOM].bg_color == GREEN)
                        area[old_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 3)
                {
                    if (area[old_position_object_nr + LEFT_LEFT_BOTTOM].figure_color == WHITE)
                        area[old_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = RED;
                    else if (area[old_position_object_nr + LEFT_LEFT_BOTTOM].figure_color == EMPTY)
                        area[old_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = GREEN;
                }
            }
        }

        // RIGH RIGHT TOP
        if (old_position_object_nr >= 8)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + RIGHT_RIGHT_TOP].figure_color == WHITE && area[old_position_object_nr + RIGHT_RIGHT_TOP].bg_color == GREEN || virtual_area[old_position_object_nr + RIGHT_RIGHT_TOP].checking == true)
                        area[old_position_object_nr + RIGHT_RIGHT_TOP].bg_color = RED;
                    else if (area[old_position_object_nr + RIGHT_RIGHT_TOP].figure_color == EMPTY && area[old_position_object_nr + RIGHT_RIGHT_TOP].bg_color == GREEN)
                        area[old_position_object_nr + RIGHT_RIGHT_TOP].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 6)
                {
                    if (area[old_position_object_nr + RIGHT_RIGHT_TOP].figure_color == WHITE)
                        area[old_position_object_nr + RIGHT_RIGHT_TOP].bg_color = RED;
                    else if (area[old_position_object_nr + RIGHT_RIGHT_TOP].figure_color == EMPTY)
                        area[old_position_object_nr + RIGHT_RIGHT_TOP].bg_color = GREEN;
                }
            }
        }

        // RIGH RIGHT BOTTOM
        if (old_position_object_nr <= 53)
        {
            if (virtual_area[old_position_object_nr].bg_color == PURPLE)
                ;
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].figure_color == WHITE && area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color == GREEN || virtual_area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].checking == true)
                        area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = RED;
                    else if (area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].figure_color == EMPTY && area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color == GREEN)
                        area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = GREEN;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 6)
                {
                    if (area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].figure_color == WHITE)
                        area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = RED;
                    else if (area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].figure_color == EMPTY)
                        area[old_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = GREEN;
                }
            }
        }
    }
}
void paintAreaColorsBishop()
{
    topLeftSide();
    topRighttSide();
    bottomLeftSide();
    bottomRightSide();
}
void paintAreaColorsRook()
{
    topSide();
    bottomSide();
    leftSide();
    rightSide();
}
void paintAreaColorsQueen()
{
    topSide();
    bottomSide();
    leftSide();
    rightSide();
    topLeftSide();
    topRighttSide();
    bottomLeftSide();
    bottomRightSide();
}
void paintAreaColorsKing()
{
    ///////////////// WHITE /////////////////
    if (area[old_position_object_nr].figure_color == WHITE)
    {
        // TOP SIDE
        if (area[old_position_object_nr].row > 1)
        {
            if (area[old_position_object_nr + TOP].figure_color == BLACK && virtual_area[old_position_object_nr + TOP].bg_color != YELLOW)
                area[old_position_object_nr + TOP].bg_color = RED;
            else if (area[old_position_object_nr + TOP].figure_color == EMPTY && virtual_area[old_position_object_nr + TOP].bg_color != GREEN && virtual_area[old_position_object_nr + TOP].bg_color != RED && virtual_area[old_position_object_nr + TOP].bg_color != YELLOW_2)
                area[old_position_object_nr + TOP].bg_color = GREEN;
        }

        // BOTTOM SIDE
        if (area[old_position_object_nr].row < 8)
        {
            if (area[old_position_object_nr + BOTTOM].figure_color == BLACK && virtual_area[old_position_object_nr + BOTTOM].bg_color != YELLOW)
                area[old_position_object_nr + BOTTOM].bg_color = RED;
            else if (area[old_position_object_nr + BOTTOM].figure_color == EMPTY && virtual_area[old_position_object_nr + BOTTOM].bg_color != GREEN && virtual_area[old_position_object_nr + BOTTOM].bg_color != RED && virtual_area[old_position_object_nr + BOTTOM].bg_color != YELLOW_2)
                area[old_position_object_nr + BOTTOM].bg_color = GREEN;
        }

        // LEFT SIDE
        if (area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr + LEFT].figure_color == BLACK && virtual_area[old_position_object_nr + LEFT].bg_color != YELLOW)
                area[old_position_object_nr + LEFT].bg_color = RED;
            else if (area[old_position_object_nr + LEFT].figure_color == EMPTY && virtual_area[old_position_object_nr + LEFT].bg_color != GREEN && virtual_area[old_position_object_nr + LEFT].bg_color != RED && virtual_area[old_position_object_nr + LEFT].bg_color != YELLOW_2)
                area[old_position_object_nr + LEFT].bg_color = GREEN;
        }

        // RIGHT SIDE
        if (area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + RIGHT].figure_color == BLACK && virtual_area[old_position_object_nr + RIGHT].bg_color != YELLOW)
                area[old_position_object_nr + RIGHT].bg_color = RED;
            else if (area[old_position_object_nr + RIGHT].figure_color == EMPTY && virtual_area[old_position_object_nr + RIGHT].bg_color != GREEN && virtual_area[old_position_object_nr + RIGHT].bg_color != RED && virtual_area[old_position_object_nr + RIGHT].bg_color != YELLOW_2)
                area[old_position_object_nr + RIGHT].bg_color = GREEN;
        }

        // TOP LEFT SIDE
        if (area[old_position_object_nr].row > 1 && area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr + TOP_LEFT].figure_color == BLACK && virtual_area[old_position_object_nr + TOP_LEFT].bg_color != YELLOW)
                area[old_position_object_nr + TOP_LEFT].bg_color = RED;
            else if (area[old_position_object_nr + TOP_LEFT].figure_color == EMPTY && virtual_area[old_position_object_nr + TOP_LEFT].bg_color != GREEN && virtual_area[old_position_object_nr + TOP_LEFT].bg_color != RED && virtual_area[old_position_object_nr + TOP_LEFT].bg_color != YELLOW_2)
                area[old_position_object_nr + TOP_LEFT].bg_color = GREEN;
        }

        // TOP RIGHT SIDE
        if (area[old_position_object_nr].row > 1 && area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + TOP_RIGHT].figure_color == BLACK && virtual_area[old_position_object_nr + TOP_RIGHT].bg_color != YELLOW)
                area[old_position_object_nr + TOP_RIGHT].bg_color = RED;
            else if (area[old_position_object_nr + TOP_RIGHT].figure_color == EMPTY && virtual_area[old_position_object_nr + TOP_RIGHT].bg_color != GREEN && virtual_area[old_position_object_nr + TOP_RIGHT].bg_color != RED && virtual_area[old_position_object_nr + TOP_RIGHT].bg_color != YELLOW_2)
                area[old_position_object_nr + TOP_RIGHT].bg_color = GREEN;
        }

        // BOTTOM LEFT SIDE
        if (area[old_position_object_nr].row < 8 && area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr + BOTTOM_LEFT].figure_color == BLACK && virtual_area[old_position_object_nr + BOTTOM_LEFT].bg_color != YELLOW)
                area[old_position_object_nr + BOTTOM_LEFT].bg_color = RED;
            else if (area[old_position_object_nr + BOTTOM_LEFT].figure_color == EMPTY && virtual_area[old_position_object_nr + BOTTOM_LEFT].bg_color != GREEN && virtual_area[old_position_object_nr + BOTTOM_LEFT].bg_color != RED && virtual_area[old_position_object_nr + BOTTOM_LEFT].bg_color != YELLOW_2)
                area[old_position_object_nr + BOTTOM_LEFT].bg_color = GREEN;
        }

        // BOTTOM RIGHT SIDE
        if (area[old_position_object_nr].row < 8 && area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + BOTTOM_RIGHT].figure_color == BLACK && virtual_area[old_position_object_nr + BOTTOM_RIGHT].bg_color != YELLOW)
                area[old_position_object_nr + BOTTOM_RIGHT].bg_color = RED;
            else if (area[old_position_object_nr + BOTTOM_RIGHT].figure_color == EMPTY && virtual_area[old_position_object_nr + BOTTOM_RIGHT].bg_color != GREEN && virtual_area[old_position_object_nr + BOTTOM_RIGHT].bg_color != RED && virtual_area[old_position_object_nr + BOTTOM_RIGHT].bg_color != YELLOW_2)
                area[old_position_object_nr + BOTTOM_RIGHT].bg_color = GREEN;
        }

        // QUEEN SIDE CASTLING
        if (active_white_left_castling == true && white_king_check == false && virtual_area[57].figure == ' ' && virtual_area[58].bg_color != RED && virtual_area[59].bg_color != RED)
        {
            if (area[58].figure_color == EMPTY)
                area[58].bg_color = GREEN;
        }

        // KING SIDE CASTLING
        if (active_white_right_castling == true && white_king_check == false && virtual_area[61].bg_color != RED && virtual_area[62].bg_color != RED)
        {
            if (area[62].figure_color == EMPTY)
                area[62].bg_color = GREEN;
        }
    }

    ///////////////// BLACK /////////////////
    if (area[old_position_object_nr].figure_color == BLACK)
    {
        // TOP SIDE
        if (area[old_position_object_nr].row > 1)
        {
            if (area[old_position_object_nr + TOP].figure_color == WHITE && virtual_area[old_position_object_nr + TOP].bg_color != YELLOW)
                area[old_position_object_nr + TOP].bg_color = RED;
            else if (area[old_position_object_nr + TOP].figure_color == EMPTY && virtual_area[old_position_object_nr + TOP].bg_color != GREEN && virtual_area[old_position_object_nr + TOP].bg_color != RED && virtual_area[old_position_object_nr + TOP].bg_color != YELLOW_2)
                area[old_position_object_nr + TOP].bg_color = GREEN;
        }

        // BOTTOM SIDE
        if (area[old_position_object_nr].row < 8)
        {
            if (area[old_position_object_nr + BOTTOM].figure_color == WHITE && virtual_area[old_position_object_nr + BOTTOM].bg_color != YELLOW)
                area[old_position_object_nr + BOTTOM].bg_color = RED;
            else if (area[old_position_object_nr + BOTTOM].figure_color == EMPTY && virtual_area[old_position_object_nr + BOTTOM].bg_color != GREEN && virtual_area[old_position_object_nr + BOTTOM].bg_color != RED && virtual_area[old_position_object_nr + BOTTOM].bg_color != YELLOW_2)
                area[old_position_object_nr + BOTTOM].bg_color = GREEN;
        }

        // LEFT SIDE
        if (area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr + LEFT].figure_color == WHITE && virtual_area[old_position_object_nr + LEFT].bg_color != YELLOW)
                area[old_position_object_nr + LEFT].bg_color = RED;
            else if (area[old_position_object_nr + LEFT].figure_color == EMPTY && virtual_area[old_position_object_nr + LEFT].bg_color != GREEN && virtual_area[old_position_object_nr + LEFT].bg_color != RED && virtual_area[old_position_object_nr + LEFT].bg_color != YELLOW_2)
                area[old_position_object_nr + LEFT].bg_color = GREEN;
        }

        // RIGHT SIDE
        if (area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + RIGHT].figure_color == WHITE && virtual_area[old_position_object_nr + RIGHT].bg_color != YELLOW)
                area[old_position_object_nr + RIGHT].bg_color = RED;
            else if (area[old_position_object_nr + RIGHT].figure_color == EMPTY && virtual_area[old_position_object_nr + RIGHT].bg_color != GREEN && virtual_area[old_position_object_nr + RIGHT].bg_color != RED && virtual_area[old_position_object_nr + RIGHT].bg_color != YELLOW_2)
                area[old_position_object_nr + RIGHT].bg_color = GREEN;
        }

        // TOP LEFT SIDE
        if (area[old_position_object_nr].row > 1 && area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr + TOP_LEFT].figure_color == WHITE && virtual_area[old_position_object_nr + TOP_LEFT].bg_color != YELLOW)
                area[old_position_object_nr + TOP_LEFT].bg_color = RED;
            else if (area[old_position_object_nr + TOP_LEFT].figure_color == EMPTY && virtual_area[old_position_object_nr + TOP_LEFT].bg_color != GREEN && virtual_area[old_position_object_nr + TOP_LEFT].bg_color != RED && virtual_area[old_position_object_nr + TOP_LEFT].bg_color != YELLOW_2)
                area[old_position_object_nr + TOP_LEFT].bg_color = GREEN;
        }

        // TOP RIGHT SIDE
        if (area[old_position_object_nr].row > 1 && area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + TOP_RIGHT].figure_color == WHITE && virtual_area[old_position_object_nr + TOP_RIGHT].bg_color != YELLOW)
                area[old_position_object_nr + TOP_RIGHT].bg_color = RED;
            else if (area[old_position_object_nr + TOP_RIGHT].figure_color == EMPTY && virtual_area[old_position_object_nr + TOP_RIGHT].bg_color != GREEN && virtual_area[old_position_object_nr + TOP_RIGHT].bg_color != RED && virtual_area[old_position_object_nr + TOP_RIGHT].bg_color != YELLOW_2)
                area[old_position_object_nr + TOP_RIGHT].bg_color = GREEN;
        }

        // BOTTOM LEFT SIDE
        if (area[old_position_object_nr].row < 8 && area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr + BOTTOM_LEFT].figure_color == WHITE && virtual_area[old_position_object_nr + BOTTOM_LEFT].bg_color != YELLOW)
                area[old_position_object_nr + BOTTOM_LEFT].bg_color = RED;
            else if (area[old_position_object_nr + BOTTOM_LEFT].figure_color == EMPTY && virtual_area[old_position_object_nr + BOTTOM_LEFT].bg_color != GREEN && virtual_area[old_position_object_nr + BOTTOM_LEFT].bg_color != RED && virtual_area[old_position_object_nr + BOTTOM_LEFT].bg_color != YELLOW_2)
                area[old_position_object_nr + BOTTOM_LEFT].bg_color = GREEN;
        }

        // BOTTOM RIGHT SIDE
        if (area[old_position_object_nr].row < 8 && area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + BOTTOM_RIGHT].figure_color == WHITE && virtual_area[old_position_object_nr + BOTTOM_RIGHT].bg_color != YELLOW)
                area[old_position_object_nr + BOTTOM_RIGHT].bg_color = RED;
            else if (area[old_position_object_nr + BOTTOM_RIGHT].figure_color == EMPTY && virtual_area[old_position_object_nr + BOTTOM_RIGHT].bg_color != GREEN && virtual_area[old_position_object_nr + BOTTOM_RIGHT].bg_color != RED && virtual_area[old_position_object_nr + BOTTOM_RIGHT].bg_color != YELLOW_2)
                area[old_position_object_nr + BOTTOM_RIGHT].bg_color = GREEN;
        }

        // QUEEN SIDE CASTLING
        if (active_black_left_castling == true && white_king_check == false && virtual_area[1].figure == ' ' && virtual_area[2].bg_color != RED && virtual_area[3].bg_color != RED)
        {
            if (area[2].figure_color == EMPTY)
                area[2].bg_color = GREEN;
        }

        // KING SIDE CASTLING
        if (active_black_right_castling == true && white_king_check == false && virtual_area[5].bg_color != RED && virtual_area[6].bg_color != RED)
        {
            if (area[6].figure_color == EMPTY)
                area[6].bg_color = GREEN;
        }
    }
}

void pawnTopSide()
{
    if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
        ;
    else if (white_king_check == true)
    {
        if (virtual_area[old_position_object_nr + TOP].bg_color == GREEN)
            area[old_position_object_nr + TOP].bg_color = GREEN;
    }
    else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
    {
        if (area[old_position_object_nr + TOP].figure_color == EMPTY && virtual_area[old_position_object_nr + TOP].bg_color == PURPLE)
            area[old_position_object_nr + TOP].bg_color = GREEN;
    }
    else
    {
        if (area[old_position_object_nr + TOP].figure_color == EMPTY)
            area[old_position_object_nr + TOP].bg_color = GREEN;
    }
}

void pawnTopTopSide()
{
    if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
        ;
    else if (white_king_check == true)
    {
        if (virtual_area[old_position_object_nr + TOP_TOP].bg_color == GREEN)
            area[old_position_object_nr + TOP_TOP].bg_color = GREEN;
    }
    else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
    {
        if (area[old_position_object_nr + TOP_TOP].figure_color == EMPTY && virtual_area[old_position_object_nr + TOP_TOP].bg_color == PURPLE)
            area[old_position_object_nr + TOP_TOP].bg_color = GREEN;
    }
    else
    {
        if (area[old_position_object_nr + TOP_TOP].figure_color == EMPTY)
            area[old_position_object_nr + TOP_TOP].bg_color = GREEN;
    }
}

void pawnTopLeftSide()
{
    if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
        ;
    else if (white_king_check == true)
    {
        if (virtual_area[old_position_object_nr + TOP_LEFT].checking == true)
            area[old_position_object_nr + TOP_LEFT].bg_color = RED;
    }
    else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
    {
        if (area[old_position_object_nr + TOP_LEFT].figure_color == BLACK && area[old_position_object_nr].column > 1 && virtual_area[old_position_object_nr + TOP_LEFT].bg_color == PURPLE)
            area[old_position_object_nr + TOP_LEFT].bg_color = RED;
    }
    else
    {
        if (area[old_position_object_nr + TOP_LEFT].figure_color == BLACK && area[old_position_object_nr].column > 1)
            area[old_position_object_nr + TOP_LEFT].bg_color = RED;
    }
}

void pawnTopRigtSide()
{
    if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
        ;
    else if (white_king_check == true)
    {
        if (virtual_area[old_position_object_nr + TOP_RIGHT].checking == true)
            area[old_position_object_nr + TOP_RIGHT].bg_color = RED;
    }
    else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
    {
        if (area[old_position_object_nr + TOP_RIGHT].figure_color == BLACK && area[old_position_object_nr].column < 8 && virtual_area[old_position_object_nr + TOP_RIGHT].bg_color == PURPLE)
            area[old_position_object_nr + TOP_RIGHT].bg_color = RED;
    }
    else
    {
        if (area[old_position_object_nr + TOP_RIGHT].figure_color == BLACK && area[old_position_object_nr].column < 8)
            area[old_position_object_nr + TOP_RIGHT].bg_color = RED;
    }
}

void pawnTopLeft_enPassant()
{
    if (virtual_area[old_position_object_nr + LEFT].en_passant == true)
        area[old_position_object_nr + TOP_LEFT].bg_color = RED;
}

void pawnTopRight_enPassant()
{
    if (virtual_area[old_position_object_nr + RIGHT].en_passant == true)
        area[old_position_object_nr + TOP_RIGHT].bg_color = RED;
}

void pawnBottomSide()
{
    if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
        ;
    else if (black_king_check == true)
    {
        if (virtual_area[old_position_object_nr + BOTTOM].bg_color == GREEN)
            area[old_position_object_nr + BOTTOM].bg_color = GREEN;
    }
    else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
    {
        if (area[old_position_object_nr + BOTTOM].figure_color == EMPTY && virtual_area[old_position_object_nr + BOTTOM].bg_color == PURPLE)
            area[old_position_object_nr + BOTTOM].bg_color = GREEN;
    }
    else
    {
        if (area[old_position_object_nr + BOTTOM].figure_color == EMPTY)
            area[old_position_object_nr + BOTTOM].bg_color = GREEN;
    }
}

void pawnBottomBottomSide()
{
    if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
        ;
    else if (black_king_check == true)
    {
        if (virtual_area[old_position_object_nr + TOP_TOP].bg_color == GREEN)
            area[old_position_object_nr + TOP_TOP].bg_color = GREEN;
    }
    else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
    {
        if (area[old_position_object_nr + BOTTOM_BOTTOM].figure_color == EMPTY && virtual_area[old_position_object_nr + BOTTOM_BOTTOM].bg_color == PURPLE)
            area[old_position_object_nr + BOTTOM_BOTTOM].bg_color = GREEN;
    }
    else
    {
        if (area[old_position_object_nr + BOTTOM_BOTTOM].figure_color == EMPTY)
            area[old_position_object_nr + BOTTOM_BOTTOM].bg_color = GREEN;
    }
}

void pawnBottomLeftSide()
{
    if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
        ;
    else if (black_king_check == true)
    {
        if (virtual_area[old_position_object_nr + BOTTOM_LEFT].checking == true)
            area[old_position_object_nr + BOTTOM_LEFT].bg_color = RED;
    }
    else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
    {
        if (area[old_position_object_nr + BOTTOM_LEFT].figure_color == WHITE && area[old_position_object_nr].column > 1 && virtual_area[old_position_object_nr + BOTTOM_LEFT].bg_color == PURPLE)
            area[old_position_object_nr + BOTTOM_LEFT].bg_color = RED;
    }
    else
    {
        if (area[old_position_object_nr + BOTTOM_LEFT].figure_color == WHITE && area[old_position_object_nr].column > 1)
            area[old_position_object_nr + BOTTOM_LEFT].bg_color = RED;
    }
}

void pawnBottomRigtSide()
{
    if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
        ;
    else if (black_king_check == true)
    {
        if (virtual_area[old_position_object_nr + BOTTOM_RIGHT].checking == true)
            area[old_position_object_nr + BOTTOM_RIGHT].bg_color = RED;
    }
    else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
    {
        if (area[old_position_object_nr + BOTTOM_RIGHT].figure_color == WHITE && area[old_position_object_nr].column < 8 && virtual_area[old_position_object_nr + BOTTOM_RIGHT].bg_color == PURPLE)
            area[old_position_object_nr + BOTTOM_RIGHT].bg_color = RED;
    }
    else
    {
        if (area[old_position_object_nr + BOTTOM_RIGHT].figure_color == WHITE && area[old_position_object_nr].column < 8)
            area[old_position_object_nr + BOTTOM_RIGHT].bg_color = RED;
    }
}

void pawnBottomLeft_enPassant()
{
    if (virtual_area[old_position_object_nr + LEFT].en_passant == true)
        area[old_position_object_nr + BOTTOM_LEFT].bg_color = RED;
}

void pawnBottomRight_enPassant()
{
    if (virtual_area[old_position_object_nr + RIGHT].en_passant == true)
        area[old_position_object_nr + BOTTOM_RIGHT].bg_color = RED;
}

void topSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == WHITE)
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1)
                    break;
                if (area[old_position_object_nr + TOP * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP * i].figure_color == BLACK && virtual_area[old_position_object_nr + TOP * i].bg_color == GREEN || virtual_area[old_position_object_nr + TOP * i].checking == true)
                    {
                        area[old_position_object_nr + TOP * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr + TOP * i].bg_color == GREEN)
                    area[old_position_object_nr + TOP * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1)
                    break;
                if (area[old_position_object_nr + TOP * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP * i].figure_color == BLACK && virtual_area[old_position_object_nr + TOP * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + TOP * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr + TOP * i].bg_color == PURPLE)
                    area[old_position_object_nr + TOP * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP * i].row == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1)
                    break;
                if (area[old_position_object_nr + TOP * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP * i].figure_color == BLACK)
                    {
                        area[old_position_object_nr + TOP * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8)
                    area[old_position_object_nr + TOP * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP * i].row == 1)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == BLACK)
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1)
                    break;
                if (area[old_position_object_nr + TOP * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP * i].figure_color == WHITE && virtual_area[old_position_object_nr + TOP * i].bg_color == GREEN || virtual_area[old_position_object_nr + TOP * i].checking == true)
                    {
                        area[old_position_object_nr + TOP * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr + TOP * i].bg_color == GREEN)
                    area[old_position_object_nr + TOP * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1)
                    break;
                if (area[old_position_object_nr + TOP * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP * i].figure_color == WHITE && virtual_area[old_position_object_nr + TOP * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + TOP * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr + TOP * i].bg_color == PURPLE)
                    area[old_position_object_nr + TOP * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP * i].row == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1)
                    break;
                if (area[old_position_object_nr + TOP * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP * i].figure_color == WHITE)
                    {
                        area[old_position_object_nr + TOP * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8)
                    area[old_position_object_nr + TOP * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP * i].row == 1)
                    break;
            }
        }
    }
}

void bottomSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == WHITE)
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8)
                    break;
                if (area[old_position_object_nr + BOTTOM * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM * i].figure_color == BLACK && virtual_area[old_position_object_nr + BOTTOM * i].bg_color == GREEN || virtual_area[old_position_object_nr + BOTTOM * i].checking == true)
                    {
                        area[old_position_object_nr + BOTTOM * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + BOTTOM * i].bg_color == GREEN)
                    area[old_position_object_nr + BOTTOM * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8)
                    break;
                if (area[old_position_object_nr + BOTTOM * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM * i].figure_color == BLACK && virtual_area[old_position_object_nr + BOTTOM * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + BOTTOM * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + BOTTOM * i].bg_color == PURPLE)
                    area[old_position_object_nr + BOTTOM * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM * i].row == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8)
                    break;
                if (area[old_position_object_nr + BOTTOM * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM * i].figure_color == BLACK)
                    {
                        area[old_position_object_nr + BOTTOM * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55)
                    area[old_position_object_nr + BOTTOM * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM * i].row == 8)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == BLACK)
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8)
                    break;
                if (area[old_position_object_nr + BOTTOM * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM * i].figure_color == WHITE && virtual_area[old_position_object_nr + BOTTOM * i].bg_color == GREEN || virtual_area[old_position_object_nr + BOTTOM * i].checking == true)
                    {
                        area[old_position_object_nr + BOTTOM * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + BOTTOM * i].bg_color == GREEN)
                    area[old_position_object_nr + BOTTOM * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8)
                    break;
                if (area[old_position_object_nr + BOTTOM * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM * i].figure_color == WHITE && virtual_area[old_position_object_nr + BOTTOM * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + BOTTOM * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + BOTTOM * i].bg_color == PURPLE)
                    area[old_position_object_nr + BOTTOM * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM * i].row == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8)
                    break;
                if (area[old_position_object_nr + BOTTOM * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM * i].figure_color == WHITE)
                    {
                        area[old_position_object_nr + BOTTOM * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55)
                    area[old_position_object_nr + BOTTOM * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM * i].row == 8)
                    break;
            }
        }
    }
}

void leftSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == WHITE)
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + LEFT * i].figure_color == BLACK && virtual_area[old_position_object_nr + LEFT * i].bg_color == GREEN || virtual_area[old_position_object_nr + LEFT * i].checking == true)
                    {
                        area[old_position_object_nr + LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column >= 2 && virtual_area[old_position_object_nr + LEFT * i].bg_color == GREEN)
                    area[old_position_object_nr + LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + LEFT * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + LEFT * i].figure_color == BLACK && virtual_area[old_position_object_nr + LEFT * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column >= 2 && virtual_area[old_position_object_nr + LEFT * i].bg_color == PURPLE)
                    area[old_position_object_nr + LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + LEFT * i].column == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + LEFT * i].figure_color == BLACK)
                    {
                        area[old_position_object_nr + LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column >= 2)
                    area[old_position_object_nr + LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + LEFT * i].column == 1)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == BLACK)
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + LEFT * i].figure_color == WHITE && virtual_area[old_position_object_nr + LEFT * i].bg_color == GREEN || virtual_area[old_position_object_nr + LEFT * i].checking == true)
                    {
                        area[old_position_object_nr + LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column >= 2 && virtual_area[old_position_object_nr + LEFT * i].bg_color == GREEN)
                    area[old_position_object_nr + LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + LEFT * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + LEFT * i].figure_color == WHITE && virtual_area[old_position_object_nr + LEFT * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column >= 2 && virtual_area[old_position_object_nr + LEFT * i].bg_color == PURPLE)
                    area[old_position_object_nr + LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + LEFT * i].column == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + LEFT * i].figure_color == WHITE)
                    {
                        area[old_position_object_nr + LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column >= 2)
                    area[old_position_object_nr + LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + LEFT * i].column == 1)
                    break;
            }
        }
    }
}

void rightSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == WHITE)
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + RIGHT * i].figure_color == BLACK && virtual_area[old_position_object_nr + RIGHT * i].bg_color == GREEN || virtual_area[old_position_object_nr + RIGHT * i].checking == true)
                    {
                        area[old_position_object_nr + RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column <= 7 && virtual_area[old_position_object_nr + RIGHT * i].bg_color == GREEN)
                    area[old_position_object_nr + RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + RIGHT * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + RIGHT * i].figure_color == BLACK && virtual_area[old_position_object_nr + RIGHT * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column <= 7 && virtual_area[old_position_object_nr + RIGHT * i].bg_color == PURPLE)
                    area[old_position_object_nr + RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + RIGHT * i].column == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + RIGHT * i].figure_color == BLACK)
                    {
                        area[old_position_object_nr + RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column <= 7)
                    area[old_position_object_nr + RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + RIGHT * i].column == 8)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == BLACK)
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + RIGHT * i].figure_color == WHITE && virtual_area[old_position_object_nr + RIGHT * i].bg_color == GREEN || virtual_area[old_position_object_nr + RIGHT * i].checking == true)
                    {
                        area[old_position_object_nr + RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column <= 7 && virtual_area[old_position_object_nr + RIGHT * i].bg_color == GREEN)
                    area[old_position_object_nr + RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + RIGHT * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + RIGHT * i].figure_color == WHITE && virtual_area[old_position_object_nr + RIGHT * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column <= 7 && virtual_area[old_position_object_nr + RIGHT * i].bg_color == PURPLE)
                    area[old_position_object_nr + RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + RIGHT * i].column == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + RIGHT * i].figure_color == WHITE)
                    {
                        area[old_position_object_nr + RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column <= 7)
                    area[old_position_object_nr + RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + RIGHT * i].column == 8)
                    break;
            }
        }
    }
}

void topLeftSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == WHITE)
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + TOP_LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP_LEFT * i].figure_color == BLACK && virtual_area[old_position_object_nr + TOP_LEFT * i].bg_color == GREEN || virtual_area[old_position_object_nr + TOP_LEFT * i].checking == true)
                    {
                        area[old_position_object_nr + TOP_LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 9 && virtual_area[old_position_object_nr + TOP_LEFT * i].bg_color == GREEN)
                    area[old_position_object_nr + TOP_LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP_LEFT * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + TOP_LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP_LEFT * i].figure_color == BLACK && virtual_area[old_position_object_nr + TOP_LEFT * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + TOP_LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 9 && virtual_area[old_position_object_nr + TOP_LEFT * i].bg_color == PURPLE)
                    area[old_position_object_nr + TOP_LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP_LEFT * i].row == 1 || area[old_position_object_nr + TOP_LEFT * i].column == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + TOP_LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP_LEFT * i].figure_color == BLACK)
                    {
                        area[old_position_object_nr + TOP_LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 9)
                    area[old_position_object_nr + TOP_LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP_LEFT * i].row == 1 || area[old_position_object_nr + TOP_LEFT * i].column == 1)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == BLACK)
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + TOP_LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP_LEFT * i].figure_color == WHITE && virtual_area[old_position_object_nr + TOP_LEFT * i].bg_color == GREEN || virtual_area[old_position_object_nr + TOP_LEFT * i].checking == true)
                    {
                        area[old_position_object_nr + TOP_LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 9 && virtual_area[old_position_object_nr + TOP_LEFT * i].bg_color == GREEN)
                    area[old_position_object_nr + TOP_LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP_LEFT * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + TOP_LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP_LEFT * i].figure_color == WHITE && virtual_area[old_position_object_nr + TOP_LEFT * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + TOP_LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 9 && virtual_area[old_position_object_nr + TOP_LEFT * i].bg_color == PURPLE)
                    area[old_position_object_nr + TOP_LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP_LEFT * i].row == 1 || area[old_position_object_nr + TOP_LEFT * i].column == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + TOP_LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP_LEFT * i].figure_color == WHITE)
                    {
                        area[old_position_object_nr + TOP_LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 9)
                    area[old_position_object_nr + TOP_LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP_LEFT * i].row == 1 || area[old_position_object_nr + TOP_LEFT * i].column == 1)
                    break;
            }
        }
    }
}

void topRighttSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == WHITE)
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + TOP_RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP_RIGHT * i].figure_color == WHITE && virtual_area[old_position_object_nr + TOP_RIGHT * i].bg_color == GREEN || virtual_area[old_position_object_nr + TOP_RIGHT * i].checking == true)
                    {
                        area[old_position_object_nr + TOP_RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr + TOP_RIGHT * i].bg_color == GREEN)
                    area[old_position_object_nr + TOP_RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP_RIGHT * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + TOP_RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP_RIGHT * i].figure_color == BLACK && virtual_area[old_position_object_nr + TOP_RIGHT * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + TOP_RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr + TOP_RIGHT * i].bg_color == PURPLE)
                    area[old_position_object_nr + TOP_RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP_RIGHT * i].row == 1 || area[old_position_object_nr + TOP_RIGHT * i].column == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + TOP_RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP_RIGHT * i].figure_color == BLACK)
                    {
                        area[old_position_object_nr + TOP_RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8)
                    area[old_position_object_nr + TOP_RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP_RIGHT * i].row == 1 || area[old_position_object_nr + TOP_RIGHT * i].column == 8)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == BLACK)
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + TOP_RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP_RIGHT * i].figure_color == WHITE && virtual_area[old_position_object_nr + TOP_RIGHT * i].bg_color == GREEN || virtual_area[old_position_object_nr + TOP_RIGHT * i].checking == true)
                    {
                        area[old_position_object_nr + TOP_RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr + TOP_RIGHT * i].bg_color == GREEN)
                    area[old_position_object_nr + TOP_RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP_RIGHT * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + TOP_RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP_RIGHT * i].figure_color == WHITE && virtual_area[old_position_object_nr + TOP_RIGHT * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + TOP_RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr + TOP_RIGHT * i].bg_color == PURPLE)
                    area[old_position_object_nr + TOP_RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP_RIGHT * i].row == 1 || area[old_position_object_nr + TOP_RIGHT * i].column == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + TOP_RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + TOP_RIGHT * i].figure_color == WHITE)
                    {
                        area[old_position_object_nr + TOP_RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8)
                    area[old_position_object_nr + TOP_RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + TOP_RIGHT * i].row == 1 || area[old_position_object_nr + TOP_RIGHT * i].column == 8)
                    break;
            }
        }
    }
}

void bottomLeftSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == WHITE)
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + BOTTOM_LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM_LEFT * i].figure_color == BLACK && virtual_area[old_position_object_nr + BOTTOM_LEFT * i].bg_color == GREEN || virtual_area[old_position_object_nr + BOTTOM_LEFT * i].checking == true)
                    {
                        area[old_position_object_nr + BOTTOM_LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + BOTTOM_LEFT * i].bg_color == GREEN)
                    area[old_position_object_nr + BOTTOM_LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM_LEFT * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + BOTTOM_LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM_LEFT * i].figure_color == BLACK && virtual_area[old_position_object_nr + BOTTOM_LEFT * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + BOTTOM_LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + BOTTOM_LEFT * i].bg_color == PURPLE)
                    area[old_position_object_nr + BOTTOM_LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM_LEFT * i].row == 8 || area[old_position_object_nr + BOTTOM_LEFT * i].column == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + BOTTOM_LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM_LEFT * i].figure_color == BLACK)
                    {
                        area[old_position_object_nr + BOTTOM_LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55)
                    area[old_position_object_nr + BOTTOM_LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM_LEFT * i].row == 8 || area[old_position_object_nr + BOTTOM_LEFT * i].column == 1)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == BLACK)
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + BOTTOM_LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM_LEFT * i].figure_color == WHITE && virtual_area[old_position_object_nr + BOTTOM_LEFT * i].bg_color == GREEN || virtual_area[old_position_object_nr + BOTTOM_LEFT * i].checking == true)
                    {
                        area[old_position_object_nr + BOTTOM_LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + BOTTOM_LEFT * i].bg_color == GREEN)
                    area[old_position_object_nr + BOTTOM_LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM_LEFT * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + BOTTOM_LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM_LEFT * i].figure_color == WHITE && virtual_area[old_position_object_nr + BOTTOM_LEFT * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + BOTTOM_LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + BOTTOM_LEFT * i].bg_color == PURPLE)
                    area[old_position_object_nr + BOTTOM_LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM_LEFT * i].row == 8 || area[old_position_object_nr + BOTTOM_LEFT * i].column == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + BOTTOM_LEFT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM_LEFT * i].figure_color == WHITE)
                    {
                        area[old_position_object_nr + BOTTOM_LEFT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55)
                    area[old_position_object_nr + BOTTOM_LEFT * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM_LEFT * i].row == 8 || area[old_position_object_nr + BOTTOM_LEFT * i].column == 1)
                    break;
            }
        }
    }
}

void bottomRightSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == WHITE)
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + BOTTOM_RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM_RIGHT * i].figure_color == BLACK && virtual_area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color == GREEN || virtual_area[old_position_object_nr + BOTTOM_RIGHT * i].checking == true)
                    {
                        area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 54 && virtual_area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color == GREEN)
                    area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM_RIGHT * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + BOTTOM_RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM_RIGHT * i].figure_color == BLACK && virtual_area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 54 && virtual_area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color == PURPLE)
                    area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM_RIGHT * i].row == 8 || area[old_position_object_nr + BOTTOM_RIGHT * i].column == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + BOTTOM_RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM_RIGHT * i].figure_color == BLACK)
                    {
                        area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 54)
                    area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM_RIGHT * i].row == 8 || area[old_position_object_nr + BOTTOM_RIGHT * i].column == 8)
                    break;
            }
        }
    }

    // BLACK
    if (area[old_position_object_nr].figure_color == BLACK)
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == PURPLE)
            ;
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + BOTTOM_RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM_RIGHT * i].figure_color == WHITE && virtual_area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color == GREEN || virtual_area[old_position_object_nr + BOTTOM_RIGHT * i].checking == true)
                    {
                        area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 54 && virtual_area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color == GREEN)
                    area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM_RIGHT * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == PURPLE)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + BOTTOM_RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM_RIGHT * i].figure_color == WHITE && virtual_area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color == PURPLE)
                    {
                        area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 54 && virtual_area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color == PURPLE)
                    area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM_RIGHT * i].row == 8 || area[old_position_object_nr + BOTTOM_RIGHT * i].column == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + BOTTOM_RIGHT * i].figure_color != EMPTY)
                {
                    if (area[old_position_object_nr + BOTTOM_RIGHT * i].figure_color == WHITE)
                    {
                        area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color = RED;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 54)
                    area[old_position_object_nr + BOTTOM_RIGHT * i].bg_color = GREEN;
                if (area[old_position_object_nr + BOTTOM_RIGHT * i].row == 8 || area[old_position_object_nr + BOTTOM_RIGHT * i].column == 8)
                    break;
            }
        }
    }
}

void paintVirtualAreaWhiteColors()
{
    if (virtual_area[virtual_position_object_nr].figure == PAWN)
        paintVirtualAreaColorsWhitePawn();
    else if (virtual_area[virtual_position_object_nr].figure == KNIGHT)
        paintVirtualAreaColorsWhiteKnight();
    else if (virtual_area[virtual_position_object_nr].figure == BISHOP)
        paintVirtualAreaColorsWhiteBishop();
    else if (virtual_area[virtual_position_object_nr].figure == ROOK)
        paintVirtualAreaColorsWhiteRook();
    else if (virtual_area[virtual_position_object_nr].figure == QUEEN)
        paintVirtualAreaColorsWhiteQueen();
    else if (virtual_area[virtual_position_object_nr].figure == KING)
        paintVirtualAreaColorsWhiteKing();
}

void paintVirtualAreaColorsWhitePawn()
{
    if (virtual_area[virtual_position_object_nr].figure_color == WHITE)
    {
        // TOP LEFT
        if (virtual_area[virtual_position_object_nr + TOP_LEFT].big_figure == "blackKing")
        {
            if (virtual_area[virtual_position_object_nr + TOP_LEFT].bg_color != YELLOW)
                virtual_area[virtual_position_object_nr + TOP_LEFT].bg_color = GREEN;
            if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                virtual_area[virtual_position_object_nr].bg_color = GREEN;
            virtual_area[virtual_position_object_nr].checking = true;
        }
        else if (virtual_area[virtual_position_object_nr + TOP_LEFT].figure_color != WHITE && virtual_area[virtual_position_object_nr].column > 1 && virtual_area[virtual_position_object_nr + TOP_LEFT].bg_color != YELLOW && virtual_area[virtual_position_object_nr + TOP_LEFT].bg_color != GREEN && virtual_area[virtual_position_object_nr + TOP_LEFT].bg_color != PURPLE)
            virtual_area[virtual_position_object_nr + TOP_LEFT].bg_color = RED;
        else if (virtual_area[virtual_position_object_nr + TOP_LEFT].figure_color == WHITE && virtual_area[virtual_position_object_nr].column > 1 && virtual_area[virtual_position_object_nr + TOP_LEFT].bg_color != PURPLE)
            virtual_area[virtual_position_object_nr + TOP_LEFT].bg_color = YELLOW;

        // TOP RIGHT
        if (virtual_area[virtual_position_object_nr + TOP_RIGHT].big_figure == "blackKing")
        {
            if (virtual_area[virtual_position_object_nr + TOP_RIGHT].bg_color != YELLOW)
                virtual_area[virtual_position_object_nr + TOP_RIGHT].bg_color = GREEN;
            if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                virtual_area[virtual_position_object_nr].bg_color = GREEN;
            virtual_area[virtual_position_object_nr].checking = true;
        }
        else if (virtual_area[virtual_position_object_nr + TOP_RIGHT].figure_color != WHITE && virtual_area[virtual_position_object_nr].column < 8 && virtual_area[virtual_position_object_nr + TOP_RIGHT].bg_color != YELLOW && virtual_area[virtual_position_object_nr + TOP_RIGHT].bg_color != GREEN && virtual_area[virtual_position_object_nr + TOP_RIGHT].bg_color != PURPLE)
            virtual_area[virtual_position_object_nr + TOP_RIGHT].bg_color = RED;
        else if (virtual_area[virtual_position_object_nr + TOP_RIGHT].figure_color == WHITE && virtual_area[virtual_position_object_nr].column < 8 && virtual_area[virtual_position_object_nr + TOP_RIGHT].bg_color != PURPLE)
            virtual_area[virtual_position_object_nr + TOP_RIGHT].bg_color = YELLOW;
    }
}

void paintVirtualAreaColorsWhiteKnight()
{
    if (virtual_area[virtual_position_object_nr].figure_color == WHITE)
    {
        // TOP TOP LEFT
        if (virtual_position_object_nr >= 17)
        {
            if (virtual_area[virtual_position_object_nr].column >= 2)
            {
                if (virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].figure_color != WHITE && virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color != YELLOW && virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color != GREEN && virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].figure_color == WHITE && virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color = YELLOW;
            }
        }

        // TOP TOP RIGHT
        if (virtual_position_object_nr >= 16)
        {
            if (virtual_area[virtual_position_object_nr].column <= 7)
            {
                if (virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].figure_color != WHITE && virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color != YELLOW && virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color != GREEN && virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].figure_color == WHITE && virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color = YELLOW;
            }
        }

        // BOTTOM BOTTOM LEFT
        if (virtual_position_object_nr <= 47)
        {
            if (virtual_area[virtual_position_object_nr].column >= 2)
            {
                if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].figure_color != WHITE && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color != YELLOW && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color != GREEN && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].figure_color == WHITE && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = YELLOW;
            }
        }

        // BOTTOM BOTTOM RIGHT
        if (virtual_position_object_nr <= 46)
        {
            if (virtual_area[virtual_position_object_nr].column <= 7)
            {
                if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].figure_color != WHITE && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color != YELLOW && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color != GREEN && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].figure_color == WHITE && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = YELLOW;
            }
        }

        // LEFT LEFT TOP
        if (virtual_position_object_nr >= 10)
        {
            if (virtual_area[virtual_position_object_nr].column >= 3)
            {
                if (virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].figure_color != WHITE && virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color != YELLOW && virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color != GREEN && virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].figure_color == WHITE && virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color = YELLOW;
            }
        }

        // LEFT LEFT BOTTOM
        if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr].column >= 3)
            {
                if (virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].figure_color != WHITE && virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color != YELLOW && virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color != GREEN && virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].figure_color == WHITE && virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = YELLOW;
            }
        }

        // RIGH RIGHT TOP
        if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr].column <= 6)
            {
                if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].figure_color != WHITE && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color != YELLOW && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color != GREEN && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].figure_color == WHITE && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color = YELLOW;
            }
        }

        // RIGH RIGHT BOTTOM
        if (virtual_position_object_nr <= 53)
        {
            if (virtual_area[virtual_position_object_nr].column <= 6)
            {
                if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].figure_color != WHITE && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color != YELLOW && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color != GREEN && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].figure_color == WHITE && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = YELLOW;
            }
        }
    }
}

void paintVirtualAreaColorsWhiteBishop()
{
    if (virtual_area[virtual_position_object_nr].figure_color == WHITE)
    {
        virtualWhiteTopLeftSide();
        virtualWhiteTopRightSide();
        virtualWhiteBottomLeftSide();
        virtualWhiteBottomRightSide();
    }
}

void paintVirtualAreaColorsWhiteRook()
{
    if (virtual_area[virtual_position_object_nr].figure_color == WHITE)
    {
        virtualWhiteTopSide();
        virtualWhiteBottomSide();
        virtualWhiteLeftSide();
        virtualWhiteRightSide();
    }
}

void paintVirtualAreaColorsWhiteQueen()
{
    if (virtual_area[virtual_position_object_nr].figure_color == WHITE)
    {
        virtualWhiteTopSide();
        virtualWhiteBottomSide();
        virtualWhiteLeftSide();
        virtualWhiteRightSide();
        virtualWhiteTopLeftSide();
        virtualWhiteTopRightSide();
        virtualWhiteBottomLeftSide();
        virtualWhiteBottomRightSide();
    }
}

void paintVirtualAreaColorsWhiteKing()
{
    if (virtual_area[virtual_position_object_nr].figure_color == WHITE)
    {
        // TOP SIDE
        if (virtual_area[virtual_position_object_nr].row > 1)
        {
            if (virtual_area[virtual_position_object_nr + TOP].figure_color != WHITE)
                virtual_area[virtual_position_object_nr + TOP].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + TOP].figure_color == WHITE)
                virtual_area[virtual_position_object_nr + TOP].bg_color = YELLOW;
        }

        // BOTTOM SIDE
        if (virtual_area[virtual_position_object_nr].row < 8)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM].figure_color != WHITE)
                virtual_area[virtual_position_object_nr + BOTTOM].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + BOTTOM].figure_color == WHITE)
                virtual_area[virtual_position_object_nr + BOTTOM].bg_color = YELLOW;
        }

        // LEFT SIDE
        if (virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr + LEFT].figure_color != WHITE)
                virtual_area[virtual_position_object_nr + LEFT].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + LEFT].figure_color == WHITE)
                virtual_area[virtual_position_object_nr + LEFT].bg_color = YELLOW;
        }

        // RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + RIGHT].figure_color != WHITE)
                virtual_area[virtual_position_object_nr + RIGHT].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + RIGHT].figure_color == WHITE)
                virtual_area[virtual_position_object_nr + RIGHT].bg_color = YELLOW;
        }

        // TOP LEFT SIDE
        if (virtual_area[virtual_position_object_nr].row > 1 && virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr + TOP_LEFT].figure_color != WHITE)
                virtual_area[virtual_position_object_nr + TOP_LEFT].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + TOP_LEFT].figure_color == WHITE)
                virtual_area[virtual_position_object_nr + TOP_LEFT].bg_color = YELLOW;
        }

        // TOP RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].row > 1 && virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + TOP_RIGHT].figure_color != WHITE)
                virtual_area[virtual_position_object_nr + TOP_RIGHT].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + TOP_RIGHT].figure_color == WHITE)
                virtual_area[virtual_position_object_nr + TOP_RIGHT].bg_color = YELLOW;
        }

        // BOTTOM LEFT SIDE
        if (virtual_area[virtual_position_object_nr].row < 8 && virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT].figure_color != WHITE)
                virtual_area[virtual_position_object_nr + BOTTOM_LEFT].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT].figure_color == WHITE)
                virtual_area[virtual_position_object_nr + BOTTOM_LEFT].bg_color = YELLOW;
        }

        // BOTTOM RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].row < 8 && virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].figure_color != WHITE)
                virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].figure_color == WHITE)
                virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].bg_color = YELLOW;
        }
    }
}

void paintVirtualAreaBlackColors()
{
    if (virtual_area[virtual_position_object_nr].figure == PAWN)
        paintVirtualAreaColorsBlackPawn();
    else if (virtual_area[virtual_position_object_nr].figure == KNIGHT)
        paintVirtualAreaColorsBlackKnight();
    else if (virtual_area[virtual_position_object_nr].figure == BISHOP)
        paintVirtualAreaColorsBlackBishop();
    else if (virtual_area[virtual_position_object_nr].figure == ROOK)
        paintVirtualAreaColorsBlackRook();
    else if (virtual_area[virtual_position_object_nr].figure == QUEEN)
        paintVirtualAreaColorsBlackQueen();
    else if (virtual_area[virtual_position_object_nr].figure == KING)
        paintVirtualAreaColorsBlackKing();
}

void paintVirtualAreaColorsBlackPawn()
{
    if (virtual_area[virtual_position_object_nr].figure_color == BLACK)
    {
        // BOTTOM LEFT
        if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT].big_figure == "whiteKing")
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT].bg_color != YELLOW)
                virtual_area[virtual_position_object_nr + BOTTOM_LEFT].bg_color = GREEN;
            if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                virtual_area[virtual_position_object_nr].bg_color = GREEN;
            virtual_area[virtual_position_object_nr].checking = true;
        }
        else if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT].figure_color != BLACK && virtual_area[virtual_position_object_nr].column > 1 && virtual_area[virtual_position_object_nr + BOTTOM_LEFT].bg_color != YELLOW && virtual_area[virtual_position_object_nr + BOTTOM_LEFT].bg_color != GREEN && virtual_area[virtual_position_object_nr + BOTTOM_LEFT].bg_color != PURPLE)
            virtual_area[virtual_position_object_nr + BOTTOM_LEFT].bg_color = RED;
        else if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT].figure_color == BLACK && virtual_area[virtual_position_object_nr].column > 1 && virtual_area[virtual_position_object_nr + BOTTOM_LEFT].bg_color != PURPLE)
            virtual_area[virtual_position_object_nr + BOTTOM_LEFT].bg_color = YELLOW;

        // BOTTOM RIGHT
        if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].big_figure == "whiteKing")
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].bg_color != YELLOW)
                virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].bg_color = GREEN;
            if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                virtual_area[virtual_position_object_nr].bg_color = GREEN;
            virtual_area[virtual_position_object_nr].checking = true;
        }
        else if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].figure_color != BLACK && virtual_area[virtual_position_object_nr].column < 8 && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].bg_color != YELLOW && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].bg_color != GREEN && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].bg_color != PURPLE)
            virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].bg_color = RED;
        else if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].figure_color == BLACK && virtual_area[virtual_position_object_nr].column < 8 && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].bg_color != PURPLE)
            virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].bg_color = YELLOW;
    }
}

void paintVirtualAreaColorsBlackKnight()
{
    if (virtual_area[virtual_position_object_nr].figure_color == BLACK)
    {
        // TOP TOP LEFT
        if (virtual_position_object_nr >= 17)
        {
            if (virtual_area[virtual_position_object_nr].column >= 2)
            {
                if (virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].figure_color != BLACK && virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color != YELLOW && virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color != GREEN && virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].figure_color == BLACK && virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + TOP_TOP_LEFT].bg_color = YELLOW;
            }
        }

        // TOP TOP RIGHT
        if (virtual_position_object_nr >= 16)
        {
            if (virtual_area[virtual_position_object_nr].column <= 7)
            {
                if (virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].figure_color != BLACK && virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color != YELLOW && virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color != GREEN && virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].figure_color == BLACK && virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + TOP_TOP_RIGHT].bg_color = YELLOW;
            }
        }

        // BOTTOM BOTTOM LEFT
        if (virtual_position_object_nr <= 47)
        {
            if (virtual_area[virtual_position_object_nr].column >= 2)
            {
                if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].figure_color != BLACK && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color != YELLOW && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color != GREEN && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].figure_color == BLACK && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_LEFT].bg_color = YELLOW;
            }
        }

        // BOTTOM BOTTOM RIGHT
        if (virtual_position_object_nr <= 46)
        {
            if (virtual_area[virtual_position_object_nr].column <= 7)
            {
                if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].figure_color != BLACK && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color != YELLOW && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color != GREEN && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].figure_color == BLACK && virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + BOTTOM_BOTTOM_RIGHT].bg_color = YELLOW;
            }
        }

        // LEFT LEFT TOP
        if (virtual_position_object_nr >= 10)
        {
            if (virtual_area[virtual_position_object_nr].column >= 3)
            {
                if (virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].figure_color != BLACK && virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color != YELLOW && virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color != GREEN && virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].figure_color == BLACK && virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + LEFT_LEFT_TOP].bg_color = YELLOW;
            }
        }

        // LEFT LEFT BOTTOM
        if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr].column >= 3)
            {
                if (virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].figure_color != BLACK && virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color != YELLOW && virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color != GREEN && virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].figure_color == BLACK && virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + LEFT_LEFT_BOTTOM].bg_color = YELLOW;
            }
        }

        // RIGH RIGHT TOP
        if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr].column <= 6)
            {
                if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].figure_color != BLACK && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color != YELLOW && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color != GREEN && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].figure_color == BLACK && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + RIGHT_RIGHT_TOP].bg_color = YELLOW;
            }
        }

        // RIGH RIGHT BOTTOM
        if (virtual_position_object_nr <= 53)
        {
            if (virtual_area[virtual_position_object_nr].column <= 6)
            {
                if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = GREEN;
                    if (virtual_area[virtual_position_object_nr].bg_color != GREEN)
                        virtual_area[virtual_position_object_nr].bg_color = GREEN;
                    virtual_area[virtual_position_object_nr].checking = true;
                }
                else if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].figure_color != BLACK && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color != YELLOW && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color != GREEN && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = RED;
                else if (virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].figure_color == BLACK && virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color != PURPLE)
                    virtual_area[virtual_position_object_nr + RIGHT_RIGHT_BOTTOM].bg_color = YELLOW;
            }
        }
    }
}

void paintVirtualAreaColorsBlackBishop()
{
    if (virtual_area[virtual_position_object_nr].figure_color == BLACK)
    {
        virtualBlackTopLeftSide();
        virtualBlackTopRightSide();
        virtualBlackBottomLeftSide();
        virtualBlackBottomRightSide();
    }
}

void paintVirtualAreaColorsBlackRook()
{
    if (virtual_area[virtual_position_object_nr].figure_color == BLACK)
    {
        virtualBlackTopSide();
        virtualBlackBottomSide();
        virtualBlackLeftSide();
        virtualBlackRightSide();
    }
}

void paintVirtualAreaColorsBlackQueen()
{
    if (virtual_area[virtual_position_object_nr].figure_color == BLACK)
    {
        virtualBlackTopSide();
        virtualBlackBottomSide();
        virtualBlackLeftSide();
        virtualBlackRightSide();
        virtualBlackTopLeftSide();
        virtualBlackTopRightSide();
        virtualBlackBottomLeftSide();
        virtualBlackBottomRightSide();
    }
}

void paintVirtualAreaColorsBlackKing()
{
    if (virtual_area[virtual_position_object_nr].figure_color == BLACK)
    {
        // TOP SIDE
        if (virtual_area[virtual_position_object_nr].row > 1)
        {
            if (virtual_area[virtual_position_object_nr + TOP].figure_color != BLACK)
                virtual_area[virtual_position_object_nr + TOP].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + TOP].figure_color == BLACK)
                virtual_area[virtual_position_object_nr + TOP].bg_color = YELLOW;
        }

        // BOTTOM SIDE
        if (virtual_area[virtual_position_object_nr].row < 8)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM].figure_color != BLACK)
                virtual_area[virtual_position_object_nr + BOTTOM].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + BOTTOM].figure_color == BLACK)
                virtual_area[virtual_position_object_nr + BOTTOM].bg_color = YELLOW;
        }

        // LEFT SIDE
        if (virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr + LEFT].figure_color != BLACK)
                virtual_area[virtual_position_object_nr + LEFT].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + LEFT].figure_color == BLACK)
                virtual_area[virtual_position_object_nr + LEFT].bg_color = YELLOW;
        }

        // RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + RIGHT].figure_color != BLACK)
                virtual_area[virtual_position_object_nr + RIGHT].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + RIGHT].figure_color == BLACK)
                virtual_area[virtual_position_object_nr + RIGHT].bg_color = YELLOW;
        }

        // TOP LEFT SIDE
        if (virtual_area[virtual_position_object_nr].row > 1 && virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr + TOP_LEFT].figure_color != BLACK)
                virtual_area[virtual_position_object_nr + TOP_LEFT].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + TOP_LEFT].figure_color == BLACK)
                virtual_area[virtual_position_object_nr + TOP_LEFT].bg_color = YELLOW;
        }

        // TOP RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].row > 1 && virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + TOP_RIGHT].figure_color != BLACK)
                virtual_area[virtual_position_object_nr + TOP_RIGHT].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + TOP_RIGHT].figure_color == BLACK)
                virtual_area[virtual_position_object_nr + TOP_RIGHT].bg_color = YELLOW;
        }

        // BOTTOM LEFT SIDE
        if (virtual_area[virtual_position_object_nr].row < 8 && virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT].figure_color != BLACK)
                virtual_area[virtual_position_object_nr + BOTTOM_LEFT].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT].figure_color == BLACK)
                virtual_area[virtual_position_object_nr + BOTTOM_LEFT].bg_color = YELLOW;
        }

        // BOTTOM RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].row < 8 && virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].figure_color != BLACK)
                virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].bg_color = RED;
            else if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].figure_color == BLACK)
                virtual_area[virtual_position_object_nr + BOTTOM_RIGHT].bg_color = YELLOW;
        }
    }
}

void virtualWhiteTopSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].row == 1)
            break;
        if (virtual_area[virtual_position_object_nr + TOP * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + TOP * i].big_figure == "blackKing")
            {
                if (virtual_area[virtual_position_object_nr + TOP * i].row != 1 && virtual_area[virtual_position_object_nr + TOP * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + TOP * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + TOP * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + TOP * i].figure_color == BLACK)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + TOP * (i + k)].row == 1 && virtual_area[virtual_position_object_nr + TOP * (i + k)].big_figure != "blackKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + TOP * (i + k)].big_figure != "blackKing")
                    {
                        if (virtual_area[virtual_position_object_nr + TOP * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + TOP * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + TOP * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + TOP * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + TOP * (i + k)].big_figure == "blackKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + TOP * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + TOP * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + TOP * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr + TOP * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + TOP * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + TOP * i].row == 1)
            break;
    }
}

void virtualWhiteBottomSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].row == 8)
            break;
        if (virtual_area[virtual_position_object_nr + BOTTOM * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM * i].big_figure == "blackKing")
            {
                if (virtual_area[virtual_position_object_nr + BOTTOM * i].row != 8 && virtual_area[virtual_position_object_nr + BOTTOM * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + BOTTOM * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + BOTTOM * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + BOTTOM * i].figure_color == BLACK)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + BOTTOM * (i + k)].row == 8 && virtual_area[virtual_position_object_nr + BOTTOM * (i + k)].big_figure != "blackKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + BOTTOM * (i + k)].big_figure != "blackKing")
                    {
                        if (virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + BOTTOM * (i + k)].big_figure == "blackKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + BOTTOM * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + BOTTOM * i].row == 8)
            break;
    }
}

void virtualWhiteLeftSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].column == 1)
            break;
        if (virtual_area[virtual_position_object_nr + LEFT * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + LEFT * i].big_figure == "blackKing")
            {
                if (virtual_area[virtual_position_object_nr + LEFT * i].column != 1 && virtual_area[virtual_position_object_nr + LEFT * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + LEFT * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + LEFT * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + LEFT * i].figure_color == BLACK)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + LEFT * (i + k)].column == 1 && virtual_area[virtual_position_object_nr + LEFT * (i + k)].big_figure != "blackKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + LEFT * (i + k)].big_figure != "blackKing")
                    {
                        if (virtual_area[virtual_position_object_nr + LEFT * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + LEFT * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + LEFT * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + LEFT * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + LEFT * (i + k)].big_figure == "blackKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + LEFT * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + LEFT * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + LEFT * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_area[virtual_position_object_nr].column >= 2)
        {
            if (virtual_area[virtual_position_object_nr + LEFT * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + LEFT * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + LEFT * i].column == 1)
            break;
    }
}

void virtualWhiteRightSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].column == 8)
            break;
        if (virtual_area[virtual_position_object_nr + RIGHT * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + RIGHT * i].big_figure == "blackKing")
            {
                if (virtual_area[virtual_position_object_nr + RIGHT * i].column != 8 && virtual_area[virtual_position_object_nr + RIGHT * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + RIGHT * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + RIGHT * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + RIGHT * i].figure_color == BLACK)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + RIGHT * (i + k)].column == 8 && virtual_area[virtual_position_object_nr + RIGHT * (i + k)].big_figure != "blackKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + RIGHT * (i + k)].big_figure != "blackKing")
                    {
                        if (virtual_area[virtual_position_object_nr + RIGHT * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + RIGHT * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + RIGHT * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + RIGHT * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + RIGHT * (i + k)].big_figure == "blackKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + RIGHT * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + RIGHT * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + RIGHT * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_area[virtual_position_object_nr].column <= 7)
        {
            if (virtual_area[virtual_position_object_nr + RIGHT * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + RIGHT * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + RIGHT * i].column == 8)
            break;
    }
}

void virtualWhiteTopLeftSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].row == 1 || virtual_area[virtual_position_object_nr].column == 1)
            break;
        if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].figure_color != EMPTY)
        {

            if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].big_figure == "blackKing")
            {
                if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].row != 1 && virtual_area[virtual_position_object_nr + TOP_LEFT * i].column != 1 && virtual_area[virtual_position_object_nr + TOP_LEFT * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + TOP_LEFT * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + TOP_LEFT * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }

            else if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].figure_color == BLACK)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + TOP_LEFT * (i + k)].row == 1 && virtual_area[virtual_position_object_nr + TOP_LEFT * (i + k)].column == 1 && virtual_area[virtual_position_object_nr + TOP_LEFT * (i + k)].big_figure != "blackKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + TOP_LEFT * (i + k)].big_figure != "blackKing")
                    {
                        if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + TOP_LEFT * (i + k)].big_figure == "blackKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + TOP_LEFT * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr >= 9)
        {
            if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].row == 1 || virtual_area[virtual_position_object_nr + TOP_LEFT * i].column == 1)
            break;
    }
}

void virtualWhiteTopRightSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].row == 1 || virtual_area[virtual_position_object_nr].column == 8)
            break;
        if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].big_figure == "blackKing")
            {
                if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].row != 1 && virtual_area[virtual_position_object_nr + TOP_RIGHT * i].column != 8 && virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + TOP_RIGHT * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].figure_color == BLACK)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + k)].row == 1 && virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + k)].column == 8 && virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + k)].big_figure != "blackKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + k)].big_figure != "blackKing")
                    {
                        if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + k)].big_figure == "blackKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + TOP_RIGHT * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].row == 1 || virtual_area[virtual_position_object_nr + TOP_RIGHT * i].column == 8)
            break;
    }
}

void virtualWhiteBottomLeftSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].row == 8 || virtual_area[virtual_position_object_nr].column == 1)
            break;
        if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].big_figure == "blackKing")
            {
                if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].row != 8 && virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].column != 1 && virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + BOTTOM_LEFT * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].figure_color == BLACK)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + k)].row == 8 && virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + k)].column == 1 && virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + k)].big_figure != "blackKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + k)].big_figure != "blackKing")
                    {
                        if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + k)].big_figure == "blackKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + BOTTOM_LEFT * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].row == 8 || virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].column == 1)
            break;
    }
}

void virtualWhiteBottomRightSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].row == 8 || virtual_area[virtual_position_object_nr].column == 8)
            break;
        if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].big_figure == "blackKing")
            {
                if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].row != 8 && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].column != 8 && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].figure_color == BLACK)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + k)].row == 8 && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + k)].column == 8 && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + k)].big_figure != "blackKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + k)].big_figure != "blackKing")
                    {
                        if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + k)].big_figure == "blackKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr <= 54)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].row == 8 || virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].column == 8)
            break;
    }
}

void virtualBlackTopSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].row == 1)
            break;
        if (virtual_area[virtual_position_object_nr + TOP * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + TOP * i].big_figure == "whiteKing")
            {
                if (virtual_area[virtual_position_object_nr + TOP * i].row != 1 && virtual_area[virtual_position_object_nr + TOP * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + TOP * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + TOP * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + TOP * i].figure_color == WHITE)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + TOP * (i + k)].row == 1 && virtual_area[virtual_position_object_nr + TOP * (i + k)].big_figure != "whiteKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + TOP * (i + k)].big_figure != "whiteKing")
                    {
                        if (virtual_area[virtual_position_object_nr + TOP * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + TOP * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + TOP * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + TOP * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + TOP * (i + k)].big_figure == "whiteKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + TOP * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + TOP * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + TOP * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr + TOP * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + TOP * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + TOP * i].row == 1)
            break;
    }
}

void virtualBlackBottomSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].row == 8)
            break;
        if (virtual_area[virtual_position_object_nr + BOTTOM * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM * i].big_figure == "whiteKing")
            {
                if (virtual_area[virtual_position_object_nr + BOTTOM * i].row != 8 && virtual_area[virtual_position_object_nr + BOTTOM * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + BOTTOM * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + BOTTOM * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + BOTTOM * i].figure_color == WHITE)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + BOTTOM * (i + k)].row == 8 && virtual_area[virtual_position_object_nr + BOTTOM * (i + k)].big_figure != "whiteKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + BOTTOM * (i + k)].big_figure != "whiteKing")
                    {
                        if (virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + BOTTOM * (i + k)].big_figure == "whiteKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + BOTTOM * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + BOTTOM * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + BOTTOM * i].row == 8)
            break;
    }
}

void virtualBlackLeftSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].column == 1)
            break;
        if (virtual_area[virtual_position_object_nr + LEFT * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + LEFT * i].big_figure == "whiteKing")
            {
                if (virtual_area[virtual_position_object_nr + LEFT * i].column != 1 && virtual_area[virtual_position_object_nr + LEFT * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + LEFT * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + LEFT * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + LEFT * i].figure_color == WHITE)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + LEFT * (i + k)].column == 1 && virtual_area[virtual_position_object_nr + LEFT * (i + k)].big_figure != "whiteKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + LEFT * (i + k)].big_figure != "whiteKing")
                    {
                        if (virtual_area[virtual_position_object_nr + LEFT * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + LEFT * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + LEFT * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + LEFT * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + LEFT * (i + k)].big_figure == "whiteKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + LEFT * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + LEFT * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + LEFT * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_area[virtual_position_object_nr].column >= 2)
        {
            if (virtual_area[virtual_position_object_nr + LEFT * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + LEFT * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + LEFT * i].column == 1)
            break;
    }
}

void virtualBlackRightSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].column == 8)
            break;
        if (virtual_area[virtual_position_object_nr + RIGHT * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + RIGHT * i].big_figure == "whiteKing")
            {
                if (virtual_area[virtual_position_object_nr + RIGHT * i].column != 8 && virtual_area[virtual_position_object_nr + RIGHT * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + RIGHT * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + RIGHT * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + RIGHT * i].figure_color == WHITE)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + RIGHT * (i + k)].column == 8 && virtual_area[virtual_position_object_nr + RIGHT * (i + k)].big_figure != "whiteKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + RIGHT * (i + k)].big_figure != "whiteKing")
                    {
                        if (virtual_area[virtual_position_object_nr + RIGHT * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + RIGHT * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + RIGHT * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + RIGHT * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + RIGHT * (i + k)].big_figure == "whiteKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + RIGHT * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + RIGHT * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + RIGHT * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_area[virtual_position_object_nr].column <= 7)
        {
            if (virtual_area[virtual_position_object_nr + RIGHT * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + RIGHT * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + RIGHT * i].column == 8)
            break;
    }
}

void virtualBlackTopLeftSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].row == 1 || virtual_area[virtual_position_object_nr].column == 1)
            break;
        if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].big_figure == "whiteKing")
            {
                if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].row != 1 && virtual_area[virtual_position_object_nr + TOP_LEFT * i].column != 1 && virtual_area[virtual_position_object_nr + TOP_LEFT * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + TOP_LEFT * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + TOP_LEFT * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].figure_color == WHITE)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + TOP_LEFT * (i + k)].row == 1 && virtual_area[virtual_position_object_nr + TOP_LEFT * (i + k)].column == 1 && virtual_area[virtual_position_object_nr + TOP_LEFT * (i + k)].big_figure != "whiteKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + TOP_LEFT * (i + k)].big_figure != "whiteKing")
                    {
                        if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + TOP_LEFT * (i + k)].big_figure == "whiteKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + TOP_LEFT * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr >= 9)
        {
            if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + TOP_LEFT * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + TOP_LEFT * i].row == 1 || virtual_area[virtual_position_object_nr + TOP_LEFT * i].column == 1)
            break;
    }
}

void virtualBlackTopRightSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].row == 1 || virtual_area[virtual_position_object_nr].column == 8)
            break;
        if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].big_figure == "whiteKing")
            {
                if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].row != 1 && virtual_area[virtual_position_object_nr + TOP_RIGHT * i].column != 8 && virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + TOP_RIGHT * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].figure_color == WHITE)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + k)].row == 1 && virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + k)].column == 8 && virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + k)].big_figure != "whiteKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + k)].big_figure != "whiteKing")
                    {
                        if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + TOP_RIGHT * (i + k)].big_figure == "whiteKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + TOP_RIGHT * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + TOP_RIGHT * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + TOP_RIGHT * i].row == 1 || virtual_area[virtual_position_object_nr + TOP_RIGHT * i].column == 8)
            break;
    }
}

void virtualBlackBottomLeftSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].row == 8 || virtual_area[virtual_position_object_nr].column == 1)
            break;
        if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].big_figure == "whiteKing")
            {
                if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].row != 8 && virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].column != 1 && virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + BOTTOM_LEFT * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].figure_color == WHITE)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + k)].row == 8 && virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + k)].column == 1 && virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + k)].big_figure != "whiteKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + k)].big_figure != "whiteKing")
                    {
                        if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * (i + k)].big_figure == "whiteKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + BOTTOM_LEFT * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].row == 8 || virtual_area[virtual_position_object_nr + BOTTOM_LEFT * i].column == 1)
            break;
    }
}

void virtualBlackBottomRightSide()
{
    bool stop = false;
    for (int i = 1; i <= 8; i++)
    {
        if (virtual_area[virtual_position_object_nr].row == 8 || virtual_area[virtual_position_object_nr].column == 8)
            break;
        if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].figure_color != EMPTY)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].big_figure == "whiteKing")
            {
                if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].row != 8 && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].column != 8 && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + 1)].figure_color == EMPTY)
                    virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + 1)].bg_color = YELLOW_2;

                for (int j = i; j >= 1; j--)
                {
                    virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * j].bg_color = GREEN;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != YELLOW)
                    virtual_area[virtual_position_object_nr].bg_color = GREEN;
                virtual_area[virtual_position_object_nr].checking = true;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].figure_color == WHITE)
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + k)].row == 8 && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + k)].column == 8 && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + k)].big_figure != "whiteKing")
                    {
                        stop = true;
                        break;
                    }
                    else if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + k)].big_figure != "whiteKing")
                    {
                        if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color != YELLOW && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color != GREEN && virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color != PURPLE)
                        {
                            virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color = RED;
                            stop = true;
                            break;
                        }
                        else
                        {
                            stop = true;
                            break;
                        }
                    }
                    else if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * (i + k)].big_figure == "whiteKing")
                    {
                        for (int j = (i + k - 1); j >= 1; j--)
                        {
                            virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * j].bg_color = PURPLE;
                        }
                        virtual_area[virtual_position_object_nr].bg_color = PURPLE;
                        stop = true;
                        break;
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color != PURPLE)
            {
                virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color = YELLOW;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr <= 54)
        {
            if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color != PURPLE)
                virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].bg_color = RED;
        }
        if (virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].row == 8 || virtual_area[virtual_position_object_nr + BOTTOM_RIGHT * i].column == 8)
            break;
    }
}

// TEXT COLORS

void textColorStandard()
{
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void textColorBlue()
{
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void textColorRed()
{
    SetConsoleTextAttribute(hOut, FOREGROUND_RED);
}

void textColorYellow()
{
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
}

void textColorGreen()
{
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
}

// AREA COLORS

void bgColorAquaTextColorWhite()
{
    SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
}
void bgColorAquaTextColorBlack()
{
    SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
}

void bgColorBlueTextColorWhite()
{
    SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
}
void bgColorBlueTextColorBlack()
{
    SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
}

// CHECKING MOVE COLORS

void bgcolorGreen_colorWhite()
{
    SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
}
void bgcolorGreen_colorBlack()
{
    SetConsoleTextAttribute(hOut, BACKGROUND_RED);
}

void bgcolorRed_colorWhite()
{
    SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
}
void bgcolorRed_colorBlack()
{
    SetConsoleTextAttribute(hOut, BACKGROUND_RED);
}

void bgcolorPurple_colorWhite()
{
    SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
}
void bgcolorPurple_colorBlack()
{
    SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE);
}
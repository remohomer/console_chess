#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include "figures.h"

using namespace std;

void mainMenu();
void newGame();
void resumeGame();
void rematch();
void howToPlay();
void gamesStory();

void gamePlay();
void resetArea();
void resetAreaColors();
void resetVirtualAreaColors(); // virtual
void resetCastling();
void refreshArea();
void refreshVirtualArea(); // virtual

void whiteKingCheck();
void blackKingCheck();

void checkingMoveFigures();
void moveFigures();
void moveFigures_VirtualArea(); // virtual
void whoWins();

// --------------- DEV TOOLS --------------- //

void refreshAreaID();
void refreshAreaPosition();
void refreshAreaNR();
void showAreaStats();
void showBools();

// --------------- PAINT COLORS --------------- //

void paintAreaColors();
void paintAreaColorsPawn();   // pawn
void paintAreaColorsKnight(); // knight
void paintAreaColorsBishop(); // bishop
void paintAreaColorsRook();   // rook
void paintAreaColorsQueen();  // queen
void paintAreaColorsKing();   // king

void pawnTopSide();          // pawn top
void pawnTopTopSide();       // pawn top top
void pawnTopLeftSide();      // pawn top left
void pawnTopRigtSide();      // pawn top right
void pawnBottomSide();       // pawn bottom
void pawnBottomBottomSide(); // pawn bottom bottom
void pawnBottomLeftSide();   // pawn bottom left
void pawnBottomRigtSide();   // pawn bottom right

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

void bgColorAquaTextColorWhite();
void bgColorAquaTextColorBlack();
void bgColorBlueTextColorWhite();
void bgColorBlueTextColorBlack();

// --------------- GLOBAL VARIABLES --------------- //

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

HANDLE hOut;

// --------------- GLOBAL OBJECTS --------------- //

Area area[64]{
    {"a8", 1, 1, 0, 'B', 'W', "blackLeftRook", 1},
    {"b8", 1, 2, 1, 'B', 'S', "blackLeftKnight", 2},
    {"c8", 1, 3, 0, 'B', 'G', "blackDarkBishop", 3},
    {"d8", 1, 4, 1, 'B', 'H', "blackQueen", 4},
    {"e8", 1, 5, 0, 'B', 'K', "blackKing", 5},
    {"f8", 1, 6, 1, 'B', 'G', "blackLightBishop", 6},
    {"g8", 1, 7, 0, 'B', 'S', "blackRightKnight", 7},
    {"h8", 1, 8, 1, 'B', 'W', "blackRightRook", 8},
    {"a7", 2, 1, 1, 'B', 'P', "blackPawn1", 9},
    {"b7", 2, 2, 0, 'B', 'P', "blackPawn2", 10},
    {"c7", 2, 3, 1, 'B', 'P', "blackPawn3", 11},
    {"d7", 2, 4, 0, 'B', 'P', "blackPawn4", 12},
    {"e7", 2, 5, 1, 'B', 'P', "blackPawn5", 13},
    {"f7", 2, 6, 0, 'B', 'P', "blackPawn6", 14},
    {"g7", 2, 7, 1, 'B', 'P', "blackPawn7", 15},
    {"h7", 2, 8, 0, 'B', 'P', "blackPawn8", 16},
    {"a6", 3, 1, 0, 'E', ' ', "", 17},
    {"b6", 3, 2, 1, 'E', ' ', "", 18},
    {"c6", 3, 3, 0, 'E', ' ', "", 19},
    {"d6", 3, 4, 1, 'E', ' ', "", 20},
    {"e6", 3, 5, 0, 'E', ' ', "", 21},
    {"f6", 3, 6, 1, 'E', ' ', "", 22},
    {"g6", 3, 7, 0, 'E', ' ', "", 23},
    {"h6", 3, 8, 1, 'E', ' ', "", 24},
    {"a5", 4, 1, 1, 'E', ' ', "", 25},
    {"b5", 4, 2, 0, 'E', ' ', "", 26},
    {"c5", 4, 3, 1, 'E', ' ', "", 27},
    {"d5", 4, 4, 0, 'E', ' ', "", 28},
    {"e5", 4, 5, 1, 'E', ' ', "", 29},
    {"f5", 4, 6, 0, 'E', ' ', "", 30},
    {"g5", 4, 7, 1, 'E', ' ', "", 31},
    {"h5", 4, 8, 0, 'E', ' ', "", 32},
    {"a4", 5, 1, 0, 'E', ' ', "", 33},
    {"b4", 5, 2, 1, 'E', ' ', "", 34},
    {"c4", 5, 3, 0, 'E', ' ', "", 35},
    {"d4", 5, 4, 1, 'E', ' ', "", 36},
    {"e4", 5, 5, 0, 'E', ' ', "", 37},
    {"f4", 5, 6, 1, 'E', ' ', "", 38},
    {"g4", 5, 7, 0, 'E', ' ', "", 39},
    {"h4", 5, 8, 1, 'E', ' ', "", 40},
    {"a3", 6, 1, 1, 'E', ' ', "", 41},
    {"b3", 6, 2, 0, 'E', ' ', "", 42},
    {"c3", 6, 3, 1, 'E', ' ', "", 43},
    {"d3", 6, 4, 0, 'E', ' ', "", 44},
    {"e3", 6, 5, 1, 'E', ' ', "", 45},
    {"f3", 6, 6, 0, 'E', ' ', "", 46},
    {"g3", 6, 7, 1, 'E', ' ', "", 47},
    {"h3", 6, 8, 0, 'E', ' ', "", 48},
    {"a2", 7, 1, 0, 'W', 'P', "whitePawn1", 49},
    {"b2", 7, 2, 1, 'W', 'P', "whitePawn2", 50},
    {"c2", 7, 3, 0, 'W', 'P', "whitePawn3", 51},
    {"d2", 7, 4, 1, 'W', 'P', "whitePawn4", 52},
    {"e2", 7, 5, 0, 'W', 'P', "whitePawn5", 53},
    {"f2", 7, 6, 1, 'W', 'P', "whitePawn6", 54},
    {"g2", 7, 7, 0, 'W', 'P', "whitePawn7", 55},
    {"h2", 7, 8, 1, 'W', 'P', "whitePawn8", 56},
    {"a1", 8, 1, 1, 'W', 'W', "whiteLeftRook", 57},
    {"b1", 8, 2, 0, 'W', 'S', "whiteLeftKnight", 58},
    {"c1", 8, 3, 1, 'W', 'G', "whiteLightBishop", 59},
    {"d1", 8, 4, 0, 'W', 'H', "whiteQueen", 60},
    {"e1", 8, 5, 1, 'W', 'K', "whiteKing", 61},
    {"f1", 8, 6, 0, 'W', 'G', "whiteDarkBishop", 62},
    {"g1", 8, 7, 1, 'W', 'S', "whiteRightKnight", 63},
    {"h1", 8, 8, 0, 'W', 'W', "whiteRightRook", 64}};

Area virtual_area[64]{
    {"a8", 1, 1, 0, 'B', 'W', "blackLeftRook", 1},
    {"b8", 1, 2, 1, 'B', 'S', "blackLeftKnight", 2},
    {"c8", 1, 3, 0, 'B', 'G', "blackDarkBishop", 3},
    {"d8", 1, 4, 1, 'B', 'H', "blackQueen", 4},
    {"e8", 1, 5, 0, 'B', 'K', "blackKing", 5},
    {"f8", 1, 6, 1, 'B', 'G', "blackLightBishop", 6},
    {"g8", 1, 7, 0, 'B', 'S', "blackRightKnight", 7},
    {"h8", 1, 8, 1, 'B', 'W', "blackRightRook", 8},
    {"a7", 2, 1, 1, 'B', 'P', "blackPawn1", 9},
    {"b7", 2, 2, 0, 'B', 'P', "blackPawn2", 10},
    {"c7", 2, 3, 1, 'B', 'P', "blackPawn3", 11},
    {"d7", 2, 4, 0, 'B', 'P', "blackPawn4", 12},
    {"e7", 2, 5, 1, 'B', 'P', "blackPawn5", 13},
    {"f7", 2, 6, 0, 'B', 'P', "blackPawn6", 14},
    {"g7", 2, 7, 1, 'B', 'P', "blackPawn7", 15},
    {"h7", 2, 8, 0, 'B', 'P', "blackPawn8", 16},
    {"a6", 3, 1, 0, 'E', ' ', "", 17},
    {"b6", 3, 2, 1, 'E', ' ', "", 18},
    {"c6", 3, 3, 0, 'E', ' ', "", 19},
    {"d6", 3, 4, 1, 'E', ' ', "", 20},
    {"e6", 3, 5, 0, 'E', ' ', "", 21},
    {"f6", 3, 6, 1, 'E', ' ', "", 22},
    {"g6", 3, 7, 0, 'E', ' ', "", 23},
    {"h6", 3, 8, 1, 'E', ' ', "", 24},
    {"a5", 4, 1, 1, 'E', ' ', "", 25},
    {"b5", 4, 2, 0, 'E', ' ', "", 26},
    {"c5", 4, 3, 1, 'E', ' ', "", 27},
    {"d5", 4, 4, 0, 'E', ' ', "", 28},
    {"e5", 4, 5, 1, 'E', ' ', "", 29},
    {"f5", 4, 6, 0, 'E', ' ', "", 30},
    {"g5", 4, 7, 1, 'E', ' ', "", 31},
    {"h5", 4, 8, 0, 'E', ' ', "", 32},
    {"a4", 5, 1, 0, 'E', ' ', "", 33},
    {"b4", 5, 2, 1, 'E', ' ', "", 34},
    {"c4", 5, 3, 0, 'E', ' ', "", 35},
    {"d4", 5, 4, 1, 'E', ' ', "", 36},
    {"e4", 5, 5, 0, 'E', ' ', "", 37},
    {"f4", 5, 6, 1, 'E', ' ', "", 38},
    {"g4", 5, 7, 0, 'E', ' ', "", 39},
    {"h4", 5, 8, 1, 'E', ' ', "", 40},
    {"a3", 6, 1, 1, 'E', ' ', "", 41},
    {"b3", 6, 2, 0, 'E', ' ', "", 42},
    {"c3", 6, 3, 1, 'E', ' ', "", 43},
    {"d3", 6, 4, 0, 'E', ' ', "", 44},
    {"e3", 6, 5, 1, 'E', ' ', "", 45},
    {"f3", 6, 6, 0, 'E', ' ', "", 46},
    {"g3", 6, 7, 1, 'E', ' ', "", 47},
    {"h3", 6, 8, 0, 'E', ' ', "", 48},
    {"a2", 7, 1, 0, 'W', 'P', "whitePawn1", 49},
    {"b2", 7, 2, 1, 'W', 'P', "whitePawn2", 50},
    {"c2", 7, 3, 0, 'W', 'P', "whitePawn3", 51},
    {"d2", 7, 4, 1, 'W', 'P', "whitePawn4", 52},
    {"e2", 7, 5, 0, 'W', 'P', "whitePawn5", 53},
    {"f2", 7, 6, 1, 'W', 'P', "whitePawn6", 54},
    {"g2", 7, 7, 0, 'W', 'P', "whitePawn7", 55},
    {"h2", 7, 8, 1, 'W', 'P', "whitePawn8", 56},
    {"a1", 8, 1, 1, 'W', 'W', "whiteLeftRook", 57},
    {"b1", 8, 2, 0, 'W', 'S', "whiteLeftKnight", 58},
    {"c1", 8, 3, 1, 'W', 'G', "whiteLightBishop", 59},
    {"d1", 8, 4, 0, 'W', 'H', "whiteQueen", 60},
    {"e1", 8, 5, 1, 'W', 'K', "whiteKing", 61},
    {"f1", 8, 6, 0, 'W', 'G', "whiteDarkBishop", 62},
    {"g1", 8, 7, 1, 'W', 'S', "whiteRightKnight", 63},
    {"h1", 8, 8, 0, 'W', 'W', "whiteRightRook", 64}};

int main()
{
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    mainMenu();
    return 0;
}

void mainMenu()
{
    string choice{};

    do
    {
        system("cls");

        textColorStandard();
        cout << "1. NOWA GRA\n";

        if (winner == 'P')
        {
            textColorYellow();
            cout << "2. WZNOW GRE\n";
            textColorStandard();
        }
        else if (winner == 'E')
        {
            textColorBlue();
            cout << "2. REWANZ\n";
            textColorStandard();
        }
        else
        {
            textColorRed();
            cout << "2. REWANZ\n";
            textColorStandard();
        }

        cout << "3. JAK GRAC\n";
        cout << "4. HISTORIA GIER\n";
        cout << "5. WYJSCIE\n\n";
        textColorYellow();
        cout << "Twoj wybor: ";
        textColorRed();
        cin >> choice;
        textColorStandard();

        if (choice == "1")
        {
            newGame();
        }
        else if (choice == "2")
        {
            if (winner == 'P')
                resumeGame();
            else if (winner == 'E')
                rematch();
            else
            {
                textColorRed();
                cout << "\nMusisz najpierw rozegrac gre by uzyc tej opcji . . .";
                textColorStandard();
                Sleep(1500);
            }
        }
        else if (choice == "3")
        {
            howToPlay();
        }
        else if (choice == "4")
        {
            gamesStory();
        }
        else if (choice == "5")
        {
            cout << "Dziekuje za gre i zapraszam ponownie . . .";
            Sleep(1500);
        }
        else
        {
            textColorRed();
            cout << "\nBledny wybor! Sprobuj jeszcze raz . . .";
            textColorStandard();
            Sleep(1500);
        }
    } while (choice != "5");
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
    cout << "Poruszanie sie figurami po szachownicy odbywa sie\nza pomoca komend slownych.\n\n";
    textColorStandard();
    cout << "W pozycji";
    textColorRed();
    cout << " \"Ktora figure poruszyc\" ";
    textColorStandard();
    cout << "nalezy wpisac\npolozenie na szachownicy figury, ktora chcemy \nzlapac (np.";
    textColorYellow();
    cout << " e2 ";
    textColorStandard();
    cout << ").\n\nNastepnie w pozycji";
    textColorRed();
    cout << " \"Gdzie postawic figure\" ";
    textColorStandard();
    cout << "nalezy\nwpisac polozenie na szachownicy, na ktora chcemy \nprzesunac figure (np.";
    textColorYellow();
    cout << " e4 ";
    textColorStandard();
    cout << ").\n\nAby zmienic juz wybrana figure na inna wpisz\nkomende";
    textColorYellow();
    cout << " again ";

    if (active_game == false)
    {
        textColorStandard();
        cout << "\n\n\nWcisnij ENTER by wrocic do Menu Glownego . . .";
        getchar();
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
void gamesStory()
{
    system("cls");
    textColorYellow();
    cout << "Poki co nie ma historii gier...\nWybacz!";
    textColorStandard();
    cout << "\n\nWcisnij ENTER by wrocic do Menu Glownego . . .";
    getchar();
    getchar();
}

void gamePlay()
{
    winner = ' ';
    active_game = true;
    resetAreaColors();
    resetVirtualAreaColors();

    refreshArea();

    while (winner == ' ')
    {
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

        checkingMoveFigures();
        if (winner != 'E' && winner != 'P')
        {
            moveFigures();
            moveFigures_VirtualArea();
        }
    }

    whoWins();
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
    cout << "\nhow";
    textColorStandard();
    cout << "\tjak grac?";

    textColorRed();
    cout << "\nagain";
    textColorStandard();
    cout << "\twybierz inna figure";

    textColorRed();
    cout << "\npause";
    textColorStandard();
    cout << "\twstrzymaj gre";

    textColorRed();
    cout << "\nexit";
    textColorStandard();
    cout << "\twyjdz z gry";

    textColorYellow();
    cout << "\n\nDEV COMMANDS: ";

    textColorRed();
    cout << "\nshowb";
    textColorStandard();
    cout << "\twyswietla zawartosc zmiennych typu 'bool'";

    textColorRed();
    cout << "\nshowv";
    textColorStandard();
    cout << "\twyswietla podglad virtualnej szachownicy";

    textColorStandard();
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

void refreshAreaID()
{
    system("cls");

    int nr = 1;

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
    cout << endl;
    int nr = 8;

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

    cout << endl;
    int nr = 8;

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
        if (virtual_area[j].big_figure == "whiteKing" && virtual_area[j].bg_color == 3)
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
        if (virtual_area[j].big_figure == "blackKing" && virtual_area[j].bg_color == 3)
        {
            black_king_check = true;
            break;
        }
        black_king_check = false;
    }
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

        if (old_position == "pause" || old_position == "PAUSE")
        {
            winner = 'P';
            check = "pause";
        }

        else if (old_position == "exit" || old_position == "EXIT")
        {
            winner = 'E';
            check = "exit";
            active_game = false;
        }

        else if (old_position == "again" || old_position == "AGAIN")
        {
            check = "again";
            textColorRed();
            cout << "\nJeszcze nie wybrales figury!";
            textColorStandard();
            Sleep(1500);
            refreshArea();
        }

        else if (old_position == "how" || old_position == "HOW")
        {
            winner = 'P';
            check = "how";
            howToPlay();
        }

        else if (old_position == "showb" || old_position == "SHOWB")
        {
            showBools();
            system("pause");
            refreshArea();
            check = "again";
        }

        else if (old_position == "showv" || old_position == "SHOWV")
        {
            system("cls");
            refreshVirtualArea();
            cout << endl;
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
                    if (whith_player % 2 == 0 && area[i].figure_color == 'B' || whith_player % 2 == 1 && area[i].figure_color == 'W')
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
                        /////////////////////////////////////// PRAWIDLOWO WYBRANA STARA POZYCJA ///////////////////////////////////////

                        old_position_object_nr = i;
                        paintAreaColors();
                        area[old_position_object_nr].bg_color = 2;
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
        if (check == "pause" || old_position == "PAUSE" || old_position == "exit" || old_position == "EXIT" || old_position == "how" || old_position == "HOW")
        {
            break;
        }
        else
        {
            textColorYellow();
            cout << "\n\nGdzie postawic figure? ";
            textColorRed();
            cin >> new_position;

            if (new_position == "again" || new_position == "AGAIN")
            {
                resetAreaColors();
                checkingMoveFigures();
                check = "pass";
            }

            else if (new_position == "how" || old_position == "HOW")
            {
                winner = 'P';
                check = "how";
                howToPlay();
            }

            else if (new_position == "pause" || old_position == "PAUSE")
            {
                winner = 'P';
                check = "pause";
            }

            else if (new_position == "exit" || old_position == "EXIT")
            {
                winner = 'E';
                check = "exit";
            }

            else if (old_position == "showb" || old_position == "SHOWB")
            {
                showBools();
                system("pause");
                refreshArea();
                check = "again";
            }

            else if (old_position == "showv" || old_position == "SHOWV")
            {
                system("cls");
                refreshVirtualArea();
                cout << endl;
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
                        if (whith_player % 2 == 0 && area[i].figure_color == 'W' || whith_player % 2 == 1 && area[i].figure_color == 'B')
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
                            /////////////////////////////////////// PRAWIDLOWO WYBRANA NOWA POZYCJA ///////////////////////////////////////
                            new_position_object_nr = i;

                            if (area[i].bg_color == 3 || area[i].bg_color == 4)
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
    char temp_figure_color{'E'};

    // PROMOTION WHITE PAWNS
    if (area[old_position_object_nr].figure == 'P' && area[old_position_object_nr].figure_color == 'W' && area[new_position_object_nr].row == 1)
    {
        area[old_position_object_nr].big_figure = "";
        area[old_position_object_nr].figure = ' ';
        area[old_position_object_nr].figure_color = 'E';
        area[new_position_object_nr].figure = '?';
        area[new_position_object_nr].figure_color = 'W';
        area[new_position_object_nr].bg_color = 2;

        bool white_promoted_choise = true;

        do
        {
            refreshArea();
            string promotion_figure{""};
            textColorYellow();
            cout << "\n\n Na jaka figure promowac Pionka?: ";
            textColorRed();
            cin >> promotion_figure;
            textColorStandard();

            if (promotion_figure == "H" || promotion_figure == "Hetman" || promotion_figure == "Q" || promotion_figure == "Queen" || promotion_figure == "D" || promotion_figure == "Dama" || promotion_figure == "Damka")
            {
                area[new_position_object_nr].big_figure = "whitePromotedQueen";
                area[new_position_object_nr].figure = 'H';
                area[new_position_object_nr].figure_color = 'W';
                white_promoted_choise = true;
            }

            else if (promotion_figure == "W" || promotion_figure == "Wieza" || promotion_figure == "R" || promotion_figure == "Rook")
            {
                area[new_position_object_nr].big_figure = "whitePromotedRook";
                area[new_position_object_nr].figure = 'W';
                area[new_position_object_nr].figure_color = 'W';
                white_promoted_choise = true;
            }

            else if (promotion_figure == "G" || promotion_figure == "Goniec" || promotion_figure == "B" || promotion_figure == "Bishop" || promotion_figure == "L" || promotion_figure == "Laufer")
            {
                area[new_position_object_nr].big_figure = "whitePromotedBishop";
                area[new_position_object_nr].figure = 'G';
                area[new_position_object_nr].figure_color = 'W';
                white_promoted_choise = true;
            }

            else if (promotion_figure == "S" || promotion_figure == "Skoczek" || promotion_figure == "K" || promotion_figure == "Knight" || promotion_figure == "K" || promotion_figure == "Kon" || promotion_figure == "Konik")
            {
                area[new_position_object_nr].big_figure = "whitePromotedKnight";
                area[new_position_object_nr].figure = 'S';
                area[new_position_object_nr].figure_color = 'W';
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
    else if (area[old_position_object_nr].figure == 'P' && area[old_position_object_nr].figure_color == 'B' && area[new_position_object_nr].row == 8)
    {
        area[old_position_object_nr].big_figure = "";
        area[old_position_object_nr].figure = ' ';
        area[old_position_object_nr].figure_color = 'E';
        area[new_position_object_nr].figure = '?';
        area[new_position_object_nr].figure_color = 'B';
        area[new_position_object_nr].bg_color = 2;

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

            if (promotion_figure == "H" || promotion_figure == "Hetman" || promotion_figure == "Q" || promotion_figure == "Queen" || promotion_figure == "D" || promotion_figure == "Dama" || promotion_figure == "Damka")
            {
                area[new_position_object_nr].big_figure = "blackPromotedQueen";
                area[new_position_object_nr].figure = 'H';
                area[new_position_object_nr].figure_color = 'B';
                black_promoted_choise = true;
            }

            else if (promotion_figure == "W" || promotion_figure == "Wieza" || promotion_figure == "R" || promotion_figure == "Rook")
            {
                area[new_position_object_nr].big_figure = "blackPromotedRook";
                area[new_position_object_nr].figure = 'W';
                area[new_position_object_nr].figure_color = 'B';
                black_promoted_choise = true;
            }

            else if (promotion_figure == "G" || promotion_figure == "Goniec" || promotion_figure == "B" || promotion_figure == "Bishop" || promotion_figure == "L" || promotion_figure == "Laufer")
            {
                area[new_position_object_nr].big_figure = "blackPromotedBishop";
                area[new_position_object_nr].figure = 'G';
                area[new_position_object_nr].figure_color = 'B';
                black_promoted_choise = true;
            }

            else if (promotion_figure == "S" || promotion_figure == "Skoczek" || promotion_figure == "K" || promotion_figure == "Knight" || promotion_figure == "K" || promotion_figure == "Kon" || promotion_figure == "Konik")
            {
                area[new_position_object_nr].big_figure = "blackPromotedKnight";
                area[new_position_object_nr].figure = 'S';
                area[new_position_object_nr].figure_color = 'B';
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
        area[58].big_figure = "whiteKing";
        area[58].figure = 'K';
        area[58].figure_color = 'W';
        area[60].big_figure = "";
        area[60].figure = ' ';
        area[60].figure_color = 'E';

        area[59].big_figure = "whiteLeftRook";
        area[59].figure = 'W';
        area[59].figure_color = 'W';
        area[56].big_figure = "";
        area[56].figure = ' ';
        area[56].figure_color = 'E';

        active_white_left_castling = false;
        active_white_right_castling = false;
    }

    // WHITE - KING SIDE CASTLING
    else if (area[old_position_object_nr].big_figure == "whiteKing" && area[new_position_object_nr].position == "g1" && active_white_right_castling == true)
    {
        area[62].big_figure = "whiteKing";
        area[62].figure = 'K';
        area[62].figure_color = 'W';
        area[60].big_figure = "";
        area[60].figure = ' ';
        area[60].figure_color = 'E';

        area[61].big_figure = "whiteRightRook";
        area[61].figure = 'W';
        area[61].figure_color = 'W';
        area[63].big_figure = "";
        area[63].figure = ' ';
        area[63].figure_color = 'E';

        active_white_left_castling = false;
        active_white_right_castling = false;
    }

    // BLACK - QUEEN SIDE CASTLING
    else if (area[old_position_object_nr].big_figure == "blackKing" && area[new_position_object_nr].position == "c8" && active_black_left_castling == true)
    {
        area[2].big_figure = "blackKing";
        area[2].figure = 'K';
        area[2].figure_color = 'B';
        area[4].big_figure = "";
        area[4].figure = ' ';
        area[4].figure_color = 'E';

        area[3].big_figure = "blackLeftRook";
        area[3].figure = 'W';
        area[3].figure_color = 'B';
        area[9].big_figure = "";
        area[9].figure = ' ';
        area[9].figure_color = 'E';

        active_black_left_castling = false;
        active_black_right_castling = false;
    }

    // BLACK - KING SIDE CASTLING
    else if (area[old_position_object_nr].big_figure == "blackKing" && area[new_position_object_nr].position == "g8" && active_black_right_castling == true)
    {
        area[6].big_figure = "blackKing";
        area[6].figure = 'K';
        area[6].figure_color = 'B';
        area[4].big_figure = "";
        area[4].figure = ' ';
        area[4].figure_color = 'E';

        area[5].big_figure = "blackRightRook";
        area[5].figure = 'W';
        area[5].figure_color = 'B';
        area[7].big_figure = "";
        area[7].figure = ' ';
        area[7].figure_color = 'E';

        active_black_left_castling = false;
        active_black_right_castling = false;
    }

    else
    {
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

        temp_big_figure = area[old_position_object_nr].big_figure;
        temp_figure = area[old_position_object_nr].figure;
        temp_figure_color = area[old_position_object_nr].figure_color;
        area[old_position_object_nr].big_figure = "";
        area[old_position_object_nr].figure = ' ';
        area[old_position_object_nr].figure_color = 'E';

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

    if (winner == '1')
    {
        textColorYellow();
        cout << "\n\nWygral: ";
        bgColorBlueTextColorWhite();
        cout << player_1;
    }
    else if (winner == '2')
    {
        textColorYellow();
        cout << "\n\nWygral: ";
        bgColorBlueTextColorWhite();
        cout << player_2;
    }
    else if (winner == 'R')
    {
        textColorYellow();
        cout << "\n\nREMIS!";
    }

    if (winner == '1' || winner == '2' || winner == '3')
    {
        active_game = false;
        textColorStandard();
        cout << "\n\nWcisnij ENTER by wrocic do menu glownego . . .";
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

void paintAreaColors()
{
    if (area[old_position_object_nr].figure == 'P')
        paintAreaColorsPawn();
    else if (area[old_position_object_nr].figure == 'S')
        paintAreaColorsKnight();
    else if (area[old_position_object_nr].figure == 'G')
        paintAreaColorsBishop();
    else if (area[old_position_object_nr].figure == 'W')
        paintAreaColorsRook();
    else if (area[old_position_object_nr].figure == 'H')
        paintAreaColorsQueen();
    else if (area[old_position_object_nr].figure == 'K')
        paintAreaColorsKing();
}

void paintAreaColorsPawn()
{
    ///////////////// WHITE /////////////////
    if (area[old_position_object_nr].figure_color == 'W')
    {
        if (area[old_position_object_nr].row == 7)
        {
            pawnTopSide();
            pawnTopTopSide();
            pawnTopLeftSide();
            pawnTopRigtSide();
        }
        else
        {
            pawnTopSide();
            pawnTopLeftSide();
            pawnTopRigtSide();
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
        }
        else
        {
            pawnBottomSide();
            pawnBottomLeftSide();
            pawnBottomRigtSide();
        }
    }
}
void paintAreaColorsKnight()
{

    ///////////////// WHITE /////////////////
    if (area[old_position_object_nr].figure_color == 'W')
    {

        // TOP TOP LEFT
        if (old_position_object_nr >= 17)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr - 17].figure_color == 'B' && area[old_position_object_nr - 17].bg_color == 3)
                        area[old_position_object_nr - 17].bg_color = 4;
                    else if (area[old_position_object_nr - 17].figure_color == 'E' && area[old_position_object_nr - 17].bg_color == 3)
                        area[old_position_object_nr - 17].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr - 17].figure_color == 'B')
                        area[old_position_object_nr - 17].bg_color = 4;
                    else if (area[old_position_object_nr - 17].figure_color == 'E')
                        area[old_position_object_nr - 17].bg_color = 3;
                }
            }
        }

        // TOP TOP RIGHT
        if (old_position_object_nr >= 16)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr - 15].figure_color == 'B' && area[old_position_object_nr - 15].bg_color == 3)
                        area[old_position_object_nr - 15].bg_color = 4;
                    else if (area[old_position_object_nr - 15].figure_color == 'E' && area[old_position_object_nr - 15].bg_color == 3)
                        area[old_position_object_nr - 15].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 7)
                {
                    if (area[old_position_object_nr - 15].figure_color == 'B')
                        area[old_position_object_nr - 15].bg_color = 4;
                    else if (area[old_position_object_nr - 15].figure_color == 'E')
                        area[old_position_object_nr - 15].bg_color = 3;
                }
            }
        }

        // BOTTOM BOTTOM LEFT
        if (old_position_object_nr <= 47)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + 15].figure_color == 'B' && area[old_position_object_nr + 15].bg_color == 3)
                        area[old_position_object_nr + 15].bg_color = 4;
                    else if (area[old_position_object_nr + 15].figure_color == 'E' && area[old_position_object_nr + 15].bg_color == 3)
                        area[old_position_object_nr + 15].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + 15].figure_color == 'B')
                        area[old_position_object_nr + 15].bg_color = 4;
                    else if (area[old_position_object_nr + 15].figure_color == 'E')
                        area[old_position_object_nr + 15].bg_color = 3;
                }
            }
        }

        // BOTTOM BOTTOM RIGHT
        if (old_position_object_nr <= 46)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + 17].figure_color == 'B' && area[old_position_object_nr + 17].bg_color == 3)
                        area[old_position_object_nr + 17].bg_color = 4;
                    else if (area[old_position_object_nr + 17].figure_color == 'E' && area[old_position_object_nr + 17].bg_color == 3)
                        area[old_position_object_nr + 17].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 7)
                {
                    if (area[old_position_object_nr + 17].figure_color == 'B')
                        area[old_position_object_nr + 17].bg_color = 4;
                    else if (area[old_position_object_nr + 17].figure_color == 'E')
                        area[old_position_object_nr + 17].bg_color = 3;
                }
            }
        }

        // LEFT LEFT TOP
        if (old_position_object_nr >= 10)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr - 10].figure_color == 'B' && area[old_position_object_nr - 10].bg_color == 3)
                        area[old_position_object_nr - 10].bg_color = 4;
                    else if (area[old_position_object_nr - 10].figure_color == 'E' && area[old_position_object_nr - 10].bg_color == 3)
                        area[old_position_object_nr - 10].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 3)
                {
                    if (area[old_position_object_nr - 10].figure_color == 'B')
                        area[old_position_object_nr - 10].bg_color = 4;
                    else if (area[old_position_object_nr - 10].figure_color == 'E')
                        area[old_position_object_nr - 10].bg_color = 3;
                }
            }
        }

        // LEFT LEFT BOTTOM
        if (old_position_object_nr <= 55)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + 6].figure_color == 'B' && area[old_position_object_nr + 6].bg_color == 3)
                        area[old_position_object_nr + 6].bg_color = 4;
                    else if (area[old_position_object_nr + 6].figure_color == 'E' && area[old_position_object_nr + 6].bg_color == 3)
                        area[old_position_object_nr + 6].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 3)
                {
                    if (area[old_position_object_nr + 6].figure_color == 'B')
                        area[old_position_object_nr + 6].bg_color = 4;
                    else if (area[old_position_object_nr + 6].figure_color == 'E')
                        area[old_position_object_nr + 6].bg_color = 3;
                }
            }
        }

        // RIGH RIGHT TOP
        if (old_position_object_nr >= 8)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr - 6].figure_color == 'B' && area[old_position_object_nr - 6].bg_color == 3)
                        area[old_position_object_nr - 6].bg_color = 4;
                    else if (area[old_position_object_nr - 6].figure_color == 'E' && area[old_position_object_nr - 6].bg_color == 3)
                        area[old_position_object_nr - 6].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 6)
                {
                    if (area[old_position_object_nr - 6].figure_color == 'B')
                        area[old_position_object_nr - 6].bg_color = 4;
                    else if (area[old_position_object_nr - 6].figure_color == 'E')
                        area[old_position_object_nr - 6].bg_color = 3;
                }
            }
        }

        // RIGH RIGHT BOTTOM
        if (old_position_object_nr <= 53)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (white_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + 10].figure_color == 'B' && area[old_position_object_nr + 10].bg_color == 3)
                        area[old_position_object_nr + 10].bg_color = 4;
                    else if (area[old_position_object_nr + 10].figure_color == 'E' && area[old_position_object_nr + 10].bg_color == 3)
                        area[old_position_object_nr + 10].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 6)
                {
                    if (area[old_position_object_nr + 10].figure_color == 'B')
                        area[old_position_object_nr + 10].bg_color = 4;
                    else if (area[old_position_object_nr + 10].figure_color == 'E')
                        area[old_position_object_nr + 10].bg_color = 3;
                }
            }
        }
    }

    ///////////////// BLACK /////////////////
    if (area[old_position_object_nr].figure_color == 'B')
    {
        // TOP TOP LEFT
        if (old_position_object_nr >= 17)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr - 17].figure_color == 'W' && area[old_position_object_nr - 17].bg_color == 3)
                        area[old_position_object_nr - 17].bg_color = 4;
                    else if (area[old_position_object_nr - 17].figure_color == 'E' && area[old_position_object_nr - 17].bg_color == 3)
                        area[old_position_object_nr - 17].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr - 17].figure_color == 'W')
                        area[old_position_object_nr - 17].bg_color = 4;
                    else if (area[old_position_object_nr - 17].figure_color == 'E')
                        area[old_position_object_nr - 17].bg_color = 3;
                }
            }
        }

        // TOP TOP RIGHT
        if (old_position_object_nr >= 16)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr - 15].figure_color == 'W' && area[old_position_object_nr - 15].bg_color == 3)
                        area[old_position_object_nr - 15].bg_color = 4;
                    else if (area[old_position_object_nr - 15].figure_color == 'E' && area[old_position_object_nr - 15].bg_color == 3)
                        area[old_position_object_nr - 15].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 7)
                {
                    if (area[old_position_object_nr - 15].figure_color == 'W')
                        area[old_position_object_nr - 15].bg_color = 4;
                    else if (area[old_position_object_nr - 15].figure_color == 'E')
                        area[old_position_object_nr - 15].bg_color = 3;
                }
            }
        }

        // BOTTOM BOTTOM LEFT
        if (old_position_object_nr <= 47)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + 15].figure_color == 'W' && area[old_position_object_nr + 15].bg_color == 3)
                        area[old_position_object_nr + 15].bg_color = 4;
                    else if (area[old_position_object_nr + 15].figure_color == 'E' && area[old_position_object_nr + 15].bg_color == 3)
                        area[old_position_object_nr + 15].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + 15].figure_color == 'W')
                        area[old_position_object_nr + 15].bg_color = 4;
                    else if (area[old_position_object_nr + 15].figure_color == 'E')
                        area[old_position_object_nr + 15].bg_color = 3;
                }
            }
        }

        // BOTTOM BOTTOM RIGHT
        if (old_position_object_nr <= 46)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + 17].figure_color == 'W' && area[old_position_object_nr + 17].bg_color == 3)
                        area[old_position_object_nr + 17].bg_color = 4;
                    else if (area[old_position_object_nr + 17].figure_color == 'E' && area[old_position_object_nr + 17].bg_color == 3)
                        area[old_position_object_nr + 17].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 7)
                {
                    if (area[old_position_object_nr + 17].figure_color == 'W')
                        area[old_position_object_nr + 17].bg_color = 4;
                    else if (area[old_position_object_nr + 17].figure_color == 'E')
                        area[old_position_object_nr + 17].bg_color = 3;
                }
            }
        }

        // LEFT LEFT TOP
        if (old_position_object_nr >= 10)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr - 10].figure_color == 'W' && area[old_position_object_nr - 10].bg_color == 3)
                        area[old_position_object_nr - 10].bg_color = 4;
                    else if (area[old_position_object_nr - 10].figure_color == 'E' && area[old_position_object_nr - 10].bg_color == 3)
                        area[old_position_object_nr - 10].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 3)
                {
                    if (area[old_position_object_nr - 10].figure_color == 'W')
                        area[old_position_object_nr - 10].bg_color = 4;
                    else if (area[old_position_object_nr - 10].figure_color == 'E')
                        area[old_position_object_nr - 10].bg_color = 3;
                }
            }
        }

        // LEFT LEFT BOTTOM
        if (old_position_object_nr <= 55)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + 6].figure_color == 'W' && area[old_position_object_nr + 6].bg_color == 3)
                        area[old_position_object_nr + 6].bg_color = 4;
                    else if (area[old_position_object_nr + 6].figure_color == 'E' && area[old_position_object_nr + 6].bg_color == 3)
                        area[old_position_object_nr + 6].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column >= 3)
                {
                    if (area[old_position_object_nr + 6].figure_color == 'W')
                        area[old_position_object_nr + 6].bg_color = 4;
                    else if (area[old_position_object_nr + 6].figure_color == 'E')
                        area[old_position_object_nr + 6].bg_color = 3;
                }
            }
        }

        // RIGH RIGHT TOP
        if (old_position_object_nr >= 8)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr - 6].figure_color == 'W' && area[old_position_object_nr - 6].bg_color == 3)
                        area[old_position_object_nr - 6].bg_color = 4;
                    else if (area[old_position_object_nr - 6].figure_color == 'E' && area[old_position_object_nr - 6].bg_color == 3)
                        area[old_position_object_nr - 6].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 6)
                {
                    if (area[old_position_object_nr - 6].figure_color == 'W')
                        area[old_position_object_nr - 6].bg_color = 4;
                    else if (area[old_position_object_nr - 6].figure_color == 'E')
                        area[old_position_object_nr - 6].bg_color = 3;
                }
            }
        }

        // RIGH RIGHT BOTTOM
        if (old_position_object_nr <= 53)
        {
            if (virtual_area[old_position_object_nr].bg_color == 5);
            else if (black_king_check == true)
            {
                if (area[old_position_object_nr].column >= 2)
                {
                    if (area[old_position_object_nr + 10].figure_color == 'W' && area[old_position_object_nr + 10].bg_color == 3)
                        area[old_position_object_nr + 10].bg_color = 4;
                    else if (area[old_position_object_nr + 10].figure_color == 'E' && area[old_position_object_nr + 10].bg_color == 3)
                        area[old_position_object_nr + 10].bg_color = 3;
                }
            }
            else
            {
                if (area[old_position_object_nr].column <= 6)
                {
                    if (area[old_position_object_nr + 10].figure_color == 'W')
                        area[old_position_object_nr + 10].bg_color = 4;
                    else if (area[old_position_object_nr + 10].figure_color == 'E')
                        area[old_position_object_nr + 10].bg_color = 3;
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
    if (area[old_position_object_nr].figure_color == 'W')
    {
        // TOP SIDE
        if (area[old_position_object_nr].row > 1)
        {
            if (area[old_position_object_nr - 8].figure_color == 'B' && virtual_area[old_position_object_nr - 8].bg_color != 2)
                area[old_position_object_nr - 8].bg_color = 4;
            else if (area[old_position_object_nr - 8].figure_color == 'E' && virtual_area[old_position_object_nr - 8].bg_color != 3 && virtual_area[old_position_object_nr - 8].bg_color != 4)
                area[old_position_object_nr - 8].bg_color = 3;
        }

        // BOTTOM SIDE
        if (area[old_position_object_nr].row < 8)
        {
            if (area[old_position_object_nr + 8].figure_color == 'B' && virtual_area[old_position_object_nr + 8].bg_color != 2)
                area[old_position_object_nr + 8].bg_color = 4;
            else if (area[old_position_object_nr + 8].figure_color == 'E' && virtual_area[old_position_object_nr + 8].bg_color != 3 && virtual_area[old_position_object_nr + 8].bg_color != 4)
                area[old_position_object_nr + 8].bg_color = 3;
        }

        // LEFT SIDE
        if (area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr - 1].figure_color == 'B' && virtual_area[old_position_object_nr - 1].bg_color != 2)
                area[old_position_object_nr - 1].bg_color = 4;
            else if (area[old_position_object_nr - 1].figure_color == 'E' && virtual_area[old_position_object_nr - 1].bg_color != 3 && virtual_area[old_position_object_nr - 1].bg_color != 4)
                area[old_position_object_nr - 1].bg_color = 3;
        }

        // RIGHT SIDE
        if (area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + 1].figure_color == 'B' && virtual_area[old_position_object_nr + 1].bg_color != 2)
                area[old_position_object_nr + 1].bg_color = 4;
            else if (area[old_position_object_nr + 1].figure_color == 'E' && virtual_area[old_position_object_nr + 1].bg_color != 3 && virtual_area[old_position_object_nr + 1].bg_color != 4)
                area[old_position_object_nr + 1].bg_color = 3;
        }

        // TOP LEFT SIDE
        if (area[old_position_object_nr].row > 1 && area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr - 9].figure_color == 'B' && virtual_area[old_position_object_nr - 9].bg_color != 2)
                area[old_position_object_nr - 9].bg_color = 4;
            else if (area[old_position_object_nr - 9].figure_color == 'E' && virtual_area[old_position_object_nr - 9].bg_color != 3 && virtual_area[old_position_object_nr - 9].bg_color != 4)
                area[old_position_object_nr - 9].bg_color = 3;
        }

        // TOP RIGHT SIDE
        if (area[old_position_object_nr].row > 1 && area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr - 7].figure_color == 'B' && virtual_area[old_position_object_nr - 7].bg_color != 2)
                area[old_position_object_nr - 7].bg_color = 4;
            else if (area[old_position_object_nr - 7].figure_color == 'E' && virtual_area[old_position_object_nr - 7].bg_color != 3 && virtual_area[old_position_object_nr - 7].bg_color != 4)
                area[old_position_object_nr - 7].bg_color = 3;
        }

        // BOTTOM LEFT SIDE
        if (area[old_position_object_nr].row < 8 && area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr + 7].figure_color == 'B' && virtual_area[old_position_object_nr + 7].bg_color != 2)
                area[old_position_object_nr + 7].bg_color = 4;
            else if (area[old_position_object_nr + 7].figure_color == 'E' && virtual_area[old_position_object_nr + 7].bg_color != 3 && virtual_area[old_position_object_nr + 7].bg_color != 4)
                area[old_position_object_nr + 7].bg_color = 3;
        }

        // BOTTOM RIGHT SIDE
        if (area[old_position_object_nr].row < 8 && area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + 9].figure_color == 'B' && virtual_area[old_position_object_nr + 9].bg_color != 2)
                area[old_position_object_nr + 9].bg_color = 4;
            else if (area[old_position_object_nr + 9].figure_color == 'E' && virtual_area[old_position_object_nr + 9].bg_color != 3 && virtual_area[old_position_object_nr + 9].bg_color != 4)
                area[old_position_object_nr + 9].bg_color = 3;
        }

        // QUEEN SIDE CASTLING
        if (active_white_left_castling == true && white_king_check == false && virtual_area[58].bg_color != 4 && virtual_area[59].bg_color != 4)
        {
            if (area[58].figure_color == 'E')
                area[58].bg_color = 3;
        }

        // KING SIDE CASTLING
        if (active_white_right_castling == true && white_king_check == false && virtual_area[61].bg_color != 4 && virtual_area[62].bg_color != 4)
        {
            if (area[62].figure_color == 'E')
                area[62].bg_color = 3;
        }
    }

    ///////////////// BLACK /////////////////
    if (area[old_position_object_nr].figure_color == 'B')
    {
        // TOP SIDE
        if (area[old_position_object_nr].row > 1)
        {
            if (area[old_position_object_nr - 8].figure_color == 'W' && virtual_area[old_position_object_nr - 8].bg_color != 2)
                area[old_position_object_nr - 8].bg_color = 4;
            else if (area[old_position_object_nr - 8].figure_color == 'E' && virtual_area[old_position_object_nr - 8].bg_color != 3 && virtual_area[old_position_object_nr - 8].bg_color != 4)
                area[old_position_object_nr - 8].bg_color = 3;
        }

        // BOTTOM SIDE
        if (area[old_position_object_nr].row < 8)
        {
            if (area[old_position_object_nr + 8].figure_color == 'W' && virtual_area[old_position_object_nr + 8].bg_color != 2)
                area[old_position_object_nr + 8].bg_color = 4;
            else if (area[old_position_object_nr + 8].figure_color == 'E' && virtual_area[old_position_object_nr + 8].bg_color != 3 && virtual_area[old_position_object_nr + 8].bg_color != 4)
                area[old_position_object_nr + 8].bg_color = 3;
        }

        // LEFT SIDE
        if (area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr - 1].figure_color == 'W' && virtual_area[old_position_object_nr - 1].bg_color != 2)
                area[old_position_object_nr - 1].bg_color = 4;
            else if (area[old_position_object_nr - 1].figure_color == 'E' && virtual_area[old_position_object_nr - 1].bg_color != 3 && virtual_area[old_position_object_nr - 1].bg_color != 4)
                area[old_position_object_nr - 1].bg_color = 3;
        }

        // RIGHT SIDE
        if (area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + 1].figure_color == 'W' && virtual_area[old_position_object_nr + 1].bg_color != 2)
                area[old_position_object_nr + 1].bg_color = 4;
            else if (area[old_position_object_nr + 1].figure_color == 'E' && virtual_area[old_position_object_nr + 1].bg_color != 3 && virtual_area[old_position_object_nr + 1].bg_color != 4)
                area[old_position_object_nr + 1].bg_color = 3;
        }

        // TOP LEFT SIDE
        if (area[old_position_object_nr].row > 1 && area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr - 9].figure_color == 'W' && virtual_area[old_position_object_nr - 9].bg_color != 2)
                area[old_position_object_nr - 9].bg_color = 4;
            else if (area[old_position_object_nr - 9].figure_color == 'E' && virtual_area[old_position_object_nr - 9].bg_color != 3 && virtual_area[old_position_object_nr - 9].bg_color != 4)
                area[old_position_object_nr - 9].bg_color = 3;
        }

        // TOP RIGHT SIDE
        if (area[old_position_object_nr].row > 1 && area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr - 7].figure_color == 'W' && virtual_area[old_position_object_nr - 7].bg_color != 2)
                area[old_position_object_nr - 7].bg_color = 4;
            else if (area[old_position_object_nr - 7].figure_color == 'E' && virtual_area[old_position_object_nr - 7].bg_color != 3 && virtual_area[old_position_object_nr - 7].bg_color != 4)
                area[old_position_object_nr - 7].bg_color = 3;
        }

        // BOTTOM LEFT SIDE
        if (area[old_position_object_nr].row < 8 && area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr + 7].figure_color == 'W' && virtual_area[old_position_object_nr + 7].bg_color != 2)
                area[old_position_object_nr + 7].bg_color = 4;
            else if (area[old_position_object_nr + 7].figure_color == 'E' && virtual_area[old_position_object_nr + 7].bg_color != 3 && virtual_area[old_position_object_nr + 7].bg_color != 4)
                area[old_position_object_nr + 7].bg_color = 3;
        }

        // BOTTOM RIGHT SIDE
        if (area[old_position_object_nr].row < 8 && area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + 9].figure_color == 'W' && virtual_area[old_position_object_nr + 9].bg_color != 2)
                area[old_position_object_nr + 9].bg_color = 4;
            else if (area[old_position_object_nr + 9].figure_color == 'E' && virtual_area[old_position_object_nr + 9].bg_color != 3 && virtual_area[old_position_object_nr + 9].bg_color != 4)
                area[old_position_object_nr + 9].bg_color = 3;
        }

        // QUEEN SIDE CASTLING
        if (active_black_left_castling == true && white_king_check == false && virtual_area[2].bg_color != 4 && virtual_area[3].bg_color != 4)
        {
            if (area[2].figure_color == 'E')
                area[2].bg_color = 3;
        }

        // KING SIDE CASTLING
        if (active_black_right_castling == true && white_king_check == false && virtual_area[5].bg_color != 4 && virtual_area[6].bg_color != 4)
        {
            if (area[6].figure_color == 'E')
                area[6].bg_color = 3;
        }
    }
}

void pawnTopSide()
{
    if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
    else if (white_king_check == true)
    {
        if (virtual_area[old_position_object_nr - 8].bg_color == 3)
            area[old_position_object_nr - 8].bg_color = 3;
    }
    else if (virtual_area[old_position_object_nr].bg_color == 5)
    {
        if (area[old_position_object_nr - 8].figure_color == 'E' && virtual_area[old_position_object_nr - 8].bg_color == 5)
            area[old_position_object_nr - 8].bg_color = 3;
    }
    else
    {
        if (area[old_position_object_nr - 8].figure_color == 'E')
            area[old_position_object_nr - 8].bg_color = 3;
    }
}
void pawnTopTopSide()
{
    if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
    else if (white_king_check == true)
    {
        if (virtual_area[old_position_object_nr - 16].bg_color == 3)
            area[old_position_object_nr - 16].bg_color = 3;
    }
    else if (virtual_area[old_position_object_nr].bg_color == 5)
    {
        if (area[old_position_object_nr - 16].figure_color == 'E' && virtual_area[old_position_object_nr - 16].bg_color == 5)
            area[old_position_object_nr - 16].bg_color = 3;
    }
    else
    {
        if (area[old_position_object_nr - 16].figure_color == 'E')
            area[old_position_object_nr - 16].bg_color = 3;
    }
}
void pawnTopLeftSide()
{
    if (virtual_area[old_position_object_nr].bg_color == 5)
    {
        if (area[old_position_object_nr - 9].figure_color == 'B' && area[old_position_object_nr].column > 1 && virtual_area[old_position_object_nr - 9].bg_color == 5)
            area[old_position_object_nr - 9].bg_color = 4;
    }
    else
    {
        if (area[old_position_object_nr - 9].figure_color == 'B' && area[old_position_object_nr].column > 1)
            area[old_position_object_nr - 9].bg_color = 4;
    }
}
void pawnTopRigtSide()
{
    if (virtual_area[old_position_object_nr].bg_color == 5)
    {
        if (area[old_position_object_nr - 7].figure_color == 'B' && area[old_position_object_nr].column < 8 && virtual_area[old_position_object_nr - 7].bg_color == 5)
            area[old_position_object_nr - 7].bg_color = 4;
    }
    else
    {
        if (area[old_position_object_nr - 7].figure_color == 'B' && area[old_position_object_nr].column < 8)
            area[old_position_object_nr - 7].bg_color = 4;
    }
}
void pawnBottomSide()
{
    if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
    else if (black_king_check == true)
    {
        if (virtual_area[old_position_object_nr + 8].bg_color == 3)
            area[old_position_object_nr + 8].bg_color = 3;
    }
    else if (virtual_area[old_position_object_nr].bg_color == 5)
    {
        if (area[old_position_object_nr + 8].figure_color == 'E' && virtual_area[old_position_object_nr + 8].bg_color == 5)
            area[old_position_object_nr + 8].bg_color = 3;
    }
    else
    {
        if (area[old_position_object_nr + 8].figure_color == 'E')
            area[old_position_object_nr + 8].bg_color = 3;
    }
}
void pawnBottomBottomSide()
{
    if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
    else if (black_king_check == true)
    {
        if (virtual_area[old_position_object_nr - 16].bg_color == 3)
            area[old_position_object_nr - 16].bg_color = 3;
    }
    else if (virtual_area[old_position_object_nr].bg_color == 5)
    {
        if (area[old_position_object_nr + 16].figure_color == 'E' && virtual_area[old_position_object_nr + 16].bg_color == 5)
            area[old_position_object_nr + 16].bg_color = 3;
    }
    else
    {
        if (area[old_position_object_nr + 16].figure_color == 'E')
            area[old_position_object_nr + 16].bg_color = 3;
    }
}
void pawnBottomLeftSide()
{
    if (virtual_area[old_position_object_nr].bg_color == 5)
    {
        if (area[old_position_object_nr + 7].figure_color == 'W' && area[old_position_object_nr].column > 1 && virtual_area[old_position_object_nr + 7].bg_color == 5)
            area[old_position_object_nr + 7].bg_color = 4;
    }
    else
    {
        if (area[old_position_object_nr + 7].figure_color == 'W' && area[old_position_object_nr].column > 1)
            area[old_position_object_nr + 7].bg_color = 4;
    }
}
void pawnBottomRigtSide()
{
    if (virtual_area[old_position_object_nr].bg_color == 5)
    {
        if (area[old_position_object_nr + 9].figure_color == 'W' && area[old_position_object_nr].column < 8 && virtual_area[old_position_object_nr + 9].bg_color == 5)
            area[old_position_object_nr + 9].bg_color = 4;
    }
    else
    {
        if (area[old_position_object_nr + 9].figure_color == 'W' && area[old_position_object_nr].column < 8)
            area[old_position_object_nr + 9].bg_color = 4;
    }
}

void topSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == 'W')
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1)
                    break;
                if (area[old_position_object_nr - 8 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 8 * i].figure_color == 'B' && virtual_area[old_position_object_nr - 8 * i].bg_color == 3)
                    {
                        area[old_position_object_nr - 8 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr - 8 * i].bg_color == 3)
                    area[old_position_object_nr - 8 * i].bg_color = 3;
                if (area[old_position_object_nr - 8 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1)
                    break;
                if (area[old_position_object_nr - 8 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 8 * i].figure_color == 'B' && virtual_area[old_position_object_nr - 8 * i].bg_color == 5)
                    {
                        area[old_position_object_nr - 8 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr - 8 * i].bg_color == 5)
                    area[old_position_object_nr - 8 * i].bg_color = 3;
                if (area[old_position_object_nr - 8 * i].row == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1)
                    break;
                if (area[old_position_object_nr - 8 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 8 * i].figure_color == 'B')
                    {
                        area[old_position_object_nr - 8 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8)
                    area[old_position_object_nr - 8 * i].bg_color = 3;
                if (area[old_position_object_nr - 8 * i].row == 1)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == 'B')
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1)
                    break;
                if (area[old_position_object_nr - 8 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 8 * i].figure_color == 'W' && virtual_area[old_position_object_nr - 8 * i].bg_color == 3)
                    {
                        area[old_position_object_nr - 8 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr - 8 * i].bg_color == 3)
                    area[old_position_object_nr - 8 * i].bg_color = 3;
                if (area[old_position_object_nr - 8 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1)
                    break;
                if (area[old_position_object_nr - 8 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 8 * i].figure_color == 'W' && virtual_area[old_position_object_nr - 8 * i].bg_color == 5)
                    {
                        area[old_position_object_nr - 8 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr - 8 * i].bg_color == 5)
                    area[old_position_object_nr - 8 * i].bg_color = 3;
                if (area[old_position_object_nr - 8 * i].row == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1)
                    break;
                if (area[old_position_object_nr - 8 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 8 * i].figure_color == 'W')
                    {
                        area[old_position_object_nr - 8 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8)
                    area[old_position_object_nr - 8 * i].bg_color = 3;
                if (area[old_position_object_nr - 8 * i].row == 1)
                    break;
            }
        }
    }
}
void bottomSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == 'W')
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8)
                    break;
                if (area[old_position_object_nr + 8 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 8 * i].figure_color == 'B' && virtual_area[old_position_object_nr + 8 * i].bg_color == 3)
                    {
                        area[old_position_object_nr + 8 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + 8 * i].bg_color == 3)
                    area[old_position_object_nr + 8 * i].bg_color = 3;
                if (area[old_position_object_nr + 8 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8)
                    break;
                if (area[old_position_object_nr + 8 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 8 * i].figure_color == 'B' && virtual_area[old_position_object_nr + 8 * i].bg_color == 5)
                    {
                        area[old_position_object_nr + 8 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + 8 * i].bg_color == 5)
                    area[old_position_object_nr + 8 * i].bg_color = 3;
                if (area[old_position_object_nr + 8 * i].row == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8)
                    break;
                if (area[old_position_object_nr + 8 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 8 * i].figure_color == 'B')
                    {
                        area[old_position_object_nr + 8 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55)
                    area[old_position_object_nr + 8 * i].bg_color = 3;
                if (area[old_position_object_nr + 8 * i].row == 8)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == 'B')
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8)
                    break;
                if (area[old_position_object_nr + 8 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 8 * i].figure_color == 'W' && virtual_area[old_position_object_nr + 8 * i].bg_color == 3)
                    {
                        area[old_position_object_nr + 8 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + 8 * i].bg_color == 3)
                    area[old_position_object_nr + 8 * i].bg_color = 3;
                if (area[old_position_object_nr + 8 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8)
                    break;
                if (area[old_position_object_nr + 8 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 8 * i].figure_color == 'W' && virtual_area[old_position_object_nr + 8 * i].bg_color == 5)
                    {
                        area[old_position_object_nr + 8 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + 8 * i].bg_color == 5)
                    area[old_position_object_nr + 8 * i].bg_color = 3;
                if (area[old_position_object_nr + 8 * i].row == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8)
                    break;
                if (area[old_position_object_nr + 8 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 8 * i].figure_color == 'W')
                    {
                        area[old_position_object_nr + 8 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55)
                    area[old_position_object_nr + 8 * i].bg_color = 3;
                if (area[old_position_object_nr + 8 * i].row == 8)
                    break;
            }
        }
    }
}
void leftSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == 'W')
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr - 1 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 1 * i].figure_color == 'B' && virtual_area[old_position_object_nr - 1 * i].bg_color == 3)
                    {
                        area[old_position_object_nr - 1 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column >= 2 && virtual_area[old_position_object_nr - 1 * i].bg_color == 3)
                    area[old_position_object_nr - 1 * i].bg_color = 3;
                if (area[old_position_object_nr - 1 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr - 1 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 1 * i].figure_color == 'B' && virtual_area[old_position_object_nr - 1 * i].bg_color == 5)
                    {
                        area[old_position_object_nr - 1 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column >= 2 && virtual_area[old_position_object_nr - 1 * i].bg_color == 5)
                    area[old_position_object_nr - 1 * i].bg_color = 3;
                if (area[old_position_object_nr - 1 * i].column == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr - 1 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 1 * i].figure_color == 'B')
                    {
                        area[old_position_object_nr - 1 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column >= 2)
                    area[old_position_object_nr - 1 * i].bg_color = 3;
                if (area[old_position_object_nr - 1 * i].column == 1)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == 'B')
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr - 1 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 1 * i].figure_color == 'W' && virtual_area[old_position_object_nr - 1 * i].bg_color == 3)
                    {
                        area[old_position_object_nr - 1 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column >= 2 && virtual_area[old_position_object_nr - 1 * i].bg_color == 3)
                    area[old_position_object_nr - 1 * i].bg_color = 3;
                if (area[old_position_object_nr - 1 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr - 1 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 1 * i].figure_color == 'W' && virtual_area[old_position_object_nr - 1 * i].bg_color == 5)
                    {
                        area[old_position_object_nr - 1 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column >= 2 && virtual_area[old_position_object_nr - 1 * i].bg_color == 5)
                    area[old_position_object_nr - 1 * i].bg_color = 3;
                if (area[old_position_object_nr - 1 * i].column == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr - 1 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 1 * i].figure_color == 'W')
                    {
                        area[old_position_object_nr - 1 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column >= 2)
                    area[old_position_object_nr - 1 * i].bg_color = 3;
                if (area[old_position_object_nr - 1 * i].column == 1)
                    break;
            }
        }
    }
}
void rightSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == 'W')
    {
       if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else  if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + 1 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 1 * i].figure_color == 'B' && virtual_area[old_position_object_nr + 1 * i].bg_color == 3)
                    {
                        area[old_position_object_nr + 1 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column <= 7 && virtual_area[old_position_object_nr + 1 * i].bg_color == 3)
                    area[old_position_object_nr + 1 * i].bg_color = 3;
                if (area[old_position_object_nr + 1 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + 1 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 1 * i].figure_color == 'B' && virtual_area[old_position_object_nr + 1 * i].bg_color == 5)
                    {
                        area[old_position_object_nr + 1 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column <= 7 && virtual_area[old_position_object_nr + 1 * i].bg_color == 5)
                    area[old_position_object_nr + 1 * i].bg_color = 3;
                if (area[old_position_object_nr + 1 * i].column == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + 1 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 1 * i].figure_color == 'B')
                    {
                        area[old_position_object_nr + 1 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column <= 7)
                    area[old_position_object_nr + 1 * i].bg_color = 3;
                if (area[old_position_object_nr + 1 * i].column == 8)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == 'B')
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + 1 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 1 * i].figure_color == 'W' && virtual_area[old_position_object_nr + 1 * i].bg_color == 3)
                    {
                        area[old_position_object_nr + 1 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column <= 7 && virtual_area[old_position_object_nr + 1 * i].bg_color == 3)
                    area[old_position_object_nr + 1 * i].bg_color = 3;
                if (area[old_position_object_nr + 1 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + 1 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 1 * i].figure_color == 'W' && virtual_area[old_position_object_nr + 1 * i].bg_color == 5)
                    {
                        area[old_position_object_nr + 1 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column <= 7 && virtual_area[old_position_object_nr + 1 * i].bg_color == 5)
                    area[old_position_object_nr + 1 * i].bg_color = 3;
                if (area[old_position_object_nr + 1 * i].column == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + 1 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 1 * i].figure_color == 'W')
                    {
                        area[old_position_object_nr + 1 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (area[old_position_object_nr].column <= 7)
                    area[old_position_object_nr + 1 * i].bg_color = 3;
                if (area[old_position_object_nr + 1 * i].column == 8)
                    break;
            }
        }
    }
}
void topLeftSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == 'W')
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr - 9 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 9 * i].figure_color == 'B' && virtual_area[old_position_object_nr - 9 * i].bg_color == 3)
                    {
                        area[old_position_object_nr - 9 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 9 && virtual_area[old_position_object_nr - 9 * i].bg_color == 3)
                    area[old_position_object_nr - 9 * i].bg_color = 3;
                if (area[old_position_object_nr - 9 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr - 9 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 9 * i].figure_color == 'B' && virtual_area[old_position_object_nr - 9 * i].bg_color == 5)
                    {
                        area[old_position_object_nr - 9 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 9 && virtual_area[old_position_object_nr - 9 * i].bg_color == 5)
                    area[old_position_object_nr - 9 * i].bg_color = 3;
                if (area[old_position_object_nr - 9 * i].row == 1 || area[old_position_object_nr - 9 * i].column == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr - 9 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 9 * i].figure_color == 'B')
                    {
                        area[old_position_object_nr - 9 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 9)
                    area[old_position_object_nr - 9 * i].bg_color = 3;
                if (area[old_position_object_nr - 9 * i].row == 1 || area[old_position_object_nr - 9 * i].column == 1)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == 'B')
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr - 9 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 9 * i].figure_color == 'W' && virtual_area[old_position_object_nr - 9 * i].bg_color == 3)
                    {
                        area[old_position_object_nr - 9 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 9 && virtual_area[old_position_object_nr - 9 * i].bg_color == 3)
                    area[old_position_object_nr - 9 * i].bg_color = 3;
                if (area[old_position_object_nr - 9 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr - 9 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 9 * i].figure_color == 'W' && virtual_area[old_position_object_nr - 9 * i].bg_color == 5)
                    {
                        area[old_position_object_nr - 9 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 9 && virtual_area[old_position_object_nr - 9 * i].bg_color == 5)
                    area[old_position_object_nr - 9 * i].bg_color = 3;
                if (area[old_position_object_nr - 9 * i].row == 1 || area[old_position_object_nr - 9 * i].column == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr - 9 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 9 * i].figure_color == 'W')
                    {
                        area[old_position_object_nr - 9 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 9)
                    area[old_position_object_nr - 9 * i].bg_color = 3;
                if (area[old_position_object_nr - 9 * i].row == 1 || area[old_position_object_nr - 9 * i].column == 1)
                    break;
            }
        }
    }
}
void topRighttSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == 'W')
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr - 7 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 7 * i].figure_color == 'W' && virtual_area[old_position_object_nr - 7 * i].bg_color == 3)
                    {
                        area[old_position_object_nr - 7 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr - 7 * i].bg_color == 3)
                    area[old_position_object_nr - 7 * i].bg_color = 3;
                if (area[old_position_object_nr - 7 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr - 7 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 7 * i].figure_color == 'B' && virtual_area[old_position_object_nr - 7 * i].bg_color == 5)
                    {
                        area[old_position_object_nr - 7 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr - 7 * i].bg_color == 5)
                    area[old_position_object_nr - 7 * i].bg_color = 3;
                if (area[old_position_object_nr - 7 * i].row == 1 || area[old_position_object_nr - 7 * i].column == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr - 7 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 7 * i].figure_color == 'B')
                    {
                        area[old_position_object_nr - 7 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8)
                    area[old_position_object_nr - 7 * i].bg_color = 3;
                if (area[old_position_object_nr - 7 * i].row == 1 || area[old_position_object_nr - 7 * i].column == 8)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == 'B')
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr - 7 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 7 * i].figure_color == 'W' && virtual_area[old_position_object_nr - 7 * i].bg_color == 3)
                    {
                        area[old_position_object_nr - 7 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr - 7 * i].bg_color == 3)
                    area[old_position_object_nr - 7 * i].bg_color = 3;
                if (area[old_position_object_nr - 7 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr - 7 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 7 * i].figure_color == 'W' && virtual_area[old_position_object_nr - 7 * i].bg_color == 5)
                    {
                        area[old_position_object_nr - 7 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8 && virtual_area[old_position_object_nr - 7 * i].bg_color == 5)
                    area[old_position_object_nr - 7 * i].bg_color = 3;
                if (area[old_position_object_nr - 7 * i].row == 1 || area[old_position_object_nr - 7 * i].column == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 1 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr - 7 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr - 7 * i].figure_color == 'W')
                    {
                        area[old_position_object_nr - 7 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr >= 8)
                    area[old_position_object_nr - 7 * i].bg_color = 3;
                if (area[old_position_object_nr - 7 * i].row == 1 || area[old_position_object_nr - 7 * i].column == 8)
                    break;
            }
        }
    }
}
void bottomLeftSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == 'W')
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + 7 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 7 * i].figure_color == 'B' && virtual_area[old_position_object_nr + 7 * i].bg_color == 3)
                    {
                        area[old_position_object_nr + 7 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + 7 * i].bg_color == 3)
                    area[old_position_object_nr + 7 * i].bg_color = 3;
                if (area[old_position_object_nr + 7 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + 7 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 7 * i].figure_color == 'B' && virtual_area[old_position_object_nr + 7 * i].bg_color == 5)
                    {
                        area[old_position_object_nr + 7 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + 7 * i].bg_color == 5)
                    area[old_position_object_nr + 7 * i].bg_color = 3;
                if (area[old_position_object_nr + 7 * i].row == 8 || area[old_position_object_nr + 7 * i].column == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + 7 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 7 * i].figure_color == 'B')
                    {
                        area[old_position_object_nr + 7 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55)
                    area[old_position_object_nr + 7 * i].bg_color = 3;
                if (area[old_position_object_nr + 7 * i].row == 8 || area[old_position_object_nr + 7 * i].column == 1)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == 'B')
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + 7 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 7 * i].figure_color == 'W' && virtual_area[old_position_object_nr + 7 * i].bg_color == 3)
                    {
                        area[old_position_object_nr + 7 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + 7 * i].bg_color == 3)
                    area[old_position_object_nr + 7 * i].bg_color = 3;
                if (area[old_position_object_nr + 7 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + 7 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 7 * i].figure_color == 'W' && virtual_area[old_position_object_nr + 7 * i].bg_color == 5)
                    {
                        area[old_position_object_nr + 7 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55 && virtual_area[old_position_object_nr + 7 * i].bg_color == 5)
                    area[old_position_object_nr + 7 * i].bg_color = 3;
                if (area[old_position_object_nr + 7 * i].row == 8 || area[old_position_object_nr + 7 * i].column == 1)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 1)
                    break;
                if (area[old_position_object_nr + 7 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 7 * i].figure_color == 'W')
                    {
                        area[old_position_object_nr + 7 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 55)
                    area[old_position_object_nr + 7 * i].bg_color = 3;
                if (area[old_position_object_nr + 7 * i].row == 8 || area[old_position_object_nr + 7 * i].column == 1)
                    break;
            }
        }
    }
}
void bottomRightSide()
{
    // WHITE
    if (area[old_position_object_nr].figure_color == 'W')
    {
        if (white_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (white_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + 9 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 9 * i].figure_color == 'B' && virtual_area[old_position_object_nr + 9 * i].bg_color == 3)
                    {
                        area[old_position_object_nr + 9 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 54 && virtual_area[old_position_object_nr + 9 * i].bg_color == 3)
                    area[old_position_object_nr + 9 * i].bg_color = 3;
                if (area[old_position_object_nr + 9 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + 9 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 9 * i].figure_color == 'B' && virtual_area[old_position_object_nr + 9 * i].bg_color == 5)
                    {
                        area[old_position_object_nr + 9 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 54 && virtual_area[old_position_object_nr + 9 * i].bg_color == 5)
                    area[old_position_object_nr + 9 * i].bg_color = 3;
                if (area[old_position_object_nr + 9 * i].row == 8 || area[old_position_object_nr + 9 * i].column == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + 9 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 9 * i].figure_color == 'B')
                    {
                        area[old_position_object_nr + 9 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 54)
                    area[old_position_object_nr + 9 * i].bg_color = 3;
                if (area[old_position_object_nr + 9 * i].row == 8 || area[old_position_object_nr + 9 * i].column == 8)
                    break;
            }
        }
    }
    // BLACK
    if (area[old_position_object_nr].figure_color == 'B')
    {
        if (black_king_check == true && virtual_area[old_position_object_nr].bg_color == 5);
        else if (black_king_check == true)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + 9 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 9 * i].figure_color == 'W' && virtual_area[old_position_object_nr + 9 * i].bg_color == 3)
                    {
                        area[old_position_object_nr + 9 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 54 && virtual_area[old_position_object_nr + 9 * i].bg_color == 3)
                    area[old_position_object_nr + 9 * i].bg_color = 3;
                if (area[old_position_object_nr + 9 * i].row == 1)
                    break;
            }
        }
        else if (virtual_area[old_position_object_nr].bg_color == 5)
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + 9 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 9 * i].figure_color == 'W' && virtual_area[old_position_object_nr + 9 * i].bg_color == 5)
                    {
                        area[old_position_object_nr + 9 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 54 && virtual_area[old_position_object_nr + 9 * i].bg_color == 5)
                    area[old_position_object_nr + 9 * i].bg_color = 3;
                if (area[old_position_object_nr + 9 * i].row == 8 || area[old_position_object_nr + 9 * i].column == 8)
                    break;
            }
        }
        else
        {
            for (int i = 1; i <= 8; i++)
            {
                if (area[old_position_object_nr].row == 8 || area[old_position_object_nr].column == 8)
                    break;
                if (area[old_position_object_nr + 9 * i].figure_color != 'E')
                {
                    if (area[old_position_object_nr + 9 * i].figure_color == 'W')
                    {
                        area[old_position_object_nr + 9 * i].bg_color = 4;
                        break;
                    }
                    else
                        break;
                }
                else if (old_position_object_nr <= 54)
                    area[old_position_object_nr + 9 * i].bg_color = 3;
                if (area[old_position_object_nr + 9 * i].row == 8 || area[old_position_object_nr + 9 * i].column == 8)
                    break;
            }
        }
    }
}

void paintVirtualAreaWhiteColors()
{
    if (virtual_area[virtual_position_object_nr].figure == 'P')
        paintVirtualAreaColorsWhitePawn();
    else if (virtual_area[virtual_position_object_nr].figure == 'S')
        paintVirtualAreaColorsWhiteKnight();
    else if (virtual_area[virtual_position_object_nr].figure == 'G')
        paintVirtualAreaColorsWhiteBishop();
    else if (virtual_area[virtual_position_object_nr].figure == 'W')
        paintVirtualAreaColorsWhiteRook();
    else if (virtual_area[virtual_position_object_nr].figure == 'H')
        paintVirtualAreaColorsWhiteQueen();
    else if (virtual_area[virtual_position_object_nr].figure == 'K')
        paintVirtualAreaColorsWhiteKing();
}

void paintVirtualAreaColorsWhitePawn()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'W')
    {
        // TOP LEFT
        if (virtual_area[virtual_position_object_nr - 9].big_figure == "blackKing")
        {
            if (virtual_area[virtual_position_object_nr - 9].bg_color != 2)
                virtual_area[virtual_position_object_nr - 9].bg_color = 3;
            if (virtual_area[virtual_position_object_nr].bg_color != 2)
                virtual_area[virtual_position_object_nr].bg_color = 3;
        }
        else if (virtual_area[virtual_position_object_nr - 9].figure_color != 'W' && virtual_area[virtual_position_object_nr].column > 1 && virtual_area[virtual_position_object_nr - 9].bg_color != 2 && virtual_area[virtual_position_object_nr - 9].bg_color != 3 && virtual_area[virtual_position_object_nr - 9].bg_color != 5)
            virtual_area[virtual_position_object_nr - 9].bg_color = 4;
        else if (virtual_area[virtual_position_object_nr - 9].figure_color == 'W' && virtual_area[virtual_position_object_nr].column > 1 && virtual_area[virtual_position_object_nr - 9].bg_color != 5)
            virtual_area[virtual_position_object_nr - 9].bg_color = 2;

        // TOP RIGHT
        if (virtual_area[virtual_position_object_nr - 7].big_figure == "blackKing")
        {
            if (virtual_area[virtual_position_object_nr - 7].bg_color != 2)
                virtual_area[virtual_position_object_nr - 7].bg_color = 3;
            if (virtual_area[virtual_position_object_nr].bg_color != 2)
                virtual_area[virtual_position_object_nr].bg_color = 3;
        }
        else if (virtual_area[virtual_position_object_nr - 7].figure_color != 'W' && virtual_area[virtual_position_object_nr].column < 8 && virtual_area[virtual_position_object_nr - 7].bg_color != 2 && virtual_area[virtual_position_object_nr - 7].bg_color != 3 && virtual_area[virtual_position_object_nr - 7].bg_color != 5)
            virtual_area[virtual_position_object_nr - 7].bg_color = 4;
        else if (virtual_area[virtual_position_object_nr - 7].figure_color == 'W' && virtual_area[virtual_position_object_nr].column < 8 && virtual_area[virtual_position_object_nr - 7].bg_color != 5)
            virtual_area[virtual_position_object_nr - 7].bg_color = 2;
    }
}

void paintVirtualAreaColorsWhiteKnight()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'W')
    {
        // TOP TOP LEFT
        if (virtual_position_object_nr >= 17)
        {
            if (virtual_area[virtual_position_object_nr].column >= 2)
            {
                if (virtual_area[virtual_position_object_nr - 17].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr - 17].bg_color != 3)
                        virtual_area[virtual_position_object_nr - 17].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr - 17].figure_color != 'W' && virtual_area[virtual_position_object_nr - 17].bg_color != 2 && virtual_area[virtual_position_object_nr - 17].bg_color != 3 && virtual_area[virtual_position_object_nr - 17].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 17].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr - 17].figure_color == 'W' && virtual_area[virtual_position_object_nr - 17].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 17].bg_color = 2;
            }
        }

        // TOP TOP RIGHT
        if (virtual_position_object_nr >= 16)
        {
            if (virtual_area[virtual_position_object_nr].column <= 7)
            {
                if (virtual_area[virtual_position_object_nr - 15].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr - 15].bg_color != 3)
                        virtual_area[virtual_position_object_nr - 15].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr - 15].figure_color != 'W' && virtual_area[virtual_position_object_nr - 15].bg_color != 2 && virtual_area[virtual_position_object_nr - 15].bg_color != 3 && virtual_area[virtual_position_object_nr - 15].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 15].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr - 15].figure_color == 'W' && virtual_area[virtual_position_object_nr - 15].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 15].bg_color = 2;
            }
        }

        // BOTTOM BOTTOM LEFT
        if (virtual_position_object_nr <= 47)
        {
            if (virtual_area[virtual_position_object_nr].column >= 2)
            {
                if (virtual_area[virtual_position_object_nr + 15].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr + 15].bg_color != 3)
                        virtual_area[virtual_position_object_nr + 15].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr + 15].figure_color != 'W' && virtual_area[virtual_position_object_nr + 15].bg_color != 2 && virtual_area[virtual_position_object_nr + 15].bg_color != 3 && virtual_area[virtual_position_object_nr + 15].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 15].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr + 15].figure_color == 'W' && virtual_area[virtual_position_object_nr + 15].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 15].bg_color = 2;
            }
        }

        // BOTTOM BOTTOM RIGHT
        if (virtual_position_object_nr <= 46)
        {
            if (virtual_area[virtual_position_object_nr].column <= 7)
            {
                if (virtual_area[virtual_position_object_nr + 17].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr + 17].bg_color != 3)
                        virtual_area[virtual_position_object_nr + 17].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr + 17].figure_color != 'W' && virtual_area[virtual_position_object_nr + 17].bg_color != 2 && virtual_area[virtual_position_object_nr + 17].bg_color != 3 && virtual_area[virtual_position_object_nr + 17].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 17].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr + 17].figure_color == 'W' && virtual_area[virtual_position_object_nr + 17].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 17].bg_color = 2;
            }
        }

        // LEFT LEFT TOP
        if (virtual_position_object_nr >= 10)
        {
            if (virtual_area[virtual_position_object_nr].column >= 3)
            {
                if (virtual_area[virtual_position_object_nr - 10].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr - 10].bg_color != 3)
                        virtual_area[virtual_position_object_nr - 10].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr - 10].figure_color != 'W' && virtual_area[virtual_position_object_nr - 10].bg_color != 2 && virtual_area[virtual_position_object_nr - 10].bg_color != 3 && virtual_area[virtual_position_object_nr - 10].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 10].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr - 10].figure_color == 'W' && virtual_area[virtual_position_object_nr - 10].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 10].bg_color = 2;
            }
        }

        // LEFT LEFT BOTTOM
        if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr].column >= 3)
            {
                if (virtual_area[virtual_position_object_nr + 6].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr + 6].bg_color != 3)
                        virtual_area[virtual_position_object_nr + 6].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr + 6].figure_color != 'W' && virtual_area[virtual_position_object_nr + 6].bg_color != 2 && virtual_area[virtual_position_object_nr + 6].bg_color != 3 && virtual_area[virtual_position_object_nr + 6].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 6].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr + 6].figure_color == 'W' && virtual_area[virtual_position_object_nr + 6].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 6].bg_color = 2;
            }
        }

        // RIGH RIGHT TOP
        if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr].column <= 6)
            {
                if (virtual_area[virtual_position_object_nr - 6].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr - 6].bg_color != 3)
                        virtual_area[virtual_position_object_nr - 6].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr - 6].figure_color != 'W' && virtual_area[virtual_position_object_nr - 6].bg_color != 2 && virtual_area[virtual_position_object_nr - 6].bg_color != 3 && virtual_area[virtual_position_object_nr - 6].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 6].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr - 6].figure_color == 'W' && virtual_area[virtual_position_object_nr - 6].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 6].bg_color = 2;
            }
        }

        // RIGH RIGHT BOTTOM
        if (virtual_position_object_nr <= 53)
        {
            if (virtual_area[virtual_position_object_nr].column <= 6)
            {
                if (virtual_area[virtual_position_object_nr + 10].big_figure == "blackKing")
                {
                    if (virtual_area[virtual_position_object_nr + 10].bg_color != 3)
                        virtual_area[virtual_position_object_nr + 10].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr + 10].figure_color != 'W' && virtual_area[virtual_position_object_nr + 10].bg_color != 2 && virtual_area[virtual_position_object_nr + 10].bg_color != 3 && virtual_area[virtual_position_object_nr + 10].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 10].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr + 10].figure_color == 'W' && virtual_area[virtual_position_object_nr + 10].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 10].bg_color = 2;
            }
        }
    }
}

void paintVirtualAreaColorsWhiteBishop()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'W')
    {
        virtualWhiteTopLeftSide();
        virtualWhiteTopRightSide();
        virtualWhiteBottomLeftSide();
        virtualWhiteBottomRightSide();
    }
}

void paintVirtualAreaColorsWhiteRook()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'W')
    {
        virtualWhiteTopSide();
        virtualWhiteBottomSide();
        virtualWhiteLeftSide();
        virtualWhiteRightSide();
    }
}

void paintVirtualAreaColorsWhiteQueen()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'W')
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
    if (virtual_area[virtual_position_object_nr].figure_color == 'W')
    {
        // TOP SIDE
        if (virtual_area[virtual_position_object_nr].row > 1)
        {
            if (virtual_area[virtual_position_object_nr - 8].figure_color != 'W')
                virtual_area[virtual_position_object_nr - 8].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr - 8].figure_color == 'W')
                virtual_area[virtual_position_object_nr - 8].bg_color = 2;
        }

        // BOTTOM SIDE
        if (virtual_area[virtual_position_object_nr].row < 8)
        {
            if (virtual_area[virtual_position_object_nr + 8].figure_color != 'W')
                virtual_area[virtual_position_object_nr + 8].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr + 8].figure_color == 'W')
                virtual_area[virtual_position_object_nr + 8].bg_color = 2;
        }

        // LEFT SIDE
        if (virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr - 1].figure_color != 'W')
                virtual_area[virtual_position_object_nr - 1].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr - 1].figure_color == 'W')
                virtual_area[virtual_position_object_nr - 1].bg_color = 2;
        }

        // RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + 1].figure_color != 'W')
                virtual_area[virtual_position_object_nr + 1].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr + 1].figure_color == 'W')
                virtual_area[virtual_position_object_nr + 1].bg_color = 2;
        }

        // TOP LEFT SIDE
        if (virtual_area[virtual_position_object_nr].row > 1 && virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr - 9].figure_color != 'W')
                virtual_area[virtual_position_object_nr - 9].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr - 9].figure_color == 'W')
                virtual_area[virtual_position_object_nr - 9].bg_color = 2;
        }

        // TOP RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].row > 1 && virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr - 7].figure_color != 'W')
                virtual_area[virtual_position_object_nr - 7].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr - 7].figure_color == 'W')
                virtual_area[virtual_position_object_nr - 7].bg_color = 2;
        }

        // BOTTOM LEFT SIDE
        if (virtual_area[virtual_position_object_nr].row < 8 && virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr + 7].figure_color != 'W')
                virtual_area[virtual_position_object_nr + 7].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr + 7].figure_color == 'W')
                virtual_area[virtual_position_object_nr + 7].bg_color = 2;
        }

        // BOTTOM RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].row < 8 && virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + 9].figure_color != 'W')
                virtual_area[virtual_position_object_nr + 9].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr + 9].figure_color == 'W')
                virtual_area[virtual_position_object_nr + 9].bg_color = 2;
        }
    }
}

void paintVirtualAreaBlackColors()
{
    if (virtual_area[virtual_position_object_nr].figure == 'P')
        paintVirtualAreaColorsBlackPawn();
    else if (virtual_area[virtual_position_object_nr].figure == 'S')
        paintVirtualAreaColorsBlackKnight();
    else if (virtual_area[virtual_position_object_nr].figure == 'G')
        paintVirtualAreaColorsBlackBishop();
    else if (virtual_area[virtual_position_object_nr].figure == 'W')
        paintVirtualAreaColorsBlackRook();
    else if (virtual_area[virtual_position_object_nr].figure == 'H')
        paintVirtualAreaColorsBlackQueen();
    else if (virtual_area[virtual_position_object_nr].figure == 'K')
        paintVirtualAreaColorsBlackKing();
}

void paintVirtualAreaColorsBlackPawn()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'B')
    {
        // BOTTOM LEFT
        if (virtual_area[virtual_position_object_nr + 7].big_figure == "whiteKing")
        {
            if (virtual_area[virtual_position_object_nr + 7].bg_color != 2)
                virtual_area[virtual_position_object_nr + 7].bg_color = 3;
            if (virtual_area[virtual_position_object_nr].bg_color != 2)
                virtual_area[virtual_position_object_nr].bg_color = 3;
        }
        else if (virtual_area[virtual_position_object_nr + 7].figure_color != 'B' && virtual_area[virtual_position_object_nr].column > 1 && virtual_area[virtual_position_object_nr + 7].bg_color != 2 && virtual_area[virtual_position_object_nr + 7].bg_color != 3 && virtual_area[virtual_position_object_nr + 7].bg_color != 5)
            virtual_area[virtual_position_object_nr + 7].bg_color = 4;
        else if (virtual_area[virtual_position_object_nr + 7].figure_color == 'B' && virtual_area[virtual_position_object_nr].column > 1 && virtual_area[virtual_position_object_nr + 7].bg_color != 5)
            virtual_area[virtual_position_object_nr + 7].bg_color = 2;

        // BOTTOM RIGHT
        if (virtual_area[virtual_position_object_nr + 9].big_figure == "whiteKing")
        {
            if (virtual_area[virtual_position_object_nr + 9].bg_color != 2)
                virtual_area[virtual_position_object_nr + 9].bg_color = 3;
            if (virtual_area[virtual_position_object_nr].bg_color != 2)
                virtual_area[virtual_position_object_nr].bg_color = 3;
        }
        else if (virtual_area[virtual_position_object_nr + 9].figure_color != 'B' && virtual_area[virtual_position_object_nr].column < 8 && virtual_area[virtual_position_object_nr + 9].bg_color != 2 && virtual_area[virtual_position_object_nr + 9].bg_color != 3 && virtual_area[virtual_position_object_nr + 9].bg_color != 5)
            virtual_area[virtual_position_object_nr + 9].bg_color = 4;
        else if (virtual_area[virtual_position_object_nr + 9].figure_color == 'B' && virtual_area[virtual_position_object_nr].column < 8 && virtual_area[virtual_position_object_nr + 9].bg_color != 5)
            virtual_area[virtual_position_object_nr + 9].bg_color = 2;
    }
}

void paintVirtualAreaColorsBlackKnight()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'B')
    {
        // TOP TOP LEFT
        if (virtual_position_object_nr >= 17)
        {
            if (virtual_area[virtual_position_object_nr].column >= 2)
            {
                if (virtual_area[virtual_position_object_nr - 17].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr - 17].bg_color != 3)
                        virtual_area[virtual_position_object_nr - 17].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr - 17].figure_color != 'B' && virtual_area[virtual_position_object_nr - 17].bg_color != 2 && virtual_area[virtual_position_object_nr - 17].bg_color != 3 && virtual_area[virtual_position_object_nr - 17].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 17].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr - 17].figure_color == 'B' && virtual_area[virtual_position_object_nr - 17].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 17].bg_color = 2;
            }
        }

        // TOP TOP RIGHT
        if (virtual_position_object_nr >= 16)
        {
            if (virtual_area[virtual_position_object_nr].column <= 7)
            {
                if (virtual_area[virtual_position_object_nr - 15].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr - 15].bg_color != 3)
                        virtual_area[virtual_position_object_nr - 15].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr - 15].figure_color != 'B' && virtual_area[virtual_position_object_nr - 15].bg_color != 2 && virtual_area[virtual_position_object_nr - 15].bg_color != 3 && virtual_area[virtual_position_object_nr - 15].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 15].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr - 15].figure_color == 'B' && virtual_area[virtual_position_object_nr - 15].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 15].bg_color = 2;
            }
        }

        // BOTTOM BOTTOM LEFT
        if (virtual_position_object_nr <= 47)
        {
            if (virtual_area[virtual_position_object_nr].column >= 2)
            {
                if (virtual_area[virtual_position_object_nr + 15].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr + 15].bg_color != 3)
                        virtual_area[virtual_position_object_nr + 15].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr + 15].figure_color != 'B' && virtual_area[virtual_position_object_nr + 15].bg_color != 2 && virtual_area[virtual_position_object_nr + 15].bg_color != 3 && virtual_area[virtual_position_object_nr + 15].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 15].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr + 15].figure_color == 'B' && virtual_area[virtual_position_object_nr + 15].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 15].bg_color = 2;
            }
        }

        // BOTTOM BOTTOM RIGHT
        if (virtual_position_object_nr <= 46)
        {
            if (virtual_area[virtual_position_object_nr].column <= 7)
            {
                if (virtual_area[virtual_position_object_nr + 17].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr + 17].bg_color != 3)
                        virtual_area[virtual_position_object_nr + 17].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr + 17].figure_color != 'B' && virtual_area[virtual_position_object_nr + 17].bg_color != 2 && virtual_area[virtual_position_object_nr + 17].bg_color != 3 && virtual_area[virtual_position_object_nr + 17].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 17].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr + 17].figure_color == 'B' && virtual_area[virtual_position_object_nr + 17].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 17].bg_color = 2;
            }
        }

        // LEFT LEFT TOP
        if (virtual_position_object_nr >= 10)
        {
            if (virtual_area[virtual_position_object_nr].column >= 3)
            {
                if (virtual_area[virtual_position_object_nr - 10].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr - 10].bg_color != 3)
                        virtual_area[virtual_position_object_nr - 10].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr - 10].figure_color != 'B' && virtual_area[virtual_position_object_nr - 10].bg_color != 2 && virtual_area[virtual_position_object_nr - 10].bg_color != 3 && virtual_area[virtual_position_object_nr - 10].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 10].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr - 10].figure_color == 'B' && virtual_area[virtual_position_object_nr - 10].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 10].bg_color = 2;
            }
        }

        // LEFT LEFT BOTTOM
        if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr].column >= 3)
            {
                if (virtual_area[virtual_position_object_nr + 6].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr + 6].bg_color != 3)
                        virtual_area[virtual_position_object_nr + 6].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr + 6].figure_color != 'B' && virtual_area[virtual_position_object_nr + 6].bg_color != 2 && virtual_area[virtual_position_object_nr + 6].bg_color != 3 && virtual_area[virtual_position_object_nr + 6].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 6].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr + 6].figure_color == 'B' && virtual_area[virtual_position_object_nr + 6].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 6].bg_color = 2;
            }
        }

        // RIGH RIGHT TOP
        if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr].column <= 6)
            {
                if (virtual_area[virtual_position_object_nr - 6].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr - 6].bg_color != 3)
                        virtual_area[virtual_position_object_nr - 6].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr - 6].figure_color != 'B' && virtual_area[virtual_position_object_nr - 6].bg_color != 2 && virtual_area[virtual_position_object_nr - 6].bg_color != 3 && virtual_area[virtual_position_object_nr - 6].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 6].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr - 6].figure_color == 'B' && virtual_area[virtual_position_object_nr - 6].bg_color != 5)
                    virtual_area[virtual_position_object_nr - 6].bg_color = 2;
            }
        }

        // RIGH RIGHT BOTTOM
        if (virtual_position_object_nr <= 53)
        {
            if (virtual_area[virtual_position_object_nr].column <= 6)
            {
                if (virtual_area[virtual_position_object_nr + 10].big_figure == "whiteKing")
                {
                    if (virtual_area[virtual_position_object_nr + 10].bg_color != 3)
                        virtual_area[virtual_position_object_nr + 10].bg_color = 3;
                    if (virtual_area[virtual_position_object_nr].bg_color != 3)
                        virtual_area[virtual_position_object_nr].bg_color = 3;
                }
                else if (virtual_area[virtual_position_object_nr + 10].figure_color != 'B' && virtual_area[virtual_position_object_nr + 10].bg_color != 2 && virtual_area[virtual_position_object_nr + 10].bg_color != 3 && virtual_area[virtual_position_object_nr + 10].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 10].bg_color = 4;
                else if (virtual_area[virtual_position_object_nr + 10].figure_color == 'B' && virtual_area[virtual_position_object_nr + 10].bg_color != 5)
                    virtual_area[virtual_position_object_nr + 10].bg_color = 2;
            }
        }
    }
}

void paintVirtualAreaColorsBlackBishop()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'B')
    {
        virtualBlackTopLeftSide();
        virtualBlackTopRightSide();
        virtualBlackBottomLeftSide();
        virtualBlackBottomRightSide();
    }
}

void paintVirtualAreaColorsBlackRook()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'B')
    {
        virtualBlackTopSide();
        virtualBlackBottomSide();
        virtualBlackLeftSide();
        virtualBlackRightSide();
    }
}

void paintVirtualAreaColorsBlackQueen()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'B')
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
    if (virtual_area[virtual_position_object_nr].figure_color == 'B')
    {
        // TOP SIDE
        if (virtual_area[virtual_position_object_nr].row > 1)
        {
            if (virtual_area[virtual_position_object_nr - 8].figure_color != 'B')
                virtual_area[virtual_position_object_nr - 8].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr - 8].figure_color == 'B')
                virtual_area[virtual_position_object_nr - 8].bg_color = 2;
        }

        // BOTTOM SIDE
        if (virtual_area[virtual_position_object_nr].row < 8)
        {
            if (virtual_area[virtual_position_object_nr + 8].figure_color != 'B')
                virtual_area[virtual_position_object_nr + 8].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr + 8].figure_color == 'B')
                virtual_area[virtual_position_object_nr + 8].bg_color = 2;
        }

        // LEFT SIDE
        if (virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr - 1].figure_color != 'B')
                virtual_area[virtual_position_object_nr - 1].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr - 1].figure_color == 'B')
                virtual_area[virtual_position_object_nr - 1].bg_color = 2;
        }

        // RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + 1].figure_color != 'B')
                virtual_area[virtual_position_object_nr + 1].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr + 1].figure_color == 'B')
                virtual_area[virtual_position_object_nr + 1].bg_color = 2;
        }

        // TOP LEFT SIDE
        if (virtual_area[virtual_position_object_nr].row > 1 && virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr - 9].figure_color != 'B')
                virtual_area[virtual_position_object_nr - 9].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr - 9].figure_color == 'B')
                virtual_area[virtual_position_object_nr - 9].bg_color = 2;
        }

        // TOP RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].row > 1 && virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr - 7].figure_color != 'B')
                virtual_area[virtual_position_object_nr - 7].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr - 7].figure_color == 'B')
                virtual_area[virtual_position_object_nr - 7].bg_color = 2;
        }

        // BOTTOM LEFT SIDE
        if (virtual_area[virtual_position_object_nr].row < 8 && virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr + 7].figure_color != 'B')
                virtual_area[virtual_position_object_nr + 7].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr + 7].figure_color == 'B')
                virtual_area[virtual_position_object_nr + 7].bg_color = 2;
        }

        // BOTTOM RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].row < 8 && virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + 9].figure_color != 'B')
                virtual_area[virtual_position_object_nr + 9].bg_color = 4;
            else if (virtual_area[virtual_position_object_nr + 9].figure_color == 'B')
                virtual_area[virtual_position_object_nr + 9].bg_color = 2;
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
        if (virtual_area[virtual_position_object_nr - 8 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr - 8 * i].big_figure == "blackKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr - 8 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr - 8 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr - 8 * i].figure_color == 'B')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr - 8 * (i + k)].figure_color == 'B')
                    {
                        if (virtual_area[virtual_position_object_nr - 8 * (i + k)].big_figure != "blackKing")
                        {
                            if (virtual_area[virtual_position_object_nr - 8 * i].bg_color != 2 && virtual_area[virtual_position_object_nr - 8 * i].bg_color != 3 && virtual_area[virtual_position_object_nr - 8 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr - 8 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr - 8 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr - 8 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr - 8 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr - 8 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr - 8 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr - 8 * i].row == 1)
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
        if (virtual_area[virtual_position_object_nr + 8 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr + 8 * i].big_figure == "blackKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr + 8 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr + 8 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + 8 * i].figure_color == 'B')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + 8 * (i + k)].figure_color == 'B')
                    {
                        if (virtual_area[virtual_position_object_nr + 8 * (i + k)].big_figure != "blackKing")
                        {
                            if (virtual_area[virtual_position_object_nr + 8 * i].bg_color != 2 && virtual_area[virtual_position_object_nr + 8 * i].bg_color != 3 && virtual_area[virtual_position_object_nr + 8 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr + 8 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr + 8 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + 8 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr + 8 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr + 8 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr + 8 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr + 8 * i].row == 8)
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
        if (virtual_area[virtual_position_object_nr - 1 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr - 1 * i].big_figure == "blackKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr - 1 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr - 1 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr - 1 * i].figure_color == 'B')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr - 1 * (i + k)].figure_color == 'B')
                    {
                        if (virtual_area[virtual_position_object_nr - 1 * (i + k)].big_figure != "blackKing")
                        {
                            if (virtual_area[virtual_position_object_nr - 8 * i].bg_color != 2 && virtual_area[virtual_position_object_nr + 1 * i].bg_color != 3 && virtual_area[virtual_position_object_nr + 1 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr - 1 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr - 1 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr - 1 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr - 1 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_area[virtual_position_object_nr].column >= 2)
        {
            if (virtual_area[virtual_position_object_nr - 1 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr - 1 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr - 1 * i].column == 1)
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
        if (virtual_area[virtual_position_object_nr + 1 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr + 1 * i].big_figure == "blackKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr + 1 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr + 1 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + 1 * i].figure_color == 'B')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + 1 * (i + k)].figure_color == 'B')
                    {
                        if (virtual_area[virtual_position_object_nr + 1 * (i + k)].big_figure != "blackKing")
                        {
                            if (virtual_area[virtual_position_object_nr + 1 * i].bg_color != 2 && virtual_area[virtual_position_object_nr + 1 * i].bg_color != 3 && virtual_area[virtual_position_object_nr + 1 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr + 1 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr + 1 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + 1 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr + 1 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_area[virtual_position_object_nr].column <= 7)
        {
            if (virtual_area[virtual_position_object_nr + 1 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr + 1 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr + 1 * i].column == 8)
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
        if (virtual_area[virtual_position_object_nr - 9 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr - 9 * i].big_figure == "blackKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr - 9 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr - 9 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr - 9 * i].figure_color == 'B')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr - 9 * (i + k)].figure_color == 'B')
                    {
                        if (virtual_area[virtual_position_object_nr - 9 * (i + k)].big_figure != "blackKing")
                        {
                            if (virtual_area[virtual_position_object_nr - 9 * i].bg_color != 2 && virtual_area[virtual_position_object_nr - 9 * i].bg_color != 3 && virtual_area[virtual_position_object_nr - 9 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr - 9 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr - 9 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr - 9 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr - 9 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr >= 9)
        {
            if (virtual_area[virtual_position_object_nr - 9 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr - 9 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr - 9 * i].row == 1 || virtual_area[virtual_position_object_nr - 9 * i].column == 1)
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
        if (virtual_area[virtual_position_object_nr - 7 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr - 7 * i].big_figure == "blackKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr - 7 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr - 7 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr - 7 * i].figure_color == 'B')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr - 7 * (i + k)].figure_color == 'B')
                    {
                        if (virtual_area[virtual_position_object_nr - 7 * (i + k)].big_figure != "blackKing")
                        {
                            if (virtual_area[virtual_position_object_nr - 7 * i].bg_color != 2 && virtual_area[virtual_position_object_nr - 7 * i].bg_color != 3 && virtual_area[virtual_position_object_nr - 7 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr - 7 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr - 7 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr - 7 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr - 7 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr - 7 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr - 7 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr - 7 * i].row == 1 || virtual_area[virtual_position_object_nr - 7 * i].column == 8)
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
        if (virtual_area[virtual_position_object_nr + 7 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr + 7 * i].big_figure == "blackKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr + 7 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr + 7 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + 7 * i].figure_color == 'B')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + 7 * (i + k)].figure_color == 'B')
                    {
                        if (virtual_area[virtual_position_object_nr + 7 * (i + k)].big_figure != "blackKing")
                        {
                            if (virtual_area[virtual_position_object_nr + 7 * i].bg_color != 2 && virtual_area[virtual_position_object_nr + 7 * i].bg_color != 3 && virtual_area[virtual_position_object_nr + 7 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr + 7 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr + 7 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + 7 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr + 7 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr + 7 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr + 7 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr + 7 * i].row == 8 || virtual_area[virtual_position_object_nr + 7 * i].column == 1)
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
        if (virtual_area[virtual_position_object_nr + 9 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr + 9 * i].big_figure == "blackKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr + 9 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr + 9 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + 9 * i].figure_color == 'B')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + 9 * (i + k)].figure_color == 'B')
                    {
                        if (virtual_area[virtual_position_object_nr + 9 * (i + k)].big_figure != "blackKing")
                        {
                            if (virtual_area[virtual_position_object_nr + 9 * i].bg_color != 2 && virtual_area[virtual_position_object_nr + 9 * i].bg_color != 3 && virtual_area[virtual_position_object_nr + 9 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr + 9 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr + 9 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + 9 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr + 9 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr <= 54)
        {
            if (virtual_area[virtual_position_object_nr + 9 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr + 9 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr + 9 * i].row == 8 || virtual_area[virtual_position_object_nr + 9 * i].column == 8)
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
        if (virtual_area[virtual_position_object_nr - 8 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr - 8 * i].big_figure == "whiteKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr - 8 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr - 8 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr - 8 * i].figure_color == 'W')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr - 8 * (i + k)].figure_color == 'W')
                    {
                        if (virtual_area[virtual_position_object_nr - 8 * (i + k)].big_figure != "whiteKing")
                        {
                            if (virtual_area[virtual_position_object_nr - 8 * i].bg_color != 2 && virtual_area[virtual_position_object_nr - 8 * i].bg_color != 3 && virtual_area[virtual_position_object_nr - 8 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr - 8 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr - 8 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr - 8 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr - 8 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr - 8 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr - 8 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr - 8 * i].row == 1)
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
        if (virtual_area[virtual_position_object_nr + 8 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr + 8 * i].big_figure == "whiteKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr + 8 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr + 8 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + 8 * i].figure_color == 'W')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + 8 * (i + k)].figure_color == 'W')
                    {
                        if (virtual_area[virtual_position_object_nr + 8 * (i + k)].big_figure != "whiteKing")
                        {
                            if (virtual_area[virtual_position_object_nr + 8 * i].bg_color != 2 && virtual_area[virtual_position_object_nr + 8 * i].bg_color != 3 && virtual_area[virtual_position_object_nr + 8 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr + 8 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr + 8 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + 8 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr + 8 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr + 8 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr + 8 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr + 8 * i].row == 8)
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
        if (virtual_area[virtual_position_object_nr - 1 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr - 1 * i].big_figure == "whiteKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr - 1 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr - 1 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr - 1 * i].figure_color == 'W')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr - 1 * (i + k)].figure_color == 'W')
                    {
                        if (virtual_area[virtual_position_object_nr - 1 * (i + k)].big_figure != "whiteKing")
                        {
                            if (virtual_area[virtual_position_object_nr - 1 * i].bg_color != 2 && virtual_area[virtual_position_object_nr - 1 * i].bg_color != 3 && virtual_area[virtual_position_object_nr - 1 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr - 1 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr - 1 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr - 1 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr - 1 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_area[virtual_position_object_nr].column >= 2)
        {
            if (virtual_area[virtual_position_object_nr - 1 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr - 1 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr - 1 * i].column == 1)
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
        if (virtual_area[virtual_position_object_nr + 1 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr + 1 * i].big_figure == "whiteKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr + 1 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr + 1 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + 1 * i].figure_color == 'W')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + 1 * (i + k)].figure_color == 'W')
                    {
                        if (virtual_area[virtual_position_object_nr + 1 * (i + k)].big_figure != "whiteKing")
                        {
                            if (virtual_area[virtual_position_object_nr + 1 * i].bg_color != 2 && virtual_area[virtual_position_object_nr + 1 * i].bg_color != 3 && virtual_area[virtual_position_object_nr + 1 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr + 1 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr + 1 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + 1 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr + 1 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_area[virtual_position_object_nr].column <= 7)
        {
            if (virtual_area[virtual_position_object_nr + 1 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr + 1 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr + 1 * i].column == 8)
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
        if (virtual_area[virtual_position_object_nr - 9 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr - 9 * i].big_figure == "whiteKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr - 9 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr - 9 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr - 9 * i].figure_color == 'W')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr - 9 * (i + k)].figure_color == 'W')
                    {
                        if (virtual_area[virtual_position_object_nr - 9 * (i + k)].big_figure != "whiteKing")
                        {
                            if (virtual_area[virtual_position_object_nr - 9 * i].bg_color != 2 && virtual_area[virtual_position_object_nr - 9 * i].bg_color != 3 && virtual_area[virtual_position_object_nr - 9 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr - 9 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr - 9 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr - 9 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr - 9 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr >= 9)
        {
            if (virtual_area[virtual_position_object_nr - 9 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr - 9 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr - 9 * i].row == 1 || virtual_area[virtual_position_object_nr - 9 * i].column == 1)
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
        if (virtual_area[virtual_position_object_nr - 7 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr - 7 * i].big_figure == "whiteKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr - 7 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr - 7 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr - 7 * i].figure_color == 'W')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr - 7 * (i + k)].figure_color == 'W')
                    {
                        if (virtual_area[virtual_position_object_nr - 7 * (i + k)].big_figure != "whiteKing")
                        {
                            if (virtual_area[virtual_position_object_nr - 7 * i].bg_color != 2 && virtual_area[virtual_position_object_nr - 7 * i].bg_color != 3 && virtual_area[virtual_position_object_nr - 7 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr - 7 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr - 7 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr - 7 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr - 7 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr - 7 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr - 7 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr - 7 * i].row == 1 || virtual_area[virtual_position_object_nr - 7 * i].column == 8)
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
        if (virtual_area[virtual_position_object_nr + 7 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr + 7 * i].big_figure == "whiteKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr + 7 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr + 7 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + 7 * i].figure_color == 'W')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + 7 * (i + k)].figure_color == 'W')
                    {
                        if (virtual_area[virtual_position_object_nr + 7 * (i + k)].big_figure != "whiteKing")
                        {
                            if (virtual_area[virtual_position_object_nr + 7 * i].bg_color != 2 && virtual_area[virtual_position_object_nr + 7 * i].bg_color != 3 && virtual_area[virtual_position_object_nr + 7 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr + 7 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr + 7 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + 7 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr + 7 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr + 7 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr + 7 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr + 7 * i].row == 8 || virtual_area[virtual_position_object_nr + 7 * i].column == 1)
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
        if (virtual_area[virtual_position_object_nr + 9 * i].figure_color != 'E')
        {
            if (virtual_area[virtual_position_object_nr + 9 * i].big_figure == "whiteKing")
            {
                for (int j = i; j >= 1; j--)
                {
                    if (virtual_area[virtual_position_object_nr + 9 * j].bg_color != 2)
                        virtual_area[virtual_position_object_nr + 9 * j].bg_color = 3;
                }
                if (virtual_area[virtual_position_object_nr].bg_color != 2)
                    virtual_area[virtual_position_object_nr].bg_color = 3;
                break;
            }
            else if (virtual_area[virtual_position_object_nr + 9 * i].figure_color == 'W')
            {
                for (int k = 1; k < 7; k++)
                {
                    if (virtual_area[virtual_position_object_nr + 9 * (i + k)].figure_color == 'W')
                    {
                        if (virtual_area[virtual_position_object_nr + 9 * (i + k)].big_figure != "whiteKing")
                        {
                            if (virtual_area[virtual_position_object_nr + 9 * i].bg_color != 2 && virtual_area[virtual_position_object_nr + 9 * i].bg_color != 3 && virtual_area[virtual_position_object_nr + 9 * i].bg_color != 5)
                            {
                                virtual_area[virtual_position_object_nr + 9 * i].bg_color = 4;
                                stop = true;
                                break;
                            }
                            else
                            {
                                stop = true;
                                break;
                            }
                        }
                        else
                        {
                            for (int j = (i + k - 1); j >= 1; j--)
                            {
                                virtual_area[virtual_position_object_nr + 9 * j].bg_color = 5;
                            }
                            virtual_area[virtual_position_object_nr].bg_color = 5;
                            stop = true;
                            break;
                        }
                    }
                }
            }
            else if (virtual_area[virtual_position_object_nr + 9 * i].bg_color != 5)
            {
                virtual_area[virtual_position_object_nr + 9 * i].bg_color = 2;
                break;
            }
            if (stop == true)
                break;
        }
        else if (virtual_position_object_nr <= 54)
        {
            if (virtual_area[virtual_position_object_nr + 9 * i].bg_color != 5)
                virtual_area[virtual_position_object_nr + 9 * i].bg_color = 4;
        }
        if (virtual_area[virtual_position_object_nr + 9 * i].row == 8 || virtual_area[virtual_position_object_nr + 9 * i].column == 8)
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
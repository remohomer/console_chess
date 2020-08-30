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

void refreshAreaID();       // preview of chessboard with id
void refreshAreaPosition(); // preview of chessboard with position
void refreshAreaNR();       // preview of chessboard witn rows and columns

void whiteKingCheck();
void blackKingCheck();

void checkingMoveFigures();
void moveFigures();
void moveFigures_VirtualArea(); // virtual
void whoWins();

void showAreaStats(); // preview of variables
void showBools();     // preview of variables

void paintAreaColors();
void paintAreaColorsPawn();
void paintAreaColorsKnight();
void paintAreaColorsBishop();
void paintAreaColorsRook();
void paintAreaColorsQueen();
void paintAreaColorsKing();

void paintVirtualAreaWhiteColors();       // virtual
void paintVirtualAreaColorsWhitePawn();   // virtual
void paintVirtualAreaColorsWhiteKnight(); // virtual
void paintVirtualAreaColorsWhiteBishop(); // virtual
void paintVirtualAreaColorsWhiteRook();   // virtual
void paintVirtualAreaColorsWhiteQueen();  // virtual
void paintVirtualAreaColorsWhiteKing();   // virtual

void paintVirtualAreaBlackColors();       // virtual
void paintVirtualAreaColorsBlackPawn();   // virtual
void paintVirtualAreaColorsBlackKnight(); // virtual
void paintVirtualAreaColorsBlackBishop(); // virtual
void paintVirtualAreaColorsBlackRook();   // virtual
void paintVirtualAreaColorsBlackQueen();  // virtual
void paintVirtualAreaColorsBlackKing();   // virtual

void textColorStandard();
void textColorBlue();
void textColorRed();
void textColorYellow();

void bgColorAquaTextColorWhite();
void bgColorAquaTextColorBlack();
void bgColorBlueTextColorWhite();
void bgColorBlueTextColorBlack();

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
    char choice{};

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

        switch (choice)
        {
        case '1':
            newGame();
            break;
        case '2':
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

            break;
        case '3':
            howToPlay();
            break;
        case '4':
            gamesStory();
            break;
        case '5':
            break;
        default:
            textColorRed();
            cout << "\nBledny wybor! Sprobuj jeszcze raz . . .";
            textColorStandard();
            Sleep(1500);
        }

    } while (choice != '5');
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
        if (virtual_area[j].big_figure == "whiteKing" && virtual_area[j].bg_color == 4)
        {
            white_king_check = true;
            break;
        }
    }
}

void blackKingCheck()
{
    for (int j = 0; j < 64; j++)
    {
        if (virtual_area[j].big_figure == "blackKing" && virtual_area[j].bg_color == 4)
        {
            black_king_check = true;
            break;
        }
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
                check = "again";
                resetAreaColors();
                checkingMoveFigures();
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
                system("pause");
                area[new_position_object_nr].big_figure = "whitePromotedQueen";
                area[new_position_object_nr].figure = 'H';
                area[new_position_object_nr].figure_color = 'W';
                white_promoted_choise = true;
                system("pause");
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
        if (area[old_position_object_nr].big_figure == "whiteLeftRook")
            white_left_rook_move = true;
        if (area[old_position_object_nr].big_figure == "whiteRightRook")
            white_right_rook_move = true;
        if (area[old_position_object_nr].big_figure == "blackLeftRook")
            black_left_rook_move = true;
        if (area[old_position_object_nr].big_figure == "blackRightRook")
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
    textColorStandard();
    cout << "\n\nWKC " << white_king_check;
    cout << " | BKC " << black_king_check;
    cout << "\nWLC " << active_white_left_castling;
    cout << " | WRC " << active_white_right_castling;
    cout << " | BLC " << active_black_left_castling;
    cout << " | BRC " << active_black_right_castling;

    cout << "\n\nWLRM" << white_left_rook_move;
    cout << " | WRRM " << white_right_rook_move;
    cout << " | BLRM " << black_left_rook_move;
    cout << " | BRRM " << black_right_rook_move;
    cout << " | WKM " << white_king_move;
    cout << " | BKM " << black_king_move << endl
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
        /////////// STARTED POSITION ///////////
        if (area[old_position_object_nr].row == 7)
        {
            // TOP LEFT
            if (area[old_position_object_nr - 9].figure_color == 'B' && area[old_position_object_nr].column > 1)
                area[old_position_object_nr - 9].bg_color = 4;
            // TOP RIGHT
            if (area[old_position_object_nr - 7].figure_color == 'B' && area[old_position_object_nr].column < 8)
                area[old_position_object_nr - 7].bg_color = 4;

            // TOP
            if (area[old_position_object_nr - 16].figure_color == 'E')
                area[old_position_object_nr - 16].bg_color = 3;
            if (area[old_position_object_nr - 8].figure_color == 'E')
                area[old_position_object_nr - 8].bg_color = 3;
        }

        /////////// OTHER POSITION ///////////
        else
        {
            // TOP LEFT
            if (area[old_position_object_nr - 9].figure_color == 'B' && area[old_position_object_nr].column > 1)
                area[old_position_object_nr - 9].bg_color = 4;
            // TOP RIGHT
            if (area[old_position_object_nr - 7].figure_color == 'B' && area[old_position_object_nr].column < 8)
                area[old_position_object_nr - 7].bg_color = 4;

            // TOP
            if (area[old_position_object_nr - 8].figure_color == 'E')
                area[old_position_object_nr - 8].bg_color = 3;
        }
    }

    ///////////////// BLACK /////////////////
    else
    {
        /////////// STARTED POSITION ///////////
        if (area[old_position_object_nr].row == 2)
        {
            // BOTTOM LEFT
            if (area[old_position_object_nr + 7].figure_color == 'W' && area[old_position_object_nr].column > 1)
                area[old_position_object_nr + 7].bg_color = 4;
            // BOTTOM RIGHT
            if (area[old_position_object_nr + 9].figure_color == 'W' && area[old_position_object_nr].column < 8)
                area[old_position_object_nr + 9].bg_color = 4;

            // BOTTOM
            if (area[old_position_object_nr + 8].figure_color == 'E')
                area[old_position_object_nr + 8].bg_color = 3;
            if (area[old_position_object_nr + 16].figure_color == 'E')
                area[old_position_object_nr + 16].bg_color = 3;
        }

        /////////// OTHER POSITION ///////////
        else
        {
            // BOTTOM LEFT
            if (area[old_position_object_nr + 7].figure_color == 'W' && area[old_position_object_nr].column > 1)
                area[old_position_object_nr + 7].bg_color = 4;
            // BOTTOM RIGHT
            if (area[old_position_object_nr + 9].figure_color == 'W' && area[old_position_object_nr].column < 8)
                area[old_position_object_nr + 9].bg_color = 4;

            // BOTTOM
            if (area[old_position_object_nr + 8].figure_color == 'E')
                area[old_position_object_nr + 8].bg_color = 3;
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
            if (area[old_position_object_nr].column >= 2)
            {
                if (area[old_position_object_nr - 17].figure_color == 'B')
                    area[old_position_object_nr - 17].bg_color = 4;
                else if (area[old_position_object_nr - 17].figure_color == 'E')
                    area[old_position_object_nr - 17].bg_color = 3;
            }
        }

        // TOP TOP RIGHT
        if (old_position_object_nr >= 16)
        {
            if (area[old_position_object_nr].column <= 7)
            {
                if (area[old_position_object_nr - 15].figure_color == 'B')
                    area[old_position_object_nr - 15].bg_color = 4;
                else if (area[old_position_object_nr - 15].figure_color == 'E')
                    area[old_position_object_nr - 15].bg_color = 3;
            }
        }

        // BOTTOM BOTTOM LEFT
        if (old_position_object_nr <= 47)
        {
            if (area[old_position_object_nr].column >= 2)
            {
                if (area[old_position_object_nr + 15].figure_color == 'B')
                    area[old_position_object_nr + 15].bg_color = 4;
                else if (area[old_position_object_nr + 15].figure_color == 'E')
                    area[old_position_object_nr + 15].bg_color = 3;
            }
        }

        // BOTTOM BOTTOM RIGHT
        if (old_position_object_nr <= 46)
        {
            if (area[old_position_object_nr].column <= 7)
            {
                if (area[old_position_object_nr + 17].figure_color == 'B')
                    area[old_position_object_nr + 17].bg_color = 4;
                else if (area[old_position_object_nr + 17].figure_color == 'E')
                    area[old_position_object_nr + 17].bg_color = 3;
            }
        }

        // LEFT LEFT TOP
        if (old_position_object_nr >= 10)
        {
            if (area[old_position_object_nr].column >= 3)
            {
                if (area[old_position_object_nr - 10].figure_color == 'B')
                    area[old_position_object_nr - 10].bg_color = 4;
                else if (area[old_position_object_nr - 10].figure_color == 'E')
                    area[old_position_object_nr - 10].bg_color = 3;
            }
        }

        // LEFT LEFT BOTTOM
        if (old_position_object_nr <= 55)
        {
            if (area[old_position_object_nr].column >= 3)
            {
                if (area[old_position_object_nr + 6].figure_color == 'B')
                    area[old_position_object_nr + 6].bg_color = 4;
                else if (area[old_position_object_nr + 6].figure_color == 'E')
                    area[old_position_object_nr + 6].bg_color = 3;
            }
        }

        // RIGH RIGHT TOP
        if (old_position_object_nr >= 8)
        {
            if (area[old_position_object_nr].column <= 6)
            {
                if (area[old_position_object_nr - 6].figure_color == 'B')
                    area[old_position_object_nr - 6].bg_color = 4;
                else if (area[old_position_object_nr - 6].figure_color == 'E')
                    area[old_position_object_nr - 6].bg_color = 3;
            }
        }

        // RIGH RIGHT BOTTOM
        if (old_position_object_nr <= 53)
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

    ///////////////// BLACK /////////////////
    if (area[old_position_object_nr].figure_color == 'B')
    {
        // TOP TOP LEFT
        if (old_position_object_nr >= 17)
        {
            if (area[old_position_object_nr].column >= 2)
            {
                if (area[old_position_object_nr - 17].figure_color == 'W')
                    area[old_position_object_nr - 17].bg_color = 4;
                else if (area[old_position_object_nr - 17].figure_color == 'E')
                    area[old_position_object_nr - 17].bg_color = 3;
            }
        }

        // TOP TOP RIGHT
        if (old_position_object_nr >= 16)
        {
            if (area[old_position_object_nr].column <= 7)
            {
                if (area[old_position_object_nr - 15].figure_color == 'W')
                    area[old_position_object_nr - 15].bg_color = 4;
                else if (area[old_position_object_nr - 15].figure_color == 'E')
                    area[old_position_object_nr - 15].bg_color = 3;
            }
        }

        // BOTTOM BOTTOM LEFT
        if (old_position_object_nr <= 47)
        {
            if (area[old_position_object_nr].column >= 2)
            {
                if (area[old_position_object_nr + 15].figure_color == 'W')
                    area[old_position_object_nr + 15].bg_color = 4;
                else if (area[old_position_object_nr + 15].figure_color == 'E')
                    area[old_position_object_nr + 15].bg_color = 3;
            }
        }

        // BOTTOM BOTTOM RIGHT
        if (old_position_object_nr <= 46)
        {
            if (area[old_position_object_nr].column <= 7)
            {
                if (area[old_position_object_nr + 17].figure_color == 'W')
                    area[old_position_object_nr + 17].bg_color = 4;
                else if (area[old_position_object_nr + 17].figure_color == 'E')
                    area[old_position_object_nr + 17].bg_color = 3;
            }
        }

        // LEFT LEFT TOP
        if (old_position_object_nr >= 10)
        {
            if (area[old_position_object_nr].column >= 3)
            {
                if (area[old_position_object_nr - 10].figure_color == 'W')
                    area[old_position_object_nr - 10].bg_color = 4;
                else if (area[old_position_object_nr - 10].figure_color == 'E')
                    area[old_position_object_nr - 10].bg_color = 3;
            }
        }

        // LEFT LEFT BOTTOM
        if (old_position_object_nr <= 55)
        {
            if (area[old_position_object_nr].column >= 3)
            {
                if (area[old_position_object_nr + 6].figure_color == 'W')
                    area[old_position_object_nr + 6].bg_color = 4;
                else if (area[old_position_object_nr + 6].figure_color == 'E')
                    area[old_position_object_nr + 6].bg_color = 3;
            }
        }

        // RIGH RIGHT TOP
        if (old_position_object_nr >= 8)
        {
            if (area[old_position_object_nr].column <= 6)
            {
                if (area[old_position_object_nr - 6].figure_color == 'W')
                    area[old_position_object_nr - 6].bg_color = 4;
                else if (area[old_position_object_nr - 6].figure_color == 'E')
                    area[old_position_object_nr - 6].bg_color = 3;
            }
        }

        // RIGH RIGHT BOTTOM
        if (old_position_object_nr <= 53)
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
void paintAreaColorsBishop()
{
    ///////////////// WHITE /////////////////
    if (area[old_position_object_nr].figure_color == 'W')
    {

        // TOP LEFT SIDE
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
            if (old_position_object_nr >= 9)
                area[old_position_object_nr - 9 * i].bg_color = 3;
            if (area[old_position_object_nr - 9 * i].row == 1 || area[old_position_object_nr - 9 * i].column == 1)
                break;
        }

        // TOP RIGHT SIDE
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
            if (old_position_object_nr >= 8)
                area[old_position_object_nr - 7 * i].bg_color = 3;
            if (area[old_position_object_nr - 7 * i].row == 1 || area[old_position_object_nr - 7 * i].column == 8)
                break;
        }

        // BOTTOM LEFT SIDE
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
            if (old_position_object_nr <= 55)
                area[old_position_object_nr + 7 * i].bg_color = 3;
            if (area[old_position_object_nr + 7 * i].row == 8 || area[old_position_object_nr + 7 * i].column == 1)
                break;
        }

        // BOTTOM RIGHT SIDE
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
            if (old_position_object_nr <= 54)
                area[old_position_object_nr + 9 * i].bg_color = 3;
            if (area[old_position_object_nr + 9 * i].row == 8 || area[old_position_object_nr + 9 * i].column == 8)
                break;
        }
    }

    ///////////////// BLACK /////////////////
    if (area[old_position_object_nr].figure_color == 'B')
    {
        // TOP LEFT SIDE
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
            if (old_position_object_nr >= 9)
                area[old_position_object_nr - 9 * i].bg_color = 3;
            if (area[old_position_object_nr - 9 * i].row == 1 || area[old_position_object_nr - 9 * i].column == 1)
                break;
        }

        // TOP RIGHT SIDE
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
            if (old_position_object_nr >= 8)
                area[old_position_object_nr - 7 * i].bg_color = 3;
            if (area[old_position_object_nr - 7 * i].row == 1 || area[old_position_object_nr - 7 * i].column == 8)
                break;
        }

        // BOTTOM LEFT SIDE
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
            if (old_position_object_nr <= 55)
                area[old_position_object_nr + 7 * i].bg_color = 3;
            if (area[old_position_object_nr + 7 * i].row == 8 || area[old_position_object_nr + 7 * i].column == 1)
                break;
        }

        // BOTTOM RIGHT SIDE
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
            if (old_position_object_nr <= 54)
                area[old_position_object_nr + 9 * i].bg_color = 3;
            if (area[old_position_object_nr + 9 * i].row == 8 || area[old_position_object_nr + 9 * i].column == 8)
                break;
        }
    }
}
void paintAreaColorsRook()
{
    ///////////////// WHITE /////////////////
    if (area[old_position_object_nr].figure_color == 'W')
    {

        // TOP SIDE
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
            if (old_position_object_nr >= 8)
                area[old_position_object_nr - 8 * i].bg_color = 3;
            if (area[old_position_object_nr - 8 * i].row == 1)
                break;
        }

        // BOTTOM SIDE
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
            if (old_position_object_nr <= 55)
                area[old_position_object_nr + 8 * i].bg_color = 3;
            if (area[old_position_object_nr + 8 * i].row == 8)
                break;
        }

        // LEFT SIDE
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
            if (old_position_object_nr >= 1)
                area[old_position_object_nr - 1 * i].bg_color = 3;
            if (area[old_position_object_nr - 1 * i].column == 1)
                break;
        }

        // RIGHT SIDE
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
            if (old_position_object_nr <= 62)
                area[old_position_object_nr + 1 * i].bg_color = 3;
            if (area[old_position_object_nr + 1 * i].column == 8)
                break;
        }
    }

    ///////////////// BLACK /////////////////
    if (area[old_position_object_nr].figure_color == 'B')
    {
        // TOP SIDE
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
            if (old_position_object_nr >= 8)
                area[old_position_object_nr - 8 * i].bg_color = 3;
            if (area[old_position_object_nr - 8 * i].row == 1)
                break;
        }

        // BOTTOM SIDE
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
            if (old_position_object_nr <= 55)
                area[old_position_object_nr + 8 * i].bg_color = 3;
            if (area[old_position_object_nr + 8 * i].row == 8)
                break;
        }

        // LEFT SIDE
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
            if (old_position_object_nr >= 1)
                area[old_position_object_nr - 1 * i].bg_color = 3;
            if (area[old_position_object_nr - 1 * i].column == 1)
                break;
        }

        // RIGHT SIDE
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
            if (old_position_object_nr <= 62)
                area[old_position_object_nr + 1 * i].bg_color = 3;
            if (area[old_position_object_nr + 1 * i].column == 8)
                break;
        }
    }
}
void paintAreaColorsQueen()
{
    ///////////////// WHITE /////////////////
    if (area[old_position_object_nr].figure_color == 'W')
    {

        // TOP SIDE
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
            if (old_position_object_nr >= 8)
                area[old_position_object_nr - 8 * i].bg_color = 3;
            if (area[old_position_object_nr - 8 * i].row == 1)
                break;
        }

        // BOTTOM SIDE
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
            if (old_position_object_nr <= 55)
                area[old_position_object_nr + 8 * i].bg_color = 3;
            if (area[old_position_object_nr + 8 * i].row == 8)
                break;
        }

        // LEFT SIDE
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
            if (old_position_object_nr >= 1)
                area[old_position_object_nr - 1 * i].bg_color = 3;
            if (area[old_position_object_nr - 1 * i].column == 1)
                break;
        }

        // RIGHT SIDE
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
            if (old_position_object_nr <= 62)
                area[old_position_object_nr + 1 * i].bg_color = 3;
            if (area[old_position_object_nr + 1 * i].column == 8)
                break;
        }

        // TOP LEFT SIDE
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
            if (old_position_object_nr >= 9)
                area[old_position_object_nr - 9 * i].bg_color = 3;
            if (area[old_position_object_nr - 9 * i].row == 1 || area[old_position_object_nr - 9 * i].column == 1)
                break;
        }

        // TOP RIGHT SIDE
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
            if (old_position_object_nr >= 8)
                area[old_position_object_nr - 7 * i].bg_color = 3;
            if (area[old_position_object_nr - 7 * i].row == 1 || area[old_position_object_nr - 7 * i].column == 8)
                break;
        }

        // BOTTOM LEFT SIDE
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
            if (old_position_object_nr <= 55)
                area[old_position_object_nr + 7 * i].bg_color = 3;
            if (area[old_position_object_nr + 7 * i].row == 8 || area[old_position_object_nr + 7 * i].column == 1)
                break;
        }

        // BOTTOM RIGHT SIDE
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
            if (old_position_object_nr <= 54)
                area[old_position_object_nr + 9 * i].bg_color = 3;
            if (area[old_position_object_nr + 9 * i].row == 8 || area[old_position_object_nr + 9 * i].column == 8)
                break;
        }
    }

    ///////////////// BLACK /////////////////
    if (area[old_position_object_nr].figure_color == 'B')
    {
        // TOP SIDE
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
            if (old_position_object_nr >= 8)
                area[old_position_object_nr - 8 * i].bg_color = 3;
            if (area[old_position_object_nr - 8 * i].row == 1)
                break;
        }

        // BOTTOM SIDE
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
            if (old_position_object_nr <= 55)
                area[old_position_object_nr + 8 * i].bg_color = 3;
            if (area[old_position_object_nr + 8 * i].row == 8)
                break;
        }

        // LEFT SIDE
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
            if (old_position_object_nr >= 1)
                area[old_position_object_nr - 1 * i].bg_color = 3;
            if (area[old_position_object_nr - 1 * i].column == 1)
                break;
        }

        // RIGHT SIDE
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
            if (old_position_object_nr <= 62)
                area[old_position_object_nr + 1 * i].bg_color = 3;
            if (area[old_position_object_nr + 1 * i].column == 8)
                break;
        }

        // TOP LEFT SIDE
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
            if (old_position_object_nr >= 9)
                area[old_position_object_nr - 9 * i].bg_color = 3;
            if (area[old_position_object_nr - 9 * i].row == 1 || area[old_position_object_nr - 9 * i].column == 1)
                break;
        }

        // TOP RIGHT SIDE
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
            if (old_position_object_nr >= 8)
                area[old_position_object_nr - 7 * i].bg_color = 3;
            if (area[old_position_object_nr - 7 * i].row == 1 || area[old_position_object_nr - 7 * i].column == 8)
                break;
        }

        // BOTTOM LEFT SIDE
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
            if (old_position_object_nr <= 55)
                area[old_position_object_nr + 7 * i].bg_color = 3;
            if (area[old_position_object_nr + 7 * i].row == 8 || area[old_position_object_nr + 7 * i].column == 1)
                break;
        }

        // BOTTOM RIGHT SIDE
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
            if (old_position_object_nr <= 54)
                area[old_position_object_nr + 9 * i].bg_color = 3;
            if (area[old_position_object_nr + 9 * i].row == 8 || area[old_position_object_nr + 9 * i].column == 8)
                break;
        }
    }
}
void paintAreaColorsKing()
{
    ///////////////// WHITE /////////////////
    if (area[old_position_object_nr].figure_color == 'W')
    {
        // TOP SIDE
        if (area[old_position_object_nr].row > 1)
        {
            if (area[old_position_object_nr - 8].figure_color == 'B')
                area[old_position_object_nr - 8].bg_color = 4;
            else if (area[old_position_object_nr - 8].figure_color == 'E')
                area[old_position_object_nr - 8].bg_color = 3;
        }

        // BOTTOM SIDE
        if (area[old_position_object_nr].row < 8)
        {
            if (area[old_position_object_nr + 8].figure_color == 'B')
                area[old_position_object_nr + 8].bg_color = 4;
            else if (area[old_position_object_nr + 8].figure_color == 'E')
                area[old_position_object_nr + 8].bg_color = 3;
        }

        // LEFT SIDE
        if (area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr - 1].figure_color == 'B')
                area[old_position_object_nr - 1].bg_color = 4;
            else if (area[old_position_object_nr - 1].figure_color == 'E')
                area[old_position_object_nr - 1].bg_color = 3;
        }

        // RIGHT SIDE
        if (area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + 1].figure_color == 'B')
                area[old_position_object_nr + 1].bg_color = 4;
            else if (area[old_position_object_nr + 1].figure_color == 'E')
                area[old_position_object_nr + 1].bg_color = 3;
        }

        // TOP LEFT SIDE
        if (area[old_position_object_nr].row > 1 && area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr - 9].figure_color == 'B')
                area[old_position_object_nr - 9].bg_color = 4;
            else if (area[old_position_object_nr - 9].figure_color == 'E')
                area[old_position_object_nr - 9].bg_color = 3;
        }

        // TOP RIGHT SIDE
        if (area[old_position_object_nr].row > 1 && area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr - 7].figure_color == 'B')
                area[old_position_object_nr - 7].bg_color = 4;
            else if (area[old_position_object_nr - 7].figure_color == 'E')
                area[old_position_object_nr - 7].bg_color = 3;
        }

        // BOTTOM LEFT SIDE
        if (area[old_position_object_nr].row < 8 && area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr + 7].figure_color == 'B')
                area[old_position_object_nr + 7].bg_color = 4;
            else if (area[old_position_object_nr + 7].figure_color == 'E')
                area[old_position_object_nr + 7].bg_color = 3;
        }

        // BOTTOM RIGHT SIDE
        if (area[old_position_object_nr].row < 8 && area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + 9].figure_color == 'B')
                area[old_position_object_nr + 9].bg_color = 4;
        }
        else if (area[old_position_object_nr + 9].figure_color == 'E')
            area[old_position_object_nr + 9].bg_color = 3;

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
            if (area[old_position_object_nr - 8].figure_color == 'W')
                area[old_position_object_nr - 8].bg_color = 4;
            else if (area[old_position_object_nr - 8].figure_color == 'E')
                area[old_position_object_nr - 8].bg_color = 3;
        }

        // BOTTOM SIDE
        if (area[old_position_object_nr].row < 8)
        {
            if (area[old_position_object_nr + 8].figure_color == 'W')
                area[old_position_object_nr + 8].bg_color = 4;
            else if (area[old_position_object_nr + 8].figure_color == 'E')
                area[old_position_object_nr + 8].bg_color = 3;
        }

        // LEFT SIDE
        if (area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr - 1].figure_color == 'W')
                area[old_position_object_nr - 1].bg_color = 4;
            else if (area[old_position_object_nr - 1].figure_color == 'E')
                area[old_position_object_nr - 1].bg_color = 3;
        }

        // RIGHT SIDE
        if (area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + 1].figure_color == 'W')
                area[old_position_object_nr + 1].bg_color = 4;
            else if (area[old_position_object_nr + 1].figure_color == 'E')
                area[old_position_object_nr + 1].bg_color = 3;
        }

        // TOP LEFT SIDE
        if (area[old_position_object_nr].row > 1 && area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr - 9].figure_color == 'W')
                area[old_position_object_nr - 9].bg_color = 4;
            else if (area[old_position_object_nr - 9].figure_color == 'E')
                area[old_position_object_nr - 9].bg_color = 3;
        }

        // TOP RIGHT SIDE
        if (area[old_position_object_nr].row > 1 && area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr - 7].figure_color == 'W')
                area[old_position_object_nr - 7].bg_color = 4;
            else if (area[old_position_object_nr - 7].figure_color == 'E')
                area[old_position_object_nr - 7].bg_color = 3;
        }

        // BOTTOM LEFT SIDE
        if (area[old_position_object_nr].row < 8 && area[old_position_object_nr].column > 1)
        {
            if (area[old_position_object_nr + 7].figure_color == 'W')
                area[old_position_object_nr + 7].bg_color = 4;
            else if (area[old_position_object_nr + 7].figure_color == 'E')
                area[old_position_object_nr + 7].bg_color = 3;
        }

        // BOTTOM RIGHT SIDE
        if (area[old_position_object_nr].row < 8 && area[old_position_object_nr].column < 8)
        {
            if (area[old_position_object_nr + 9].figure_color == 'W')
                area[old_position_object_nr + 9].bg_color = 4;
            else if (area[old_position_object_nr + 9].figure_color == 'E')
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
        /////////// STARTED POSITION ///////////
        if (virtual_area[virtual_position_object_nr].row == 7)
        {
            // TOP LEFT8
            if (virtual_area[virtual_position_object_nr - 9].figure_color != 'W' && virtual_area[virtual_position_object_nr].column > 1)
                virtual_area[virtual_position_object_nr - 9].bg_color = 4;
            // TOP RIGHT
            if (virtual_area[virtual_position_object_nr - 7].figure_color != 'W' && virtual_area[virtual_position_object_nr].column < 8)
                virtual_area[virtual_position_object_nr - 7].bg_color = 4;
        }
        /////////// OTHER POSITION ///////////
        else
        {
            // TOP LEFT
            if (virtual_area[virtual_position_object_nr - 9].figure_color != 'W' && virtual_area[virtual_position_object_nr].column > 1)
                virtual_area[virtual_position_object_nr - 9].bg_color = 4;

            // TOP RIGHT
            if (virtual_area[virtual_position_object_nr - 7].figure_color != 'W' && virtual_area[virtual_position_object_nr].column < 8)
                virtual_area[virtual_position_object_nr - 7].bg_color = 4;
        }
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
                if (virtual_area[virtual_position_object_nr - 17].figure_color != 'W')
                    virtual_area[virtual_position_object_nr - 17].bg_color = 4;
            }
        }

        // TOP TOP RIGHT
        if (virtual_position_object_nr >= 16)
        {
            if (virtual_area[virtual_position_object_nr].column <= 7)
            {
                if (virtual_area[virtual_position_object_nr - 15].figure_color != 'W')
                    virtual_area[virtual_position_object_nr - 15].bg_color = 4;
            }
        }

        // BOTTOM BOTTOM LEFT
        if (virtual_position_object_nr <= 47)
        {
            if (virtual_area[virtual_position_object_nr].column >= 2)
            {
                if (virtual_area[virtual_position_object_nr + 15].figure_color != 'W')
                    virtual_area[virtual_position_object_nr + 15].bg_color = 4;
            }
        }

        // BOTTOM BOTTOM RIGHT
        if (virtual_position_object_nr <= 46)
        {
            if (virtual_area[virtual_position_object_nr].column <= 7)
            {
                if (virtual_area[virtual_position_object_nr + 17].figure_color != 'W')
                    virtual_area[virtual_position_object_nr + 17].bg_color = 4;
            }
        }

        // LEFT LEFT TOP
        if (virtual_position_object_nr >= 10)
        {
            if (virtual_area[virtual_position_object_nr].column >= 3)
            {
                if (virtual_area[virtual_position_object_nr - 10].figure_color != 'W')
                    virtual_area[virtual_position_object_nr - 10].bg_color = 4;
            }
        }

        // LEFT LEFT BOTTOM
        if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr].column >= 3)
            {
                if (virtual_area[virtual_position_object_nr + 6].figure_color != 'W')
                    virtual_area[virtual_position_object_nr + 6].bg_color = 4;
            }
        }

        // RIGH RIGHT TOP
        if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr].column <= 6)
            {
                if (virtual_area[virtual_position_object_nr - 6].figure_color != 'W')
                    virtual_area[virtual_position_object_nr - 6].bg_color = 4;
            }
        }

        // RIGH RIGHT BOTTOM
        if (virtual_position_object_nr <= 53)
        {
            if (virtual_area[virtual_position_object_nr].column <= 6)
            {
                if (virtual_area[virtual_position_object_nr + 10].figure_color != 'W')
                    virtual_area[virtual_position_object_nr + 10].bg_color = 4;
            }
        }
    }
}
void paintVirtualAreaColorsWhiteBishop()
{

    if (virtual_area[virtual_position_object_nr].figure_color == 'W')
    {

        // TOP LEFT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 1 || virtual_area[virtual_position_object_nr].column == 1)
                break;
            if (virtual_area[virtual_position_object_nr - 9 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 9 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr - 9 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr - 9 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 9 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 9)
            {
                virtual_area[virtual_position_object_nr - 9 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 9 * i].row == 1 || virtual_area[virtual_position_object_nr - 9 * i].column == 1)
                break;
        }

        // TOP RIGHT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 1 || virtual_area[virtual_position_object_nr].column == 8)
                break;
            if (virtual_area[virtual_position_object_nr - 7 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 7 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr - 7 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr - 7 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 7 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 8)
            {
                virtual_area[virtual_position_object_nr - 7 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 7 * i].row == 1 || virtual_area[virtual_position_object_nr - 7 * i].column == 8)
                break;
        }

        // BOTTOM LEFT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 8 || virtual_area[virtual_position_object_nr].column == 1)
                break;
            if (virtual_area[virtual_position_object_nr + 7 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 7 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr + 7 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr + 7 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 7 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 55)
            {
                virtual_area[virtual_position_object_nr + 7 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 7 * i].row == 8 || virtual_area[virtual_position_object_nr + 7 * i].column == 1)
                break;
        }

        // BOTTOM RIGHT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 8 || virtual_area[virtual_position_object_nr].column == 8)
                break;
            if (virtual_area[virtual_position_object_nr + 9 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 9 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr + 9 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr + 9 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 9 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 54)
            {
                virtual_area[virtual_position_object_nr + 9 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 9 * i].row == 8 || virtual_area[virtual_position_object_nr + 9 * i].column == 8)
                break;
        }
    }
}
void paintVirtualAreaColorsWhiteRook()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'W')
    {

        // TOP SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 1)
                break;
            if (virtual_area[virtual_position_object_nr - 8 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 8 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr - 8 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr - 8 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 8 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 8)
            {
                virtual_area[virtual_position_object_nr - 8 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 8 * i].row == 1)
                break;
        }

        // BOTTOM SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 8)
                break;
            if (virtual_area[virtual_position_object_nr + 8 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 8 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr + 8 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr + 8 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 8 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 55)
            {
                virtual_area[virtual_position_object_nr + 8 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 8 * i].row == 8)
                break;
        }

        // LEFT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].column == 1)
                break;
            if (virtual_area[virtual_position_object_nr - 1 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 1 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr - 1 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr - 1 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 1 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 1)
            {
                virtual_area[virtual_position_object_nr - 1 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 1 * i].column == 1)
                break;
        }

        // RIGHT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].column == 8)
                break;
            if (virtual_area[virtual_position_object_nr + 1 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 1 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr + 1 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr + 1 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 1 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 62)
            {
                virtual_area[virtual_position_object_nr + 1 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 1 * i].column == 8)
                break;
        }
    }
}
void paintVirtualAreaColorsWhiteQueen()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'W')
    {

        // TOP SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 1)
                break;
            if (virtual_area[virtual_position_object_nr - 8 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 8 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr - 8 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr - 8 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 8 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 8)
            {
                virtual_area[virtual_position_object_nr - 8 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 8 * i].row == 1)
                break;
        }

        // BOTTOM SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 8)
                break;
            if (virtual_area[virtual_position_object_nr + 8 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 8 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr + 8 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr + 8 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 8 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 55)
            {
                virtual_area[virtual_position_object_nr + 8 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 8 * i].row == 8)
                break;
        }

        // LEFT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].column == 1)
                break;
            if (virtual_area[virtual_position_object_nr - 1 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 1 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr - 1 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr - 1 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 1 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 1)
            {
                virtual_area[virtual_position_object_nr - 1 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 1 * i].column == 1)
                break;
        }

        // RIGHT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].column == 8)
                break;
            if (virtual_area[virtual_position_object_nr + 1 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 1 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr + 1 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr + 1 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 1 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 62)
            {
                virtual_area[virtual_position_object_nr + 1 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 1 * i].column == 8)
                break;
        }

        // TOP LEFT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 1 || virtual_area[virtual_position_object_nr].column == 1)
                break;
            if (virtual_area[virtual_position_object_nr - 9 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 9 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr - 9 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr - 9 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 9 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 9)
            {
                virtual_area[virtual_position_object_nr - 9 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 9 * i].row == 1 || virtual_area[virtual_position_object_nr - 9 * i].column == 1)
                break;
        }

        // TOP RIGHT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 1 || virtual_area[virtual_position_object_nr].column == 8)
                break;
            if (virtual_area[virtual_position_object_nr - 7 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 7 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr - 7 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr - 7 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 7 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 8)
            {
                virtual_area[virtual_position_object_nr - 7 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 7 * i].row == 1 || virtual_area[virtual_position_object_nr - 7 * i].column == 8)
                break;
        }

        // BOTTOM LEFT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 8 || virtual_area[virtual_position_object_nr].column == 1)
                break;
            if (virtual_area[virtual_position_object_nr + 7 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 7 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr + 7 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr + 7 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 7 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 55)
            {
                virtual_area[virtual_position_object_nr + 7 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 7 * i].row == 8 || virtual_area[virtual_position_object_nr + 7 * i].column == 1)
                break;
        }

        // BOTTOM RIGHT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 8 || virtual_area[virtual_position_object_nr].column == 8)
                break;
            if (virtual_area[virtual_position_object_nr + 9 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 9 * i].figure_color == 'B')
                {
                    if (virtual_area[virtual_position_object_nr + 9 * (i + 1)].big_figure != "blackKing")
                    {
                        virtual_area[virtual_position_object_nr + 9 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 9 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 54)
            {
                virtual_area[virtual_position_object_nr + 9 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 9 * i].row == 8 || virtual_area[virtual_position_object_nr + 9 * i].column == 8)
                break;
        }
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
        }

        // BOTTOM SIDE
        if (virtual_area[virtual_position_object_nr].row < 8)
        {
            if (virtual_area[virtual_position_object_nr + 8].figure_color != 'W')
                virtual_area[virtual_position_object_nr + 8].bg_color = 4;
        }

        // LEFT SIDE
        if (virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr - 1].figure_color != 'W')
                virtual_area[virtual_position_object_nr - 1].bg_color = 4;
        }

        // RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + 1].figure_color != 'W')
                virtual_area[virtual_position_object_nr + 1].bg_color = 4;
        }

        // TOP LEFT SIDE
        if (virtual_area[virtual_position_object_nr].row > 1 && virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr - 9].figure_color != 'W')
                virtual_area[virtual_position_object_nr - 9].bg_color = 4;
        }

        // TOP RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].row > 1 && virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr - 7].figure_color != 'W')
                virtual_area[virtual_position_object_nr - 7].bg_color = 4;
        }

        // BOTTOM LEFT SIDE
        if (virtual_area[virtual_position_object_nr].row < 8 && virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr + 7].figure_color != 'W')
                virtual_area[virtual_position_object_nr + 7].bg_color = 4;
        }

        // BOTTOM RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].row < 8 && virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + 9].figure_color != 'W')
                virtual_area[virtual_position_object_nr + 9].bg_color = 4;
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
        /////////// STARTED POSITION ///////////
        if (virtual_area[virtual_position_object_nr].row == 2)
        {
            // TOP LEFT
            if (virtual_area[virtual_position_object_nr + 7].figure_color != 'B' && virtual_area[virtual_position_object_nr].column > 1)
                virtual_area[virtual_position_object_nr + 7].bg_color = 4;
            // TOP RIGHT
            if (virtual_area[virtual_position_object_nr + 9].figure_color != 'B' && virtual_area[virtual_position_object_nr].column < 8)
                virtual_area[virtual_position_object_nr + 9].bg_color = 4;
        }
        /////////// OTHER POSITION ///////////
        else
        {
            // TOP LEFT
            if (virtual_area[virtual_position_object_nr + 7].figure_color != 'B' && virtual_area[virtual_position_object_nr].column > 1)
                virtual_area[virtual_position_object_nr + 7].bg_color = 4;

            // TOP RIGHT
            if (virtual_area[virtual_position_object_nr + 9].figure_color != 'B' && virtual_area[virtual_position_object_nr].column < 8)
                virtual_area[virtual_position_object_nr + 9].bg_color = 4;
        }
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
                if (virtual_area[virtual_position_object_nr - 17].figure_color != 'B')
                    virtual_area[virtual_position_object_nr - 17].bg_color = 4;
            }
        }

        // TOP TOP RIGHT
        if (virtual_position_object_nr >= 16)
        {
            if (virtual_area[virtual_position_object_nr].column <= 7)
            {
                if (virtual_area[virtual_position_object_nr - 15].figure_color != 'B')
                    virtual_area[virtual_position_object_nr - 15].bg_color = 4;
            }
        }

        // BOTTOM BOTTOM LEFT
        if (virtual_position_object_nr <= 47)
        {
            if (virtual_area[virtual_position_object_nr].column >= 2)
            {
                if (virtual_area[virtual_position_object_nr + 15].figure_color != 'B')
                    virtual_area[virtual_position_object_nr + 15].bg_color = 4;
            }
        }

        // BOTTOM BOTTOM RIGHT
        if (virtual_position_object_nr <= 46)
        {
            if (virtual_area[virtual_position_object_nr].column <= 7)
            {
                if (virtual_area[virtual_position_object_nr + 17].figure_color != 'B')
                    virtual_area[virtual_position_object_nr + 17].bg_color = 4;
            }
        }

        // LEFT LEFT TOP
        if (virtual_position_object_nr >= 10)
        {
            if (virtual_area[virtual_position_object_nr].column >= 3)
            {
                if (virtual_area[virtual_position_object_nr - 10].figure_color != 'B')
                    virtual_area[virtual_position_object_nr - 10].bg_color = 4;
            }
        }

        // LEFT LEFT BOTTOM
        if (virtual_position_object_nr <= 55)
        {
            if (virtual_area[virtual_position_object_nr].column >= 3)
            {
                if (virtual_area[virtual_position_object_nr + 6].figure_color != 'B')
                    virtual_area[virtual_position_object_nr + 6].bg_color = 4;
            }
        }

        // RIGH RIGHT TOP
        if (virtual_position_object_nr >= 8)
        {
            if (virtual_area[virtual_position_object_nr].column <= 6)
            {
                if (virtual_area[virtual_position_object_nr - 6].figure_color != 'B')
                    virtual_area[virtual_position_object_nr - 6].bg_color = 4;
            }
        }

        // RIGH RIGHT BOTTOM
        if (virtual_position_object_nr <= 53)
        {
            if (virtual_area[virtual_position_object_nr].column <= 6)
            {
                if (virtual_area[virtual_position_object_nr + 10].figure_color != 'B')
                    virtual_area[virtual_position_object_nr + 10].bg_color = 4;
            }
        }
    }
}
void paintVirtualAreaColorsBlackBishop()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'B')
    {

        // TOP LEFT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 1 || virtual_area[virtual_position_object_nr].column == 1)
                break;
            if (virtual_area[virtual_position_object_nr - 9 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 9 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr - 9 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr - 9 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 9 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 9)
            {
                virtual_area[virtual_position_object_nr - 9 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 9 * i].row == 1 || virtual_area[virtual_position_object_nr - 9 * i].column == 1)
                break;
        }

        // TOP RIGHT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 1 || virtual_area[virtual_position_object_nr].column == 8)
                break;
            if (virtual_area[virtual_position_object_nr - 7 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 7 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr - 7 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr - 7 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 7 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 8)
            {
                virtual_area[virtual_position_object_nr - 7 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 7 * i].row == 1 || virtual_area[virtual_position_object_nr - 7 * i].column == 8)
                break;
        }

        // BOTTOM LEFT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 8 || virtual_area[virtual_position_object_nr].column == 1)
                break;
            if (virtual_area[virtual_position_object_nr + 7 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 7 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr + 7 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr + 7 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 7 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 55)
            {
                virtual_area[virtual_position_object_nr + 7 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 7 * i].row == 8 || virtual_area[virtual_position_object_nr + 7 * i].column == 1)
                break;
        }

        // BOTTOM RIGHT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 8 || virtual_area[virtual_position_object_nr].column == 8)
                break;
            if (virtual_area[virtual_position_object_nr + 9 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 9 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr + 9 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr + 9 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 9 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 54)
            {
                virtual_area[virtual_position_object_nr + 9 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 9 * i].row == 8 || virtual_area[virtual_position_object_nr + 9 * i].column == 8)
                break;
        }
    }
}
void paintVirtualAreaColorsBlackRook()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'B')
    {
        // TOP SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 1)
                break;
            if (virtual_area[virtual_position_object_nr - 8 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 8 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr - 8 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr - 8 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 8 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 8)
            {
                virtual_area[virtual_position_object_nr - 8 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 8 * i].row == 1)
                break;
        }

        // BOTTOM SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 8)
                break;
            if (virtual_area[virtual_position_object_nr + 8 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 8 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr + 8 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr + 8 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 8 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 55)
            {
                virtual_area[virtual_position_object_nr + 8 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 8 * i].row == 8)
                break;
        }

        // LEFT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].column == 1)
                break;
            if (virtual_area[virtual_position_object_nr - 1 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 1 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr - 1 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr - 1 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 1 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 1)
            {
                virtual_area[virtual_position_object_nr - 1 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 1 * i].column == 1)
                break;
        }

        // RIGHT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].column == 8)
                break;
            if (virtual_area[virtual_position_object_nr + 1 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 1 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr + 1 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr + 1 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 1 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 62)
            {
                virtual_area[virtual_position_object_nr + 1 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 1 * i].column == 8)
                break;
        }
    }
}
void paintVirtualAreaColorsBlackQueen()
{
    if (virtual_area[virtual_position_object_nr].figure_color == 'B')
    {
        // TOP SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 1)
                break;
            if (virtual_area[virtual_position_object_nr - 8 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 8 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr - 8 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr - 8 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 8 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 8)
            {
                virtual_area[virtual_position_object_nr - 8 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 8 * i].row == 1)
                break;
        }

        // BOTTOM SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 8)
                break;
            if (virtual_area[virtual_position_object_nr + 8 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 8 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr + 8 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr + 8 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 8 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 55)
            {
                virtual_area[virtual_position_object_nr + 8 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 8 * i].row == 8)
                break;
        }

        // LEFT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].column == 1)
                break;
            if (virtual_area[virtual_position_object_nr - 1 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 1 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr - 1 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr - 1 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 1 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 1)
            {
                virtual_area[virtual_position_object_nr - 1 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 1 * i].column == 1)
                break;
        }

        // RIGHT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].column == 8)
                break;
            if (virtual_area[virtual_position_object_nr + 1 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 1 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr + 1 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr + 1 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 1 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 62)
            {
                virtual_area[virtual_position_object_nr + 1 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 1 * i].column == 8)
                break;
        }

        // TOP LEFT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 1 || virtual_area[virtual_position_object_nr].column == 1)
                break;
            if (virtual_area[virtual_position_object_nr - 9 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 9 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr - 9 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr - 9 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 9 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 9)
            {
                virtual_area[virtual_position_object_nr - 9 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 9 * i].row == 1 || virtual_area[virtual_position_object_nr - 9 * i].column == 1)
                break;
        }

        // TOP RIGHT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 1 || virtual_area[virtual_position_object_nr].column == 8)
                break;
            if (virtual_area[virtual_position_object_nr - 7 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr - 7 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr - 7 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr - 7 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr - 7 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr >= 8)
            {
                virtual_area[virtual_position_object_nr - 7 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr - 7 * i].row == 1 || virtual_area[virtual_position_object_nr - 7 * i].column == 8)
                break;
        }

        // BOTTOM LEFT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 8 || virtual_area[virtual_position_object_nr].column == 1)
                break;
            if (virtual_area[virtual_position_object_nr + 7 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 7 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr + 7 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr + 7 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 7 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 55)
            {
                virtual_area[virtual_position_object_nr + 7 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 7 * i].row == 8 || virtual_area[virtual_position_object_nr + 7 * i].column == 1)
                break;
        }

        // BOTTOM RIGHT SIDE
        for (int i = 1; i <= 8; i++)
        {
            if (virtual_area[virtual_position_object_nr].row == 8 || virtual_area[virtual_position_object_nr].column == 8)
                break;
            if (virtual_area[virtual_position_object_nr + 9 * i].figure_color != 'E')
            {
                if (virtual_area[virtual_position_object_nr + 9 * i].figure_color == 'W')
                {
                    if (virtual_area[virtual_position_object_nr + 9 * (i + 1)].big_figure != "whiteKing")
                    {
                        virtual_area[virtual_position_object_nr + 9 * i].bg_color = 4;
                        break;
                    }
                    else
                    {
                        virtual_area[virtual_position_object_nr + 9 * i].bg_color = 5;
                        break;
                    }
                }
                else
                    break;
            }
            if (virtual_position_object_nr <= 54)
            {
                virtual_area[virtual_position_object_nr + 9 * i].bg_color = 4;
            }
            if (virtual_area[virtual_position_object_nr + 9 * i].row == 8 || virtual_area[virtual_position_object_nr + 9 * i].column == 8)
                break;
        }
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
        }

        // BOTTOM SIDE
        if (virtual_area[virtual_position_object_nr].row < 8)
        {
            if (virtual_area[virtual_position_object_nr + 8].figure_color != 'B')
                virtual_area[virtual_position_object_nr + 8].bg_color = 4;
        }

        // LEFT SIDE
        if (virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr - 1].figure_color != 'B')
                virtual_area[virtual_position_object_nr - 1].bg_color = 4;
        }

        // RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + 1].figure_color != 'B')
                virtual_area[virtual_position_object_nr + 1].bg_color = 4;
        }

        // TOP LEFT SIDE
        if (virtual_area[virtual_position_object_nr].row > 1 && virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr - 9].figure_color != 'B')
                virtual_area[virtual_position_object_nr - 9].bg_color = 4;
        }

        // TOP RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].row > 1 && virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr - 7].figure_color != 'B')
                virtual_area[virtual_position_object_nr - 7].bg_color = 4;
        }

        // BOTTOM LEFT SIDE
        if (virtual_area[virtual_position_object_nr].row < 8 && virtual_area[virtual_position_object_nr].column > 1)
        {
            if (virtual_area[virtual_position_object_nr + 7].figure_color != 'B')
                virtual_area[virtual_position_object_nr + 7].bg_color = 4;
        }

        // BOTTOM RIGHT SIDE
        if (virtual_area[virtual_position_object_nr].row < 8 && virtual_area[virtual_position_object_nr].column < 8)
        {
            if (virtual_area[virtual_position_object_nr + 9].figure_color != 'B')
                virtual_area[virtual_position_object_nr + 9].bg_color = 4;
        }
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
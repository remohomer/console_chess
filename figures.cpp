#include <iostream>
#include "figures.h"
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// BG COLOR
#define BLUE 0
#define AQUA 1

// FIGURE COLOR
#define EMPTY 69
#define WHITE 87
#define BLACK 66

using namespace std;

// ----------------- AREA -----------------
Area::Area(string pos, short r, short c, short started_bg_c, char started_f_c, char started_f, string started_b_f, short i, bool check, bool en, short b_c, char f_c, char f, string b_f)
{
    position = pos;
    row = r;
    column = c;
    started_bg_color = started_bg_c;
    started_figure_color = started_f_c;
    started_figure = started_f;
    started_big_figure = started_b_f;
    id = i;
    checking = check;
    en_passant = en;

    bg_color = b_c;
    figure_color = f_c;
    figure = f;
    big_figure = b_f;
}
Area::~Area()
{
}

void Area::show()
{
    if (id <= 9)
        cout << "0" << id;
    else
        cout << id;
    cout << " - " << position << " [" << row << "." << column << "]"
         << "\tbg color: " << bg_color << "\tfigure color: " << figure_color << "\tfigure: " << figure << "\tchecking: " << checking << "\ten_passant: " << en_passant << endl;
}

void Area::resetFigures()
{
    bg_color = started_bg_color;
    figure_color = started_figure_color;
    figure = started_figure;
    big_figure = started_big_figure;
}

void Area::resetBgColor()
{
    bg_color = started_bg_color;
}

void Area::resetChecking()
{
    checking = false;
}

void Area::resetEnPassant()
{
    en_passant = false;
}

void Area::drawArea()
{
    HANDLE hOut;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (bg_color == BLUE && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == BLUE && figure_color == BLACK || bg_color == BLUE && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
        cout << " " << figure << " ";
    }
    else if (bg_color == AQUA && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == AQUA && figure_color == BLACK || bg_color == AQUA && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
        cout << " " << figure << " ";
    }
    else if (bg_color == 2 && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == 2 && figure_color == BLACK || bg_color == 2 && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN);
        cout << " " << figure << " ";
    }
    else if (bg_color == 3 && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == 3 && figure_color == BLACK || bg_color == 3 && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN);
        cout << " " << figure << " ";
    }
    else if (bg_color == 4 && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == 4 && figure_color == BLACK || bg_color == 4 && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED);
        cout << " " << figure << " ";
    }
    else if (bg_color == 5 && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == 5 && figure_color == BLACK || bg_color == 5 && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE);
        cout << " " << figure << " ";
    }
    else if (bg_color == 6 && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == 6 && figure_color == BLACK || bg_color == 6 && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else
    {
        cout << "\nNiezdefiniowany kolor tla lub figury\n";
    }
}

void Area::drawAreaID()
{
    HANDLE hOut;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (bg_color == BLUE && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        if (id > 10)
            cout << " " << id-1;
        else
            cout << "  " << id-1;
    }
    else if (bg_color == BLUE && figure_color == BLACK || bg_color == BLUE && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
        if (id > 10)
            cout << " " << id-1;
        else
            cout << "  " << id-1;
    }
    else if (bg_color == AQUA && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        if (id > 10)
            cout << " " << id-1;
        else
            cout << "  " << id-1;
    }
    else if (bg_color == AQUA && figure_color == BLACK || bg_color == AQUA && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
        if (id > 10)
            cout << " " << id-1;
        else
            cout << "  " << id-1;
    }
    else
    {
        cout << "\nNiezdefiniowany kolor tla lub figury\n";
    }
}

void Area::drawAreaPosition()
{
    HANDLE hOut;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (bg_color == BLUE && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << position;
    }
    else if (bg_color == BLUE && figure_color == BLACK || bg_color == BLUE && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
        cout << " " << position;
    }
    else if (bg_color == AQUA && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << position;
    }
    else if (bg_color == AQUA && figure_color == BLACK || bg_color == AQUA && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
        cout << " " << position;
    }
    else
    {
        cout << "\nNiezdefiniowany kolor tla lub figury\n";
    }
}

void Area::drawAreaNR()
{
    HANDLE hOut;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (bg_color == BLUE && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << row << "." << column;
    }
    else if (bg_color == BLUE && figure_color == BLACK || bg_color == BLUE && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
        cout << row << "." << column;
    }
    else if (bg_color == AQUA && figure_color == WHITE)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << row << "." << column;
    }
    else if (bg_color == AQUA && figure_color == BLACK || bg_color == AQUA && figure_color == EMPTY)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
        cout << row << "." << column;
    }
    else
    {
        cout << "\nNiezdefiniowany kolor tla lub figury\n";
    }
}
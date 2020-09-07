#include <iostream>
#include "figures.h"
#include <stdlib.h>
#include <windows.h>
#include <time.h>

using namespace std;

// ----------------- AREA -----------------
Area::Area(string pos, short r, short c, short started_bg_c, char started_f_c, char started_f, string started_b_f, short i, short b_c, char f_c, char f, string b_f)
{
    position = pos;
    row = r;
    column = c;
    started_bg_color = started_bg_c;
    started_figure_color = started_f_c;
    started_figure = started_f;
    started_big_figure = started_b_f;
    id = i;

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
         << " | bg color: " << bg_color << " | started bg color: " << started_bg_color << " | figure color: " << figure_color << " | figure: " << figure << " | big figure: " << big_figure << endl;
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

void Area::drawArea()
{
    HANDLE hOut;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (bg_color == 0 && figure_color == 'W')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == 0 && figure_color == 'B' || bg_color == 0 && figure_color == 'E')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
        cout << " " << figure << " ";
    }
    else if (bg_color == 1 && figure_color == 'W')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == 1 && figure_color == 'B' || bg_color == 1 && figure_color == 'E')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
        cout << " " << figure << " ";
    }
    else if (bg_color == 2 && figure_color == 'W')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == 2 && figure_color == 'B' || bg_color == 2 && figure_color == 'E')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN);
        cout << " " << figure << " ";
    }
    else if (bg_color == 3 && figure_color == 'W')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == 3 && figure_color == 'B' || bg_color == 3 && figure_color == 'E')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN);
        cout << " " << figure << " ";
    }
    else if (bg_color == 4 && figure_color == 'W')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == 4 && figure_color == 'B' || bg_color == 4 && figure_color == 'E')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED);
        cout << " " << figure << " ";
    }
    else if (bg_color == 5 && figure_color == 'W')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << figure << " ";
    }
    else if (bg_color == 5 && figure_color == 'B' || bg_color == 5 && figure_color == 'E')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE);
        cout << " " << figure << " ";
    }
    else
    {
        cout << "\nNiezdefiniowany kolor tla lub figury\n";
    }
    cout << flush;
}

void Area::drawAreaID()
{
    HANDLE hOut;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (bg_color == 0 && figure_color == 'W')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        if (id > 10)
            cout << " " << id-1;
        else
            cout << "  " << id-1;
    }
    else if (bg_color == 0 && figure_color == 'B' || bg_color == 0 && figure_color == 'E')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
        if (id > 10)
            cout << " " << id-1;
        else
            cout << "  " << id-1;
    }
    else if (bg_color == 1 && figure_color == 'W')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        if (id > 10)
            cout << " " << id-1;
        else
            cout << "  " << id-1;
    }
    else if (bg_color == 1 && figure_color == 'B' || bg_color == 1 && figure_color == 'E')
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
    cout << flush;
}

void Area::drawAreaPosition()
{
    HANDLE hOut;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (bg_color == 0 && figure_color == 'W')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << position;
    }
    else if (bg_color == 0 && figure_color == 'B' || bg_color == 0 && figure_color == 'E')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
        cout << " " << position;
    }
    else if (bg_color == 1 && figure_color == 'W')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << " " << position;
    }
    else if (bg_color == 1 && figure_color == 'B' || bg_color == 1 && figure_color == 'E')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
        cout << " " << position;
    }
    else
    {
        cout << "\nNiezdefiniowany kolor tla lub figury\n";
    }
    cout << flush;
}

void Area::drawAreaNR()
{
    HANDLE hOut;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (bg_color == 0 && figure_color == 'W')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << row << "." << column;
    }
    else if (bg_color == 0 && figure_color == 'B' || bg_color == 0 && figure_color == 'E')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
        cout << row << "." << column;
    }
    else if (bg_color == 1 && figure_color == 'W')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << row << "." << column;
    }
    else if (bg_color == 1 && figure_color == 'B' || bg_color == 1 && figure_color == 'E')
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
        cout << row << "." << column;
    }
    else
    {
        cout << "\nNiezdefiniowany kolor tla lub figury\n";
    }
    cout << flush;
}
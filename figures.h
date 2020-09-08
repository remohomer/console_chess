#include <iostream>


using namespace std;



class Area
{
public:
    string position;
    short row, column;
    short bg_color;
    char figure_color;
    char figure;
    string big_figure;
    short id;
    bool checking;
    bool en_passant;

private:
    short started_bg_color;
    char started_figure_color;
    char started_figure;
    string started_big_figure;

public:

    Area(string="", short=0, short=0, short=0, char='E', char=' ', string="", short=0, bool=false, bool=false, short=0, char=' ', char=' ', string="");
    ~Area();

    void show();
    void resetFigures();
    void resetBgColor();
    void resetChecking();
    void resetEnPassant();
    void drawArea();

    void drawAreaID();
    void drawAreaPosition();
    void drawAreaNR();
};
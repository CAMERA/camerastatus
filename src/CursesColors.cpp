#include "CursesColors.hpp"

#include <ncurses.h>

CursesColors::CursesColors(){

}

CursesColors::~CursesColors(){

}

int CursesColors::initialize(){
    start_color();
    init_pair(CursesColors::CYANBLACK, COLOR_CYAN, COLOR_BLACK);
    init_pair(CursesColors::YELLOWBLACK, COLOR_YELLOW, COLOR_BLACK);
    init_pair(CursesColors::REDBLACK, COLOR_RED, COLOR_BLACK);
    init_pair(CursesColors::GREENBLACK, COLOR_GREEN, COLOR_BLACK);
}

int CursesColors::setColorPair(ColorPair cp){
  attron(COLOR_PAIR(cp));
  return 0;
}

int CursesColors::unsetColorPair(ColorPair cp){
  attroff(COLOR_PAIR(cp));
  return 0;
}

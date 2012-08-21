
#include "Box.hpp"
#include <time.h>

#include <ncurses.h>
#include "CursesColors.hpp"
#include "NightRiderSlider.hpp"


Box::Box(int startx,int starty, int height,int width,const char *title,
CursesColors *cp){
   mp_StartX = startx;
   mp_StartY = starty;
   mp_Height = height;
   mp_Width = width;
   if (title != NULL){
     mp_pTitle = new std::string(title);   
   }
   mp_pColors = cp;
   
}

Box::~Box(){
  if (mp_pTitle != NULL){
     delete mp_pTitle;
  }
  if (mp_pSlider != NULL){
      delete mp_pSlider;
  }
}

void Box::draw(){
   int i;
   mp_pColors->setColorPair(CursesColors::CYANBLACK);
   
   //draw upper left corner
   mvaddch(mp_StartY,mp_StartX, ACS_ULCORNER);
   
   //draw top horizontal line
   for ( i = 1; i < mp_Width; i++){
      addch(ACS_HLINE);
   }
   
   //draw upper right corner
  addch(ACS_URCORNER);
  
  //draw both vertical lines
  for ( i = 1; i < mp_Height ; i++)
  {
    mvaddch(mp_StartY + i, mp_StartX, ACS_VLINE);
    mvaddch(mp_StartY + i, mp_StartX+ mp_Width, ACS_VLINE);
  }
  
  //draw lower left corner
  mvaddch( mp_StartY + mp_Height, mp_StartX, ACS_LLCORNER);
  
  //draw lower horizontal line
  for ( i = 1; i < mp_Width; i++){
     addch(ACS_HLINE);
  }
  
  //draw lower right corner
  addch(ACS_LRCORNER);

  // starting 2 characters from upper left draw <* title *>
  mvaddstr(mp_StartY, mp_StartX + 2, "<");

  if (mp_pTitle != NULL)
  {
    addch(ACS_DIAMOND);
    addch(32);
    addstr(mp_pTitle->c_str());
    addch(32);
    addch('-');
    addch('-');
  }
  getyx(stdscr,mp_DateBlockY,mp_DateBlockX);
  update();
  
  mp_pColors->unsetColorPair(CursesColors::CYANBLACK);
}

/*
 * This method is called when the box should update itself.  The
 *  call can assume it's UI has not changed
 * @return none.
 */
void Box::update(){
    
    mp_pColors->setColorPair(CursesColors::CYANBLACK);
    
    move(mp_DateBlockY,mp_DateBlockX);
    std::string date = std::string(getDate());
    addch(' ');
    addstr(date.c_str());
    addch(32);
    addch(ACS_DIAMOND);
    addstr(">");  
    
    if (mp_pSlider == NULL){
        mp_pSlider = new NightRiderSlider(33,mp_Height,mp_pColors);
        mp_pSlider->draw();
    }else {
        mp_pSlider->update();
    }
    
    mp_pColors->unsetColorPair(CursesColors::CYANBLACK);
}

const char *Box::getDate(){
    time_t theTime = time(NULL);
    std::string timeStr = std::string(ctime((const time_t*)&theTime));
    return timeStr.substr(0,timeStr.length()-1).c_str();
}

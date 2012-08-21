#include "NightRiderSlider.hpp"
#include "CursesColors.hpp"
#include <ncurses.h>

NightRiderSlider::NightRiderSlider(int startX, int startY, CursesColors* cp){
    mp_pColors = cp;
    mp_StartX = startX;
    mp_StartY = startY;
    mp_LeftBracket = "[";
    mp_RightBracket = "]";
    mp_Bar = "---";
    mp_SliderXPos = 0;
    mp_SliderLength = 11;
    mp_SliderDirection = 1;
}

NightRiderSlider::~NightRiderSlider(){
    
}

void NightRiderSlider::draw(){
    update();
}

void NightRiderSlider::update(){
    int curX;
    int curY;
    mp_pColors->setColorPair(CursesColors::REDBLACK);
    mvaddstr(mp_StartY, mp_StartX, mp_LeftBracket.c_str());
    

    move(mp_StartY,mp_StartX+1);
    //need to put in appropriate spaces before 
    for (int i = 0; i < mp_SliderXPos;i++){
        addch(32);
    }
    //need to render slider
    addstr(mp_Bar.c_str());
    
    //need to render appropriate spaces after slider
    getyx(stdscr,curY,curX);
    for (int i = curX; i < mp_SliderLength+mp_StartX;i++){
        addch(32);
    }
    mvaddstr(mp_StartY,mp_StartX+mp_SliderLength, mp_RightBracket.c_str());
    mp_pColors->unsetColorPair(CursesColors::REDBLACK);
    
    mp_SliderXPos+=mp_SliderDirection;
    
    if (mp_SliderXPos >= (mp_SliderLength-mp_Bar.length()-1)){
        mp_SliderDirection = -1;
    }
    if (mp_SliderXPos <= 0){
        mp_SliderDirection = 1;
    }
}

/* 
 * File:   HorizontalJobBar.cpp
 * Author: churas
 * 
 * Created on August 16, 2012, 2:29 PM
 */

#include "HorizontalJobBar.hpp"
#include "CursesColors.hpp"
#include "Box.hpp"

#include <ncurses.h>
#include <math.h>

HorizontalJobBar::HorizontalJobBar(int startx,int starty, int width,CursesColors *colors) {
    mp_StartX = startx;
    mp_StartY = starty;
    mp_Width = width;
    mp_pColors = colors;
    mp_PercentLoad = 0;
    mp_LeftBracket = std::string("[");
    mp_RightBracket = std::string("%]");
}

HorizontalJobBar::~HorizontalJobBar() {
}

/**
 * This information is used to draw the contents of the horizontal bar
 * @param percentLoad number 0-100 denoting load anything above 100 will be considered 100
 *                    with respect to progress bar, but will be denoted up to 999 in
 *                    actual percentage value
 */
void HorizontalJobBar::updateLoad(int percentLoad){
    mp_PercentLoad = percentLoad;
    if (mp_PercentLoad > 999){
        mp_PercentLoad = 999;
    }
    if (mp_PercentLoad < 0){
        mp_PercentLoad = 0;
    }
}

/**
 * Draws the initial bar and calls update to fill the interior
 * Design is
 * [rrrqqqhhh ##%]
 * where rrrqqqhh is a breakdown of percentage of jobs that are
 * in running, queued, or held state and obtained from updateInputData call
 */
void HorizontalJobBar::draw(){
    mp_pColors->setColorPair(CursesColors::CYANBLACK);
    
    mvaddstr(mp_StartY,mp_StartX,mp_LeftBracket.c_str());
    mvaddstr(mp_StartY,(mp_StartX+mp_Width)-4,mp_RightBracket.c_str());
    mp_pColors->unsetColorPair(CursesColors::CYANBLACK);
    update();
}

/**
 * Renders the interior of horizontal bar namely the rrrrrrrqqqqhhh #% part from
 * data set in updateInputData() method.
 * where the rrrrqqqhhh is obtained by adding running,queued,held jobs into a total
 * the rrrqqqhhh is then rendered based on a percentage of each of these values divided
 * by the total.  The #% is the percentLoad value.  If this value is negative NA is
 * printed, if this value is greater then 999 only 999 is printed.
 */
void HorizontalJobBar::update(){
    //lets get the total value
    std::string rqhstr;
    mp_pColors->setColorPair(CursesColors::GREENBLACK);
    int availableWidth = mp_Width-(mp_LeftBracket.length()+mp_RightBracket.length()+7);
    //blank out data
    rqhstr = std::string(availableWidth+4,' ');
    mvaddstr(mp_StartY,mp_StartX+mp_LeftBracket.length(),rqhstr.c_str());

    //lets convert the mp_PercentLoad into number of characters to render by
    //taking availableWidth x (mp_PercentLoad x 0.1) values to a max value of 
    //availableWidth
    //The color of the bar will be blue if load is below 50%
    //yellow will be the color at 50-75% 
    //red will be the color above 75%
    int barWidth = (int)round((float)availableWidth * ((float)mp_PercentLoad*0.01));
    if (barWidth > availableWidth){
        barWidth = availableWidth;
    }
    if (mp_PercentLoad >= 50 && mp_PercentLoad < 75){
        mp_pColors->setColorPair(CursesColors::YELLOWBLACK);
    }
    if (mp_PercentLoad >= 75){
        mp_pColors->setColorPair(CursesColors::REDBLACK);
    }
    if (barWidth > 0){
        move(mp_StartY,mp_StartX+mp_LeftBracket.length());
        for (int i = 0; i < barWidth;i++){
            addch(ACS_BLOCK);
        }
    }

    char buff[4];
    snprintf(buff,4,"%d",mp_PercentLoad);
    
    std::string loadstr = (buff);
    loadstr = std::string(4-loadstr.length(),' ')+loadstr;
    mvaddstr(mp_StartY,mp_StartX+mp_LeftBracket.length()+availableWidth+1,loadstr.c_str());
    mp_pColors->unsetColorPair(CursesColors::CYANBLACK);
    mp_pColors->unsetColorPair(CursesColors::YELLOWBLACK);
    mp_pColors->unsetColorPair(CursesColors::REDBLACK);
    
}


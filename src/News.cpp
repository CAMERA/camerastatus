/* 
 * File:   News.cpp
 * Author: churas
 * 
 * Created on August 14, 2012, 1:36 PM
 */
#include <ncurses.h>
#include "CursesColors.hpp"


#include "News.hpp"
#include "StatusModel.hpp"
#include "URLStatusModel.hpp"

News::News(int startX, int startY, int height, int width, CursesColors *cp,
        StatusModel *model) {
    mp_StartX = startX;
    mp_StartY = startY;
    mp_Height = height;
    mp_Width = width;
    mp_pColors = cp;
    mp_pTitle = new std::string("News");
    mp_pStatusModel = model;
    mp_pClearString = new std::string(mp_Width - mp_StartX, ' ');

}

News::~News() {
    if (mp_pTitle != NULL) {
        delete mp_pTitle;
    }
    if (mp_pClearString != NULL) {
        delete mp_pClearString;
    }
}

void News::draw() {
    mp_pColors->setColorPair(CursesColors::CYANBLACK);

    //render horizontal line
    move(mp_StartY + mp_Height, mp_StartX);
    for (int i = 1; i < mp_Width; i++) {
        addch('_');
    }

    //render text in upper right corner
    move(mp_StartY, (mp_StartX + mp_Width)-(mp_pTitle->length() + 2));
    //render text
    addstr(mp_pTitle->c_str());
    mp_pColors->unsetColorPair(CursesColors::CYANBLACK);

    update();

}

void News::update() {
    mp_pColors->setColorPair(CursesColors::GREENBLACK);
    
    std::list<std::string> rList = mp_pStatusModel->getNews();
  
    if (rList.empty() == false) {
        int lineCntr = 1;
        std::list<std::string>::iterator i;
        for (i = rList.begin(); i != rList.end(); ++i) {
            std::string &entry = *i;
            std::string tempStr = std::string(entry);
            
            if (tempStr.compare("NA") == 0){
                continue;
            }
            
            mvaddstr(mp_StartY + lineCntr, mp_StartX, mp_pClearString->c_str());
            if (tempStr.length() >= mp_pClearString->length()-5){
                tempStr = tempStr.substr(0,mp_pClearString->length()-5)+std::string("...");
            }
            
            mvaddstr(mp_StartY + (lineCntr++), mp_StartX + 1, tempStr.c_str());

            //can only fit in top 3
            if (lineCntr >= mp_Height){
                break;
            }
        }
    }
    mp_pColors->unsetColorPair(CursesColors::GREENBLACK);
}


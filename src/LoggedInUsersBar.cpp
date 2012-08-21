/* 
 * File:   LoggedInUsersBar.cpp
 * Author: churas
 * 
 * Created on August 17, 2012, 1:56 PM
 */

#include <ncurses.h>

#include "LoggedInUsersBar.hpp"
#include "Box.hpp"
#include "CursesColors.hpp"
#include "StatusModel.hpp"
#include "StringUtil.hpp"

LoggedInUsersBar::LoggedInUsersBar(int startx, int starty, int width,CursesColors *colors,StatusModel *sm) {
    mp_StartX = startx;
    mp_StartY = starty;
    mp_Width = width;
    mp_pColors = colors;
    mp_pStatusModel = sm;
    mp_LoginLabel = std::string("# Logged in users: ");
    mp_LastLoginLabel = std::string(" --  Last login: ");
    mp_LastLoginClear = std::string(37,' ');
}

LoggedInUsersBar::~LoggedInUsersBar() {
    
}

void LoggedInUsersBar::draw(){
    mp_pColors->setColorPair(CursesColors::CYANBLACK);
    mvaddstr(mp_StartY,mp_StartX+1,mp_LoginLabel.c_str());
    mvaddstr(mp_StartY,mp_StartX+4+mp_LoginLabel.length(),mp_LastLoginLabel.c_str());
    mp_pColors->setColorPair(CursesColors::CYANBLACK);
    update();
}

void LoggedInUsersBar::update(){
    StringUtil stringUtil;
    mp_pColors->setColorPair(CursesColors::CYANBLACK);
    
    move(mp_StartY,mp_StartX+mp_LoginLabel.length());
    addstr(stringUtil.getIntAsPaddedString(mp_pStatusModel->getLoggedInUsers(),999,4));
    
    move(mp_StartY,mp_StartX+4+mp_LoginLabel.length()+mp_LastLoginLabel.length());
    addstr(mp_LastLoginClear.c_str());
    
    move(mp_StartY,mp_StartX+4+mp_LoginLabel.length()+mp_LastLoginLabel.length());
    
    std::string lastLogin = std::string(mp_pStatusModel->getLastLogin());
    if (lastLogin.length() >= mp_LastLoginClear.length()){
        lastLogin = lastLogin.substr(0,mp_LastLoginClear.length()-3)+std::string("...");
    }
    
    addstr(lastLogin.c_str());
    mp_pColors->unsetColorPair(CursesColors::CYANBLACK);
}



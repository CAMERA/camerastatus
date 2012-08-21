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
#include "WorkflowsRunBar.hpp"

WorkflowsRunBar::WorkflowsRunBar(int startx, int starty, int width,CursesColors *colors,StatusModel *sm) {
    mp_StartX = startx;
    mp_StartY = starty;
    mp_Width = width;
    mp_pColors = colors;
    mp_pStatusModel = sm;
    mp_WorkflowsRunLabel = std::string("# Workflows run: ");
    mp_LastSubmittedLabel = std::string(" --  Last workflow: ");
    mp_LastSubmittedClear = std::string(34,' ');
}

WorkflowsRunBar::~WorkflowsRunBar() {
    
}

void WorkflowsRunBar::draw(){
    mp_pColors->setColorPair(CursesColors::CYANBLACK);
    mvaddstr(mp_StartY,mp_StartX+1,mp_WorkflowsRunLabel.c_str());
    mvaddstr(mp_StartY,mp_StartX+6+mp_WorkflowsRunLabel.length(),mp_LastSubmittedLabel.c_str());
    mp_pColors->setColorPair(CursesColors::CYANBLACK);
    update();
}

void WorkflowsRunBar::update(){
    StringUtil stringUtil;
    mp_pColors->setColorPair(CursesColors::CYANBLACK);
    
    move(mp_StartY,mp_StartX+mp_WorkflowsRunLabel.length());
    addstr(stringUtil.getIntAsPaddedString(mp_pStatusModel->getNumberWorkflowsRun(),99999,6));
    
    move(mp_StartY,mp_StartX+6+mp_WorkflowsRunLabel.length()+mp_LastSubmittedLabel.length());
    addstr(mp_LastSubmittedClear.c_str());
    
    move(mp_StartY,mp_StartX+6+mp_WorkflowsRunLabel.length()+mp_LastSubmittedLabel.length());
    std::string lastWfSubmit = std::string(mp_pStatusModel->getLastWorkflowSubmission());
    if (lastWfSubmit.length() >= mp_LastSubmittedClear.length()){
        lastWfSubmit = lastWfSubmit.substr(0,mp_LastSubmittedClear.length()-3)+std::string("...");
    }
    addstr(lastWfSubmit.c_str());
    mp_pColors->unsetColorPair(CursesColors::CYANBLACK);
}



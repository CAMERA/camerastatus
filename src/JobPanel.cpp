/* 
 * File:   JobPanel.cpp
 * Author: churas
 * 
 * Created on August 14, 2012, 2:19 PM
 */

#include <ncurses.h>
#include "CursesColors.hpp"
#include "JobPanel.hpp"
#include "Box.hpp"
#include "StatusModel.hpp"
#include "HorizontalJobBar.hpp"
#include "StringUtil.hpp"

JobPanel::JobPanel(int startX,int startY, int height, int width,CursesColors *cp,
        StatusModel *model) {
    mp_StartX = startX;
    mp_StartY = startY;
    mp_Height = height;
    mp_Width = width;
    mp_pColors = cp;
    
    mp_pWorkflowLabel = new std::string("Workflows");
    mp_pJobsLabel = new std::string("Jobs");
    mp_pRunQueueHeader = new std::string("Running / Queued");
    mp_pWaitToRunHeader = new std::string("Avg Held To Run");
    mp_pStatusModel = model;
    mp_pWaitFieldClearString = new std::string(this->WAITFIELDSIZE,' ');
    
    
}

JobPanel::~JobPanel() {
    delete mp_pWorkflowLabel;
    delete mp_pJobsLabel;
    delete mp_pRunQueueHeader;
    delete mp_pWaitToRunHeader;
    delete mp_pWaitFieldClearString;
    delete mp_pWorkflowBar;
    delete mp_pJobBar;
}

void JobPanel::draw(){
     mp_pColors->setColorPair(CursesColors::CYANBLACK);
    
    //render horizontal line
    move(mp_StartY+mp_Height,mp_StartX);
    for (int i = 1; i < mp_Width; i++){
       addch('-');
    }
    mvaddstr(mp_StartY+1,mp_StartX+1,mp_pWorkflowLabel->c_str());
    mvaddstr(mp_StartY+2,mp_StartX+1,mp_pJobsLabel->c_str());
    
    mvaddstr(mp_StartY,mp_StartX+mp_pWorkflowLabel->length()+3,mp_pRunQueueHeader->c_str());
    
    mvaddstr(mp_StartY,mp_StartX+mp_pRunQueueHeader->length()+mp_pWorkflowLabel->length()+5,"Queue Load");
  

    addch(32);
    addch(32);
    addch(32);
    addch(32);
    addch(32);
    addch(32);
    addch(32);
    addch(32);
    addch(32);

    addstr(mp_pWaitToRunHeader->c_str());
    if (mp_pWorkflowBar == NULL){
        mp_pWorkflowBar = new HorizontalJobBar(mp_StartX+mp_pRunQueueHeader->length()+mp_pWorkflowLabel->length()+5,
                mp_StartY+1,19,mp_pColors);
    }
    if (mp_pJobBar == NULL){
        mp_pJobBar = new HorizontalJobBar(mp_StartX+mp_pRunQueueHeader->length()+mp_pWorkflowLabel->length()+5,
                mp_StartY+2,19,mp_pColors);
    }
    mp_pWorkflowBar->draw();
    mp_pJobBar->draw();
    mp_pColors->unsetColorPair(CursesColors::CYANBLACK);
    
    
}

void JobPanel::update(){
    StringUtil stringUtil;
    mp_pColors->setColorPair(CursesColors::CYANBLACK);
    
    move(mp_StartY+1,mp_StartX+mp_pWorkflowLabel->length()+4);
    addstr(stringUtil.getIntAsPaddedString(mp_pStatusModel->getNumberRunningWorkflows(),99999,JOBWORKFLOWFIELDSIZE));
    
    move(mp_StartY+1,mp_StartX+mp_pWorkflowLabel->length()+7+JOBWORKFLOWFIELDSIZE);
    addstr(stringUtil.getIntAsPaddedString(mp_pStatusModel->getNumberHeldWorkflows()+mp_pStatusModel->getNumberQueuedWorkflows(),99999,JOBWORKFLOWFIELDSIZE));
    
    move(mp_StartY+2,mp_StartX+mp_pWorkflowLabel->length()+4);
    addstr(stringUtil.getIntAsPaddedString(mp_pStatusModel->getNumberRunningJobs(),99999,JOBWORKFLOWFIELDSIZE));
    
    move(mp_StartY+2,mp_StartX+mp_pWorkflowLabel->length()+7+JOBWORKFLOWFIELDSIZE);
    addstr(stringUtil.getIntAsPaddedString(mp_pStatusModel->getNumberQueuedJobs()+mp_pStatusModel->getNumberHeldJobs(),99999,JOBWORKFLOWFIELDSIZE));
    
    move(mp_StartY+1,mp_Width-(14+mp_pWaitToRunHeader->length()));
    addstr(mp_pWaitFieldClearString->c_str());

    move(mp_StartY+1,mp_Width-(14+mp_pWaitToRunHeader->length()));
    addstr(getAvgWaitToRunAsPaddedString(mp_pStatusModel->getWorkflowWaitTimeToRunInSeconds()));
    
    move(mp_StartY+2,mp_Width-(14+mp_pWaitToRunHeader->length()));
    addstr(mp_pWaitFieldClearString->c_str());
    
    move(mp_StartY+2,mp_Width-(14+mp_pWaitToRunHeader->length()));
    addstr(getAvgWaitToRunAsPaddedString(mp_pStatusModel->getJobWaitTimeToRunInSeconds()));

    mp_pWorkflowBar->updateLoad(mp_pStatusModel->getClusterLoad("WORKFLOW"));
    mp_pWorkflowBar->update();
    
    mp_pJobBar->updateLoad(mp_pStatusModel->getClusterLoad("JOB"));
    mp_pJobBar->update();
    
    mp_pColors->unsetColorPair(CursesColors::CYANBLACK);
    
}

const char *JobPanel::getAvgWaitToRunAsPaddedString(int waitInSeconds){
    char buff[this->WAITFIELDSIZE];
    if (waitInSeconds < 60){
        snprintf(buff,WAITFIELDSIZE,"%d seconds",waitInSeconds);
    }
    else if (waitInSeconds > 60 && waitInSeconds < 3600){
        snprintf(buff,WAITFIELDSIZE,"%d minutes",waitInSeconds/60);
    }
    else if (waitInSeconds > 3600){
        snprintf(buff,WAITFIELDSIZE,"%.1f hours",(float)waitInSeconds/(float)3600.0);
    }
    std::string retval = std::string(buff);
    return retval.c_str();
}

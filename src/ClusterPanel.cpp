/* 
 * File:   ClusterPanel.cpp
 * Author: churas
 * 
 * Created on August 16, 2012, 4:41 PM
 */

#include "ClusterPanel.hpp"
#include "HorizontalJobBar.hpp"
#include "StatusModel.hpp"
#include "CursesColors.hpp"
#include "StringUtil.hpp"
#include <ncurses.h>
#include <list>

ClusterPanel::ClusterPanel(int startx,int starty,int height,int width,CursesColors *colors,StatusModel *sm) {
    mp_ClusterLabel = std::string("Cluster                      ");
    mp_ClusterLoadLabel = std::string("Cluster Load       ");
    mp_DiskLabel = std::string("Disk  ");
    mp_HrsRemainLabel = std::string("HrsRemain  ");
    mp_StatusLabel = std::string("Status      ");
    mp_StartX = startx;
    mp_StartY = starty;
    mp_Width = width;
    mp_Height = height;
    mp_pColors = colors;
    mp_pStatusModel = sm;
    mp_pStatusClearString = new std::string(STATUSFIELDSIZE,' ');
    mp_pClusterHash = NULL;
}

ClusterPanel::~ClusterPanel() {
    /* @TODO free memory from mp_pClusterHash*/
    delete mp_pStatusClearString;
}

void ClusterPanel::draw(){
    mp_pColors->setColorPair(CursesColors::CYANBLACK);
    //draw header labels
    mvaddstr(mp_StartY,mp_StartX+1,mp_ClusterLabel.c_str());
    addstr(mp_ClusterLoadLabel.c_str());
    addstr(mp_DiskLabel.c_str());
    addstr(mp_HrsRemainLabel.c_str());
    addstr(mp_StatusLabel.c_str());
    
    //create hash of clusters
    int lineCntr = 1;
    mp_pClusterHash = new std::map<std::string,HorizontalJobBar *>();
    std::list<std::string> clusterList = mp_pStatusModel->getClusterList();
    std::list<std::string>::iterator itr;
    for(itr=clusterList.begin(); itr != clusterList.end(); ++itr){
       std::string &cluster = *itr;
       HorizontalJobBar *jobBar = new HorizontalJobBar(mp_StartX+30,mp_StartY+lineCntr,19,mp_pColors);
       mp_pClusterHash->insert(std::pair<std::string,HorizontalJobBar *>(cluster,jobBar));
       jobBar->draw();
       lineCntr++;
    }
    mp_pColors->setColorPair(CursesColors::CYANBLACK);
    //draw bottom horizontal line
    move(mp_StartY+mp_Height,mp_StartX);
    for (int i = 0;i < mp_Width-1; i++){
        addch('~');
    }
    
}

void ClusterPanel::update(){
    mp_pColors->setColorPair(CursesColors::CYANBLACK);
    StringUtil stringUtil;
    //get list of clusters and fill out information for each cluster
    std::list<std::string> clusterList = mp_pStatusModel->getClusterList();
    int lineCntr = 1;
    std::list<std::string>::iterator itr;
    for(itr=clusterList.begin(); itr != clusterList.end(); ++itr){
        mp_pColors->setColorPair(CursesColors::CYANBLACK);
        std::string &cluster = *itr;
        move(mp_StartY+lineCntr,mp_StartX+1);
        addstr(cluster.c_str());
        move(mp_StartY+lineCntr,mp_StartX+13);
        addstr(stringUtil.getIntAsPaddedString(mp_pStatusModel->getClusterRunning(cluster.c_str()),99999,JOBFIELDSIZE));
        move(mp_StartY+lineCntr,mp_StartX+22);
        addstr(stringUtil.getIntAsPaddedString(mp_pStatusModel->getClusterQueued(cluster.c_str())+mp_pStatusModel->getClusterHeld(cluster.c_str()),99999,JOBFIELDSIZE));
        move(mp_StartY+lineCntr,mp_StartX+32);
        HorizontalJobBar *jobBar = this->mp_pClusterHash->find(cluster)->second;
        jobBar->updateLoad(mp_pStatusModel->getClusterLoad(cluster.c_str()));
        jobBar->update();
        mp_pColors->setColorPair(CursesColors::GREENBLACK);
        
        //render disk
        move(mp_StartY+lineCntr,mp_StartX+48);
        int clusterDisk = mp_pStatusModel->getClusterDisk(cluster.c_str());
        if (clusterDisk >=50 & clusterDisk < 75){
            mp_pColors->setColorPair(CursesColors::YELLOWBLACK);
        }
        if (clusterDisk >= 75){
            mp_pColors->setColorPair(CursesColors::REDBLACK);
        }
        addstr(stringUtil.getIntAsPaddedString(clusterDisk,999,4));
        
        mp_pColors->setColorPair(CursesColors::CYANBLACK);
        addch('%');
        
        
        //render hours remaining
        int hoursRemain = mp_pStatusModel->getClusterHoursRemaining(cluster.c_str());
        mp_pColors->setColorPair(CursesColors::GREENBLACK);
        if (hoursRemain < 100000){
            mp_pColors->setColorPair(CursesColors::YELLOWBLACK);
        }
        if (hoursRemain < 50000){
            mp_pColors->setColorPair(CursesColors::REDBLACK);
        }
        move(mp_StartY+lineCntr,mp_StartX+56);
        addstr(stringUtil.getIntAsPaddedString(hoursRemain,9999999,8));
        
        mp_pColors->setColorPair(CursesColors::CYANBLACK);
        //render status
        move(mp_StartY+lineCntr,mp_StartX+66);
        addstr(this->mp_pStatusClearString->c_str());
        move(mp_StartY+lineCntr,mp_StartX+66);
        std::string clusterStatus = std::string(mp_pStatusModel->getClusterStatus(cluster.c_str()));
        if (clusterStatus.compare("Disabled") == 0){
            mp_pColors->setColorPair(CursesColors::REDBLACK);
        }
        if (clusterStatus.compare("Available") == 0){
            mp_pColors->setColorPair(CursesColors::GREENBLACK);
        }
        addstr(clusterStatus.c_str());
        lineCntr++;
    }
    mp_pColors->unsetColorPair(CursesColors::CYANBLACK);
}

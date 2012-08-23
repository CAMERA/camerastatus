
#include "CursesView.hpp"

#include <iostream>

#include <ncurses.h>

#include "Box.hpp"
#include "CursesColors.hpp"
#include "News.hpp"
#include "JobPanel.hpp"
#include "StatusModel.hpp"
#include "ClusterPanel.hpp"
#include "LoggedInUsersBar.hpp"
#include "WorkflowsRunBar.hpp"

CursesView::CursesView(StatusModel *sm){
  // does not do anything yet
    mp_pStatusModel = sm;
    mp_pBox = NULL;
    mp_pColors = NULL;
    mp_pNews = NULL;
    mp_pJobPanel = NULL;
    mp_pClusterPanel = NULL;
    mp_pLoggedInUsersBar = NULL;
    mp_pWorkflowsRunBar = NULL;
}

CursesView::~CursesView(){
  std::cout <<"CursesView destructor"<<std::endl;
  endwin();
  if (mp_pBox != NULL){
    delete mp_pBox;
  }
  if (mp_pColors != NULL){
    delete mp_pColors;
  }
}

int CursesView::initialize(){
  initscr();
  if (has_colors() == FALSE){
     return 1;
  }
  curs_set(0);
  noecho();
  cbreak();
  
  mp_pColors = new CursesColors();
  mp_pColors->initialize(); 
  mp_pNews = new News(1,1,4,79,mp_pColors,mp_pStatusModel);
  mp_pBox = new Box(0,0,23,79,"Camera System Monitor v0.5",mp_pColors);
  mp_pJobPanel = new JobPanel(1,6,3,79,mp_pColors,mp_pStatusModel);
  mp_pClusterPanel = new ClusterPanel(1,10,6,79,mp_pColors,mp_pStatusModel);
  mp_pLoggedInUsersBar = new LoggedInUsersBar(1,17,79,mp_pColors,mp_pStatusModel);
  mp_pWorkflowsRunBar = new WorkflowsRunBar(1,18,79,mp_pColors,mp_pStatusModel);
  return 0;
}

void CursesView::draw(){
  mp_pBox->draw();
  mp_pNews->draw();
  mp_pJobPanel->draw();
  mp_pClusterPanel->draw();
  mp_pLoggedInUsersBar->draw();
  mp_pWorkflowsRunBar->draw();
  refresh();
}

void CursesView::update(){
  mp_pBox->update();
  mp_pNews->update();
  mp_pJobPanel->update();
  mp_pClusterPanel->update();
  mp_pLoggedInUsersBar->update();
  mp_pWorkflowsRunBar->update();
  refresh();
}
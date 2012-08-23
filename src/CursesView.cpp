
#include "CursesView.hpp"
#include "config.h"
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

CursesView::CursesView(StatusModel *sm) : mp_pStatusModel(sm),
mp_pBox(NULL),
mp_pColors(NULL),
mp_pNews(NULL),
mp_pJobPanel(NULL),
mp_pClusterPanel(NULL),
mp_pLoggedInUsersBar(NULL),
mp_pWorkflowsRunBar(NULL) {
    mp_Width = 79;
    mp_Height = 23;

}

CursesView::~CursesView() {
    
    //stop curses
    endwin();
    
    
    if (mp_pColors != NULL) {
        delete mp_pColors;
    }
    if (mp_pNews != NULL){
        delete mp_pNews;
    }
    
    if (mp_pBox != NULL) {
        delete mp_pBox;
    }
    if (mp_pJobPanel != NULL){
        delete mp_pJobPanel;
    }
    if (mp_pClusterPanel != NULL){
        delete mp_pClusterPanel;
    }
    if (mp_pLoggedInUsersBar != NULL){
        delete mp_pLoggedInUsersBar;
    }
    if (mp_pWorkflowsRunBar != NULL){
        delete mp_pWorkflowsRunBar;
    }
    
}

int CursesView::initialize() {
    
    //initialize curses library
    initscr();
    
    //verify we have colors with curses otherwise bail
    if (has_colors() == FALSE) {
        return 1;
    }
    //get rid of the cursor
    curs_set(0);
    
    //don't echo any characters
    noecho();
    
    //as soon as a user hits a key make it available to getch() 
    cbreak();

    mp_pColors = new CursesColors();
    mp_pColors->initialize();
    mp_pNews = new News(1, 1, 4, mp_Width, mp_pColors, mp_pStatusModel);
    std::string title = std::string("Camera System Monitor v") + std::string(PACKAGE_VERSION);
    mp_pBox = new Box(0, 0, mp_Height, mp_Width, title.c_str(), mp_pColors);
    mp_pJobPanel = new JobPanel(1, 6, 3, mp_Width, mp_pColors, mp_pStatusModel);
    mp_pClusterPanel = new ClusterPanel(1, 10, 6, mp_Width, mp_pColors, mp_pStatusModel);
    mp_pLoggedInUsersBar = new LoggedInUsersBar(1, 17, mp_Width, mp_pColors, mp_pStatusModel);
    mp_pWorkflowsRunBar = new WorkflowsRunBar(1, 18, mp_Width, mp_pColors, mp_pStatusModel);
    return 0;
}

void CursesView::draw() {
    mp_pBox->draw();
    mp_pNews->draw();
    mp_pJobPanel->draw();
    mp_pClusterPanel->draw();
    mp_pLoggedInUsersBar->draw();
    mp_pWorkflowsRunBar->draw();
    refresh();
}

void CursesView::update() {
    mp_pBox->update();
    mp_pNews->update();
    mp_pJobPanel->update();
    mp_pClusterPanel->update();
    mp_pLoggedInUsersBar->update();
    mp_pWorkflowsRunBar->update();
    refresh();
}
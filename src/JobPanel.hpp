/* 
 * File:   JobPanel.hpp
 * Author: churas
 *
 * Created on August 14, 2012, 2:19 PM
 */

#ifndef JOBPANEL_HPP
#define	JOBPANEL_HPP

#include <string>

//forward declarations
class CursesColors;
class StatusModel;
class HorizontalJobBar;


class JobPanel {
public:
    JobPanel(int startX,int startY, int height, int width,CursesColors *cp,
            StatusModel *model);
    ~JobPanel();
    void draw();
    void update();
    const char *getAvgWaitToRunAsPaddedString(int value);
    static const int JOBWORKFLOWFIELDSIZE = 6;
    static const int WAITFIELDSIZE = 19;
    int mp_StartX;
    int mp_StartY;
    int mp_Height;
    int mp_Width;
    CursesColors *mp_pColors;
    std::string *mp_pWorkflowLabel;
    std::string *mp_pJobsLabel;
    std::string *mp_pRunQueueHeader;
    std::string *mp_pWaitToRunHeader;
    StatusModel *mp_pStatusModel;
    std::string *mp_pWaitFieldClearString;
    HorizontalJobBar *mp_pWorkflowBar;
    HorizontalJobBar *mp_pJobBar;


};

#endif	/* JOBPANEL_HPP */


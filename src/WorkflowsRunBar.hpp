/* 
 * File:   LoggedInUsersBar.hpp
 * Author: churas
 *
 * Created on August 17, 2012, 1:56 PM
 */

#ifndef WORKFLOWSRUNBAR_HPP
#define	WORKFLOWSRUNBAR_HPP


#include <string>
//forward declaration
class CursesColors;
class StatusModel;

class WorkflowsRunBar {
public:
    WorkflowsRunBar(int startx, int starty, int width,CursesColors *colors,StatusModel *sm);
    virtual ~WorkflowsRunBar();
    void draw();
    void update();
    
private:
    int mp_StartX;
    int mp_StartY;
    int mp_Width;
    CursesColors *mp_pColors;
    StatusModel *mp_pStatusModel;
    std::string mp_WorkflowsRunLabel;
    std::string mp_LastSubmittedLabel;
    std::string mp_LastSubmittedClear;

};

#endif	/* WORKFLOWSRUNBAR_HPP */


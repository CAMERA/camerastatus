/* 
 * File:   LoggedInUsersBar.hpp
 * Author: churas
 *
 * Created on August 17, 2012, 1:56 PM
 */

#ifndef LOGGEDINUSERSBAR_HPP
#define	LOGGEDINUSERSBAR_HPP


#include <string>
//forward declaration
class CursesColors;
class StatusModel;

class LoggedInUsersBar {
public:
    LoggedInUsersBar(int startx, int starty, int width,CursesColors *colors,StatusModel *sm);
    virtual ~LoggedInUsersBar();
    void draw();
    void update();
    
private:
    int mp_StartX;
    int mp_StartY;
    int mp_Width;
    CursesColors *mp_pColors;
    StatusModel *mp_pStatusModel;
    std::string mp_LoginLabel;
    std::string mp_LastLoginLabel;
    std::string mp_LastLoginClear;

};

#endif	/* LOGGEDINUSERSBAR_HPP */


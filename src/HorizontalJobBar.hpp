/* 
 * File:   HorizontalJobBar.hpp
 * Author: churas
 *
 * Created on August 16, 2012, 2:29 PM
 */

#ifndef HORIZONTALJOBBAR_HPP
#define	HORIZONTALJOBBAR_HPP
#include <string>
//forward declaration
class CursesColors;

class HorizontalJobBar {
public:
    HorizontalJobBar(int startx,int starty, int width,CursesColors *colors);
    virtual ~HorizontalJobBar();
    void updateLoad(int percentLoad);
    void draw();
    void update();
    
private:
    int mp_StartX;
    int mp_StartY;
    int mp_Width;
    CursesColors *mp_pColors;
    int mp_PercentLoad;
    std::string mp_LeftBracket;
    std::string mp_RightBracket;
};

#endif	/* HORIZONTALJOBBAR_HPP */


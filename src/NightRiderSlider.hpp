/* 
 * File:   NightRiderSlider.hpp
 * Author: churas
 *
 * Created on August 14, 2012, 9:10 AM
 */

#ifndef __NIGHTRIDERSLIDER_HPP__
#define	__NIGHTRIDERSLIDER_HPP__

#include <string>

//forward declaration
class CursesColors;

class NightRiderSlider {
public:
    NightRiderSlider(int startX,int startY,CursesColors *cp);
    ~NightRiderSlider();
    void draw();
    void update();
private:
    int mp_StartX;
    int mp_StartY;
    int mp_SliderLength;
    int mp_SliderXPos;
    int mp_SliderDirection;
    std::string mp_LeftBracket;
    std::string mp_RightBracket;
    std::string mp_Bar;
    CursesColors *mp_pColors;
};


#endif	/* __NIGHTRIDERSLIDER_HPP__ */


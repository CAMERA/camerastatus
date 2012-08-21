
#ifndef __BOX_H_INCLUDED__
#define __BOX_H_INCLUDED__

#include <string>

//forward declarations
class CursesColors;
class NightRiderSlider;

class Box {
  
  public:
    Box(int startx,int starty, int height,int width,const char *title,
    CursesColors *cp);
    ~Box();
    void draw();
    void update();
    const char *getDate();
  private:
    std::string *mp_pTitle;
    int mp_StartX;
    int mp_StartY;
    int mp_Height;
    int mp_Width;
    int mp_DateBlockX;
    int mp_DateBlockY;
    CursesColors *mp_pColors;
    NightRiderSlider *mp_pSlider;
  
};
#endif // __BOX_H_INCLUDED__

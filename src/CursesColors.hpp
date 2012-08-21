#ifndef __CURSESCOLORS_H_INCLUDED__
#define __CURSESCOLORS_H_INCLUDED__


class CursesColors {
  public:
    enum ColorPair {
        NONE,
        CYANBLACK,
        YELLOWBLACK,
        REDBLACK,
        GREENBLACK
    };

    CursesColors(); //constructor
    ~CursesColors();
    int initialize();
    int setColorPair(ColorPair cp);
    int unsetColorPair(ColorPair cp); 


};


#endif // __CURSESCOLORS_H_INCLUDED__

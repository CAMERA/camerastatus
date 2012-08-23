
#ifndef __BOX_H_INCLUDED__
#define __BOX_H_INCLUDED__

#include <string>

//forward declarations
class CursesColors;
class NightRiderSlider;

/**
 * Instances of this class render a curses UI bounding box which looks
 * as follows:
 * 
 *                  -<title (date)>---------------------
 *                 |                                    |
 *                 |                                    |
 *                 |                                    |
 *                  ------------[     --- ]-------------
 * 
 * The (date) is current time obtained via getDate() method below.  Everything
 * else is set via the constructor method.  Instances of this class require
 * curses library to already be initialized via initscr() and requires support
 * of colors in curses.  
 * @author churas
 * 
 */
class Box {
public:
    /**
     * Constructor that creates the box.
     * @param startx defines upper left x coordinate of box
     * @param starty defines upper left y coordinate of box
     * @param height defines height of box
     * @param width defines width of box
     * @param title sets the title displayed at the top of the box
     * @param cp pointer to valid CursesColors object used to set colors
     *           of box
     */
    Box(int startx, int starty, int height, int width, const char *title,
            CursesColors *cp);
    
    /**
     * Destructor.  Frees memory for title and slider
     */
    ~Box();

    /**
     * Called to draw initial box.  Method also invokes update() call
     * @note It is the callers responsibility to call curses refresh() method
     * after invoking to see changes.
     */
    void draw();

    /**
     * Only updates the slider bar at the bottom and date.
     * @note It is the callers responsibility to call curses refresh() method
     * after invoking to see changes.
     */
    void update();

    /**
     * Gets the current time and returns it as a string
     * @return current time in format: Day Month MonthDay Hour:Minute:Second Year ie  Thu Aug 23 14:53:00 2012
     */
    const char *getDate();

private:

    /**
     * Defines title put on top of box
     */
    std::string *mp_pTitle;

    /**
     * Sets upper left x coordinate of box
     */
    int mp_StartX;

    /**
     * Sets upper left y coordinate of box
     */

    int mp_StartY;

    /**
     * Sets height of box
     */

    int mp_Height;

    /**
     * Sets width of box
     */
    int mp_Width;
    
    /**
     * x coordinate of date block, defined in draw phase to set location
     * of where date is rendered
     */
    int mp_DateBlockX;
    
    /**
     * y coordinate of date block, defined in draw phase to set location
     * of where date is rendered
     */
    int mp_DateBlockY;
    
    /**
     * Pointer to valid CursesColors object, used to set colors of box.  
     */
    CursesColors *mp_pColors;
    
    /**
     * Pointer to slider displayed at bottom of box.  Constructed during 
     * draw() method
     */
    NightRiderSlider *mp_pSlider;

};
#endif // __BOX_H_INCLUDED__

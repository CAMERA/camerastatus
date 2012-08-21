/* 
 * File:   News.hpp
 * Author: churas
 *
 * Created on August 14, 2012, 1:36 PM
 */

#ifndef __NEWS_HPP__
#define	__NEWS_HPP_

#include <string>
//forward declarations
class CursesColors;
class StatusModel;

class News {
public:
    News(int startX,int startY, int height, int width,CursesColors *cp,
            StatusModel *model);
    virtual ~News();
    void draw();
    void update();
private:
    int mp_StartX;
    int mp_StartY;
    int mp_Height;
    int mp_Width;
    CursesColors *mp_pColors;
    std::string *mp_pTitle;
    StatusModel *mp_pStatusModel; 
    std::string *mp_pClearString;

   

};

#endif	/* __NEWS_HPP__ */


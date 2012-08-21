/* 
 * File:   ClusterPanel.hpp
 * Author: churas
 *
 * Created on August 16, 2012, 4:41 PM
 */

#ifndef CLUSTERPANEL_HPP
#define	CLUSTERPANEL_HPP

#include <string>
#include <map>

//forward declaration   
class CursesColors;
class StatusModel;
class HorizontalJobBar;


class ClusterPanel {
public:
    static const int JOBFIELDSIZE = 6;
    static const int STATUSFIELDSIZE = 11;
    ClusterPanel(int startx,int starty,int height,int width,CursesColors *colors,StatusModel *sm);
    virtual ~ClusterPanel();
    void draw();
    void update();
    
    
private:
    int mp_StartX;
    int mp_StartY;
    int mp_Width;
    int mp_Height;
    CursesColors *mp_pColors;
    StatusModel *mp_pStatusModel;
    std::string mp_ClusterLabel;
    std::string mp_ClusterLoadLabel;
    std::string mp_DiskLabel;
    std::string mp_HrsRemainLabel;
    std::string mp_StatusLabel;
    std::map<std::string,HorizontalJobBar *> *mp_pClusterHash;
    std::string *mp_pStatusClearString;

};

#endif	/* CLUSTERPANEL_HPP */


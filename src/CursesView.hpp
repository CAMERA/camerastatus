#ifndef __CURSESVIEW_H_INCLUDED__
#define __CURSESVIEW_H_INCLUDED__

//forward declarations
class Box;
class CursesColors;
class News;
class JobPanel;
class ClusterPanel;
class LoggedInUsersBar;
class WorkflowsRunBar;
class StatusModel;

class CursesView {

  public:
    CursesView(StatusModel *sm);  //constructor  
    ~CursesView(); //destructor
    int initialize();  
    void draw(); //
    void update();

  private:
    Box *mp_pBox;
    CursesColors *mp_pColors;
    News *mp_pNews;
    JobPanel *mp_pJobPanel;
    ClusterPanel *mp_pClusterPanel;
    LoggedInUsersBar *mp_pLoggedInUsersBar;
    WorkflowsRunBar *mp_pWorkflowsRunBar;
    StatusModel *mp_pStatusModel;
};
#endif //__CURSESVIEW_H_INCLUDED__

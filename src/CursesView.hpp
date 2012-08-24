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

/**
 * Instances of this class represent the View of the application.  Instances of
 * this object are responsibile for initialization of ncurses library as well
 * as creation and updating of the various UI components of the view.  This
 * view generates a UI of the following structure with labels denoting the
 * various classes used:
 * 
 *          --Box------------------------
 *          |    News                    |
 *          |    JobPanel                |
 *          |   ClusterPanel             |
 *          |   LoggedInUsersBar         |
 *          |   WorkflowsRunBar          |
 *           ---------------------------- 
 *
 * Instances of this class first create the above objects and pass most if not
 * all of them the StatusModel object passed into the constructor of this class.
 * 
 * When draw() method is invoked, this method calls draw() on all of the above
 * objects.  When update() is called this method calls update() on all of the
 * above objects.  
 * The destructor deletes all objects the instance creates.  Before calling
 * draw() or update() the initialize() method must be called.
 */
class CursesView {
public:

    /**
     * Constructor
     * @param width Width in characters to fit display into
     * @param height Height in characters to fix display into
     * @param sm Pointer to valid StatusModel object which is used to obtain data
     *           to display
     */
    CursesView(int width,int height,StatusModel *sm); //constructor  

    /**
     * Destructor that deletes any objects instances of this class have created.
     */
    ~CursesView(); //destructor

    /**
     * Initializes curses library.  Must be called before calling draw() or update()
     * methods.  
     * @todo should make the constructor invoke this method.
     * @return 0 upon success or 1 if there was an error with initialization in
     *         which case caller should abandon using this view.
     */
    int initialize();

    /**
     * Calls draw() on all UI objects which will render non changing UI portions
     * of objects.
     * @warning Must call initialize() before calling this method
     */
    void draw();

    /**
     * Calls update() on all UI objects which will render changing UI portions of
     * objects.
     * @warning Must call draw() once before calling this method.
     */
    void update();

private:

    /**
     * Width of window UI.  This is passed to the UI components
     */
    int mp_Width;

    /**
     * Height of window UI.  This will be portioned out to some of the
     * components
     */
    int mp_Height;

    /**
     * Box UI object
     */
    Box *mp_pBox;

    /**
     * Allows UI components to set colors
     */
    CursesColors *mp_pColors;

    /**
     * News section UI object
     */
    News *mp_pNews;

    /**
     * Jobs section UI object
     */
    JobPanel *mp_pJobPanel;

    /**
     * Cluster information section UI object
     */
    ClusterPanel *mp_pClusterPanel;

    /**
     * Logged in users and last login section UI object
     */
    LoggedInUsersBar *mp_pLoggedInUsersBar;

    /**
     * Number of workflows run UI object
     */
    WorkflowsRunBar *mp_pWorkflowsRunBar;

    /**
     * Model used by the UI objects to obtain current information when update()
     * is called on them
     */
    StatusModel *mp_pStatusModel;
};
#endif //__CURSESVIEW_H_INCLUDED__

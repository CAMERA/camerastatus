
#ifndef URLSTATUSMODEL_HPP
#define	URLSTATUSMODEL_HPP

#include <stdio.h>
#include <curl/curl.h>

#include "StatusModel.hpp"
#include <list>
#include <string>


/**
 * Instances of this class obtain current CAMERA status from URL specified in 
 * the constructor.  The method refresh() tells the instance to query the URL
 * again to get fresh data.
 */
class URLStatusModel : public StatusModel {
public:
    URLStatusModel(const char *URL);
    virtual ~URLStatusModel();
    void refresh();
    std::list<std::string> getNews();
    
    int getNumberRunningWorkflows();
    int getNumberQueuedWorkflows();
    int getNumberHeldWorkflows();
    
    int getNumberRunningJobs();
    int getNumberQueuedJobs();
    int getNumberHeldJobs();
    
    int getWorkflowWaitTimeToRunInSeconds();
    int getJobWaitTimeToRunInSeconds();
    
    int getClusterQueued(const char *cluster);
    int getClusterHeld(const char *cluster);
    int getClusterRunning(const char *cluster);
    int getClusterLoad(const char *cluster);
    int getClusterDisk(const char *cluster);
    int getClusterHoursRemaining(const char *cluster);
    const char *getClusterStatus(const char *cluster);
    std::list<std::string> getClusterList();
    int getLoggedInUsers();
    const char *getLastLogin();
    std::list<std::string> getSystemAlerts();
    
    int getNumberWorkflowsRun();
    const char *getLastWorkflowSubmission();
    
    
private:
    
    /**
     * This method will parse raw data from mp_DataFromURL and obtain
     * the value corresponding to the fieldName specified.  
     * @param fieldName name of Field to search for ie lastLogin.  The search is case sensitive
     *                  be sure to NOT include the colon
     * @return 
     */
    const char *getValueOfField(const char *fieldName);

    /**
     * This method will take a string and convert it to an integer number removing
     * a % if it exists at the end
     * @param val string to convert to a number
     * @return integer value extracted from val string or -1 if there was a conversion problem
     */
    int convertStringToNumber(const char *val);
    
    const char *mp_URL;
    std::string mp_DataFromURL;

};

#endif	/* URLSTATUSMODEL_HPP */


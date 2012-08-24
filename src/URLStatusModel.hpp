
#ifndef URLSTATUSMODEL_HPP
#define	URLSTATUSMODEL_HPP

#include <stdio.h>
#include <curl/curl.h>

#include "StatusModel.hpp"
#include <list>
#include <string>

//forward declaration
class StringUtil;

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
    void refresh(const char *dataFromURL);
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
    
    const char *getRawDataFromURL();
    
    const char *getLastLine();
    
private:
    
    /**
     * This method will parse raw data from mp_DataFromURL and obtain
     * the value corresponding to the fieldName specified.  
     * @param fieldName name of Field to search for ie lastLogin.  The search is case sensitive
     *                  be sure to NOT include the colon
     * @return 
     */
    const char *getValueOfField(const char *fieldName);
    
    const char *mp_URL;
    std::string mp_DataFromURL;
    StringUtil *mp_pStringUtil;

};

#endif	/* URLSTATUSMODEL_HPP */


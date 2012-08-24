/* 
 * File:   StatusModel.hpp
 * Author: churas
 *
 * Created on August 14, 2012, 3:52 PM
 */

#ifndef STATUSMODEL_HPP
#define	STATUSMODEL_HPP

#include <list>
#include <string>

class StatusModel {
public:
    
    virtual void refresh() = 0;
    
   virtual std::list<std::string> getNews() = 0;
       
    virtual int getNumberRunningWorkflows() = 0;
    virtual int getNumberQueuedWorkflows() = 0;
    virtual int getNumberHeldWorkflows() = 0;
    
    virtual int getNumberRunningJobs() = 0;
    virtual int getNumberQueuedJobs() = 0;
    virtual int getNumberHeldJobs() = 0;
    
    virtual int getWorkflowWaitTimeToRunInSeconds() = 0;
    virtual int getJobWaitTimeToRunInSeconds() = 0;
    
       virtual int getClusterQueued(const char *cluster) = 0;
    virtual int getClusterHeld(const char *cluster) = 0;
    virtual int getClusterRunning(const char *cluster) = 0;
    virtual int getClusterLoad(const char *cluster) = 0;
    virtual int getClusterDisk(const char *cluster) = 0;
    virtual const char  *getClusterStatus(const char *cluster) =0;
    virtual int getClusterHoursRemaining(const char *cluster) = 0;
    
    virtual std::list<std::string> getClusterList() = 0;
    virtual int getLoggedInUsers() =0;
    virtual const char *getLastLogin()=0;
    virtual std::list<std::string> getSystemAlerts() = 0;
    
    virtual int getNumberWorkflowsRun() = 0;
    virtual const char *getLastWorkflowSubmission() = 0;
    
    virtual const char *getLastLine() = 0;
};


#endif	/* STATUSMODEL_HPP */


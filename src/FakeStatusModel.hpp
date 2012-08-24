/* 
 * File:   FakeStatusModel.hpp
 * Author: churas
 *
 * Created on August 14, 2012, 3:43 PM
 */

#ifndef FAKESTATUSMODEL_HPP
#define	FAKESTATUSMODEL_HPP
#include "StatusModel.hpp"
#include <list>
#include <string>

class FakeStatusModel : public StatusModel {
public:
    FakeStatusModel();
    virtual ~FakeStatusModel();
    
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
    
    const char *getLastLine();
    
private:
    int getRandomNumber(int max);
    int mp_RecentActivityCallCount;

};

#endif	/* FAKESTATUSMODEL_HPP */


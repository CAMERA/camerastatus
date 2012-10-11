/* 
 * File:   FakeStatusModel.cpp
 * Author: churas
 * 
 * Created on August 14, 2012, 3:43 PM
 */
#include <stdlib.h>
#include "FakeStatusModel.hpp"
#include "Box.hpp"

FakeStatusModel::FakeStatusModel() {
    mp_RecentActivityCallCount = 0;
}

FakeStatusModel::~FakeStatusModel() {
}

/**
 * Doesn't do anything since this is all fake
 */
void FakeStatusModel::refresh(){
    
}

int FakeStatusModel::getRandomNumber(int max){
    return 1+(int)(max * (rand() / (RAND_MAX+1.0)));
}

int FakeStatusModel::getClusterQueued(const char *cluster){
    return getRandomNumber(100000);
}

int FakeStatusModel::getClusterHeld(const char *cluster){
    return getRandomNumber(10000);
}

int FakeStatusModel::getClusterRunning(const char *cluster){
    return getRandomNumber(10000);
}

int FakeStatusModel::getClusterLoad(const char *cluster){
    return getRandomNumber(100);
}

int FakeStatusModel::getClusterDisk(const char *cluster){
  return getRandomNumber(100);   
}



const char *FakeStatusModel::getClusterStatus(const char *cluster){
    int rNum = getRandomNumber(10);
    if (rNum % 3 == 0){
        return "Available";
    }
    else if (rNum % 3 == 1){
        return "In Use";
    }
    else if (rNum % 3 == 2){
        return "Disabled";
    }
    return "Unknown";
}

int FakeStatusModel::getClusterHoursRemaining(const char *cluster){
    return getRandomNumber(100000);   
}

std::list<std::string> FakeStatusModel::getClusterList(){
    std::list<std::string> mylist;
    mylist.push_back("Local");
    mylist.push_back("Gordon");
    mylist.push_back("Trestles");
    mylist.push_back("Codonis");
    mylist.push_back("Lonestar");
    mylist.push_back("Ranger");
    mylist.push_back("Steele");
    return mylist;
}



std::list<std::string> FakeStatusModel::getNews(){
    
    std::list<std::string> mylist;
    
    if (mp_RecentActivityCallCount % 3 == 0){
        mylist.push_back(std::string("08/14/12 13:11:11 22 --  4 compute nodes down"));
        mylist.push_back(std::string("08/14/12 13:12:11 22 --  User ssun logged in"));
        mylist.push_back(std::string("08/14/12 13:11:13 22 --  User churas downloaded file"));
        
    }
    else if (mp_RecentActivityCallCount % 3 == 1){
        mylist.push_back(std::string("08/14/12 13:12:11 22 --  User ssun logged in"));
        mylist.push_back(std::string("08/14/12 13:11:13 22 --  User churas downloaded file"));
       mylist.push_back(std::string("08/14/12 13:11:11 22 --  4 compute nodes down"));
        
    }
    else if (mp_RecentActivityCallCount % 3 == 2){
        mylist.push_back(std::string("08/14/12 13:11:13 22 --  User churas downloaded file"));
        mylist.push_back(std::string("08/14/12 13:11:11 22 --  4 compute nodes down"));
        mylist.push_back(std::string("08/14/12 13:12:11 22 --  User ssun logged in"));
    }
    
    mp_RecentActivityCallCount++;
    return mylist;
}

int FakeStatusModel::getNumberRunningWorkflows(){
    return getRandomNumber(10000);
}

int FakeStatusModel::getNumberQueuedWorkflows(){
    return getRandomNumber(10000);
}

int FakeStatusModel::getNumberHeldWorkflows(){
    return getRandomNumber(10000);
}

int FakeStatusModel::getNumberRunningJobs(){
    return getRandomNumber(10000);
}

int FakeStatusModel::getNumberQueuedJobs(){
    return getRandomNumber(10000);
}

int FakeStatusModel::getNumberHeldJobs(){
    return getRandomNumber(10000);
}

int FakeStatusModel::getWorkflowWaitTimeToRunInSeconds(){
    return getRandomNumber(3800);
}

int FakeStatusModel::getJobWaitTimeToRunInSeconds(){
    return getRandomNumber(3800);
}

int FakeStatusModel::getLoggedInUsers(){
    return getRandomNumber(990);
}

const char *FakeStatusModel::getLastLogin(){
    if (this->mp_RecentActivityCallCount % 3 == 0){
        return "06/14/12 13:59:27 by smith";
    }
    if (this->mp_RecentActivityCallCount % 3 == 1){
        return "10/14/12 14:53:27 by joejobejosef";
    }
        return "03/12/11 15:12:26 by se";
}

std::list<std::string> FakeStatusModel::getSystemAlerts(){
      std::list<std::string> mylist;
    
    if (mp_RecentActivityCallCount % 3 == 0){
        mylist.push_back(std::string("4 compute nodes down"));
    }
    else if (mp_RecentActivityCallCount % 3 == 1){
        mylist.push_back(std::string("portal:/ 90% full"));
        mylist.push_back(std::string("4 compute nodes down"));
        
    }
    else if (mp_RecentActivityCallCount % 3 == 2){
        mylist.push_back(std::string("4 compute nodes down"));
        mylist.push_back(std::string("oracle db down"));
    }
    
    mp_RecentActivityCallCount++;
}

int FakeStatusModel::getNumberWorkflowsRun(){
    return this->getRandomNumber(12000);
}

const char *FakeStatusModel::getLastWorkflowSubmission(){
        if (this->mp_RecentActivityCallCount % 3 == 0){
        return "05/14/12 13:59:27 by jsee";
    }
    if (this->mp_RecentActivityCallCount % 3 == 1){
        return "09/14/12 14:53:27 by seth";
    }
        return "08/12/12 15:12:26 by george";
}
        
const char *FakeStatusModel::getLastLine(){
    return "true";
}

/* 
 * File:   URLStatusModel.cpp
 * Author: churas
 * 
 * Created on August 14, 2012, 3:43 PM
 */
#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
#include <errno.h>

#include <string.h>



#include "URLStatusModel.hpp"
#include "StringUtil.hpp"
#include "Box.hpp"
#include "CursesView.hpp"



extern "C" {

#define MYBUFFER 64000
    struct Chunk {
        char *data;
        size_t size;
    };

    size_t curl_writecallback(void *contents, size_t size, size_t nmemb, void *userdata) {
        size_t realsize = size * nmemb;
        struct Chunk *mem = (struct Chunk *) userdata;

        //too much data should fail
        if (mem->size+realsize >= MYBUFFER-1){
            return -1;
        }
        
        memcpy(&(mem->data[mem->size]), (char *) contents, realsize);
        mem->size += realsize;
        
        mem->data[mem->size] = 0;

        return realsize;
    }



}

URLStatusModel::URLStatusModel(const char *URL) {
    mp_URL = URL;
    mp_DataFromURL = std::string();
    mp_pStringUtil = new StringUtil();
}

URLStatusModel::~URLStatusModel() {
    if (mp_pStringUtil != NULL){
        delete mp_pStringUtil;
    }
}

void URLStatusModel::refresh() {
    CURL *curl;
    CURLcode res;
    struct Chunk chunk;
    
    //seems really inefficient to keep remaking this
    chunk.data = new char[MYBUFFER];
    
    //be sure to 0 out the array
    memset(chunk.data,'\0',MYBUFFER);
    
    chunk.size = 0;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, mp_URL);

        //set timeout to 10 seconds
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

        //send data to curl_writecallback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_writecallback);

        //pass in chunk struct
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

        // set user agent
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK) {
//            fprintf(stderr, "curl_easy_perform() failed: %s\n",
//                    curl_easy_strerror(res));
            chunk.size = 0;
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    //transfer chunk data to a string
    if (chunk.data != NULL && chunk.size > 0) {
        mp_DataFromURL = std::string(chunk.data);
    } else {
        mp_DataFromURL.clear();
    }

    if (chunk.data != NULL) {
        delete chunk.data;
        chunk.size = 0;
    }
}

int URLStatusModel::getClusterQueued(const char *cluster) {
    std::string cStatus = std::string(cluster) + std::string("jobsqueued");
    
    return mp_pStringUtil->convertStringToNumber(getValueOfField(cStatus.c_str()));
}

int URLStatusModel::getClusterHeld(const char *cluster) {
    return 0;
}

int URLStatusModel::getClusterRunning(const char *cluster) {
    std::string cStatus = std::string(cluster) + std::string("jobsrunning");
    return mp_pStringUtil->convertStringToNumber(getValueOfField(cStatus.c_str()));
}

int URLStatusModel::getClusterLoad(const char *cluster) {

    std::string cStatus = std::string(cluster) + std::string("load");
    if (cStatus.compare("JOBload") == 0) {
        return mp_pStringUtil->convertStringToNumber(getValueOfField("localqueueload"));
    }
    if (cStatus.compare("WORKFLOWload") == 0) {
        return mp_pStringUtil->convertStringToNumber(getValueOfField("workflowqueueload"));
    }
    
    return mp_pStringUtil->convertStringToNumber(getValueOfField(cStatus.c_str()));
}

int URLStatusModel::getClusterDisk(const char *cluster) {

    std::string cStatus = std::string(cluster) + std::string("diskfull");
    return mp_pStringUtil->convertStringToNumber(getValueOfField(cStatus.c_str()));
}

const char *URLStatusModel::getClusterStatus(const char *cluster) {
    std::string cStatus = std::string(cluster) + std::string("status");
    return getValueOfField(cStatus.c_str());
}

int URLStatusModel::getClusterHoursRemaining(const char *cluster) {
    std::string cStatus = std::string(cluster) + std::string("remainhours");

    return mp_pStringUtil->convertStringToNumber(getValueOfField(cStatus.c_str()));
}

std::list<std::string> URLStatusModel::getClusterList() {
    std::list<std::string> mylist;
    std::string clusterList = std::string(getValueOfField("clusterlist"));
    
    //need to split list which is delimited by commas and put into
    //stl list
    char clistCharArray[clusterList.length()+1];
    memset(clistCharArray,'\0',clusterList.length()+1);
    std::copy(clusterList.begin(),clusterList.end(),clistCharArray);
    
    char seps[] = ",\n";
    char *token;
    token = strtok(clistCharArray,seps);
    while (token != NULL){
        mylist.push_back(std::string(token));    
        token = strtok(NULL,seps);
    }
    
    return mylist;
}

std::list<std::string> URLStatusModel::getNews() {

    std::list<std::string> mylist;
    const char *timeStamp = getValueOfField("updatestr");
    if (mp_pStringUtil->convertStringToNumber(getValueOfField("localqueuedownhosts")) > 0){
    
        std::string downNodes = std::string(timeStamp);
        downNodes += " -- ";
        downNodes += std::string(getValueOfField("localqueuedownhosts"));
        downNodes += " compute nodes down";
        mylist.push_back(downNodes);
    }
    
    if (mp_pStringUtil->convertStringToNumber(getValueOfField("jbossmem")) > 50){
        std::string jbossMem = std::string(timeStamp);
        jbossMem  += " -- Jboss consuming ";
        jbossMem += std::string(getValueOfField("jbossmem"));
        jbossMem += " of available memory";
        mylist.push_back(jbossMem);
    }
    mylist.push_back(std::string(getValueOfField("lastportalerror")));
    return mylist;
}

int URLStatusModel::getNumberRunningWorkflows() {
    return mp_pStringUtil->convertStringToNumber(getValueOfField("workflowsrunning"));
}

int URLStatusModel::getNumberQueuedWorkflows() {
    return mp_pStringUtil->convertStringToNumber(getValueOfField("workflowsqueued"));
}

int URLStatusModel::getNumberHeldWorkflows() {
    return mp_pStringUtil->convertStringToNumber(getValueOfField("workflowsheld"));
}

int URLStatusModel::getNumberRunningJobs() {
    return mp_pStringUtil->convertStringToNumber(getValueOfField("alljobsrunning"));
}

int URLStatusModel::getNumberQueuedJobs() {
    return mp_pStringUtil->convertStringToNumber(getValueOfField("alljobsqueuedheld"));
}

int URLStatusModel::getNumberHeldJobs() {
    return 0;
}

int URLStatusModel::getWorkflowWaitTimeToRunInSeconds() {
    return mp_pStringUtil->convertStringToNumber(getValueOfField("avgworkflowwaittostart"));
}

int URLStatusModel::getJobWaitTimeToRunInSeconds() {
    return mp_pStringUtil->convertStringToNumber(getValueOfField("avgjobwaittostart"));
}

int URLStatusModel::getLoggedInUsers() {
    return mp_pStringUtil->convertStringToNumber(getValueOfField("loggedinusers"));
}

const char *URLStatusModel::getLastLogin() {
    return getValueOfField("lastlogin");
}

std::list<std::string> URLStatusModel::getSystemAlerts() {
    std::list<std::string> mylist;

    return mylist;
}

int URLStatusModel::getNumberWorkflowsRun() {
    return mp_pStringUtil->convertStringToNumber(getValueOfField("totalworkflowsrun"));
}

const char *URLStatusModel::getLastWorkflowSubmission() {
    return getValueOfField("lastworkflow");
}

const char *URLStatusModel::getRawDataFromURL(){
    return this->mp_DataFromURL.c_str();
}


const char *URLStatusModel::getValueOfField(const char *fieldName) {

    if (fieldName == NULL) {
        return "NA";
    }

    std::string fieldNameStr = std::string("\n") + fieldName + std::string(": ");

    size_t fieldPos = mp_DataFromURL.find(fieldNameStr);
    if (fieldPos == std::string::npos) {
        return "NA";
    }

    size_t newLinePos = mp_DataFromURL.find('\n', fieldPos + fieldNameStr.length());
    if (newLinePos != std::string::npos) {
        std::string uh = std::string(fieldName);
      
        return mp_DataFromURL.substr(fieldPos + fieldNameStr.length(),
                (newLinePos - (fieldPos + fieldNameStr.length()))).c_str();
    }

    return "NA";
}


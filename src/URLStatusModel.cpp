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
#include <iostream>
#include <string.h>



#include "URLStatusModel.hpp"
#include "StringUtil.hpp"
#include "Box.hpp"
#include "CursesView.hpp"



extern "C" {

    static std::string STRING_BUFFER;

    size_t curl_writecallback(char *data, size_t size, size_t nmemb, std::string *buffer) {
        // What we will return  
        int result = 0;

        // Is there anything in the buffer?  
        if (buffer != NULL && data != NULL) {
            // Append the data to the buffer  
            buffer->append(data, size * nmemb);

            // How much did we write?  
            result = size * nmemb;
        }

        return result;
    }



}

/**
 * Constant that defines delimiter for cluster list
 */
const char *URLStatusModel::CLUSTER_LIST_DELIMITER = ",";


URLStatusModel::URLStatusModel(const char *URL) {
    mp_URL = URL;
    mp_DataFromURL = std::string();
    mp_pStringUtil = new StringUtil();
    mp_pCurl = NULL;
}

URLStatusModel::~URLStatusModel() {
    if (mp_pStringUtil != NULL){
        delete mp_pStringUtil;
    }
    if (mp_pCurl != NULL){
        curl_easy_cleanup(mp_pCurl);
    }
}

void URLStatusModel::refresh(const char *dataFromURL){
    
    mp_DataFromURL.clear();

    if (dataFromURL != NULL){
        mp_DataFromURL.append(dataFromURL);
    }
}

void URLStatusModel::refresh() {
    CURLcode res;
    
    STRING_BUFFER.clear();
    mp_DataFromURL.clear();

    if (mp_pCurl == NULL){
        mp_pCurl = curl_easy_init();
    }
    if (mp_pCurl) {
        curl_easy_setopt(mp_pCurl, CURLOPT_URL, mp_URL);

        //set timeout to 10 seconds
        curl_easy_setopt(mp_pCurl, CURLOPT_TIMEOUT, 10);

        //send data to curl_writecallback function
        curl_easy_setopt(mp_pCurl, CURLOPT_WRITEFUNCTION, curl_writecallback);

        //pass in chunk struct
        curl_easy_setopt(mp_pCurl, CURLOPT_WRITEDATA, &STRING_BUFFER);

        // set user agent
        curl_easy_setopt(mp_pCurl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(mp_pCurl);
        /* Check for errors */
        if (res != CURLE_OK) {
            //fprintf(stderr, "curl_easy_perform() failed: %s\n",
            //        curl_easy_strerror(res));
            
        }
        mp_DataFromURL.append(STRING_BUFFER);
    }
}

int URLStatusModel::getClusterQueued(const char *cluster) {
    if (cluster == NULL){
        return -2;
    }
    
    std::string cStatus = std::string(cluster) + std::string("jobsqueued");
    
    if (cStatus.compare("jobsqueued") == 0){
        return -2;
    }
    
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
    
    //just return if the list is empty or if the value returned is NA
    if (clusterList.empty() == true ||
        clusterList == "NA"){
        return mylist;
    }
    mylist = mp_pStringUtil->split(clusterList.c_str(),CLUSTER_LIST_DELIMITER);
    return mylist;
}

std::list<std::string> URLStatusModel::getNews() {

    std::list<std::string> mylist;
    const char *timeStamp = getValueOfField("updatestr");
    if (mp_pStringUtil->convertStringToNumber(getValueOfField("localqueuedownhosts")) > 0){
    
        std::string downNodes;
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


const char *URLStatusModel::getLastLine(){
    return getValueOfField("lastline");
}

const char *URLStatusModel::getValueOfField(const char *fieldName) {

    if (fieldName == NULL) {
        return "NA";
    }
    std::string fieldNameStr = std::string("\n") + std::string(fieldName) + std::string(": ");
    size_t fieldPos = mp_DataFromURL.find(fieldNameStr);
    if (fieldPos == std::string::npos) {
        //add one more check its possible the field is the first entry so there
        //is no newline before hand
        fieldNameStr = std::string(fieldName) + std::string(": ");
        fieldPos = mp_DataFromURL.find(fieldNameStr);
        if (fieldPos != 0){
            return "NA";
        }
    }

    size_t newLinePos = mp_DataFromURL.find('\n', fieldPos + fieldNameStr.length());
    if (newLinePos != std::string::npos) {
        std::string res = mp_DataFromURL.substr(fieldPos + fieldNameStr.length(),
                newLinePos - (fieldPos + fieldNameStr.length())).c_str();
        return res.c_str();
    }
    return "NA";
}


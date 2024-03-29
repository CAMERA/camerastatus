/* 
 * File:   StringUtil.cpp
 * Author: churas
 * 
 * Created on August 17, 2012, 10:24 AM
 */

#include "StringUtil.hpp"
#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <stdlib.h>

StringUtil::StringUtil() {
}

StringUtil::~StringUtil() {
}


const char *StringUtil::getIntAsPaddedString(int value,int maxvalue,int width){
    
    if (width <= 0){
        return "";
    }  
    
    //don't allow any width greater then MAX_FIELD_SIZE_OF_INT
    if (width > MAX_FIELD_SIZE_OF_INT){
        width = MAX_FIELD_SIZE_OF_INT;
    }
    
      
    //If value is greater then maxvalue just return a string with # characters in it
    if (value > maxvalue){
        return std::string(width,'#').c_str();
    }
    
    char buff[width+1];
    snprintf(buff,width+1,"%d",value);

    std::string rbuff = std::string(buff);
    std::string tmp;
    for (int i = 0; i < (width - rbuff.length());i++){
        tmp.insert(0," ");
    }
    rbuff.insert(0,tmp);
    return rbuff.c_str();
}

int StringUtil::convertStringToNumber(const char *val) {
    if (val == NULL) {
        return -1;
    }
    std::string valStr = std::string(val);

    if (valStr.compare("NA") == 0) {
        return -2;
    }
    errno = 0;
    int retval = strtol(valStr.c_str(), (char **) NULL, 10);
    if (errno != 0) {
        return -3;
    }

    return retval;
}

std::list<std::string> StringUtil::split(const char *val,const char *delimiter){
    std::list<std::string> reslist;
    
    //bail if either list or delimiter is null
    if (val == NULL || delimiter == NULL){
        return reslist;
    }
    std::string::size_type prevDelim = std::string::npos;
    std::string::size_type nextDelim = std::string::npos;

    //Find first occurrence of delimiter and set nextDelim to it
    //The prevDelim is set to std::string::npos initially.
    //Loop calling find repeatedly until no more delimiters are found.
    //In each iteration add string found between prevDelim and nextDelim and handle
    //special case where prevDelim is unset.
    //Out of loop add last delimited string
    std::string valStr = std::string(val);
    nextDelim = valStr.find(delimiter,0);
    while(nextDelim != std::string::npos){
        if (prevDelim == std::string::npos){
                reslist.push_back(valStr.substr(0,nextDelim));
        }
        else {
                reslist.push_back(valStr.substr(prevDelim+1,nextDelim-prevDelim-1));
        }
        
        prevDelim = nextDelim;
        nextDelim = valStr.find(delimiter,prevDelim+1);
    }
    
    if (nextDelim == std::string::npos){
        nextDelim = valStr.length();
    }
    
    if (prevDelim != nextDelim){
        if (prevDelim == std::string::npos){
                reslist.push_back(valStr.substr(0,nextDelim));
        }
        else {
                reslist.push_back(valStr.substr(prevDelim+1,nextDelim-prevDelim-1));
        }
    }
    
    
    return reslist;
}

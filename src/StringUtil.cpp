/* 
 * File:   StringUtil.cpp
 * Author: churas
 * 
 * Created on August 17, 2012, 10:24 AM
 */

#include "StringUtil.hpp"
#include <string>
StringUtil::StringUtil() {
}

StringUtil::~StringUtil() {
}

/**
 * This method takes an integer and creates a string with padding of spaces
 * on left side of number so the string returned is of length size.
 * @param value Value to be written into string
 * @param maxvalue If value is greater then this value then ### will be printed
 * @param size width of resulting string
 * @return const char of string with spaces padding to left of value passed in
 */
const char *StringUtil::getIntAsPaddedString(int value,int maxvalue,int size){
    
    if (size <= 0){
        return "";
    }  
    char buff[size];
      
    if (value > maxvalue){
        snprintf(buff,size,"######");
    }
    else {
        snprintf(buff,size,"%d",value);
    }

    std::string rbuff = std::string(buff);
    std::string tmp;
    for (int i = 0; i < (size-rbuff.length());i++){
        tmp.insert(0," ");
    }
    rbuff.insert(0,tmp);
    return rbuff.c_str();
}


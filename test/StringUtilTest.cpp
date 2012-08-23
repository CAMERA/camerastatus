/* 
 * File:   StringUtilTest.cpp
 * Author: churas
 * 
 * Created on August 23, 2012, 11:06 AM
 */

#include "StringUtilTest.hpp"
#include "../src/StringUtil.hpp"
#include <string>
#include <string.h>
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(StringUtilTest);

void StringUtilTest::setUp() {
}

void StringUtilTest::tearDown() {
}

void StringUtilTest::testGetIntAsPaddedString() {
    int cmp;
    StringUtil sUtil;
    //check that 0 or negative size string will return empty string
    for (int i = 0; i > -2; i--) {
        const char *val = sUtil.getIntAsPaddedString(0, 123, i);
        CPPUNIT_ASSERT(val != NULL);
        CPPUNIT_ASSERT(strcmp(val, "") == 0);
    }

    //check that value is larger the 10 width is set to width of 10.
    cmp = strcmp(sUtil.getIntAsPaddedString(4, 3, 20), "##########");
    CPPUNIT_ASSERT(cmp == 0);

    //check that value is 10 width its set to width 10
    cmp = strcmp(sUtil.getIntAsPaddedString(4, 3, 10), "##########");
    CPPUNIT_ASSERT(cmp == 0);
    
    //check that value of 9 width is set to 9
    cmp = strcmp(sUtil.getIntAsPaddedString(4, 3, 9), "#########");
    CPPUNIT_ASSERT(cmp == 0);
    
    //check a negative value
    cmp = strcmp(sUtil.getIntAsPaddedString(-1, 3, 9), "       -1");
    CPPUNIT_ASSERT(cmp == 0);

    //check a 2 digit number no padding
    cmp = strcmp(sUtil.getIntAsPaddedString(32, 32, 2), "32");
    CPPUNIT_ASSERT(cmp == 0);
    
    //check a 2 digit number 1 padding
    cmp = strcmp(sUtil.getIntAsPaddedString(32, 32, 3), " 32");
    CPPUNIT_ASSERT(cmp == 0);

    //check a 2 digit number beyond threshold
    cmp = strcmp(sUtil.getIntAsPaddedString(32, 4, 2), "##");
    CPPUNIT_ASSERT(cmp == 0);

}

void StringUtilTest::testConvertStringToNumber(){
    
    StringUtil sUtil;
    
    //check passing in null returns -1
    CPPUNIT_ASSERT(sUtil.convertStringToNumber(NULL) == -1);
    
    //check passing string with a number in it
    CPPUNIT_ASSERT(sUtil.convertStringToNumber("2343") == 2343);
    
    //check passing string with % at end
    CPPUNIT_ASSERT(sUtil.convertStringToNumber("1233%") == 1233);
    CPPUNIT_ASSERT(sUtil.convertStringToNumber("1233 %") == 1233);

    
    //check passing string with % at front
    CPPUNIT_ASSERT(sUtil.convertStringToNumber("%22") == 0);
    
    //check passing non numeric string
    CPPUNIT_ASSERT(sUtil.convertStringToNumber("apple") == 0);
    
    //check passing in NA
    CPPUNIT_ASSERT(sUtil.convertStringToNumber("NA") == -2);
    
    //check passing in number with characters in it
    CPPUNIT_ASSERT(sUtil.convertStringToNumber("234A234") == 234);

    //check passing in number too large
    CPPUNIT_ASSERT(sUtil.convertStringToNumber("99999999999999999999999999999999999999999999") == -3);
}

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


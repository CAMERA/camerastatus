/* 
 * File:   StringUtilTest.hpp
 * Author: churas
 *
 * Created on August 23, 2012, 11:06 AM
 */

#ifndef STRINGUTILTEST_HPP
#define	STRINGUTILTEST_HPP

#include <cppunit/extensions/HelperMacros.h>

/**
 * Tests StringUtil class
 * @author churas
 */
class StringUtilTest : public CppUnit::TestFixture 
{
    CPPUNIT_TEST_SUITE( StringUtilTest );
    CPPUNIT_TEST( testGetIntAsPaddedString );
    CPPUNIT_TEST( testConvertStringToNumber );
    CPPUNIT_TEST( testSplitNullArgs );
    CPPUNIT_TEST( testSplitValidArgs );
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    
    void testGetIntAsPaddedString();
    void testConvertStringToNumber();
    void testSplitNullArgs();
    void testSplitValidArgs();
    
private:

};

#endif	/* STRINGUTILTEST_HPP */


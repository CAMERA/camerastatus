/* 
 * File:   StringUtilTest.hpp
 * Author: churas
 *
 * Created on August 23, 2012, 11:06 AM
 */

#ifndef STRINGUTILTEST_HPP
#define	STRINGUTILTEST_HPP

#include <cppunit/extensions/HelperMacros.h>

class StringUtilTest : public CppUnit::TestFixture 
{
    CPPUNIT_TEST_SUITE( StringUtilTest );
    CPPUNIT_TEST( testGetIntAsPaddedString );
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    
    void testGetIntAsPaddedString();
private:

};

#endif	/* STRINGUTILTEST_HPP */


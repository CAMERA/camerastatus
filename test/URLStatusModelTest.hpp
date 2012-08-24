/* 
 * File:   URLStatusModelTest.hpp
 * Author: churas
 *
 * Created on August 23, 2012, 4:42 PM
 */

#ifndef URLSTATUSMODELTEST_HPP
#define	URLSTATUSMODELTEST_HPP

#include <cppunit/extensions/HelperMacros.h>

class URLStatusModelTest : public CppUnit::TestFixture {
    
    CPPUNIT_TEST_SUITE( URLStatusModelTest );
    CPPUNIT_TEST( testRefresh );
    CPPUNIT_TEST( testGetClusterQueued );
    CPPUNIT_TEST_SUITE_END();
    
    
public:
    void setUp();
    void tearDown();
    
    void testRefresh();
    void testGetClusterQueued();
private:

};

#endif	/* URLSTATUSMODELTEST_HPP */


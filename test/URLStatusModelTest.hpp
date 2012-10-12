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
    CPPUNIT_TEST( testRefreshWithBadURL );
    //CPPUNIT_TEST( testRefreshWithFileURL );
    CPPUNIT_TEST( testGetClusterQueued );
    CPPUNIT_TEST( testGetClusterList );
    CPPUNIT_TEST_SUITE_END();
    
    
public:
    void setUp();
    void tearDown();
    
    void testRefreshWithBadURL();
    void testRefreshWithFileURL();
    void testGetClusterQueued();
    void testGetClusterList();
private:
    const char *getTmpDir();
    const char *writeJstatusFile(const char *fileName);
};

#endif	/* URLSTATUSMODELTEST_HPP */


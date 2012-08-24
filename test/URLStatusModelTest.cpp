/* 
 * File:   URLStatusModelTest.cpp
 * Author: churas
 * 
 * Created on August 23, 2012, 4:42 PM
 */

#include "URLStatusModelTest.hpp"

#include <string>


#include "../src/URLStatusModel.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(URLStatusModelTest);

void URLStatusModelTest::setUp() {
}

void URLStatusModelTest::tearDown() {
}

void URLStatusModelTest::testRefresh() {
    
    URLStatusModel usm("");
    usm.refresh();
    std::string yo = std::string(usm.getRawDataFromURL());
    CPPUNIT_ASSERT(yo.length() == 0);
    
    URLStatusModel usmtwo("http://aiwewefioj");
    usmtwo.refresh();
    yo = std::string(usmtwo.getRawDataFromURL());
    CPPUNIT_ASSERT(yo.length() == 0);
}

void URLStatusModelTest::testGetClusterQueued(){
    URLStatusModel usm("");
    
    usm.refresh("foojobsqueued: 25\nfoojobsrunning\n");
    CPPUNIT_ASSERT(usm.getClusterQueued("foo") == 25);
    
    usm.refresh("\nfoojobsqueued: 25\nfoojobsrunning\n");
    CPPUNIT_ASSERT(usm.getClusterQueued("foo") == 25);

    usm.refresh("\nfoojobsqueued: 25\nfoojobsrunning\n");
    CPPUNIT_ASSERT(usm.getClusterQueued("baa") == -2);

    usm.refresh("foojobsqueued: 25");
    CPPUNIT_ASSERT(usm.getClusterQueued("foo") == -2);
    
    usm.refresh("");
    CPPUNIT_ASSERT(usm.getClusterQueued("foo") == -2);
    
      usm.refresh("   ");
    CPPUNIT_ASSERT(usm.getClusterQueued("foo") == -2);
    
      usm.refresh("jobsqueued: 10\nfoojobsqueued: 25\nfoojobsrunning\n");
    CPPUNIT_ASSERT(usm.getClusterQueued("") == -2);
    
}


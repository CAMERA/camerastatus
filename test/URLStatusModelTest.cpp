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

    usm.refresh("foojobsqueued: 25\nfoojobsrunning\n");
    CPPUNIT_ASSERT(usm.getClusterQueued(NULL) == -2);

    
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

void URLStatusModelTest::testGetClusterList() {
    URLStatusModel usm("");
    
    usm.refresh(" ");
    std::list<std::string> cList = usm.getClusterList();
    CPPUNIT_ASSERT(cList.empty() == true);
    
    
    //try cluster list 6 elements
    usm.refresh("clusterlist: cylume,codonis,gordon,trestles,lonestar,ranger\n");
    cList = usm.getClusterList();
    CPPUNIT_ASSERT(cList.empty() == false);
    CPPUNIT_ASSERT(cList.size() == 6);
    
    CPPUNIT_ASSERT(cList.front() == "cylume");
    cList.pop_front();
    
    CPPUNIT_ASSERT(cList.front() == "codonis");
    cList.pop_front();
    CPPUNIT_ASSERT(cList.front() == "gordon");
    cList.pop_front();

    CPPUNIT_ASSERT(cList.front() == "trestles");
    cList.pop_front();

    CPPUNIT_ASSERT(cList.front() == "lonestar");
    cList.pop_front();

    CPPUNIT_ASSERT(cList.front() == "ranger");
    cList.pop_front();

    
    
    //try cluster list 1 element
    usm.refresh("clusterlist: codonis\n");
    cList = usm.getClusterList();
    CPPUNIT_ASSERT(cList.empty() == false);
    CPPUNIT_ASSERT(cList.size() == 1);
    
    CPPUNIT_ASSERT(cList.front() == "codonis");
    
    //try cluster list 2 elements
    usm.refresh("clusterlist: codonis,f\n");
    cList = usm.getClusterList();
    CPPUNIT_ASSERT(cList.empty() == false);
    CPPUNIT_ASSERT(cList.size() == 2);
    
    CPPUNIT_ASSERT(cList.front() == "codonis");
    cList.pop_front();
    
    CPPUNIT_ASSERT(cList.front() == "f");
    
   
    
}


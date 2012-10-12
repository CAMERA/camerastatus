/* 
 * File:   URLStatusModelTest.cpp
 * Author: churas
 * 
 * Created on August 23, 2012, 4:42 PM
 */

#include "URLStatusModelTest.hpp"

#include <string>
#include <stdio.h>
#include <unistd.h>

#include "../src/URLStatusModel.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(URLStatusModelTest);

void URLStatusModelTest::setUp() {
}

void URLStatusModelTest::tearDown() {
}

void URLStatusModelTest::testRefreshWithBadURL() {

    URLStatusModel usm("");
    usm.refresh();
    std::string yo = std::string(usm.getRawDataFromURL());
    CPPUNIT_ASSERT(yo.length() == 0);

    URLStatusModel usmtwo("http://aiwewefioj");
    usmtwo.refresh();
    yo = std::string(usmtwo.getRawDataFromURL());
    CPPUNIT_ASSERT(yo.length() == 0);
    usmtwo.refresh();
    yo = std::string(usmtwo.getRawDataFromURL());
    CPPUNIT_ASSERT(yo.length() == 0);
}

void URLStatusModelTest::testRefreshWithFileURL() {
    /**
     * @TODO FIGURE OUT WHY THIS TEST IS NOT WORKING!!!!!
     */
    //lets write out a file and then hit it a bunch of times
    //to verify URLStatusModel doesn't puke
    std::string outFile = std::string("file://") + std::string(writeJstatusFile("URLStatusModelTest.testRefreshWithFileURL.txt"));
    URLStatusModel usm(outFile.c_str());
    std::list<std::string> cList;
    usm.refresh();
    cList = usm.getClusterList();
    std::cout<<"cluster list size: "<<cList.size()<<std::endl;
    std::cout<<cList.front()<<std::endl;
    CPPUNIT_ASSERT(cList.size() == 6);
}

void URLStatusModelTest::testGetClusterQueued() {
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

const char *URLStatusModelTest::getTmpDir() {
    return "/tmp";
}

const char *URLStatusModelTest::writeJstatusFile(const char *fileName) {
    std::string outFile = std::string(getTmpDir()) + std::string("/") + std::string(fileName);
    FILE *fp = fopen(outFile.c_str(), "w");

    fprintf(fp, "update: 1349986082\n");
    fprintf(fp, "updatestr: 10/11 13:08:02 PDT\n");
    fprintf(fp, "sgeprojectassignerrunning: yes\n");
    fprintf(fp, "allowedworkflowsperuser: 1\n");
    fprintf(fp, "jobsunknown: 7\n");
    fprintf(fp, "jobsheld: 0\n");
    fprintf(fp, "jobsqueued: 56519\n");
    fprintf(fp, "jobsrunning: 245\n");
    fprintf(fp, "jobsqueuedheld: 56519\n");
    fprintf(fp, "localqueueload: 99%\n");
    fprintf(fp, "workflowqueueload: 100%\n");
    fprintf(fp, "localqueuetotalhosts: 141\n");
    fprintf(fp, "localqueuedownhosts: 43\n");
    fprintf(fp, "localqueuepercenthostsdown: 30%\n");
    fprintf(fp, "localqueueavailworkflowslots: 6\n");
    fprintf(fp, "localqueuedownworkflowslots: 4\n");
    fprintf(fp, "localqueuegflopsperjob: 14.88\n");
    fprintf(fp, "workflowsunknown: 2\n");
    fprintf(fp, "workflowsheld: 27\n");
    fprintf(fp, "workflowsqueued: 2\n");
    fprintf(fp, "workflowsrunning: 6\n");
    fprintf(fp, "workflowsqueuedheld: 29\n");
    fprintf(fp, "loggedinusers: 6\n");
    fprintf(fp, "diskfree: 9.4T\n");
    fprintf(fp, "percentdiskfull: 72%\n");
    fprintf(fp, "clusterlist: cylume,codonis,gordon,trestles,lonestar,ranger,steele\n");
    fprintf(fp, "cylumestatus: Available\n");
    fprintf(fp, "cylumejobsqueued: 56519\n");
    fprintf(fp, "cylumejobsrunning: 245\n");
    fprintf(fp, "cylumeload: 99%\n");
    fprintf(fp, "cylumediskfull: 72%\n");
    fprintf(fp, "cylumeremainhours: 99999999\n");
    fprintf(fp, "trestlesstatus: Disabled\n");
    fprintf(fp, "trestlesjobsqueued: 0\n");
    fprintf(fp, "trestlesjobsrunning: 0\n");
    fprintf(fp, "trestlesload: 59%\n");
    fprintf(fp, "trestlesdiskfull: 71%\n");
    fprintf(fp, "trestlesremainhours: 99021\n");
    fprintf(fp, "gordonstatus: Disabled\n");
    fprintf(fp, "gordonjobsqueued: 0\n");
    fprintf(fp, "gordonjobsrunning: 0\n");
    fprintf(fp, "gordonload: 59%\n");
    fprintf(fp, "gordondiskfull: 71%\n");
    fprintf(fp, "gordonremainhours: 925460\n");
    fprintf(fp, "codonisstatus: Disabled\n");
    fprintf(fp, "codonisjobsqueued: 0\n");
    fprintf(fp, "codonisjobsrunning: 0\n");
    fprintf(fp, "codonisload: 0%\n");
    fprintf(fp, "codonisdiskfull: 93%\n");
    fprintf(fp, "codonisremainhours: 99999999\n");
    fprintf(fp, "lonestarstatus: Disabled\n");
    fprintf(fp, "lonestarjobsqueued: 0\n");
    fprintf(fp, "lonestarjobsrunning: 0\n");
    fprintf(fp, "lonestarload: 100%\n");
    fprintf(fp, "lonestardiskfull: 3%\n");
    fprintf(fp, "lonestarremainhours: 50000\n");
    fprintf(fp, "rangerstatus: Disabled\n");
    fprintf(fp, "rangerjobsqueued: 0\n");
    fprintf(fp, "rangerjobsrunning: 0\n");
    fprintf(fp, "rangerload: 100%\n");
    fprintf(fp, "rangerdiskfull: 0%\n");
    fprintf(fp, "rangerremainhours: 100000\n");
    fprintf(fp, "steelestatus: Disabled\n");
    fprintf(fp, "steelejobsqueued: 0\n");
    fprintf(fp, "steelejobsrunning: 0\n");
    fprintf(fp, "steeleload: 94%\n");
    fprintf(fp, "steelediskfull: 0%\n");
    fprintf(fp, "steeleremainhours: 50000\n");
    fprintf(fp, "alljobsqueued: 56519\n");
    fprintf(fp, "alljobsqueuedheld: 56519\n");
    fprintf(fp, "alljobsrunning: 245\n");
    fprintf(fp, "lastlogin: 10/11/2012 13:08:59 by jlabonte\n");
    fprintf(fp, "totalworkflowsrun: 29866\n");
    fprintf(fp, "jbossmem: 38.6%\n");
    fprintf(fp, "lastworkflow: 10/11/2012 12:31:22 by rajeswari284\n");
    fprintf(fp, "lastportalerror: \n");
    fprintf(fp, "lastworkflowdownload: 10/11/12 12:22:05 DEBUG [workflows.ZipServlet] took 1980ms to download /home/validation/camera/release/wfexecutions/camilacarlos/1349212636401/outputs/\n");
    fprintf(fp, "avgworkflowwaittostart: 5454\n");
    fprintf(fp, "avgjobwaittostart: 18858\n");
    fprintf(fp, "lastline: true\n");
    fflush(fp);
    fclose(fp);
    return outFile.c_str();
}
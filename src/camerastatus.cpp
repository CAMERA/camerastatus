#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string>
#include "StatusModel.hpp"
#include "URLStatusModel.hpp"
#include "FakeStatusModel.hpp"
#include "CursesView.hpp"


void help(){
   fprintf(stderr,"Usage: camerastatus [ -h,-help,--help ] [ -url http URL ] [ -v,-version ]\n");
   fprintf(stderr,"Display current status of CAMERA system\n\n");
   fprintf(stderr,"   -h,--help\t\tDisplays this help\n");
   fprintf(stderr,"   -url [http URL]\tSets alternate URL to obtain CAMERA status from\n");
   fprintf(stderr,"   -simulate\t\tDisplays fake data to test UI\n");
   fprintf(stderr,"   -rawdata\t\tHits URL, dumping data received to stdout and exits\n");
   fprintf(stderr,"   -v,--version\t\tDisplay version\n");

   return;
}

void version(){
   fprintf(stderr,"camerastatus 0.5\n");
   return;
}

/**
 * Main function to start camerastatus.  
 * This program displays current status of
 * CAMERA system by pulling information from
 * a webpage and displaying it using 
 * the curses UI library.
 */
int main(int argc, const char* argv[]) {
   
    //Number of seconds to sleep between each update call to the CursesView 
    int sleepTimeout = 1;

    //Number of intervals to wait before hitting the URL to get fresh data.
    //to find out number of seconds of delay take this number times sleepTimeout
    int refreshInterval = 300;

    //used to check if user hit Q/q or r/R key while in loop
    char keyCheck;
    std::string command;
    std::string url = std::string("http://cylume.camera.calit2.net/jstatus.txt");

    StatusModel *status = NULL;
    int rawdata = 0;

    //loop through command line parameters passed into this program
    for (int i = 0; i < argc; i++){
      command = std::string(argv[i]);
      if (command.compare("-h") == 0 || 
          command.compare("-help") == 0 ||
          command.compare("--help") == 0){
         help();
         return 1;
      }
      else if (command.compare("-version") == 0  || 
               command.compare("--version") == 0){
         version();
         return 1;
      }
      else if (command.compare("-url") == 0){
         if (i+1>=argc){
            fprintf(stderr,"-url parameter requires an argument.  Run camerastatus -h for more information\n");
            return 2;
         }
         url = std::string(argv[++i]);
      }
      else if (command.compare("-rawdata") == 0){
          rawdata = 1;
      }
      else if (command.compare("-simulate") == 0){
         status = new FakeStatusModel();
      }
    }
 
    
    if (rawdata == 1){
        URLStatusModel usm(url.c_str());
        usm.refresh();
        printf("%s\n",usm.getRawDataFromURL());
        return 3;
    }
    
    if (status == NULL){	
	    status = (StatusModel *)new URLStatusModel(url.c_str());
    }
    
    
    
    status->refresh();
    
    //verify we got all the data if not bail
    const char *lastLine = status->getLastLine();
    if (lastLine == NULL || std::string(lastLine).compare("true") != 0){
        fprintf(stderr,"It appears the data on %s is NOT complete.\nPlease wait a minute and restart this program\n",
                url.c_str());
        return 4;
    }
    
    
    CursesView cv(status);
    cv.initialize();
    cv.draw();
    int counter = 0;
    while (1 == 1) {
        if (counter % refreshInterval == 0 || keyCheck == 'r' || keyCheck == 'R'){
           status->refresh();
           counter = 0; //reset the counter 
                        //this way if user hits r key the time will be sleepTimeout x refreshInterval
                        //in the future
        }
        cv.update();
        sleep(sleepTimeout);
        
        //exit if we see the q or Q key
        timeout(1);
        keyCheck = getch();
        if (keyCheck == 'q' || keyCheck == 'Q') {
            break;
        }
        counter++;
    }
    return 0;
}

#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include "StatusModel.hpp"
#include "URLStatusModel.hpp"
#include "FakeStatusModel.hpp"
#include "CursesView.hpp"

int main(int argc, const char* argv[]) {
    
    int sleepTimeout = 1;
    int refreshInterval = 300;
    char keyCheck;
    
    StatusModel *status = (StatusModel *)new URLStatusModel("http://cylume.camera.calit2.net/jstatus.txt");
    
    status->refresh();
    //return 0;
    CursesView cv(status);
    cv.initialize();
    cv.draw();
    int counter = 0;
    while (1 == 1) {
        if (counter % refreshInterval == 0 || keyCheck == 'r' || keyCheck == 'R'){
           status->refresh();
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

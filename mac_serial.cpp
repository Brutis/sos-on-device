#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <time.h>
#include <iostream>

using namespace std;

time_t seconds;

bool alive[2] = {false};
time_t timeStamp[2]; 

void send(){
    char command [1024];
    sprintf(command, "curl \"codeforindia.herokuapp.com/data?droneId=1&isAlive=%d&latitude=12.9734&longtitude=77.6442&objectId=2&objectIsAlive=%d\n\"", alive[0], alive[1]);
    printf("%s\n", command);
    system(command);
}

void handle(int i){
    if(!alive[i-1]){
        alive[i-1] = true;
        send();
    }
    timeStamp[i-1] = time (NULL);
}

void verify(){
    time_t now = time (NULL);
    for(int i = 0; i < 2; i++){
        if(alive[i] && ((int) difftime(now,timeStamp[i]) > 20)){
            alive[i] = false;
            send();
        }
    }
}



int main (int argc, const char * argv[]) {

    // define vars
    int STOP = 0;
    char buf[1024];

        int fd = open("/dev/cu.usbserial", O_RDONLY);
        if(fd == -1)
        {
            printf("%s", strcat("Unable to open /dev/tty.", argv[1]));
        }

        int res;
        while(STOP == 0)
        {
            while((res = read(fd,buf,1024)) == 0);
            {
                if(res > 0)
                {
                    buf[res]=0;
                    printf("%s:%d\n", buf, res);
                    handle(atoi(buf));
                    if(buf[sizeof(buf)]=='\n') break;   
                }
               verify();
            }
            sleep(1);
          }

    return 0;
}
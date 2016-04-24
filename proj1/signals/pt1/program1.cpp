#include <iostream>
#include <signal.h>
#include <string.h>

using namespace std;

// process, signal
int main(int argc, char* argv[]) {
    try
    {
        int status = kill( atoi(argv[1]), atoi(argv[2]));
        if (status == 0){
            printf( "Sent signal %s to process %s", argv[1], argv[2]);
        }
        else if (status == -1) {
            printf("Status[%d], Error[%d]: %s", status, errno, strerror(errno));
        }
        else
        {
            printf("Status[%d], unidentified path", status);
        }
    }
    catch (int e) {
        printf ("Error: unable to send signal... %d", e);
    }
    return 0;
}
#include <iostream>
#include <signal.h>

using namespace std;

// program pid signal
int main(int argc, char* argv[]) {
    try
    {
        kill( atoi(argv[1]), atoi(argv[2]));
        printf( "Sent signal %s to process %s", argv[1], argv[2]);
    }
    catch (int e) {
        printf ("Error: unable to send signal...");
    }
    return 0;
}
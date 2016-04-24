#include <iostream>
#include <signal.h>

using namespace std;

// program pid signal
int main(int argc, char* argv[]) {
    kill( atoi(argv[1]), atoi(argv[2]));
    printf( "Sent signal %d to process %d", argv[1], argv[2]);
}
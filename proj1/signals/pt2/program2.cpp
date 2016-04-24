#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Define the function to be called when ctrl-c (SIGINT) signal is sent to process
void signal_callback_handler(int signum) {

    printf("Caught signal %d\n",signum);

    if (signum == 1){
        exit(signum);
    }
}

int main() {

    // Register signal and signal handler
    signal(SIGHUP, signal_callback_handler); // 1
    signal(SIGILL, signal_callback_handler); // 4
    signal(SIGBUS, signal_callback_handler); // 7

    while(1) {
        printf("Running...\n");
        sleep(1);
    }
    return EXIT_SUCCESS;
}

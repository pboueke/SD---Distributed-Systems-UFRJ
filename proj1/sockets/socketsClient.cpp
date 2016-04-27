#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>

#define PORT "3490" // the port client will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once

bool isPrime( int number ) //LostInTheCode, SO
{
    // tests the number in the formats 6k-1, 6k and 6k+1 up until it's square root
    if ( ( (!(number & 1)) && number != 2 ) || (number < 2) || (number % 3 == 0 && number != 3) )
        return (false);
    for( int k = 1; 36*k*k-12*k < number;++k)
        if ( (number % (6*k+1) == 0) || (number % (6*k-1) == 0) )
            return (false);
    return true;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
              s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure


    if (send(sockfd, "Hello There!", 12, 0) == -1){
        perror("client: error send");
    }

    while(1) {
            if ((numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0)) == -1) {
                perror("client: error recv");
            }

        buf[numbytes] = '\0';

        if(numbytes != 0){
            printf("client: received '%s', ",buf);
        }

        int prod = atoi(buf);

        if (prod == 0)
        {
            printf("\nTerminating consumption.");
            break;
        }
        else if (isPrime(atoi(buf)))
        {
            printf("which is prime.\n");
            const char* prodString = std::to_string(prod).c_str();
            char * sendmsg = new char[strlen(prodString)+11];
            strcpy(sendmsg,prodString);
            strcat(sendmsg," is prime.");
            if (send(sockfd, sendmsg, strlen(sendmsg), 0) == -1){
                perror("client: error send");
            }
            delete sendmsg;
        }
        else
        {
            printf("which isn't prime.\n");
            const char* prodString = std::to_string(prod).c_str();
            char * sendmsg = new char[strlen(prodString)+13];
            strcpy(sendmsg,prodString);
            strcat(sendmsg," isn't prime.");
            if (send(sockfd, sendmsg, strlen(sendmsg), 0) == -1){
                perror("client: error send");
            }
            delete sendmsg;
        }
    }
    close(sockfd);

    return 0;
}

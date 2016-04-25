#include <iostream>
#include <unistd.h>

using namespace std;

inline bool IsPrime( int number ) //LostInTheCode, SO
{
    // tests the number in the formats 6k-1, 6k and 6k+1 up until it's square root
    if ( ( (!(number & 1)) && number != 2 ) || (number < 2) || (number % 3 == 0 && number != 3) )
        return (false);
    for( int k = 1; 36*k*k-12*k < number;++k)
        if ( (number % (6*k+1) == 0) || (number % (6*k-1) == 0) )
            return (false);
    return true;
}

// PRODUCER
void producer(int iterations, int file)
{
    int sent, product = 0;
    FILE *pipe_wr_end = fdopen(file, "w");
    for (int i = 0; i <= iterations; i++)
    {
        product += rand() % 100;
        sent = fprintf(pipe_wr_end, "%d", product);
        printf("Product sent[%d]: %d\n", sent, product);

    }
    fprintf(pipe_wr_end, "%d", 0);
    fclose(pipe_wr_end);
}

// CONSUMER
void consumer(int file)
{
    int ok, number;
    FILE *pipe_rd_end = fdopen(file, "r");
    while(1) {
        ok = fscanf(pipe_rd_end, "%i", &number);
        if(ok >= 1)
        {
            printf("Consumer received[%d] %d", ok, number);
            if (number == 0) {
                printf(", terminating consumption.\n");
                break;
            }
            if (IsPrime(number))
            {
                printf(", which is prime.\n");
            }
            else
            {
                printf(", which isn't prime.\n");
            }
        }
        else
        {
            //EOF or error
            printf("Consumer done[%d].\n", ok);
            break;
        }
    }
    fclose(pipe_rd_end);
}
int main(int argc, char* argv[])
{
    pid_t pid;
    int pd[2];

    // building the pipe
    if(pipe(pd))
    {
        printf("Pipe failed\n");
        return EXIT_FAILURE;
    }

    pid = fork();
    if(pid == (pid_t)0) { //child
        close(pd[1]);
        consumer(pd[0]);
        return EXIT_SUCCESS;
    }
    else{ //parent
        close(pd[0]);
        producer(atoi(argv[1]), pd[1]);
        return EXIT_SUCCESS;
    }


}

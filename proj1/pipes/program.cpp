#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <vector>

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
    for (int i = 0; i < iterations; i++)
    {
        product += rand() % 100;
        string pd = to_string(product) + " ";
        sent = fprintf(pipe_wr_end, "%s", pd.c_str());
        printf("Product sent[%d]: %d\n", sent, product);

    }
    fprintf(pipe_wr_end, "%d", 0);
    fclose(pipe_wr_end);
}

// CONSUMER
void consumer(int file)
{
    int ok, retries;
    char cnumber;
    string current = "";

    FILE *pipe_rd_end = fdopen(file, "r");

    while(1) {
        ok = fscanf(pipe_rd_end, "%c", &cnumber);

        if(ok >= 1)
        {
            if (cnumber == '0')
            {
                printf("Terminating consumption");
                break;
            }
            else if (cnumber == ' ')
            {
                if (IsPrime(stoi(current)))
                {
                    printf("Consumer got %s, which is prime.\n", current.c_str());
                }
                else
                {
                    printf("Consumer got %s, which isn't prime.\n", current.c_str());
                }
                current = "";
            }
            else
            {
                current.push_back(cnumber);
            }
        }
        else
        {
            printf("Consumer waiting...\n");
            sleep(100);
            retries++;
            if (retries == 100)
            {
                printf("Consumer leaving!\n");
                break;
            }
            //EOF or error
            //printf("Consumer done[%d].\n", ok);
            //break;
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
        waitpid(pid, NULL, 0);
        //sleep(1000);
        return EXIT_SUCCESS;
    }


}

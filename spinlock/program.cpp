#include <iostream>
#include <pthread.h>
#include <atomic>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define MEMORY_SIZE 5000000000
#define CHUNK_SIZE  5000000000

struct Lock {
    bool held = 0;
};

struct Arguments
{
    // the array with N numbers of 8 bits each
    int8_t* arr;
    // array of length 2 with accumulators to fragment the array with numbers, distributing the blovks among the threads
    long* range;
    // the sum variable
    long* distributed_sum;
    // lockspin
    Lock *lock;
};

void acquire(struct Lock *spinlock)
{
    while(__sync_lock_test_and_set(&spinlock->held, 1));
}

void release (struct Lock *spinlock)
{
    spinlock->held = 0;
}

void* partialSum (void *arguments)
{
    // takes an Argument struct pointer that must be casted into a variable to be used
    // this function is designed to be used with pthread_create
    long partial_sum = 0;
    Arguments *obj = (struct Arguments*) arguments;
    for (long i = obj->range[0]; i < obj->range[1]; ++i)
    {
        partial_sum += (long) obj->arr[i];
    }
    acquire(obj->lock);
    *obj->distributed_sum += partial_sum;
    release(obj->lock);
}


// number of numbers (N), number of threads (K)
int main(int argc, char const *argv[]) {

    struct timespec start, finish;
    //double elapsed;

    // generating the random seed
    int seed = (int) time(NULL);
    srand((unsigned int) seed);

    //taking command line arguments
    long an = atol(argv[1]);
    long n = an;
    int k  = atoi(argv[2]);

    int chunks = 1;
    int current = 0;

    if (an > (long)MEMORY_SIZE)
    {
        n = CHUNK_SIZE;
        chunks = an/(n+1) + 1;
    }

    // initializing the random numbers array and calculating the real sum
    int8_t* arr = new int8_t[n];
    long control_sum = 0;
    long distributed_sum = 0;
    struct Lock lock;

    pthread_t *threads = new pthread_t[k];
    // each thread will receive a distinct argument object pointing to the numbers array, distributed sum value and lock
    Arguments **arguments = new Arguments *[k];
    long *range = new long[2];

    for (int i = 0; i < k; ++i) {
        //each element of Arguments is a pointer to an Argument object, which is initialized as seen below
        arguments[i] = new Arguments();
        // each object points to the global lock, numbers array and the total sum
        arguments[i]->lock = &lock;
        arguments[i]->distributed_sum = &distributed_sum;
        arguments[i]->arr = arr;
    }

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    for (current; current < chunks; ++current) {

        if (current == chunks - 1)
        {
            n = an - (chunks - 1) * MEMORY_SIZE;
        }

        for (long i = 0; i < n; ++i) {
            // 8bit number between -100 and 100
            int8_t b = (int8_t) (rand() % (201) - 100);
            arr[i] = b;
            control_sum += b;
        }
        //cout << "Control sum equals: " << to_string(control_sum) << endl;

        // each block size is the the total number of numbers by the number of threads
        long block = n / k;
        // first block range
        range[0] = 0;
        range[1] = block;

        for (int i = 0; i < k; ++i) {
            // accumulators (range) are used to give each object a different block to sum, each block consisting of a different range within the numbers array
            arguments[i]->range = new long[2];
            arguments[i]->range[0] = range[0];
            arguments[i]->range[1] = range[1];
            range[0] = range[1];
            // the last block must go from range[0] to n
            range[1] = (i == k - 2) ? n : range[0] + block;
            pthread_create(&threads[i], NULL, partialSum, (void *) arguments[i]);
        }

        for (int i = 0; i < k; ++i) {
            pthread_join(threads[i], NULL);
        }
        //cout << "Distributed sum equals: " << to_string(distributed_sum) << endl;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    // cleanup
    delete[] arr;
    for (int i = 0; i < k; ++i) {
        delete[] arguments[i]->range;
        delete arguments[i];
    }
    delete[] arguments;


    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    cout << to_string(time_span.count()) << endl;

    return 0;
}


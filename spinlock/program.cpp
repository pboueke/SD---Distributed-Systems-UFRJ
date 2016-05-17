#include <iostream>
#include <pthread.h>
#include <atomic>

using namespace std;

struct Lock {
    bool held = 0;
};

struct Arguments
{
    // the array with N numbers of 8 bits each
    int8_t* arr;
    // array of length 2 with accumulators to fragment the array with numbers, distributing the blovks among the threads
    long* accumulator;
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
    Arguments *args = (struct Arguments*) arguments;
    for (long i = args->accumulator[0]; i < args->accumulator[1]; ++i)
    {
        partial_sum += (long) args->arr[i];
    }
    acquire(args->lock);
    args->distributed_sum += partial_sum;
}


// number of numbers (N), number of threads (K)
int main(int argc, char const *argv[]) {

    // generating the random seed
    int seed = (int) time(NULL);
    srand((unsigned int) seed);

    //taking command line arguments
    long n = atol(argv[1]);
    int k  = atoi(argv[2]);

    // initializing the random numbers array and calculating the real sum
    int8_t* arr = new int8_t[n];
    long control_sum = 0;
    for (long i = 0; i < n; ++i)
    {
        // 8bit number between -100 and 100
        int8_t b = (int8_t) (rand() % (201) - 100);
        arr[i] = b;
        control_sum += b;
    }
    cout << "Array created, control sum equals " << to_string(control_sum) << endl;

    // initializing variables for the distributed sum
    long distributed_sum = 0;
    Lock* lock = new Lock();
    Arguments** arguments = (Arguments **) new Arguments[k];
    pthread_t* threads = new pthread_t[k];
    long block = n / k;
    long* accumulator = new long[2];
    accumulator[0] = 0;
    accumulator[1] = block;

    for (int i = 0; i < k; ++i)
    {
        //each element of Arguments is a pointer to an Argument object, which is initialized as seen below
        arguments[i] = new Arguments();
        // each object points to the global lock, numbers array and the total sum
        arguments[i]->lock = (Lock*) &lock;
        arguments[i]->distributed_sum = &distributed_sum;
        arguments[i]->arr = arr;
        // accumulators are used to give each object a different block to sum
        arguments[i]->accumulator[0] = accumulator[0];
        arguments[i]->accumulator[1] = accumulator[1];
        accumulator[0] = accumulator[1];
        accumulator[1] = accumulator[0] + block;
        pthread_create(&threads[i], NULL, partialSum, (void*) arguments[i]);
        if (i == k - 2) {
            // if n is not divisible by 2, the last block must go from accumulator[0] to n
            accumulator[1] = n;
        }
    }

    for(int i = 0; i < k; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    // cleanup
    delete arr, arguments, threads;

    cout << "Distributed sum equals: " << to_string(distributed_sum) << endl;

    return 0;
}

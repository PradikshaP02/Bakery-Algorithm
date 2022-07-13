
#include <stdio.h>
#include <string.h>
#include <pthread.h>                                    //Contains function declarations and mappings for threading interfaces and defines a number of constants used by those functions

#define sync __sync_synchronize()                       //This function synchronizes data in all threads.
#define tCount 8

int threadArray[tCount];
int select[tCount];
int res;

void lThread(int thread)
{
    select[thread] = 1;                                 //The desire of getting into the critical section is expressed
    sync;
    int maximum = 0;
    for (int i = 0; i < tCount; i++)                    //This for loop aims at finding the maximum number among the threads
    {
        int num = threadArray[i];
        if(num > maximum)
        {
            maximum = num;
        }
    }
    threadArray[thread] = maximum + 1;                 //New number i given as max+1
    sync;
    select[thread] = 0;                                //Again setting the select as 0 as it obtains a number
    sync;

    for (int other = 0; other < tCount; other++)       //Starting the entry section
    {
                                                       // Applying the bakery algorithm conditions
        while (select[other])
        {
        }
        sync;
        while (threadArray[other] != 0 && (threadArray[other] < threadArray[thread] || (threadArray[other] == threadArray[thread] && other < thread)))
        {
        }
    }
}

void uThread(int thread)                                //Exit section code, the number is reset to 0
{
    sync;
    threadArray[thread] = 0;
}
                                                        // CRITICAL Section
void use_res(int thread)
{

    if (res != 0)
    {
        printf("The Resource was acquired by %d, but used by %d!\n", thread, res);
    }
    res = thread;
    printf("\n\t\t %d is using resource...\n", thread);

    sync;
    sleep(2);
    res = 0;
}

void *thread_body(long arg)                              //This function shows the basic implementation
{

    long thread = arg;                                   //Basically, locking the thread, using the resource and unlocking
    lThread(thread);
    use_res(thread);
    uThread(thread);
    return NULL;
}

int main()
{                                                         //Code for presenting the output
    int choice;
    printf("\n\t\t\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\n");
    printf("                                                               \n");
    printf("                      \xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\n");
    printf("                         Critical section problem                                \n");
    printf("                      \xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\n");
    printf("                                                              \n");
    printf("                    Solving using Lamport's Bakery algorithm               \n");
    printf("                                                               \n");
    printf("                                                              \n");
    printf("\t\t\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\n\n\n");
    printf("\n\t LET'S MOVE ON.....\n");

    memset((void *)threadArray, 0, sizeof(threadArray));  // memset() - allocates memory and writes in it, (pointer to the start, what to write, size)
    memset((void *)select, 0, sizeof(select));
    res = 0;

    // Declaring the thread variables
    pthread_t threads[tCount];                            //pthread_t is the data type used to uniquely identify a thread. It is returned by pthread_create() and used by the application in function calls that require a thread identifier.

    for (int i = 0; i < tCount; i++)                      // Creating a new thread with the function
    {
        pthread_create(&threads[i], NULL, &thread_body, (long)i); //The pthread_create() function starts a new thread in the calling process
                                                                /*  The first argument is a pointer to thread_id which is set by this function.
                                                                    The second argument specifies attributes. If the value is NULL, then default attributes shall be used.
                                                                    The third argument is name of function to be executed for the thread to be created.
                                                                    The fourth argument is used to pass arguments to the function, myThreadFun.*/
    }
    for (int i = 0; i < tCount; i++)
    {
                                                         // Reaping the resources used by
        pthread_join(threads[i], NULL);
    }
    return 0;
}

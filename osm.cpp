#include <iostream>
#include <sys/time.h>
#include <cmath>
#include "osm.h"


#define INVALID 0
#define ERROR (-1)
#define ITERATION_DEFAULT 1000
#define UNROLLING_FACTOR 5
#define SEC_TO_NANO 1000000000
#define MICRO_TO_NANO 1000

timeval start;
timeval end;
void func(){};



int osm_init()
{
    if(gettimeofday(&start, nullptr) == ERROR)
    {
        return ERROR;
    }

    return 0;
}

int osm_finalizer()
{
    if(gettimeofday(&end, nullptr) == ERROR)
    {
        return ERROR;
    }

    return 0;
}



double osm_operation_time(unsigned int iterations)
{
    unsigned int totalIterations = iterations == INVALID ? ITERATION_DEFAULT : iterations;
    int x1 = 0, x2 = 0, x3 = 0, x4 = 0, x5 = 0, y = 3 , z = 4;
    auto rounds = (unsigned int)std::ceil(totalIterations / UNROLLING_FACTOR);



    if(osm_init() == ERROR)
    {
        return ERROR;
    }


    for(unsigned int i = 0; i < rounds ; i++)
    {
        x1 = y + z;
        x2 = y + z;
        x3 = y + z;
        x4 = y + z;
        x5 = y + z;
    }


    if(osm_finalizer() == ERROR)
    {
        return ERROR;
    }
    
    double time = ((end.tv_sec - start.tv_sec) * SEC_TO_NANO) +
                  (end.tv_usec - start.tv_usec) * MICRO_TO_NANO;



    (void)x1;
    (void)x2;
    (void)x3;
    (void)x4;
    (void)x5;

    return time / totalIterations;
}

double osm_function_time(unsigned int iterations)
{

    unsigned int totalIterations = iterations == 0 ? ITERATION_DEFAULT : iterations;
    auto rounds = (unsigned int)std::ceil(totalIterations / UNROLLING_FACTOR);

    if(osm_init() == ERROR)
    {
        return ERROR;
    }

    for(unsigned int i = 0; i < rounds; i++)
    {
        func();
        func();
        func();
        func();
        func();
    }

    if(osm_finalizer() == ERROR)
    {
        return ERROR;
    }

    double time = ((end.tv_sec - start.tv_sec) * SEC_TO_NANO) +
                  (end.tv_usec - start.tv_usec) * MICRO_TO_NANO;

    return time / totalIterations;
}

double osm_syscall_time(unsigned int iterations)
{

    unsigned int totalIterations = iterations == 0 ? ITERATION_DEFAULT : iterations;
    auto rounds = (unsigned int)std::ceil(totalIterations / UNROLLING_FACTOR);


    if(osm_init() == ERROR)
    {
        return ERROR;
    }

    for(unsigned int i = 0; i < rounds; i ++)
    {
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;

    }

    if(osm_finalizer() == ERROR)
    {
        return ERROR;
    }

    double time = ((end.tv_sec - start.tv_sec) * SEC_TO_NANO) +
                  (end.tv_usec - start.tv_usec) * MICRO_TO_NANO;

    return time / totalIterations;
}

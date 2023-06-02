#include "active_objects.h"


int check_prime(unsigned int num)
{
    if (num < 2)
        return 1;
    if (num%2 == 0 && num != 2)
        return 1;
    
    for ( int i = 3; i * i <= num; i+=2)
    {
        if (num % i == 0)
            return 1;
    }
    return 0;
}

void randonNum(activeObject *ao, int numIterations)
{
    unsigned int* nums = malloc(numIterations * sizeof(unsigned int));
    if (nums == NULL)
    {
        printf("malloc failed.\n");
        exit(1);
    }
    
    for (int i = 0; i < numIterations; i++)
    {
        nums[i] = rand() % 900000 + 100000;
        enqueue(getActiveObjectQueue(ao), &nums[i]);
        
        if (i < numIterations - 1)
        {
            sleep(1);
        }
    }
}
#include "active_objects.c"
#include "active_objects.h"
#include "randon_prime.c"
void *active_1(void *argument)
{
    unsigned int *number_ptr = argument;
    int ans = check_prime(*number_ptr);
    char* ans2 = ans == 0 ? "true" : "false";
    
    printf("%u\n%s\n", *number_ptr, ans2);

    enqueue(getActiveObjectQueue(_p2), number_ptr);

    return NULL;
}

void *active_2(void *argument)
{
    unsigned int *number = argument;

    *number += 11;
    int ans = check_prime(*number);
    char* ans2 = ans == 0 ? "true" : "false";
    printf("%u\n%s\n", *number, ans2);

    enqueue(getActiveObjectQueue(_p3), number);

    return NULL;
}

void *active_3(void *argument)
{
    unsigned int *number = argument;

    *number -= 13;

    printf("%u\n", *number);

    enqueue(getActiveObjectQueue(_p4), number);

    return NULL;
}

void *active_4(void *argument)
{
    unsigned int *number = argument;
    *number += 2;
    printf("%u\n", *number);
    return NULL;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("write a number.  like this  ./st_pipeline [number] [(if want)seed] \n");
        return 0;
    }
    if (argc > 3)
    {
        printf("wrong writing, ./st_pipeline [number] [(if want)seed] \n");
        return 0;
    }

    int seed = argc == 3 ? atoi(argv[2]) : time(NULL);
    srand(seed);

    // init(&_p1, &_p2, &_p3, &_p4);
    _p1 = createAO(active_1);
    _p2 = createAO(active_2);
    _p3 = createAO(active_3);
    _p4 = createAO(active_4);
    int i = atoi(argv[1]);
    //run first active object
    randonNum(_p1, i);
    stop(_p1, _p2, _p3, _p4);

    return 0;
}

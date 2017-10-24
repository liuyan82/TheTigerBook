/* This file is intentionally empty.  You should fill it in with your
   solution to the programming exercise. */
#include "util.h"
#include "slp.h"
#include "maxarg.h"
#include "interp.h"

int main(int argc, char ** argv)
{
    printf("1. ====================================\n");
    printf("Maximum %d args in print statement\n", maxargs(prog()));
        
    printf("2. ====================================\n");
    interp(prog());
    return 0;
}

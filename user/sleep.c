#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc < 2)
    {
    	fprintf(2, "Usage: sleep seconds...\n");
    	exit(1);
    }
    
    int i = atoi(argv[1]);
    int j = sleep(i);
    fprintf(0, "you are going to sleep %d seconds", j);
    
    exit(0);
}

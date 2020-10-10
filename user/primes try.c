#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int number = 1;
    int data[1] = {101};
    
    for(int i=0; i<3; i++)
    {
	    if(fork()==0)
	    {
		
		fprintf(0, "child %d number: %d\n", i, number);
		number++;
		fprintf(0, "child %d number +1: %d\n", i, number);
		
		fprintf(0, "child %d data: %d\n", i, data[0]);
		data[0]++;
		fprintf(0, "child %d data +1: %d\n", i, data[0]);
		
		// exit(0);
	    }
	    else
	    {
		sleep(10);
		
		fprintf(0, "parent %d number: %d\n", i, number);
		number+=2;
		fprintf(0, "parent %d number +2: %d\n", i, number);
		
		fprintf(0, "parent %d data: %d\n", i, data[0]);
		data[0]+=2;
		fprintf(0, "parent %d data +2: %d\n", i, data[0]);
		
		wait(0);
		
		break;
	    }
	
	sleep(20);
	
	fprintf(0, "main number: %d\n", number);
        number+=3;
        fprintf(0, "main number +3: %d\n", number);
    
        fprintf(0, "main data: %d\n", data[0]);
        data[0]+=3;
        fprintf(0, "main data +3: %d\n", data[0]);
    }
    
    

    
    exit(0);
}

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int sendToRight(int[], int);

int
main(int argc, char *argv[])
{
    int data[34];
    int index = 0;
    for(int i=2; i<=35; i++)
    {
        data[index] = i;
        index++;
    }
    
    int new_length = 34;
    while(new_length>=1)
    {
    	new_length = sendToRight(data, new_length);
    }
    
    
    /*
    int new_length = sendToRight(data, 34);
    for(int j=0; j<new_length; j++)
    {
        fprintf(0, "data: %d", data[j]);
    }
    */
    
    exit(0);
}


int
sendToRight(int data[], int length)
{
    int p[2];
    char inbuf[1];
    
    int data_copy[34];
    // copy the data for use and reset all data to 0
    for(int j=0; j<length; j++)
    {
        data_copy[j] = data[j];
        data[j] = 0;
    }
    
    int return_length = 0;
    
    pipe(p);
    if(fork()==0)
    {
    	close(p[1]);
    	
    	int index_child = 0;
    	while(read(p[0], inbuf, 1)>0)
    	{
    	    if(inbuf[0]==0)
    	        break;
    	        
    	    // fprintf(0, "child receive %d", inbuf[0]);
    	    data[index_child] = inbuf[0];
    	    index_child++;
    	    return_length++;
    	}
    	
    	close(p[0]);
    	wait(0);
    }
    else
    {
    	close(p[0]);
    	
    	for(int i=0; i<length; i++)
    	{
    	    if(i==0)
    	    {
    	        fprintf(0, "prime %d\n", data_copy[0]);
    	        // sleep(10);
    	        
    	        // if there is only 1 number left, print it and don't do anything sent to child
    	    	if(length==1)
    	    	{
    	    	    char x[1];
    	    	    x[0] = 0;
    	    	    
    	    	    // fprintf(0, "length 1 now!\n");
    	    	    write(p[1], x, 1);
    	    	    break;
    	    	}
    	    }
    	    else
    	    {
    	        
    	    	    
    	    	
    	    	char x[1];
    	    	x[0] = data_copy[i];
    	    	if(data_copy[i] % data_copy[0] != 0)
    	    	{
    	    	    write(p[1], x, 1);
    	    	}
    	    }  
    	      
    	}
    	
    	close(p[1]);
    	exit(0);
    }
    
    
    // fprintf(0, "length %d", length);
    return return_length;
}

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p1[2], p2[2];
    
    // use "while -> pipe -> fork" not "pipe -> fork -> while"
    
    
    
    pipe(p1);  // parent to child
    pipe(p2);  // child to parent
    if(fork()==0)
    {
        char inbuf_child[1];
        
        close(p2[0]); // close parent read
        close(p1[1]); // close parent write
        
        // receive data from parent
        int data_child[34] = {0};
        int data_child_index = 0;
        while(read(p1[0], inbuf_child, 1)>0)
    	{
    	    fprintf(0, "child receive %d", inbuf_child[0]);
    	    data_child[data_child_index] = inbuf_child[0];
    	    data_child_index++;
    	}
    	
    	// send data to parent
    	for(int i=0; i<data_child_index; i++)
    	{
    	    fprintf(0, "child is sending...\n");
    	    char x[1];
    	    x[0] = data_child[data_child_index];
    	    write(p2[1], x, 1);
    	}
    	
        close(p1[0]); // close child read
        close(p2[1]); // close child write
    }
    else
    {
        int inbuf_parent[1];
        
        close(p1[0]); // close child read
        close(p2[1]); // close child write
        
        // initialize the first data
        int data[34];
        int index = 0;
        for(int i=2; i<=35; i++)
        {
            data[index] = i;
            index++;
        }
        
        // send the first data
        int length = 34;
        for(int i=0; i<length; i++)
    	{
    	    char x[1];
    	    x[0] = data[i];
    	    if(data[i] % data[0] != 0)
    	    {
    	    	write(p1[1], x, 1);
    	    }
    	}
    	
    	// receive data from child
        int data_parent[34] = {0};
        int data_parent_index = 0;
        fprintf(0, "parent reads begin...\n");
        while(read(p2[0], inbuf_parent, 1)>0)
    	{
    	    fprintf(0, "parent is reading...\n");
    	    fprintf(0, "parent receive %d", inbuf_parent[0]);
    	    data_parent[data_parent_index] = inbuf_parent[0];
    	    data_parent_index++;
    	}
    	fprintf(0, "parent reads end...\n");
    	
    	for(int j=0; j<data_parent_index; j++)
    	{
    	    fprintf(0, "%d", data_parent[j]);
    	}
    	
    	
        close(p2[0]); // close parent read
        close(p1[1]); // close parent write
    	
    	wait(0); // this make the program exit normally
    }
    
    
    exit(0);
}

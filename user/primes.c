#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p[2];
    
    // use "while -> pipe -> fork" not "pipe -> fork -> while"
    // child: read data, print prime, and maintan the data and the count -> close()
    // parent: write data by count -> close() -> break while() loop
    // misunderstand on the differences between variables and pipe during fork()...
    // multiple pipes seem interesting too...
    
    // initialize the data
    int data[34];
    int data_count = 0;
    for(int i=2; i<=35; i++)
    {
        data[data_count] = i;
        data_count++;
    }
    
    while(data_count>0)
    {
        pipe(p);
        
        // here is the child
        if(fork()==0)
        {
            close(p[1]);
            
            int prime = 0;
            char inbuf_child[1];
            data_count = 0; // add an "int" prefix by mistake
            
            while(read(p[0], inbuf_child, 1)>0)
            {
                int inbuf_int = inbuf_child[0];
                
                // the first item must be prime
                if(prime==0)
                {
                    prime = inbuf_child[0];
                    fprintf(0, "prime %d\n", prime);
    
                }
                    
                // remove not prime items, directly update the data[] and count
                if(inbuf_int % prime != 0)
                {
                    // basically datacount should less than i, if not, change it later
                    data[data_count++] = inbuf_int; 
                }
            }
            
            // fprintf(0, "child data count: %d\n", data_count);
            
            close(p[0]);
        }
        // here is the parent
        else
        {
            
            close(p[0]);
            
            for(int i=0; i<data_count; i++)
            {
                char x[1];
                x[0] = data[i];
                // fprintf(0, "%d\n", x[0]);
                write(p[1], x, 1);
            }
            
            // fprintf(0, "parent data count: %d\n", data_count);
            
            close(p[1]);
            
            wait(0);
            
            break;
        }
    }
    
    
    exit(0);
}

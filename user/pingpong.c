#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    // fprintf(0, "main begin\n");
    
    int p1[2], p2[2];
    char inbuf[1];
    
    if(pipe(p1) < 0 || pipe(p2) < 0)
    {
    	fprintf(0, "pipe failed.");
    	exit(1);
    }
    
    // fprintf(0, "before fork\n");
    
    if(fork() == 0)
    {
    	// fprintf(0, "this is child process");
    	close(p2[0]);
    	close(p1[1]);
    	
    	read(p1[0], inbuf, 1);
    	close(p1[0]);
    	
    	// fprintf(0, "child receive %d bytes: %c", n, inbuf[0]);
    	fprintf(0, "%d: received ping\n", getpid());
    	//fprintf(0, "child 1\n");
    	write(p2[1], inbuf, 1);
    	//fprintf(0, "child 2\n");
    	close(p2[1]);
    	//fprintf(0, "child 3\n");
    }
    else
    {
    	close(p2[1]);
    	close(p1[0]);
    	
    	// fprintf(0, "this is parent process");
    	write(p1[1], "a", 1);
    	close(p1[1]);
    	
    	read(p2[0], inbuf, 1);
    	close(p2[0]);
    	// fprintf(0, "parent receive %d bytes: %c", n, inbuf[0]);
    	fprintf(0, "%d: received pong\n", getpid());
    	//fprintf(0, "parent 1\n");
    	
    	wait(0);
    	//fprintf(0, "parent 2\n");
    }
    
    //fprintf(0, "all 1\n");
    exit(0);
    //fprintf(0, "all 2\n");
}

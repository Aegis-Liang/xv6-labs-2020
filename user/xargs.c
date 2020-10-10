#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define buf_length 256
int
main(int argc, char *argv[])
{

  // try out what the arguments are
  // printf("argv[0]: %s\n, argv[1]: %s\n, argv[2]: %s\n, argv[3]: %s\n", argv[0], argv[1], argv[2], argv[3]);

    
      
    
  if(fork()==0)
  {
      // child process
      
      // try stdin with command: echo 1 22 333 | xargs echo line
  char buf[1024];
  
  while(read(0, buf, buf_length) > 0)
  {
    //printf("stdin: %s\n", buf);
    //printf("buf[0]: %c\n", buf[0]);
    
    char *buf_argument[10] = {""};
    int buf_argument_index = 0;
    //char current_argument[100];
    
    
    int i = 0; // used for loop the buf characters
    int j = 0; // used for argument character index
    char *current_argument = (char *)malloc(sizeof(char) * buf_length);
    while(buf[i] != '\0')
    {
      
      // printf("buf: %d, %s\n", i, buf);
         
      // if found space or \n, store to next argument;
      if(buf[i]==' ' || buf[i]=='\n')
      {
        //buf_argument[buf_argument_index][j] = '\0';
        current_argument[j] = '\0';
        buf_argument[buf_argument_index] = current_argument; // missing this line will make all the result empty
        //printf("buf_argument[%d]: %s\n", buf_argument_index, buf_argument[buf_argument_index]);

        
        
        // below code is prepared for next loop
        buf_argument_index++;
        j=0;
        
        current_argument = (char *)malloc(sizeof(char) * buf_length);
        
      }
      else
      {
        //buf_argument[buf_argument_index][j] = buf[i];
        current_argument[j] = buf[i];
        //printf("buf_argument[%d][%d]: , %c\n", buf_argument_index, j, buf_argument[buf_argument_index][j]);
        //printf("current_argument[j] = buf[i]: %c = %c\n", current_argument[j], buf[i]);
        j++;
      }
        
      
      i++;
    }
    
    //exec here with [command] [old_arguments] [new_arguments]
    // execute command with new argument
    char *new_argument[10];
    int new_argument_count = 0;
    for(int k=1; k<argc; k++)
    {
       // the argv[0] is xargs, ignore it
       // the argv[1] may be echo, keep it in new_argument[0], the exec() function seems to ignore this argument during execution
       new_argument[k-1] = argv[k];
       new_argument_count++;     
    }
    
    // add new arguments
    for(int l=0; l<buf_argument_index; l++)
    {
        new_argument[new_argument_count+l] = buf_argument[l];
    }
       
         
     
    // exec
    exec(argv[1], new_argument);
        
    // exec fail
    printf("exec() fail");
  }
  }
  else
  {
    // main process
    wait(0);
  }
    
  
  
  exit(0);
}

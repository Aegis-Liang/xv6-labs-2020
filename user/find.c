#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname0(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), 'a', DIRSIZ-strlen(p));
  return buf;
}

void
strcat(char *dest, char *src)
{
  int length = strlen(src);
  int offset = strlen(dest);
  for(int i=0; i<length; i++)
    memset(dest+offset+i, src[i], 1);
}

char*
fmtname(char *path)
{
  // static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  
  return p;
}

void
find(char *path, char * filename)
{
  // comment for xargs execise
  //fprintf(0, "finding %s %s\n", path, filename);
  
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  /*
  case T_FILE:
    printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    break;
  */

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    
    
      
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      
    
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      
      // comment for xargs exercise
      // printf("buf: %s\n", buf);
      
      if(st.type==T_FILE)
      {
        if(strcmp(fmtname(buf), filename) == 0)
          printf("%s/%s\n", path, fmtname(buf)); 
        continue;
      }
      
      if(st.type==T_DIR)
      {
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
          printf("ls: path too long\n");
          break;
        }
        
      // Don't recurse into "." and ".."
      if(strcmp(fmtname(buf), ".") == 0 || strcmp(fmtname(buf), "..") == 0)
          continue;
      else
        {
          // comment all unnecessary print otherwise cannot open folder in xargs 
          //printf("inside folder: [%s] / [%s] %d %d %l\n", path, fmtname(buf), st.type, st.ino, st.size);
          
          char nextPath[256];
          strcat(nextPath, path);
          strcat(nextPath, "/");
          strcat(nextPath, fmtname(buf));
          find(nextPath, filename);
        }
      }
      
      /* 
      // int cmpResult = strcmp(fmtname(buf), ".");
      // fprintf(0, "%s compares to . result %d\n", fmtname(buf), cmpResult);
      
      // Don't recurse into "." and ".."
      if(strcmp(fmtname(buf), ".") == 0 || strcmp(fmtname(buf), "..") == 0)
          continue;
      
      if(strcmp(fmtname(buf), filename) == 0)
          printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
      */
    }
    
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  /*
  char a[10] = "abc";
  char d[3] = "de";
  
  strcat(a, d);
  fprintf(0, "%s", a);
  */
  
  if(argc < 3)
  {
      fprintf(2, "Usage: find directroy find_string ...\n");
      exit(1);
  }
  
  char *path = argv[1];
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    exit(1);
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    exit(1);
  }

  switch(st.type){
  /*
  case T_FILE:
    if(strcmp(fmtname(buf), argv[2]) == 0)
        printf("%s/%s %d %d %l\n", argv[1], fmtname(buf), st.type, st.ino, st.size);
        //printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    break;
  */
  
  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      
      if(st.type==T_FILE)
      {
        if(strcmp(fmtname(buf), argv[2]) == 0)
          printf("%s/%s\n", argv[1], fmtname(buf)); 
      }
      
      
      if(st.type==T_DIR)
      {
        
        
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
          printf("ls: path too long\n");
          break;
        }
        
        // Don't recurse into "." and ".."
        if(strcmp(fmtname(buf), ".") == 0 || strcmp(fmtname(buf), "..") == 0)
          continue;
        else
        {
          // comment all unnecessary print otherwise cannot open folder in xargs
          // printf("folder: [%s] / [%s] %d %d %l\n", argv[1], fmtname(buf), st.type, st.ino, st.size);
          
          char nextPath[256] = "";  // not setting it = "" will occurs error 
          strcat(nextPath, argv[1]);
          strcat(nextPath, "/");
          strcat(nextPath, fmtname(buf));
          
          find(nextPath, argv[2]);
        }
      }
        
      
      //printf("%s%s %d %d %d\n", p, fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  
  close(fd);
  
  exit(0);
}

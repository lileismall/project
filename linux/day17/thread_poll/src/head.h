#ifndef __HEAD_H__
#define __HEAD_H__
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>  //查看进程id，
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/msg.h>
#include <signal.h>
#include <strings.h>
#include <pthread.h>
#include <setjmp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/uio.h>       
#include <sys/sendfile.h>

#define ARGS_CHECK(argc,num){ if(argc != num) { printf("error argc\n");return -1; }}

#define ERROR_CHECK(ret,retval,funcName){if(ret==retval) { printf("%d\n",errno);perror(funcName); return -1; }}

#define THREAD_ERROR_CHECK(ret,funcname)  {if(ret!=0){printf("%s:%s\n",funcname,strerror(ret));return -1;}}



#endif

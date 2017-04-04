


#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>


#include<sys/types.h>  /*提供类型pid_t,size_t的定义*/
#include<sys/stat.h>
#include<fcntl.h>


#include "err.h"

/*@sock_ntop @*/
char *Sock_ntop(const struct sockaddr *sa,socklen_t addrlen){
     char portstr[8];
     static char str[128];
     switch (sa->sa_family)
     {
         case AF_INET:
         {
             struct sockaddr_in *sin=(struct sockaddr_in *)sa;
             if(inet_ntop(AF_INET,&sin->sin_addr,str,sizeof(str))==NULL){
                 return NULL;
             }
             if((ntohs(sin->sin_port))!=0){
                 snprintf(portstr,sizeof(portstr),":%d",ntohs(sin->sin_port));
                 strcat(str,portstr);
             }
             return str;
         }
     default:
         break;
     }

}

/*@sock_ntop end@*/

/*@readn writen @*/
/*@readn@*/
ssize_t readn(int fd,void *vptr,size_t n){
  
  size_t nleft;
  ssize_t nread;
  char *ptr;
  ptr=vptr;
  nleft=n;
  while(nleft>0){
      if((nread=read(fd,ptr,nleft))<0)
      {
          if(errno==EINTR){
             nread=0;
          }else{
              return -1;
        }
          
      }else if(nleft==0){
          break;

      }

      nleft-=nread;
      ptr+=nread;
  }
  return (n-nleft);

}


/*@readn end@*/

ssize_t writen(int fd,void *vptr,size_t sz){
 size_t nleft;
 ssize_t nwriten;

 const char *ptr;
 ptr=vptr;
 
 nleft=sz;
 while(nleft>0){
     if((nwriten=write(fd,ptr,nleft))<0){
         if(errno==EINTR||nwriten<0){
             nwriten=0;
         }else{
             return -1;
         }
     }
     nleft-=nwriten;
     ptr+=nwriten;
 }
  return sz;
}
/*@writen end@*/
ssize_t readline(int fd,void *vptr,size_t maxlen){
 ssize_t rc,n;
 char c,*ptr;
 ptr=vptr;
 for(n=1;n<maxlen;n++){
     again:
     if((rc=read(fd,&c,1))==1){
         *ptr++=c;
         if(c=='\n'){
             break;
         }
     }else if(rc==0){
         *ptr=0;
         return n-1;
     }else {
         if(errno==EINTR){
             goto again;
             return (-1);
         }
     }
     
 }
}

/*@ main function*/
int main(){

   int fd;

   char buf[MAX_BUF];

   bzero(buf,sizeof(buf));

   fd=open("test_err.c",O_RDONLY);

   readline(fd,buf,MAX_BUF);

   printf("%s",buf);

   return 0;

}
/*@main end*/


/*@err.h create by jackwu@*/



#ifndef  __ERROR__JW___H__
#define  __ERROR__JW___H__
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
//#include <string.h>


#define  MAX_BUF        4096

static void handler(int,int ,const char *fmt,va_list);


/*@err_exit  function@*/
void err_exit(int error,const char *fmt,...){
  
  va_list ap;  
  va_start(ap,fmt);
  handler(1,error,fmt,ap);
  va_end(ap);
  exit(1);
}

/*@err_exit  end@*/

/*@ err_dump@*/
void errr_dump(const char *fmt,...){

  va_list ap;  
  va_start(ap,fmt);
  handler(1,errno,fmt,ap);
  va_end(ap);

  abort();
  exit(1);

}

/*@ err_dump end@*/

/*@err_msg function@*/
void err_msg(const char *fmt,...){
  va_list ap;
  va_start(ap,fmt);
  handler(0,0,fmt,ap);
  va_end(ap);
}

/*@err_msg function end@*/

/*@ err_ret@*/
void err_ret(const char *fmt,...){
  va_list ap;  
  va_start(ap,fmt);
  handler(1,errno,fmt,ap);
  va_end(ap);
}

/*@ err_ret end@*/

/*@err_sys@*/
void err_sys(const char *fmt,...){
  va_list ap;
  va_start(ap,fmt);
  handler(1,errno,fmt,ap);
  va_end(ap);
  exit(1);
}

/*@err_sys end@*/



/*@handler  start@*/
static void handler(int flag,int error,const char *fmt,va_list ap){

    char buf[MAX_BUF];
    vsnprintf(buf,sizeof(buf),fmt,ap);
    if(flag){//whether increase string
         snprintf(buf+strlen(buf),MAX_BUF-strlen(buf),"%s\n",strerror(errno));
    }
    strcat(buf,"\n");
   fflush(stdout);
   fputs(buf,stderr);
   fflush(NULL);
}
/*@handler  end@*/





#endif
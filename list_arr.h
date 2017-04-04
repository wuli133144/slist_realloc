


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define  err_exit(m) \
do{ \
    perror(m);\
    exit(errno);\
}while(0);
/*@jackwu create list inode@*/
typedef  struct _inode{
    struct _inode *next;
    int data;
    int cur_size;
}t_inode,*t_pnode;

/*@list inode end@*/


/*@jackwu realoc@*/

void  *Realloc(void *mem_address, unsigned int newsize){
      
 void *p;
 if((p=realloc(mem_address,newsize))==NULL){
     err_exit("realloc error");
 }
  return p;
}

/*@jackwu realoc@*/

/*$malloc$    */

void * Malloc(size_t sz){
    void *p;
    if((p=malloc(sz))==NULL){
        err_exit("malloc failed!");
    }
    
    return p;
}


/*$malloc end$*/

/*@list impl@*/


void create(t_pnode *head){
     if(*head==NULL){
         *head=(t_pnode)Malloc(sizeof(t_inode));
         (*head)->next=NULL;
         (*head)->cur_size=1;//not include headnode
     }
}

void * insert(t_pnode head,int lhs){

     t_pnode p=NULL;
     p=(t_pnode)Realloc(head,sizeof(t_inode)*(head->cur_size+1));
    
  if(head==NULL){
     head=p; 
  }else{
    while(head->next!=NULL){
        head=head->next;
    }
    head->next=NULL;
    head->data=lhs;
  }
}

/*@show listnode@*/
void show(t_pnode head){
    head=head->next;
    while(head!=NULL)
    {
        printf("data:%d\n",head->data);
        head=head->next;
    }

}
/*@show end@*/
/*@list ene@*/




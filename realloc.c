


#include "list_arr.h"
/*@show end@*/
int main(int argc,char **argv){
      
    
    t_inode *head=NULL;
    
    create(&head);
    
    insert(head,12);
    insert(head,13);
    insert(head,14);
    insert(head,15);
   
    show(head);


    return 0;
}
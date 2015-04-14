/* deleting an element from myprptr->senderqueue-its basically deprptr->senderqueueing */

#include<xinu.h>

pid32  my_delete()
{
  struct procent *prptr;
  prptr = &proctab[currpid];
  pid32 element;
   if(prptr->front==-1)
    {
      kprintf("\n Underflow");
      }
    element=prptr->senderqueue[prptr->front];
     if(prptr->front==prptr->rear)
	 prptr->front=prptr->rear=-1;
		         
     else
     {
       if(prptr->front==NPROC-1)
	    prptr->front=0;
				        
       else
	  prptr->front++;
	
       }
  return element;							 
 }

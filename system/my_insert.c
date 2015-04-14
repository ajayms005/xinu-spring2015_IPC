/* this is a function to insert an element in my queue*/

#include<xinu.h>

void my_insert(pid32 item, pid32 pid)
{
 struct procent * prptr;
 prptr = &proctab[pid];

 if((prptr->front==0 && prptr->rear==NPROC-1)||(prptr->front==prptr->rear+1))
     kprintf("\n Queue OverFlow Occured");
       
 else if(prptr->front==-1 && prptr->rear==-1)
         {
	    prptr->front=0;
	    prptr->rear=0;
	    prptr->senderqueue[prptr->rear] = item;
		      
           }
   else if(prptr->rear==NPROC-1 && prptr->front!=0)
        {
	  prptr->rear=0;
	  prptr->senderqueue[prptr->rear] = item;
	  }
    else
	 {
	   prptr->rear++;
	   prptr->senderqueue[prptr->rear]= item;
         }	
 }

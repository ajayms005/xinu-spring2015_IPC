/* sendb.c - blocking version of send */

#include<xinu.h>


syscall sendb(
        pid32 pid,
	umsg32  msg,
	int32 maxwait
	)
{
   intmask mask;            /*Saved interrupt mask*/
   struct procent *prptr;   /* Ptr to process table entry*/

   if (maxwait < 0) {
     kprintf("Negative maxwait: Should fail\n");
     return SYSERR;
   }

   mask = disable();
   if(isbadpid(pid)) {
          restore(mask);
	  return SYSERR;
   }

   prptr = &proctab[pid];

   if(prptr->prstate == PR_FREE){
       restore(mask);
       return SYSERR;
   }


  
     if(prptr->prhasmsg){
             proctab[currpid].prstate = PR_SND;
	     proctab[currpid].sndmsg = msg;
	     proctab[currpid].sndflag = 1;
	   
	       
	     
	     if(maxwait>0)
	     {
	       insertd(currpid, sleepq, maxwait);
	       }
	     
	     my_insert(currpid, pid); //adding the sending process to the receiver's queue
	     resched();

	  }
       
       if((prptr->prhasmsg)==FALSE)
       {
       prptr->prmsg = msg;             /* Deliver message              */
       prptr->prhasmsg = TRUE;         /* Indicate message is waiting  */
       proctab[currpid].sndflag = 0;
      
     

       if (prptr->prstate == PR_RECV) {
	   ready(pid);
       } else if (prptr->prstate == PR_RECTIM) {
            unsleep(pid);
	    ready(pid);
       }

   }
   else{
     proctab[currpid].sndflag = 0 ;
     restore(mask);
     return TIMEOUT;
     }
    
    restore(mask);
    return OK;

}



 

  

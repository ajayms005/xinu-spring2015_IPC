/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;                   /* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/

        pid32 this_sender = -1;

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/
	if(!((prptr->front ==-1) && (prptr->rear==-1))){
	     int sender =0;
	     while(sender==0){
	        pid32 sendpid;
		if(!((prptr->front ==-1) && (prptr->rear==-1)))
		{
		   sendpid = my_delete();
		   if(proctab[sendpid].sndflag!=0)
		   {
		    sender = 1;
		    this_sender = sendpid;
                    }
	          }
	        else{
	             restore(mask);
	             return msg;
	            }
	}
	}
	


//	prptr->prmsg = proctab[sendpid].sndmsg;
//	prptr->prhasmsg = TRUE;
//	proctab[sendpid].sndflag = 0;
	
       if(unsleep(this_sender)!=SYSERR)
	  ready(this_sender);

	restore(mask);
	return msg;
}

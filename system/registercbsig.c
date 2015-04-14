#include <xinu.h>

syscall	registercbsig(uint16 asig, int (* func) (void), uint32 optarg)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process table entry	*/

	mask = disable();
	if (func == NULL) {
		restore(mask);
		return SYSERR;
	}
	
	

	prptr = &proctab[currpid];
	prptr->asigcb = 1;
	if(asig == ARECV){
	
	prptr->optarg = 0;
	prptr->arecvfunc = func;
	
	}
	
	if(asig == AALRM){
	
	prptr->alarmfunc = func;
	prptr->optarg = optarg;
	kprintf("going to add globalclock %d\n",myglobalclock);
	prptr->alarm_time = myglobalclock + optarg ;	
	//kprintf("going out add %d\n",prptr->alarm_time);
	}
	restore(mask);		/* restore interrupts */
	return OK;
}

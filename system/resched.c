/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
			if(ptold->alarm_time > 0){
			//	kprintf("value of myglblclk %d\n",myglobalclock);
			//	kprintf("Inside alarm_time\n");
				if(myglobalclock >= ptold->alarm_time){

				//	kprintf("Inside alarm_time another if loop\n");

					ptold->alarm_time = -1;
					(*ptold->alarmfunc)();
					//		ptnext->prhasmsg = FALSE;
				}


			}



			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/*Calling callback function	*/
	struct procent *ptnext;
	ptnext = &proctab[currpid];
	
	if(ptnext->asigcb == 0){
	if(ptnext->func!=NULL && ptnext->prhasmsg == 1){
	*(ptnext->abuf) = ptnext->prmsg;
	ptnext->prhasmsg = 0;
	(*ptnext->func)();
	
	}
	}

	if(ptnext->asigcb ==1){
	
		if(ptnext->optarg == 0){
		
		if(ptnext->arecvfunc!=NULL && ptnext->prhasmsg == 1){
		
			(*ptnext->arecvfunc)();
		//	ptnext->prhasmsg = FALSE;
		
		}
		
		}
//		if(ptnext->optarg > 0){
		
			 // kprintf("outside alarm_time\n");
//		if(ptnext->alarmfunc!=NULL && ptnext->prhasmsg == TRUE){
		if(ptnext->alarm_time > 0){
		         // kprintf("value of myglblclk %d\n",myglobalclock);
			 // kprintf("Inside alarm_time\n");
			if(myglobalclock >= ptnext->alarm_time){

			 // kprintf("Inside alarm_time another if loop\n");
			
			ptnext->alarm_time = -1;
			(*ptnext->alarmfunc)();
	//		ptnext->prhasmsg = FALSE;
		}
		
		
		}
	
	}
	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}

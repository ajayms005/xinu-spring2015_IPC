#include <xinu.h>

syscall	registercb(umsg32 *abuf, int (*func)(void))
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process table entry	*/

	mask = disable();
	if ((abuf == NULL) || (func == NULL)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[currpid];
	prptr->abuf = abuf;
	prptr->func = func;
	restore(mask);		/* restore interrupts */
	return OK;
}

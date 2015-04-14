/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>


int bonusrecvhandler3(void){
	kprintf("after 3 = %d\n", myglobalclock);
//	umsg32 msg;
	//    msg = receive();
	// kprintf("Inside bonushandler2\n");
	kprintf("Bonus Passed\n");
	return OK;
}
int bonusrecvhandler4(void){
	kprintf("After-4 = %d\n", myglobalclock);
//	umsg32 msg;
	//    msg = receive();
	// kprintf("Inside bonushandler2\n");
	kprintf("Bonus Passed\n");
	return OK;
}




void bonusrecv3(void)
{

	kprintf("Before-3  = %d\n", myglobalclock);
	if(registercbsig(AALRM,&bonusrecvhandler3,50) != OK) {
		kprintf("recv1 handler registration failed\n");
	}
	// kprintf("Before  = %d\n", myglobalclock);
	while(1) {}
}

void bonusrecv4(void)
{

	kprintf("Before-4  = %d\n", myglobalclock);
	if(registercbsig(AALRM,&bonusrecvhandler4,100) != OK) {
		kprintf("recv1 handler registration failed\n");
	}
	// kprintf("Before  = %d\n", myglobalclock);
	while(1) {}
}

umsg32 proc1buf;
umsg32 proc2buf;

int myrecvhandler1(void) {
      kprintf("msg received = %d for process = %d\n",proc1buf,currpid);
      return(OK);
}

int myrecvhandler2(void) {
	          
kprintf("msg received = %d for process = %d\n",proc2buf,currpid);
return(OK);
}

void recv1(void)
{
   if (registercb(&proc1buf,&myrecvhandler1) != OK) {
            kprintf("recv1 handler registration failed\n");
    }
    while(1) {}
}

void recv2(void)
{
  if (registercb(&proc2buf,&myrecvhandler2) != OK) {
	 kprintf("recv2 handler registration failed\n");
 }
	 while(1) {}
 }

void send1(pid32 pid1, umsg32 msg1, umsg32 msg2)
{
   send(pid1, msg1);
  // sleepms(5);
   send(pid1, msg2);
}



void send2(pid32 pid1, umsg32 msg1)
{
  send(pid1, msg1);
 }

void sendb1(pid32 pid1,umsg32 msg1, umsg32 msg2, umsg32 msg3, umsg32 msg4)
{
  
  //kprintf("Before 1st: %d\n",myglobalclock);
  sendb(pid1, msg1, 10);
 // kprintf("After 1st: %d\n", myglobalclock);
  sendb(pid1, msg2, 15);
  sendb(pid1, msg3, 1);
   sendb(pid1, msg4, 0);
}

void sendb2(pid32 pid1, umsg32 msg1, int32 maxwait)
{
 sendb(pid1, msg1, maxwait);
 }

 void recvb2()
 {
  umsg32 msg;
  msg = receive();
  kprintf("The message is %d\n", msg);
  }


void recvb1()
{ 
 umsg32 msg;
 int i = 0;
 for(i=0;i<4;i++)
 {
  msg = receive();
  kprintf("The message is %d\n", msg);
  }
}


int bonusrecvhandler1(void){
   umsg32 msg;
      msg = receive();
      kprintf("Bonus1: msg received= %d\n",msg);
      return OK;
	  }
	
int bonusrecvhandler2(void){
    
    umsg32 msg;
    msg = receive();
   
    kprintf("Bonus2: msg received= %d\n",msg);
    return OK;
}


void bonusrecv1(void)
{
   if (registercbsig(ARECV,&bonusrecvhandler1,0) != OK) {
            kprintf("recv1 handler registration failed\n");
	  }
	
	while(1) {}
 }

void bonusrecv2(void)
 {
    if (registercbsig(ARECV,&bonusrecvhandler2,0) != OK) {
	kprintf("recv1 handler registration failed\n");
      }
     while(1) {}
 }




process	main(void)
{
	kprintf("\nHello World!\n");
	kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
	kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
	kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
	kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
	kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
//	kprintf("\n...creating a shell\n");
//	recvclr();
//	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */
/*
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	*/
//pid32 pid1, pid2, pid3;

// pid2 = create(bonusrecv3,1024,20,"r2",0);
// pid3 = create(bonusrecv4,1024,20,"r2",0);

// resume(pid2);
// resume(pid3);

       // pid32 rec1, rec2, snd1,snd2;
       // rec1 = create(recv1,1024,20,"r1",0);
       // rec2 = create(recv2,1024,20,"r2",0);
       // snd1 = create(send1,1024,20,"s1",3,rec1,1);
       //	snd2 = create(send2,1024,20,"s2",3,rec2,2);
       // resume(snd1);
       // resume(rec1);
       // resume(rec2);
//	resume(snd2);
//
  // pid32 snd1, snd2,snd3,snd4,snd5, rcv1, rcv2;
  // rcv1 = create(recvb2,1024,20,"r1",0);

  // rcv2 = create(recvb2,1024,20,"r1",0);
  // snd1 = create(sendb2,1024,20,"s1",3,rcv1,'a', 10);
  // snd2 = create(sendb2,1024,20,"s2",3,rcv1,'b',5);
  // snd3 = create(sendb2,1024,20,"s3",3,rcv1,'c',15);
  // snd4 = create(sendb2,1024,20,"s4",3,rcv1,'d',0);
  // snd5 = create(sendb2,1024,20,"s5",3,rcv1,'e',8);

  // resume(snd2);
  // resume(snd1);
  // resume(snd3);
  // resume(snd4);
  // resume(rcv1);
  // resume(snd5);
  // resume(rcv2);
  
  // pid32 rec1, rec2, snd1;
  // rec1 = create(bonusrecv1,1024,20,"r1",0);
  // rec2 = create(bonusrecv2,1024,20,"r2",0);
  // snd1 = create(send1,1024,20,"s1",4,rec1,rec2,'a','b');
  // resume(snd1);
  // resume(rec1);
  // resume(rec2);
  
  pid32 rec1, rec2, snd1;
  rec1 = create(bonusrecv1,1024,20,"r1",0);
	         
  snd1 = create(send1,1024,20,"s1",3,rec1,'a','b');
  resume(snd1);
  resume(rec1);


  


//return OK;
}

// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;

    for (num = 0; num < 5; num++) {
	    printf("*** thread %d id %d looped %d times\n", which, currentThread->GetThreadID(), num);
        
        for(int i = 0; i < 128; i++) { 
            if (allThreads[i] == currentThread) {
            }
        }
        
        currentThread->Yield();
        
    }
}

void
SimpleThread2(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
	    printf("*** thread %d id %d looped %d times\n", which, currentThread->GetThreadID(), num);
        currentThread->Yield();
    }
    // 每个
    Thread *t = new Thread("forked thread");
    t->Fork(SimpleThread2, 1);
    t = new Thread("forked thread");
    t->Fork(SimpleThread2, 1);
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread");

    t->Fork(SimpleThread, 1);
    SimpleThread(0);
}

//----------------------------------------------------------------------
// ThreadTest2
// 	Create 2 forked threads.
//----------------------------------------------------------------------

void
ThreadTest2()
{
    Thread *t = new Thread("Forked 1");
    
    t->Fork(SimpleThread, 1);
    
    t = new Thread("Forked 2");
    
    t->Fork(SimpleThread, 2);
}

//----------------------------------------------------------------------
// ThreadTest3
// 	Call SimpleThread2
//	Every SimpleThread2 create two new SimpleThread2.
//----------------------------------------------------------------------

void
ThreadTest3()
{
    Thread *t = new Thread("Forked 1");
    
    t->Fork(SimpleThread2, 1);
}

//----------------------------------------------------------------------
// ThreadTest4
// 	Test TS Command
//----------------------------------------------------------------------

void
ThreadTest4()
{
    ThreadTest2();
    PrintThreadsStatus();
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    case 2:
    ThreadTest2();
    break;
    case 3:
    ThreadTest3();
    break;
    case 4:
    ThreadTest4();
    break;
    default:
	printf("No test specified.\n");
	break;
    }
}


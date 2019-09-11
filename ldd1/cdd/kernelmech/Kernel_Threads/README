Kernel Threads:
--------------
A kernel thread is a way to implement background tasks inside the kernel. 

Use of Kernel Threads:
-------------------
1. The task can be busy handling asynchronous events or sleep-waiting for an event to occur. 
2. It needs access to kernel data structures because the actual detection of events is done by other parts of
the kernel.
3. It has to invoke a user mode helper program, which is a time-consuming operation.

Kernel thread vs User Thread:
----------------------------

Kernel threads are similar to user processes, except that they live in kernel space and have access to kernel functions and data structures. 

Many device drivers utilize the services of kernel threads to implement assistant or helper tasks. For example, the khubd
kernel thread, which is part of the Linux USB driver core monitors USB hubs and configures USB devices when they are hot-plugged into the system.

Create a Kernel Thread:
----------------------
kernel_thread(mykthread, NULL,CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD);

The flags specify the resources to be shared between the parent and child threads. 
CLONE_FILES specifies that open files are to be shared, and CLONE_SIGHAND requests that signal handlers be shared.

The thread starts by invoking daemonize(), which performs initial housekeeping and 
changes the parent of the calling thread to a kernel thread called kthreadd. 
Each Linux thread has a single parent.

daemonize() blocks all signals by default, use allow_signal() to enable delivery  if your thread desires to handle a particular signal.

There are no signal handlers inside the kernel, so use signal_pending() to check for signals and take appropriate action.

ps -ef
The entries in the right­most column showing up in square brackets are kernel threads.
Parent process ID is 2 i.e. [kthreadd]

Example of Kthread: softirqd

cat /proc/<proc ID>/status
cat /proc/<proc ID>/maps




Message Queues:

In many ways, message queues are like named pipes, but without the complexity associated with opening and closing the pipe.
However, using messages doesn’t get us away from the problems that we have with named pipes, such
as blocking on full pipes.

Advantage:

Message queues provide a reasonably easy and efficient way of passing data between two unrelated pro-
cesses. 
They have the advantage over named pipes that the message queue exists independently of both
the sending and receiving processes, which removes some of the difficulties that occur in synchronizing
the opening and closing of named pipes.

Disadvantage:

The bad news is that, just like pipes, there’s a maximum size
limit imposed on each block of data and also a limit on the maximum total size of all blocks on all
queues throughout the system.



  msgget()  :  create a message queue

  msgsnd() :  Send a message

  msgrcv() :  Receive a message





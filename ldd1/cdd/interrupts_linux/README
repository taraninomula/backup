The following examples explains How to implement interrupts in Linux.

LDD_CDD_06_01: This is basic example shows how to implement keyboard/mouse device interrupt in linux as a module. 

LDD_CDD_06_02: This example shows how to implement tasklets in Linux. 

LDD_CDD_06_03: This example shows parallel port interrupt.    

Device driver
------------
When the device file is first opened, register an interrupt handler for the device’s interrupt channel.

Interrupt handler
-----------------
Called when an interrupt is raised.
Acknowledge the interrupt
If needed, schedule a tasklet taking care of handling data.
Otherwise, wake up processes waiting for the data.

Tasklet
-------
Process the data
Wake up processes waiting for the data

Device driver
-------------
When the device is no longer opened by any process,
unregister the interrupt handler

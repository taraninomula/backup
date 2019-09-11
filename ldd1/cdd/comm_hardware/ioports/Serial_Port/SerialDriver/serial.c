/***************************************************************************
 *      Organisation    : Kernel Masters, KPHB, Hyderabad, India.          *
 *      facebook page   : www.facebook.com/kernelmasters                   *
 *                                                                         *
 *  Conducting Workshops on - Embedded Linux & Device Drivers Training.    *
 *  -------------------------------------------------------------------    *
 *  Tel : 91-9949062828, Email : kernelmasters@gmail.com                   *
 *  Website: www.kernelmasters.org                                         *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation. No warranty is attached; we cannot take *
 *   responsibility for errors or fitness for use.                         *
 ***************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include<linux/delay.h>
#include<linux/ioport.h>
#include<linux/interrupt.h>
#include<linux/ioctl.h>
#include<asm/io.h>
#include<linux/delay.h>
#define NAME serial_driver  
#define short_base 0x3f8
#include"serial_ioctl_commands.h"

#define LINE_CTRL_REG short_base+3
#define DIVISOR_LATCH_L   short_base+0
#define DIVISOR_LATCH_H  short_base+1
#define RECIEVE_REG   short_base
#define TRANSMIT_REG  short_base
#define INT_ENABLE_REG short_base+1
#define INT_IDENTIFICATION_REG short_base+2
//1.8432mhz
#define BAUD_9600_L 0x0c
#define BAUD_9600_H 0x00
#define BAUD_19200_L 0x06
#define BAUD_19200_H 0x00


 


//recieve buffer
unsigned char rbuff,tbuff='k';
int rflag=0,tflag=1;







//Function Prototypes
int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *indoe, struct file *filp);
ssize_t NAME_write(struct file *filp,const char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t NAME_read(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp);
int NAME_ioctl(struct file*, unsigned int,unsigned long);
irqreturn_t irq_handler (int irq_num ,void *dev_id ,struct pt_regs *regs);

//structure for paralel port resource
struct resource *serial_port;




//Structure that defines the operations that the driver provides
struct file_operations fops = 
{
	.owner   = THIS_MODULE,
	.open    = NAME_open, 
	.read    = NAME_read,
	.write   = NAME_write,
	.release = NAME_release,
        .unlocked_ioctl   = NAME_ioctl, 
};

//Structure for a character driver
struct cdev *my_cdev;


//Init Module
static int __init CharDevice_init(void)
{
	int result;
	int MAJOR,MINOR;
	dev_t Mydev;
	Mydev = MKDEV(255,0);//Create a device number
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);

	printk("\nSerial port Device driverloaded sucessfully\n");
	printk("\nThe Major Number is %d...THe Minor Number is %d\n",MAJOR,MINOR);

	result=register_chrdev_region(Mydev,1,"MyCharDevice");//register device region.....
	if(result<0)
	{
		printk(KERN_ALERT "\nThe Region requested for is not obtainable\n");
		return(-1);
	}
	printk("\nDevice driver registered sucessfully\n");
	
	my_cdev = cdev_alloc();//allocate memory to Char Device structure
	my_cdev->ops = &fops;//link our file operations to the char device

	result=cdev_add(my_cdev,Mydev,1);//Notify the kernel abt the new device
	if(result<0)
	{
		printk(KERN_ALERT "\nThe Char Device has not been created......\n");
		return (-1);
	}
	printk("\nChar Device has been created sucessfully\n");

      
        //register for Serial Port region i.e. 0x3f8
         serial_port=request_region(short_base,8,"Serial_port");

result = request_irq(4,irq_handler,0,"serial_int",my_cdev);

	if(result ==0)
         printk(KERN_ALERT "\n#>>>interrupt handler successfully registered");
       else
         printk(KERN_ALERT "\n#>>>interrupt handler not registered");


//=======================================================================================


	return 0;
}


//Cleanup Module
void __exit CharDevice_exit(void)
{
	dev_t Mydev;
        int MAJOR,MINOR;
	Mydev=MKDEV(255,0);
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\nThe Major Number is %d...THe Minor Number is %d\n",MAJOR,MINOR);
	unregister_chrdev_region(Mydev,1);//unregister the device numbers and the device created
	cdev_del(my_cdev);
	printk(KERN_ALERT "\ne unregistered the stuff that was allocated.....Goodbye for ever.....\n");

        //relese the region allocated
             release_region(short_base,8);
       //release the IRQ
            free_irq(4,my_cdev);     
	printk(KERN_ALERT "\nSerial Driver region released successfully..\n");
       
	return;
}


//Open System Call
int NAME_open(struct inode *inode, struct file *filp)
{
       
	printk(KERN_ALERT "\n entered the open system call \n");

       
        //int irq_no;
        unsigned char mod_reg,mod_prev;  
        
	printk(KERN_ALERT "\n open system call for the serial port driver ..\n");

//=====================================================================================
//Default Settings for Serial Port
//=====================================================================================

//disable transmit and recieve interrupts
 outb_p( 0x0,INT_ENABLE_REG );     

         printk(KERN_ALERT "\n*****************************************");
         printk(KERN_ALERT "\nDefault Configuration for the Serial Port");
         printk(KERN_ALERT "\n*****************************************");
//set BAUD to 9600

         outb_p( 0x80 , LINE_CTRL_REG );      //set DLAB=1 in Line control register
         outb_p( BAUD_9600_L , DIVISOR_LATCH_L );//set Divisor latch LSB 
         outb_p( BAUD_9600_H , DIVISOR_LATCH_H );//set Divisor latch MSB 
         outb_p( 0x00 , LINE_CTRL_REG );      //set DLAB=0 in Line control register
         printk(KERN_ALERT "\n ->baud rate set to 9600bps ..\n");
/* 
//set even parity
         outb_p( 0x0 , LINE_CTRL_REG );      //set DLAB=1 in Line control register
         printk(KERN_ALERT "\n ->even parity set ..\n");
//set no of stop bits as 1          
         mod_prev=inb_p(LINE_CTRL_REG );      //read contents of line contol register
         mod_reg = mod_prev & 0xfb;           //and with 0xfb to  set no of stop bits as 1
         outb_p(mod_reg , LINE_CTRL_REG );    //write back value to the register
         printk(KERN_ALERT "\n ->1 stop bit ..\n");
//set no of data bits as 8 
         mod_prev=inb_p(LINE_CTRL_REG );        //read contents of line contol register
         mod_reg = mod_prev | 0x3 ;             //or it with 0x3 to set data bits as 8  
         outb_p(mod_reg , LINE_CTRL_REG );      //write back value to the register
         printk(KERN_ALERT "\n ->8 data bits ..\n");*/

 outb_p(0x0b,LINE_CTRL_REG ); //set 1 stopbit,8 data bits , odd parity   

         printk(KERN_ALERT "\n ->even parity set ..\n");
         printk(KERN_ALERT "\n ->1 stop bit ..\n");
         printk(KERN_ALERT "\n ->8 data bits ..\n");

//enable transmit and recieve interrupts
 outb_p( 0x3,INT_ENABLE_REG ); 


/* not needed for serial port      
 //probe for IRQ of parallel PORT
       
        unsigned long mask;
          mask=probe_irq_on();
          outb_p(0x10,short_base + 2);//enable reporting
          outb_p(0x00,short_base);    //clear the bit
          outb_p(0xff,short_base);    //set the bit: interrupt! 
          outb_p(0x00,short_base);    //set the bit: interrupt! 
          outb_p(0x00,short_base + 2);//disable reporting
          udelay(5);//delay of 5 secs
          irq_no=probe_irq_off(mask);                  
 

         printk(KERN_ALERT "\n#>>>the irq number reported is = %d \n",irq_no);
*/
	return 0;
}

//Close System Call
int NAME_release(struct inode *indoe, struct file *filp)
{
	printk(KERN_ALERT "\nThis is the release method for  Serial Driver..\n");
    
	return 0;
} 


//Write Functionality
ssize_t NAME_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp)
{
   
  printk(KERN_ALERT "\n Entered write system call");
  int result;

  while(tflag == 1);
  result=copy_from_user((char *)&tbuff,(char *)Ubuff,1); //copy user data to tarnsmit buffer

  printk(KERN_ALERT "\ndata is tbuff = %c",tbuff);
  outb_p(tbuff,TRANSMIT_REG);//Write value to the Transmit Register

  tflag=0; 
  mdelay(20);  
  return (ssize_t) 1;
}


//read Functionality	
ssize_t NAME_read(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp)
{
   int result;
   while(rflag == 0);
    
   result=copy_to_user((char *)Ubuff,(char *)&rbuff,1); //copy to user
   rflag=0;
   return (ssize_t) 1;
}



int NAME_ioctl(struct file *fl, unsigned int cmd, unsigned long arg)
{
unsigned char mod_reg,mod_prev;
    switch(cmd)
    {
      case SET_BAUD_9600:
         mod_prev=inb_p(LINE_CTRL_REG );     //read contents of line contol register
         mod_reg = mod_prev | 0x80;             //or it with 0x80 t0 set DLAB to 1  
         outb_p( mod_reg , LINE_CTRL_REG );      //set DLAB=1 in Line control register
         outb_p( BAUD_9600_L , DIVISOR_LATCH_L );//set Divisor latch LSB 
         outb_p( BAUD_9600_H , DIVISOR_LATCH_H );//set Divisor latch MSB 
         outb_p( mod_prev , LINE_CTRL_REG );    //restore the earlier value of DLAB
      break;     

      case SET_BAUD_19200:
         mod_prev=inb_p(LINE_CTRL_REG );      //read contents of line contol register
         mod_reg = mod_prev | 0x80;              //or it with 0x80 t0 set DLAB to 1  
         outb_p( mod_reg , LINE_CTRL_REG );      //set DLAB=1 in Line control register
         outb_p( BAUD_19200_L , DIVISOR_LATCH_L );//set Divisor latch LSB 
         outb_p( BAUD_19200_H ,DIVISOR_LATCH_H );//set Divisor latch MSB 
         outb_p( mod_prev , LINE_CTRL_REG );     //restore the earlier value of DLAB
      break;     

      case SET_EVEN_PARITY:
         mod_prev=inb_p(LINE_CTRL_REG );      //read contents of line contol register
         mod_reg = mod_prev | 0x18;             //or it with 0x80 t0 set DLAB to 1  
         outb_p(mod_reg , LINE_CTRL_REG );      //set DLAB=1 in Line control register
      break;     
      
      case SET_ODD_PARITY:
         mod_prev=inb_p(LINE_CTRL_REG );      //read contents of line contol register
         mod_reg = mod_prev | 0x8;              //or it with 0x80 t0 set DLAB to 1  
         outb_p(mod_reg , LINE_CTRL_REG );      //set DLAB=1 in Line control register
      break;     

      case SET_NO_PARITY:
         mod_prev=inb_p(LINE_CTRL_REG );      //read contents of line contol register
         mod_reg = mod_prev & 0xf7;              //and it with 0x80 t0 set DLAB to 1  
         outb_p(mod_reg , LINE_CTRL_REG );      //set DLAB=1 in Line control register
      break;     

      case SET_STOP_BITS_AS_1:
         mod_prev=inb_p(LINE_CTRL_REG );      //read contents of line contol register
         mod_reg = mod_prev & 0xfb;              //and it with 0x80 t0 set DLAB to 1  
         outb_p(mod_reg , LINE_CTRL_REG );      //set DLAB=1 in Line control register
      break;     

      case SET_CHAR_LEN_AS_8:
         mod_prev=inb_p(LINE_CTRL_REG );      //read contents of line contol register
         mod_reg = mod_prev | 0x3 ;             //and it with 0x80 t0 set DLAB to 1  
         outb_p(mod_reg , LINE_CTRL_REG );      //set DLAB=1 in Line control register
      break;     

      case ENABLE_INTERRUPTS:
          outb_p( 0x3,INT_ENABLE_REG ); 
      break;     
	
      case DISABLE_INTERRUPTS:
          outb_p( 0x0,INT_ENABLE_REG ); 
      break;     
}
return 1;
}
union intr{
unsigned char buffer;

struct int_identification_reg{
unsigned char interrupt_pending:1;
unsigned char interrupt_select:3;
unsigned char crap:4;
} int_ir;

} int_id;

irqreturn_t irq_handler (int irq_num ,void *dev_id ,struct pt_regs *regs)
{
         
         printk(KERN_ALERT "\n##--->ISR---->Entered the ISR ");

         int_id.buffer=inb_p(INT_IDENTIFICATION_REG );//read contents of Interrutp identification register
         
         if(int_id.int_ir.interrupt_pending == 0)
         {
               switch(int_id.int_ir.interrupt_select)
               {
                  case 1:
                   printk("##---->ISR---->Transmit interrupt eneterd");
                   printk("##---->ISR---->tflag = %d",tflag);
                    tflag=0;
                   printk("##---->ISR---->tflag made to 1");
                   printk("##---->ISR---->tflag = %d",tflag);
                    break;
           
                  case 2:
                   rbuff=inb_p( RECIEVE_REG );//Write value to the Recieve Register
                   rflag=1;
                   break;
         
                  default:
                   break;
               }
            
               return IRQ_HANDLED;
          }

       else
               return IRQ_NONE;
             
}

//Module over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);

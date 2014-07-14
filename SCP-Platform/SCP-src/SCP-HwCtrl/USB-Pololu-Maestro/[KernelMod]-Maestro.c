/*
 * "Pololu Maestro Servo Controller" - Linux Kernel Driver Module
 *
 * Copyright (C) 2013-2014 Roosemberth Palacios <roosemberth@roosemberth.usr.sh>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 * derived from Dream Cheeky USB Missile Launcher driver
 * Copyright (C) 2007 Matthias Vallentin <vallentin@icsi.berkeley.edu>
 *
 *  Kernel Driver Applies for:
 *      -> Micro Maestro 6 (http://www.pololu.com/catalog/product/1350)
 *      -> Mini Maestro 12 (http://www.pololu.com/catalog/product/1352)
 *      -> Mini Maestro 18 (http://www.pololu.com/catalog/product/1354)
 *      -> Mini Maestro 24 (http://www.pololu.com/catalog/product/1356)
 *
 *  Jun 2014 - Roosemberth Palacios - El Salvador
 */

/* Driver Definitions */
#define DRIVER_VERSION 		"v1.0"
#define DRIVER_AUTHOR 		"Roosemberth Palacios <roosemberth@roosemberth.usr.sh>"
#define DRIVER_DESC 		"Pololu Micro/Mini Maestro Kernel Driver"
#define SHORT_DRIVER_DESC 	"Pololu Micro/Mini Maestro Driver"

/* Hardware Definitions */
#define MAESTRO_VENDOR_ID           0x1FFB
#define Micro6_MAESTRO_PRODUCT_ID   0x0089
#define Mini12_MAESTRO_PRODUCT_ID   0x008A
#define Mini18_MAESTRO_PRODUCT_ID   0x008B
#define Mini24_MAESTRO_PRODUCT_ID   0x008C

/* Software Definitions */

/* TODO: Faire attention sur cette constante!
 * Update: In theory we're working with dynamic minors, so in order to determine the right minor we should test
 * Matthias Valletin himself recommended to guess in a sort of test/fail procedure
 */

#ifdef CONFIG_USB_DYNAMIC_MINORS
	#define MAESTRO_MINOR_BASE			0
#else
	#define MAESTRO_MINOR_BASE			0
#endif

/* Include Files */
#include "../../../SCP-Kernel/include/linux/slab.h"				// kmallock
#include "../../../SCP-Kernel/include/linux/usb.h"
#include "../../../SCP-Kernel/include/linux/mutex.h"
#include "../../../SCP-Kernel/include/asm-generic/ioctl.h"
#include "../../../SCP-Kernel/include/linux/gfp.h"				// GFP_KERNEL
#include "../../../SCP-Kernel/include/linux/fs.h"				// struct file
#include "../../../SCP-Kernel/include/asm-generic/uaccess.h"	// copy_from_*
#include "../../../SCP-Kernel/include/linux/kernel.h"			// Strtoint
#include "../../../SCP-Kernel/include/linux/semaphore.h"		// init_MUTEX

#include "../../../SCP-Kernel/include/linux/module.h"
#include "../../../SCP-Kernel/include/linux/init.h"
#include "../../../SCP-Kernel/include/uapi/asm-generic/errno-base.h"
/*
 * - 3rd Party Related Code -
 *
 * Debug Level Definitions - Based on Matthias Vallentin's <vallentin@icsi.berkeley.edu>
 * "Dream Cheeky USB Missile Launcher driver"-> "ml_driver.c"
 */

#define DEBUG_LEVEL_INFO		0x0F	// 0x1000b
#define DEBUG_LEVEL_WARN		0x07	// 0x0100b
#define DEBUG_LEVEL_ERROR		0x03	// 0x0010b
#define DEBUG_LEVEL_CRITICAL	0x01	// 0x0001b

#define DEBUG_INFO(fmt, args...)  if ((DebugLevel & DEBUG_LEVEL_INFO) == DEBUG_LEVEL_INFO) \
    printk( KERN_DEBUG "[Info    ]:  %s(%d): " fmt "\n", __FUNCTION__, __LINE__, ## args)
#define DEBUG_WARN(fmt, args...)  if ((DebugLevel & DEBUG_LEVEL_WARN) == DEBUG_LEVEL_WARN) \
    printk( KERN_DEBUG "[Warning ]:  %s(%d): " fmt "\n", __FUNCTION__, __LINE__, ## args)
#define DEBUG_ERROR(fmt, args...) if ((DebugLevel & DEBUG_LEVEL_ERROR) == DEBUG_LEVEL_ERROR) \
    printk( KERN_DEBUG "[Error   ]:   %s(%d): " fmt "\n", __FUNCTION__, __LINE__, ## args)
#define DEBUG_CRIT(fmt, args...)  if ((DebugLevel & DEBUG_LEVEL_CRITICAL) == DEBUG_LEVEL_CRITICAL) \
    printk( KERN_DEBUG "[Critical]:  %s(%d): " fmt "\n", __FUNCTION__, __LINE__, ## args)

static ushort DebugLevel = 15;
static ushort DebugTrace = 0;

module_param(DebugLevel, ushort, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);	// File Permissions: 644
module_param(DebugTrace, ushort, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);	// FIle Permissions: 644

MODULE_PARM_DESC(DebugLevel, "Debug level (bitmask)");
MODULE_PARM_DESC(DebugTrace, "Enable function tracing");


/*
 * End of 3rd-Party Related Code
 */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Roosemberth Palacios <roosemberth@roosemberth.usr.sh>");

//#include "Maestro-Definitions.h"

#define MAESTRO_CONTROL_REQUEST_TYPE	0x80 	// 10000000b
#define MAESTRO_CONTROL_REQUEST			0x06	// GET_DESCRIPTOR
#define MAESTRO_CONTROL_VALUE			0x00	// Am I sure?
#define MAESTRO_CONTROL_INDEX			0x05	// Transmission to 5th Interface (USB 2.0 Specification, Page 249)
#define MAESTRO_CONTROL_BUFFER_SIZE		0xff	// wLength

#include "Maestro-Definitions.h"

/*
 * Maestro Platform Description
 */

struct usb_Maestro {
	struct usb_device       		*usbdev;
    struct usb_interface    		*interface;
    char							SerialNumber[8];
    char 							minor;

    unsigned int					open_count;				// Device file "open" count
    struct semaphore				semaphore;				// Device file Open Callback Semaphore

    char							*ctrl_buffer;			// control transfer buffer
    struct urb						*ctrl_urb;				// control transfer urb
    struct usb_ctrlrequest			*ctrl_spi;				// control transfer setup packet information

    unsigned char           		MaestroChsCount;		// How Many Channels are there?
    struct MaestroDescriptor		CtrlDescriptor;
};

const static struct usb_device_id Maestro_table [] = {
    {USB_DEVICE(MAESTRO_VENDOR_ID, Micro6_MAESTRO_PRODUCT_ID)},
    {USB_DEVICE(MAESTRO_VENDOR_ID, Mini12_MAESTRO_PRODUCT_ID)},
    {USB_DEVICE(MAESTRO_VENDOR_ID, Mini18_MAESTRO_PRODUCT_ID)},
    {USB_DEVICE(MAESTRO_VENDOR_ID, Mini24_MAESTRO_PRODUCT_ID)},
    { }
};

MODULE_DEVICE_TABLE(usb, Maestro_table);

/* Prevent races between open() and disconnect */
static DEFINE_MUTEX(disconnect_mutex);
static struct usb_driver Maestro_driver;

/*
 * 	Some Cleanup Functions
 */
static void Maestro_Cleanup(struct usb_Maestro *dev){
	if (dev->ctrl_urb) usb_kill_urb(dev->ctrl_urb);

	/* Free data structures */
	if (dev->ctrl_urb)			usb_free_urb(dev->ctrl_urb);
	kfree(dev->ctrl_buffer);
	kfree(dev->ctrl_spi);
	kfree(dev);
}

static void Maestro_Control_Callback(struct urb *urb){

}

/*
 * Alors on Procède à l'analyse des donées écrit sur le fichier /dev/MaestroX
 */

int raw_buffer_to_words(u8 *RecievedBuffer, int count, u8 **Strings){
	unsigned char BuffIndex = 0;
	unsigned char WordCharCounter = 0;
	unsigned int NumDesMots = 0;
	unsigned char WordOffset = 0;
	unsigned char i = 0;

	DEBUG_INFO("raw_buffer_to_words Function Called, Count: %d, Recieved Buffer: 0x%x", count, (unsigned int)RecievedBuffer);
	DEBUG_INFO("BuffIndex, WordCharCounter, NumDesMots Allocated");

	for(BuffIndex=0; BuffIndex<count; ++BuffIndex){
		if ((RecievedBuffer[BuffIndex]!=' ')&&(BuffIndex!=count-1)){
			WordCharCounter++;							// Ajout le charactère au mot
		} else {										// On a trouvé un espace mais pas à la fin
			DEBUG_INFO("Found Word from Position %d to %d of RecievedBuffer, Pushing to Strings[%d]", WordOffset, BuffIndex, NumDesMots);
			if (WordCharCounter==0) DEBUG_WARN("Found WhiteSpace on first Character!");
//			Strings[NumDesMots]=kmalloc(WordCharCounter*sizeof(char *), GFP_KERNEL); FIXME: Oddities
			Strings[NumDesMots]=kmalloc((WordCharCounter==0?1:WordCharCounter)*sizeof(char *), GFP_KERNEL);
			WordOffset = BuffIndex-WordCharCounter;
			for (i=0; WordOffset<BuffIndex; ++WordOffset){
				Strings[NumDesMots][i]=RecievedBuffer[WordOffset];
				++i;
			}
			Strings[NumDesMots++][WordCharCounter]='\0';// Ferme le string avec '\0'
			DEBUG_INFO("Found Word was \"%s\"", Strings[NumDesMots-1]);
			WordCharCounter=0;							// Reinitializer l'index de charactère de mot
		}
	}
	DEBUG_INFO("Done Separating Words from buffer, Returning Number of Words found");
	return NumDesMots;
}

int MaestroWriteHandler(struct usb_Maestro *dev, u8 *RecievedBuffer, int count){
	int i;
	int val;
	int errno;
	u8 **Strings;
	int wordcount;
	int *Arguments;
	struct ControlTransferDescriptor *ControlPacket;
	DEBUG_INFO("MaestroWriteHandler Function Called, Count: %d, Recieved Buffer: %s", count, RecievedBuffer);
	DEBUG_INFO("Allocating Memory for ControlPacket Structure");
	ControlPacket = kzalloc(sizeof(struct ControlTransferDescriptor), GFP_KERNEL);
	DEBUG_INFO("Allocating Memory for Strings buffer");
	Strings = kzalloc(count*sizeof(u8 *), GFP_KERNEL);
	if (!ControlPacket || !Strings){
		DEBUG_ERROR("Not Enough Memory for Allocating ControlPacket and Strings Structures");
		return -ENOMEM;
	}
	DEBUG_INFO("Extracting Words");
	wordcount = raw_buffer_to_words(RecievedBuffer, count, Strings);
	DEBUG_INFO("Allocating Memory for Arguments list");
	Arguments=kzalloc(sizeof(int)*wordcount , GFP_KERNEL);
	if (!Arguments){
		DEBUG_ERROR("Not Enough Memory for Allocating Arguments list");
		return -ENOMEM;
	}
	DEBUG_INFO("Got everything up!, Trying to Parse Arguments, String[0][1]=0x%x", Strings[0][1]);
	for (i=0; i<wordcount ; ++i){
		errno = 0;										// To distinguish success/failure after call
        val = kstrtol(Strings[i], (i==0)?16:10, (long *)Arguments[i]);
//        if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0)) DEBUG_WARN("kstrtol Parse Error!, Error %d, Parsed Value: %ld \n long=[%ld,%ld]", errno, val, LONG_MIN, LONG_MAX);	// Check for Errors
        if (errno != 0) DEBUG_WARN("kstrtol Parse Error!, Error %d, Parsed Value: %ld \n long=[%ld,%ld]", errno, val, LONG_MIN, LONG_MAX);	// Check for Errors - In any case error would be different
		DEBUG_INFO("Parsed Strings[%d] to Argument[%d]:%s->%d", i, i, Strings[i], Arguments[i]);
	}
	DEBUG_INFO("Parsing Successful!");
	if (Strings[0][1]=='\0') Arguments[0]=Strings[0][0];
	//if (count<2) DEBUG_WARN("Too few Bytes Written!, what did you mean?"); return 0;
	if (Arguments[0] != REQUEST_COMPLEX) ControlPacket->Request = Arguments[0];
	DEBUG_INFO("Request set to 0x%x", Arguments[0]);
	ControlPacket->Index=0;
	ControlPacket->Value=0;
	ControlPacket->Data=NULL;
	ControlPacket->Lenght=0;
	switch (Arguments[0]){
	case REQUEST_COMPLEX:
		// TODO: Implement Complex Functions
		// Set 	ControlPacket->RequestType
		DEBUG_INFO("Hey There!");
		return count;
		break;
	case REQUEST_GET_PARAMETER:
		ControlPacket->RequestType=MAESTRO_CONTROL_INCOMING_REQ_TYPE;
		break;
	case REQUEST_SET_PARAMETER:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		break;
	case REQUEST_GET_VARIABLES:
		ControlPacket->RequestType=MAESTRO_CONTROL_INCOMING_REQ_TYPE;
		break;
	case REQUEST_SET_SERVO_VARIABLE:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		break;
	case REQUEST_SET_TARGET:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		ControlPacket->Index=Arguments[1];
		ControlPacket->Value=Arguments[2];
		break;
	case REQUEST_CLEAR_ERRORS:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		break;
	case REQUEST_GET_SERVO_SETTINGS:
		ControlPacket->RequestType=MAESTRO_CONTROL_INCOMING_REQ_TYPE;
		break;
	case REQUEST_GET_STACK:
		ControlPacket->RequestType=MAESTRO_CONTROL_INCOMING_REQ_TYPE;
		break;
	case REQUEST_GET_CALL_STACK:
		ControlPacket->RequestType=MAESTRO_CONTROL_INCOMING_REQ_TYPE;
		break;
	case REQUEST_SET_PWM:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		break;
	case REQUEST_REINITIALIZE:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		break;
	case REQUEST_ERASE_SCRIPT:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		break;
	case REQUEST_WRITE_SCRIPT:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		break;
	case REQUEST_SET_SCRIPT_DONE:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		break;
	case REQUEST_RESTART_SCRIPT_AT_SUBROUTINE:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		break;
	case REQUEST_RESTART_SCRIPT_AT_SUBROUTINE_WITH_PARAMETER:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		break;
	case REQUEST_RESTART_SCRIPT:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		break;
	case REQUEST_START_BOOTLOADER:
		ControlPacket->RequestType=MAESTRO_CONTROL_OUTGOING_REQ_TYPE;
		break;
	default:
		DEBUG_WARN("Could not understand Request!");
		return count;
	}

	dev->ctrl_spi->bRequest=ControlPacket->Request;
	dev->ctrl_spi->bRequestType=ControlPacket->RequestType;
	dev->ctrl_spi->wIndex=cpu_to_le16(ControlPacket->Index);
	dev->ctrl_spi->wLength=cpu_to_le16(ControlPacket->Lenght);
	dev->ctrl_spi->wValue=cpu_to_le16(ControlPacket->Value);

    usb_fill_control_urb(dev->ctrl_urb, dev->usbdev,				// URB to fill, USBDevice
    					 usb_sndctrlpipe(dev->usbdev, 0),			// usb_sndctrlpipe(USBDevice, Endpoint)
    					 (unsigned char *)dev->ctrl_spi,			// Setup Packet
    					 ControlPacket->Data,
    					 ControlPacket->Lenght,
    					 Maestro_Control_Callback,
    					 dev);

    i=usb_submit_urb(dev->ctrl_urb, GFP_KERNEL);
    if (i==0){
        	DEBUG_INFO("Reussie!: Value %d Written to Servo Number %d!", Arguments[2], Arguments[1]);
        	return count;
    } else {
    	DEBUG_ERROR("USB Control Message Sending Failed with %serror code %d", i>0?" Positive! ":"", i);
    	return i>0?-i:i;
    }
}

/*
 * Maestro Device (/dev/MaestroX) File Operations
 */
static int Maestro_Open(struct inode *inode, struct file *file){
    /* open syscall */
	int subminor;
	struct usb_Maestro *dev;
	struct usb_interface *interface;
	subminor = iminor(inode);
	mutex_lock(&disconnect_mutex);
	DEBUG_INFO("Mutex Locked");

	interface = usb_find_interface(&Maestro_driver, MAESTRO_MINOR_BASE);
	DEBUG_INFO("Searching USB Interface");
	if (!interface){
		DEBUG_ERROR("Cannot find device for minor %d", subminor);
		mutex_unlock(&disconnect_mutex);
		return -ENODEV;
	}
	DEBUG_INFO("USB Interface Found!");

	dev = usb_get_intfdata(interface);
	DEBUG_INFO("Loading usb_Maestro Interface Data");
	if (!dev){
		mutex_unlock(&disconnect_mutex);
		return -ENODEV;
	}
	DEBUG_INFO("usb_Maestro Data OK");

	/* Lock this device */
	if (down_interruptible(&dev->semaphore)){
		DEBUG_ERROR("Semaphore down failed");
		mutex_unlock(&disconnect_mutex);
		return -ERESTARTSYS;
	}
	DEBUG_INFO("Semaphore Locked");

	dev->open_count++;

	if (dev->open_count > 1) DEBUG_INFO("Open_Count = %d", dev->open_count);

	file->private_data = dev;
	DEBUG_INFO("We Got Interface Data on File Private Data");
	up(&dev->semaphore);
	DEBUG_INFO("Semaphore Unlocked");
	mutex_unlock(&disconnect_mutex);
	DEBUG_INFO("Mutex Unlocked");
	return 0;
}

static int Maestro_Release(struct inode *inode, struct file *file){
    /* close syscall */
	struct usb_Maestro *dev = NULL;
	DEBUG_INFO("Maestro_Release Function Called");
	dev = file->private_data;
	if (!dev) DEBUG_ERROR("Device is NULL"); return -ENODEV;

	if (down_interruptible(&dev->semaphore)) return -ERESTARTSYS;

	if (dev->open_count <= 0) DEBUG_ERROR("Device not Opened"); up(&dev->semaphore); return -ENODEV;

	if (!dev->usbdev) DEBUG_INFO("Device unplugged before releasing the file"); up(&dev->semaphore); Maestro_Cleanup(dev); return 0;

	if (dev->open_count > 1) DEBUG_INFO("Open_Count = %d", dev->open_count);

	Maestro_Cleanup(dev);
	dev->open_count--;
	up(&dev->semaphore);
	return 0;
}

static ssize_t Maestro_Read(struct file *file, char __user *user_buf, size_t count, loff_t *f_ops){
	struct usb_Maestro *dev;
	const char *Greetings;
	DEBUG_INFO("Device Located");
	dev = file->private_data;
	DEBUG_INFO("Got Private_data");
	if (down_interruptible(&dev->semaphore)) return -ERESTARTSYS;
	DEBUG_INFO("semaphore down_interruptible");
	DEBUG_INFO("So dev->usbdev points to 0x%x", (unsigned int)dev->usbdev);
	if (!dev->usbdev){
		DEBUG_ERROR("No device or device unplugged (%d)", -ENODEV);
		up(&dev->semaphore);
		return -ENODEV;
	}
	DEBUG_INFO("So, Device is Here");
	if (count == 0){
		up(&dev->semaphore);
		return 0;
	}
	DEBUG_INFO("Hey There!, Attemped to Read!");
	Greetings="Hey There!\n";
	if (copy_to_user(user_buf, Greetings, count)){
		up(&dev->semaphore);
		return -EFAULT;
	}
	up(&dev->semaphore);
	return sizeof(Greetings);
}

static ssize_t Maestro_Write(struct file *file, const char __user *user_buf, size_t count, loff_t *f_ops){
	struct usb_Maestro *dev;
	int ret;
	u8 RecievedBuffer[count];
	DEBUG_INFO("Maestro_Write Function Called, count = %d", count);
	dev = file->private_data;

	if (down_interruptible(&dev->semaphore)) return -ERESTARTSYS;
	if (!dev->usbdev){
		DEBUG_ERROR("No device or device unplugged (%d)", -ENODEV);
		up(&dev->semaphore);
		return -ENODEV;
	}
	if (count == 0){
		up(&dev->semaphore);
		return 0;
	}

	if (copy_from_user(&RecievedBuffer, user_buf, count)){
		up(&dev->semaphore);
		return -EFAULT;
	}

	/* FIXME: Now RecievedBuffer hold the bytes written to the dev file and we need to fill ControlPacket Structure */
	ret = MaestroWriteHandler(dev, RecievedBuffer, count);
	if (ret<0) DEBUG_ERROR("Problem Writting Data Written to /dev/Maestro%d, with error code %d", dev->minor, ret);

	up(&dev->semaphore);
	return ret;
}

static struct file_operations Maestro_fops = {
    .owner 	 =	THIS_MODULE,
    .write 	 =	Maestro_Write,
    .open 	 =	Maestro_Open,
    .release =	Maestro_Release,
    .read 	 =	Maestro_Read,
};

/*
 * Maestro USB Class
 */

static struct usb_class_driver usb_Maestro_class = {
	.name = "Maestro%d",
	.fops = &Maestro_fops,
	.minor_base = MAESTRO_MINOR_BASE,
};

/*
 * Maestro Device (/dev/MaestroX) Definitions
 */

static int Maestro_probe(struct usb_interface *interface, const struct usb_device_id *id){
	/*if (DebugLevel == 0||DebugTrace == 0){
		printk("[Maestro Module] Maestro Control Module Won't Print Debug Information!");
	}*/

	struct usb_device *usbdev = interface_to_usbdev(interface);
    struct usb_Maestro *dev = NULL;

	/* Multipurpose Variable */
	int i=0;

	DEBUG_INFO("usbdev pointing to: 0x%x", (int)usbdev);
	if (!usbdev) {
		DEBUG_ERROR("usbdev is NULL!");
		return -ENODEV;
	}

	dev = kzalloc(sizeof(struct usb_Maestro), GFP_KERNEL);

	if (!dev){
    	DEBUG_ERROR("Cannot Allocate Memory Structure for usb_Maestro");
    	return -ENOMEM;
    }

    sema_init(&dev->semaphore, 1);

    dev->usbdev 	= usbdev;
    dev->interface 	= interface;

    dev->ctrl_urb	= usb_alloc_urb(0, GFP_KERNEL);
    dev->ctrl_buffer= kzalloc(MAESTRO_CONTROL_BUFFER_SIZE, GFP_KERNEL);
    dev->ctrl_spi	= kzalloc(sizeof(struct usb_ctrlrequest), GFP_KERNEL);

    if (!(dev->ctrl_urb) || !(dev->ctrl_buffer) || !(dev->ctrl_spi)){
    	DEBUG_ERROR("Cannot Allocate Memory for Control URB, Buffer or Setup Packet Structures");
    	Maestro_Cleanup(dev);
    	return -ENOMEM;
    }

    dev->ctrl_spi->bRequestType	= USB_CTRL_STD_INCOMING_REQ_TYPE;
    dev->ctrl_spi->bRequest		= USB_REQ_GET_DESCRIPTOR;
    dev->ctrl_spi->wValue		= 0;
    dev->ctrl_spi->wIndex		= cpu_to_le16(MAESTRO_CTRL_INTERFACE);
    dev->ctrl_spi->wLength		= cpu_to_le16(USB_CTRL_TRANSF_MAX_BUFFER_SIZE);

    usb_fill_control_urb(dev->ctrl_urb, dev->usbdev,
    					 usb_sndctrlpipe(dev->usbdev, 0),
    					 (unsigned char *)dev->ctrl_spi,
    					 dev->ctrl_buffer,
    					 MAESTRO_CONTROL_BUFFER_SIZE,
    					 Maestro_Control_Callback,
    					 dev);


    /* Get the Serial Number */
    if (! usb_string(usbdev, usbdev->descriptor.iSerialNumber, dev->SerialNumber, sizeof(dev->SerialNumber))) {
    	DEBUG_ERROR("Could not retrieve Serial Number");
    	Maestro_Cleanup(dev);
    	return -ENODEV;
    }

    /* Print Serial Number */
    printk("\001 [Maestro] New Maestro Device Found! Serial Number: ");
    for (i = 0; i < 7; ++i) printk("0x%x, ", dev->SerialNumber[i]);
    printk("\n");

    /* Save the data pointer in this interface device */
    usb_set_intfdata(interface, dev);

    /* Register the device towards the kernel */
    i = usb_register_dev(interface, &usb_Maestro_class);
    if (i){
    	DEBUG_ERROR("Not able to get a minor for this device");
    	usb_set_intfdata(interface, NULL);
    	Maestro_Cleanup(dev);
    	return i;
    }
    DEBUG_INFO("New Maestro Device Assigned to /dev/Maestro%d", interface->minor);

    return 0;
}

static void Maestro_disconnect(struct usb_interface *interface){
    /*called when unplugging a USB device.*/
    struct usb_Maestro *dev = usb_get_intfdata(interface);
    int minor = dev->minor;
	mutex_lock(&disconnect_mutex);
    usb_set_intfdata(interface, NULL);
    down(&dev->semaphore);
    usb_deregister_dev(interface, &usb_Maestro_class);
	if (! dev->open_count) {
		up(&dev->semaphore);
	} else {
		dev->usbdev = NULL;
		up(&dev->semaphore);
	    dev->interface = NULL;
	}
	Maestro_Cleanup(dev);
	mutex_unlock(&disconnect_mutex);
    DEBUG_INFO("Maestro /dev/Maestro%d Gone!", minor);
}

static struct usb_driver Maestro_driver = {
    .name       = "Pololu_Maestro_Servo_Controller",
    .id_table   = Maestro_table,
    .probe      = Maestro_probe,
    .disconnect = Maestro_disconnect,
};

/*
 * Maestro Kernel-Module Registration
 */

static int __init usb_Maestro_init(void){
    int result;
    result = usb_register(&Maestro_driver);
	if (result) {
		DEBUG_ERROR("Registering driver failed");
	} else {
		DEBUG_INFO("Driver registered successfully");
	}
	return result;
}

static void __exit usb_Maestro_exit(void){
    /* called on module unloading */
    usb_deregister(&Maestro_driver);
}

MODULE_DEVICE_TABLE(usb, Maestro_table);
module_init(usb_Maestro_init);
module_exit(usb_Maestro_exit);

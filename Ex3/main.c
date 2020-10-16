/*
 * Audio Bypass Project
 */

#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <AIC_func.h>
#include <stdio.h>


void main(void)
{
	Int16 x_right[1], x_left[1]; //AIC inputs
	Int16 r_right[1], r_left[1]; //AIC outputs

	USBSTK5515_init(); 	//Initializing the Processor
	AIC_init(); 		//Initializing the Audio Codec
	while(1)
	{
		AIC_read2(x_right, x_left);
		r_right[0]=x_right[0];
		r_left[0]=x_left[0];
		AIC_write2(r_right[0],r_left[0]);
	}
}

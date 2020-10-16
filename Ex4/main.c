/*
 * FIR Implementation in C Project
 */

#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <AIC_func.h>
#include <stdio.h>
#include <firc.h>

Int16 in_left[TAPS]={0};
Int16 in_right[TAPS]={0};
Int16* in;

Int16 coef[TAPS] = {
	#include "lpf.dat"
};
 
Int16 firc(Uint16 i)
{
	Int32 sum;
	Uint16 j;
	Uint32 index;
	sum=0;

	//The actual filter work
	for(j=0; j<TAPS; j++)
	{
		if(i>=j)
 			index = i - j;
		else 
 			index = TAPS + i - j;
		sum += (Int32)in[index] * (Int32)coef[j];
	}
	sum = sum + 0x00004000;			// So we round rather than truncate.
	return (Int16) (sum >> 15);  	// Conversion from 32 Q30 to 16 Q15.

}

void main(void)
{
	Uint16 i=0;
	Int16 right, left; //AIC inputs
	Int16 out_right, out_left; //AIC output

	USBSTK5515_init(); 	//Initializing the Processor
	AIC_init(); 		//Initializing the Audio Codec
	while(1)
	{
		if(i>=TAPS) i=0;
		AIC_read2(&right, &left);
		in_right[i] = right;
		in = in_right;
		out_right = firc(i);
		
		in_left[i] = left;
		in = in_left;
		out_left = firc(i);
		
		AIC_write2(out_right, out_left);
		i++;
	}
}

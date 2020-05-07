#include <Bela.h>

extern "C" {
#include "cAPA102.h"
}
#include <iostream>

AuxiliaryTask lightTask;		// Auxiliary task to read/write BLE

void lights(void* data);

int readCount = 0;			// How long until we read again...
int readIntervalSamples = 100; // How many samples between reads
int readInterval = 1;

bool setup(BelaContext *context, void *userData)
{
	if(cAPA102_Init(6, 2, 1, 128) == 0)
		std::cout<<"works";
	cAPA102_Refresh();
	lightTask = Bela_createAuxiliaryTask(lights, 90, "light");
	return true;
}

void render(BelaContext *context, void *userData)
{
		if(++readCount >= readIntervalSamples) {
			readCount = 0;
			Bela_scheduleAuxiliaryTask(lightTask);
		}
	
}

void cleanup(BelaContext *context, void *userData)
{

}

void lights(void* data){
	cAPA102_Set_Pixel_RGB(5, 255, 0, 0);
	cAPA102_Refresh();
	usleep(5000);
}
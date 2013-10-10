#include <stdint.h>

uint8_t readbuff[64], writebuff[64];

// functions exported by gcc
void (*const reset_handler)(void) = 0x61646f66;
void (*const gcc_main)(void) = 0x61646f66;

void USB1Interrupt() iv IVT_INT_OTG_FS {
	USB_Interrupt_Proc();
}

void main() {
	if(0) {
		// functions imported by gcc
		asm {
			BL _HID_Read;
			BL _HID_Write;
		};
	}

	NVIC_IntEnable(IVT_INT_OTG_FS);
	HID_Enable(readbuff, writebuff);

	reset_handler();
	gcc_main();
}

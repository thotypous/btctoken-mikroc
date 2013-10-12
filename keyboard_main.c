#include <stdint.h>
#include <string.h>
#include "keyboard_objects.h"

uint8_t Keyboard_Is_Running = 1;
unsigned int password_len = 0;

// variables imported by gcc
uint8_t readbuff[64], writebuff[64];
unsigned char password[SIZE_PASS+2] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
char payment_addr[35]       = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
char payment_btc_amount[18] = "99999999.99999999";
char payment_btc_fee[18]    = "99999999.99999999";

// functions exported by gcc
void (*const reset_handler)(void)         = 0x61646f66;
void (*const answer_pubkey_request)(void) = 0x61646f66;
int  (*const receive_transactions)(void)  = 0x61646f66;
int  (*const sign_stuff)(void)            = 0x61646f66;

void USB1Interrupt() iv IVT_INT_OTG_FS {
  USB_Interrupt_Proc();
}

void Set_Transaction_Info_Labels(void) {
  memcpy(Label_Addr1_Caption, &payment_addr[ 0], 17);
  Label_Addr1_Caption[17] = 0;
  memcpy(Label_Addr2_Caption, &payment_addr[17], 17);
  Label_Addr2_Caption[17] = 0;
  
  sprintf(Label_Value1_Caption,"$ %s",payment_btc_amount);
  sprintf(Label_Value2_Caption,"+ %s",payment_btc_fee);
}

void Display_Message(const char *msg) {
  strcpy(Label_Message_Caption, msg);
  DrawScreen(&Screen2);
}

void main() {
  if(0) {
    // functions imported by gcc
    asm {
      BL _HID_Read;
      BL _HID_Write;
      BL _HID_Disable;
    };
  }

  NVIC_IntEnable(IVT_INT_OTG_FS);
  HID_Enable(readbuff, writebuff);

  //Start the touchpad and initialize the screen
  Start_TP();

  reset_handler();
  answer_pubkey_request();
  
  Display_Message("RECEIVING  TRANSACTION");
  
  if(receive_transactions() == 0) {
    Display_Message("INVALID  TRANSACTION");
    return;
  }

  Set_Transaction_Info_Labels();
  DrawScreen(&Screen1);
  
  while(1) {
    Keyboard_Is_Running = 1;
    while(Keyboard_Is_Running) {
      //Check the touchscreen for clicks
      Check_TP();
    }
    if(sign_stuff())
      break;
    DrawMessagePasswordField("WRONG PASSWORD");
    password_len = 0;
  }
  
  Display_Message("TRANSACTION  SIGNED  SUCCESSFULLY");
}

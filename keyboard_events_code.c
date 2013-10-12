#include "keyboard_objects.h"
#include "keyboard_resources.h"

int kb = 0, shift = 0;

static const int pass_stars_left = 4, pass_stars_top = 100;
static const int pass_stars_color = 0, pass_star_width = 11;

// Draw or erase previously drawn password stars
void DrawPasswordStars(int erase) {
  int i, pos;
  TFT_Set_Font(Courier_New12x23_Bold, erase ? Box3.Color : 0, FO_HORIZONTAL);
  pos = pass_stars_left;
  for(i = 0; i < password_len && i < MAX_SHOWN_PASS && pos < 240-pass_star_width; i++) {
    TFT_Write_Char('*', pos, pass_stars_top);
    pos += pass_star_width;
  }
}

void DrawMessagePasswordField(const char *msg) {
  DrawPasswordStars(1);
  TFT_Set_Font(Courier_New12x23_Bold, CL_RED, FO_HORIZONTAL);
  TFT_Write_Text(msg, pass_stars_left, pass_stars_top);
  Delay_ms(300);
  TFT_Set_Font(Courier_New12x23_Bold, Box3.Color, FO_HORIZONTAL);
  TFT_Write_Text(msg, pass_stars_left, pass_stars_top);
}

// Erase a label and clear its contents
void ClearLabel(TLabel *_label) {
  unsigned int old_color = _label->Font_Color;
  _label->Font_Color = Box3.Color;
  DrawLabel(_label);
  _label->Font_Color = old_color;
  _label->Caption[0] = 0;
}

// Show a indicator for a brief period of time
void ShowSign(char sign_type) {
  Label_Sign.Caption[0] = sign_type;
  Label_Sign.Caption[1] = 0;
  DrawLabel(&Label_Sign);
  Delay_ms(90);
  ClearLabel(&Label_Sign);
}

// Event Handlers
void DrawKeyboard()
{
   DrawScreen(&Screen1);
   DrawPasswordStars(0);
}

void ButtonsEvent(TButton *_button)
{
  if(password_len < SIZE_PASS) {
    password[password_len] = _button->Caption[0];
    ++password_len;
    password[password_len] = 0;
    DrawPasswordStars(0);
    ShowSign('.');
  }
  else {
    ShowSign('X');
  }
}

//Change the keyboard to the first one
void Button_KB1Click() {
  kb = 0; //set keyboard number
  DrawKeyboard();
}

//Change the keyboard to the second one
void Button_KB2Click() {
  kb = 1; //set keyboard number
  DrawKeyboard();
}

//Change the keyboard to the third one
void Button_KB3Click() {
  kb = 2; //set keyboard number
  DrawKeyboard();
}

//Change the keyboard to the fourth one
void Button_KB4Click() {
  kb = 3; //set keyboard number
  DrawKeyboard();
}

// Button 7ajs
void Button_7ajsClick() {
  ButtonsEvent(&Button_7ajs);
}

// Button 8bkt
void Button_8bktClick() {
  ButtonsEvent(&Button_8bkt);
}

// Button 5enw
void Button_5enwClick() {
  ButtonsEvent(&Button_5enw);
}

//Button 9clu
void Button_9cluClick() {
  ButtonsEvent(&Button_9clu);
}

//Button DELETE
void Button_DelClick() {
  if(password_len == 0) return;
  DrawPasswordStars(1);
  --password_len;
  password[password_len] = 0;
  DrawPasswordStars(0);
  ShowSign('<');
}

// Button 4dmv
void Button_4dmvClick() {
  ButtonsEvent(&Button_4dmv);
}

// Button 6fox
void Button_6foxClick() {
  ButtonsEvent(&Button_6fox);
}

// Button shift
void Button_ShiftClick() {
  shift = !shift;
  DrawKeyboard();
}

//Button 1gpy
void Button_1gpyClick() {
  ButtonsEvent(&Button_1gpy);
}

//Button 2hqz
void Button_2hqzClick() {
  ButtonsEvent(&Button_2hqz);
}

//Button 3ir-
void Button_3ir_Click() {
  ButtonsEvent(&Button_3ir_);
}

//Button 0_
void Button_0_Click() {
  ButtonsEvent(&Button_0_);
}

// Button pto
void Button_ptClick() {
  ButtonsEvent(&Button_pt);
}

//Button Finish (enter)
void Button_FinishClick() {
  Keyboard_Is_Running = 0;
}

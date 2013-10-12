#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include <stdint.h>

#define SIZE_PASS      64     // total size of password
#define MAX_SHOWN_PASS 21     // number of '*' chars that fit in the screen

extern unsigned char password[SIZE_PASS+2];
extern unsigned int password_len;
extern uint8_t Keyboard_Is_Running;

enum GlcdColor {_clClear, _clDraw, _clInvert};

typedef struct Screen TScreen;

typedef struct  Button {
  TScreen*  OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          Pen_Width;
  unsigned int  Pen_Color;
  char          Visible;
  char          Active;
  char          Transparent;
  char          *Caption;
  const char    *FontName;
  unsigned int  Font_Color;
  char          Gradient;
  char          Gradient_Orientation;
  unsigned int  Gradient_Start_Color;
  unsigned int  Gradient_End_Color;
  unsigned int  Color;
  char          PressColEnabled;
  unsigned int  Press_Color;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TButton;

typedef struct  Label {
  TScreen*  OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          *Caption;
  const char    *FontName;
  unsigned int  Font_Color;
  char          Visible;
  char          Active;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TLabel;

typedef struct  Box {
  TScreen*  OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          Pen_Width;
  unsigned int  Pen_Color;
  char          Visible;
  char          Active;
  char          Transparent;
  char          Gradient;
  char          Gradient_Orientation;
  unsigned int  Gradient_Start_Color;
  unsigned int  Gradient_End_Color;
  unsigned int  Color;
  char          PressColEnabled;
  unsigned int  Press_Color;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TBox;

struct Screen {
  unsigned int           Color;
  unsigned int           Width;
  unsigned int           Height;
  unsigned short         ObjectsCount;
  unsigned int           ButtonsCount;
  TButton                * const code *Buttons;
  unsigned int           LabelsCount;
  TLabel                 * const code *Labels;
  unsigned int           BoxesCount;
  TBox                   * const code *Boxes;
};

extern   TScreen                Screen1;
extern   TButton               Button_7ajs;
extern   TButton               Button_4dmv;
extern   TButton               Button_1gpy;
extern   TButton               Button_0_;
extern   TButton               Button_8bkt;
extern   TButton               Button_5enw;
extern   TButton               Button_2hqz;
extern   TButton               Button_pt;
extern   TButton               Button_9clu;
extern   TButton               Button_6fox;
extern   TButton               Button_3ir_;
extern   TButton               Button_KB3;
extern   TButton               Button_KB4;
extern   TButton               Button_Del;
extern   TButton               Button_Shift;
extern   TBox                   Box3;
extern   TButton               Button_KB1;
extern   TButton               Button_KB2;
extern   TButton               Button_Finish;
extern   TBox                   Box1;
extern   TLabel                 Label_Addr1;
extern   TLabel                 Label_Addr2;
extern   TLabel                 Label_Value1;
extern   TLabel                 Label_Value2;
extern   TLabel                 Label_Pass;
extern   TLabel                 Label_Title;
extern   TLabel                 Label_Sign;
extern   TButton                * const code Screen1_Buttons[18];
extern   TLabel                 * const code Screen1_Labels[7];
extern   TBox                   * const code Screen1_Boxes[2];


extern   TScreen                Screen2;
extern   TLabel                 Label7;
extern   TLabel                 Label8;
extern   TLabel                 Label_Message;
extern   TLabel                 * const code Screen2_Labels[4];



/////////////////////////
// Events Code Declarations
void Button_7ajsClick();
void Button_4dmvClick();
void Button_1gpyClick();
void Button_0_Click();
void Button_8bktClick();
void Button_5enwClick();
void Button_2hqzClick();
void Button_ptClick();
void Button_9cluClick();
void Button_6foxClick();
void Button_3ir_Click();
void Button_KB3Click();
void Button_KB4Click();
void Button_DelClick();
void Button_ShiftClick();
void Button_KB1Click();
void Button_KB2Click();
void Button_FinishClick();
/////////////////////////

/////////////////////////////////
// Caption variables Declarations
extern char Button_7ajs_Caption[];
extern char Button_4dmv_Caption[];
extern char Button_1gpy_Caption[];
extern char Button_0__Caption[];
extern char Button_8bkt_Caption[];
extern char Button_5enw_Caption[];
extern char Button_2hqz_Caption[];
extern char Button_pt_Caption[];
extern char Button_9clu_Caption[];
extern char Button_6fox_Caption[];
extern char Button_3ir__Caption[];
extern char Button_KB3_Caption[];
extern char Button_KB4_Caption[];
extern char Button_Del_Caption[];
extern char Button_Shift_Caption[];
extern char Button_KB1_Caption[];
extern char Button_KB2_Caption[];
extern char Button_Finish_Caption[];
extern char Label_Addr1_Caption[];
extern char Label_Addr2_Caption[];
extern char Label_Value1_Caption[];
extern char Label_Value2_Caption[];
extern char Label_Pass_Caption[];
extern const char Label_Title_Caption[];
extern char Label_Sign_Caption[];
extern char Label7_Caption[];
extern char Label8_Caption[];
extern char Label_Message_Caption[];
/////////////////////////////////

void DrawScreen(TScreen *aScreen);
void DrawButton(TButton *aButton);
void DrawLabel(TLabel *ALabel);
void DrawBox(TBox *ABox);
void Check_TP();
void Start_TP();

////////////////////////////////
extern int kb;
extern int shift;
void DrawMessagePasswordField(const char *msg);
////////////////////////////////

#endif

#include "keyboard_objects.h"
#include "keyboard_resources.h"

// Screen Calibration Parameters
const unsigned int x_min = 356;
const unsigned int x_max = 3609;
const unsigned int y_min = 225;
const unsigned int y_max = 3724;

//Colors
const int Numbers_Gradient_Start_Color = 0xFDA2;
const int Numbers_Gradient_End_Color = 0x51E0;
const int Other_Gradient_Start_Color = 0xF800;
const int Other_Gradient_End_Color = 0x0000;

// TFT module connections
unsigned int TFT_DataPort at GPIOE_ODR;
sbit TFT_RST at GPIOE_ODR.B8;
sbit TFT_RS at GPIOE_ODR.B12;
sbit TFT_CS at GPIOE_ODR.B15;
sbit TFT_RD at GPIOE_ODR.B10;
sbit TFT_WR at GPIOE_ODR.B11;
sbit TFT_BLED at GPIOE_ODR.B9;
// End TFT module connections

// Touch Panel module connections
sbit DriveX_Left at GPIOB_ODR.B1;
sbit DriveX_Right at GPIOB_ODR.B8;
sbit DriveY_Up at GPIOB_ODR.B9;
sbit DriveY_Down at GPIOB_ODR.B0;
// End Touch Panel module connections

// Global variables
unsigned int Xcoord, Ycoord;
const ADC_THRESHOLD = 750;
char PenDown;
void *PressedObject;
int PressedObjectType;
unsigned int caption_length, caption_height;
unsigned int display_width, display_height;

int _object_count;
unsigned short object_pressed;
TButton *local_button;
TButton *exec_button;
short button_order;
TLabel *local_label;
TLabel *exec_label;
short label_order;
TBox *local_box;
TBox *exec_box;
short box_order;

void Init_ADC() {
  ADC_Set_Input_Channel(_ADC_CHANNEL_8 | _ADC_CHANNEL_9);
  ADC1_Init();
  Delay_ms(100);
}

static void InitializeTouchPanel() {
  Init_ADC();
  TFT_Set_Default_Mode();
  TFT_Init_ILI9341_8bit(320, 240);

  TP_TFT_Init(320, 240, 8, 9);                                  // Initialize touch panel
  TP_TFT_Set_ADC_Threshold(ADC_THRESHOLD);                              // Set touch panel ADC threshold

  PenDown = 0;
  PressedObject = 0;
  PressedObjectType = -1;
}

void Calibrate() {
  TP_TFT_Set_Calibration_Consts(x_min, x_max, y_min, y_max);
}


/////////////////////////
  TScreen*  CurrentScreen;

  TScreen                Screen1;  //Main screen
  TButton               Button_7ajs;
char Button_7ajs_Caption[8][2] = {"7","a","j","s","&","A","J","S"};    //a,j,s

  TButton               Button_4dmv;
char Button_4dmv_Caption[8][2] = {"4","d","m","v","$","D","M","V"};    //d,m,v

  TButton               Button_1gpy;
char Button_1gpy_Caption[8][2] = {"1","g","p","y","!","G","P","Y"};           //g,p,y

  TButton               Button_0_;
char Button_0__Caption[8][2] = {"0"," "," "," ",")"," "," "," "};          //space

  TButton               Button_8bkt;
char Button_8bkt_Caption[8][2] = {"8","b","k","t","*","B","K","T"};         //b,k,t

  TButton               Button_5enw;
char Button_5enw_Caption[8][2] = {"5","e","n","w","%","E","N","W"};        //e,n,w

  TButton               Button_2hqz;
char Button_2hqz_Caption[8][2] = {"2","h","q","z","@","H","Q","Z"};       //h,q,z

  TButton               Button_pt;
char Button_pt_Caption[8][2] = {".",".",".",".",",",",",",",","};       //

  TButton               Button_9clu;
char Button_9clu_Caption[8][2] = {"9","c","l","u","(","C","L","U"};       //c,l,u

  TButton               Button_6fox;
char Button_6fox_Caption[8][2] = {"6","f","o","x","+","F","O","X"};       //f,o,x

  TButton               Button_3ir_;
char Button_3ir__Caption[8][2] = {"3","i","r","-","?","I","R","_"};      //i,r,-

  TButton               Button_Del;
char Button_Del_Caption[8][2] = {"<","<","<","<","<","<","<","<"};

  TButton               Button_Shift;
char Button_Shift_Caption[8][2] = {"^","^","^","^","^","^","^","^"};

  TBox                   Box3;      //Writing box
  TButton               Button_KB1;
char Button_KB1_Caption[8][4] = {"0-9","0-9","0-9","0-9","SYM","SYM","SYM","SYM"};

  TButton               Button_KB2;
char Button_KB2_Caption[8][4] = {"a-i","a-i","a-i","a-i","A-I","A-I","A-I","A-I"};

  TButton               Button_KB3;
char Button_KB3_Caption[8][4] = {"j-r","j-r","j-r","j-r","J-R","J-R","J-R","J-R"};

  TButton               Button_KB4;
char Button_KB4_Caption[8][4] = {"s-z","s-z","s-z","s-z","S-Z","S-Z","S-Z","S-Z"};

  TButton               Button_Finish;
char Button_Finish_Caption[8][3] = {"#","#","#","#","#","#","#","#"};

  TBox                   Box1;
  TLabel                 Label_Addr1;
char Label_Addr1_Caption[18];

  TLabel                 Label_Addr2;
char Label_Addr2_Caption[18];

  TLabel                 Label_Value1;
char Label_Value1_Caption[25];

  TLabel                 Label_Value2;
char Label_Value2_Caption[25];

  TLabel                 Label_Title;
const char Label_Title_Caption[] = "BTC  Token";

  TLabel                 Label_Sign;
char Label_Sign_Caption[4] = "";

  TButton                * const code Screen1_Buttons[18]=
         {
         &Button_7ajs,
         &Button_4dmv,
         &Button_1gpy,
         &Button_0_,
         &Button_8bkt,
         &Button_5enw,
         &Button_2hqz,
         &Button_pt,
         &Button_9clu,
         &Button_6fox,
         &Button_3ir_,
         &Button_KB3,
         &Button_KB4,
         &Button_Del,
         &Button_Shift,
         &Button_KB1,
         &Button_KB2,
         &Button_Finish
         };
  TLabel                 * const code Screen1_Labels[6]=
         {
         &Label_Addr1,
         &Label_Addr2,
         &Label_Value1,
         &Label_Value2,
         &Label_Title,
         &Label_Sign
         };
  TBox                   * const code Screen1_Boxes[2]=
         {
         &Box3,                
         &Box1                 
         };


  TScreen                Screen2;
  TLabel                 Label_Message;
char Label_Message_Caption[64];

  TLabel                 * const code Screen2_Labels[1]=
         {
         &Label_Message,
         };




static void InitializeObjects() {
  Screen1.Color                     = 0x0000;
  Screen1.Width                     = 240;
  Screen1.Height                    = 320;
  Screen1.ButtonsCount              = 18;
  Screen1.Buttons                   = Screen1_Buttons;
  Screen1.LabelsCount               = 6;
  Screen1.Labels                    = Screen1_Labels;
  Screen1.BoxesCount                = 2;
  Screen1.Boxes                     = Screen1_Boxes;
  Screen1.ObjectsCount              = 26;

  Screen2.Color                     = 0x0000;
  Screen2.Width                     = 320;
  Screen2.Height                    = 240;
  Screen2.ButtonsCount              = 0;
  Screen2.LabelsCount               = 1;
  Screen2.Labels                    = Screen2_Labels;
  Screen2.BoxesCount                = 0;
  Screen2.ObjectsCount              = 1;

  Box3.OwnerScreen     = &Screen1;
  Box3.Order           = 15;
  Box3.Left            = 0;
  Box3.Top             = 25;
  Box3.Width           = 240;
  Box3.Height          = 97;
  Box3.Pen_Width       = 0;
  Box3.Pen_Color       = 0x0000;
  Box3.Visible         = 1;
  Box3.Active          = 1;
  Box3.Transparent     = 1;
  Box3.Gradient        = 0;
  Box3.Gradient_Orientation    = 0;
  Box3.Gradient_Start_Color    = 0x07E0;
  Box3.Gradient_End_Color      = 0x0540;
  Box3.Color           = 0x07E8;
  Box3.PressColEnabled     = 0;
  Box3.Press_Color     = 0x8410;
  Box3.OnUpPtr         = 0;
  Box3.OnDownPtr       = 0;
  Box3.OnClickPtr      = 0;
  Box3.OnPressPtr      = 0;

  Box1.OwnerScreen     = &Screen1;
  Box1.Order           = 19;
  Box1.Left            = 0;
  Box1.Top             = 0;
  Box1.Width           = 240;
  Box1.Height          = 26;
  Box1.Pen_Width       = 1;
  Box1.Pen_Color       = 0x0000;
  Box1.Visible         = 1;
  Box1.Active          = 1;
  Box1.Transparent     = 1;
  Box1.Gradient        = 1;
  Box1.Gradient_Orientation    = 0;
  Box1.Gradient_Start_Color    = Numbers_Gradient_Start_Color;
  Box1.Gradient_End_Color      = Numbers_Gradient_End_Color;
  Box1.Color           = 0xC618;
  Box1.PressColEnabled     = 0;
  Box1.Press_Color     = 0x8410;
  Box1.OnUpPtr         = 0;
  Box1.OnDownPtr       = 0;
  Box1.OnClickPtr      = 0;
  Box1.OnPressPtr      = 0;

  Label_Addr1.OwnerScreen     = &Screen1;
  Label_Addr1.Order          = 20;
  Label_Addr1.Left           = 25;
  Label_Addr1.Top            = 30;
  Label_Addr1.Width          = 210;
  Label_Addr1.Height         = 20;
  Label_Addr1.Visible        = 1;
  Label_Addr1.Active         = 1;
  Label_Addr1.Caption        = Label_Addr1_Caption;
  Label_Addr1.FontName       = Courier_New12x23_Bold;
  Label_Addr1.Font_Color     = 0x0000;
  Label_Addr1.OnUpPtr         = 0;
  Label_Addr1.OnDownPtr       = 0;
  Label_Addr1.OnClickPtr      = 0;
  Label_Addr1.OnPressPtr      = 0;

  Label_Addr2.OwnerScreen     = &Screen1;
  Label_Addr2.Order          = 21;
  Label_Addr2.Left           = 25;
  Label_Addr2.Top            = 46;
  Label_Addr2.Width          = 210;
  Label_Addr2.Height         = 20;
  Label_Addr2.Visible        = 1;
  Label_Addr2.Active         = 1;
  Label_Addr2.Caption        = Label_Addr2_Caption;
  Label_Addr2.FontName       = Courier_New12x23_Bold;
  Label_Addr2.Font_Color     = 0x0000;
  Label_Addr2.OnUpPtr         = 0;
  Label_Addr2.OnDownPtr       = 0;
  Label_Addr2.OnClickPtr      = 0;
  Label_Addr2.OnPressPtr      = 0;

  Label_Value1.OwnerScreen     = &Screen1;
  Label_Value1.Order          = 22;
  Label_Value1.Left           = 15;
  Label_Value1.Top            = 65;
  Label_Value1.Width          = 210;
  Label_Value1.Height         = 20;
  Label_Value1.Visible        = 1;
  Label_Value1.Active         = 1;
  Label_Value1.Caption        = Label_Value1_Caption;
  Label_Value1.FontName       = Courier_New12x23_Bold;
  Label_Value1.Font_Color     = 0x0000;
  Label_Value1.OnUpPtr         = 0;
  Label_Value1.OnDownPtr       = 0;
  Label_Value1.OnClickPtr      = 0;
  Label_Value1.OnPressPtr      = 0;

  Label_Value2.OwnerScreen     = &Screen1;
  Label_Value2.Order          = 23;
  Label_Value2.Left           = 15;
  Label_Value2.Top            = 81;
  Label_Value2.Width          = 210;
  Label_Value2.Height         = 20;
  Label_Value2.Visible        = 1;
  Label_Value2.Active         = 1;
  Label_Value2.Caption        = Label_Value2_Caption;
  Label_Value2.FontName       = Courier_New12x23_Bold;
  Label_Value2.Font_Color     = 0x0000;
  Label_Value2.OnUpPtr         = 0;
  Label_Value2.OnDownPtr       = 0;
  Label_Value2.OnClickPtr      = 0;
  Label_Value2.OnPressPtr      = 0;

  Label_Title.OwnerScreen     = &Screen1;
  Label_Title.Order          = 24;
  Label_Title.Left           = 15;
  Label_Title.Top            = 5;
  Label_Title.Width          = 210;
  Label_Title.Height         = 20;
  Label_Title.Visible        = 1;
  Label_Title.Active         = 1;
  Label_Title.Caption        = Label_Title_Caption;
  Label_Title.FontName       = Arial16x19_Bold;
  Label_Title.Font_Color     = 0xFFFF;
  Label_Title.OnUpPtr         = 0;
  Label_Title.OnDownPtr       = 0;
  Label_Title.OnClickPtr      = 0;
  Label_Title.OnPressPtr      = 0;

  Label_Sign.OwnerScreen     = &Screen1;
  Label_Sign.Order          = 25;
  Label_Sign.Left           = 5;
  Label_Sign.Top            = 27;
  Label_Sign.Width          = 12;
  Label_Sign.Height         = 22;
  Label_Sign.Visible        = 1;
  Label_Sign.Active         = 1;
  Label_Sign.Caption        = Label_Sign_Caption;
  Label_Sign.FontName       = Courier_New12x23_Bold;
  Label_Sign.Font_Color     = 0xF800;
  Label_Sign.OnUpPtr         = 0;
  Label_Sign.OnDownPtr       = 0;
  Label_Sign.OnClickPtr      = 0;
  Label_Sign.OnPressPtr      = 0;

  Label_Message.OwnerScreen     = &Screen2;
  Label_Message.Order          = 0;
  Label_Message.Left           = 5;
  Label_Message.Top            = 5;
  Label_Message.Width          = 310;
  Label_Message.Height         = 230;
  Label_Message.Visible        = 1;
  Label_Message.Active         = 1;
  Label_Message.Caption        = Label_Message_Caption;
  Label_Message.FontName       = Tahoma13x16_Regular;
  Label_Message.Font_Color     = 0xFFFF;
  Label_Message.OnUpPtr         = 0;
  Label_Message.OnDownPtr       = 0;
  Label_Message.OnClickPtr      = 0;
  Label_Message.OnPressPtr      = 0;
}

static void InitializeButtons() {
  Button_7ajs.OwnerScreen     = &Screen1;
  Button_7ajs.Order           = 0;
  Button_7ajs.Left            = 0;
  Button_7ajs.Top             = 162;
  Button_7ajs.Width           = 60;
  Button_7ajs.Height          = 40;
  Button_7ajs.Pen_Width       = 1;
  Button_7ajs.Pen_Color       = 0x0000;
  Button_7ajs.Visible         = 1;
  Button_7ajs.Active          = 1;
  Button_7ajs.Transparent     = 1;
  Button_7ajs.Caption         = Button_7ajs_Caption[kb+4*shift];
  Button_7ajs.FontName        = Arial21x24_Bold;
  Button_7ajs.PressColEnabled = 1;
  Button_7ajs.Font_Color      = 0xFFFF;
  Button_7ajs.Gradient        = 1;
  Button_7ajs.Gradient_Orientation    = 0;
  Button_7ajs.Gradient_Start_Color    = Numbers_Gradient_Start_Color;
  Button_7ajs.Gradient_End_Color      = Numbers_Gradient_End_Color;
  Button_7ajs.Color           = 0xC618;
  Button_7ajs.Press_Color     = 0xC618;
  Button_7ajs.OnUpPtr         = 0;
  Button_7ajs.OnDownPtr       = 0;
  Button_7ajs.OnClickPtr      = Button_7ajsClick;
  Button_7ajs.OnPressPtr      = 0;

  Button_4dmv.OwnerScreen     = &Screen1;
  Button_4dmv.Order           = 1;
  Button_4dmv.Left            = 0;
  Button_4dmv.Top             = 202;
  Button_4dmv.Width           = 60;
  Button_4dmv.Height          = 40;
  Button_4dmv.Pen_Width       = 1;
  Button_4dmv.Pen_Color       = 0x0000;
  Button_4dmv.Visible         = 1;
  Button_4dmv.Active          = 1;
  Button_4dmv.Transparent     = 1;
  Button_4dmv.Caption         = Button_4dmv_Caption[kb+4*shift];
  Button_4dmv.FontName        = Arial21x24_Bold;
  Button_4dmv.PressColEnabled = 1;
  Button_4dmv.Font_Color      = 0xFFFF;
  Button_4dmv.Gradient        = 1;
  Button_4dmv.Gradient_Orientation    = 0;
  Button_4dmv.Gradient_Start_Color    = Numbers_Gradient_Start_Color;
  Button_4dmv.Gradient_End_Color      = Numbers_Gradient_End_Color;
  Button_4dmv.Color           = 0xC618;
  Button_4dmv.Press_Color     = 0xC618;
  Button_4dmv.OnUpPtr         = 0;
  Button_4dmv.OnDownPtr       = 0;
  Button_4dmv.OnClickPtr      = Button_4dmvClick;
  Button_4dmv.OnPressPtr      = 0;

  Button_1gpy.OwnerScreen     = &Screen1;
  Button_1gpy.Order           = 2;
  Button_1gpy.Left            = 0;
  Button_1gpy.Top             = 242;
  Button_1gpy.Width           = 60;
  Button_1gpy.Height          = 40;
  Button_1gpy.Pen_Width       = 1;
  Button_1gpy.Pen_Color       = 0x0000;
  Button_1gpy.Visible         = 1;
  Button_1gpy.Active          = 1;
  Button_1gpy.Transparent     = 1;
  Button_1gpy.Caption         = Button_1gpy_Caption[kb+4*shift];
  Button_1gpy.FontName        = Arial21x24_Bold;
  Button_1gpy.PressColEnabled = 1;
  Button_1gpy.Font_Color      = 0xFFFF;
  Button_1gpy.Gradient        = 1;
  Button_1gpy.Gradient_Orientation    = 0;
  Button_1gpy.Gradient_Start_Color    = Numbers_Gradient_Start_Color;
  Button_1gpy.Gradient_End_Color      = Numbers_Gradient_End_Color;
  Button_1gpy.Color           = 0xC618;
  Button_1gpy.Press_Color     = 0xC618;
  Button_1gpy.OnUpPtr         = 0;
  Button_1gpy.OnDownPtr       = 0;
  Button_1gpy.OnClickPtr      = Button_1gpyClick;
  Button_1gpy.OnPressPtr      = 0;

  Button_0_.OwnerScreen     = &Screen1;
  Button_0_.Order           = 3;
  Button_0_.Left            = 0;
  Button_0_.Top             = 282;
  Button_0_.Width           = 120;
  Button_0_.Height          = 40;
  Button_0_.Pen_Width       = 1;
  Button_0_.Pen_Color       = 0x0000;
  Button_0_.Visible         = 1;
  Button_0_.Active          = 1;
  Button_0_.Transparent     = 1;
  Button_0_.Caption         = Button_0__Caption[kb+4*shift];
  Button_0_.FontName        = Arial21x24_Bold;
  Button_0_.PressColEnabled = 1;
  Button_0_.Font_Color      = 0xFFFF;
  Button_0_.Gradient        = 1;
  Button_0_.Gradient_Orientation    = 0;
  Button_0_.Gradient_Start_Color    = Numbers_Gradient_Start_Color;
  Button_0_.Gradient_End_Color      = Numbers_Gradient_End_Color;
  Button_0_.Color           = 0xC618;
  Button_0_.Press_Color     = 0xC618;
  Button_0_.OnUpPtr         = 0;
  Button_0_.OnDownPtr       = 0;
  Button_0_.OnClickPtr      = Button_0_Click;
  Button_0_.OnPressPtr      = 0;

  Button_8bkt.OwnerScreen     = &Screen1;
  Button_8bkt.Order           = 4;
  Button_8bkt.Left            = 60;
  Button_8bkt.Top             = 162;
  Button_8bkt.Width           = 60;
  Button_8bkt.Height          = 40;
  Button_8bkt.Pen_Width       = 1;
  Button_8bkt.Pen_Color       = 0x0000;
  Button_8bkt.Visible         = 1;
  Button_8bkt.Active          = 1;
  Button_8bkt.Transparent     = 1;
  Button_8bkt.Caption         = Button_8bkt_Caption[kb+4*shift];
  Button_8bkt.FontName        = Arial21x24_Bold;
  Button_8bkt.PressColEnabled = 1;
  Button_8bkt.Font_Color      = 0xFFFF;
  Button_8bkt.Gradient        = 1;
  Button_8bkt.Gradient_Orientation    = 0;
  Button_8bkt.Gradient_Start_Color    = Numbers_Gradient_Start_Color;
  Button_8bkt.Gradient_End_Color      = Numbers_Gradient_End_Color;
  Button_8bkt.Color           = 0xC618;
  Button_8bkt.Press_Color     = 0xC618;
  Button_8bkt.OnUpPtr         = 0;
  Button_8bkt.OnDownPtr       = 0;
  Button_8bkt.OnClickPtr      = Button_8bktClick;
  Button_8bkt.OnPressPtr      = 0;

  Button_5enw.OwnerScreen     = &Screen1;
  Button_5enw.Order           = 5;
  Button_5enw.Left            = 60;
  Button_5enw.Top             = 202;
  Button_5enw.Width           = 60;
  Button_5enw.Height          = 40;
  Button_5enw.Pen_Width       = 1;
  Button_5enw.Pen_Color       = 0x0000;
  Button_5enw.Visible         = 1;
  Button_5enw.Active          = 1;
  Button_5enw.Transparent     = 1;
  Button_5enw.Caption         = Button_5enw_Caption[kb+4*shift];
  Button_5enw.FontName        = Arial21x24_Bold;
  Button_5enw.PressColEnabled = 1;
  Button_5enw.Font_Color      = 0xFFFF;
  Button_5enw.Gradient        = 1;
  Button_5enw.Gradient_Orientation    = 0;
  Button_5enw.Gradient_Start_Color    = Numbers_Gradient_Start_Color;
  Button_5enw.Gradient_End_Color      = Numbers_Gradient_End_Color;
  Button_5enw.Color           = 0xC618;
  Button_5enw.Press_Color     = 0xC618;
  Button_5enw.OnUpPtr         = 0;
  Button_5enw.OnDownPtr       = 0;
  Button_5enw.OnClickPtr      = Button_5enwClick;
  Button_5enw.OnPressPtr      = 0;

  Button_2hqz.OwnerScreen     = &Screen1;
  Button_2hqz.Order           = 6;
  Button_2hqz.Left            = 60;
  Button_2hqz.Top             = 242;
  Button_2hqz.Width           = 60;
  Button_2hqz.Height          = 40;
  Button_2hqz.Pen_Width       = 1;
  Button_2hqz.Pen_Color       = 0x0000;
  Button_2hqz.Visible         = 1;
  Button_2hqz.Active          = 1;
  Button_2hqz.Transparent     = 1;
  Button_2hqz.Caption         = Button_2hqz_Caption[kb+4*shift];
  Button_2hqz.FontName        = Arial21x24_Bold;
  Button_2hqz.PressColEnabled = 1;
  Button_2hqz.Font_Color      = 0xFFFF;
  Button_2hqz.Gradient        = 1;
  Button_2hqz.Gradient_Orientation    = 0;
  Button_2hqz.Gradient_Start_Color    = Numbers_Gradient_Start_Color;
  Button_2hqz.Gradient_End_Color      = Numbers_Gradient_End_Color;
  Button_2hqz.Color           = 0xC618;
  Button_2hqz.Press_Color     = 0xC618;
  Button_2hqz.OnUpPtr         = 0;
  Button_2hqz.OnDownPtr       = 0;
  Button_2hqz.OnClickPtr      = Button_2hqzClick;
  Button_2hqz.OnPressPtr      = 0;

  Button_pt.OwnerScreen     = &Screen1;
  Button_pt.Order           = 7;
  Button_pt.Left            = 120;
  Button_pt.Top             = 282;
  Button_pt.Width           = 60;
  Button_pt.Height          = 40;
  Button_pt.Pen_Width       = 1;
  Button_pt.Pen_Color       = 0x0000;
  Button_pt.Visible         = 1;
  Button_pt.Active          = 1;
  Button_pt.Transparent     = 1;
  Button_pt.Caption         = Button_pt_Caption[kb+4*shift];
  Button_pt.FontName        = Arial21x24_Bold;
  Button_pt.PressColEnabled = 1;
  Button_pt.Font_Color      = 0xFFFF;
  Button_pt.Gradient        = 1;
  Button_pt.Gradient_Orientation    = 0;
  Button_pt.Gradient_Start_Color    = Numbers_Gradient_Start_Color;
  Button_pt.Gradient_End_Color      = Numbers_Gradient_End_Color;
  Button_pt.Color           = 0xC618;
  Button_pt.Press_Color     = 0xC618;
  Button_pt.OnUpPtr         = 0;
  Button_pt.OnDownPtr       = 0;
  Button_pt.OnClickPtr      = Button_ptClick;
  Button_pt.OnPressPtr      = 0;

  Button_9clu.OwnerScreen     = &Screen1;
  Button_9clu.Order           = 8;
  Button_9clu.Left            = 120;
  Button_9clu.Top             = 162;
  Button_9clu.Width           = 60;
  Button_9clu.Height          = 40;
  Button_9clu.Pen_Width       = 1;
  Button_9clu.Pen_Color       = 0x0000;
  Button_9clu.Visible         = 1;
  Button_9clu.Active          = 1;
  Button_9clu.Transparent     = 1;
  Button_9clu.Caption         = Button_9clu_Caption[kb+4*shift];
  Button_9clu.FontName        = Arial21x24_Bold;
  Button_9clu.PressColEnabled = 1;
  Button_9clu.Font_Color      = 0xFFFF;
  Button_9clu.Gradient        = 1;
  Button_9clu.Gradient_Orientation    = 0;
  Button_9clu.Gradient_Start_Color    = Numbers_Gradient_Start_Color;
  Button_9clu.Gradient_End_Color      = Numbers_Gradient_End_Color;
  Button_9clu.Color           = 0xC618;
  Button_9clu.Press_Color     = 0xC618;
  Button_9clu.OnUpPtr         = 0;
  Button_9clu.OnDownPtr       = 0;
  Button_9clu.OnClickPtr      = Button_9cluClick;
  Button_9clu.OnPressPtr      = 0;

  Button_6fox.OwnerScreen     = &Screen1;
  Button_6fox.Order           = 9;
  Button_6fox.Left            = 120;
  Button_6fox.Top             = 202;
  Button_6fox.Width           = 60;
  Button_6fox.Height          = 40;
  Button_6fox.Pen_Width       = 1;
  Button_6fox.Pen_Color       = 0x0000;
  Button_6fox.Visible         = 1;
  Button_6fox.Active          = 1;
  Button_6fox.Transparent     = 1;
  Button_6fox.Caption         = Button_6fox_Caption[kb+4*shift];
  Button_6fox.FontName        = Arial21x24_Bold;
  Button_6fox.PressColEnabled = 1;
  Button_6fox.Font_Color      = 0xFFFF;
  Button_6fox.Gradient        = 1;
  Button_6fox.Gradient_Orientation    = 0;
  Button_6fox.Gradient_Start_Color    = Numbers_Gradient_Start_Color;
  Button_6fox.Gradient_End_Color      = Numbers_Gradient_End_Color;
  Button_6fox.Color           = 0xC618;
  Button_6fox.Press_Color     = 0xC618;
  Button_6fox.OnUpPtr         = 0;
  Button_6fox.OnDownPtr       = 0;
  Button_6fox.OnClickPtr      = Button_6foxClick;
  Button_6fox.OnPressPtr      = 0;

  Button_3ir_.OwnerScreen     = &Screen1;
  Button_3ir_.Order           = 10;
  Button_3ir_.Left            = 120;
  Button_3ir_.Top             = 242;
  Button_3ir_.Width           = 60;
  Button_3ir_.Height          = 40;
  Button_3ir_.Pen_Width       = 1;
  Button_3ir_.Pen_Color       = 0x0000;
  Button_3ir_.Visible         = 1;
  Button_3ir_.Active          = 1;
  Button_3ir_.Transparent     = 1;
  Button_3ir_.Caption         = Button_3ir__Caption[kb+4*shift];
  Button_3ir_.FontName        = Arial21x24_Bold;
  Button_3ir_.PressColEnabled = 1;
  Button_3ir_.Font_Color      = 0xFFFF;
  Button_3ir_.Gradient        = 1;
  Button_3ir_.Gradient_Orientation    = 0;
  Button_3ir_.Gradient_Start_Color    = Numbers_Gradient_Start_Color;
  Button_3ir_.Gradient_End_Color      = Numbers_Gradient_End_Color;
  Button_3ir_.Color           = 0xC618;
  Button_3ir_.Press_Color     = 0xC618;
  Button_3ir_.OnUpPtr         = 0;
  Button_3ir_.OnDownPtr       = 0;
  Button_3ir_.OnClickPtr      = Button_3ir_Click;
  Button_3ir_.OnPressPtr      = 0;

  Button_KB3.OwnerScreen     = &Screen1;
  Button_KB3.Order           = 11;
  Button_KB3.Left            = 120;
  Button_KB3.Top             = 123;
  Button_KB3.Width           = 60;
  Button_KB3.Height          = 40;
  Button_KB3.Pen_Width       = 1;
  Button_KB3.Pen_Color       = 0x0000;
  Button_KB3.Visible         = 1;
  Button_KB3.Active          = 1;
  Button_KB3.Transparent     = 1;
  Button_KB3.Caption         = Button_KB3_Caption[kb+4*shift];
  Button_KB3.FontName        = Arial21x24_Bold;
  Button_KB3.PressColEnabled = 1;
  Button_KB3.Font_Color      = 0xFFFF;
  Button_KB3.Gradient        = 1;
  Button_KB3.Gradient_Orientation    = 0;
  Button_KB3.Gradient_Start_Color    = Other_Gradient_Start_Color;
  Button_KB3.Gradient_End_Color      = Other_Gradient_End_Color;
  Button_KB3.Color           = 0xC618;
  Button_KB3.Press_Color     = 0xC618;
  Button_KB3.OnUpPtr         = 0;
  Button_KB3.OnDownPtr       = 0;
  Button_KB3.OnClickPtr      = Button_KB3Click;
  Button_KB3.OnPressPtr      = 0;

  Button_KB4.OwnerScreen     = &Screen1;
  Button_KB4.Order           = 12;
  Button_KB4.Left            = 180;
  Button_KB4.Top             = 123;
  Button_KB4.Width           = 60;
  Button_KB4.Height          = 40;
  Button_KB4.Pen_Width       = 1;
  Button_KB4.Pen_Color       = 0x0000;
  Button_KB4.Visible         = 1;
  Button_KB4.Active          = 1;
  Button_KB4.Transparent     = 1;
  Button_KB4.Caption         = Button_KB4_Caption[kb+4*shift];
  Button_KB4.FontName        = Arial21x24_Bold;
  Button_KB4.PressColEnabled = 1;
  Button_KB4.Font_Color      = 0xFFFF;
  Button_KB4.Gradient        = 1;
  Button_KB4.Gradient_Orientation    = 0;
  Button_KB4.Gradient_Start_Color    = Other_Gradient_Start_Color;
  Button_KB4.Gradient_End_Color      = Other_Gradient_End_Color;
  Button_KB4.Color           = 0xC618;
  Button_KB4.Press_Color     = 0xC618;
  Button_KB4.OnUpPtr         = 0;
  Button_KB4.OnDownPtr       = 0;
  Button_KB4.OnClickPtr      = Button_KB4Click;
  Button_KB4.OnPressPtr      = 0;

  Button_Del.OwnerScreen     = &Screen1;
  Button_Del.Order           = 13;
  Button_Del.Left            = 180;
  Button_Del.Top             = 162;
  Button_Del.Width           = 60;
  Button_Del.Height          = 40;
  Button_Del.Pen_Width       = 1;
  Button_Del.Pen_Color       = 0x0000;
  Button_Del.Visible         = 1;
  Button_Del.Active          = 1;
  Button_Del.Transparent     = 1;
  Button_Del.Caption         = Button_Del_Caption[kb+4*shift];
  Button_Del.FontName        = Arial21x24_Bold;
  Button_Del.PressColEnabled = 1;
  Button_Del.Font_Color      = 0xFFFF;
  Button_Del.Gradient        = 1;
  Button_Del.Gradient_Orientation    = 0;
  Button_Del.Gradient_Start_Color    = Other_Gradient_Start_Color;
  Button_Del.Gradient_End_Color      = Other_Gradient_End_Color;
  Button_Del.Color           = 0xC618;
  Button_Del.Press_Color     = 0xC618;
  Button_Del.OnUpPtr         = 0;
  Button_Del.OnDownPtr       = 0;
  Button_Del.OnClickPtr      = Button_DelClick;
  Button_Del.OnPressPtr      = 0;

  Button_Shift.OwnerScreen     = &Screen1;
  Button_Shift.Order           = 14;
  Button_Shift.Left            = 180;
  Button_Shift.Top             = 202;
  Button_Shift.Width           = 60;
  Button_Shift.Height          = 40;
  Button_Shift.Pen_Width       = 1;
  Button_Shift.Pen_Color       = 0x0000;
  Button_Shift.Visible         = 1;
  Button_Shift.Active          = 1;
  Button_Shift.Transparent     = 1;
  Button_Shift.Caption         = Button_Shift_Caption[kb+4*shift];
  Button_Shift.FontName        = Arial21x24_Bold;
  Button_Shift.PressColEnabled = 1;
  Button_Shift.Font_Color      = 0xFFFF;
  Button_Shift.Gradient        = 1;
  Button_Shift.Gradient_Orientation    = 0;
  Button_Shift.Gradient_Start_Color    = Other_Gradient_Start_Color;
  Button_Shift.Gradient_End_Color      = Other_Gradient_End_Color;
  Button_Shift.Color           = 0xC618;
  Button_Shift.Press_Color     = 0xC618;
  Button_Shift.OnUpPtr         = 0;
  Button_Shift.OnDownPtr       = 0;
  Button_Shift.OnClickPtr      = Button_ShiftClick;
  Button_Shift.OnPressPtr      = 0;

  Button_KB1.OwnerScreen     = &Screen1;
  Button_KB1.Order           = 16;
  Button_KB1.Left            = 0;
  Button_KB1.Top             = 123;
  Button_KB1.Width           = 60;
  Button_KB1.Height          = 40;
  Button_KB1.Pen_Width       = 1;
  Button_KB1.Pen_Color       = 0x0000;
  Button_KB1.Visible         = 1;
  Button_KB1.Active          = 1;
  Button_KB1.Transparent     = 1;
  Button_KB1.Caption         = Button_KB1_Caption[kb+4*shift];
  Button_KB1.FontName        = Arial21x24_Bold;
  Button_KB1.PressColEnabled = 1;
  Button_KB1.Font_Color      = 0xFFFF;
  Button_KB1.Gradient        = 1;
  Button_KB1.Gradient_Orientation    = 0;
  Button_KB1.Gradient_Start_Color    = Other_Gradient_Start_Color;
  Button_KB1.Gradient_End_Color      = Other_Gradient_End_Color;
  Button_KB1.Color           = 0xC618;
  Button_KB1.Press_Color     = 0xC618;
  Button_KB1.OnUpPtr         = 0;
  Button_KB1.OnDownPtr       = 0;
  Button_KB1.OnClickPtr      = Button_KB1Click;
  Button_KB1.OnPressPtr      = 0;

  Button_KB2.OwnerScreen     = &Screen1;
  Button_KB2.Order           = 17;
  Button_KB2.Left            = 60;
  Button_KB2.Top             = 123;
  Button_KB2.Width           = 60;
  Button_KB2.Height          = 40;
  Button_KB2.Pen_Width       = 1;
  Button_KB2.Pen_Color       = 0x0000;
  Button_KB2.Visible         = 1;
  Button_KB2.Active          = 1;
  Button_KB2.Transparent     = 1;
  Button_KB2.Caption         = Button_KB2_Caption[kb+4*shift];
  Button_KB2.FontName        = Arial21x24_Bold;
  Button_KB2.PressColEnabled = 1;
  Button_KB2.Font_Color      = 0xFFFF;
  Button_KB2.Gradient        = 1;
  Button_KB2.Gradient_Orientation    = 0;
  Button_KB2.Gradient_Start_Color    = Other_Gradient_Start_Color;
  Button_KB2.Gradient_End_Color      = Other_Gradient_End_Color;
  Button_KB2.Color           = 0xC618;
  Button_KB2.Press_Color     = 0xC618;
  Button_KB2.OnUpPtr         = 0;
  Button_KB2.OnDownPtr       = 0;
  Button_KB2.OnClickPtr      = Button_KB2Click;
  Button_KB2.OnPressPtr      = 0;

  Button_Finish.OwnerScreen     = &Screen1;
  Button_Finish.Order           = 18;
  Button_Finish.Left            = 180;
  Button_Finish.Top             = 242;
  Button_Finish.Width           = 60;
  Button_Finish.Height          = 80;
  Button_Finish.Pen_Width       = 1;
  Button_Finish.Pen_Color       = 0x0000;
  Button_Finish.Visible         = 1;
  Button_Finish.Active          = 1;
  Button_Finish.Transparent     = 1;
  Button_Finish.Caption         = Button_Finish_Caption[kb+4*shift];
  Button_Finish.FontName        = Arial21x24_Bold;
  Button_Finish.PressColEnabled = 1;
  Button_Finish.Font_Color      = 0xFFFF;
  Button_Finish.Gradient        = 1;
  Button_Finish.Gradient_Orientation    = 0;
  Button_Finish.Gradient_Start_Color    = Other_Gradient_Start_Color;
  Button_Finish.Gradient_End_Color      = Other_Gradient_End_Color;
  Button_Finish.Color           = 0xC618;
  Button_Finish.Press_Color     = 0xC618;
  Button_Finish.OnUpPtr         = 0;
  Button_Finish.OnDownPtr       = 0;
  Button_Finish.OnClickPtr      = Button_FinishClick;
  Button_Finish.OnPressPtr      = 0;
}

static char IsInsideObject (unsigned int X, unsigned int Y, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height) { // static
  if ( (Left<= X) && (Left+ Width - 1 >= X) &&
       (Top <= Y)  && (Top + Height - 1 >= Y) )
    return 1;
  else
    return 0;
}


#define GetButton(index)              CurrentScreen->Buttons[index]
#define GetLabel(index)               CurrentScreen->Labels[index]
#define GetBox(index)                 CurrentScreen->Boxes[index]


void DrawButton(TButton *Abutton) {
  InitializeButtons();
  if (Abutton->Visible == 1) {
    if (object_pressed == 1) {
      object_pressed = 0;
      TFT_Set_Brush(Abutton->Transparent, Abutton->Press_Color, Abutton->Gradient, Abutton->Gradient_Orientation, Abutton->Gradient_End_Color, Abutton->Gradient_Start_Color);
    }
    else {
      TFT_Set_Brush(Abutton->Transparent, Abutton->Color, Abutton->Gradient, Abutton->Gradient_Orientation, Abutton->Gradient_Start_Color, Abutton->Gradient_End_Color);
    }
    TFT_Set_Pen(Abutton->Pen_Color, Abutton->Pen_Width);
    TFT_Rectangle(Abutton->Left, Abutton->Top, Abutton->Left + Abutton->Width - 1, Abutton->Top + Abutton->Height - 1);
    TFT_Set_Font(Abutton->FontName, Abutton->Font_Color, FO_HORIZONTAL);
    TFT_Write_Text_Return_Pos(Abutton->Caption, Abutton->Left, Abutton->Top);
    TFT_Write_Text(Abutton->Caption, (Abutton->Left + ((Abutton->Width - caption_length) / 2)), (Abutton->Top + ((Abutton->Height - caption_height) / 2)));
  }
}

void DrawLabel(TLabel *ALabel) {
int x_pos, y_pos;
  x_pos = 0;
  y_pos = 0;
  if (ALabel->Visible == 1) {
    TFT_Set_Font(ALabel->FontName, ALabel->Font_Color, FO_HORIZONTAL);
    TFT_Write_Text_Return_Pos(ALabel->Caption, ALabel->Left, ALabel->Top);
    x_pos = ALabel->Left + ((int)(ALabel->Width - caption_length) / 2);
    y_pos = ALabel->Top + ((int)(ALabel->Height - caption_height) / 2);
    if (x_pos > ALabel->Left) {
      TFT_Write_Text(ALabel->Caption, x_pos, y_pos);
    }
    else {
      TFT_Write_Text(ALabel->Caption, ALabel->Left, ALabel->Top);
    }
  }
}

void DrawBox(TBox *ABox) {
  if (ABox->Visible == 1) {
    if (object_pressed == 1) {
      object_pressed = 0;
      TFT_Set_Brush(ABox->Transparent, ABox->Press_Color, ABox->Gradient, ABox->Gradient_Orientation, ABox->Gradient_End_Color, ABox->Gradient_Start_Color);
    }
    else {
      TFT_Set_Brush(ABox->Transparent, ABox->Color, ABox->Gradient, ABox->Gradient_Orientation, ABox->Gradient_Start_Color, ABox->Gradient_End_Color);
    }
    TFT_Set_Pen(ABox->Pen_Color, ABox->Pen_Width);
    TFT_Rectangle(ABox->Left, ABox->Top, ABox->Left + ABox->Width - 1, ABox->Top + ABox->Height - 1);
  }
}

void DrawScreen(TScreen *aScreen) {
  unsigned short order;
  unsigned short button_idx;
  TButton *local_button;
  unsigned short label_idx;
  TLabel *local_label;
  unsigned short box_idx;
  TBox *local_box;
  char save_bled, save_bled_direction;

  object_pressed = 0;
  order = 0;
  button_idx = 0;
  label_idx = 0;
  box_idx = 0;
  CurrentScreen = aScreen;

  if ((display_width != CurrentScreen->Width) || (display_height != CurrentScreen->Height)) {
    save_bled = TFT_BLED;
    TFT_BLED           = 0;
    TFT_Init_ILI9341_8bit(CurrentScreen->Width, CurrentScreen->Height);
    TP_TFT_Init(CurrentScreen->Width, CurrentScreen->Height, 8, 9);                                  // Initialize touch panel
    TP_TFT_Set_ADC_Threshold(ADC_THRESHOLD);                              // Set touch panel ADC threshold
    TFT_Fill_Screen(CurrentScreen->Color);
    display_width = CurrentScreen->Width;
    display_height = CurrentScreen->Height;
    TFT_BLED           = save_bled;
  }
  else
    TFT_Fill_Screen(CurrentScreen->Color);


  while (order < CurrentScreen->ObjectsCount) {
    if (button_idx < CurrentScreen->ButtonsCount) {
      local_button = GetButton(button_idx);
      if (order == local_button->Order) {
        button_idx++;
        order++;
        DrawButton(local_button);
      }
    }

    if (label_idx < CurrentScreen->LabelsCount) {
      local_label = GetLabel(label_idx);
      if (order == local_label->Order) {
        label_idx++;
        order++;
        DrawLabel(local_label);
      }
    }

    if (box_idx < CurrentScreen->BoxesCount) {
      local_box = GetBox(box_idx);
      if (order == local_box->Order) {
        box_idx++;
        order++;
        DrawBox(local_box);
      }
    }

  }
}

void Get_Object(unsigned int X, unsigned int Y) {
  button_order        = -1;
  label_order         = -1;
  box_order           = -1;
  //  Buttons
  for ( _object_count = 0 ; _object_count < CurrentScreen->ButtonsCount ; _object_count++ ) {
    local_button = GetButton(_object_count);
    if (local_button->Active == 1) {
      if (IsInsideObject(X, Y, local_button->Left, local_button->Top,
                         local_button->Width, local_button->Height) == 1) {
        button_order = local_button->Order;
        exec_button = local_button;
      }
    }
  }

  //  Labels
  for ( _object_count = 0 ; _object_count < CurrentScreen->LabelsCount ; _object_count++ ) {
    local_label = GetLabel(_object_count);
    if (local_label->Active == 1) {
      if (IsInsideObject(X, Y, local_label->Left, local_label->Top,
                         local_label->Width, local_label->Height) == 1) {
        label_order = local_label->Order;
        exec_label = local_label;
      }
    }
  }

  //  Boxes
  for ( _object_count = 0 ; _object_count < CurrentScreen->BoxesCount ; _object_count++ ) {
    local_box = GetBox(_object_count);
    if (local_box->Active == 1) {
      if (IsInsideObject(X, Y, local_box->Left, local_box->Top,
                         local_box->Width, local_box->Height) == 1) {
        box_order = local_box->Order;
        exec_box = local_box;
      }
    }
  }

  _object_count = -1;
  if (button_order > _object_count)
    _object_count = button_order;
  if (label_order >  _object_count )
    _object_count = label_order;
  if (box_order >  _object_count )
    _object_count = box_order;
}


static void Process_TP_Press(unsigned int X, unsigned int Y) {
  exec_button         = 0;
  exec_label          = 0;
  exec_box            = 0;

  Get_Object(X, Y);


  if (_object_count != -1) {
    if (_object_count == button_order) {
      if (exec_button->Active == 1) {
        if (exec_button->OnPressPtr != 0) {
          exec_button->OnPressPtr();
          return;
        }
      }
    }

    if (_object_count == label_order) {
      if (exec_label->Active == 1) {
        if (exec_label->OnPressPtr != 0) {
          exec_label->OnPressPtr();
          return;
        }
      }
    }

    if (_object_count == box_order) {
      if (exec_box->Active == 1) {
        if (exec_box->OnPressPtr != 0) {
          exec_box->OnPressPtr();
          return;
        }
      }
    }

  }
}

static void Process_TP_Up(unsigned int X, unsigned int Y) {

  switch (PressedObjectType) {
    // Button
    case 0: {
      if (PressedObject != 0) {
        exec_button = (TButton*)PressedObject;
        if ((exec_button->PressColEnabled == 1) && (exec_button->OwnerScreen == CurrentScreen)) {
          DrawButton(exec_button);
        }
        break;
      }
      break;
    }
    // Box
    case 6: {
      if (PressedObject != 0) {
        exec_box = (TBox*)PressedObject;
        if ((exec_box->PressColEnabled == 1) && (exec_box->OwnerScreen == CurrentScreen)) {
          DrawBox(exec_box);
        }
        break;
      }
      break;
    }
  }

  exec_label          = 0;

  Get_Object(X, Y);


  if (_object_count != -1) {
  // Buttons
    if (_object_count == button_order) {
      if (exec_button->Active == 1) {
        if (exec_button->OnUpPtr != 0)
          exec_button->OnUpPtr();
        if (PressedObject == (void *)exec_button)
          if (exec_button->OnClickPtr != 0)
            exec_button->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  // Labels
    if (_object_count == label_order) {
      if (exec_label->Active == 1) {
        if (exec_label->OnUpPtr != 0)
          exec_label->OnUpPtr();
        if (PressedObject == (void *)exec_label)
          if (exec_label->OnClickPtr != 0)
            exec_label->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  // Boxes
    if (_object_count == box_order) {
      if (exec_box->Active == 1) {
        if (exec_box->OnUpPtr != 0)
          exec_box->OnUpPtr();
        if (PressedObject == (void *)exec_box)
          if (exec_box->OnClickPtr != 0)
            exec_box->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  }
  PressedObject = 0;
  PressedObjectType = -1;
}

static void Process_TP_Down(unsigned int X, unsigned int Y) {

  object_pressed      = 0;
  exec_button         = 0;
  exec_label          = 0;
  exec_box            = 0;

  Get_Object(X, Y);

  if (_object_count != -1) {
    if (_object_count == button_order) {
      if (exec_button->Active == 1) {
        if (exec_button->PressColEnabled == 1) {
          object_pressed = 1;
          DrawButton(exec_button);
        }
        PressedObject = (void *)exec_button;
        PressedObjectType = 0;
        if (exec_button->OnDownPtr != 0) {
          exec_button->OnDownPtr();
          return;
        }
      }
    }

    if (_object_count == label_order) {
      if (exec_label->Active == 1) {
        PressedObject = (void *)exec_label;
        PressedObjectType = 2;
        if (exec_label->OnDownPtr != 0) {
          exec_label->OnDownPtr();
          return;
        }
      }
    }

    if (_object_count == box_order) {
      if (exec_box->Active == 1) {
        if (exec_box->PressColEnabled == 1) {
          object_pressed = 1;
          DrawBox(exec_box);
        }
        PressedObject = (void *)exec_box;
        PressedObjectType = 6;
        if (exec_box->OnDownPtr != 0) {
          exec_box->OnDownPtr();
          return;
        }
      }
    }

  }
}

void Check_TP() {
  if (TP_TFT_Press_Detect()) {
    // After a PRESS is detected read X-Y and convert it to Display dimensions space
    if (TP_TFT_Get_Coordinates(&Xcoord, &Ycoord) == 0) {
      Process_TP_Press(Xcoord, Ycoord);
      if (PenDown == 0) {
        PenDown = 1;
        Process_TP_Down(Xcoord, Ycoord);
      }
    }
  }
  else if (PenDown == 1) {
    PenDown = 0;
    Process_TP_Up(Xcoord, Ycoord);
  }
}

void Init_MCU(){
  GPIO_Config(&GPIOE_BASE, _GPIO_PINMASK_9, _GPIO_CFG_DIGITAL_OUTPUT);
  TFT_BLED = 1;
  TFT_Set_Default_Mode();
  TP_TFT_Set_Default_Mode();
}

void Start_TP() {
  Init_MCU();

  InitializeTouchPanel();

  //Delay_ms(1000);
  TFT_Fill_Screen(0);
  Calibrate();
  TFT_Fill_Screen(0);

  InitializeObjects();
  display_width = Screen1.Height;
  display_height = Screen1.Width;
  kb = shift = 0;
  //DrawScreen(&Screen1);
}

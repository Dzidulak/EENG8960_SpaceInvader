// The maps for the various characters
static char sprite1[] ={
    0x20,0x80,0x11,0x00,0x3F,0x80,0x6E,0xC0,0xFF,0xE0,0xBF,0xA0,0xA0,0xA0,0x1B ,0x00
    };
static char sprite2[] ={
    0x20,0x80,0x91,0x20,0xBF,0xA0,0xEE,0xE0,0xFF,0xE0,0x3F,0x80,0x20,0x80,0x1B ,0x00
    };
static char shooter[] = {
    0x04,0x00,0x0E,0x00,0x0E,0x00,0x7F,0xC0,0xFF,0xE0,0xFF,0xE0,0xFF,0xE0,0xFF ,0xE0
    };
    
struct sprite{
    char snum; //sprite number
    int xpos;
    int ypos;
    int oldy;
    char active;
    char *type;
    // x position
    // y position
    // prvious y pos
     // 1 = sprite displayed 0 = sprite destroyed
     //sprite1 or 2
    };
    
sprite spritetab[] = {
     {0,1,0,0,1,sprite1},
     {1,16,0,0,1,sprite2},
     {2,32,0,0,1,sprite1},
     {3,48,0,0,1,sprite2},
     {4,64,0,0,1,sprite1},
     {5,80,0,0,1,sprite2},
     {6,96,0,0,1,sprite1},
     {7,112,0,0,1,sprite2}
    };
// Some defines
#define WIN 1
#define LOOSE 0
#define BASE 24 // the display baseline Y location for the shooter

PwmOut r(p23);//red rgb
PwmOut g(p24);//green rgb
C12832 lcd(p5, p7, p6, p8, p11);
//joystick declarations
DigitalIn joyL(p13);
DigitalIn joyR(p16);
InterruptIn joyC(p14);


#include "mbed.h"
#include "C12832.h" // LCD display
#include "graphics.h"

int setup_shooter();
int draw_shooter(int, int); //Display the shooter at some point shx
int getnew_shooter(int); // get the new shooter position (X axis)
void draw_sprite(struct sprite *);
void endgame(char);
Bitmap bm ; //Create a bitmap structure
struct sprite *ps = spritetab;
struct sprite *dps;
    int nsxp; // new shooter x position
    int osxp; // old shooter x position
    int numsprite = 7;
//Custom additions
void draw_bullet();//Display the bullet at shooter point 
void moveSprite();//moves the sprites 
void sprite_kill(struct sprite *ps);//kill the sprite 
int bullx;
int bully = BASE - 4;;
Ticker tick;
int switchCounter = 0;
int downCounter = 0;
int killCount;
bool firstLine = true;
bool gameOver = false;

int main() {
    float t = 0.01;
    
    
    //Set up the bitmap parameters for the display objects
    bm.xSize = 16; // 16 pixels wide
    bm.ySize = 8; // 8 pixels high
    bm.Byte_in_Line = 2; //i.e. 16bits
    
    //Initialise the PWM period for the multi colour LED control
    r.period(0.001);
    //And turn the 2 active (R and G) colours off
    r = 1.0; g = 1.0;
    
    // Draw the shooter image in its initial position
    // i.e x = 1 and y = 24 the base line
    osxp = setup_shooter();
    
    
    tick.attach(&moveSprite, 2.0);//make sprites move continously throught game.
    killCount = 0;//increments everytime a sprite is killed.
    
    while(1){ 
        
        nsxp = getnew_shooter(osxp);// Get the new shooter position   
        osxp = draw_shooter(nsxp,osxp);//Draw it shooter st new postion
        wait(t);
    
        bullx = osxp + 5;//bullet x position.
        
        //When all sprites are killed the lcd scrren will clear and show that the player has won
        if(killCount == 8){
            endgame(WIN);
        }
        if(ps->ypos == 24){
            gameOver = true;
            endgame(LOOSE);
        }
        
        
        if (joyC){
            printf("Kill count = %d\n", killCount);
            draw_bullet();
            bm.data = ps->type;//use sprite image as defined by type
            //Kill sprite 1
            if(bullx >= ps[0].xpos && bullx <= ps[0].xpos +10){
                if(ps[0].active == 1){
                    ps[0].active = 0;
                    sprite_kill(&ps[0]);//function removes sprite from screen
                    killCount++;//increment the kill count
                    printf("Kill count = %d\n", killCount);
                }
            }
            //same situation for 7 below as above. 
            else if(bullx >= ps[1].xpos && bullx <= ps[1].xpos+10){//Kill sprite 2
                if(ps[1].active == 1){
                    ps[1].active = 0;
                    sprite_kill(&ps[1]);
                    killCount++;
                    printf("Kill count = %d\n", killCount);
                }
            }
            else if(bullx >= ps[2].xpos && bullx <= ps[2].xpos+10){//Kill sprite 3
                if(ps[2].active == 1){
                    ps[2].active = 0;
                    sprite_kill(&ps[2]);
                    killCount++;
                    printf("Kill count = %d\n", killCount);
                }
            }
            else if(bullx >= ps[3].xpos && bullx <= ps[3].xpos+10){//Kill sprite 4
                if(ps[3].active == 1){
                    ps[3].active = 0;
                    sprite_kill(&ps[3]);
                    killCount++;
                    printf("Kill count = %d\n", killCount);
                }
            }
            else if(bullx >= ps[4].xpos && bullx <= ps[4].xpos+10){//Kill sprite 5
                if(ps[4].active == 1){
                    killCount++;
                    ps[4].active = 0;
                    sprite_kill(&ps[4]);
                    printf("Kill count = %d\n", killCount);
                }
            }
            else if(bullx >= ps[5].xpos && bullx <= ps[5].xpos+10){//Kill sprite 6
                if(ps[5].active == 1){
                    ps[5].active = 0;
                    sprite_kill(&ps[5]);
                    killCount++;
                    printf("Kill count = %d\n", killCount);
                }
            }
            else if(bullx >= ps[6].xpos && bullx <= ps[6].xpos+10){//Kill sprite 7
                if(ps[6].active == 1){
                    ps[6].active = 0;
                    sprite_kill(&ps[6]);
                    killCount++;
                    printf("Kill count = %d\n", killCount);
                }
            }
            else if(bullx >= ps[7].xpos && bullx <= ps[7].xpos+10){//Kill sprite 8
                if(ps[7].active == 1){
                    ps[7].active = 0;
                    sprite_kill(&ps[7]);
                    killCount++;
                    printf("Kill count = %d\n", killCount);
                }
            }
        }
        wait(t);
    }
}

// setup the shooter image at location 1
int setup_shooter()
{
    lcd.cls(); //Clear the screen
    return (draw_shooter(1,0));
}

// Display the shooter at location shx the Y location (BASE) is always 24
int draw_shooter(int shx, int oldx) //shx = new position , oldx = current (old) position
{
    bm.data = shooter; // use the shooter image
    lcd.setmode(XOR); // XOR mode a second write in the same place erases the image
    if (oldx != 0){ // first time round
    lcd.print_bm(bm, oldx, BASE); // so this erases current shooter
    lcd.copy_to_lcd();
    }
    lcd.print_bm(bm, shx, BASE); // and this draws the new shooter at location shx
    lcd.copy_to_lcd(); // update lcd
    return shx; // 'current' position returned to become 'old' position
}

/* Get the new shooter X position in response to left or right
joystick movements stops at limits x = 1 and x = 112 */
int getnew_shooter(int oldx)
{
    int tmpx = oldx;
    if (joyL)
    tmpx--;
    if (tmpx <= 1)
    tmpx = 1;
    if (joyR)
    tmpx++;
    if (tmpx >= 112)
    tmpx = 112;
    return tmpx;
}

/*
This Function creates the first line of sprites then
moves the sprites down by a couple pixels each time its called.
*/
void moveSprite(){
    bm.data = ps->type; // use sprite image as defined by type

    int spriteNumber;
    if(!gameOver){
        //move sprites down after a some time
        for (spriteNumber = 0; spriteNumber <= 7; spriteNumber++) {
            //old y postion becomes new current y position. 
            ps[spriteNumber].oldy = ps[spriteNumber].ypos;
            //current y position gets new y positon which is 2 pixels down.
            ps[spriteNumber].ypos = ps[spriteNumber].ypos +2;
            //if sprite is active, sprite is printed otherwise it isnt. 
            if(ps[spriteNumber].active != 0) {
                draw_sprite(&ps[spriteNumber]);
            }
        }
    }
}


// Determine sprite 1 or 2 and display
void draw_sprite(struct sprite *ps)
{
    bm.data = ps->type; // use sprite image as defined by type
    lcd.setmode(XOR); // XOR mode a second write in the same place erases the image
    if (ps->active != 0){
        if (ps->oldy != 0){ // first time round
        lcd.print_bm(bm, ps->xpos, ps->oldy); // so this erases current sprite
        lcd.copy_to_lcd();
        }
        lcd.print_bm(bm, ps->xpos, ps->ypos); // and this draws the new sprite at location
        lcd.copy_to_lcd(); // update lcd
        return;
    } 
}

/*
This function will print another sprite in the same postion as the sprite argument therefore
removing the sprite from the screen.
*/
void sprite_kill(struct sprite *ps){
    bm.data = ps->type; // use sprite image as defined by type

    lcd.print_bm(bm, ps->xpos, ps->ypos);//prints sprite on top of sprite being killed. 
    
}

/*
This function draws the bullet and its animantion.
This print 4 pixels in a line(the bullet) then prints in the same postion to remove it then 
print the bullet 1 pixel higher.
*/
void draw_bullet()
{   
     for( int y=bully; y>=0; y--) {
        lcd.pixel(bullx, y, 1);
        lcd.pixel(bullx, y-1, 1);
        lcd.pixel(bullx, y-2, 1);
        lcd.pixel(bullx, y-3, 1);
        wait(0.015);                 
        lcd.copy_to_lcd();          
        lcd.pixel(bullx, y, 1);
        lcd.pixel(bullx, y-1, 1);
        lcd.pixel(bullx, y-2, 1);
        lcd.pixel(bullx, y-3, 1);
        }
}

void endgame( char result) // LED == GREEN for WIN
{   
        lcd.cls();
        lcd.locate(32,12);
        if(result == WIN){
        lcd.printf("YOU WIN!!!!");
        r = 1.0;
        g = 0.0;
        }
        else {
        lcd.printf("YOU LOSE! : (");
        r = 0.0;
        g = 1.0;
        while(1){}
}
}
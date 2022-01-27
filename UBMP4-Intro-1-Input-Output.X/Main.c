/*==============================================================================
 Project: Intro-1-Input-Output
 Date:    May 16, 2021
 
 This example UBMP4 input and output program demonstrates pushbutton input, LED
 (bit) output, port latch (byte) output, time delay functions, and simple 'if'
 condition structures.
 
 Additional program analysis and programming activities demonstrate byte output,
 logical condition operators AND and OR, using delay functions to create sound,
 and simulated start-stop button functionality.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions
#include    <math.h>            //ez maths
#include    "UBMP4.h"           // Include UBMP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// The main function is required, and the program begins executing from here.
void neopixel_send(unsigned char colour);
void neopixel_fill_a(unsigned char leds, unsigned char red[], unsigned char green[], unsigned char blue[]);
void neopixel_fill(unsigned char leds, unsigned char red, unsigned char green, unsigned char blue);



#define pixelLength 30
#define halfLength (pixelLength/2)
#define speed 1
#define centerPoint 127

#define LEDs 10

unsigned char red[LEDs];
unsigned char green[LEDs];
unsigned char blue[LEDs];

unsigned char redS[LEDs];
unsigned char greenS[LEDs];
unsigned char blueS[LEDs];

unsigned char sRed = 0;
unsigned char sGreen = 0;
unsigned char sBlue = 0;

unsigned char arrayLength = 4;
unsigned char indexFunction = 0;

int tick = 1;
int ticks_left = 0;
bool isPressed = false;


void pulsingRGB();



unsigned char leds;
unsigned char redArray[pixelLength+1], greenArray[pixelLength+1], blueArray[pixelLength+1];


void hsvToRGB(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char h1, unsigned char s1, unsigned char v1) {
    unsigned char region, p, q, t;
    unsigned int h, s, v, remainder;

    if (s1 == 0)
    {
        *r = v1;
        *g = v1;
        *b = v1;
    }

    // converting to 16 bit to prevent overflow
    h = h1;
    s = s1;
    v = v1;

    region = h / 43;
    remainder = (h - (region * 43)) * 6; 

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            *r = v;
            *g = t;
            *b = p;
            break;
        case 1:
            *r = q;
            *g = v;
            *b = p;
            break;
        case 2:
            *r = p;
            *g = v;
            *b = t;
            break;
        case 3:
            *r = p;
            *g = q;
            *b = v;
            break;
        case 4:
            *r = t;
            *g = p;
            *b = v;
            break;
        default:
            *r = v;
            *g = p;
            *b = q;
            break;
    }
}

unsigned char ledNum = LEDs;
bool rev = false;

void pulsingRGB() {
    for(unsigned char i = 0; i < LEDs; i++) {
        hsvToRGB(&redS[i], &greenS[i], &blueS[i], (unsigned char) (tick) + (i * 2), 255, 255);
        if(i > ledNum) {
            redS[i] = 0;
            blueS[i] = 0;
            greenS[i] = 0;
        }
    }
    if(ticks_left != 0) ticks_left--;
    tick++;
    
    if(rev) {
        ledNum++;
        if(ledNum == LEDs) rev = false;
    } else {
        ledNum--;
        if(ledNum == 0) {
            rev = true;
        }
        neopixel_fill_a(LEDs, redS, greenS, blueS);
    }
    neopixel_fill_a(LEDs, redS, greenS, blueS);
    __delay_ms(15);
}

unsigned int soundV2;
unsigned int soundMemory;
unsigned int sound;
int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
    ADC_config();
    ADC_select_channel(ANH1);
    __delay_ms(100);
    // Code in this while loop runs repeatedly.
    int led = 5;
    int brightness = 255;
    while(1)
	{

        sound = ADC_read();
        soundV2 = soundMemory - centerPoint;
        if (sound > 200 || sound < 200) {
            
            soundMemory = sound;
            
        }
        if (soundMemory > 200 || soundMemory < 200) {
            LED4 = 1;
        } else {
            LED4 = 0;
        }
        
        if (sound > -130) {
            LED3 = 1;
        } else {
            LED3 = 0;
        }
        

        
        
        
//        int prevNum = halfLength;
//        int leftNum = halfLength-1; 
//        int prevLeftNum = halfLength;
//        // If SW2 is pressed, make a flashy light pattern
//
//        for (int i = halfLength+1; i <= (pixelLength); i++) {
//            for (int ii = 0; ii < 255-(255%speed); ii++) {
//                
//                redArray[i]+=speed;
//                redArray[leftNum]+=speed;
//                redArray[prevNum]-=speed;
//                
//                if (prevLeftNum != halfLength) { 
//                    redArray[prevLeftNum]-=speed;
//                }
//                neopixel_fill_a(pixelLength, redArray, greenArray, blueArray);
//                
//                __delay_us(200);
//            }
//            prevLeftNum = leftNum;
//            leftNum--;
//            prevNum = i;
//            
//        }
//        leftNum = 0;
//        prevLeftNum = -1;
//        for (int i3 = pixelLength; i3 >= halfLength+1; i3--) {
//            for (int i4 = 0; i4 < 255-(255%speed); i4++) {
//                
//                redArray[i3]+=speed;
//                //if (leftNum != halfLength) {
//                    redArray[leftNum]+=speed;
//                //}
//                redArray[prevNum]-=speed;
//
//                if (prevLeftNum != halfLength) {
//                    
//                    redArray[prevLeftNum]-=speed;
//                }
//                neopixel_fill_a(pixelLength, redArray, greenArray, blueArray);
//                
//                __delay_us(200);
//            }
//            prevLeftNum = leftNum;
//            leftNum++;
//            prevNum = i3;
//            
//        }
        

        // Add code for your Program Analysis and Programming Activities here:

        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
        
        
    }
}

void neopixel_fill_a(unsigned char leds, unsigned char red[], unsigned char green[], unsigned char blue[]) {
    int ledNum = 0;
    for(; ledNum != leds; ledNum++) {
        neopixel_send(green[ledNum]);
        neopixel_send(red[ledNum]);
        neopixel_send(blue[ledNum]);
    }
}

//void neopixel_fill(unsigned char leds, unsigned char red, unsigned char green, unsigned char blue) {
//    for (; leds != 0; leds--) {
//        neopixel_send(green);
//        neopixel_send(red);
//        neopixel_send(blue);
//    }
//    
//}

void neopixel_send(unsigned char colour)
{
    for(unsigned char bits = 8; bits != 0; bits --)
    {
        H2OUT = 1;
        if((colour & 0b10000000) == 0)
        {
            H2OUT = 0;
        }
        NOP();
        H2OUT = 0;
        colour = colour << 1;
    }
}

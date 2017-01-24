#ifndef _CONSTANTS_h
#define _CONSTANTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//=====================================================
// Pins
//-----------------------------------------------------

// The pin of the first strip
#define PIN_STRIP_1			12

// The pin of the second strip
#define PIN_STRIP_2			11

// The photo resistor pin
#define PIN_PHOTO_RESISTOR	A5


//=====================================================
//  LCD Touchscreen information
//-----------------------------------------------------
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin


// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


// Color definitions
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

/******************* UI details */
#define BUTTON_X 120
#define BUTTON_Y 40
#define BUTTON_W_SM 60
#define BUTTON_H_SM 30
#define BUTTON_W_LG 210
#define BUTTON_H_LG 60
#define BUTTON_SPACING_X 10
#define BUTTON_SPACING_Y 20
#define BUTTON_TEXTSIZE_SM 2
#define BUTTON_TEXTSIZE_LG 3


#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin


//Touch For New ILI9341 TP
#define TS_MINX 120
#define TS_MAXX 900

#define TS_MINY 70
#define TS_MAXY 920

#define MINPRESSURE 10
#define MAXPRESSURE 1000


//=====================================================
// LED information
//-----------------------------------------------------

// The number of LED modules (of 9 LEDs each) on strip 1
#define STRIP_1_MODULE_COUNT	2

// The number of LED modules (of 9 LEDs each) on strip 2
#define STRIP_2_MODULE_COUNT	3

// This is the maximum allowed brightness
#define LEDS_MAX_BRIGHTNESS		164 //128



//=====================================================
// Ambient light
//-----------------------------------------------------

// The threshold between dark and twilight (below = dark, above = twilight)
#define TWILIGHT_LOW			630

// The threshold between light and twilight (below = twilight, above = light)
#define TWILIGHT_HIGH			800




//=====================================================
// Calculated constants
//
// Math magic explained: "<< 2" is the same thing as "times 4", but quicker and easier for the Arduino.
//-----------------------------------------------------

// The total number of LED modules
#define MODULE_COUNT			STRIP_1_MODULE_COUNT + STRIP_2_MODULE_COUNT

// The number of individual LEDs on strip 1
#define LEDS_STRIP_1			STRIP_1_MODULE_COUNT *9 //<< 2

// The number of individual LEDs on strip 2
#define LEDS_STRIP_2			STRIP_2_MODULE_COUNT * 9 //<< 2

// The total number of individual LEDs
#define TOTAL_LED_COUNT			(STRIP_1_MODULE_COUNT + STRIP_2_MODULE_COUNT) * 9 //<< 2



#endif


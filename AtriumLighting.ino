#include "Constants.h"
#include "AmbientLight.h"
#include "TwoStripManager.h"
#include "StripBrightnessManager.h"

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#include "Effect.h"
#include "FireEffect.h"
#include "ChristmasEffect.h"


// The set of available effects:
FireEffect _fireEffect;
//ChristmasEffect _christmasEffect;

// The current effect:
Effect *_currentEffect;

// Strip and brightness managers:
StripManager *_stripManager = new TwoStripManager();
AmbientLight *_ambientLight = new AmbientLight(PIN_PHOTO_RESISTOR, TWILIGHT_LOW, TWILIGHT_HIGH);
StripBrightnessManager *_stripBrightnessManager = new StripBrightnessManager(_stripManager, _ambientLight);


Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button buttons[4];


void setup()
{
	Serial.begin(9600);
	Serial.println("Starting...");

	// Hardcoded effect selection (to be replaced with some kind of manual selection)
	_currentEffect = &_fireEffect;
	//_currentEffect = &_christmasEffect;


  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(2);
  tft.fillScreen(BLACK);
  
  // create buttons
  buttons[0].initButton(&tft, BUTTON_X, BUTTON_Y, BUTTON_W_LG, BUTTON_H_LG, ILI9341_WHITE, ILI9341_DARKGREEN, ILI9341_WHITE, "On", BUTTON_TEXTSIZE_LG); 
  buttons[0].drawButton();
  buttons[1].initButton(&tft, BUTTON_X, BUTTON_Y + BUTTON_H_LG + BUTTON_SPACING_Y, BUTTON_W_LG, BUTTON_H_LG, ILI9341_WHITE, ILI9341_LIGHTGREY, ILI9341_WHITE,"Off", BUTTON_TEXTSIZE_LG);
  buttons[1].drawButton();

  buttons[2].initButton(&tft, BUTTON_X, BUTTON_Y + BUTTON_H_LG * 2 + BUTTON_SPACING_Y * 2, BUTTON_W_LG, BUTTON_H_LG, ILI9341_WHITE, ILI9341_ORANGE, ILI9341_WHITE,"Candle", BUTTON_TEXTSIZE_LG);
  buttons[2].drawButton();
  buttons[3].initButton(&tft, BUTTON_X, BUTTON_Y + BUTTON_H_LG * 3 + BUTTON_SPACING_Y * 3, BUTTON_W_LG, BUTTON_H_LG, ILI9341_WHITE, ILI9341_RED, ILI9341_WHITE,"XMas", BUTTON_TEXTSIZE_LG);
  buttons[3].drawButton();
  
	_stripManager->Init();
	_stripBrightnessManager->Init();
}

void loop()
{

////////////////////////////////////////////////
//
//       Touch sensing
//
////////////////////////////////////////////////
 
  /*
  TSPoint p;
  p = ts.getPoint(); 
  */
  
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  
  // p = ts.getPoint(); 
  /*
  if (ts.bufferSize()) {
    
  } else {
    // this is our way of tracking touch 'release'!
    p.x = p.y = p.z = -1;
  }*/
  
  // Scale from ~0->4000 to tft.width using the calibration #'s
  /*
  if (p.z != -1) {
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    Serial.print("("); Serial.print(p.x); Serial.print(", "); 
    Serial.print(p.y); Serial.print(", "); 
    Serial.print(p.z); Serial.println(") ");
  }*/
   if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // scale from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
    Serial.print("X: ");Serial.print(p.x);Serial.print(" Y: ");Serial.println(p.y);
   }
   
  // go thru all the buttons, checking if they were pressed
  for (uint8_t b=0; b<4; b++) {
    if (buttons[b].contains(p.x, p.y)) {
      Serial.print("Pressing: "); Serial.println(b);
      buttons[b].press(true);  // tell the button it is pressed
      //buttons[b].drawButton(true);  // draw invert!
    } else {
      //Serial.print("Not Pressing: "); Serial.println(b);
      buttons[b].press(false);  // tell the button it is NOT pressed
      //buttons[b].drawButton(false);  // draw invert!
    }
  }

  // now we can ask the buttons if their state has changed
  for (uint8_t b=0; b<4; b++) {
    if (buttons[b].justReleased()) {
       //Serial.print("Released: "); Serial.println(b);
      buttons[b].drawButton();  // draw normal
    }

    if (buttons[b].justPressed()) {
        buttons[b].drawButton(true);  // draw invert!
        if (buttons[0].justPressed()) Serial.println("Turned on");
        if (buttons[1].justPressed()) Serial.println("Turned off");
        if (buttons[2].justPressed()) Serial.println("Candle effect");
        if (buttons[3].justPressed()) Serial.println("Christmas effect");

    }
  }

 delay(100);

  ///////////////////////////////////////
  //
  //    Update Lights
  //
  ///////////////////////////////////////
	if (!_stripBrightnessManager->Update())
	{
		// The strip is OFF.
		return;
	}

	_currentEffect->Update();

	_stripManager->ApplyEffect(_currentEffect);

}

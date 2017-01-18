#include "Constants.h"
#include "AmbientLight.h"
#include "TwoStripManager.h"
#include "StripBrightnessManager.h"

//#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_TFTLCD.h> // Hardware-specific library
//#include <TouchScreen.h>

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

/*
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button buttons[15];
char buttonlabels[7][17] = {"On", "Off", "Candle", "XMas", "Brighter", "Dimmer", "Use light sensor"};
uint16_t buttoncolors[7] = {ILI9341_DARKGREEN, ILI9341_DARKGREY, ILI9341_ORANGE, 
                             ILI9341_RED, ILI9341_BLUE, ILI9341_BLUE, 
                             ILI9341_BLUE};
*/

void setup()
{
	Serial.begin(9600);
	Serial.println("Starting...");

	// Hardcoded effect selection (to be replaced with some kind of manual selection)
	_currentEffect = &_fireEffect;
	//_currentEffect = &_christmasEffect;

/*
  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(2);
  tft.fillScreen(BLACK);
  
  // create buttons
  for (uint8_t row=0; row<3; row++) {
    for (uint8_t col=0; col<3; col++) {
      buttons[col + row*3].initButton(&tft, BUTTON_X+col*(BUTTON_W+BUTTON_SPACING_X), 
                 BUTTON_Y+row*(BUTTON_H+BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  BUTTON_W, BUTTON_H, ILI9341_WHITE, buttoncolors[col+row*3], ILI9341_WHITE,
                  buttonlabels[col + row*3], BUTTON_TEXTSIZE); 
      buttons[col + row*3].drawButton();
    }
  }
*/  
	_stripManager->Init();
	_stripBrightnessManager->Init();
}

void loop()
{
	if (!_stripBrightnessManager->Update())
	{
		// The strip is OFF.
		return;
	}

	_currentEffect->Update();

	_stripManager->ApplyEffect(_currentEffect);
}

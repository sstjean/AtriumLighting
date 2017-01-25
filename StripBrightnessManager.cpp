#include "StripBrightnessManager.h"
#include "StripManager.h"
#include "AmbientLight.h"


StripBrightnessManager::StripBrightnessManager(StripManager *stripManager, AmbientLight *ambientLight)
{
	_stripManager = stripManager;
	_ambientLight = ambientLight;
}

void StripBrightnessManager::Init()
{
	_currentBrightness = 0;
  EnableLightSensor();
	_stripManager->SetBrightness(_currentBrightness);
}

void StripBrightnessManager::EnableLightSensor(){
  _useLightSensor = true;
  //Serial.println("Using light sensor: ");
  return;
}

void StripBrightnessManager::DisableLightSensor(){
  _useLightSensor = false;
  //Serial.println("Not using light sensor: ");
  return;
}

int StripBrightnessManager::GetBrightness()
{
  return _currentBrightness;
}

bool StripBrightnessManager::Update()
{  
  AmbientLightState ambientLightState;
  
	if (_useLightSensor){
  
		_ambientLight->Update();

	  ambientLightState = _ambientLight->GetState();
    
	} else {
    //SSJ - Force to full brightness.  Do not fade in.
    ambientLightState = Dark;
	}
 
	switch (ambientLightState)
	{
	case Light:
	case Unknown:
	{
		if (_currentBrightness != 0)
		{
			_currentBrightness = 0;
			_stripManager->SetBrightness(_currentBrightness);
		}
		return false; // Return FALSE to indicate that the strip should be off.
	}

	case Dark:
	{
		if (_currentBrightness != LEDS_MAX_BRIGHTNESS)
		{
			_currentBrightness = LEDS_MAX_BRIGHTNESS;
			_stripManager->SetBrightness(_currentBrightness);
		}
		break;
	}

	case Twilight:
	{
		uint8_t brightness = LEDS_MAX_BRIGHTNESS * (1 - _ambientLight->GetTwilightFactor());
		if (_currentBrightness != brightness)
		{
			_currentBrightness = brightness;
			_stripManager->SetBrightness(_currentBrightness);
		}
		break;
	}

	default:
		break;
	}

	return true; // Return TRUE to indicate that the strip is active.
}


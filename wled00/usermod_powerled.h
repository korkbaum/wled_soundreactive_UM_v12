/*
This user mode uses several parts of usermod_touchbrightness.h by Justin Kühner https://github.com/NeariX67 
On short touch event the RGB Leds will toggle on/off.
On Long touch event the PowerLed toggles power on/off.
*/

#pragma once

#include "wled.h"

#ifdef ESP32		//won't run on ESP8266

#define TOUCHCONTROL_ENABLED 1    // turn touch control on or off (unelegantly)
#define TOUCH_DEBUG 0             // enable serial output to check touch threshold value

//this is to run analogwrite style pwm dimming on esp32
#define LEDC_CHANNEL_0     0
#define LEDC_TIMER_13_BIT  13
#define LEDC_BASE_FREQ     5000

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);   // calculate duty, 8191 from 2 ^ 13 - 1
  ledcWrite(channel, duty);
}


class usermod_powerled : public Usermod {
	
  private:
	  unsigned long lastTime = 0;           //Interval
    unsigned long lastTouch = 0;        //Timestamp of last Touch
    unsigned long lastRelease = 0;      //Timestamp of last Touch release
    boolean released = true;            //current Touch state (touched/released)
    uint16_t touchReading = 0;          //sensor reading
    uint16_t touchDuration = 0;         //duration of last touch
    uint16_t touchreading_old = 0;      //to compare last value and current value

    int my_touchpin;                    //variables read from /cfg
    int my_threshold;                   //KK: MagicReel: 12,  CubeBall: 9, def 60, MicroCube: 3
	
  public:

    // some variables for Power Led control
    bool PWRon = 0;
    bool PWRonLast = 0;
    uint8_t PWRbri = 16;
    uint8_t PWRbriLast = 0;

    void setup() {
      lastTouch = millis();
      lastRelease = millis();
      lastTime = millis();
      PWRon = 0;
      //PWRbri = 0;
		  
  		//for pwm dimming pwr led, no "analogwrite" function on esp32 like on ESP8266
  		ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  		ledcAttachPin(PWRLedPin, LEDC_CHANNEL_0);			
    }

    void connected() {
    }

    void loop() {
		
        if (TOUCHCONTROL_ENABLED) {
          if (millis() - lastTime >= 50) {                          //Check every 50ms if a touch occurs
            lastTime = millis();
            touchReading = touchRead(my_touchpin);                    //Read touch sensor 
            if (TOUCH_DEBUG) Serial.println(touchReading);

            if(touchReading < my_threshold && released) {              //touch started
              released = false;
              lastTouch = millis();
            }
            else if (touchReading >= my_threshold && !released) {      //Touch released
              released = true;
              lastRelease = millis();
              touchDuration = lastRelease - lastTouch;              //Calculate duration
            }
    
            if(touchDuration >= 500 && released) {                   //800 Toggle power if button press is longer than 800ms
              touchDuration = 0;                                     //Reset touch duration to avoid multiple actions on same touch
              PWRon = !PWRon;
              PWRtoggleOnOff();
              if (TOUCH_DEBUG) Serial.println("PWRtoggle");
            } 
            else if (touchDuration >= 150 && released) {             //100 Switch to next brightness if touch is between 100 and 800ms
              touchDuration = 0;                                     //Reset touch duration to avoid multiple actions on same touch
              toggleOnOff();
              colorUpdated(NOTIFIER_CALL_MODE_DIRECT_CHANGE);
              updateInterfaces(NOTIFIER_CALL_MODE_DIRECT_CHANGE);                                    
              if (TOUCH_DEBUG) Serial.println("toggle");
            }
          }
        }
		
    		if (PWRbri != PWRbriLast) {                             //change pwr led brightness if it was changed in GUI
          if (!PWRon) PWRon = 1;
    			ledcAnalogWrite(LEDC_CHANNEL_0, PWRbri);
    			PWRbriLast = PWRbri;
          colorUpdated(NOTIFIER_CALL_MODE_DIRECT_CHANGE);
          updateInterfaces(NOTIFIER_CALL_MODE_DIRECT_CHANGE);
    		}
    
    		if (PWRon != PWRonLast) {                               //change pwr on/off state if it was changed in GUI
          PWRtoggleOnOff();
    		}		

    } // loop end


  	void PWRtoggleOnOff() { 
      if (PWRon) {
        PWRbri = PWRbriLast;
        ledcAnalogWrite(LEDC_CHANNEL_0, PWRbri);
      }
      else {
        ledcAnalogWrite(LEDC_CHANNEL_0, 0);
      }
      PWRonLast = PWRon;
      colorUpdated(NOTIFIER_CALL_MODE_DIRECT_CHANGE);
      updateInterfaces(NOTIFIER_CALL_MODE_DIRECT_CHANGE);
  	}

    void addToJsonState(JsonObject& root){
  		root["PWRon"] = PWRon;
  		root["PWRbri"] = PWRbri;
    }

    void readFromJsonState(JsonObject& root){
  		PWRbri = root["PWRbri"] | PWRbri;
      userVar0 = PWRbri;
  		PWRon = root["PWRon"] | PWRon;
      userVar1 = PWRon;
    }

    void addToConfig(JsonObject& root){
  		JsonObject top = root.createNestedObject("usermod_powerled");
      top["PWRbri"] = PWRbri;
      userVar0 = PWRbri;
  		top["PWRon"] = PWRon;	
      userVar1 = PWRon;

      if (TOUCHCONTROL_ENABLED) {
        JsonObject top = root.createNestedObject("pwrtouch");
        top["tpin"] = my_touchpin;
        top["thre"] = my_threshold;
      }
    }

    void readFromConfig(JsonObject& root){
  		JsonObject top = root["usermod_powerled"];
      PWRbri = top["PWRbri"] | userVar0;
  		PWRon  = top["PWRon"] | userVar1;

      if (TOUCHCONTROL_ENABLED) {
        JsonObject top = root["pwrtouch"];
        my_touchpin = top["tpin"] | 15;   // Touchpin T3 = GPIO 15 / default
        my_threshold = top["thre"] | 20;  // threshold
      }
    }
    
    uint16_t getId(){
      return USERMOD_ID_POWERLED;
    }
    
};
#endif

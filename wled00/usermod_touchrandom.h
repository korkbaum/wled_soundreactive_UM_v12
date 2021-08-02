/*********************************
This user mode is based on usermod_touchbrightness.h by Justin Kühner https://github.com/NeariX67 
On short touch event the effect + palette will change randomly within the currently active ones (as defined in usermod_fxpalselection.h).
Long touch toggles power on/off.
**********************************/

#pragma once

#include "wled.h"

#define threshold 3       //KK: MagicReel: 12,  CubeBall: 9, def 60, MicroCube: 3
#define TOUCH_PIN T3

class usermod_touchrandom : public Usermod {
	
  private:
    int fx_active[MODE_COUNT];
    int fx_active_count = 0;
    int pal_active[GRADIENT_PALETTE_COUNT];
    int pal_active_count = 0;
	  
    unsigned long lastTime = 0;         //Interval
    unsigned long lastTouch = 0;        //Timestamp of last Touch
    unsigned long lastRelease = 0;      //Timestamp of last Touch release
    boolean released = true;            //current Touch state (touched/released)
    uint16_t touchReading = 0;          //sensor reading
    uint16_t touchDuration = 0;         //duration of last touch
    uint16_t touchreading_old = 0;      //to compare last value and current value
	
  public:

    void setup() {
      lastTouch = millis();
      lastRelease = millis();
      lastTime = millis();

      //identify activated effects, assign to array to get valid values for random selection in loop
      for (int i = 1; i < MODE_COUNT; i++) {
        if (fxsel_active[i]) {
          fx_active[fx_active_count] = i;
          fx_active_count++;
        }
      }
      
      //identify activated palettes, assign to array to get valid values for random selection in loop
      for (int i = 1; i < GRADIENT_PALETTE_COUNT; i++) {
        if (palsel_active[i]) {
          pal_active[pal_active_count] = i;
          pal_active_count++;
        }
      }

    }

    void connected() {
    }

    void loop() {
		
        if (millis() - lastTime >= 50) {                          //Check every 50ms if a touch occurs
          lastTime = millis();
          touchReading = touchRead(TOUCH_PIN);                    //Read touch sensor 
          //Serial.println(touchReading);

          if(touchReading < threshold && released) {              //touch started
            released = false;
            lastTouch = millis();
          }
          else if (touchReading >= threshold && !released) {      //Touch released
            released = true;
            lastRelease = millis();
            touchDuration = lastRelease - lastTouch;              //Calculate duration
          }
  
          if(touchDuration >= 500 && released) {                   //800 Toggle power if button press is longer than 800ms
            touchDuration = 0;                                     //Reset touch duration to avoid multiple actions on same touch
            toggleOnOff();
            colorUpdated(NOTIFIER_CALL_MODE_DIRECT_CHANGE);
            updateInterfaces(NOTIFIER_CALL_MODE_DIRECT_CHANGE);
            //Serial.println("toggle on/off");
          } 
          else if (touchDuration >= 100 && released) {             //100 trigger random effect & palette
            touchDuration = 0;                                     //Reset touch duration to avoid multiple actions on same touch
            
            int eff_index = random(1, fx_active_count);            //random effect, leave solid out
            effectCurrent = fx_active[eff_index];
            
            int pal_index = random(0, pal_active_count);           //random palette
            effectPalette = pal_active[pal_index];
            
            colorUpdated(NOTIFIER_CALL_MODE_DIRECT_CHANGE);
            updateInterfaces(NOTIFIER_CALL_MODE_DIRECT_CHANGE);                                    
            //Serial.printf("%s%i%s%i", "\neffect: ", fx_active[eff_index], " palette: ", pal_active[pal_index]);
          }
        }

    } // loop end
    
    uint16_t getId(){
      return USERMOD_ID_TOUCHRANDOM;
    }
};
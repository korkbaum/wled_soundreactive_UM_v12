/*********************************
This user mode is based on usermod_touchbrightness.h by Justin Kühner https://github.com/NeariX67 
On short touch event the effect + palette will change randomly within the currently active ones (as defined in usermod_fxpalselection.h).
Long touch toggles power on/off.
**********************************/

#pragma once

#include "wled.h"

#define TOUCHRANDOM_DEBUG 0             // enable serial output to check touch threshold value

#ifndef USERMOD_ID_POWERLED
  #define POWERLED 0
#else
  #define POWERLED 1
#endif


class usermod_touchrandom : public Usermod {
	
  private:
      /* TO DO: relocate to usermod_fxpal_selection*/
    int fx_active[MODE_COUNT];
    int fx_active_count = 0;
    int pal_active[PAL_COUNT];
    int pal_active_count = 0;

    int my_touchpin;                    //variables read from /cfg
    int my_threshold;                   //KK: MagicReel: 12,  CubeBall: 9, def 60, MicroCube: 3
	  
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
      /* TO DO: relocate to usermod_fxpal_selection*/
      for (int i = 1; i < MODE_COUNT; i++) {
        if (fxsel_active[i]) {
          fx_active[fx_active_count] = i;
          fx_active_count++;
          if (TOUCHRANDOM_DEBUG) Serial.printf("%s %d %d\n", "FX: ", fx_active_count, fx_active[fx_active_count]);
        }
      }
      
      //identify activated palettes, assign to array to get valid values for random selection in loop
      for (int i = 1; i < PAL_COUNT; i++) {
        if (palsel_active[i]) {
          pal_active[pal_active_count] = i;
          pal_active_count++;
          if (TOUCHRANDOM_DEBUG) Serial.printf("%s %d %d\n","PAL: ", pal_active_count, pal_active[pal_active_count]);
        }
      }

    }

    void connected() {
    }

    void loop() {
		
        if (millis() - lastTime >= 50) {                         // Check every 50ms if a touch occurs
          lastTime = millis();
          touchReading = touchRead(my_touchpin);                 // Read touch sensor 
          if (TOUCHRANDOM_DEBUG) Serial.println(touchReading);

          if(touchReading <= my_threshold && released) {         //touch started
            released = false;
            lastTouch = millis();
          }
          else if (touchReading > my_threshold && !released) {    //Touch released
            released = true;
            lastRelease = millis();
            touchDuration = lastRelease - lastTouch;              //Calculate duration
          }
  
          if ( !(POWERLED) && (touchDuration >= 500 && released) ) {    //500ms Toggle power if button press is longer than 800ms
                                                                                  // USERMOD_ID_POWERLED also triggers power on/off, if both are used, don't introduce overlapping touch fuctions
            touchDuration = 0;                                     //Reset touch duration to avoid multiple actions on same touch
            toggleOnOff();
            colorUpdated(NOTIFIER_CALL_MODE_DIRECT_CHANGE);
            updateInterfaces(NOTIFIER_CALL_MODE_DIRECT_CHANGE);
            if (TOUCHRANDOM_DEBUG) Serial.println("toggle on/off");
          } 
          else if (touchDuration >= 150 && released) {             //150ms trigger random effect & palette
            touchDuration = 0;                                     //Reset touch duration to avoid multiple actions on same touch
            
            int eff_index = random(0, fx_active_count);            //random effect from active fx array
            effectCurrent = fx_active[eff_index];
            
            int pal_index = random(0, pal_active_count);           //random palette from active pal array
            effectPalette = pal_active[pal_index];
            
            colorUpdated(NOTIFIER_CALL_MODE_DIRECT_CHANGE);
            updateInterfaces(NOTIFIER_CALL_MODE_DIRECT_CHANGE);                                    
            if (TOUCHRANDOM_DEBUG) Serial.printf("%s%i%s%i", "\neffect: ", fx_active[eff_index], " palette: ", pal_active[pal_index]);
          }
        }

    } // loop end

    void addToConfig(JsonObject& root) {
      JsonObject top = root.createNestedObject("touchrandom");
      top["tpin"] = my_touchpin;
      top["thre"] = my_threshold;
    }

    void readFromConfig(JsonObject& root) {
      JsonObject top = root["touchrandom"];
      my_touchpin = top["tpin"] | 13;   // Touchpin T4 = GPIO 13 = default
      my_threshold = top["thre"] | 20;  // threshold 
    }

    uint16_t getId(){
      return USERMOD_ID_TOUCHRANDOM;
    }
}; 
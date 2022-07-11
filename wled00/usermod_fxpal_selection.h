// prepare a bunch of json keys + values to mark effectcs and palettes as active or not (true/false).
// activation/deactivation is done with checkboxes in settings_LEDS.htm
// selected config is stored in littleFS /cfg file. 
// korkbaum Updated June 2022

#pragma once

#include "wled.h"

#define PAL_COUNT GRADIENT_PALETTE_COUNT + 13     // ugly, should be strip.getPaletteCount() from FX_fcn.cpp

class usermod_fxpal_selection : public Usermod {
	
  private:
    int fx_active[MODE_COUNT];
    int fx_active_count = 0;
    int pal_active[PAL_COUNT];
    int pal_active_count = 0;
    
  public:
    void setup() {
      //identify activated effects, assign to array
      for (int i = 1; i < MODE_COUNT; i++) {
        if (fxsel_active[i]) {
          fx_active[fx_active_count] = i;
          fx_active_count++;
        }
      }
      
      //identify activated palettes, assign to array 
      for (int i = 1; i < PAL_COUNT; i++) {
        if (palsel_active[i]) {
          pal_active[pal_active_count] = i;
          pal_active_count++;
        }
      }
    }

    void connected() {
    }

    void loop() {
		} 

    void addToConfig(JsonObject& root){
  		JsonObject top = root.createNestedObject("usermod_fxpal_selection");
       
      char indx[12];

      for (int i = 1; i < MODE_COUNT; i++) {                        //prepare fx selection keys
        indx[0] = '\0';
        sprintf(indx, "%s%d", "fxc", i);
        top[indx] = fxsel_active[i];
      }

      for (int i = 1; i < PAL_COUNT; i++) {            //prepare pal selection keys
        indx[0] = '\0';  
        sprintf(indx, "%s%d", "palc", i);
        top[indx] = palsel_active[i];
      }
    }

    void readFromConfig(JsonObject& root){                        
      JsonObject top = root["usermod_fxpal_selection"];

      char indx[12];
      for (int i = 1; i < MODE_COUNT; i++) {                        //read current fx selection values
        indx[0] = '\0';
        sprintf(indx, "%s%d", "fxc", i);
        fxsel_active[i] = top[indx] | true;
      }

      for (int i = 1; i < PAL_COUNT; i++) {            //read current pal selection values
        indx[0] = '\0';  
        sprintf(indx, "%s%d", "palc", i);
        palsel_active[i] = top[indx] | true;
      }
    }

    uint16_t getId(){
      return USERMOD_ID_FXPAL_SELECTION;
    }
};


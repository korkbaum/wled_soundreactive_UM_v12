#pragma once

#include "wled.h"

class usermod_fxpal_selection : public Usermod {
	
  private:
	
  public:
   
    void setup() {
    }

    void connected() {
    }

    void loop() {
		} 

    void addToConfig(JsonObject& root){
  		JsonObject top = root.createNestedObject("usermod_fxpal_selection");
       
      char indx[12];
      int fx_check = 0;
      int pal_check = 0;

      for (int i = 1; i < MODE_COUNT; i++) {                        //prepare fx selection keys
        indx[0] = '\0';
        sprintf(indx, "%s%d", "fxc", i);
        top[indx] = fxsel_active[i];
        if (fxsel_active[i]) fx_check++;
      }

      if (fx_check == 0) {                                            // no effect selected at all (likely first run) --> activate all effects
        for (int i = 1; i < MODE_COUNT; i++) {
          indx[0] = '\0';
          sprintf(indx, "%s%d", "fxc", i);
          top[indx] = true;
        }
      }
      
      for (int i = 1; i < GRADIENT_PALETTE_COUNT; i++) {            //prepare pal selection keys
        indx[0] = '\0';  
        sprintf(indx, "%s%d", "palc", i);
        top[indx] = palsel_active[i];
        if (palsel_active[i]) pal_check++;
      }
      
      if (pal_check == 0) {                                         // no palette selected at all (likely first run) --> activate all palettes
        for (int i = 1; i < GRADIENT_PALETTE_COUNT; i++) {
          indx[0] = '\0';
          sprintf(indx, "%s%d", "palc", i);
          top[indx] = true;
        }
      }
    }

    void readFromConfig(JsonObject& root){                        
      JsonObject top = root["usermod_fxpal_selection"];

      char indx[12];
      for (int i = 1; i < MODE_COUNT; i++) {                        //read current fx selection values
        indx[0] = '\0';
        sprintf(indx, "%s%d", "fxc", i);
        fxsel_active[i] = top[indx];
      }

      for (int i = 1; i < GRADIENT_PALETTE_COUNT; i++) {            //read current pal selection values
        indx[0] = '\0';  
        sprintf(indx, "%s%d", "palc", i);
        palsel_active[i] = top[indx];
      }
    }

    uint16_t getId(){
      return USERMOD_ID_FXPAL_SELECTION;
    }
};


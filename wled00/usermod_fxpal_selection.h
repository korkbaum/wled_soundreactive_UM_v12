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
       //fx selections
      char indx[12];
      for (int i = 1; i < strip.getModeCount(); i++) {
        indx[0] = '\0';
        sprintf(indx, "%s%d", "fxc", i);
        top[indx] = fxsel_active[i];
      }
      
      //pal selections
      for (int i = 1; i < strip.getPaletteCount(); i++) {
        indx[0] = '\0';  
        sprintf(indx, "%s%d", "palc", i);
        top[indx] = palsel_active[i];
      }
      //Serial.println("addtoconfig fx pal ready.");
    }

    void readFromConfig(JsonObject& root){
      JsonObject top = root["usermod_fxpal_selection"];
      //fx selection values
      char indx[12];
      for (int i = 1; i < strip.getModeCount(); i++) {
        indx[0] = '\0';
        sprintf(indx, "%s%d", "fxc", i);
        fxsel_active[i] = top[indx];
      }

      //pal selection values
      for (int i = 1; i < strip.getPaletteCount(); i++) {
        indx[0] = '\0';  
        sprintf(indx, "%s%d", "palc", i);
        palsel_active[i] = top[indx];
      }
      //Serial.println("readfromconfig fx pal ready.");
    }

    uint16_t getId(){
      return USERMOD_ID_FXPAL_SELECTION;
    }
};


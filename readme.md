Yet another fork of the awesome Aircoookie WLED project, or well, the awesome soundreactive branch by atuline.

My motivation for applying changes:
I built a few lamps with Power LEDs in addition to the RGB LEDs. So I wanted to integrate separate power & brightness controls for those. After that was done, I personally found that the UI is subject to some improvements. 

Main points:
Changing between Solid Color and Effects is -from my point of view- counter-intuitive because you may not just tab on the color wheel but instead you will have to activate Solid Color first on the Effect tab. Now, the Solid Color and the effects tabs are united.

The next thing to change was the FX/Palette selection approach. It requires a lot of scrolling already; adding even more buttons for effects and palettes in the future is going to worsen this. Searching for effect names is not very convenient either. 
Two measures were found to make it more convenient: 
Firstly, the usage of drop-downs and secondly a Pre-Selection of effects & palettes which I added in LED settings. 

<h2>Overview of changes:<br></h2>
1: Changes in Top Navigation Bar:<br>
--	Buttons removed: <br>
-------	Nightlight: Honestly, I find it obsolete<br>
-------	Info: I moved this to the bottom as a vertical button, it shows the wled name as text and the connection indicator is „integrated“.<br>
-------	(Toggle) PC Mode: not required any more<br>
--	Buttons added: <br>
-------	„Room“ Power (for PowerLed)<br>
-------	Segments: This should ideally also go to the LED settings (who needs to change the segments all the time?) but it was hard to move it (too hard for me, at least)<br>
--	Buttons changed: <br>
-------	Power „Mood“: Only changed the icon and renamed it, this is the RGB LED Power button<br>
-------	Additional Brightness Slider for PowerLED<br>
-------	Slider Icons changed<br>
<br>
2: Changes in Bottom Tab Bar:<br>
-------	The Bottom Tab Bar was eliminated; Colors and Effects Pages are now consolidated<br>
-------	Segments Tab was moved as button in Top Bar<br>
-------	Favorites Tab now shown in consolidated Tab as "Presets"; i.e. the Label became a button<br>
<br>
3: Changes in Colors & Effects:<br>
------- Color Wheel is changing to Solid Color Effect when clicked<br>
------- Effects Controls are only shown if an effect is active other than solid color<br>
-------	Effect selection has been modeled as dropdown<br>
-------	Palette selection has been modeled as dropdown<br>
------- Sliders beneath color wheel have been removed (Honestly, I never used them and found them obsolete)<br>
-------	Color Selectors 1,2,3 have been removedo	(Honestly, I never used them and found them obsolete as well)<br>
<br>
4: Changes in Settings:<br>
------- Overview page has much smaller buttons & hover effect<br>
-------	Effect and Palette pre-selection were integrated into LED Settings page<br>
<br>
I'm really keen to get any feedback on all these changes!
<br>
<p align="center">Original V12 UI:<br>
<img src="https://github.com/korkbaum/WLED/blob/wled_V12_kk2/images/v12orig.png"></p>

<br>
<p align="center">Modified V12 UI. No effect controls because no effect is active.<br>
<img src="https://github.com/korkbaum/WLED/blob/wled_V12_kk2/images/V12_modified1.png"></p>
<br>
<p align="center">Modified V12 UI. Only the pre-selected effects are shown in a dropdown.<br>
<img src="https://github.com/korkbaum/WLED/blob/wled_V12_kk2/images/V12_modified2.png"></p>
<br>
<p align="center">Modified V12 UI. Effect is active, effect controls are now shown.<br>
<img src="https://github.com/korkbaum/WLED/blob/wled_V12_kk2/images/V12_modified4.png"></p>
<br>
<p align="center">Modified V12 UI. Settings page with smaller buttons.<br>
<img src="https://github.com/korkbaum/WLED/blob/wled_V12_kk2/images/V12_modified5.png"></p>
<br>
<p align="center">Modified V12 UI. New Effects Selection section in settings_leds.htm. Only those with a checked box will appear in the effects dropdown.<br>
<img src="/images/https://github.com/korkbaum/WLED/blob/wled_V12_kk2/images/V12_modified6.png"></p>
<br>
<p align="center">Modified V12 UI. Palette Selection section in settings_leds.htm. Only those with a checked box will appear in the palette dropdown.<br>
<img src="https://github.com/korkbaum/WLED/blob/wled_V12_kk2/images/V12_modified7.png"></p>
<br>
<br>
<br>
<br>
<p align="center">
  <img src="/images/wled_logo_akemi.png">
  <a href="https://github.com/Aircoookie/WLED/releases"><img src="https://img.shields.io/github/release/Aircoookie/WLED.svg?style=flat-square"></a>
  <a href="https://raw.githubusercontent.com/Aircoookie/WLED/master/LICENSE"><img src="https://img.shields.io/github/license/Aircoookie/wled?color=blue&style=flat-square"></a>
  <a href="https://wled.discourse.group"><img src="https://img.shields.io/discourse/topics?colorB=blue&label=forum&server=https%3A%2F%2Fwled.discourse.group%2F&style=flat-square"></a>
  <a href="https://discord.gg/KuqP7NE"><img src="https://img.shields.io/discord/473448917040758787.svg?colorB=blue&label=discord&style=flat-square"></a>
  <a href="https://github.com/Aircoookie/WLED/wiki"><img src="https://img.shields.io/badge/quick_start-wiki-blue.svg?style=flat-square"></a>
  <a href="https://github.com/Aircoookie/WLED-App"><img src="https://img.shields.io/badge/app-wled-blue.svg?style=flat-square"></a>
  <a href="https://gitpod.io/#https://github.com/Aircoookie/WLED"><img src="https://img.shields.io/badge/Gitpod-ready--to--code-blue?style=flat-square&logo=gitpod"></a>

  </p>
  
# Welcome to my project WLED! ✨

A fast and feature-rich implementation of an ESP8266/ESP32 webserver to control NeoPixel (WS2812B, WS2811, SK6812) LEDs or also SPI based chipsets like the WS2801 and APA102!

## ⚙️ Features
- WS2812FX library integrated for over 100 special effects  
- FastLED noise effects and 50 palettes  
- Modern UI with color, effect and segment controls  
- Segments to set different effects and colors to parts of the LEDs  
- Settings page - configuration over network  
- Access Point and station mode - automatic failsafe AP  
- Up to 10 LED outputs per instance
- Support for RGBW strips  
- Up to 250 user presets to save and load colors/effects easily, supports cycling through them.  
- Presets can be used to automatically execute API calls  
- Nightlight function (gradually dims down)  
- Full OTA software updatability (HTTP + ArduinoOTA), password protectable  
- Configurable analog clock + support for the Cronixie kit by Diamex  
- Configurable Auto Brightness limit for safer operation  
- Filesystem-based config for easier backup of presets and settings  

## 💡 Supported light control interfaces
- WLED app for [Android](https://play.google.com/store/apps/details?id=com.aircoookie.WLED) and [iOS](https://apps.apple.com/us/app/wled/id1475695033)
- JSON and HTTP request APIs  
- MQTT  
- Blynk IoT  
- E1.31, Art-Net, DDP and TPM2.net
- [Hyperion](https://github.com/hyperion-project/hyperion.ng)
- UDP realtime  
- Alexa voice control (including dimming and color)  
- Sync to Philips hue lights  
- Adalight (PC ambilight via serial) and TPM2  
- Sync color of multiple WLED devices (UDP notifier)  
- Infrared remotes (24-key RGB, receiver required)  
- Simple timers/schedules (time from NTP, timezones/DST supported)  

## 📲 Quick start guide and documentation

See the [wiki](https://github.com/Aircoookie/WLED/wiki)!

[On this page](https://github.com/Aircoookie/WLED/wiki/Learning-the-ropes) you can find excellent tutorials made by the community and helpful tools to help you get your new lamp up and running!

## 🖼️ Images
<img src="/images/macbook-pro-space-gray-on-the-wooden-table.jpg" width="50%"><img src="/images/walking-with-iphone-x.jpg" width="50%">

## 💾 Compatible LED Strips
Type | Voltage | Comments
|---|---|---|
WS2812B | 5v |
WS2813 | 5v | 
SK6812 | 5v | RGBW
APA102 | 5v | C/D
WS2801 | 5v | C/D
LPD8806 | 5v | C/D
TM1814 | 12v | RGBW
WS2811 | 12v | 3-LED segments
WS2815 | 12v | 
GS8208 | 12v |
Analog/non-addressable | any | Requires additional circuitry

## 🧊 Compatible PC RGB Fans and ARGB accessories
Brand | Model | Comments
|---|---|---|
Corsair | HD120 Fan | Uses WS2812B, data-in only
PCCOOLER | Moonlight 5-pack Fans | Uses WS2812B, includes Data-out connector to keep each fan uniquely addressable if wired in series like traditional LED strips
Any | 5v 3-pin ARGB for PC | Any PC RGB device that supports the 5v 3-pin ARGB motherboard header should work fine with WLED. All the major motherboard vendors support the Corsair HD120 and PCCOOLER fans listed, so we can safely assume any device that supports motherboard ARGB 5V 3-Pin standard will work with WLED.


## ✌️ Other

Licensed under the MIT license  
Credits [here](https://github.com/Aircoookie/WLED/wiki/Contributors-&-About)!

Uses Linearicons by Perxis!

Join the Discord server to discuss everything about WLED!

<a href="https://discord.gg/KuqP7NE"><img src="https://discordapp.com/api/guilds/473448917040758787/widget.png?style=banner2" width="25%"></a>

Check out the WLED [Discourse forum](https://wled.discourse.group)!  
You can also send me mails to [dev.aircoookie@gmail.com](mailto:dev.aircoookie@gmail.com), but please only do so if you want to talk to me privately.  
If WLED really brightens up your every day, you can [![](https://img.shields.io/badge/send%20me%20a%20small%20gift-paypal-blue.svg?style=flat-square)](https://paypal.me/aircoookie)


*Disclaimer:*   
If you are sensitive to photosensitive epilepsy it is not recommended that you use this software.  
In case you still want to try, don't use strobe, lighting or noise modes or high effect speed settings.
As per the MIT license, I assume no liability for any damage to you or any other person or equipment.  


#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "ws2811.h"
#include "Storage.h"
#include "StoredData.h"
#include "DeviceID.h"
#include "BleManager.h"

void setup() {
  Serial.begin(115200);


deviceIdInit();
bleInit();
//initLedTimers();
////// ws2811 ////////

  FastLED.addLeds<WS2811, LED_PIN_1, GRB>(leds1, NUM_LEDS_1);
  FastLED.addLeds<WS2811, LED_PIN_2, GRB>(leds2, NUM_LEDS_2);
 
}

void loop() {
 
  switch (lightShow0) {
    case 0:rgb(0, rgbColor0.r, rgbColor0.g, rgbColor0.b);
      break;
    case 1:rainbow(0);
     break;
    case 2:chase(0, rgbColor0.r, rgbColor0.g, rgbColor0.b);
     break;
     case 3:larsonScanner(0, rgbColor0.r, rgbColor0.g, rgbColor0.b);
     break;
     case 4:paletteCrossfade(0);
     break;
     case 5:sparkle(0);
     break;
     case 6:twinkle(0);
     break;
     case 7:fire2012(0);
     break;
     case 8:randomColor(0);//fadeStep(0);
     break;
     case 9:randomColor(0);
     break;
     default:rainbow(0);
     break;
  }

switch (lightShow1) {
    case 0:rgb(1, rgbColor1.r, rgbColor1.g, rgbColor1.b);
      break;
    case 1:rainbow(1);
     break;
    case 2:chase(1, rgbColor1.r, rgbColor1.g, rgbColor1.b);
     break;
     case 3:larsonScanner(1, rgbColor1.r, rgbColor1.g, rgbColor1.b);
     break;
     case 4:paletteCrossfade(1);
     break;
     case 5:sparkle(1);
     break;
     case 6:twinkle(1);
     break;
     case 7:fire2012(1);
     break;
     case 8:randomColor(1);//fadeStep(1);
     break;
     case 9:randomColor(1);
     break;
     default:rainbow(1);
     break;
  }
 
    FastLED.show();
    delay(20);

 
}

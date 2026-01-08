
#include "ws2811.h"

CRGB leds1[NUM_LEDS_1];
CRGB leds2[NUM_LEDS_2];


String objects[9] = {"RGB",
        "Rainbow",
        "Chase",
        "LarsonScanner",
        "PaletteCrossfade",
        "Sparkle",
        "Twinkle",
        "Fire2012",
        "Random"};

uint8_t lightShow0;
uint8_t lightShow1;
CRGB rgbColor0 = CRGB(255, 0, 0); 
CRGB rgbColor1 = CRGB(0, 0, 255); 

struct LedTimer {
  uint32_t interval;     // ms
  uint32_t lastUpdate;   // millis()
};

LedTimer ledTimers1[NUM_LEDS_1];
LedTimer ledTimers2[NUM_LEDS_2];

CRGB randomColor() {
  return CRGB(random8(), random8(), random8());
}


void rgb(uint8_t channel, uint8_t r, uint8_t g, uint8_t b) {
 
  switch (channel) {
    case 0:fill_solid(leds1, NUM_LEDS_1, CRGB::Black);
            fill_solid(leds1, NUM_LEDS_1, CRGB(g, r, b));
        break;
    case 1:fill_solid(leds2, NUM_LEDS_2, CRGB::Black);
            fill_solid(leds2, NUM_LEDS_2, CRGB(g, r, b));
        break;
    default:
        break;
  }
}

void rainbow(uint8_t channel) {
   static uint8_t hue = 0;

  switch (channel) {
    case 0:for (uint8_t i = 0; i < NUM_LEDS_1; i++) {
        leds1[i] = CHSV(hue + i * 3, 255, 255);
    }
        break;
    case 1:for (uint8_t i = 0; i < NUM_LEDS_2; i++) {
        leds2[i] = CHSV(hue + i * 3, 255, 255);
    }
        break;
    default:
        break;
  }
    hue++;
}

void chase(uint8_t channel, uint8_t r, uint8_t g, uint8_t b) {
  static uint8_t pos = 0;

  switch (channel) {
    case 0:fill_solid(leds1, NUM_LEDS_1, CRGB::Black);
            leds1[pos] = CRGB(g, r, b);
            pos = (pos + 1) % NUM_LEDS_1;
        break;
    case 1:fill_solid(leds2, NUM_LEDS_2, CRGB::Black);
            leds2[pos] = CRGB(g, r, b);
            pos = (pos + 1) % NUM_LEDS_2;
        break;
    default:
        break;
  }
}

void larsonScanner(uint8_t channel, uint8_t r, uint8_t g, uint8_t b) {
  switch (channel) {
    case 0:static uint8_t pos = 0;
    static uint8_t dir = 1;
    fadeToBlackBy(leds1, NUM_LEDS_1, 40);
    leds1[pos] = CRGB::Black;
    leds1[pos] = CRGB(g, r, b);
    //FastLED.show();
    pos += dir;
    if (pos == 0 || pos == NUM_LEDS_1 - 1) dir = -dir;
        break;
    case 1:static uint8_t pos1 = 0;
    static uint8_t dir1 = 1;
    fadeToBlackBy(leds2, NUM_LEDS_2, 40);
    leds1[pos] = CRGB::Black;
    leds2[pos1] = CRGB(g, r, b);
    //FastLED.show();
    pos1 += dir1;
    if (pos1 == 0 || pos1 == NUM_LEDS_2 - 1) dir1 = -dir1;
        break;
    default:
        break;
  }
}

void paletteCrossfade(uint8_t channel) {
  switch (channel) {
    case 0:static uint8_t index = 0;
    fill_palette(leds1, NUM_LEDS_1, index++, 255, RainbowColors_p, 255, LINEARBLEND);
        break;
    case 1:static uint8_t index1 = 0;
    fill_palette(leds2, NUM_LEDS_2, index1++, 255, RainbowColors_p, 255, LINEARBLEND);
        break;
    default:
        break;
  }
}

void sparkle(uint8_t channel) {
  switch (channel) {
    case 0:fadeToBlackBy(leds1, NUM_LEDS_1, 20);
leds1[random(NUM_LEDS_1)] = CRGB::White;
        break;
    case 1:fadeToBlackBy(leds2, NUM_LEDS_2, 20);
leds2[random(NUM_LEDS_2)] = CRGB::White;
        break;
    default:
        break;
  }
}

void twinkle(uint8_t channel) {
  switch (channel) {
    case 0:leds1[random(NUM_LEDS_1)] += CRGB(50, 50, 50);
fadeToBlackBy(leds1, NUM_LEDS_1, 10);
        break;
    case 1:leds2[random(NUM_LEDS_2)] += CRGB(50, 50, 50);
fadeToBlackBy(leds2, NUM_LEDS_2, 10);
        break;
    default:
        break;
  }
}

void fire2012(uint8_t channel) {
  switch (channel) {
    case 0:static byte heat[NUM_LEDS_1];

  for (uint8_t i = 0; i < NUM_LEDS_1; i++) {
    heat[i] = qsub8(heat[i], random8(0, ((55 * 10) / NUM_LEDS_1) + 2));
  }

  for (uint8_t k = NUM_LEDS_1 - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  if (random8() < 120) {
    uint8_t y = random8(7);
    heat[y] = qadd8(heat[y], random8(160, 255));
  }

  for (int j = 0; j < NUM_LEDS_1; j++) {
    CRGB color = HeatColor(heat[j]);
    leds1[j] = color;
  }

break;
case 1:static byte heat1[NUM_LEDS_2];

  for (uint8_t i = 0; i < NUM_LEDS_2; i++) {
    heat1[i] = qsub8(heat1[i], random8(0, ((55 * 10) / NUM_LEDS_2) + 2));
  }

  for (uint8_t k = NUM_LEDS_2 - 1; k >= 2; k--) {
    heat1[k] = (heat1[k - 1] + heat1[k - 2] + heat1[k - 2]) / 3;
  }

  if (random8() < 120) {
    uint8_t y = random8(7);
    heat1[y] = qadd8(heat1[y], random8(160, 255));
  }

  for (uint8_t j = 0; j < NUM_LEDS_2; j++) {
    CRGB color = HeatColor(heat1[j]);
    leds2[j] = color;
  }

break;
default:
break;
}

}

CRGB currentColor;
    CRGB nextColor;
CRGB scaled;
CRGB scaled1;
    CRGB currentColor1;
    CRGB nextColor1;

 uint8_t brightness = 0;
     int8_t fadeDir = 1;   // 1 = fade in, -1 = fade out
     uint8_t fadeSpeed = 3;

 uint8_t brightness1 = 0;
   int8_t fadeDir1 = 1;   // 1 = fade in, -1 = fade out
     uint8_t fadeSpeed1 = 3;

void fadeStep(uint8_t channel) {



    switch (channel) {
      case 0:brightness += fadeDir * fadeSpeed;

    if (brightness >= 255) {
      brightness = 255;
      fadeDir = -1;   // start fading out
    }

    if (brightness == 0 && fadeDir == -1) {
      nextColor = randomColor();
      currentColor = nextColor;
      fadeDir = 1;    // start fading in
    }

    scaled = currentColor;
    scaled.nscale8_video(brightness);
fill_solid(leds1, NUM_LEDS_1, scaled);

break;

case 1:brightness1 += fadeDir1 * fadeSpeed1;

    if (brightness1 >= 255) {
      brightness1 = 255;
      fadeDir1 = -1;   // start fading out
    }

    if (brightness1 == 0 && fadeDir1 == -1) {
      nextColor1 = randomColor();
      currentColor1 = nextColor1;
      fadeDir1 = 1;    // start fading in
    }

    scaled1 = currentColor1;
    scaled1.nscale8_video(brightness1);
fill_solid(leds2, NUM_LEDS_2, scaled1);
break;
default:
break;
    }
  
  
}



void randomColor(uint8_t channel) {
  uint32_t now = millis();

switch (channel) {
    case 0:
  for (int i = 0; i < NUM_LEDS_1; i++) {
    if (now - ledTimers1[i].lastUpdate >= ledTimers1[i].interval) {

      ledTimers1[i].lastUpdate = now;

      // Change LED parameters
      leds1[i] = CHSV(
        random8(),            // hue
        255,                  // saturation
        random8(64, 255)      // brightness
      );


        ledTimers1[i].interval = random(1000, 3000);
     // }
    }
  }
  break;
  case 1:for (int i = 0; i < NUM_LEDS_1; i++) {
    if (now - ledTimers2[i].lastUpdate >= ledTimers2[i].interval) {

      ledTimers2[i].lastUpdate = now;

      // Change LED parameters
      leds2[i] = CHSV(
        random8(),            // hue
        255,                  // saturation
        random8(64, 255)      // brightness
      );

        ledTimers2[i].interval = random(1000, 3000);
   //   }
    }
  }
  break;
  default:
  break;
}
}

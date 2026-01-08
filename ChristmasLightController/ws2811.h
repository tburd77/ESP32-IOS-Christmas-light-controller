#pragma once
#include <FastLED.h>


#define LED_PIN_1 5
#define NUM_LEDS_1 100
extern CRGB leds1[NUM_LEDS_1];


#define LED_PIN_2 18
#define NUM_LEDS_2 100
extern CRGB leds2[NUM_LEDS_2];


extern String objects[9];

extern uint8_t lightShow0;
extern uint8_t lightShow1;

extern CRGB rgbColor0;
extern CRGB rgbColor1;
// --------------------
#define BRIGHTNESS 150

void fadeInOutRGB(uint8_t channel, unsigned long now);
void rgb(uint8_t channel, uint8_t r, uint8_t g, uint8_t b);
void rainbow(uint8_t channel);
void chase(uint8_t channel, uint8_t r, uint8_t g, uint8_t b);
void larsonScanner(uint8_t channel, uint8_t r, uint8_t g, uint8_t b);
void paletteCrossfade(uint8_t channel);
void fire2012(uint8_t channel);
void sparkle(uint8_t channel);
void twinkle(uint8_t channel);
void fadeStep(uint8_t channel);
void initLedTimers();
void randomColor(uint8_t channel);



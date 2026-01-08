#pragma once

#include <FastLED.h>

struct StoredData {
  char showName[32];
  char str2[32];
  int brightness;
  CRGB color;
};

// declare (no storage here!)
extern StoredData defaultsA;
extern StoredData defaultsB;

#include "DeviceID.h"
#include <Preferences.h>
#include <esp_system.h>

static Preferences prefs;
static char deviceId[32];   // persistent RAM copy

void deviceIdInit() {
  prefs.begin("device", false);

  // Try to load existing ID
  if (prefs.getString("id", deviceId, sizeof(deviceId)) > 0) {
    prefs.end();
    return;
  }

  // Generate from chip ID (eFuse MAC)
  uint64_t chipId = ESP.getEfuseMac(); // 48-bit unique ID

  snprintf(
    deviceId,
    sizeof(deviceId),
    "XMAS_%04X%08X",
    (uint16_t)(chipId >> 32),
    (uint32_t)chipId
  );

  // Store permanently
  prefs.putString("id", deviceId);
  prefs.end();
}

const char* getDeviceId() {
  return deviceId;
}

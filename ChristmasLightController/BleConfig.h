#pragma once
#include <Arduino.h>

/* ===============================
   BLE Device Identity
   =============================== */

constexpr char BLE_ADVERTISING_NAME[] = "XMASLIGHTS_5";
constexpr char UNIQUE_DEVICE_ID[] = "12345678-1234-1234-1234-1234567890bc";


constexpr char GAP_NAME[] = "XMASLIGHTS_CONTROLLER";
/*Purpose
The Bluetooth advertising name
Visible in:
iOS BLE scan
System Bluetooth UI
Debug tools
Characteristics
Same for all ESP32s running this firmware
Not guaranteed unique
iOS may cache it
Changing it does not reliably distinguish devices
Best Practice
Use the same name for all devices of the same product.*/

/* Optional: unique per device */
//constexpr char UNIQUE_DEVICE_ID[] = "12345678-1234-1234-1234-1234567890b4";//"XMASLIGHTS_4";//Change this only -- Logical unique ID How your app identifies each ESP32
/*Purpose
A unique identifier inside your protocol
Read via a BLE characteristic
Used by your iPhone app to:
Tell devices apart
Save per-device settings
Reconnect reliably
Characteristics
Must be unique per ESP32
Not shown in system UI
Fully under your control
Stable across reboots*/
/* ===============================
   BLE UUIDs (same for all devices)
   =============================== */
/*Why You Need Both (iOS Reality)
iOS BLE limitations:
Device names are cached
MAC addresses are hidden
Discovery order is unstable
➡️ Device Name alone is not reliable*/
constexpr char SERVICE_UUID[] =
  "12345678-1234-1234-1234-1234567890ab";

constexpr char CHAR_RX_UUID[] =
  "12345678-1234-1234-1234-1234567890ac"; // iPhone → ESP32

constexpr char CHAR_TX_UUID[] =
  "12345678-1234-1234-1234-1234567890ad"; // ESP32 → iPhone

constexpr char CHAR_ID_UUID[] =
  "12345678-1234-1234-1234-1234567890ae"; // Device ID (read-only)

/* ===============================
   BLE Settings
   =============================== */

constexpr uint16_t BLE_MTU_SIZE = 185;


/*#pragma once

#include <FastLED.h>

#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHAR_UUID_RX        "12345678-1234-1234-1234-1234567890ac" // Write
#define CHAR_UUID_TX        "12345678-1234-1234-1234-1234567890ad" // Notify*/
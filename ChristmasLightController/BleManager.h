#pragma once

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

//extern StoredData slotA;
//extern StoredData slotB;
void bleInit();
void bleSend(const uint8_t* data, size_t len);
bool bleIsConnected();
void parseCommand(const String& cmd);




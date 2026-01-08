#include "BleManager.h"
#include "BleConfig.h"
#include "ws2811.h"
#include "Storage.h"
#include "StoredData.h"
#include "DeviceID.h"
/* ===============================
   Globals (BLE owns these)
   =============================== */

BLECharacteristic* txCharacteristic = nullptr;
bool deviceConnected = false;
const int NUM_OBJECTS = sizeof(objects) / sizeof(objects[0]);
StoredData slotA;
StoredData slotB;

int indexOf(const String& target) {
    for (int i = 0; i < NUM_OBJECTS; i++) {
        if (objects[i] == target) {
            return i;
        }
    }
    return -1;
}
    
/* ===============================
   Callbacks
   =============================== */

class ServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer*) override {
    deviceConnected = true;
    Serial.println("iOS connected");
  }
  void onDisconnect(BLEServer*) override {
    deviceConnected = false;
    Serial.println("iOS disconnected");
    BLEDevice::startAdvertising();
  }
};

class RxCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pChar) {
    String value = pChar->getValue();
    if (value.length()) {
      Serial.print("Received: ");
      Serial.println(value.c_str());

      if (value.isEmpty()) return;

    String cmd = String(value.c_str());
    cmd.trim();    
    if (value.c_str() != "Hello ESP32 From IOS") {
      parseCommand(cmd);
    }

    String reply = "Hello IOS from ESP32";
      //txCharacteristic->setValue(value);
      txCharacteristic->setValue(reply);
      txCharacteristic->notify();
    }
  }
};

/* ===============================
   BLE Init
   =============================== */

void bleInit() {
  BLEDevice::init(GAP_NAME);
  BLEDevice::setMTU(BLE_MTU_SIZE);

  BLEServer* server = BLEDevice::createServer();
  server->setCallbacks(new ServerCallbacks());

  BLEService* service =
    server->createService(SERVICE_UUID);

  // RX (write)
  BLECharacteristic* rxChar =
    service->createCharacteristic(
      CHAR_RX_UUID,
      BLECharacteristic::PROPERTY_WRITE
    );
  rxChar->setCallbacks(new RxCallbacks());

  // TX (notify)
  txCharacteristic =
    service->createCharacteristic(
      CHAR_TX_UUID,
      BLECharacteristic::PROPERTY_NOTIFY
    );
  txCharacteristic->addDescriptor(new BLE2902());


  // Device ID (read-only)
  BLECharacteristic* idChar =
    service->createCharacteristic(
      CHAR_ID_UUID,
      BLECharacteristic::PROPERTY_READ
    );
    
    
  idChar->setValue(UNIQUE_DEVICE_ID);

  service->start();

//BLEAdvertisementData adv;
//adv.setManufacturerData(BLE_ADVERTISING_NAME);
//BLEDevice::getAdvertising()->setAdvertisementData(adv);
//adv->start();



BLEAdvertisementData adv;
//adv.setManufacturerData(std::string(BLE_ADVERTISING_NAME));
adv.setManufacturerData(BLE_ADVERTISING_NAME);
BLEAdvertising *advertising = BLEDevice::getAdvertising();
advertising->setAdvertisementData(adv);
advertising->start();   

//BLEAdvertisementData adv;
//adv.setName(advertisingName);   // Visible in scan
//BLEDevice::getAdvertising()->setAdvertisementData(adv);


  //BLEAdvertising* adv = BLEDevice::getAdvertising();
  //adv->addServiceUUID(SERVICE_UUID);
  //adv->start();

  Serial.println("ESP32 BLE ready");

    if (!loadStoredData(slotA, slotB)) {
    Serial.println("No saved data — writing defaults");
    saveStoredData(defaultsA, defaultsB);
    slotA = defaultsA;
    slotB = defaultsB;
  }

  lightShow0 =  indexOf(slotA.showName);
  lightShow1 =  indexOf(slotB.showName);

  rgbColor0 = slotA.color;
  rgbColor1 = slotB.color;

  //not used
  objects[lightShow0].toCharArray(slotA.showName, sizeof(slotA.showName));
  String fromStr = "No Data";
  fromStr.toCharArray(slotA.str2, sizeof(slotA.str2));
  fromStr.toCharArray(slotB.str2, sizeof(slotB.str2));
  slotA.brightness = 150;
  slotB.brightness = 150;

  saveStoredData(slotA, slotB);

   Serial.println("Slot A:");
  Serial.println(slotA.showName);
  Serial.println(slotA.str2);
  Serial.println(slotA.brightness);
  Serial.printf("Color: %d %d %d\n",
                slotA.color.r, slotA.color.g, slotA.color.b);

  Serial.println("Slot B:");
  Serial.println(slotB.showName);
  Serial.println(slotB.str2);
  Serial.println(slotB.brightness);
  Serial.printf("Color: %d %d %d\n",
                slotB.color.r, slotB.color.g, slotB.color.b);
}

/* ===============================
   Public API
   =============================== */

void bleSend(const uint8_t* data, size_t len) {
  if (!deviceConnected || !txCharacteristic) return;
  txCharacteristic->setValue(data, len);
  txCharacteristic->notify();
}

bool bleIsConnected() {
  return deviceConnected;
}

void parseCommand(const String& cmd) {
    String mutableCmd = cmd;
    Serial.println("Parsing");
    Serial.println(mutableCmd);
    int channel = 3;

    if (mutableCmd.startsWith("0")) {
      channel = 0;
    }else if (mutableCmd.startsWith("1")){
      channel = 1;
    }

    if (channel != 3) {

      int spaceIndex = mutableCmd.indexOf(' ');
      if (spaceIndex != -1) {
            mutableCmd.remove(0, spaceIndex + 1);
      }
      Serial.println(mutableCmd);
      if (mutableCmd.startsWith("RGB ")) {
        int r, g, b;

        if (sscanf(mutableCmd.c_str(), "RGB %d %d %d", &r, &g, &b) == 3) {
          r = constrain(r, 0, 255);
          g = constrain(g, 0, 255);
          b = constrain(b, 0, 255);
          Serial.println("command is a rgb");
        } else {
          Serial.println("Parse error");
        }

        if (channel == 0) {
            lightShow0 = 0;
            rgbColor0 = CRGB(r, g, b);
        }else {
            lightShow1 = 0;
            rgbColor1 = CRGB(r, g, b);
        }
      }else {
          if (channel == 0) {
             lightShow0 =  indexOf(mutableCmd);
          }else {
             lightShow1 =  indexOf(mutableCmd);
          }

      }

      if (lightShow0 >= 0 && lightShow0 < 10) {
          objects[lightShow0].toCharArray(slotA.showName, sizeof(slotA.showName));
      }
      if (lightShow1 >= 0 && lightShow1 < 10) {
          objects[lightShow1].toCharArray(slotB.showName, sizeof(slotB.showName));
      }
      slotA.color = rgbColor0;
      slotB.color = rgbColor1;
 
       saveStoredData(slotA, slotB);
    }

    Serial.println("lightShow0 = ");
        Serial.println(lightShow0);
        Serial.println("lightShow1 = ");
        Serial.println(lightShow1);
}

#include "Storage.h"

Preferences prefs;

void saveStoredData(const StoredData& a, const StoredData& b) {
  prefs.begin("storage", false);   // RW

  prefs.putBytes("slotA", &a, sizeof(StoredData));
  prefs.putBytes("slotB", &b, sizeof(StoredData));
 Serial.println("saveStoredData");
  prefs.end();
}

bool loadStoredData(StoredData& a, StoredData& b) {
  prefs.begin("storage", true);   // Read-only

  bool ok = true;

  if (prefs.getBytesLength("slotA") == sizeof(StoredData)) {
    prefs.getBytes("slotA", &a, sizeof(StoredData));
  } else ok = false;

  if (prefs.getBytesLength("slotB") == sizeof(StoredData)) {
    prefs.getBytes("slotB", &b, sizeof(StoredData));
  } else ok = false;
 Serial.println("loadStoredData");
  prefs.end();
  return ok;
}
/*lightShow0 =  indexOf(mutableCmd);
String str = slotA.showName;
lightShow0 =  indexOf(str);
  lightShow1 =  indexOf(slotB.showName);

  rgbColor0 = slotA.color;
  rgbColor1 = slotB.color;*/



  



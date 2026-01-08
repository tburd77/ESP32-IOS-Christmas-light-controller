#pragma once

#include <Preferences.h>
#include "StoredData.h"

void saveStoredData(const StoredData& a, const StoredData& b);
bool loadStoredData(StoredData& a, StoredData& b);

#include "lwz.h"

void initializeLWZCodeMap() {
    for (int i = 0; i < 256; ++i) {
        string code = string(1, static_cast<char>(i));
        lwzCodeMap[code] = i;
    }
}


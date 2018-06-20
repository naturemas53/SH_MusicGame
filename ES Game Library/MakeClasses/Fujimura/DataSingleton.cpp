#include "DataSingleton.h"

DataSingleton::DataSingleton():
atlasSp_(nullptr),

NOTESIZE_(Vector2(64.0f,32.0f)),
SINGLENOTERECT_(RectWH(0, 80, 64, 32)),
LONGNOTERECT_(RectWH(64, 80, 64, 32)),
EVENTNOTERECT_(RectWH(128, 80, 64, 32)),

NORMCOMBO_(50),

LONG_OK_RELEASE_TIME_(20),

BOMB_MAX_PAL_VALUE_(30)
{}
#include "IGTimerHelper.h"

TMap<FTimerHandle, FIGTimerHelper::FTimePoint> FIGTimerHelper::DeltaTimeMap;
TMap<FTimerHandle, FIGTimerHelper::FTimePoint> FIGTimerHelper::DelayMap;
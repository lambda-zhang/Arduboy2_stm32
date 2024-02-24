
#include <WString.h>
// #include "Utils.h"

extern const __FlashStringHelper * FlashString(const char * string);

const char OccularName[] = "AN OCCULAR";
const char SkeletonName[] = "A SKELETON";
const char SparkatName[] = "A SPARKAT";
const char WraithName[] = "A WRAITH";
const char DragonName[] = "A DRAGON";
const char RatName[] = "A RAT";
const char SlimeName[] = "A SLIME";

const __FlashStringHelper * EnemyNames[] = {
    FlashString(OccularName),
    FlashString(SkeletonName),
    FlashString(SparkatName),
    FlashString(WraithName),
    FlashString(DragonName),
    FlashString(RatName),
    FlashString(SlimeName),    
};

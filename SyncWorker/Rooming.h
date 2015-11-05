#pragma once
#include "RoomProcessor.h"

extern std::map<int, RoomProcessor*> _processors;
extern std::map<int, Entity*> _roomless_entities;
extern int proc_count;
#pragma once
#include <stdio.h>
#include <STRUCTS/structs.h>
#include <cmath>
#include <STRUCTS/structs.h>

class kinematics {
public:
    static void calcModuleState(ModuleState&, BotState, Cecilia);
};
#pragma once
#include <stdio.h>
#include <STRUCTS/structs.h>
#include <cmath>

class kinematics {
public:
    static void calcModuleState(ModuleState&, BotState, Cecilia);
};
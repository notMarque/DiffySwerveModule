#include <kinematics.h>

void kinematics::calcModuleState(ModuleState& modSt, BotState botSt, Cecilia cici) {
    // Calculations for turning
    float w_x = cici.y * botSt.w;
    float w_y = cici.x * botSt.w;

    float sum_x = w_x + botSt.u;
    float sum_y = w_y + botSt.v;

    float angle = atan2(sum_y, sum_x);
    float speed = sqrt(pow(sum_x, 2) + pow(sum_y, 2));
    modSt.theta = (int)(angle * 1000);
    modSt.v = (int)(speed * 10);
}
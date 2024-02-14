#include "calc.hpp"

double returnVolts(int eightBit)
{
   return static_cast<double>(eightBit * 12/127);
}

int returnPct(int eightBit)
{
    return static_cast<int>(100 * static_cast<double>(eightBit/127));
}

double toRad(float angle)
{
    return static_cast<double>(angle * 3.14159/180);
}
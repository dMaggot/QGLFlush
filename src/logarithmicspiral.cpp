#include "logarithmicspiral.h"

#include <cmath>

LogarithmicSpiral::LogarithmicSpiral(float a, float b) :
        a(a), b(b)
{
}

LogarithmicSpiral::~LogarithmicSpiral()
{
}

float LogarithmicSpiral::radius(float p)
{
        return a * exp(b * p);
}

float LogarithmicSpiral::param(float r)
{
        return log(r / a) / b;
}


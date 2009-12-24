#ifndef LOGARITHMICSPIRAL_H
#define LOGARITHMICSPIRAL_H

#include "spiral.h"

class LogarithmicSpiral: public Spiral
{
public:
        LogarithmicSpiral(float, float);
        virtual ~LogarithmicSpiral();
        float param(float);
        float radius(float);

private:
        float a;
        float b;
};

#endif // LOGARITHMICSPIRAL_H

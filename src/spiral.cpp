#include "spiral.h"

#include <cmath>

Spiral::Spiral()
{
}

Spiral::~Spiral()
{
}

void Spiral::transform(int & x, int & y, float tick)
{
        float r = sqrt(pow(x, 2) + pow(y, 2));

        float p = this->param(r);

        float angle = atan2(y, x) - p;

        p -= pow(p, 5) * tick;

        float tr = this->radius(p);
        float tx = tr * cos(p);
        float ty = tr * sin(p);

        x = cos(angle) * tx - sin(angle) * ty + 300;
        y = sin(angle) * tx + cos(angle) * ty + 300;
}

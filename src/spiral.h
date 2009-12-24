#ifndef SPIRAL_H
#define SPIRAL_H

class Spiral
{
public:
        Spiral();
        virtual ~Spiral();
        void transform(int &, int &, float);
        virtual float param(float) = 0;
        virtual float radius(float) = 0;
};
#endif // SPIRAL_H

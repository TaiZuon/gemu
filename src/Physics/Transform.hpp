#include "Vector2D.hpp"

class Transform
{
public:
    double X, Y;
    Transform(double x, double y)
    {
        X = x; Y = y;
    }
    void TranslateX(double x) {x += x;}
    void TranslateY(double y) {Y += y;}
    void Translate(Vector2D v) 
    {
        X += v.X;
        Y += v.Y;
    }
};

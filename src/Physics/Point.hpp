#pragma once

class Point
{
private:
    
public:
    double X;
    double Y;
    Point(double x, double y)
    {
        X = x;
        Y = y;
    }
    Point Add_Point(Point a)
    {
        X += a.X;
        Y += a.Y;
    }
    Point ScalarMultiply_Point(double k)
    {
        X = X * k;
        Y = Y * k;
    }
};



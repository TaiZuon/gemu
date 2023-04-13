#pragma once

#include <bits/stdc++.h>

class Vector2D
{
public:
    double X;
    double Y;
public:
    Vector2D(){}
    Vector2D(double x, double y);
    Vector2D Add_Vector( Vector2D a, Vector2D b );
    Vector2D ScalarMultiply_Vector( Vector2D a, double k );
    double DotProduct_Vector( Vector2D a, Vector2D b );
    double Magnitude_Vector( Vector2D a );
    double Angle_Vector( Vector2D a, Vector2D b );

};
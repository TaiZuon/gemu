#include "Vector2D.hpp"

Vector2D::Vector2D(double x, double y)
{
    X = x; Y = y;
}

Vector2D Vector2D::Add_Vector( Vector2D a, Vector2D b )
{
    double x = a.X + b.X;
    double y = a.Y + b.Y;
    Vector2D c( x, y );
    return c;
}

Vector2D Vector2D::ScalarMultiply_Vector( Vector2D a, double k )
{
    Vector2D c( a.X * k, a.Y * k );
    return c;
}

double Vector2D::DotProduct_Vector( Vector2D a, Vector2D b )
{
    return a.X * b.X + a.Y * b.Y;
}

double Vector2D::Magnitude_Vector( Vector2D a )
{
    return sqrt( a.X*a.X + a.Y*a.Y);
}

double Vector2D::Angle_Vector( Vector2D a, Vector2D b )
{
    double DotPro = Vector2D::DotProduct_Vector( a, b );
    double Mag = Vector2D::Magnitude_Vector( a ) * Vector2D::Magnitude_Vector( b );
    double Cos = DotPro / Mag;
    double Angle = acos( Cos );
}


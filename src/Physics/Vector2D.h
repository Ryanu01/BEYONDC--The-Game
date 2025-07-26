#ifndef VECTOR2D_H
#define VECTOR2D_H
#include<iostream>
#include<string>

class Vector2D
{
public:
    float X, Y;
public:
    Vector2D(float x = 0, float y = 0) : X(x), Y(y) {}

public:
    //Addition + (to add vectors of x and y corrdinates)
    inline Vector2D operator+(const Vector2D& v2) const{
        return Vector2D(X + v2.X, Y + v2.Y);
    }

    //Difference - (to subtract vectors of x and y cordinates)
    inline Vector2D operator-(const Vector2D& v2) const{
        return Vector2D(X - v2.X, Y - v2.Y);
    }

    //Multiplication *
    inline Vector2D operator*(const float scalar)const
    {
        return Vector2D(X*scalar, Y*scalar);
    }
  
    void Log(std::string msg = "")
    {
        std::cout<< msg <<"(X Y) = (" << X << " "<< Y << ")"<<std::endl;
    }

};

#endif
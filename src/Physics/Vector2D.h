#ifndef VECTOR2D_H
#define VECTOR2D_H
#include<iostream>
#include<cmath>
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

    static float Distance(Vector2D a, Vector2D b){
        return sqrt(pow(b.X - a.X, 2) + pow(b.Y - a.Y, 2));
    }
  
    //Normalize funxtion
    Vector2D Normalize() const{
        float length = sqrt(X*X + Y*Y);
        if(length == 0)
        {
            return Vector2D(0,0);
        }
        return Vector2D(X/length, Y/length);
    }

    Vector2D operator/(float scalar) const {
        return Vector2D(X / scalar, Y / scalar);
    }
 Vector2D& operator+=(const Vector2D& v) {
        X += v.X;
        Y += v.Y;
        return *this;
    }
    void Zero()
    {
        X = 0.0f;
        Y = 0.0f;
    }

    void Log(std::string msg = "")
    {
        std::cout<< msg <<"(X Y) = (" << X << " "<< Y << ")"<<std::endl;
    }

};

#endif
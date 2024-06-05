/******************************************************************************/
// Project: - shape header
// Date: 03.01.2023
// Author: karam aamar
// Reviewer: 
// Version: 
/******************************************************************************/
#ifndef ILRD_HRD26_SHAPE_HPP
#define ILRD_HRD26_SHAPE_HPP

#include <string>

namespace ilrd_26
{

class Shape
{
    public:
        virtual ~Shape();
        virtual void Draw() = 0;
        virtual void Move() = 0;
    
};

class Line:public Shape
{
    public:
        Line(); 
        void Draw();
        void Move();
    private:
        std::string derived;
};
class Circle:public Shape
{
    public:
        Circle(); 
        void Draw();
        void Move();
    private:
        std::string derived;
};
class Rectangle:public Shape
{
    public:
        Rectangle(); 
        void Draw();
        void Move();
    private:
        std::string derived;
};
class Square:public Shape
{
    public:
        Square(); 
        void Draw();
        void Move();
    private:
        std::string derived;
};

}
#endif//ILRD_HRD26_SHAPE_HPP

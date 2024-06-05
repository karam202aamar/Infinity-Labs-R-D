/******************************************************************************/
// Project:  - shape cpp
// Date: 03.01.2023
// Author: karam aamar
// Reviewer: 
// Version: 
/******************************************************************************/
#include <iostream> //cin cout

#include "shape.hpp"

using namespace std;
using namespace ilrd_26;
/******************************************************************************/
void Shape::Draw()
{
    //empty
}
void Shape::Move()
{
    //empty
}
Shape::~Shape()
{
    //empty
}
/******************************************************************************/
Line::Line():derived("Line")
{
    //empty
}
void Line::Draw()
{
    std::cout << derived << std::endl;
}
void Line::Move()
{
    std::cout.width(100); std::cout << std::right << derived << '\n';
}
/******************************************************************************/
Circle::Circle():derived("Circle")
{
    //empty
}
void Circle::Draw()
{
    std::cout << derived << std::endl;
}
void Circle::Move()
{
    std::cout.width(100); std::cout << std::right << derived << '\n';
}
/******************************************************************************/
Rectangle::Rectangle():derived("Rectangle")
{
    //empty
}
void Rectangle::Draw()
{
    std::cout << derived << std::endl;
}
void Rectangle::Move()
{
    std::cout.width(100); std::cout << std::right << derived << '\n';
}
/******************************************************************************/
Square::Square():derived("Square")
{
    //empty
}
void Square::Draw()
{
    std::cout << derived << std::endl;
}
void Square::Move()
{
    std::cout.width(100); std::cout << std::right << derived << '\n';
}
/******************************************************************************/


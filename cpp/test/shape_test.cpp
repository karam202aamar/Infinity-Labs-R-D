/******************************************************************************/
// Project:  - shape test
// Date: 03.01.2023
// Author: karam aamar
// Reviewer: 
// Version: 
/******************************************************************************/
#include "shape.hpp"
#include <iostream> //cin cout
#include <list>//list
#include <iterator>//list_iterator
/******************************************************************************/
static void TestIMP();
/******************************************************************************/
int main()
{
    TestIMP();

    return 0;
}
/******************************************************************************/
static void TestIMP()
{
    ilrd_26::Line* l1 = new ilrd_26::Line;

    l1->Draw();
    l1->Move();
/********************/
    ilrd_26::Circle* c1 = new ilrd_26::Circle;

    c1->Draw();
    c1->Move();
/********************/
    ilrd_26::Rectangle* r1 = new ilrd_26::Rectangle;

    r1->Draw();
    r1->Move();
/********************/
    ilrd_26::Square* s1 = new ilrd_26::Square;

    s1->Draw();
    s1->Move();
/********************/
    std::cout << "\t\t\t\t\tlist prints: "  << std::endl;

    std::list<ilrd_26::Shape*>shapes_list;
    shapes_list.push_back(l1);
    shapes_list.push_back(c1);
    shapes_list.push_back(r1);
    shapes_list.push_back(s1);

    std::list<ilrd_26::Shape*>::iterator it;

    for (it = shapes_list.begin(); it != shapes_list.end(); ++it)
    {
        (*it)->Draw();
        (*it)->Move();
    }
    /* 
    (shapes_list.front())->Draw();
    (shapes_list.front())->Move();
    shapes_list.pop_front(); */

/********************/
    delete l1;
    delete c1;
    delete r1;
    delete s1;
}
/******************************************************************************/
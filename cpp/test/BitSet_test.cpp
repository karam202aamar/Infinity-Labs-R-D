/*******************************************************************************
* Project: BitSet - Test
* Date: 27.01.2023
* Author: karam
* Reviewer: 
* Version: 1.0
*******************************************************************************/
#include <iostream>
#include "BitSet.hpp"
/******************************************************************************/
static void OperatorEqualBool();
/******************************************************************************/
using namespace ilrd::hrd26;

int main()
{
	OperatorEqualBool();

	return 0;
}
/******************************************************************************/
void OperatorEqualBool()
{
    /* size_t ret;
	BitSet<128> instance;
	instance[10] = true;
    std::cout<< "hey" <<std::endl;

    ret = instance.CountTrueBits();
    std::cout<< ret <<std::endl;

    std::cout<< instance <<std::endl; */
    BitSet<128> instance_1;
    BitSet<128> instance_2;
    instance_1[10] = true;
	instance_2[20] = true;
    
    if(instance_1 == instance_2)
    {
        std::cout<< "failed" <<std::endl;
    }
    
}
/******************************************************************************/
void CountOnBits()
{
    BitSet<3000> instance_1;

    instance_1[10] = true;
    instance_1[100] = true;
    instance_1[1000] = true;

    if(3 != instance_1.CountTrueBits())
    {
        std::cout<< "failed" <<std::endl;
    }
}
/******************************************************************************/
void SquareBrackets()
{
    BitSet<3000> instance_1;
  
    instance_1[10] = true;

    if(true != instance_1[10])
    {
        std::cout<< "failed" <<std::endl;
    }
    if(false != instance_1[1000])
    {
        std::cout<< "failed" <<std::endl;
    }
}
/******************************************************************************/
void AndOperator()
{
    BitSet<128> instance_1;
    BitSet<128> instance_2;
    instance_1[0] = true;
	instance_2[1] = true;

    BitSet<128> result = instance_1 &= instance_2;

    if(result[0] != 0 && result[1] != 0)
    {
        std::cout<< "failed" <<std::endl;
    }
}
/******************************************************************************/
void OrOperator()
{
    BitSet<128> instance_1;
    BitSet<128> instance_2;
    instance_1[0] = true;
	instance_2[1] = true;

    BitSet<128> result = instance_1 &= instance_2;

    if(result[0] != 1 && result[1] != 1)
    {
        std::cout<< "failed" <<std::endl;
    }
}
/******************************************************************************/
void NotOrOperator()
{
    BitSet<128> instance_1;
    BitSet<128> instance_2;
    instance_1[0] = true;
	instance_2[1] = true;

    BitSet<128> result = instance_1 ^= instance_2;

    if(result[0] != 1 && result[1] != 1)
    {
        std::cout<< "failed" <<std::endl;
    }
}
/******************************************************************************/
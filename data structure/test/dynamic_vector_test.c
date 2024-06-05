/*******************************************************************************
 * Project: Data Structures - Dynamic Vector
 * Date: 09/08/22
 * Name: karam Aamar
 * Reviewer: dana shapso
 * Version: 2.0
*******************************************************************************/
#include <stdio.h> /* puts */

#include "dynamic_vector.h"

static void ImplementTest();
static void PushBackAndGetAccessTest(dynamic_vector_ty *vector);
static void PopBackAndCurrentSizeTest(dynamic_vector_ty *vector);
static void CapacityTest(dynamic_vector_ty *vector);
static void ReserveTest(dynamic_vector_ty *vector);
static void ShrinkTest(dynamic_vector_ty *vector);

int main()
{
	ImplementTest();
	
	return 0;
}

static void ImplementTest()
{
	size_t size_of_element = sizeof(int);
	size_t num_of_elements = 5;
	
	dynamic_vector_ty *vector = DynamicVectorCreate(size_of_element,
							       num_of_elements);
							       							   
	if (NULL == vector)
	{
		puts("Create test failed");
	}
	
	PushBackAndGetAccessTest(vector);
	PopBackAndCurrentSizeTest(vector);
	CapacityTest(vector);
	ReserveTest(vector);
	ShrinkTest(vector);
	
	DynamicVectorDestroy(vector);
}

static void PushBackAndGetAccessTest(dynamic_vector_ty *vector)
{
	int element0 = 0;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	
	int result0 = DynamicVectorPushback(vector, &element0);
	int result1 = DynamicVectorPushback(vector, &element1);
	int result2 = DynamicVectorPushback(vector, &element2);
	int result3 = DynamicVectorPushback(vector, &element3);
	
	int *element0_result = (int *)DynamicVectorGetAccessToElement(vector, 1);
	int *element1_result = (int *)DynamicVectorGetAccessToElement(vector, 2);
	int *element2_result = (int *)DynamicVectorGetAccessToElement(vector, 3);
	int *element3_result = (int *)DynamicVectorGetAccessToElement(vector, 4);
	
	if (result0 || result1 || result2 || result3)
	{
		puts("PushBack test failed");
	}
	
	if (element0 != *element0_result)
	{
		puts("GetAccess test0 failed");
	}
	
	if (element1 != *element1_result)
	{
		puts("GetAccess test1 failed");
	}
	
	if (element2 != *element2_result)
	{
		puts("GetAccess test2 failed");
	}
	
	if (element3 != *element3_result)
	{
		puts("GetAccess test3 failed");
	}
}

static void PopBackAndCurrentSizeTest(dynamic_vector_ty *vector)
{
	DynamicVectorPopBack(vector);
	
	if (3 != DynamicVectorCurrentSize(vector))
	{
		puts("PopBack and CurrentSize test failed");
	}
}

static void CapacityTest(dynamic_vector_ty *vector)
{
	
	if (5 != DynamicVectorCapacity(vector))
	{
		puts("Capacity test failed");
	}
}

static void ReserveTest(dynamic_vector_ty *vector)
{
	size_t new_capacity = 40;
	
	if (VectorReserve(vector, new_capacity))
	{
		puts("Reserve test failed");
	}
	
	if (10 != DynamicVectorCapacity(vector))
	{
		puts("Capacity after reserve test failed");
	}
}

static void ShrinkTest(dynamic_vector_ty *vector)
{
	if (VectorShrink(vector))
	{
		puts("Shrink test failed");
	}
	
	if (9 != DynamicVectorCapacity(vector))
	{
		puts("Capacity after shrink test failed");
	}
}


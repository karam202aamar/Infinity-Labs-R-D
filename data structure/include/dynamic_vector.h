/*******************************************************************************
 * Project: Data Structures - Dynamic Vector
 * Date: 07/08/22
 * Name: 
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/

#ifndef __DYNAMIC_VECTOR_H_ILRD__
#define __DYNAMIC_VECTOR_H_ILRD__

#include <stddef.h> /* size_t */

typedef struct dynamic_vector dynamic_vector_ty;

/*******************************************************************************
** Description: Create a new empty dynamic vector in the size of initial
								capacity.
** Arguments: size_of_element - size in bytes of the element to be stored
**            num_of_elements - the initial size of the vector
** Return Value: the vector created
*******************************************************************************/
dynamic_vector_ty *DynamicVectorCreate(size_t size_of_element,
							size_t num_of_elements);
							
/*******************************************************************************
** Description: Destroys vector.
** Arguments: vector - pointer to the vector handler to destroy
*******************************************************************************/
void DynamicVectorDestroy(dynamic_vector_ty *vector);

/*******************************************************************************
** Description: Adds an element to the end of vector.
** Arguments: vector - pointer to the vector handler to add the element to
**            elements - the element to add to the vector
** Return Value: 0 - success
**               1 - fail
** Undefined behavior: if element is NULL.
*******************************************************************************/
int DynamicVectorPushback(dynamic_vector_ty *vector, void *element);

/*******************************************************************************
** Description: Removes the last element in the given vector.
** Arguments: vector - pointer to the vector handler
** Undefined behavior: if vector is empty
*******************************************************************************/
void DynamicVectorPopBack(dynamic_vector_ty *vector);

/*******************************************************************************
** Description: Returns the element in the given index of vector.
** Arguments: vector - pointer to the vector handler
**	      index - the index of the element to return
** Undefined behavior: if the index is greater than current size of vector
*******************************************************************************/
void *DynamicVectorGetAccessToElement(const dynamic_vector_ty *vector,
							size_t index);
/*******************************************************************************
** Description: Returns the number of elements currently in vector.
** Arguments: vector - pointer to the vector handler 
** Return Value: the number of element currently in the vector
*******************************************************************************/
size_t DynamicVectorCurrentSize(const dynamic_vector_ty *vector);

/*******************************************************************************
** Description: Returns the number of current maximum capacity in vector.
** Arguments: vector - pointer to the vector handler
** Return Value: the capacity of the vector
*******************************************************************************/
size_t DynamicVectorCapacity(const dynamic_vector_ty *vector);

/*******************************************************************************
** Description: Changes the vector capacity to the required new capacity.
** Arguments: vector - pointer to the vector handler
**            new_capacity - new capacity
** Return Value: 0 - success
**               1 - fail
** Undefined behavior: if new_capacity is smaller than the current capacity
*******************************************************************************/
int VectorReserve(dynamic_vector_ty *vector, size_t new_capacity); 

/*****************************************************************************
** Description: Reduces the vector capacity to an internally pre-defined 
				proportion relative to the current vector size.
** Arguments: vector - pointer to the vector handler
** Return Value: 0 - success
**               1 - fail
******************************************************************************/
int VectorShrink(dynamic_vector_ty *vector); 

#endif /* __DYNAMIC_VECTOR_H_ILRD__ */

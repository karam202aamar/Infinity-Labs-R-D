/*******************************************************************************
 * Project: Data Structures - Dynamic Vector
 * Date: 08/08/22
 * Name: 
 * Reviewer: 
 * Version: 1.1
*******************************************************************************/
#include <stdio.h> /*printf, perror*/
#include <stdlib.h>/*malloc, free*/
#include <string.h>/*memcpy, strerror*/ 
#include <assert.h>/*assert*/
#include <errno.h> /*ernno*/

#include "dynamic_vector.h" 
/******************************************************************************/
enum STATUS {SUCCESS = 0, FAILURE};
/******************************************************************************/
struct dynamic_vector
{
	void *array_of_elems;
	size_t max_num_of_elem;
	size_t size_of_elem;
	size_t current_num_of_elem;
	size_t grow_factor;
};
/******************************************************************************/
dynamic_vector_ty *DynamicVectorCreate(size_t size_of_element,
														 size_t num_of_elements)
{
	dynamic_vector_ty *user_vector = NULL;
	/*Allocate memory for the entire stack.*/
	user_vector = (dynamic_vector_ty *)malloc(sizeof(dynamic_vector_ty));

	if (NULL == user_vector)
	{
		perror(strerror(errno));
		return NULL;
	}
	/*Initialize and allocate memory for the void pointer array_of_elems.*/
	user_vector->current_num_of_elem = 0;
	user_vector->size_of_elem = size_of_element;
	user_vector->max_num_of_elem = num_of_elements;
	/*Set the desired grow factor*/
	user_vector->grow_factor = 2;
	user_vector->array_of_elems = malloc(sizeof(char) *
									       (num_of_elements * size_of_element));
	
	/*Check the memory allocation for the array_of_elems */
	if (NULL == user_vector->array_of_elems)
	{
		perror(strerror(errno));
		free(user_vector);
		user_vector = NULL; 
		return NULL;
	}
	
	return user_vector;
}
/******************************************************************************/
void DynamicVectorDestroy(dynamic_vector_ty *vector)
{
	/*Free the allocated memory.*/
	assert(vector);
	free(vector->array_of_elems);
	vector->array_of_elems = NULL;
	
	free(vector);
 	vector = NULL;
}
/******************************************************************************/
int DynamicVectorPushback(dynamic_vector_ty *vector, void *element)
{
	/*Initialize and allocate memory for the void pointer array_of_elems.*/
	char *ptr_to_push_to = NULL; 
	size_t curr_num_of_elem = vector->current_num_of_elem;
	size_t size_of_elem = vector->size_of_elem;
	size_t max_num_of_elem = vector->max_num_of_elem;
	int status = 0;
	
	assert(vector);
	assert(element);
	/*If there is not enough memory for storing the added element.*/
	if(curr_num_of_elem == max_num_of_elem)
	{
		/*Add memory with multiplication by the grow factor.*/
		status = VectorReserve
						  (vector, vector->max_num_of_elem*vector->grow_factor);
	}
	ptr_to_push_to = (char *)vector->array_of_elems;
	ptr_to_push_to += curr_num_of_elem*size_of_elem;
	/*Copy bytes to the pushing memory location.*/
	memcpy((char *)ptr_to_push_to, element, size_of_elem);
	++vector->current_num_of_elem;

	return status;
}
/******************************************************************************/
void DynamicVectorPopBack(dynamic_vector_ty *vector)
{	
	/*Perform memory shrinking if needed*/
	if(vector->current_num_of_elem == 
									vector->max_num_of_elem/vector->grow_factor)
	{
		VectorShrink(vector);
	}
	--vector->current_num_of_elem;
}
/******************************************************************************/
void *DynamicVectorGetAccessToElement(const dynamic_vector_ty *vector,
							size_t index)
{
	size_t return_index = vector->size_of_elem*index;
	char *ptr_to_index = vector->array_of_elems;
	/*Return the element at the desired index.*/
	ptr_to_index += return_index;
	return ptr_to_index;  
}
/******************************************************************************/
size_t DynamicVectorCurrentSize(const dynamic_vector_ty *vector)
{
	return vector->current_num_of_elem;
}
/******************************************************************************/
size_t DynamicVectorCapacity(const dynamic_vector_ty *vector)
{
	return vector->max_num_of_elem;
}
/******************************************************************************/
int VectorReserve(dynamic_vector_ty *vector, size_t new_capacity)
{
	size_t size_of_elem = vector->size_of_elem;
	vector->array_of_elems = realloc(vector->array_of_elems, 
													 new_capacity*size_of_elem);
	/*If the allocation of new_capacity memory has been failed.*/	
	if(errno)
	{
		perror(strerror(errno));
		return FAILURE;
	}
	vector->max_num_of_elem = new_capacity;
	return SUCCESS;
}
/******************************************************************************/
int VectorShrink(dynamic_vector_ty *vector)
{
	size_t max_num_of_elem = vector->max_num_of_elem;
	size_t grow_factor = vector->grow_factor;
	size_t size_of_elem = vector->size_of_elem;
	
	vector->array_of_elems = realloc(vector->array_of_elems, 
							        (max_num_of_elem/grow_factor)*size_of_elem);
	/*If the re-allocation of new_capacity memory has been failed.*/						        
	if (errno)
	{
		perror(strerror(errno));
		return FAILURE;	
	}	
	
	vector->max_num_of_elem /= vector->grow_factor;
	return SUCCESS;
}

#if 0
/*******************************************************************************
 * Project: Data Structures - Dynamic Vector
 * Date: 09/08/22
 * Name: karam Aamar
 * Reviewer: dana shapso
 * Version: 2.0
*******************************************************************************/

#include <stdio.h>  /* print */
#include <assert.h> /* NULL pointers check */
#include <stdlib.h> /* allocation */
#include <string.h> /* memcpy strerror */
#include <errno.h>  /* errno perror */

/*****************************************************************************/

#include "dynamic_vector.h"

/*****************************************************************************/

enum Status {SUCCESS = 0 , FAIL = 1}; 

#define GROWTH 2

/*****************************************************************************/

struct dynamic_vector
{
	void* vector_array;
	size_t size_of_ele;
	size_t num_of_ele;
	size_t curr_elem_count;
};

/*****************************************************************************/

dynamic_vector_ty *DynamicVectorCreate(size_t size_of_element,
							size_t num_of_elements)
{
	/* dynamic allocation for the the vector struct */	
	dynamic_vector_ty* vector_obj = (dynamic_vector_ty*)malloc
						(sizeof(dynamic_vector_ty));
						
	/* dynamic allocation for the array we store the values at */				
	char *ptr_vec_array = (char*)malloc(num_of_elements * size_of_element);
	
	/* check input */
	assert(num_of_elements);
	assert(size_of_element);
	
	/* check if the allocation success */
	if(NULL == ptr_vec_array )
	{
		perror(strerror(errno));
		return NULL;
	}
	
	if(NULL == vector_obj)
	{
		perror(strerror(errno));
		return NULL;
	}
	
	/* assignment the values in the struct */
	vector_obj -> vector_array = ptr_vec_array;
	vector_obj -> size_of_ele = size_of_element;
	vector_obj -> num_of_ele = num_of_elements;
	vector_obj -> curr_elem_count = 0;
	
	return vector_obj;
}
		
/*****************************************************************************/	

void DynamicVectorDestroy(dynamic_vector_ty *vector)
{
	/* free the array we store the values at */
	free(vector -> vector_array); 
	vector -> vector_array = NULL;
	
	/* free the struct */
	free(vector);	
	vector = NULL;
}
						
/*****************************************************************************/	

int DynamicVectorPushback(dynamic_vector_ty *vector, void *element)
{
	int status = FAIL;
	
	assert(vector);
	assert(element);
	
	/* if we need more place more than the allocated */	
	if((vector -> curr_elem_count) < (vector -> num_of_ele))
	{
	
		/* copy byte byte to the needed positin */
		memcpy((char *)vector -> vector_array + ((vector -> 
			       curr_elem_count) * (vector -> size_of_ele)) 
				        , element , vector-> size_of_ele);
				
		/* we added a value then increment */		
		++vector -> curr_elem_count;
		
		return SUCCESS;
	}
	else
	{
		/* we need allocation for the new elements */
		status = VectorReserve(vector, (vector -> num_of_ele) * GROWTH);
			
		if(SUCCESS == status)
		{
			/* copy byte byte to the needed positin so -1 */
			memcpy((char *)vector -> vector_array + ((vector -> 
		                curr_elem_count ) * (vector -> size_of_ele)) 
					      , element , vector-> size_of_ele);
					      
			/* one more element count */		      
			++vector -> curr_elem_count;
			
			/* now we got double the capacity so */
			vector -> num_of_ele = GROWTH * (vector -> num_of_ele);
			
			return SUCCESS; 
			
		}else
		{
				
			return FAIL;					      
		}
		
		
	}			
}

/*****************************************************************************/	

void DynamicVectorPopBack(dynamic_vector_ty *vector)
{
	int zero_value = 0;
	int * ptr = &zero_value ;
	size_t step_array = 0;
	
	assert(vector);
	
	step_array = (vector -> curr_elem_count - 1) * (vector -> size_of_ele);
	
	if(0 < (vector ->curr_elem_count))
	{
		memcpy((char *)vector -> vector_array +  step_array , ptr , 
							vector-> size_of_ele);
	}
	--vector -> curr_elem_count;
}

/*****************************************************************************/	

void *DynamicVectorGetAccessToElement(const dynamic_vector_ty *vector,
								size_t index)
{
       assert(vector);
       assert( vector -> curr_elem_count);
	
       return ((char *)vector -> vector_array + (index - 1) * 
       							vector -> size_of_ele);
}							

/*****************************************************************************/	

size_t DynamicVectorCurrentSize(const dynamic_vector_ty *vector)
{
	assert(vector);
	
	return vector -> curr_elem_count;
}

/*****************************************************************************/	

size_t DynamicVectorCapacity(const dynamic_vector_ty *vector)
{
	assert(vector);
	
	return vector -> num_of_ele;
}

/*****************************************************************************/	

int VectorReserve(dynamic_vector_ty *vector, size_t new_capacity)
{
	char *ptr_new_array;
	
	assert(vector);
	assert(vector -> curr_elem_count < new_capacity);
	
	/* dynamic allocation */
	ptr_new_array = (char*)realloc(vector -> vector_array , new_capacity);
	
	if(NULL == ptr_new_array)
	{
		perror(strerror(errno));
		return FAIL; 
	}else{
		
		/* point to the location of the new allocation */		
		vector -> vector_array = ptr_new_array;
		
		/*  increment number of elements */	
		vector -> num_of_ele = new_capacity / vector -> size_of_ele;
		
		return SUCCESS; 
	     }
}

/*****************************************************************************/	

int VectorShrink(dynamic_vector_ty *vector)
{
	char *ptr_new_array;
	
	assert(vector);
	
	/*  shrink the size by the current size */
	ptr_new_array = (char*)realloc(vector -> vector_array , 
			      vector ->curr_elem_count * vector -> size_of_ele);
	
	vector -> vector_array = ptr_new_array;	
		      
	if(NULL == ptr_new_array)
	{
		perror(strerror(errno));
		return FAIL; 
	}else{
		--vector -> num_of_ele;
		return SUCCESS; 
	     }
}

/*****************************************************************************/	
#endif
								

/*******************************************************************************
 * Project: knight tour 
 * Date: 06/11/2022
 * Name: karam
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include "knight_tour.h"
#include "bit_array.h"
/******************************************************************************/
#include <assert.h>	/*assert*/
#include <string.h>	/*strerro*/
#include <errno.h>	/*errno*/
#include <stdlib.h>	/*malloc, free*/
#include <stdio.h>	/*perror*/
#include <stddef.h>  /*size_t*/
#include <time.h> /*time*/
/******************************************************************************/

typedef enum status{FAIL = 0, SUCCESS = 1}status_ty;
enum {SWAP = 1, NO_SWAP = 0, DIRECTIONS = 8, SIZE_OF_ARRAY = 8, INVALID_OPTION = 9, BOARD_SIZE = 64, INVALID_POS = 64};
/******************************** helper function *****************************/
static int KnightTourRec(bit_arr_ty board_, unsigned char curr_pos_, 
                                            size_t latest, unsigned char* tour);
static void NextPositionIMP(u_char curr_pos_, u_char* positions_arr, u_char* num_of_options);

static size_t IsLegalPosIMP(bit_arr_ty board_, int row_, int col_);
static size_t NumOfOptionsIMP(bit_arr_ty board_, size_t position);
static size_t GetRowIndexIMP(size_t position);
static size_t GetColIndexIMP(size_t position);
static unsigned char GetPositionFromRowColIMP(size_t row_, size_t col_);
static int IsVisitedMapFullIMP(bit_arr_ty board_);

static void SortArrIMP(u_char* arr_to_sort, u_char*  positions_arr, size_t arr_size);
static void SwapFunc(u_char* num1 , u_char* num2);
static void InitSetupLutIMP(u_char steps[][DIRECTIONS], bit_arr_ty board_);

static u_char WhichPosIMP(bit_arr_ty board_, int dir_index, size_t curr_pos_);
/******************************************************************************/
int KnightTour(unsigned char tour[64], unsigned char start)
{
    /* define time_out */
    size_t timout = time(NULL) + 300;

    /* get the row and col for starting point */
    int row = GetRowIndexIMP(start);
    int col = GetColIndexIMP(start);

    /* define bit_array board - type size_t 64 bits */
    bit_arr_ty board = 0;
   
    /* check if start_ is a legal position */
    if(!IsLegalPosIMP(board, row, col))
    {
        return 1; /*fail*/
    }
    
    /* call recursive function */
    return KnightTourRec(board, start, timout, tour);
}
/******************************************************************************/
static int KnightTourRec(bit_arr_ty board_, u_char curr_pos_, 
                                             size_t latest, u_char* tour)
{
    int i = 0;
    int status = 0;

    /*define array for positions*/
    u_char positions_arr[DIRECTIONS] = {0};

    /*define array for num of options for each position*/
    u_char num_of_options[DIRECTIONS] = {0};

    /* check if we passed limited time */
    if((size_t)time(NULL) > latest)
    {
        return 1;/*fail*/ 
    } 
    /*set on */
    board_ = BitArraySetOn(board_, (size_t)curr_pos_);

    /* check if we have a full board */
    if(~(bit_arr_ty)0 == board_)
    {
        *tour = curr_pos_;
        return 0;/*success*/
    }
    /*call NextPositionIMP & get sorted arrays */
    NextPositionIMP(curr_pos_, positions_arr, num_of_options);

    /* loop num of steps */
    while(i < DIRECTIONS && positions_arr[i] != INVALID_POS)
    {
        status = KnightTourRec(board_, positions_arr[i], latest, tour);

        /*if success*/
        if(0 == status)
        {
            /*set current to tour array*/
            *tour = curr_pos_;
            return 0;
        }
        ++i;
    }
    /*fail*/
    return 1;
}
/******************************************************************************/
/* return the sorted array */
static void NextPositionIMP(u_char curr_pos_, u_char* positions_arr, u_char* num_of_options)
{
    static u_char steps[BOARD_SIZE][DIRECTIONS];
    static int init_status = 0;
    bit_arr_ty board = 0;

    int i = 0;

    if(!init_status)
    {
        InitSetupLutIMP(steps, board);
        init_status = 1;
        /*debug note: init works*/
    }

    for(i = 0; i < DIRECTIONS; ++i)
    {
        /* set relevant position in the array */
        positions_arr[i] = steps[curr_pos_][i];

        /* set number of option for each possible position */
        /*TODO: if i have position 64 i have to take care of it before i send it */
        
        num_of_options[i] = NumOfOptionsIMP(board, positions_arr[i]);
        /* check if the possiblty is zero then change it to INVALID_OPTION because it's a lower priority */
        if(0 == num_of_options[i])
        {
            /*invalid possiblity*/
            num_of_options[i] = INVALID_OPTION;
        }
    }
    /* sort the two arrays by num of options */
    SortArrIMP(num_of_options, positions_arr, DIRECTIONS);
}
/******************************************************************************/
static void SortArrIMP(u_char* arr_to_sort, u_char*  positions_arr, size_t arr_size)
{
    /* define variable for the satus if swapped or not */
	size_t status = SWAP , i = 0;

	/* loop untill there is nothing to swap */
	while(status)
	{
		/* set status no_swap this way if there is no*/
		status = NO_SWAP;
		/* loop & if cuurent value bigger than next swap*/ 
		for(i = 0; i < (arr_size - 1); ++i)
		{
			if(arr_to_sort[i] > arr_to_sort[i+1])
			{
				SwapFunc(arr_to_sort + i, arr_to_sort + i + 1);
                SwapFunc(positions_arr + i, positions_arr + i + 1);
				status = SWAP;
			}
		}
	}
}
/******************************************************************************/
static void InitSetupLutIMP(u_char steps[][DIRECTIONS], bit_arr_ty board_)
{
    /* define indexes */
    size_t i = 0;
    int dir_index = 0;

    for(i = 0; i < BOARD_SIZE; ++i)
    {
        for(dir_index = 0; dir_index < DIRECTIONS; ++dir_index)
        {
            steps[i][dir_index] = WhichPosIMP(board_, dir_index, i);
        }
    }
}
/******************************************************************************/
static u_char WhichPosIMP(bit_arr_ty board_, int dir_index, size_t curr_pos_)
{
    switch (dir_index)
    {
    case 0:
        if(IsLegalPosIMP(board_, GetRowIndexIMP(curr_pos_) - 1, GetColIndexIMP(curr_pos_) - 2))
        {
            return GetPositionFromRowColIMP(GetRowIndexIMP(curr_pos_) - 1 , GetColIndexIMP(curr_pos_) - 2);
        }
        else
        {
            return INVALID_POS;
        }
        break;

    case 1:
        if(IsLegalPosIMP(board_, GetRowIndexIMP(curr_pos_) - 2, GetColIndexIMP(curr_pos_) - 1))
        {
            return GetPositionFromRowColIMP(GetRowIndexIMP(curr_pos_) - 2 , GetColIndexIMP(curr_pos_) - 1);
        }
        else
        {
            return INVALID_POS;
        }
        break;

    case 2:
        if(IsLegalPosIMP(board_, GetRowIndexIMP(curr_pos_) - 2, GetColIndexIMP(curr_pos_) + 1))
        {
            return GetPositionFromRowColIMP(GetRowIndexIMP(curr_pos_) - 2 , GetColIndexIMP(curr_pos_) - 1);
        }
        else
        {
            return INVALID_POS;
        }
        break;
    
    case 3:
        if(IsLegalPosIMP(board_, GetRowIndexIMP(curr_pos_) - 1, GetColIndexIMP(curr_pos_) + 2))
        {
            return GetPositionFromRowColIMP(GetRowIndexIMP(curr_pos_) - 1 , GetColIndexIMP(curr_pos_) + 2);
        }
        else
        {
            return INVALID_POS;
        }
        break;

    case 4:
        if(IsLegalPosIMP(board_, GetRowIndexIMP(curr_pos_) + 1, GetColIndexIMP(curr_pos_) + 2))
        {
            return GetPositionFromRowColIMP(GetRowIndexIMP(curr_pos_) + 1 , GetColIndexIMP(curr_pos_) + 2);
        }
        else
        {
            return INVALID_POS;
        }
        break;
    
    case 5:
        if(IsLegalPosIMP(board_, GetRowIndexIMP(curr_pos_) + 2, GetColIndexIMP(curr_pos_) + 1))
        {
            return GetPositionFromRowColIMP(GetRowIndexIMP(curr_pos_) + 2 , GetColIndexIMP(curr_pos_) + 1);
        }
        else
        {
            return INVALID_POS;
        }
        break;
    
    case 6:
        if(IsLegalPosIMP(board_, GetRowIndexIMP(curr_pos_) + 2, GetColIndexIMP(curr_pos_) - 1))
        {
            return GetPositionFromRowColIMP(GetRowIndexIMP(curr_pos_) + 2 , GetColIndexIMP(curr_pos_) - 1);
        }
        else
        {
            return INVALID_POS;
        }
        break;
    
    case 7:
        if(IsLegalPosIMP(board_, GetRowIndexIMP(curr_pos_) + 1, GetColIndexIMP(curr_pos_) - 2))
        {
            return GetPositionFromRowColIMP(GetRowIndexIMP(curr_pos_) + 1 , GetColIndexIMP(curr_pos_) - 2);
        }
        else
        {
            return INVALID_POS;
        }
        break;

    default:
        break;
    }
}
/******************************************************************************/
static size_t IsLegalPosIMP(bit_arr_ty board_, int row_, int col_)
{
    /* check if the index is inside the range */
    if(row_ >= 0 && row_ < 8 && col_ >= 0 && col_ < 8)
    {
        
        /* check the value inside visited_map 
        if(!BitArrayGetVal(board_, GetPositionFromRowColIMP(row_, col_)))
        {
            
        } */
        return 1;  
    }
    return 0;
}
/******************************************************************************/
static size_t NumOfOptionsIMP(bit_arr_ty board_, size_t position)
{
    int i = 0;

    /* define count */
    size_t count = 0;

    /* define row and col of the position */
    int row =  0;
    int col = 0;

    /* define two arrays for positions */
    int pos_x[SIZE_OF_ARRAY] = {2, 1, 2, 1, -2, -1, -2, -1};
    int pos_y[SIZE_OF_ARRAY] = {1, 2, -1, -2, 1, 2, -1, -2};
    
    while(i < SIZE_OF_ARRAY && position < INVALID_POS)
    {
        row = GetRowIndexIMP(position) + pos_x[i];
        col = GetColIndexIMP(position) + pos_y[i];

        /* add to count legal positions */
        count += IsLegalPosIMP(board_, row, col);

        /*increment i (indexe for pos_x & pos_y )*/
        ++i;
    }
    return count;
}
/******************************************************************************/
static size_t GetRowIndexIMP(size_t position)
{
    return (position / 8);
}
/******************************************************************************/
static size_t GetColIndexIMP(size_t position)
{
    return (position % 8);
}
/******************************************************************************/
static unsigned char GetPositionFromRowColIMP(size_t row_, size_t col_)
{
    return (row_ * 8) + (col_ % 8);
}
/******************************************************************************/
static int IsVisitedMapFullIMP(bit_arr_ty board_)
{
    return (0xFFFFFFFFFFFFFFFF==(board_ & (~0)));
}
/******************************************************************************/
static void SwapFunc(u_char* num1 , u_char* num2)
{
	u_char temp = *num1;
	*num1 = *num2;
	*num2= temp;
}
/******************************************************************************/


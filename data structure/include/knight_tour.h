/******************************************************************************
Project: simple shell header
Date: 09/11/2022
Name: karam aamar
Reviewer: 
Version: 1.0
*******************************************************************************/
#ifndef __KNIGHTTOUR__
#define __KNIGHTTOUR__

typedef unsigned char u_char;

/*******************************************************************************
	Knight will start in a random position, returns 0 when time limit of 
        5 minutes hasn`t expired.
        Note: start 0 is the top left index
  *****************************************************************************/
int KnightTour(unsigned char tour[64], unsigned char start);



#endif /*__KNIGHTTOUR__*/

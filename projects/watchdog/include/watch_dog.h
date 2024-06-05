#ifndef __WATCHDOG_H_ILRD__
#define __WATCHDOG_H_ILRD__

/*******************************************************************************
* Program description: 
                creates the "watchdog" that conrolls the functunalities of the 
                calling process , the watchdog raises a signal to the process & 
                if it fails then the watch dog restart the process. 
*******************************************************************************/

/*******************************************************************************
* Function description: Create a watchdog handler and use it.
* arguments: signal interval tme between signals ,
             argv,
             tolerance_count.            
* Return val: 0 on success, 1 on failure
*******************************************************************************/ 
int MakeMeImMortal(time_t interval, size_t tolerance_count, char *argv[]);

/*******************************************************************************
* Function description: Stops the watchdog prog , and let the process die
* arguments: NULL
* Return val: 0 on success, 1 on failure
*******************************************************************************/
void LetMeDie();

#endif /* __WATCHDOG_H_ILRD__ */

/*int MakeMeImMortal(size_t time_interval, char *argv[], size_t tolerance_count);*/

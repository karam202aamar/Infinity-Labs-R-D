/******************************************************************************/
// Project: containers histo - cpp
// Date: 01.01.2023
// Author: karam 
// Reviewer: ayman
// Version: 
/******************************************************************************/
#include <iostream> //cin cout
#include <map>      //map
#include <string>   //string
#include <queue>    //queue
/******************************************************************************/
#include "histo.hpp"
/******************************************************************************/
using namespace std;//why in main 
/******************************************************************************/
void Histo()
{
    map<string, size_t> string_container;
    string buffer;
    queue<string> q;

    while(1)
    {
        getline(cin, buffer);

        if (buffer == ".")
        { 
            break; 
        };

        // increase value in map at string
        ++string_container[buffer];

        if(string_container[buffer] == 1)
        {
            q.push(buffer);
        }
    }

    while(!q.empty())
    {
        string tmp = q.front();
        q.pop();
        std::map<string, size_t>::iterator it= string_container.find(tmp);

        std::cout << tmp << ": " << it->second << std::endl;
    }
}
/******************************************************************************/


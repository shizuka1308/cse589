/**
 * @utils
 * @author  Kajol <kajol@buffalo.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This contains utilites which will be required in the whole code.
 */


#include "../include/global.h"
#include "../include/logger.h"
#include <string.h>
#include <regex>
#include <stdlib.h>
using namespace std;

bool numberOrNot(char element)
{
    bool cases = false;
    if ((element - '0' >= 0) && (element - '9' <= 0))
    {
        cases = true;
    }
    switch (cases)
    {
    case false:
        return false;
        break;
    case true:
        return true;
        break;
    }
}

//reference https://www.tutorialspoint.com/validate-ip-address-in-cplusplus
vector<string> splitting(const string& words, char delimitor){
   auto ikea = 0;
   vector<string> listings;
   auto pos = words.find(delimitor);
   while (pos != string::npos){
      listings.push_back(words.substr(ikea, pos - ikea));
      ikea = ++pos;
      pos = words.find(delimitor, pos);
   }
   listings.push_back(words.substr(ikea, words.length()));
   return listings;
}

bool numberChecking(const string& words){
   return !words.empty() &&
   (words.find_first_not_of("[0123456789]") == std::string::npos);
}

int ipValidOrNot(string ipAddress)
{
    vector<string> lisitngs = splitting(ipAddress, '.');
   if (lisitngs.size() != 4)
      return 0;
   for (string shabad : lisitngs){
      if (!numberChecking(shabad) || stoi(shabad) < 0 || stoi(shabad) > 255)
         return 0;
   }
   return 1;
}

int fsize(FILE *filepart)
{
    float previous = ftell(filepart);
    fseek(filepart, 0L, SEEK_END);

    float currPos = ftell(filepart);
    fseek(filepart, previous, SEEK_SET);

    return currPos;
}

int convertStringToInt(string s)
{
    int size = s.length();
    float result = 0;

    char arrauy[size + 1];

    strcpy(arrauy, s.c_str());
    result = atoi(arrauy);
    return result;
}

vector<string> breakString(const string s, const string &seperator)
{
    vector<string> answer;
    int m = seperator.size();
    int size = s.length();
    int result = 0;

    char arrauy[size + 1];

    strcpy(arrauy, s.c_str());
    char sep[m + 1];

    strcpy(sep, seperator.c_str());
    char *ptr;
    ptr = strtok(arrauy, sep);
    while (ptr != NULL)
    {
        answer.push_back(ptr);
        ptr = strtok(NULL, " , ");
    }
    return answer;
}

int portValidOrNot(string portNo)
{
    uint  iterator = 0;
    if(iterator < portNo.length()){
    do
    {
        if (!numberOrNot(portNo[iterator]))
            return 0;
        iterator++;
    }while(iterator < portNo.length());
    }
    uint tmpPort = convertStringToInt(portNo);
    if (tmpPort >= 1024)
    {
        if (tmpPort <= 49151)
        {
            return 1;
        }
    }

    return 0;
}

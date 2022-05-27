#include <stdio.h>
#include "Utils.h"


int NewRandomNumber(vector<int> *permissibleValues){
    
    int randomNumber; 
    
    int max = permissibleValues->size();
    
    if(max == 0) return -1;

    randomNumber = rand() % max;   
        
    return permissibleValues->at(randomNumber);
}

void DefinePosition(float &sx, float &sy, float sh, float sw, float xOffset, float yOffset, int row, int column){
    
    sx = sw*column + xOffset;
    sy = sh*row + yOffset;
}

void itoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}

void reverse(char s[])
{
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}

int strlen(char s[])
{
    char * ptr = s;
    int len = 0;
    
    while(( * ptr ++) != 0) len ++;
    
    return len;

}
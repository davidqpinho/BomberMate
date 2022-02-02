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
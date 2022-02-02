#ifndef __UTILS_H_
#define __UTILS_H_

    #include <cstdlib> 
    #include <ctime>
    #include <vector>

    using namespace std;

    int NewRandomNumber(vector<int> *permissibleValues);
    void DefinePosition(float &sx, float &sy, float sh, float sw, float xOffset, float yOffset, int row, int column);
    
    
#endif
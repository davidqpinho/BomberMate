#ifndef __UTILS_H_
#define __UTILS_H_

    #include <cstdlib> 
    #include <ctime>
    #include <vector>
    #include <string>
    #include <fstream>
    #include <iostream>

    using namespace std;

    int  NewRandomNumber(vector<int> *permissibleValues);
    void DefinePosition(float &sx, float &sy, float sh, float sw, float xOffset, float yOffset, int row, int column);
    void itoa(int n, char s[]);
    void reverse(char s[]);
    int  strlen(char s[]);
    void AppendKeyToFile(string key, int value);
    void CreateFile();
    string GetFileContent();
    int  ReadIntFromTag(string tag);    
    bool CheckIfFileExists();
    
#endif
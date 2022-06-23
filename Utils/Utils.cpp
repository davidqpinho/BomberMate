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

void AppendKeyToFile(string key, int value){

    fstream file;

    file.open("Save.txt", ios::app);
    
    if (file.is_open()){
        file << key + "::"+ to_string(value) + "$$\n";
        file.close();
    }

}

void CreateFile(){
 
 fstream file;

 file.open("Save.txt", ios::out);
 
 if (file.is_open()){
    file << ":::::::SAVE:::::::\n";
    file.close();
 }

}

string GetFileContent(){
    
    fstream file;
    string ret = "";

    file.open("Save.txt", ios::in);
    
    if (file.is_open()){
        
        string line;
        
        while(getline( file, line)) ret += line;        

        file.close();
    }

    return ret;
}

int  ReadIntFromTag(string tag){
    
    string text = GetFileContent();
    int initialPos = text.find(tag);
    int finalPos   = text.find("$$",initialPos);
    int payloadStart = initialPos + tag.length() + 2;

    string payload = text.substr(payloadStart, finalPos - payloadStart);
    cout << tag + "\n";
    cout << payload + "\n";
    return stoi( payload );
}

bool CheckIfFileExists(){
    
    fstream fileStream;

    fileStream.open("Save.txt");
    
    return !fileStream.fail(); 
        
}

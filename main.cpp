#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

struct KeyFinderHelper
{
    int positionInString;
    int sizeOfKey;
};


vector<KeyFinderHelper>  parseData(string data,string keyReq);
void printValues(vector<KeyFinderHelper> ptrOfchar,string toCheckAgainst);
char *strncpy( char *dest,  char *src, size_t n);

int main(){


string t ="{\"wawa\":{\"key\":178},\"wvawa\":{\"kehy\":14},\"wawa\":{\"keyt\":\"mama\"}}";
auto vectorofkeyys= parseData(t,"\"key\"");

printValues(vectorofkeyys,t);

std::cout<<"from jsonparser";

    return 0;
}

vector<KeyFinderHelper>  parseData(string data,string keyReq){
vector<KeyFinderHelper> ptrOfchar;
for (size_t i = 0; i < data.length(); i++)
{
    char* array= new char[keyReq.length()];

  auto where = strncpy(array,&data[i],keyReq.length());
  int equeal= strcmp (array, keyReq.c_str());
  if (equeal==0)
  {
      cout<<"found the location of the key in "<< i<<endl;
      KeyFinderHelper type;
      type.positionInString=i;
      type.sizeOfKey=keyReq.length();

      ptrOfchar.push_back(type);
  }
  

}
return ptrOfchar;



}



void printValues(vector<KeyFinderHelper> ptrOfchar,string toCheckAgainst){

  for (size_t i = 0; i < ptrOfchar.size(); i++)
  {
    int whereinstring =ptrOfchar.at(i).positionInString;

      auto pos=&toCheckAgainst[whereinstring];

        pos+=ptrOfchar.at(i).sizeOfKey;
        pos+=1;
     
      //recording the value
      int numberOfQuotes=0;
      while (numberOfQuotes<2&&*pos!='}')
      {
          //checking if startign quotes
          if (*pos=='\"')
          {
              numberOfQuotes++;
          }
          cout<<*pos;
            pos+=1;
          
      }
      cout<<'\n';
      

  }
  


}






      char *
           strncpy(char *dest,  char *src, size_t n)
           {
               size_t i;

               for (i = 0; i < n && src[i] != '\0'; i++)
                   dest[i] = src[i];
               for ( ; i < n; i++)
                   dest[i] = '\0';

               return dest;
           }
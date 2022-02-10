#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "JsonBuilder.h"
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

string vc="{}";
string t ="{\"wxawa\":{\"keyt\":178,\"keyzztc\":true},\"arracyman\":[\"cc\",\"ccz\",1,\"ccvb\",\"cxz\"],\"wow\":false,\"arrayzxman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}],\"arrayman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}],\"wvawa\":{\"keytShloimFS\":\"}\"},\"wawa\":{\"keyt\":\"mama\"}}";
string f =/*"{\"wvawa\":{\"keytShloimFS\":\"}\"},*/"{\"arrayman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}],\"arrayman\":[\"cc\",\"ccz\"1,\"ccvb\",\"cxz\"]}";
JSONString2JsonElement js2e;
int i =0;
int calls =0;
js2e.refToInt=0;
JSONELEMENT* father= new JSONELEMENT();
father->entireValuAsString=t;






auto ff =js2e.FindJsonKey(father->entireValuAsString,i,father,js2e.refToInt);
  js2e.FixJsonElementsValues(father);
cout<<father->str();

auto vectorofkeyys= parseData(t,"\"keyt\"");

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
      while (numberOfQuotes<2)
      {
          if ((*pos=='}')&&numberOfQuotes>0)
          {
            /* code */
            break;
            
          }
          


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






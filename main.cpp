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



int main()
{

  string vc = "{}";
  string t = "{\"wxawa\":{\"keyt\":178,\"keyzztc\":true},\"arracyman\":[\"cc\",\"ccz\",1,\"ccvb\",\"cxz\"],\"wow\":false,\"arrayzxman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}],\"arrayman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}],\"wvawa\":{\"keytShloimFS\":\"}\"},\"wawa\":{\"keyt\":\"mama\"}}";
  string f = /*"{\"wvawa\":{\"keytShloimFS\":\"}\"},*/ "{\"arrayman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}],\"arrayman\":[\"cc\",\"ccz\"1,\"ccvb\",\"cxz\"]}";
  JSONString2JsonElement js2e;



  auto Object_= js2e.ParsedObject(t);
  //cout << Object_->str();
    cout<<Object_->elmenetsptr.at(0)->str();
 

  std::cout << "from jsonparser";

  return 0;
}


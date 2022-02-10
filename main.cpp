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
 
  JSONBuilder jb;
  auto obj=jb.R_create_json_object("wowowsuperKey");
  auto fc= jb.R_create_Key_value("hello",3.4555);
  auto fcx= jb.R_create_Key_value("hello",4555);
  jb.R_add_to_object(obj,fc);
  jb.R_add_to_object(obj,fcx);
  auto master = jb.R_create_json_object("mize");
  jb.root= new JSONELEMENT();
  jb.R_add_to_object(jb.root,obj);
  cout<<'\n'<<jb.str();





  std::cout << "from jsonparser";

  return 0;
}




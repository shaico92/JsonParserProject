#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include "JsonBuilder.h"
using namespace std;

struct KeyFinderHelper
{
  int positionInString;
  int sizeOfKey;
};
string readFileIntoString(const string& path);

int main()
{

  string vc = "{}";
  auto dd=readFileIntoString("C:/VSCode/JsonParserProject/data.txt");
  string t = "{\"wxawa\":{\"keyt\":178,\"keyzztc\":true},\"arracyman\":[\"cc\",\"ccz\",1,\"ccvb\",\"cxz\"],\"arrayzxman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}],\"wow\":false,\"arrayman\":[{\"cc\":{\"ccz\":false}},{\"ccvb\":\"cxz\"}],\"wvawa\":{\"keytShloimFS\":\"}\"},\"wawa\":{\"keyt\":\"mama\"}}";
  string f = /*"{\"wvawa\":{\"keytShloimFS\":\"}\"},*/ "{\"arrayman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}],\"arrayman\":[\"cc\",\"ccz\"1,\"ccvb\",\"cxz\"]}";
  JSONString2JsonElement js2e;

  auto Object_ = js2e.ParsedObject(dd);
  //cout << Object_->str();

  JSONBuilder jb;
  auto obj = jb.R_create_json_object("wowowsuperKey");
  auto fc = jb.R_create_Key_value("hello", 3.5);
  auto fcx = jb.R_create_Key_value("helclo", 4555);
  jb.R_add_to_object(obj, fc);
  jb.R_add_to_object(obj, fcx);
  cout << obj->str();
  auto master = jb.R_create_json_object("mize");
  auto arrnokey = jb.R_create_noneKey_array("noKeyArr");
  auto cvcv = jb.R_create_nokey_value("false");
  auto ccd = jb.R_create_nokey_value("true");
  ;
  jb.R_add_to_object(arrnokey, cvcv);
  jb.R_add_to_object(arrnokey, ccd);
  jb.R_add_to_object(master, arrnokey);
  jb.R_add_to_object(master, obj);

  jb.R_bundle(master);

  //auto res =js2e.FindJSONElementByKey(master,"false");

  auto res =js2e.FindJSONElementByKeyUnderSpecificKeyHirerchy(Object_,"cc","arrayman");
  cout << '\n'
       << jb.str();

  std::cout << "from jsonparser";

  return 0;
}

string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
}
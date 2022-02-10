#pragma once
#include "JsonBuilder.h"

using namespace std;

#pragma region JsonElement




JSONELEMENT::JSONELEMENT() {};

void JSONELEMENT::HandleType(JSONELEMENT& element) {
	switch (element.type)
	{
	case typeOfJsonElement::_val:

			break;
	case typeOfJsonElement::_NoKeyArray:

			break;
	case typeOfJsonElement::_object:

			break;
	default:
		break;
	}
}


JSONELEMENT::JSONELEMENT(const std::string key, const std::string value,const typeOfJsonElement type)
	:key(key), value(value),type(type),  fatherStart("{"), fatherEnd("}"), indentsize(2){
	//fatherStart = "{";
//	fatherEnd = "}";

};
JSONELEMENT::JSONELEMENT(const std::string key,  const typeOfJsonElement type)
	:key(key),type(type) {


};
void JSONELEMENT::append(std::ostringstream& oss, std::vector<JSONELEMENT*> elmenets)const {
	//not cpp11 standard
	//for (const auto& e : elmenets) {
	// 
	int i = 0;
	// 
	//this is cpp11 standard

	#if CPPSTD==201103L||CPPSTD==199711 // std11 
	
	for each(auto& e in elmenets)
	{
		oss << '{' << endl;
		if (e->partOfArray ==true)
		{
			
		}
		oss << "\"" << e->key << "\"";
		oss << ":" << endl;
	
		if (e->type==typeOfJsonElement::_object&&e->elmenetsptr.size()>0)
		{
		
			oss << '{' << endl;
		
			append(oss, e->elmenetsptr);


			oss << '}' << endl;
			
			if (i == elmenets.size() - 1)
			{

			}
			else {
				oss << "," << endl;
			}
		}
		else if (e->type == typeOfJsonElement::_ObjectsArray) {
		
			oss << '[' << endl;
		
			append(oss, e->elmenetsptr);


			oss << ']' << endl;
			oss << '}' << endl;
			if (i == elmenets.size() - 1)
			{
			
			}
			else {
				oss << "," << endl;
			}
		
		}
		else {

			oss << "\"" << e->value << "\"";
			if (e->partOfArray)
			{
				oss << "}";
			}
			if (i == elmenets.size() - 1)
			{

			}
			else {
				oss << "," << endl;
			}
		}
		++i;

	}
	
	#endif 
	
	#if CPPSTD==201402L //std 14

	
	
	for(auto& e : elmenets)
	{
		oss << '{' << endl;
		if (e->partOfArray ==true)
		{
			
		}
		oss << "\"" << e->key << "\"";
		oss << ":" << endl;
	
		if (e->type==typeOfJsonElement::_object&&e->elmenetsptr.size()>0)
		{
		
			oss << '{' << endl;
		
			append(oss, e->elmenetsptr);


			oss << '}' << endl;
			
			if (i == elmenets.size() - 1)
			{

			}
			else {
				oss << "," << endl;
			}
		}
		else if (e->type == typeOfJsonElement::_NoKeyArray) {
		
			oss << '[' << endl;
		
			append(oss, e->elmenetsptr);


			oss << ']' << endl;
			oss << '}' << endl;
			if (i == elmenets.size() - 1)
			{
			
			}
			else {
				oss << "," << endl;
			}
		
		}
		else {

			oss << "\"" << e->value << "\"";
			if (e->partOfArray)
			{
				oss << "}";
			}
			if (i == elmenets.size() - 1)
			{

			}
			else {
				oss << "," << endl;
			}
		}
		++i;

	}
	
	#endif // std11 
	
	
	
}

string JSONELEMENT::str(int indent)const
{
	ostringstream oss;
	
	string i(indentsize * indent, ' ');

	append(oss, elmenetsptr);

	
	return oss.str();
	//}

}




#pragma endregion

#pragma region JsonBuilder



JSONBuilder::JSONBuilder() {

	root.fatherStart = "{";
	root.fatherEnd = "}";
};



JSONELEMENT JSONBuilder::create_array(std::string key, std::vector<JSONELEMENT>& sons) {


	auto e = createobjectptr(key, typeOfJsonElement::_NoKeyArray);
	
	for (size_t i = 0; i < sons.size(); i++)
	{
		sons[i].partOfArray = true;
	}


	
	

	return *e;
}
JSONELEMENT* JSONBuilder::create_array(std::string key, std::vector<JSONELEMENT*> sons) {


	auto e = createobjectptr(key, typeOfJsonElement::_NoKeyArray);

	if (sons.size()<1)
	{
		return e;
	}
	#if  CPPSTD==201103L||CPPSTD==199711 // std11 

	for each(auto& son in sons)
	{
		son->partOfArray = true;
		e->elmenetsptr.emplace_back(son);
	}
	//root.elmenetsptr.push_back(e);
	#endif
	#if CPPSTD==201402L // std14 

	for (auto& son : sons)
	{
		son->partOfArray = true;
		e->elmenetsptr.emplace_back(son);
	}
	//root.elmenetsptr.push_back(e);
	#endif

	return e;
}
JSONELEMENT* JSONBuilder::create_array(JSONELEMENT* ptrTojsonElm, std::vector<JSONELEMENT*> sons) {

	ptrTojsonElm->type = typeOfJsonElement::_NoKeyArray;
	//auto e = createobjectptr(key, typeOfJsonElement::_array);


	/*for (auto& son : sons)
	{
		son->partOfArray = true;
		ptrTojsonElm->elmenetsptr.emplace_back(son);
	}*/
	for (size_t i = 0; i < sons.size(); i++)
	{
		sons[i]->partOfArray = true;
		ptrTojsonElm->elmenetsptr.emplace_back(sons[i]);
	}

	//root.elmenetsptr.push_back(ptrTojsonElm);

	return ptrTojsonElm;
}
JSONELEMENT* JSONBuilder::add_to_existing_object(JSONELEMENT* ptrTojsonElm, std::vector<JSONELEMENT*> sons) {

	ptrTojsonElm->type = typeOfJsonElement::_NoKeyArray;
	//auto e = createobjectptr(key, typeOfJsonElement::_array);


	/*for each(auto& son in sons)
	{
		son->partOfArray = true;
		ptrTojsonElm->elmenetsptr.emplace_back(son);
	}*/
	for (size_t i = 0; i < sons.size(); i++)
	{
		sons[i]->partOfArray = true;
		ptrTojsonElm->elmenetsptr.emplace_back(sons[i]);
	}
	//root.elmenetsptr.push_back(ptrTojsonElm);

	return ptrTojsonElm;
}
JSONELEMENT* JSONBuilder::add_to_existing_object(JSONELEMENT* ptrTojsonElm, JSONELEMENT* son) {

	ptrTojsonElm->type = typeOfJsonElement::_NoKeyArray;
	//auto e = createobjectptr(key, typeOfJsonElement::_array);


	
		son->partOfArray = true;
		ptrTojsonElm->elmenetsptr.emplace_back(son);
	
	//root.elmenetsptr.push_back(ptrTojsonElm);

	return ptrTojsonElm;
}


JSONELEMENT JSONBuilder::createobjectWithValue(string key, string val,typeOfJsonElement type ) {

	auto e =JSONELEMENT(key, val, type);
	//JSONELEMENT e{ key,val,valueIsObject };
	
	return e;
}

JSONELEMENT* JSONBuilder::createobjectWithValueptr(string key, string val, typeOfJsonElement type) {

	auto e =new JSONELEMENT(key, val, type);
	//JSONELEMENT e{ key,val,valueIsObject };

	return e;
}
JSONELEMENT* JSONBuilder::createobjectWithNoValue(string key, typeOfJsonElement type) {

	auto e = new JSONELEMENT(key, type);
	//JSONELEMENT e{ key,val,valueIsObject };

	return e;
}

JSONELEMENT* JSONBuilder::createobjectptr(string key, typeOfJsonElement type) {

	auto e =new JSONELEMENT(key, type);
	//JSONELEMENT e{ key,valueIsObject };
	//root.elmenetsptr.push_back(e);
	return e;
}

JSONELEMENT* JSONBuilder::findByKey(string key) {

	for (size_t i = 0; i < root.elmenetsptr.size(); i++)
	{
		if (root.elmenetsptr[i]->key== key)
		{
			return root.elmenetsptr[i];
		}
		
		
	}
	return	findByKey(key);
}






void JSONBuilder::add_Complex( JSONELEMENT* elm) {
	
	root.elmenetsptr.push_back(elm);
}

void JSONBuilder::print() {
	cout << root.str();
}
string JSONBuilder::str() {
	
	return root.str(); }

string JSONBuilder::str(JSONELEMENT& elementToChoose) {
	return elementToChoose.str();
}


#pragma endregion



#pragma region JSONString2JsonElement
JSONELEMENT* JSONString2JsonElement::FindJsonKey(std::string json,int i,JSONELEMENT* jsonElementFather,int& refrenceIndexInRootJsonString) {

i++;


	//finding the key

	


	string theKey = "";





	while (i<json.length()-1)
	{
		if (json[i] == '\"')
		{
			break;
		}
	
	
		i++;


	}
	//i is now the index of the opening \" in the json string
	i++;

	while (i < json.length() - 1)
	{
		
		if (json[i] == '\"')
		{
			break;
		}
		theKey += json[i];

		i++;


	}
	//getting the index to ":" position in key value structure
	i++;
	
	//starting to create the object
	JSONELEMENT* je = new JSONELEMENT();
	//here already have the key
	je->key = theKey;
i++;
	je->type = FindValueType(json, i);

	
	je->entireValuAsString=FindKeyValueEnd(i,json,je);
	

	if (je->type==typeOfJsonElement::_object)
	{
jsonElementFather->elmenetsptr.push_back(FindJsonKey( je->entireValuAsString,  0,je,refrenceIndexInRootJsonString ));
		
	}
		if (je->type==typeOfJsonElement::_val)
	{
jsonElementFather->elmenetsptr.push_back(je);

			
		
	}
			if (je->type==typeOfJsonElement::_NoKeyArray)
	{
jsonElementFather->elmenetsptr.push_back(je);

			
		
	}
				if (je->type==typeOfJsonElement::_ObjectsArray)
	{

//{\"arrayman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}]}
	

jsonElementFather->elmenetsptr.push_back(je);

			
		
	}
	
	


refrenceIndexInRootJsonString=i+je->entireValuAsString.length();
			if (json[refrenceIndexInRootJsonString]==',')
			{
				
				FindJsonKey( jsonElementFather->entireValuAsString,  refrenceIndexInRootJsonString,jsonElementFather,refrenceIndexInRootJsonString );
			}

	
	return jsonElementFather;
}
 void JSONString2JsonElement::FixJsonElementsValues(JSONELEMENT* father)
 {

	 if (father->elmenetsptr.size()>0)
	 {
		for (size_t i = 0; i < father->elmenetsptr.size(); i++)
		{
			if (father->elmenetsptr.at(i)->type==typeOfJsonElement::_val)
			{
				father->elmenetsptr.at(i)->value=father->elmenetsptr.at(i)->entireValuAsString;
				SetValueType(father->elmenetsptr.at(i));
				cout<<"key : "<< father->elmenetsptr.at(i)->key<<" type is :"<< father->elmenetsptr.at(i)->valueType<<" value : "<<father->elmenetsptr.at(i)->entireValuAsString<<'\n';
				
				continue;
			}
				if (father->elmenetsptr.at(i)->type==typeOfJsonElement::_NoKeyValue)
			{
				SetValueType(father->elmenetsptr.at(i));
				cout<<"no key value : "<< father->elmenetsptr.at(i)->value<<'\n';
				
				continue;
			}
			
			
			
				FixJsonElementsValues( father->elmenetsptr.at(i));
			
			
		}
		
		

	 }
	 
	 
	 

	return; 
 }

JSONELEMENT* JSONString2JsonElement::FindJsonValue(std::string json, int &i, JSONELEMENT* element) {
	
	while (true)
	{
		if (element->type == typeOfJsonElement::_object)
		{
			//handle object
		}
		if (element->type == typeOfJsonElement::_NoKeyArray)
		{
		// handle array
		}
		if (element->type == typeOfJsonElement::_val)
		{
			//handle plain value


			if (json[i] == '\"') {
				i += 1;
				//string value
				while (json[i] != '\"')
				{

					
					cout << json[i];
					element->value += json[i];;
					i += 1;
				}
				i += 1;
				break;
			}
			else {

				while (json[i] != '}')
				{

					cout << json[i];
					element->value += json[i];
					i += 1;
				}
				i += 1;
				break;
			}




		}

		//return typeOfJsonElement::_val;
	}

	return element;

}
typeOfJsonElement JSONString2JsonElement::FindValueType(std::string json, int indexInString) {
	//moving the index to pass the ":" in the string
	
	while (true)
	{
		if (json[indexInString]=='[')
		{
			indexInString++;
			if (json[indexInString]=='{')
			{
				return typeOfJsonElement::_ObjectsArray;
			}
			
			return typeOfJsonElement::_NoKeyArray;
		}
		if (json[indexInString] == '{')
		{
			return typeOfJsonElement::_object;
		}
		return typeOfJsonElement::_val;
	}
}



string JSONString2JsonElement::FindKeyValueEnd(int index,string json,JSONELEMENT* theObjectSoFar) {
	

	int count=0;
	int startIndex=0;
startIndex= int(index);
	//finding the key


	string retString="";

	//if its an array of objects
	if (theObjectSoFar->type==typeOfJsonElement::_ObjectsArray){
		cout<<"\nobjects array";		
		
		//{\"arrayman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}]}
		string theCurrentJson="";
	int AnotherCounterForParentethees=0;
while (index<json.length())
	{
		if (json[index]=='\"'&&AnotherCounterForParentethees>0)
		{
			AnotherCounterForParentethees--;
		}
		else if (json[index]=='\"')
		{
			AnotherCounterForParentethees++;
		}
			if(AnotherCounterForParentethees<1)
			
			{

	if (json[index]=='[')
		{
			count++;
		}
		if (json[index]==']')
		{
			count--;
		}
		if (count==0)
		{
	theCurrentJson+=json[index];
			break;
		}



			}

	theCurrentJson+=json[index];
		index++;


	}

// in this loop im dividing the array to json objects and activating the find json key function on them


	int findex=1;
int endIndex=0;
int pairStartIndex=0;
int stringBracketsCounter=0;
int secondCounter=0;
vector<string> vectorOfJsonObjectsAsStrings;
while (findex<theCurrentJson.length()-1)
{
  	if (theCurrentJson[findex]=='\"'&&stringBracketsCounter>0)
		{
			stringBracketsCounter--;
		}
		else if (theCurrentJson[findex]=='\"')
		{
			stringBracketsCounter++;
		}
			if(stringBracketsCounter<1)
			
			{

	if (theCurrentJson[findex]=='{')
		{
        if (secondCounter==0)
        {
         pairStartIndex=findex;
         secondCounter++;
        }
        
			count++;
		}
		if (theCurrentJson[findex]=='}')
		{
			count--;
		}




			}


	
		findex++;
    		if (count==0&&theCurrentJson[findex]!=',')
		{

    
      


      endIndex=findex;;
//auto p1 = std::make_pair(pairStartIndex, endIndex-1);
        string temp="";
  for (int i = pairStartIndex; i < endIndex; i++)
      {
       
          if (theCurrentJson[i]==','&&i+1>endIndex-1)
          {
            continue;
          }
          
        
        temp+=theCurrentJson[i];
        
        
      }
		cout<<findex;
    vectorOfJsonObjectsAsStrings.push_back(temp);
  secondCounter=0;
		}

}

#if CPPSTD==201402L // std11 
for (auto &&jsonString : vectorOfJsonObjectsAsStrings)
{
	JSONELEMENT* je= new JSONELEMENT();
	auto res =FindJsonKey(jsonString,0,theObjectSoFar,refToInt);
	cout<<res->entireValuAsString;
//	theObjectSoFar->elmenetsptr.push_back(res);
}
#endif; 
#if CPPSTD==201103L||CPPSTD==199711
for each(auto &&jsonString in vectorOfJsonObjectsAsStrings)
{
	JSONELEMENT* je= new JSONELEMENT();
	auto res =FindJsonKey(jsonString,0,theObjectSoFar,refToInt);
	cout<<res->entireValuAsString;
//	theObjectSoFar->elmenetsptr.push_back(res);
}
#endif 

return theCurrentJson;




	}
	if (theObjectSoFar->type==typeOfJsonElement::_NoKeyArray){

		string tempValue;
		int AnotherCounterForParentethees=0;
		string theCurrentJson="";
	while (index<json.length())
	{
		if (json[index]=='\"'&&AnotherCounterForParentethees>0)
		{
			AnotherCounterForParentethees--;
		}
		else if (json[index]=='\"')
		{
			AnotherCounterForParentethees++;
		}
			if(AnotherCounterForParentethees<1)
			
			{

	if (json[index]=='[')
		{
			count++;
		}
		if (json[index]==']')
		{
			count--;
		}
		if (count==0)
		{
	theCurrentJson+=json[index];
			break;
		}



			}

	theCurrentJson+=json[index];
		index++;


	}
		
		index=1;

		
		while (index<theCurrentJson.length())
	{
//  [\"na''',me\",1,5,\"f}]f\"]
		if (theCurrentJson[index]=='\"'&&AnotherCounterForParentethees>0)
		{
			
		
tempValue+=theCurrentJson[index];
AnotherCounterForParentethees--;

index++;



continue;
		}


		 if (theCurrentJson[index]=='\"'&&AnotherCounterForParentethees<1)
		{
				
		
			AnotherCounterForParentethees++;
		}
		if ((AnotherCounterForParentethees==0)&&(
		(theCurrentJson[index]==',')||
		(theCurrentJson[index]=='[')||
		(theCurrentJson[index]==']')||
		(theCurrentJson[index]=='}')||
		(theCurrentJson[index]=='{')
		))
		{
		
				if (tempValue.length()>0)
				{
				
							JSONELEMENT* je= new JSONELEMENT();
je->type=typeOfJsonElement::_NoKeyValue;
je->value=tempValue;
theObjectSoFar->elmenetsptr.push_back(je);
				
				index++;
				tempValue="";
continue;
				}

				
		}
		

	

tempValue+=theCurrentJson[index];
	
	

		
		
		
		
			index++;
	}

//after finishing loop in array


//   [\"na''',me\",6,\"f}]f\",5,1],\"keyt\":\"}\"

	return theCurrentJson;

	}
	//if its an array of values


	//if its an object
	if (theObjectSoFar->type==typeOfJsonElement::_object)
	{
		/* code */
	int stringBracketsCounter=0;
		
	while (index<json.length())
	{
		if (json[index]=='\"'&&stringBracketsCounter>0)
		{
			stringBracketsCounter--;
		}
		else if (json[index]=='\"')
		{
			stringBracketsCounter++;
		}
			if(stringBracketsCounter<1)
			
			{

	if (json[index]=='{')
		{
			count++;
		}
		if (json[index]=='}')
		{
			count--;
		}
		if (count==0)
		{

			break;
		}



			}

	
		index++;


	}
	
	}
	if (theObjectSoFar->type==typeOfJsonElement::_val)
	{
		/* code */
		
	while (index<json.length())
	{
			if (json[index]=='\"'&&count>0)
		{
			count--;
		}
		else if (json[index]=='\"')
		{
			count++;
		}
	
		// if its not zero already its probably a number 
			


		if ((json[index]=='}'||json[index]==',')&&count==0)
		{
			break;
		}
		
	
		index++;


	}
	}
//get end of value index;
		index++;
//add check if , or } and decremente index 

			if ((theObjectSoFar->type==typeOfJsonElement::_val)
		&&(json[json.length()-1]==','))
		{
			theObjectSoFar->partOfArray;
			
		}

		if ((theObjectSoFar->type==typeOfJsonElement::_val)
		&&(json[json.length()-1]==','||json[json.length()-1]=='}'))
		{
			index--;
		}
	




	for(int im=startIndex;im<index;im++)
	{
		retString+=json[im];
	}
	

	
	
index=startIndex;

	return retString;	
}


#pragma endregion

#pragma region UseFullParsing

void SetValueType(JSONELEMENT* element){
//this is for determin which type the jsonelement value is 
	int index=0;

	if (element->value[0]=='\"')
	{
		//always a string 
		element->valueType=JsonElementValueType::STRING;
		return;
	}

	
	char TrueOrFalse[5];
	string FALSE_="false";
	string TRUE_="true";
	strncpy(TrueOrFalse,&element->value[index],5);
	strcmp (TrueOrFalse, FALSE_.c_str());
	if ((strcmp (TrueOrFalse, FALSE_.c_str())==0)||
	(strcmp (TrueOrFalse, TRUE_.c_str())==0))
	{
		//always a boolean
			element->valueType=JsonElementValueType::BOOLEAN;
			return;
	}
	
		element->valueType=JsonElementValueType::INTEGER;
			return;

	
	

}

char*      strncpy(char *dest,  char *src, size_t n)
           {
               size_t i;

               for (i = 0; i < n && src[i] != '\0'; i++)
                   dest[i] = src[i];
               for ( ; i < n; i++)
                   dest[i] = '\0';

               return dest;
           }

#pragma endregion

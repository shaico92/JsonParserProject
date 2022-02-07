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
	case typeOfJsonElement::_array:

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
		else if (e->type == typeOfJsonElement::_array) {
		
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
		else if (e->type == typeOfJsonElement::_array) {
		
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


	auto e = createobjectptr(key, typeOfJsonElement::_array);
	
	for (size_t i = 0; i < sons.size(); i++)
	{
		sons[i].partOfArray = true;
	}


	
	

	return *e;
}
JSONELEMENT* JSONBuilder::create_array(std::string key, std::vector<JSONELEMENT*> sons) {


	auto e = createobjectptr(key, typeOfJsonElement::_array);

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

	ptrTojsonElm->type = typeOfJsonElement::_array;
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

	ptrTojsonElm->type = typeOfJsonElement::_array;
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

	ptrTojsonElm->type = typeOfJsonElement::_array;
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

refrenceIndexInRootJsonString=i+je->entireValuAsString.length();
			if (json[refrenceIndexInRootJsonString]==',')
			{
				
				FindJsonKey( jsonElementFather->entireValuAsString,  refrenceIndexInRootJsonString,jsonElementFather,refrenceIndexInRootJsonString );
			}

	
	return jsonElementFather;
}

JSONELEMENT* JSONString2JsonElement::FindJsonValue(std::string json, int &i, JSONELEMENT* element) {
	
	while (true)
	{
		if (element->type == typeOfJsonElement::_object)
		{
			//handle object
		}
		if (element->type == typeOfJsonElement::_array)
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
			return typeOfJsonElement::_array;
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

	

	//if its an object
	if (theObjectSoFar->type==typeOfJsonElement::_object)
	{
		/* code */

		
	while (index<json.length())
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



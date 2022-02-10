#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define CPPSTD __cplusplus 

#pragma region GeneralObjects

enum typeOfJsonElement {
	_val=0,
	_object,
	_NoKeyArray,
	_ObjectsArray,
	_NoKeyValue
};

enum JsonElementValueType {
	INTEGER=0,
	STRING,
	BOOLEAN,
	
	
};

struct JSONELEMENT {

	
	std::vector<JSONELEMENT*> elmenetsptr;
	std::string key, value;
	std::string entireValuAsString;
	bool partOfArray;
	bool valueIsObject;
	bool lastJsonInArray;
	typeOfJsonElement type;
	bool nonull;
	JsonElementValueType valueType;
	  std::string fatherStart;

	 std::string fatherEnd;

	 size_t indentsize; //= 2;

	void append(std::ostringstream& oss);


	JSONELEMENT();
	void HandleType(JSONELEMENT& element);
	
	JSONELEMENT(const std::string key, const std::string value,  const typeOfJsonElement type);
	
	JSONELEMENT(const std::string key, const typeOfJsonElement type);

	void	insertSon(const JSONELEMENT& element);
	void ToString_refac(std::ostringstream& oss, std::vector<JSONELEMENT*> elmenets)const;
	std::string str(int indent = 0)const;
	void append(std::ostringstream& oss, std::vector<JSONELEMENT*> elmenets)const;

};
#pragma endregion
#pragma region JSONBuilder
struct JSONBuilder {

	JSONELEMENT root;
	JSONBuilder();
	void add_Complex( JSONELEMENT* elm);
	JSONELEMENT* findByKey(std::string key);
	JSONELEMENT create_array(std::string key, std::vector<JSONELEMENT>& sons);
	JSONELEMENT*  create_array(std::string key, std::vector<JSONELEMENT*> sons);
	JSONELEMENT* add_to_existing_object(JSONELEMENT* ptrTojsonElm, std::vector<JSONELEMENT*> sons);
	JSONELEMENT add_keyval(std::string key, std::string val, typeOfJsonElement type);
	JSONELEMENT* add_to_existing_object(JSONELEMENT* ptrTojsonElm, JSONELEMENT* son);
	JSONELEMENT createobjectWithValue(std::string key, std::string val,typeOfJsonElement type=typeOfJsonElement::_val);
	
	JSONELEMENT* create_array(JSONELEMENT* ptrTojsonElm, std::vector<JSONELEMENT*> sons);
	JSONELEMENT* createobjectWithNoValue(std::string key, typeOfJsonElement type=typeOfJsonElement::_object);
	JSONELEMENT* createobjectWithValueptr(std::string key, std::string val, typeOfJsonElement type = typeOfJsonElement::_object);
	

	JSONELEMENT* createobjectptr(std::string key, typeOfJsonElement type);
	void add_keyval(std::string key, const JSONELEMENT element, typeOfJsonElement type);
	void add_Complex(const JSONELEMENT elm);
	void print();
	std::string str();
	std::string str(JSONELEMENT& elementToChoose);


};
#pragma endregion
#pragma region JSONString2JsonElement
struct JSONString2JsonElement


{
	int refToInt;
	std::string FindKeyValueEnd(int index,std::string json,JSONELEMENT* theObjectSoFar) ;
	typeOfJsonElement FindValueType(std::string json, int indexInString);

	JSONELEMENT* FindJsonKey(std::string json,int i,JSONELEMENT* jsonElementFather,int& refrenceIndexInRootJsonString);

	JSONELEMENT* FindJsonValue(std::string json, int &i, JSONELEMENT* element);

	void FixJsonElementsValues(JSONELEMENT* father);

	
};
#pragma endregion


#pragma region UseFullParsing

void SetValueType(JSONELEMENT* element);

char*      strncpy(char *dest,  char *src, size_t n);
#pragma endregion
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define CPPSTD __cplusplus

#pragma region GeneralObjects

enum typeOfJsonElement
{
	_val = 0,
	_object,
	_NoKeyArray,
	_ObjectsArray,
	_NoKeyValue
};

enum JsonElementValueType
{
	INTEGER = 0,
	STRING,
	BOOLEAN,

};

struct JSONELEMENT
{

	std::vector<JSONELEMENT *> elmenetsptr;
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

	void append(std::ostringstream &oss);

	JSONELEMENT();
	void HandleType(JSONELEMENT &element);
	
	JSONELEMENT(const std::string key, const std::string value, const typeOfJsonElement type);

	JSONELEMENT(const std::string key, const typeOfJsonElement type);
	JSONELEMENT(const std::string key, const int value, const typeOfJsonElement type);
	JSONELEMENT(const std::string key, const double value, const typeOfJsonElement type);
	JSONELEMENT(const std::string key, const bool value, const typeOfJsonElement type);

	void insertSon(const JSONELEMENT &element);
	void ToString_refac(std::ostringstream &oss, std::vector<JSONELEMENT *> elmenets) const;
	std::string str(int indent = 0) const;
	void append(std::ostringstream &oss, std::vector<JSONELEMENT *> elmenets) const;
};
#pragma endregion
#pragma region JSONBuilder
struct JSONBuilder
{

	JSONELEMENT* root;
	JSONBuilder();
	
	JSONELEMENT *findByKey(std::string key);

	void print();
	std::string str();
	std::string str(JSONELEMENT &elementToChoose);



	//after refactor

	void R_add_key_value(std::string key,std::string value,JSONELEMENT* elementToAddTo,JsonElementValueType typeOfval);
	JSONELEMENT* R_create_json_object(std::string key);
	JSONELEMENT*  R_create_Key_value(std::string key,int value);
	JSONELEMENT*  R_create_Key_value(std::string key,bool value);
	JSONELEMENT*  R_create_Key_value(std::string key,double value);
	JSONELEMENT*  R_create_Key_value(std::string key,std::string value);
	JSONELEMENT*  R_create_noneKey_array(std::string key);
	JSONELEMENT*  R_create_objects_array(std::string key);
	JSONELEMENT*  R_create_nokey_value(std::string value);

	//no key array
	void R_add_to_no_key_array(JSONELEMENT* array,JSONELEMENT* element);
	void R_add_to_no_key_array(JSONELEMENT* array,std::vector<JSONELEMENT*> elements);

	//objects array
	void R_add_to_objects_array(JSONELEMENT* array,JSONELEMENT* elements);
	void R_add_to_objects_array(JSONELEMENT* array,std::vector<JSONELEMENT*> elements);

	//objects
	void R_add_to_object(JSONELEMENT* jsonObject,JSONELEMENT* element);
	void R_add_to_object(JSONELEMENT* jsonObject,std::vector<JSONELEMENT*> elements);
	void R_bundle(JSONELEMENT* element);
};
#pragma endregion
#pragma region JSONString2JsonElement
struct JSONString2JsonElement

{
	int refToInt;
	std::string FindKeyValueEnd(int index, std::string json, JSONELEMENT *theObjectSoFar);
	typeOfJsonElement FindValueType(std::string json, int indexInString);

	JSONELEMENT *FindJsonKey(std::string json, int i, JSONELEMENT *jsonElementFather, int &refrenceIndexInRootJsonString);
JSONELEMENT* ParsedObject(std::string);


	void FixJsonElementsValues(JSONELEMENT *father);
};
#pragma endregion

#pragma region UseFullParsing

void SetValueType(JSONELEMENT *element);

char *strncpy(char *dest, char *src, size_t n);
#pragma endregion
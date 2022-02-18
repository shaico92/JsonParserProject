#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>

#define CPPSTD __cplusplus

#pragma region GeneralObjects

enum typeOfJsonElement
{
	_val = 0,
	_object,
	_NoKeyArray,
	_ObjectsArray,
	_ArraysArray,
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

	bool lastJsonInArray;
	typeOfJsonElement type;

	JsonElementValueType valueType;

	JSONELEMENT();

	JSONELEMENT(const std::string key, const std::string value, const typeOfJsonElement type);

	JSONELEMENT(const std::string key, const typeOfJsonElement type);
	JSONELEMENT(const std::string key, const int value, const typeOfJsonElement type);
	JSONELEMENT(const std::string key, const double value, const typeOfJsonElement type);
	JSONELEMENT(const std::string key, const bool value, const typeOfJsonElement type);


	void ToString_refac(std::ostringstream &oss, std::vector<JSONELEMENT *> elmenets) const;
	std::string str(int indent = 0) const;

};
#pragma endregion
#pragma region JSONBuilder
struct JSONBuilder
{

	JSONELEMENT *root;
	JSONBuilder();

	JSONELEMENT *findByKey(std::string key);

	void print();
	std::string str();
	std::string str(JSONELEMENT &elementToChoose);

	//after refactor

	void R_add_key_value(std::string key, std::string value, JSONELEMENT *elementToAddTo, JsonElementValueType typeOfval);
	JSONELEMENT *R_create_json_object(std::string key);
	JSONELEMENT *R_create_Key_value(std::string key, int value);
	JSONELEMENT *R_create_Key_value(std::string key, bool value);
	JSONELEMENT *R_create_Key_value(std::string key, double value);
	JSONELEMENT *R_create_Key_value(std::string key, std::string value);
	JSONELEMENT *R_create_noneKey_array(std::string key);
	JSONELEMENT *R_create_objects_array(std::string key);
	JSONELEMENT *R_create_nokey_value(std::string value);
	JSONELEMENT *R_create_nokeyArray_array(std::string key);

	//no key array
	void R_add_to_no_key_array(JSONELEMENT *array, JSONELEMENT *element);
	void R_add_to_no_key_array(JSONELEMENT *array, std::vector<JSONELEMENT *> elements);

	//objects array
	void R_add_to_objects_array(JSONELEMENT *array, JSONELEMENT *elements);
	void R_add_to_objects_array(JSONELEMENT *array, std::vector<JSONELEMENT *> elements);

	//objects
	void R_add_to_object(JSONELEMENT *jsonObject, JSONELEMENT *element);
	void R_add_to_object(JSONELEMENT *jsonObject, std::vector<JSONELEMENT *> elements);

	//arrays array
	void R_add_to_nokeyArray_array(JSONELEMENT *array, JSONELEMENT *element);
	void R_add_tonokeyArray_array(JSONELEMENT *array, std::vector<JSONELEMENT *> elements);

	void R_bundle(JSONELEMENT *element);
};
#pragma endregion
#pragma region JSONString2JsonElement
struct JSONString2JsonElement

{
	int refToInt;
	std::string FindKeyValueEnd(int index, std::string json, JSONELEMENT *theObjectSoFar);
	typeOfJsonElement FindValueType(std::string json, int indexInString);

	JSONELEMENT *ConvertToJSONElement(std::string json, int i, JSONELEMENT *jsonElementFather, int &refrenceIndexInRootJsonString);
	JSONELEMENT *ParsedObject(std::string);

	std::vector<JSONELEMENT *> FindJSONElementByKey(JSONELEMENT * element,std::string key);
	std::vector<JSONELEMENT *> FindJSONElementByKeyUnderSpecificKeyHirerchy(JSONELEMENT * element,std::string key,std::string FatherKey);

	void FixJsonElementsValues(JSONELEMENT *father);
};
#pragma endregion

#pragma region UseFullParsing

void SetValueType(JSONELEMENT *element);

char *strncpy(char *dest, char *src, size_t n);
std::string removingTabsAndBreakLines(std::string json);
#pragma endregion
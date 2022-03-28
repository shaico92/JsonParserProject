#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>

#define CPPSTD __cplusplus
#define JSON_PARSER_API __declspec(dllexport)
#pragma region GeneralObjects




enum typeOfJsonElement
{
	_val = 0,
	_object,
	_NoKeyArray,
	_ObjectsArray,
	_ArraysArray,
	_NoKeyValue,
	_invalid
};

enum JsonElementValueType
{
	_INVALID=-1,
	INTEGER = 0,
	STRING,
	_BOOLEAN,

};


struct JSONELEMENT
{
	
	std::vector<JSONELEMENT*> elmenetsptr;
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
	JSONELEMENT(const std::string key, const long value, const typeOfJsonElement type);
	JSONELEMENT(const std::string key, const double value, const typeOfJsonElement type);
	JSONELEMENT(const std::string key, const bool value, const typeOfJsonElement type);
	JSON_PARSER_API ~JSONELEMENT();

	void ToString_refac(std::ostringstream& oss, std::vector<JSONELEMENT*> elmenets, std::string seperator="") const;
	JSON_PARSER_API	std::string str(std::string seperator="") const;

};

#pragma endregion
#pragma region JSONBuilder
struct JSONBuilder
{

	JSONELEMENT* root;
	JSONBuilder();

	JSONELEMENT* findByKey(std::string key);

	void print();
	JSON_PARSER_API std::string str();
	std::string str(JSONELEMENT& elementToChoose);

	//after refactor

	void  R_add_key_value(std::string key, std::string value, JSONELEMENT* elementToAddTo, JsonElementValueType typeOfval);
	JSON_PARSER_API	JSONELEMENT* R_create_json_object(std::string key);
	JSON_PARSER_API	JSONELEMENT* R_create_Key_value(std::string key, int value);
	JSON_PARSER_API	JSONELEMENT* R_create_Key_value(std::string key, bool value);
	JSON_PARSER_API	JSONELEMENT* R_create_Key_value(std::string key, double value);
	JSON_PARSER_API	JSONELEMENT* R_create_Key_valueS(std::string key, std::string value);
	JSON_PARSER_API	JSONELEMENT* R_create_Key_valueSWithParenthesis(std::string key, std::string value);
	JSON_PARSER_API	JSONELEMENT* R_create_noneKey_array(std::string key);
	JSON_PARSER_API	JSONELEMENT* R_create_objects_array(std::string key);
	JSON_PARSER_API	JSONELEMENT* R_create_nokey_value(std::string value);
	JSON_PARSER_API	JSONELEMENT* R_create_nokeyArray_array(std::string key);

	//no key array
	void JSON_PARSER_API R_add_to_no_key_array(JSONELEMENT* array, JSONELEMENT* element);
	void JSON_PARSER_API R_add_to_no_key_array(JSONELEMENT* array, std::vector<JSONELEMENT*> elements);

	//objects array
	void JSON_PARSER_API R_add_to_objects_array(JSONELEMENT* array, JSONELEMENT* elements);
	void JSON_PARSER_API R_add_to_objects_array(JSONELEMENT* array, std::vector<JSONELEMENT*> elements);

	//objects
	void JSON_PARSER_API R_add_to_object(JSONELEMENT* jsonObject, JSONELEMENT* element);
	void JSON_PARSER_API R_add_to_object(JSONELEMENT* jsonObject, std::vector<JSONELEMENT*> elements);

	//arrays array
	void JSON_PARSER_API R_add_to_nokeyArray_array(JSONELEMENT* array, JSONELEMENT* element);
	void JSON_PARSER_API R_add_tonokeyArray_array(JSONELEMENT* array, std::vector<JSONELEMENT*> elements);



	JSONELEMENT* DEEP_COPY(JSONELEMENT* origin);

	void JSON_PARSER_API R_bundle(JSONELEMENT* element);
};
#pragma endregion
#pragma region JSONString2JsonElement
struct JSONString2JsonElement

{
	int refToInt;
	std::string FindKeyValueEnd(int index, std::string json, JSONELEMENT* theObjectSoFar);
	typeOfJsonElement FindValueType(std::string json, int indexInString);

	JSONELEMENT* ConvertToJSONElement(std::string json, int i, JSONELEMENT* jsonElementFather, int& refrenceIndexInRootJsonString);
	JSONELEMENT* ParsedObject(std::string);

	std::vector<JSONELEMENT*> FindJSONElementByKey(JSONELEMENT* element, std::string key);
	std::vector<JSONELEMENT*> FindJSONElementByKeyUnderSpecificKeyHirerchy(JSONELEMENT* element, std::string key, std::string FatherKey);
	std::vector<JSONELEMENT*>	FindConainersForKeyAndValues(JSONELEMENT* Father, std::string key, std::string value);
	void FixJsonElementsValues(JSONELEMENT* father);

	void EmptyAllValues(JSONELEMENT* father);
};
#pragma endregion

#pragma region UseFullParsing

void SetValueType(JSONELEMENT* element);

char* strncpy(char* dest, char* src, size_t n);
std::string removingTabsAndBreakLines(std::string json);



#pragma region JSON_API


extern "C"	JSON_PARSER_API JSONELEMENT * pass_string_to_dll(char* json, long size);
extern "C"	JSON_PARSER_API char* get_string_fromcpp(std::string RequiredString);
extern "C"	JSON_PARSER_API JSONELEMENT * deep_copy(JSONELEMENT * origin);
extern "C"	JSON_PARSER_API void  empty_json_structure(JSONELEMENT * father);

extern "C"	JSON_PARSER_API void DestroyAllJsonElemnt(JSONELEMENT* elemnt);
extern "C"	JSON_PARSER_API std::vector<char*>*  delete_ptr();


extern "C"	JSON_PARSER_API std::vector<JSONELEMENT*> findElementsByKey(JSONELEMENT * element, std::string key, std::string FatherKey);
extern "C"	JSON_PARSER_API JSONELEMENT* findOneElementsByKey(JSONELEMENT * element, std::string key, std::string FatherKey);

extern "C"	JSON_PARSER_API std::vector<JSONELEMENT*> FindJSONElementByKey(JSONELEMENT * element, std::string key);
extern "C"	JSON_PARSER_API JSONELEMENT* FindOneJSONElementByKey(JSONELEMENT * element, std::string key);

extern "C"	JSON_PARSER_API  JSONBuilder json_builder();
 extern "C"	JSON_PARSER_API std::vector<JSONELEMENT*> FindConainersForKeyAndValuesAPI(JSONELEMENT* element, std::string key, std::string value);
 extern "C"	JSON_PARSER_API JSONELEMENT* FindOneConainersForKeyAndValuesAPI(JSONELEMENT * element, std::string key, std::string value);
#pragma endregion


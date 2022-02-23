// JSON_Parser.cpp : Defines the exported functions for the DLL application.
//






#include "JsonBuilder.h"

using namespace std;

#pragma region JsonElement
JSONELEMENT::JSONELEMENT()
{
}

JSONELEMENT::JSONELEMENT(const std::string key, const std::string value, const typeOfJsonElement type)
	: key(key), value(value), type(type) {
	this->value = value;

};

JSONELEMENT::JSONELEMENT(const std::string key, const int value, const typeOfJsonElement type) : partOfArray(false), key(key + ""), value(value + ""), type(type)
{
	//cout << value;
	ostringstream oss;
	oss << value;
	this->value = oss.str();
};
JSONELEMENT::JSONELEMENT(const std::string key, const bool value, const typeOfJsonElement type) : partOfArray(false), key(key + ""), value(value + ""), type(type)
{

	if (value)
	{
		this->value = "true";
	}
	else
	{
		this->value = "false";
	}
};
JSONELEMENT::JSONELEMENT(const std::string key, const double value, const typeOfJsonElement type) : partOfArray(false), key(key + ""), type(type)
{
	//this->value=to_string(value);
	//cout << value;
	ostringstream oss;
	oss << value;
	this->value = oss.str();
};

JSONELEMENT::JSONELEMENT(const std::string key, const typeOfJsonElement type)
	: key(key), type(type) {

};

string JSONELEMENT::str(int indent) const
{
	ostringstream oss;

	//append(oss, elmenetsptr);
	oss << '{';

	ToString_refac(oss, elmenetsptr);
	oss << '}';
	return oss.str();
	//}
}

void JSONELEMENT::ToString_refac(std::ostringstream& oss, std::vector<JSONELEMENT*> elmenets) const
{

#if CPPSTD == 201103L || CPPSTD == 199711 // std11

	for each (auto & e in elmenets)
	{
		if (e->partOfArray)
		{
			oss << '{';
		}

		if (e->type == typeOfJsonElement::_val)
		{

			oss << '\"' << e->key << '\"' << ':' << e->value;
		}
		if (e->type == typeOfJsonElement::_NoKeyValue)
		{

			oss << e->value;

		}
		if (e->type == typeOfJsonElement::_object)
		{
			if (e->key.length()>1)
			{
				oss << '\"' << e->key << '\"' << ':' << '{';
			}

			
			if (e->elmenetsptr.size() > 0)
			{
				ToString_refac(oss, e->elmenetsptr);
			}
			if (e->key.length() > 1)
			{
				oss << '}';
			}

			
		}
		if (e->type == typeOfJsonElement::_ArraysArray)
		{
			oss << '\"' << e->key << '\"' << ':' << '[';
			if (e->elmenetsptr.size() > 0)
			{
				for  each (auto && elm in e->elmenetsptr)
				{
					oss << '[';
					ToString_refac(oss, elm->elmenetsptr);
					oss << ']';
					if (!elm->lastJsonInArray)
					{
						oss << ',';
					}

				}



			}

			oss << ']';
		}


		if (e->type == typeOfJsonElement::_NoKeyArray)
		{
			oss << '\"' << e->key << '\"' << ':' << '[';
			if (e->elmenetsptr.size() > 0)
			{
				ToString_refac(oss, e->elmenetsptr);
			}

			oss << ']';
		}
		if (e->type == typeOfJsonElement::_ObjectsArray)
		{
			oss << '\"' << e->key << '\"' << ':' << '[';

			if (e->elmenetsptr.size() > 0)
			{
				for  each (auto && elm in e->elmenetsptr)
				{
					elm->partOfArray = true;
					if (elm->elmenetsptr.size()>0)
					{
						ToString_refac(oss, elm->elmenetsptr);
					}
				}

					ToString_refac(oss, e->elmenetsptr);
			}

			oss << ']';
		}

		if (e->partOfArray)
		{
			oss << '}';
		}

		if (e->lastJsonInArray)
		{
		}
		else
		{
			oss << ',';
		}
	}

#endif

#if CPPSTD == 201402L //std 14

	for (auto& e : elmenets)
	{
		if (e->partOfArray)
		{
			oss << '{';
		}

		if (e->type == typeOfJsonElement::_val)
		{

			oss << '\"' << e->key << '\"' << ':' << e->value;
		}
		if (e->type == typeOfJsonElement::_NoKeyValue)
		{

			oss << e->value;

		}
		if (e->type == typeOfJsonElement::_object)
		{
			oss << '\"' << e->key << '\"' << ':' << '{';
			if (e->elmenetsptr.size() > 0)
			{
				ToString_refac(oss, e->elmenetsptr);
			}

			oss << '}';
		}
		if (e->type == typeOfJsonElement::_ArraysArray)
		{
			oss << '\"' << e->key << '\"' << ':' << '[';
			if (e->elmenetsptr.size() > 0)
			{
				for (auto&& elm : e->elmenetsptr)
				{
					oss << '[';
					ToString_refac(oss, elm->elmenetsptr);
					oss << ']';
					if (!elm->lastJsonInArray)
					{
						oss << ',';
					}

				}



			}

			oss << ']';
		}


		if (e->type == typeOfJsonElement::_NoKeyArray)
		{
			oss << '\"' << e->key << '\"' << ':' << '[';
			if (e->elmenetsptr.size() > 0)
			{
				ToString_refac(oss, e->elmenetsptr);
			}

			oss << ']';
		}
		if (e->type == typeOfJsonElement::_ObjectsArray)
		{
			oss << '\"' << e->key << '\"' << ':' << '[';

			if (e->elmenetsptr.size() > 0)
			{
				for (auto&& elm : e->elmenetsptr)
				{
					elm->partOfArray = true;
				}

				//	ToString_refac(oss, e->elmenetsptr);
			}

			oss << ']';
		}

		if (e->partOfArray)
		{
			oss << '}';
		}

		if (e->lastJsonInArray)
		{
		}
		else
		{
			oss << ',';
		}
}

#endif // std11
}

#pragma endregion

#pragma region JsonBuilder

JSONBuilder::JSONBuilder()
{
	root = NULL;
};

void JSONBuilder::print()
{
	cout << root->str();
}
string JSONBuilder::str()
{

	return root->str();
}

string JSONBuilder::str(JSONELEMENT& elementToChoose)
{
	return elementToChoose.str();
}

//after refactor

void JSONBuilder::R_add_key_value(std::string key, std::string value, JSONELEMENT* elementToAddTo, JsonElementValueType typeOfval)
{
	JSONELEMENT* key_value = new JSONELEMENT();
	if (typeOfval == JsonElementValueType::STRING)
	{
		if (key[0] == '\"' || key[key.length() - 1] == '\"')
		{
			cout << " need to insert only none quoted strings";
			return;
		}
		else
		{
			key_value->key = '\"' + key + '\"';
			key_value->value = '\"' + value + '\"';
		}
		key_value->type = typeOfJsonElement::_val;
		elementToAddTo->elmenetsptr.push_back(key_value);
	}
}
JSONELEMENT* JSONBuilder::R_create_json_object(std::string key)
{
	JSONELEMENT* obj = new JSONELEMENT(key, typeOfJsonElement::_object);
	obj->partOfArray = false;
	return obj;
}
JSONELEMENT* JSONBuilder::R_create_Key_valueS(const std::string key,const std::string value)
{
	JSONELEMENT* obj = new JSONELEMENT(key, value, typeOfJsonElement::_val);
	obj->partOfArray = false;
	return obj;
}
JSONELEMENT* JSONBuilder::R_create_Key_value(const std::string key, const bool value)
{
	JSONELEMENT* obj = new JSONELEMENT(key, value, typeOfJsonElement::_val);
	obj->partOfArray = false;
	return obj;
}
JSONELEMENT* JSONBuilder::R_create_Key_value(const std::string key, const int value)
{
	JSONELEMENT* obj = new JSONELEMENT(key, value, typeOfJsonElement::_val);
	obj->partOfArray = false;
	return obj;
}
JSONELEMENT* JSONBuilder::R_create_Key_value(const std::string key, const double value)
{
	JSONELEMENT* obj = new JSONELEMENT(key, value, typeOfJsonElement::_val);
	return obj;
}
JSONELEMENT* JSONBuilder::R_create_nokey_value(const std::string value)
{
	JSONELEMENT* obj = new JSONELEMENT();
	obj->value = value;
	obj->type = typeOfJsonElement::_NoKeyValue;
	return obj;
}

JSONELEMENT* JSONBuilder::R_create_noneKey_array(const std::string key)
{
	JSONELEMENT* obj = new JSONELEMENT(key, typeOfJsonElement::_NoKeyArray);
	obj->partOfArray = false;
	return obj;
}
JSONELEMENT* R_create_nokeyArray_array(const std::string key) {
	JSONELEMENT* obj = new JSONELEMENT(key, typeOfJsonElement::_ArraysArray);
	obj->partOfArray = false;
	return obj;
}
JSONELEMENT* JSONBuilder::R_create_objects_array(const std::string key)
{
	JSONELEMENT* obj = new JSONELEMENT(key, typeOfJsonElement::_ObjectsArray);
	return obj;
}

void JSONBuilder::R_add_to_no_key_array(JSONELEMENT* array, JSONELEMENT* element)
{
	if (array->type != typeOfJsonElement::_NoKeyArray)
	{
		cout << "can only use no key array with this function";
		return;
	}
	if (element->type != typeOfJsonElement::_NoKeyValue)
	{
		cout << "can only add a  no key value with this function";
		return;
	}
	array->elmenetsptr.push_back(element);
}

void JSONBuilder::R_add_to_no_key_array(JSONELEMENT* array, vector<JSONELEMENT*> elements)
{

	for (size_t i = 0; i < elements.size(); i++)
	{
		elements.at(i)->lastJsonInArray = false;
		R_add_to_no_key_array(array, elements.at(i));
	}
	elements.at(elements.size() - 1)->lastJsonInArray = true;
}
void JSONBuilder::R_add_to_objects_array(JSONELEMENT* array, JSONELEMENT* element)
{

	if (array->type != typeOfJsonElement::_ObjectsArray)
	{
		cout << "can only use no key array with this function";
		return;
	}
	if (element->type == typeOfJsonElement::_NoKeyValue)
	{
		cout << "can only not  use no key value with this function";
		return;
	}

	element->partOfArray = true;

	array->elmenetsptr.push_back(element);
}

void JSONBuilder::R_add_to_objects_array(JSONELEMENT* array, vector<JSONELEMENT*> elements)
{

	for (size_t i = 0; i < elements.size(); i++)
	{
		elements.at(i)->lastJsonInArray = false;
		R_add_to_objects_array(array, elements.at(i));
	}
	elements.at(elements.size() - 1)->lastJsonInArray = true;
}

void JSONBuilder::R_add_to_object(JSONELEMENT* jsonObject, JSONELEMENT* element)
{

	if (jsonObject->type == typeOfJsonElement::_NoKeyValue || jsonObject->type == typeOfJsonElement::_val)
	{
		//	cout << "can not use the type :" << jsonObject->type << "as the object father";
		return;
	}

	if (jsonObject->elmenetsptr.size() > 0)
	{
		jsonObject->elmenetsptr.at(jsonObject->elmenetsptr.size() - 1)->lastJsonInArray = false;
	}
	element->lastJsonInArray = true;
	jsonObject->elmenetsptr.push_back(element);
}

void JSONBuilder::R_add_to_object(JSONELEMENT* jsonObject, vector<JSONELEMENT*> elements)
{

	for (size_t i = 0; i < elements.size(); i++)
	{
		elements.at(i)->lastJsonInArray = false;
		R_add_to_object(jsonObject, elements.at(i));
	}
	elements.at(elements.size() - 1)->lastJsonInArray = true;
}



void R_add_to_nokeyArray_array(JSONELEMENT* array, JSONELEMENT* element) {
	if (array->type != typeOfJsonElement::_ArraysArray)
	{
		cout << "can only add to an arrays  array with this function";
		return;
	}
	if (element->type != typeOfJsonElement::_NoKeyArray)
	{
		cout << "can only add a  no key value with this function";
		return;
	}
	array->elmenetsptr.push_back(element);


}


void R_add_tonokeyArray_array(JSONELEMENT* array, std::vector<JSONELEMENT*> elements) {
	for (size_t i = 0; i < elements.size(); i++)
	{
		elements.at(i)->lastJsonInArray = false;
		R_add_to_nokeyArray_array(array, elements.at(i));
	}
	elements.at(elements.size() - 1)->lastJsonInArray = true;



}


void JSONBuilder::R_bundle(JSONELEMENT* element)
{
	if (NULL == this->root)
	{
		this->root = new JSONELEMENT();
	}
	root->elmenetsptr.push_back(element);
}

JSONELEMENT* JSONBuilder::DEEP_COPY(JSONELEMENT* origin)
{
	JSONELEMENT* copy = new JSONELEMENT();
	copy->key = origin->key;
	copy->value = origin->value;
	copy->lastJsonInArray = origin->lastJsonInArray;
	copy->partOfArray = origin->partOfArray;
	copy->type = origin->type;
	copy->valueType = origin->valueType;

	if (origin->elmenetsptr.size() > 0)
	{
		for (size_t i = 0; i < origin->elmenetsptr.size(); i++)
		{
			JSONELEMENT* copySon = DEEP_COPY(origin->elmenetsptr.at(i));
			copy->elmenetsptr.push_back(copySon);


		}

	}




	return copy;
}

#pragma endregion

#pragma region JSONString2JsonElement

JSONELEMENT* JSONString2JsonElement::ConvertToJSONElement(std::string json, int i, JSONELEMENT* jsonElementFather, int& refrenceIndexInRootJsonString)
{

	i++;

	//finding the key

	string theKey = "";

	while (i < json.length() - 1)
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
	if (i > json.length())
	{
		return jsonElementFather;
	}


	//starting to create the object
	JSONELEMENT* je = new JSONELEMENT();
	//here already have the key
	je->key = theKey;
	i++;
	je->type = FindValueType(json, i);

	je->entireValuAsString = FindKeyValueEnd(i, json, je);

	if (je->type == typeOfJsonElement::_object)
	{
		jsonElementFather->elmenetsptr.push_back(ConvertToJSONElement(je->entireValuAsString, 0, je, refToInt));
	}
	if (je->type == typeOfJsonElement::_val)
	{
		je->value = je->entireValuAsString;
		SetValueType(je);
		
		jsonElementFather->elmenetsptr.push_back(je);
	}
	if (je->type == typeOfJsonElement::_NoKeyArray)
	{

		jsonElementFather->elmenetsptr.push_back(je);
	}
	if (je->type == typeOfJsonElement::_ObjectsArray)
	{

		//{\"arrayman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}]}

		jsonElementFather->elmenetsptr.push_back(je);
	}



	refrenceIndexInRootJsonString = i + je->entireValuAsString.length();

	if (je->type == typeOfJsonElement::_ArraysArray)
	{

		//{\"arrayman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}]}

		jsonElementFather->elmenetsptr.push_back(je);


		//refrenceIndexInRootJsonString=refToInt-1;
	}



	if (refrenceIndexInRootJsonString > json.length())
	{
		return jsonElementFather;
	}







	if (json[refrenceIndexInRootJsonString] == ',')
	{

		ConvertToJSONElement(jsonElementFather->entireValuAsString, refToInt, jsonElementFather, refToInt);
	}
	else
	{
		je->lastJsonInArray = true;
	}

	return jsonElementFather;
}
void JSONString2JsonElement::FixJsonElementsValues(JSONELEMENT* father)
{

	//this function is empting the memory allocated while parsing the string to json element
	father->entireValuAsString.erase(0, father->entireValuAsString.length()).reserve();

	if (father->elmenetsptr.size() > 0)
	{
		for (size_t i = 0; i < father->elmenetsptr.size(); i++)
		{

			father->elmenetsptr.at(i)->entireValuAsString.erase(0, father->elmenetsptr.at(i)->entireValuAsString.length()).reserve();
			JSONELEMENT* son = father->elmenetsptr.at(i);

			FixJsonElementsValues(son);
		}
	}

	return;
}

void JSONString2JsonElement::EmptyAllValues(JSONELEMENT* father) {
	father->value.erase(0, father->value.length()).reserve();

	if (father->elmenetsptr.size() > 0)
	{
		for (size_t i = 0; i < father->elmenetsptr.size(); i++)
		{

			
			JSONELEMENT* son = father->elmenetsptr.at(i);
			son->value.erase(0, son->value.length()).reserve();
			EmptyAllValues(son);
		}
	}


}

typeOfJsonElement JSONString2JsonElement::FindValueType(std::string json, int indexInString)
{
	//moving the index to pass the ":" in the string

	while (true)
	{
		if (json[indexInString] == '[')
		{
			indexInString++;
			if (json[indexInString] == '{')
			{
				return typeOfJsonElement::_ObjectsArray;
			}
			if (json[indexInString] == '[')
			{
				return typeOfJsonElement::_ArraysArray;
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

string JSONString2JsonElement::FindKeyValueEnd(int index, string json, JSONELEMENT* theObjectSoFar)
{

	int count = 0;
	int startIndex = 0;
	startIndex = int(index);
	//finding the key

	string retString = "";

	//if its an array of objects
	if (theObjectSoFar->type == typeOfJsonElement::_ObjectsArray)
	{
		//	cout << "\nobjects array";

			//{\"arrayman\":[{\"cc\":{\"ccz\":1}},{\"ccvb\":\"cxz\"}]}
		string theCurrentJson = "";
		int AnotherCounterForParentethees = 0;
		while (index < json.length())
		{
			if (json[index] == '\"' && AnotherCounterForParentethees > 0)
			{
				AnotherCounterForParentethees--;
			}
			else if (json[index] == '\"')
			{
				AnotherCounterForParentethees++;
			}
			if (AnotherCounterForParentethees < 1)

			{

				if (json[index] == '[')
				{
					count++;
				}
				if (json[index] == ']')
				{
					count--;
				}
				if (count == 0)
				{
					theCurrentJson += json[index];
					break;
				}
			}

			theCurrentJson += json[index];
			index++;
		}

		// in this loop im dividing the array to json objects and activating the find json key function on them

		int findex = 1;
		int endIndex = 0;
		int pairStartIndex = 0;
		int stringBracketsCounter = 0;
		int secondCounter = 0;
		vector<string> vectorOfJsonObjectsAsStrings;
		while (findex < theCurrentJson.length() - 1)
		{
			if (theCurrentJson[findex] == '\"' && stringBracketsCounter > 0)
			{
				stringBracketsCounter--;
			}
			else if (theCurrentJson[findex] == '\"')
			{
				stringBracketsCounter++;
			}
			if (stringBracketsCounter < 1)

			{

				if (theCurrentJson[findex] == '{')
				{
					if (secondCounter == 0)
					{
						pairStartIndex = findex;
						secondCounter++;
					}

					count++;
				}
				if (theCurrentJson[findex] == '}')
				{
					count--;
				}
			}

			findex++;
			if (count == 0 && theCurrentJson[findex] != ',')
			{

				endIndex = findex;
				;
				//auto p1 = std::make_pair(pairStartIndex, endIndex-1);
				string temp = "";
				for (int i = pairStartIndex; i < endIndex; i++)
				{

					if (theCurrentJson[i] == ',' && i + 1 > endIndex - 1)
					{
						continue;
					}

					temp += theCurrentJson[i];
				}
				//	cout << findex;
				vectorOfJsonObjectsAsStrings.push_back(temp);
				secondCounter = 0;
					}
				}
		theObjectSoFar->entireValuAsString = theCurrentJson;
		int indexInTotalString = 0;
#if CPPSTD == 201402L // std11
		for (auto&& jsonString : vectorOfJsonObjectsAsStrings)
		{
			JSONELEMENT* je = new JSONELEMENT();
			je->entireValuAsString = jsonString;
			auto res = ConvertToJSONElement(jsonString, 0, je, refToInt);
			je->partOfArray = true;
			theObjectSoFar->elmenetsptr.push_back(je);
		}
#endif
#if CPPSTD == 201103L || CPPSTD == 199711


		for each (auto && jsonString in vectorOfJsonObjectsAsStrings)
		{
			JSONELEMENT* je = new JSONELEMENT();
			je->entireValuAsString = jsonString;
			auto res = ConvertToJSONElement(jsonString, 0, je, refToInt);
			je->partOfArray = true;
			je->type = typeOfJsonElement::_object;
			theObjectSoFar->elmenetsptr.push_back(je);
			


		}


#endif
		int sizeOfElementsList = theObjectSoFar->elmenetsptr.size();
		if (sizeOfElementsList < 1)
		{
			/* code */
		}
		else
		{
#if CPPSTD == 201402L
			for (auto&& elements : theObjectSoFar->elmenetsptr)
			{
				elements->lastJsonInArray = false;
				elements->partOfArray = true;
			}
#endif
#if CPPSTD == 201103L || CPPSTD == 199711
			for each (auto && elements in theObjectSoFar->elmenetsptr)
			{
				elements->lastJsonInArray = false;
				elements->partOfArray = true;
			}
#endif

			theObjectSoFar->elmenetsptr.at(sizeOfElementsList - 1)->lastJsonInArray = true;
		}
		refToInt -= theObjectSoFar->entireValuAsString.length();
		return theObjectSoFar->entireValuAsString;
		}
	if (theObjectSoFar->type == typeOfJsonElement::_NoKeyArray)
	{

		string tempValue;
		int AnotherCounterForParentethees = 0;
		string theCurrentJson = "";
		while (index < json.length())
		{
			if (json[index] == '\"' && AnotherCounterForParentethees > 0)
			{
				AnotherCounterForParentethees--;
			}
			else if (json[index] == '\"')
			{
				AnotherCounterForParentethees++;
			}
			if (AnotherCounterForParentethees < 1)

			{

				if (json[index] == '[')
				{
					count++;
				}
				if (json[index] == ']')
				{
					count--;
				}
				if (count == 0)
				{
					theCurrentJson += json[index];
					break;
				}
			}

			theCurrentJson += json[index];
			index++;
		}

		index = 1;

		while (index < theCurrentJson.length())
		{
			//  [\"na''',me\",1,5,\"f}]f\"]
			if (theCurrentJson[index] == '\"' && AnotherCounterForParentethees > 0)
			{

				tempValue += theCurrentJson[index];
				AnotherCounterForParentethees--;

				index++;

				continue;
			}

			if (theCurrentJson[index] == '\"' && AnotherCounterForParentethees < 1)
			{

				AnotherCounterForParentethees++;
			}
			if ((AnotherCounterForParentethees == 0) && ((theCurrentJson[index] == ',') ||
				(theCurrentJson[index] == '[') ||
				(theCurrentJson[index] == ']') ||
				(theCurrentJson[index] == '}') ||
				(theCurrentJson[index] == '{')))
			{

				if (tempValue.length() > 0)
				{

					JSONELEMENT* je = new JSONELEMENT();
					je->type = typeOfJsonElement::_NoKeyValue;
					je->value = tempValue;
					je->partOfArray = false;
					je->lastJsonInArray = false;

					SetValueType(je);

					theObjectSoFar->elmenetsptr.push_back(je);

					index++;
					tempValue = "";
					continue;
				}
			}

			tempValue += theCurrentJson[index];

			index++;
		}
		int sizeOftheElemetsList = theObjectSoFar->elmenetsptr.size();
		if (sizeOftheElemetsList < 1)
		{
			/* code */
		}
		else
		{
			theObjectSoFar->elmenetsptr.at(sizeOftheElemetsList - 1)->lastJsonInArray = true;
		}

		//after finishing loop in array

		//   [\"na''',me\",6,\"f}]f\",5,1],\"keyt\":\"}\"

		return theCurrentJson;
	}
	//if its an array of values

	//if its an arrays Array
	if (theObjectSoFar->type == typeOfJsonElement::_ArraysArray)
	{
		/* code */


		string tempValue;
		int AnotherCounterForParentethees = 0;
		string theCurrentJson = "";
		while (index < json.length())
		{
			if (json[index] == '\"' && AnotherCounterForParentethees > 0)
			{
				AnotherCounterForParentethees--;
			}
			else if (json[index] == '\"')
			{
				AnotherCounterForParentethees++;
			}
			if (AnotherCounterForParentethees < 1)

			{

				if (json[index] == '[')
				{
					count++;
				}
				if (json[index] == ']')
				{
					count--;
				}
				if (count == 0)
				{
					theCurrentJson += json[index];
					break;
				}
			}

			theCurrentJson += json[index];
			index++;
		}






		index = 1;
		int endIndex = 0;
		int pairStartIndex = 0;
		int stringBracketsCounter = 0;
		int secondCounter = 0;
		vector<string> vectorOfJsonObjectsAsStrings;
		while (index < theCurrentJson.length())
		{
			if (theCurrentJson[index] == '\"' && stringBracketsCounter > 0)
			{
				stringBracketsCounter--;
			}
			else if (theCurrentJson[index] == '\"')
			{
				stringBracketsCounter++;
			}
			if (stringBracketsCounter < 1)

			{

				if (theCurrentJson[index] == '[')
				{
					if (secondCounter == 0)
					{
						pairStartIndex = index;
						secondCounter++;
					}

					count++;
				}
				if (theCurrentJson[index] == ']')
				{
					count--;
				}
			}

			index++;
			if (count == 0 && theCurrentJson[index] != ',')
			{

				endIndex = index;
				;
				//auto p1 = std::make_pair(pairStartIndex, endIndex-1);
				string temp = "";
				for (int i = pairStartIndex; i < endIndex; i++)
				{

					// if (json[i] == ',' && i + 1 > endIndex - 1)
					// {
					// 	continue;
					// }

					temp += theCurrentJson[i];
				}
				//	cout << findex;
				vectorOfJsonObjectsAsStrings.push_back(temp);
				secondCounter = 0;
			}
		}

		int sizeOftheElemetsList = vectorOfJsonObjectsAsStrings.size();
		if (sizeOftheElemetsList < 1)
		{
			/* code */
		}
		else
		{
			while (json[refToInt] != '\"')
			{
				/* code */
				++refToInt;
			}
			string keySize = "";
			++refToInt;
			while (json[refToInt] != '\"')
			{
				/* code */
				keySize += json[refToInt];
				++refToInt;
			}


			++refToInt;
			++refToInt;
			++refToInt;



			for (size_t zi = 0; zi < sizeOftheElemetsList; zi++)
			{
				/* code */

				JSONELEMENT* jsonNoKeyArray = new JSONELEMENT();
				jsonNoKeyArray->entireValuAsString = vectorOfJsonObjectsAsStrings.at(zi);
				jsonNoKeyArray->type = typeOfJsonElement::_NoKeyArray;

				//TODO: fix the naming
				int ind = 0;

				FindKeyValueEnd(refToInt, json, jsonNoKeyArray);
				jsonNoKeyArray->partOfArray = false;
				theObjectSoFar->partOfArray = false;
				jsonNoKeyArray->lastJsonInArray = false;
				theObjectSoFar->elmenetsptr.push_back(jsonNoKeyArray);
				refToInt += jsonNoKeyArray->entireValuAsString.length();





			}
			theObjectSoFar->entireValuAsString += '[';
			for (size_t index_ = 0; index_ < theObjectSoFar->elmenetsptr.size(); index_++)
			{


				theObjectSoFar->entireValuAsString += theObjectSoFar->elmenetsptr.at(index_)->entireValuAsString;



			}
			theObjectSoFar->entireValuAsString += ']';
			//theObjectSoFar->entireValuAsString+="]";


			theObjectSoFar->elmenetsptr.at(sizeOftheElemetsList - 1)->lastJsonInArray = true;

			//	refToInt+=theObjectSoFar->entireValuAsString.length();
			return theObjectSoFar->entireValuAsString;

		}




	}



	//if its an object
	if (theObjectSoFar->type == typeOfJsonElement::_object)
	{
		/* code */
		int stringBracketsCounter = 0;

		while (index < json.length())
		{
			if (json[index] == '\"' && stringBracketsCounter > 0)
			{
				stringBracketsCounter--;
			}
			else if (json[index] == '\"')
			{
				stringBracketsCounter++;
			}
			if (stringBracketsCounter < 1)

			{

				if (json[index] == '{')
				{
					count++;
				}
				if (json[index] == '}')
				{
					count--;
				}
				if (count == 0)
				{

					break;
				}
			}

			index++;
		}
	}
	if (theObjectSoFar->type == typeOfJsonElement::_val)
	{
		/* code */

		while (index < json.length())
		{
			if (json[index] == '\"' && count > 0)
			{
				count--;
			}
			else if (json[index] == '\"')
			{
				count++;
			}

			// if its not zero already its probably a number

			if ((json[index] == '}' || json[index] == ',') && count == 0)
			{
				break;
			}

			index++;
		}
	}
	//get end of value index;
	index++;
	//add check if , or } and decremente index

	if ((theObjectSoFar->type == typeOfJsonElement::_val) && (json[json.length() - 1] == ','))
	{
		theObjectSoFar->partOfArray;
	}

	if ((theObjectSoFar->type == typeOfJsonElement::_val) && (json[json.length() - 1] == ',' || json[json.length() - 1] == '}'))
	{
		index--;
	}

	for (int im = startIndex; im < index; im++)
	{
		retString += json[im];
	}
	if (json[json.length() - 1] == ',');
	{
		retString = "";
		for (int im = startIndex; im < index; im++)
		{
			if (im + 2 > index && json[im] == ',')
			{
				break;
			}

			retString += json[im];
		}
		index = startIndex;

		return retString;
		/* code */
	}




	return retString;
			}

JSONELEMENT* JSONString2JsonElement::ParsedObject(std::string jsonString)
{
	int i = 0;
	JSONELEMENT* jsonElementFather = new JSONELEMENT();

	jsonElementFather->entireValuAsString = removingTabsAndBreakLines(jsonString);
	cout << "finish to read and fix file\n";
	refToInt = 0;
	ConvertToJSONElement(jsonElementFather->entireValuAsString, i, jsonElementFather, refToInt);
		FixJsonElementsValues(jsonElementFather);
	cout << "finish to parsing fix file\n";
	return jsonElementFather;
}

vector<JSONELEMENT*> JSONString2JsonElement::FindJSONElementByKey(JSONELEMENT* element, std::string key) {

	int i = 0;
	vector<JSONELEMENT* > elements;
	while (i < element->elmenetsptr.size())
	{
		if (strcmp(element->elmenetsptr.at(i)->key.c_str(), key.c_str()) == 0)
		{
			elements.push_back(element->elmenetsptr.at(i));
		}
		else {
			vector<JSONELEMENT*> results = FindJSONElementByKey(element->elmenetsptr.at(i), key);
			for (int i = 0;i < results.size();++i) {
				elements.push_back(results.at(i));
			}
		}

		++i;
	}

	return elements;


}
std::vector<JSONELEMENT*> JSONString2JsonElement::FindJSONElementByKeyUnderSpecificKeyHirerchy(JSONELEMENT* element, std::string key, std::string FatherKey) {

	int i = 0;
	vector<JSONELEMENT* > elements;

	while (i < element->elmenetsptr.size())
	{
		std::vector<JSONELEMENT*>  res = FindJSONElementByKey(element, FatherKey);
		int j = 0;
		while (j < res.size())
		{
			std::vector<JSONELEMENT*>  RequiredSons = FindJSONElementByKey(res.at(i), key);
			int k = 0;
			while (k < RequiredSons.size())
			{
				elements.push_back(RequiredSons.at(k));
				++k;
			}

			return elements;
			++j;
		}
		++i;
	}



	return elements;

}

#pragma endregion

#pragma region UseFullParsing

void SetValueType(JSONELEMENT* element)
{
	//this is for determin which type the jsonelement value is
	int index = 0;

	if (element->value[0] == '\"')
	{
		//always a string
		element->valueType = JsonElementValueType::STRING;
		return;
		}

	char TrueOrFalse[5];
	string FALSE_ = "false";
	string TRUE_ = "true";
	strncpy(TrueOrFalse, &element->value[index], 5);

#if __linux__

	strcmp(TrueOrFalse, FALSE_.c_str());
	if ((strcmp(TrueOrFalse, FALSE_.c_str()) == 0) ||
		(strcmp(TrueOrFalse, TRUE_.c_str()) == 0))
	{
		//always a boolean
		element->valueType = JsonElementValueType::_BOOLEAN;
		return;
	}
#endif
#if _WIN32

	strcmp(TrueOrFalse, FALSE_.c_str());
	if ((strcmp(TrueOrFalse, FALSE_.c_str()) == 0) ||
		(strcmp(TrueOrFalse, TRUE_.c_str()) == 0))
	{
		//always a boolean
		element->valueType = JsonElementValueType::_BOOLEAN;
		return;
	}
#endif

	element->valueType = JsonElementValueType::INTEGER;
	return;
	}

char* strncpy(char* dest, char* src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';

	return dest;
}

std::string removingTabsAndBreakLines(std::string json)
{
	vector<int> indexesOFRegex;
	int index = 0;
	ostringstream stream;
	int stringBracketsCounter = 0;
	int secondCounter = 0;
	while (index < json.length())
	{

		if (json[index] == '\"' && stringBracketsCounter > 0)
		{
			stringBracketsCounter--;
		}
		else if (json[index] == '\"')
		{
			stringBracketsCounter++;
		}
		if (stringBracketsCounter < 1)

		{
			if (json[index] == '\t' || json[index] == '\n' || json[index] == ' ' || json[index] == '\r')
			{

			}
			else
			{
				stream << json[index];
			}



		}
		else {

			stream << json[index];
		}


		++index;







	}




	return stream.str();
}

#pragma endregion




#pragma region JSON_API


	 JSONELEMENT* pass_string_to_dll( char* json, long size)
{
	 char* jsonStr = new char[size];
	std::string jsonAsString="";

	//strcpy_s(jsonStr, size, json);
	memcpy_s(jsonStr, size, json, size);
	 //strcpy_s(jsonStr, size, json);
	 JSONString2JsonElement js2je;
	 //strcpy_s(jsonAsString, size, jsonStr);
	 //js2je.ParsedObject(jsonStr);

	return js2je.ParsedObject(jsonStr);
	//return std::string str(jsonStr,size);
	
	
};

	 void* get_string_fromcpp(string RequiredString) {

		 
		 char* smth = new char[RequiredString.length()];

		 strcpy_s(smth, RequiredString.length() + 1, RequiredString.c_str());

		 return smth;

	 }

	 JSONELEMENT* deep_copy(JSONELEMENT* origin)
	 {
		 
		 JSONBuilder jb;
		 return jb.DEEP_COPY(origin);
		 

		 


	 };
	 void empty_json_structure(JSONELEMENT* father) {

		 JSONString2JsonElement js2je;
		 js2je.EmptyAllValues(father);


	 }

	 vector<JSONELEMENT*> findElementsByKey(JSONELEMENT* element, std::string key, std::string FatherKey) {


		 JSONString2JsonElement js2e;

		 return js2e.FindJSONElementByKeyUnderSpecificKeyHirerchy(element, key, FatherKey);


	 }


	 std::vector<JSONELEMENT*> FindJSONElementByKey(JSONELEMENT* element, std::string key) {

		 JSONString2JsonElement js2e;

		 return js2e.FindJSONElementByKey(element, key);

	 }

	 JSONBuilder json_builder() {

		 JSONBuilder jsonBuilder;
		 return jsonBuilder;
	 }

#pragma endregion
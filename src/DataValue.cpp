#include "DataValue.h"
#include <iostream>
#include <string>

using namespace std;

using UndavDataValue::DataValue;



struct UndavDataValue::DataValue
{
	ValueType valueType;
	void *value;

};

bool IsInteger(string value)
{
	bool isInteger = true;
	for(unsigned int indiceValue= 0; indiceValue < value.size() && isInteger; indiceValue++ )
	{
		isInteger = value[indiceValue] >= 48 &&  value[indiceValue] <= 57;
	}
	return isInteger;
}

DataValue* UndavDataValue::Create(string value)
{
	DataValue* newDataValue;
	if(value == "True" or value == "False")
	{
		if(value == "True")
		{
			newDataValue = CreateBoolean(true);
		}
		else
		{
			newDataValue = CreateBoolean(false);
		}
	}
	else if(IsInteger(value))
	{
		newDataValue = CreateNumber(std::stoi(value));
	}
	else if(value.empty())
	{
		newDataValue = CreateNull();
	}
	else
	{
		newDataValue = CreateString(value);
	}
	return newDataValue;
}

UndavDataValue::DataValue*UndavDataValue:: CreateNumber(int value)
{
	DataValue* newDataValue = new DataValue;
	newDataValue->valueType = Number;
	newDataValue->value =  new int;
	*((int *) newDataValue->value) = value;

	return newDataValue;
}

UndavDataValue::DataValue* UndavDataValue::CreateString(string value)
{
	DataValue *newDataValue = new DataValue;
	newDataValue->valueType = String;
	newDataValue->value =  new string;
	*((string*) newDataValue->value) = value;

	return newDataValue;
}

UndavDataValue::DataValue* UndavDataValue::CreateBoolean(bool value)
{
	DataValue *newDataValue = new DataValue;
	newDataValue->valueType = Boolean;
	newDataValue->value = new bool;
	*((bool *)newDataValue->value) = value;
	return newDataValue;
}

UndavDataValue::DataValue* UndavDataValue::CreateNull()
{
	DataValue *newDataValue = new DataValue;
	newDataValue->valueType = Null;
	newDataValue->value = NULL;
	return newDataValue;
}


string	UndavDataValue::Get(const DataValue* value)
{
	string encapsulatedValue;
	if (value->valueType ==String)
	{
		encapsulatedValue = *((string*)value->value);
	}
	if(value->valueType == Boolean)
	{
		if(*((bool*)value->value) == true)
		{
			encapsulatedValue = "True";
		}
		else
			encapsulatedValue = "False" ;
	}
	if (value->valueType == Number)
	{
		encapsulatedValue = std::to_string (*((int*)value->value));
	}
	if (value->valueType == Null)
	{
		encapsulatedValue = "--NULL--";
	}
	return encapsulatedValue;
}

UndavDataValue::ValueType UndavDataValue::GetType(const DataValue* value)
{
	return (value->valueType);
}


UndavDataValue::DataValue* UndavDataValue::Add(const DataValue* leftValue, const DataValue* rigthValue)
{
		DataValue* newDataValue = new DataValue;
		if(leftValue->valueType == Number && rigthValue->valueType == Number)
		{
			int resultSum = *((int*) leftValue->value) + *((int *)rigthValue->value);
			newDataValue = CreateNumber(resultSum);
		}
		else if (leftValue->valueType == String && rigthValue->valueType == String)
		{
			string resultSum = *((string*) leftValue->value) + *((string*) rigthValue->value);
			newDataValue = CreateString(resultSum);
		}
		else if(leftValue->valueType == Boolean && rigthValue->valueType == Boolean)
		{
			bool resultSum = *((bool*)leftValue->value) || *((bool*)rigthValue->value);
			newDataValue = CreateBoolean(resultSum);
		}
		else if(leftValue->valueType == String && rigthValue->valueType == Number)
		{
			string resultSum = *((string*) leftValue->value) + std::to_string(*((int*) rigthValue->value));
			newDataValue = CreateString(resultSum);

		}
		else if(leftValue->valueType == Number && rigthValue->valueType == String)
		{
			string resultSum = std::to_string(*((int*) leftValue->value)) + *((string*) rigthValue->value);
			newDataValue = CreateString(resultSum);
		}
		else
		{
			newDataValue = CreateNull();
		}

		return newDataValue;

}


bool UndavDataValue::Equals(const DataValue* leftValue,const DataValue* rigthValue)
{
	bool equals = false;
	if(leftValue->valueType == rigthValue->valueType)
	{
		ValueType type = GetType(leftValue);
		if (type == Null)
		{
			equals = true;
		}
		else if(type == Number)
		{
			equals = *((int*)leftValue->value) == *((int*) rigthValue->value);
		}
		else if (type == String)
		{
			equals = *((string*)leftValue->value) == *((string*) rigthValue->value);
		}
		else if (type == Boolean)
			equals = *((bool*)leftValue->value) == *((bool*) rigthValue->value);
	}
	return equals;
}


void UndavDataValue::Replace(DataValue* valueToReplace,const DataValue* newValue)
{
	valueToReplace->valueType = newValue->valueType;
	if(valueToReplace->valueType == Null)
	{
		valueToReplace->value = NULL;
	}
	else if(valueToReplace->valueType  == Boolean)
	{
		*((bool *)valueToReplace->value) = *((bool *) newValue->value);
	}
	else if(valueToReplace->valueType  == String)
	{
		*((string*) valueToReplace->value) = *((string*)newValue->value);
	}
	else
	{
		*((int*) valueToReplace->value) = *((int*) newValue->value);
	}


}


bool UndavDataValue::IsLess(const DataValue* leftValue,const DataValue* rigthValue)
{
	bool isLess=false;
	if(leftValue->valueType == rigthValue->valueType)
	{
		if(leftValue->valueType==Number)
		{

			isLess= *((int*)leftValue->value) < *((int*)rigthValue->value);
		}
		else if(leftValue->valueType==String)
				{

					isLess= *((string*)leftValue->value) < *((string*)rigthValue->value);
				}
		if(leftValue->valueType==Boolean)
				{

					isLess= *((bool*)leftValue->value) < *((bool*)rigthValue->value);
				}
	}
	return isLess;
}

void UndavDataValue::DestroyDataValue(DataValue* value)
{
	if (value->valueType == Number)
	{
		delete ((int *)value->value);
	}
	else if(value->valueType==String)
	{
		delete ((string *)value->value);
	}
	else{
		delete ((bool *)value->value);
	}
	delete value;
}


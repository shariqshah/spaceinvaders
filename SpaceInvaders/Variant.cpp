#include "Variant.h"

Variant::Variant()
{
	type = VariantType::None;
}

Variant::Variant(const Variant & other)
{
	type = other.GetType();
	switch(type)
	{
	case VariantType::Int:     data.intVal     = other.GetInt();     break;
	case VariantType::Double:  data.doubleVal  = other.GetDouble();  break;
	case VariantType::Float:   data.floatVal   = other.GetFloat();   break;
	case VariantType::String:  data.stringVal  = other.GetString();  break;
	case VariantType::Bool:    data.boolVal    = other.GetBool();    break;
	case VariantType::VoidPtr: data.voidPtrVal = other.GetVoidPtr(); break;
	};
}

Variant::Variant(int value)
{
	type = VariantType::Int;
	data.intVal = value;
}

Variant::Variant(float value)
{
	data.floatVal = value;
	type = VariantType::Float;
}

Variant::Variant(double value)
{
	data.doubleVal = value;
	type = VariantType::Double;
}

Variant::Variant(const std::string & value)
{
	data.stringVal = value;
	type = VariantType::String;
}

Variant::Variant(bool value)
{
	data.boolVal = value;
	type = VariantType::Bool;
}

Variant::Variant(void * ptr)
{
	data.voidPtrVal = ptr;
	type = VariantType::VoidPtr;
}

Variant::~Variant()
{
}

Variant Variant::operator=(const Variant & other)
{
	return Variant(other);
}

int Variant::GetInt() const
{
	if(type == VariantType::Int)
		return data.intVal;
	else
		return 0;
}

float Variant::GetFloat() const
{
	if(type == VariantType::Float)
		return data.floatVal;
	else
		return 0.0f;
}

double Variant::GetDouble() const
{
	if(type == VariantType::Double)
		return data.doubleVal;
	else
		return 0.0;
}

bool Variant::GetBool() const
{
	if(type == VariantType::Bool)
		return data.boolVal;
	else
		return false;
}

std::string Variant::GetString() const
{
	if(type == VariantType::String)
		return data.stringVal;
	else
		return std::string("");
}

void * Variant::GetVoidPtr() const
{
	if(type == VariantType::VoidPtr)
		return data.voidPtrVal;
	else
		return NULL;
}

#pragma once

#include <string>

enum class VariantType
{
	None = 0,
	Int,
	Uint,
	Float,
	Double,
	String,
	Bool,
	VoidPtr
};

union VariantValue
{
	int intVal;
	uint32_t uintVal;
	float floatVal;
	double doubleVal;
	bool boolVal;
	std::string stringVal;
	void* voidPtrVal;

	VariantValue() {}
	~VariantValue() {}
};

/* 
A data type that can hold values of multiple types. Used when sending event paramaters to methods where the 
type of the paramters is arbitrary and providing method signatures for all possible combinations is cumbersome and
restricting. Instead we use a hash map that contains Variant values mapped to string keys to make things simpler
*/
class Variant
{
	VariantValue data;
	VariantType type;
public:
	Variant();
	Variant(const Variant& other);
	Variant(int value);
	Variant(uint32_t value);
	Variant(float value);
	Variant(double value);
	Variant(const std::string& value);
	Variant(bool value);
	Variant(void* ptr);
	~Variant();

	Variant operator=(const Variant& other);
	VariantType GetType() const { return type; };

	int GetInt() const;
	uint32_t GetUint() const;
	float GetFloat() const;
	double GetDouble() const;
	bool GetBool() const;
	std::string GetString() const;
	void* GetVoidPtr() const;
};


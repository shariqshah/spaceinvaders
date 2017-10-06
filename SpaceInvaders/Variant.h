#pragma once

#include <string>

// A data type that can hold values of multiple types

enum class VariantType
{
	None = 0,
	Int,
	Float,
	Double,
	String,
	Bool,
	VoidPtr
};

union VariantValue
{
	int intVal;
	float floatVal;
	double doubleVal;
	bool boolVal;
	std::string stringVal;
	void* voidPtrVal;

	VariantValue() {}
	~VariantValue() {}
};

class Variant
{
	VariantValue data;
	VariantType type;
public:
	Variant();
	Variant(const Variant& other);
	Variant(int value);
	Variant(float value);
	Variant(double value);
	Variant(const std::string& value);
	Variant(bool value);
	Variant(void* ptr);
	~Variant();

	Variant operator=(const Variant& other);
	VariantType GetType() const { return type; };

	int GetInt() const;
	float GetFloat() const;
	double GetDouble() const;
	bool GetBool() const;
	std::string GetString() const;
	void* GetVoidPtr() const;
};


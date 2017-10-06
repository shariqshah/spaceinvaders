#include "Log.h"

#include <stdio.h>
#include <stdarg.h>

void Log::MessageRaw(const char* message, ...)
{
	va_list list;
	va_start(list, message);
	vprintf(message, list);
	va_end(list);
}

void Log::Message(const char* message, ...)
{
	printf("Message: ");
	va_list list;
	va_start(list, message);
	vprintf(message, list);
	va_end(list);
	printf("\n");
}

void Log::Error(const char* context, const char* errorMessage,...)
{
	printf("Error(%s): ", context);
	va_list list;
	va_start(list, errorMessage);
	vprintf(errorMessage, list);
	va_end(list);
	printf("\n");
}

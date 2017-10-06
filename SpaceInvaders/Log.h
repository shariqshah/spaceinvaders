#ifndef LOG_H
#define LOG_H

namespace Log
{
	void Message(const char* message, ...);
	void MessageRaw(const char* message, ...);
	void Error(const char* context, const char* errorMessage,...);
}

#endif

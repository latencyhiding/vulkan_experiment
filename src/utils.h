#pragma once
#include <cstdio>
#include <iostream>

namespace Utils
{

// Hash combine from boost
template<typename T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

#define LOG(logtype, format, ...) \
    do \
    { \
        fprintf(stderr, logtype " %s::%s, line %d: ", __FILE__, __FUNCTION__, __LINE__); \
        fprintf(stderr, format, ##__VA_ARGS__);                              \
        fprintf(stderr, "\n");                              \
    } while (false);
#define LOG_ERROR(format, ...) LOG("ERROR", format, ##__VA_ARGS__)
#define RUNTIME_ERROR(format, ...)                             \
    do                                                         \
    {                                                          \
        LOG_ERROR(format, ##__VA_ARGS__)\
        exit(2);\
    } while (false);

#ifdef APP_DEBUG

#define LOG_DEBUG(format, ...) LOG("DEBUG", format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) LOG("WARNING", format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) LOG("INFO", format, ##__VA_ARGS__)

#define ASSERT_MSG(cond, msg, ...)  if (!(cond)) { RUNTIME_ERROR("Assertion failed: " #cond ". " msg, ##__VA_ARGS__) };
#define ASSERT_WARN(cond, msg, ...) if (!(cond)) { LOG_WARNING("Assertion failed: " #cond ". " msg, ##__VA_ARGS__) };
#define ASSERT(cond) ASSERT_MSG(cond, "")
    
#else
#define LOG_DEBUG(format, ...)
#define LOG_WARNING(format, ...)
#define LOG_INFO(format, ...)

#define ASSERT_MSG(cond, msg, ...) 
#define ASSERT_WARN(cond, msg, ...)
#define ASSERT(cond)
#endif

#define IMPLEMENT_ME RUNTIME_ERROR("Function %s not implemented!", __func__);

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(*arr))
}
// Description: Precompiled header file for HiveEngine

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>

//Platform detection
#if defined(__linux__)
#define HIVE_PLATFORM_LINUX
#elif defined(_WIN32)
#define HIVE_PLATFORM_WINDOWS
#else
#error "Unsupported platform"
#endif

template<typename T>
using URef = std::unique_ptr<T>;

template<typename T>
using SRef = std::shared_ptr<T>;


//Visibility
#ifdef HEXPORTS
// Exports
#ifdef _MSC_VER
#define HAPI __declspec(dllexport)
#else
#define HAPI __attribute__((visibility("default")))
#endif
#else
// Imports
#ifdef _MSC_VER
#define HAPI __declspec(dllimport)
#else
#define HAPI
#endif
#endif
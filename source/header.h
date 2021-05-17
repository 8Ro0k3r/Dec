#pragma once

#include "vulkan/vulkan.h"
#include <ctype.h>
#include <iostream>
#include <assert.h>
#include <set>
#include <vector>
#include <optional>

#ifdef WIN32
typedef ptrdiff_t   PTRDIFF;
typedef uint64_t    U64;
typedef uint32_t	U32;
typedef int32_t		S32;
typedef uint16_t	U16;
typedef int16_t		S16;
typedef uint8_t		U8;
typedef int8_t		S8;
typedef float		F32;
typedef double		F64;
typedef char		CHAR;
typedef bool		BOOL;

template<class T>
using Vector = std::vector<T>;

template<class T>
using Placehoder = std::optional<T>;

template<class T>
using Set = std::set<T>;

#endif

typedef void(*funcVulkanExtensions)(Vector<const CHAR*>&);
typedef VkResult(*funVulkanCreateSurface)(VkInstance, VkSurfaceKHR&);

#define popAlign(size, alignment) ((size + alignment - 1) & ~(alignment - 1))
#define popArraySize(array) (sizeof(array)/sizeof(array[0]))
#define popLogError(message) std::clog << message << std::endl
#define popNew(object) new object
#define popDelete(pObject) delete(pObject) 

#if defined(Debug)
#define popAssert(expression)	assert(expression) 
#else
#define popAssert(condition)
#endif // defined(Debug)

#if defined(Debug)
#define popCallAPI(call) { \
	VkResult rlt  = call; \
	popAssert(rlt == VK_SUCCESS); \
}

#else
#define popCallAPI(call) call
#endif

#define DEFINE_PRAVATE_MEMBER_HANDLE(classname, name) \
public: \
inline const classname Get##name() const { return m_##name; } \
private: \
classname m_##name;

#define DEFINE_PRAVATE_CONST_MEMBER_REFERENCE(classname, name) \
public: \
inline const classname& Get##name() const { return m_##name; } \
private: \
const classname& m_##name;

#define DEFINE_PRAVATE_MEMBER_BASE_TYPE(classname, name) \
public: \
inline const classname Get##name() const { return m_##name; } \
private: \
classname m_##name;

#define DEFINE_PRAVATE_CONST_MEMBER_PTR(classname, name) \
public: \
inline const classname* Get##name() const { return m_##name; } \
private: \
const classname* m_##name;

#define DEFINE_PRAVATE_MEMBER_PTR(classname, name) \
public: \
inline const classname* Get##name() const { return m_##name; } \
private: \
classname* m_##name;

#define popBegin namespace Dec { 
#define popEnd }; // namespace Dirty

#define pop1080pHeight   1080
#define pop1080pWidth	 1920

const Vector<const char*> g_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };
const Vector<const char*> g_DeviceExtension = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

#include "types.h"
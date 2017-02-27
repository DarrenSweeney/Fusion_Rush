/*
  Copyright (c) 2009 Dave Gamble
 
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
 
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

/*
 * Note: the functions have been moved into the GameSparks namespace to avoid
 * linker errors if the client code also uses cJSON.
 * */

#ifndef cJSON__h
#define cJSON__h

#if !defined(CLASS_DECLSPEC)
#  if PLATFORM_WINDOWS && !IS_MONOLITHIC // we're building a dll on UE4 windows
#    if defined(GS_BUILDING_MODULE) // as opposed to using the dll
#      define CLASS_DECLSPEC __declspec( dllexport )
#    else /* defined(GS_BUILDING_MODULE) */
#      define CLASS_DECLSPEC __declspec( dllimport )
#    endif /* defined(GS_BUILDING_MODULE) */
#  else /* PLATFORM_WINDOWS */
#    define CLASS_DECLSPEC
#  endif /* PLATFORM_WINDOWS */
#endif /* !defined(GS_API) */

#if !defined(CLASS_DECLSPEC)
# if defined(DLL_BUILD) && (defined(WINDOWS_PHONE8)|| defined(WINDOWS_32))
#  ifdef LIBRARY_EXPORTS
#    define CLASS_DECLSPEC    __declspec(dllexport)
#  else
#    define CLASS_DECLSPEC    __declspec(dllimport)
#  endif
# else
#  define CLASS_DECLSPEC
# endif
#endif /* CLASS_DECLSPEC */

//#ifdef __cplusplus
//extern "C"
//{
//#endif

/* cJSON Types: */
#define cJSON_False 0
#define cJSON_True 1
#define cJSON_NULL 2
#define cJSON_Number 3
#define cJSON_String 4
#define cJSON_Array 5
#define cJSON_Object 6
	
#define cJSON_IsReference 256

#include <stdlib.h>

namespace GameSparks {

/* The cJSON structure: */
    typedef struct cJSON {
      struct cJSON *next, *prev;
      /* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
      struct cJSON *child;
      /* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */

      int type;
      /* The type of the item, as above. */

      char *valuestring;
      /* The item's string, if type==cJSON_String */
      int valueint;
      /* The item's number, if type==cJSON_Number */
      double valuedouble;
      /* The item's number, if type==cJSON_Number */

      char *string;                /* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
    } cJSON;

    typedef struct cJSON_Hooks {
      void *(*malloc_fn)(size_t sz);

      void (*free_fn)(void *ptr);
    } cJSON_Hooks;

/* Supply malloc, realloc and free functions to cJSON */
    extern CLASS_DECLSPEC void cJSON_InitHooks(cJSON_Hooks *hooks);


/* Supply a block of JSON, and this returns a cJSON object you can interrogate. Call cJSON_Delete when finished. */
    extern CLASS_DECLSPEC cJSON *cJSON_Parse(const char *value);

/* Render a cJSON entity to text for transfer/storage. Free the char* when finished. */
    extern CLASS_DECLSPEC char *cJSON_Print(cJSON *item);

/* Render a cJSON entity to text for transfer/storage without any formatting. Free the char* when finished. */
    extern CLASS_DECLSPEC char *cJSON_PrintUnformatted(cJSON *item);

/* Delete a cJSON entity and all subentities. */
    extern CLASS_DECLSPEC void cJSON_Delete(cJSON *c);

/* Returns the number of items in an array (or object). */
    extern CLASS_DECLSPEC int cJSON_GetArraySize(cJSON *array);

/* Retrieve item number "item" from array "array". Returns NULL if unsuccessful. */
    extern CLASS_DECLSPEC cJSON *cJSON_GetArrayItem(cJSON *array, int item);

/* Get item "string" from object. Case insensitive. */
    extern CLASS_DECLSPEC cJSON *cJSON_GetObjectItem(cJSON *object, const char *string);

/* For analysing failed parses. This returns a pointer to the parse error. You'll probably need to look a few chars back to make sense of it. Defined when cJSON_Parse() returns 0. 0 when cJSON_Parse() succeeds. */
    extern CLASS_DECLSPEC const char *cJSON_GetErrorPtr(void);

/* These calls create a cJSON item of the appropriate type. */
    extern CLASS_DECLSPEC cJSON *cJSON_CreateNull(void);

    extern CLASS_DECLSPEC cJSON *cJSON_CreateTrue(void);

    extern CLASS_DECLSPEC cJSON *cJSON_CreateFalse(void);

    extern CLASS_DECLSPEC cJSON *cJSON_CreateBool(int b);

    extern CLASS_DECLSPEC cJSON *cJSON_CreateNumber(double num);

    extern CLASS_DECLSPEC cJSON *cJSON_CreateString(const char *string);

    extern CLASS_DECLSPEC cJSON *cJSON_CreateArray(void);

    extern CLASS_DECLSPEC cJSON *cJSON_CreateObject(void);

/* These utilities create an Array of count items. */
    extern CLASS_DECLSPEC cJSON *cJSON_CreateIntArray(const int *numbers, int count);
	
	extern CLASS_DECLSPEC cJSON *cJSON_CreateLongLongArray(const long long *numbers, int count);

    extern CLASS_DECLSPEC cJSON *cJSON_CreateFloatArray(const float *numbers, int count);

    extern CLASS_DECLSPEC cJSON *cJSON_CreateDoubleArray(const double *numbers, int count);

    extern CLASS_DECLSPEC cJSON *cJSON_CreateStringArray(const char **strings, int count);

/* Append item to the specified array/object. */
    extern CLASS_DECLSPEC void cJSON_AddItemToArray(cJSON *array, cJSON *item);

    extern CLASS_DECLSPEC void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);

/* Append reference to item to the specified array/object. Use this when you want to add an existing cJSON to a new cJSON, but don't want to corrupt your existing cJSON. */
    extern CLASS_DECLSPEC void cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item);

    extern CLASS_DECLSPEC void cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item);

/* Remove/Detatch items from Arrays/Objects. */
    extern CLASS_DECLSPEC cJSON *cJSON_DetachItemFromArray(cJSON *array, int which);

    extern CLASS_DECLSPEC void cJSON_DeleteItemFromArray(cJSON *array, int which);

    extern CLASS_DECLSPEC cJSON *cJSON_DetachItemFromObject(cJSON *object, const char *string);

    extern CLASS_DECLSPEC void cJSON_DeleteItemFromObject(cJSON *object, const char *string);

/* Update array items. */
    extern CLASS_DECLSPEC void cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem);

    extern CLASS_DECLSPEC void cJSON_ReplaceItemInObject(cJSON *object, const char *string, cJSON *newitem);

/* Duplicate a cJSON item */
    extern CLASS_DECLSPEC cJSON *cJSON_Duplicate(cJSON *item, int recurse);
/* Duplicate will create a new, identical cJSON item to the one you pass, in new memory that will
need to be released. With recurse!=0, it will duplicate any children connected to the item.
The item->next and ->prev pointers are always zero on return from Duplicate. */

/* ParseWithOpts allows you to require (and check) that the JSON is null terminated, and to retrieve the pointer to the final byte parsed. */
    extern CLASS_DECLSPEC cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end,
                                                     int require_null_terminated);

    extern void cJSON_Minify(char *json);

/* Macros for creating things quickly. */
#define cJSON_AddNullToObject(object, name)        ::GameSparks::cJSON_AddItemToObject(object, name, cJSON_CreateNull())
#define cJSON_AddTrueToObject(object, name)        ::GameSparks::cJSON_AddItemToObject(object, name, cJSON_CreateTrue())
#define cJSON_AddFalseToObject(object, name)       ::GameSparks::cJSON_AddItemToObject(object, name, cJSON_CreateFalse())
#define cJSON_AddBoolToObject(object, name, b)     ::GameSparks::cJSON_AddItemToObject(object, name, cJSON_CreateBool(b))
#define cJSON_AddNumberToObject(object, name, n)   ::GameSparks::cJSON_AddItemToObject(object, name, cJSON_CreateNumber(n))
#define cJSON_AddStringToObject(object, name, s)   ::GameSparks::cJSON_AddItemToObject(object, name, cJSON_CreateString(s))

/* When assigning an integer value, it needs to be propagated to valuedouble too. */
#define cJSON_SetIntValue(object, val)            ((object)?(object)->valueint=(object)->valuedouble=(val):(val))

} /* namespace GameSparks */

//#ifdef __cplusplus
//}
//#endif

#endif

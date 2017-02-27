#ifndef _SYSTEM_FAILABLE_FORWARD_HPP_INCLUDED_
#define _SYSTEM_FAILABLE_FORWARD_HPP_INCLUDED_

#if (defined(__clang__) || (defined(__GNUC__) && __GNUC__ >= 5))
#   if __has_attribute(warn_unused_result)
#   	define GS_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#   endif
#elif defined(_MSC_VER) && !defined(IW_SDK)
#	define GS_WARN_UNUSED_RESULT //_Check_return_
#else
#	define GS_WARN_UNUSED_RESULT
#endif


namespace System
{
    template <typename T>
    class GS_WARN_UNUSED_RESULT Failable;
}


#endif /* _SYSTEM_FAILABLE_FORWARD_HPP_INCLUDED_ */

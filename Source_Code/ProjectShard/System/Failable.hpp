#ifndef _SYSTEM_FAILABLE_HPP_INCLUDED_
#define _SYSTEM_FAILABLE_HPP_INCLUDED_

#include <System/Nullable.hpp>
#include "./Exception.hpp"
#include <System/FailableForward.hpp>
#include <memory>

namespace System {

	/*!
	 * represents either success or failure.
	 * Used as a return type of operations that might fail.
	 * This is necessary because UE4 Android and marmalade
	 * do not support exceptions.
	 * */
	template <typename ResultType>
	class GS_WARN_UNUSED_RESULT Failable
	{
		public:
            // success case
            Failable(const ResultType& o)
			:ok(o) {}

			// result type conversion
			template <typename CompatibleType>
			Failable(const Failable<CompatibleType>& o)
			:Failable(o.ok, o.error)
			{

			}

            // failure case
            Failable(const Exception& e)
			:error(e){}

            bool isOK() const
			{
				assert(error.HasValue() || ok.HasValue());
				return (!error.HasValue());
			}

            const ResultType& GetResult() const
			{
				assert(isOK());
				return ok.Value();
			}

            Exception& GetException()
			{
				assert(!isOK());
				return error.Value();
			}

            //explicit operator const ResultType& () const;
		private:
			template<typename U> friend class Failable;

			Failable(const Nullable<ResultType>& o, const Nullable<Exception>& e)
			:ok(o), error(e) {}

			Nullable<ResultType> ok;
			Nullable<Exception> error;
	};

	template <>
	class GS_WARN_UNUSED_RESULT Failable<void>
	{
	public:
		// success case
		Failable(){}

		// failure case
		Failable(const Exception& e):error(e) {}

		bool isOK() const
		{
			return (!error.HasValue());
		}

		Exception& GetException()
		{
			assert(!isOK());
			assert(error.HasValue());
			return error.Value();
		}
	private:
		Nullable<Exception> error;
	};

} /* namespace System */

/// use this to push the current stack frame to the passed exception and return it as a Failable<T>
#define GS_THROW(exception) \
{ \
	auto tmp = (exception); \
	tmp.PushFrame(__FILE__, __LINE__, __func__); \
	return tmp; \
}

#define GS_UNIQUE_IDENTIFIER_INNER(x, y) x ## y
#define GS_UNIQUE_IDENTIFIER(x, y) GS_UNIQUE_IDENTIFIER_INNER(x, y)

/// use this to assign the *result* of a failable expression *expr* to var_name
/// returns the exception if one occurs.
#define GS_ASSIGN_OR_THROW(var_name, expr) \
	auto var_name##_ = (expr); \
	if(!var_name##_.isOK()) \
		GS_THROW(var_name##_.GetException()); \
	auto var_name = var_name##_.GetResult();

/// use this to call functions that are Failable<void>
#define GS_CALL_OR_THROW(expr) \
    { \
        auto var_name##_ = (expr); \
	    if(!var_name##_.isOK()) \
		    GS_THROW(var_name##_.GetException()); \
    }


#define GS_PROGRAMMING_ERROR(message) \
	assert(false); \
	std::clog << "Programming Error: " << message << std::endl;


/*!
 * Usage Example:

GS_TRY
{
	GS_ASSIGN_OR_CATCH(number, i_dont_throw());
	ASSERT_EQ(number, 42);
	GS_CALL_OR_CATCH(g());
}
GS_CATCH(e)
{
	std::clog << e << std::endl;
}

 Note: only one try/catch block per scope is allowed, also only one GS_CATCH will work as expected

 * */


#define GS_UNIQUE_IDENTIFIER_INNER(x, y) x ## y
#define GS_UNIQUE_IDENTIFIER(x, y) GS_UNIQUE_IDENTIFIER_INNER(x, y)


 /// Note: as this is using a do/while loop behind the curtain, you need to be extra careful with nesting loops inside a
 /// GS_TRY / GS_CATCH construct.
#define GS_TRY \
std::unique_ptr<System::Exception> exception; \
for(int GS_UNIQUE_IDENTIFIER(result, __LINE__) = 0; GS_UNIQUE_IDENTIFIER(result, __LINE__) != 1; ++GS_UNIQUE_IDENTIFIER(result, __LINE__))


#define GS_CATCH(identifier) \
const auto& identifier = *exception; \
if(exception)



// Visual Studio 2013 does not define __func__
#if defined(_MSC_VER) && _MSC_VER <= 1900
#	define __func__ __FUNCTION__
#endif

#define GS_PASS_EXCEPTION_TO_CATCH(expression) \
{\
        exception = std::unique_ptr<System::Exception>(new System::Exception(expression)); \
        exception->PushFrame(__FILE__, __LINE__, __func__); \
        continue; \
}


/// Call *expression* or pass exception to GS_CATCH block. Can only be used inside GS_TRY block.
#define GS_CALL_OR_CATCH(expression) \
    auto GS_UNIQUE_IDENTIFIER(result, __LINE__) = (expression); \
    if(!GS_UNIQUE_IDENTIFIER(result, __LINE__).isOK()) \
    {\
        GS_PASS_EXCEPTION_TO_CATCH(GS_UNIQUE_IDENTIFIER(result, __LINE__).GetException()); \
    }


/// assign result of *expression* to identifier or pass exception to GS_CATCH block. Can only be used inside GS_TRY block.
#define GS_ASSIGN_OR_CATCH(identifier, expression) \
    auto GS_UNIQUE_IDENTIFIER(result, __LINE__) = (expression); \
    if(!GS_UNIQUE_IDENTIFIER(result, __LINE__).isOK()) \
    {\
        GS_PASS_EXCEPTION_TO_CATCH(GS_UNIQUE_IDENTIFIER(result, __LINE__).GetException()); \
    } \
    auto identifier = GS_UNIQUE_IDENTIFIER(result, __LINE__).GetResult();


/// return result of *expression* as Failable<T> or pass exception to GS_CATCH block. Can only be used inside GS_TRY block.
#define GS_RETURN_OR_CATCH(expression) \
	{ \
		auto GS_UNIQUE_IDENTIFIER(result, __LINE__) = (expression); \
        if(!GS_UNIQUE_IDENTIFIER(result, __LINE__).isOK()) \
        {\
            GS_PASS_EXCEPTION_TO_CATCH(GS_UNIQUE_IDENTIFIER(result, __LINE__).GetException()); \
		} \
		else \
		{ \
			return GS_UNIQUE_IDENTIFIER(result, __LINE__); \
		} \
	}


#define GS_RETURN_RESULT_OR_CATCH(expression) \
	{ \
		auto GS_UNIQUE_IDENTIFIER(result, __LINE__) = (expression); \
        if(!GS_UNIQUE_IDENTIFIER(result, __LINE__).isOK()) \
        {\
            GS_PASS_EXCEPTION_TO_CATCH(GS_UNIQUE_IDENTIFIER(result, __LINE__).GetException()); \
		} \
		else \
		{ \
			return GS_UNIQUE_IDENTIFIER(result, __LINE__).GetResult(); \
		} \
	}


#endif /* _SYSTEM_FAILABLE_HPP_INCLUDED_ */

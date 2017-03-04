// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#ifndef GSOptional_h__
#define GSOptional_h__

#pragma once

#include "./gsstl.h"
#include <GameSparks/GSLeakDetector.h>

namespace GameSparks
{
	//! namespace for optional types
	//! This is roughly equivalent to C-Sharps Nullable or boost::optional
	namespace Optional
	{
		/*!
		 *  Template class for optional values.
		 * @tparam ValueType the wrapped data type		 
		 */

		template<typename ValueType>
		class Optional
		{
			public:
				//! construct an empty Optional
				Optional()
	                : m_Value(ValueType())
	                , m_HasValue(false)
				{

				}

				//! construct an Optional from a given value
				Optional(const ValueType& value)
					: m_Value(value)
	                , m_HasValue(true)
				{

				}

				/// construct an optional from value and hasValue
				Optional(const ValueType& value, bool hasValue)
					: m_Value(value)
	                , m_HasValue(hasValue)
				{

				}

				/// copy constructor
				Optional(const Optional& other)
					: m_Value(other.m_Value)
	                , m_HasValue(other.m_HasValue)
				{

				}

				//! compare two Optional<T>. No implicity type conversion will be performed.
				//! Two Optional are equal, if the wrapped value is equal AND both are set.
				Optional& operator=(const Optional& other)
				{
					if (&other != this)
					{
						m_HasValue = other.m_HasValue;
						m_Value = other.m_Value;
					}
					return *this;
				}

				//! return the wrapped value. You have to check HasValue before doing this, otherwise the default constructed wrapped type will be returned.
				ValueType& GetValue()
				{
					return m_Value;
				}

				//! checks whether a value has been set or not
				bool HasValue() const
				{
					return m_HasValue;
				}

			private:
				ValueType m_Value;
				bool m_HasValue;
	            
	            GS_LEAK_DETECTOR(Optional)
        };

		/// an optional string
		typedef Optional<gsstl::string> t_StringOptional;
		/// an optional int
		typedef Optional<int> t_IntOptional;
		/// an optional long
		typedef Optional<long> t_LongOptional;
		/// an optional long long
		typedef Optional<long long> t_LongLongOptional;
		/// an optional float
		typedef Optional<float> t_FloatOptional;
		/// an optional double
		typedef Optional<double> t_DoubleOptional;
		/// an optional bool
		typedef Optional<bool> t_BoolOptional;
	}

}
#endif // GSOptional_h__

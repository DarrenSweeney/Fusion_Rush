#ifndef _SYSTEM_NULLABLE_HPP_
#define _SYSTEM_NULLABLE_HPP_

#include <utility>
#include <algorithm>
#include <cassert>
#include <ostream>
#include <GameSparksRT/GSLinking.hpp>

namespace System {


    /*! Represents a value type that can be assigned null. This is similar to boost::optional<T>.
     *
     * example:
     * @code
     * Nullable<int> a(10);
     * Nullable<int> b(a);
     * std::cout << a << ", " << b << std::endl;
     * std::cout << a == b << std::endl;
     * Nullable<int> c;
     * std::cout << c.GetValueOrDefault(42) << std::endl;
     * @endcode
     */
    template <class T>
    class GS_API Nullable
    {
        public:
            typedef T value_type;

            /// constructs a nulled instance
            Nullable() /* noexcept */
            :val(nullptr) { }

            /// copy constructor
            Nullable(const Nullable& o)
            :val(o.HasValue()?new T(*o.val):nullptr) { }

            /// copy construct a nullable from a T.
            Nullable(const T& v)
            {
                assert(val != &v);
                delete val;
                val = new T(v);
            }

            /// copy construct from a compatible type
            template <typename CompatibleType>
            Nullable(const Nullable<CompatibleType>& o)
            {
                //assert(val != o.val);
                delete val;
                if(o.HasValue())
                    val = new T(o.Value());
            }

            /// destructor
            ~Nullable()
            {
                delete val;
            }

            /// copy constructor
            Nullable& operator=(Nullable o)
            {
                swap(*this, o);
                return *this;
            }

            friend void swap(Nullable& a, Nullable& b)
            {
                using std::swap;
                swap(a.val, b.val);
            }

            const T* operator ->() const { return &Value(); }
            T* operator ->()             { return &Value(); }
            const T& operator *() const  { return Value(); }
            T& operator *()              { return Value(); }

            //explicit operator bool() const /* noexcept */ { return val != nullptr; }

            /// returns the value. make sure to check via HasValue() first or use GetValueOrDefault().
            T const& Value() const
            {
                assert(val);
                return *val;
            }

            /// returns the value. make sure to check via HasValue() first or use GetValueOrDefault().
            T& Value()
            {
                assert(val);
                return *val;
            }

            /// return true, if this value is not null.
            bool HasValue() const
            {
                return val != nullptr;
            }

            /// returns the value or if it is not set returns the default value.
            T GetValueOrDefault(const T& defaultValue) const
            {
                if(this->HasValue()) return Value();
                else return defaultValue;
            }

            /// comparison operator
            bool operator == (const Nullable<T>& o) const
            {
                return (!val && !o.val) || (*val == *o.val);
            }

            /// comparison operator
            bool operator == (const T& o) const
            {
                if(!val) return false;
                return (*val == o);
            }

            /*friend bool operator == (const T& a, const Nullable<T>& b)
            {
                if(!b.val) return false;
                return a == *b.val;
            }*/

            /// ostream operator for debug output.
            friend std::ostream& operator << (std::ostream& os, const Nullable<T>& n)
            {
                if(!n.HasValue()) os << "(null)";
                else os << n.Value();
                return os;
            }
        private:
            template<typename U> friend class Nullable;
            T* val = nullptr;  // exposition only
    };
} // namespace std

#endif /* _SYSTEM_NULLABLE_HPP_ */

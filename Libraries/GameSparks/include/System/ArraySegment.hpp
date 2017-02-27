#ifndef _SYSTEM_ARRAYSEGMENT_HPP_INCLUDED_
#define _SYSTEM_ARRAYSEGMENT_HPP_INCLUDED_

#include <vector>
#include <cassert>

namespace System {

    /// represents a section of a one dimensional array.
    template <typename T>
	class ArraySegment
	{
		public:

		//
		// Properties
		//
	    const std::vector<T>& Array() const {
			return array;
		}

        /// number of bytes in this ArraySegment of the underlying array
	    int Count() const {
            return count;
		}

        /// offset into the underlying array
	    int Offset() const {
            return offset;
		}

		/// Construct and ArraySegment that represents the whole of the passed array.
        /// you need to make sure, that the passed array stay around as long as the ArraySegment.
	    ArraySegment (const std::vector<T>& array_)
        :array(array_)
        ,offset(0)
        ,count(int(array.size()))
        {}

        /// Construct an ArraySegment to represent a section of the passed array.
        /// you need to make sure, that the passed array stay around as long as the ArraySegment.
	    ArraySegment (const std::vector<T>& array_, int offset_, int count_)
        :array(array_)
        ,offset(offset_)
        ,count(count_)
        {
            assert(count >= 0);
            assert(offset >= 0);
            assert(offset+count <= array.size());
        }

        /// compare for equality
        bool operator == (const ArraySegment<T>& o) const
        {
            return count == o.count && offset == o.offset && array == o.array;
        }

        /// compare for inequality
        bool operator != (const ArraySegment<T>& o) const
        {
            return !(*this == o);
        }

        private:
            const std::vector<T>& array;
            int offset;
            int count;
    };

} /* namespace System */

#endif /* _SYSTEM_ARRAYSEGMENT_HPP_INCLUDED_ */

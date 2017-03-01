#include <assert.h>
#include <vector>
#include "./MemoryStream.hpp"
#include "IOException.hpp"
#include "../ArgumentOutOfRangeException.hpp"
#include "../NotSupportedException.hpp"

namespace System { namespace IO {
        MemoryStream::MemoryStream(int capacity)
        {
            if (capacity < 0)
            {
                GS_PROGRAMMING_ERROR("ArgumentOutOfRangeException: capacity");
                //GS_THROW(ArgumentOutOfRangeException("ArgumentOutOfRangeException: capacity"));
            }

            //TODO: error checking. How do we handle a throwing constructor?
            _buffer.resize(capacity);


            _capacity = capacity;
            _expandable = true;
            _writable = true;
            //_exposable = true;
            _origin = 0;      // Must be 0 for byte[]'s created by MemoryStream
            _isOpen = true;
        }

        MemoryStream::~MemoryStream() {

        }

        const Bytes& MemoryStream::GetBuffer() const {
            return _buffer;
        }

        bool MemoryStream::CanRead() const {
            return _isOpen;
        }

        bool MemoryStream::CanWrite() const {
            return _writable;
        }

        Failable<void> MemoryStream::WriteByte(unsigned char value) {
            assert(_isOpen);
            EnsureWriteable();

            if (_position >= _length)
            {
                int newLength = _position + 1;
                bool mustZero = _position > _length;
                if (newLength >= _capacity)
                {
                    GS_ASSIGN_OR_THROW(allocatedNewArray, EnsureCapacity(newLength));
                    if (allocatedNewArray)
                    {
                        mustZero = false;
                    }
                }
                if (mustZero)
                {
                    std::fill(_buffer.begin() + _length, _buffer.end(), 0);
                    //Array.Clear(_buffer, _length, _position - _length);
                }
                _length = newLength;
            }
            _buffer[_position++] = value;
            return {};
        }

        Failable<void> MemoryStream::Write(const System::Bytes &buffer, int offset, int count) {
            if (offset < 0)
            {
                GS_THROW(ArgumentOutOfRangeException("ArgumentOutOfRangeException: offset (NeedNonNegNum)"));
            }
            if (count < 0)
            {
                GS_THROW(ArgumentOutOfRangeException("ArgumentOutOfRangeException: count (NeedNonNegNum)"));
            }
            if (static_cast<int>(buffer.size()) - offset < count)
            {
                GS_THROW(ArgumentException("ArgumentException: InvalidOffLen"));
            }

            assert(_isOpen);
            EnsureWriteable();

            int i = _position + count;
            // Check for overflow
            if (i < 0)
            {
                GS_THROW(IOException("IOException: StreamTooLong"));
            }

            if (i > _length)
            {
                bool mustZero = _position > _length;
                if (i > _capacity)
                {
                    GS_ASSIGN_OR_THROW(allocatedNewArray, EnsureCapacity(i));
                    if (allocatedNewArray)
                    {
                        mustZero = false;
                    }
                }
                if (mustZero)
                {
                    std::fill(_buffer.begin() + _length, _buffer.end(), 0);
                    //Array.Clear(_buffer, _length, i - _length);
                }
                _length = i;
            }
            if ((count <= 8) && (buffer != _buffer))
            {
                int byteCount = count;
                while (--byteCount >= 0)
                {
                    _buffer[_position + byteCount] = buffer[offset + byteCount];
                }
            }
            else
            {
                std::copy(
                    buffer.begin()+offset, buffer.begin()+offset+count,
                    _buffer.begin()+_position
                );
                //Buffer.BlockCopy(buffer, offset, _buffer, _position, count);
            }
            _position = i;
            return {};
        }

        Failable<int> MemoryStream::ReadByte() {
            assert(_isOpen);
            if (_position >= _length)
            {
                return -1;
            }

            return _buffer[_position++];
        }

        Failable<int> MemoryStream::Read(System::Bytes &buffer, int offset, int count) {
            if (offset < 0)
            {
                GS_THROW(ArgumentOutOfRangeException("ArgumentOutOfRangeException: offset (NeedNonNegNum)"));
            }
            if (count < 0)
            {
                GS_THROW(ArgumentOutOfRangeException("ArgumentOutOfRangeException: count (NeedNonNegNum)"));
            }
            if (static_cast<int>(buffer.size()) - offset < count)
            {
                GS_THROW(ArgumentException("ArgumentException: InvalidOffLen"));
            }
            assert(_isOpen);
            int n = _length - _position;
            if (n > count)
            {
                n = count;
            }
            if (n <= 0)
            {
                return 0;
            }

            assert(_position + n >= 0 && "_position + n >= 0");  // len is less than 2^31 -1.

            if (n <= 8)
            {
                int byteCount = n;
                while (--byteCount >= 0)
                    buffer[offset + byteCount] = _buffer[_position + byteCount];
            }
            else
                std::copy(
                    _buffer.begin() + _position, _buffer.begin() + _position + n,
                    buffer.begin() + offset
                );
                //Buffer.BlockCopy(_buffer, _position, buffer, offset, n);
            _position += n;

            return n;
        }

        template <typename T>
        static T unchecked(const T& v)
        {
            return v;
        }

        Failable<int64_t> MemoryStream::Seek(int64_t offset, IO::SeekOrigin loc) {
            assert(_isOpen);
            if (offset > MemStreamMaxLength)
            {
                GS_THROW(ArgumentOutOfRangeException("ArgumentOutOfRangeException: offset (StreamLength)"));
            }

            switch (loc)
            {
                case SeekOrigin::Begin:
                {
                    int tempPosition = unchecked(_origin + (int)offset);
                    if (offset < 0 || tempPosition < _origin)
                    {
                        GS_THROW(IOException("IOException: SeekBeforeBegin"));
                    }

                    _position = tempPosition;
                    break;
                }
                case SeekOrigin::Current:
                {
                    int tempPosition = unchecked(_position + (int)offset);
                    if (unchecked(_position + offset) < _origin || tempPosition < _origin)
                    {
                        GS_THROW(IOException("IOException: SeekBeforeBegin"));
                    }

                    _position = tempPosition;
                    break;
                }
                case SeekOrigin::End:
                {
                    int tempPosition = unchecked(_length + (int)offset);
                    if (unchecked(_length + offset) < _origin || tempPosition < _origin)
                    {
                        GS_THROW(IOException("IOException: SeekBeforeBegin"));
                    }

                    _position = tempPosition;
                    break;
                }
                default:
                    GS_THROW(ArgumentException("ArgumentException: InvalidSeekOrigin"));
            }

            assert(_position >= 0 && "_position >= 0");
            return _position;
        }

        int MemoryStream::Position() const {
            assert(_isOpen);
            return _position - _origin;
        }

        Failable<void> MemoryStream::Position(const int value) {
            if (value < 0)
            {
                GS_THROW(ArgumentOutOfRangeException("ArgumentOutOfRangeException: Value (NeedNonNegNum)"));
            }
            assert(_isOpen);
            if (value > MemStreamMaxLength)
            {
                GS_THROW(ArgumentOutOfRangeException("ArgumentOutOfRangeException: Value (StreamLength)"));
            }

            _position = _origin + (int)value;
            return {};
        }

        void MemoryStream::EnsureWriteable() {
            if (!CanWrite())
            {
                GS_PROGRAMMING_ERROR("NotSupported: UnwritableStream");
            }
        }

        Failable<bool> MemoryStream::EnsureCapacity(int value) {
            // Check for overflow
            if (value < 0)
            {
                GS_THROW(IOException("IOException: StreamTooLong"));
            }
            if (value > _capacity)
            {
                int newCapacity = value;
                if (newCapacity < 256)
                {
                    newCapacity = 256;
                }
                if (newCapacity < _capacity * 2)
                {
                    newCapacity = _capacity * 2;
                }

                GS_CALL_OR_THROW(Capacity(newCapacity));
                return true;
            }
            return false;
        }

        Failable<void> MemoryStream::Capacity(int value) {
            // Only update the capacity if the MS is expandable and the Value is different than the current capacity.
            // Special behavior if the MS isn't expandable: we don't throw if Value is the same as the current capacity
            if (value < Length())
            {
                GS_THROW(ArgumentOutOfRangeException("ArgumentOutOfRangeException: Value (SmallCapacity)"));
            }
            assert(_isOpen);
            if (!_expandable && (value != Capacity()))
            {
                GS_THROW(NotSupportedException("NotSupportedException: MemStreamNotExpandable"));
            }

            // MemoryStream has this invariant: _origin > 0 => !expandable (see ctors)
            if (_expandable && value != _capacity)
            {
                _buffer.resize(value);
                /*if (Value > 0)
                {
                    byte[] newBuffer = new byte[Value];
                    if (_length > 0)
                    {
                        Buffer.BlockCopy(_buffer, 0, newBuffer, 0, _length);
                    }

                    _buffer = newBuffer;
                }
                else
                {
                    _buffer = null;
                }*/
                _capacity = value;
            }
            return {};
        }

        int64_t MemoryStream::Length() const {
            assert(_isOpen);
            return _length - _origin;
        }

        int MemoryStream::Capacity() const {
            assert(_isOpen);
            return _capacity - _origin;
        }
    }} /* namespace System.IO */

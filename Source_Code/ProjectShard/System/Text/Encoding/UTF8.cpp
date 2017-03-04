#include <iterator>

#include "./UTF8.hpp"

namespace System { namespace Text { namespace Encoding {

std::string UTF8::GetString(const System::Bytes& in)
{
    std::string out;
    std::copy(in.begin(), in.end(), std::back_inserter(out));
    return out;
}

std::string UTF8::GetString(const System::Bytes& in, int index, int count)
{

    assert(index < static_cast<int>(in.size()));
    assert(count <= static_cast<int>(in.size())-index);

    std::string out;
    std::copy(in.begin()+index, in.begin()+index+count, std::back_inserter(out));
    return out;
}

System::Bytes UTF8::GetBytes(const std::string& in)
{
    System::Bytes out;
    std::copy(in.begin(), in.end(), std::back_inserter(out));
    return out;
}

}}} /* namespace System.Text.Encoding */

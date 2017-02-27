#include <GameSparksRT/RTData.hpp>
#include <GameSparksRT/Proto/RTVal.hpp>
#include "./Proto/RTData.Serializer.hpp"

namespace GameSparks { namespace RT {

using namespace Proto;

System::Failable<void> RTData::WriteRTData (System::IO::Stream& stream, const RTData& instance)
{
    GS_CALL_OR_THROW(Proto::RTDataSerializer::WriteRTData(stream, instance));
    return {};
}

System::Failable<void> RTData::ReadRTData (System::IO::Stream& stream, System::IO::BinaryReader& br, RTData& instance){
    GS_CALL_OR_THROW(Proto::RTDataSerializer::ReadRTData (stream, br, instance));
    return {};
}

static bool IndexIsValid(uint index)
{
    if(index < 1)
    {
        std::cerr << "RTData field index must be greater than zero." << std::endl;
        return false;
    }

    if(index >= GameSparksRT::MAX_RTDATA_SLOTS)
    {
        std::cerr << "RTData field index must be less than " << GameSparksRT::MAX_RTDATA_SLOTS << "." << std::endl;
        return false;
    }

    return true;
}

System::Nullable<int> RTData::GetInt(uint index) const {
    if(!IndexIsValid(index)) return {};
    if(data[index].long_val.HasValue())
        return (int)(data[index].long_val.Value());
    return {};
}

System::Nullable<RTVector> RTData::GetRTVector(uint index) const {
    if(!IndexIsValid(index)) return {};
    return data[index].vec_val;
}

System::Nullable<int64_t> RTData::GetLong(uint index) const {
    if(!IndexIsValid(index)) return {};
    return data[index].long_val;
}

System::Nullable<float> RTData::GetFloat(uint index) const {
    if(!IndexIsValid(index)) return {};
    return data[index].float_val;
}

System::Nullable<double> RTData::GetDouble(uint index) const {
    if(!IndexIsValid(index)) return {};
    return data[index].double_val;
}

System::Nullable<std::string> RTData::GetString(uint index) const {
    if(!IndexIsValid(index)) return {};
    return data[index].string_val;
}

System::Nullable<RTData> RTData::GetData(uint index) const {
    if(!IndexIsValid(index)) return {};
    return data[index].data_val;
}

RTData &RTData::SetInt(uint index, int value) {
    if(!IndexIsValid(index)) return *this;
    data[index] = RTVal((int64_t)value);
    return *this;
}

RTData &RTData::SetLong(uint index, int64_t value) {
    if(!IndexIsValid(index)) return *this;
    data[index] = RTVal(value);
    return *this;
}

RTData &RTData::SetRTVector(uint index, RTVector value) {
    if(!IndexIsValid(index)) return *this;
    data[index] = RTVal(value);
    return *this;
}

RTData &RTData::SetFloat(uint index, float value) {
    if(!IndexIsValid(index)) return *this;
    data[index] = RTVal(value);
    return *this;
}

RTData &RTData::SetDouble(uint index, double value) {
    if(!IndexIsValid(index)) return *this;
    data[index] = RTVal(value);
    return *this;
}

RTData &RTData::SetString(uint index, const std::string &value) {
    if(!IndexIsValid(index)) return *this;
    data[index] = RTVal(value);
    return *this;
}

RTData &RTData::SetData(uint index, const RTData &value) {
    if(!IndexIsValid(index)) return *this;
    data[index] = RTVal(value);
    return *this;
}

std::ostream& operator << (std::ostream& os, const RTVector& p)
{
    os << "(";
    if(p.x.HasValue()) os << "x=" << p.x.Value() << ", ";
    if(p.y.HasValue()) os << "y=" << p.y.Value() << ", ";
    if(p.z.HasValue()) os << "z=" << p.z.Value() << ", ";
    if(p.w.HasValue()) os << "w=" << p.w.Value() << ", ";
    os << ")";
    return os;
}


GS_API std::ostream &operator<<(std::ostream &os, const RTData &p) {
    os << " {";

    auto i=0;
    for(const auto& val : p.data)
    {
        if(val)
        {
            os << " [" << i << " " << val << "] ";
        }
        ++i;
    }
    os << "} ";
    return os;
}


}} /* namespace GameSparks.RT */

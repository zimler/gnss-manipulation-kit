#include "InertialMeasurementsStdMessage.h"
#include <cassert>

namespace Greis
{
    InertialMeasurementsStdMessage::InertialMeasurementsStdMessage( const char* pc_message, int p_length ) 
        : _id(pc_message, 2), _bodySize(p_length - HeadSize())
    {
        char* p_message = const_cast<char*>(pc_message);
        
        p_message += HeadSize();
    
        _serializer.Deserialize(p_message, sizeof(std::vector<Types::f4>::value_type) * 3, _accelerations);
        p_message += sizeof(std::vector<Types::f4>::value_type) * 3;
        _serializer.Deserialize(p_message, sizeof(std::vector<Types::f4>::value_type) * 3, _angularVelocities);
        p_message += sizeof(std::vector<Types::f4>::value_type) * 3;
        _serializer.Deserialize(p_message, _cs);
        p_message += sizeof(_cs);
        
        assert(p_message - pc_message == p_length);
    }

    std::string InertialMeasurementsStdMessage::ToString() const
    {
        return toString("InertialMeasurementsStdMessage");
    }
    bool InertialMeasurementsStdMessage::Validate() const
    {
        if (!Validate())
        {
            return false;
        }

        auto message = ToByteArray();
        return validateChecksum8Bin(message.data(), message.size());
    }

    QByteArray InertialMeasurementsStdMessage::ToByteArray() const
    {
        QByteArray result;
        result.append(headToByteArray());

        _serializer.Serialize(_accelerations, result);
        _serializer.Serialize(_angularVelocities, result);
        _serializer.Serialize(_cs, result);
        
        assert(result.size() == Size());
        return result;
    }
}
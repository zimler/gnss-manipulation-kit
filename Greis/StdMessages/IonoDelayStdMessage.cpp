#include "IonoDelayStdMessage.h"
#include <cassert>

namespace Greis
{
    IonoDelayStdMessage::IonoDelayStdMessage( const char* pc_message, int p_length ) 
        : _id(pc_message, 2), _bodySize(p_length - HeadSize())
    {
        char* p_message = const_cast<char*>(pc_message);
        
        p_message += HeadSize();
    
        int arraySizeInUniformFillFields = (BodySize() - 1) / 4;

        _serializer.Deserialize(p_message, sizeof(std::vector<Types::f4>::value_type) * arraySizeInUniformFillFields, _delay);
        p_message += sizeof(std::vector<Types::f4>::value_type) * arraySizeInUniformFillFields;
        _serializer.Deserialize(p_message, _cs);
        p_message += sizeof(_cs);
        
        assert(p_message - pc_message == p_length);
    }
    
    IonoDelayStdMessage::IonoDelayStdMessage( const std::string& p_id, int p_bodySize ) 
        : _id(p_id), _bodySize(p_bodySize)
    {
    }

    std::string IonoDelayStdMessage::ToString() const
    {
        return toString("IonoDelayStdMessage");
    }
    bool IonoDelayStdMessage::Validate() const
    {
        if (!StdMessage::Validate())
        {
            return false;
        }

        auto message = ToByteArray();
        return validateChecksum8Bin(message.data(), message.size());
    }

    QByteArray IonoDelayStdMessage::ToByteArray() const
    {
        QByteArray result;
        result.append(headToByteArray());

        _serializer.Serialize(_delay, result);
        _serializer.Serialize(_cs, result);
        
        assert(result.size() == Size());
        return result;
    }
}

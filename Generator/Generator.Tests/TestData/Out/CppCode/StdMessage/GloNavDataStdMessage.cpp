#include "GloNavDataStdMessage.h"
#include <cassert>
#include "ChecksumComputer.h"
#include "Common/Logger.h"

namespace Greis
{
    GloNavDataStdMessage::GloNavDataStdMessage( const char* pc_message, int p_length ) 
        : _id(pc_message, 2), _bodySize(p_length - HeadSize())
    {
        char* p_message = const_cast<char*>(pc_message);
        
        p_message += HeadSize();
    
        int arraySizeInUniformFillFields = (BodySize() - 2) / 18;

        _serializer.Deserialize(p_message, _recSize);
        p_message += sizeof(_recSize);
        _serializer.Deserialize(p_message, 18 * arraySizeInUniformFillFields, 18, _dat);
        p_message += 18 * arraySizeInUniformFillFields;
        _serializer.Deserialize(p_message, _cs);
        p_message += sizeof(_cs);

        _isCorrect = (p_message - pc_message == p_length);
        if (!_isCorrect)
        {
            sLogger.Debug(QString("The message %1 is incorrect. Excepted size is %2 whilst the actual size is %3.")
                .arg(QString::fromStdString(ToString())).arg(p_length).arg(p_message - pc_message));
        }
    }
    
    GloNavDataStdMessage::GloNavDataStdMessage( const std::string& p_id, int p_size ) 
        : _id(p_id), _bodySize(p_size - HeadSize())
    {
        _isCorrect = true;
    }

    std::string GloNavDataStdMessage::ToString() const
    {
        return toString("GloNavDataStdMessage");
    }
    
    bool GloNavDataStdMessage::Validate() const
    {
        if (!_isCorrect || !StdMessage::Validate())
        {
            return false;
        }

        auto message = ToByteArray();
        return validateChecksum8Bin(message.data(), message.size());
    }
    
    void GloNavDataStdMessage::RecalculateChecksum()
    {
        if (!_isCorrect)
        {
            return;
        }
        auto message = ToByteArray();
        _cs = ChecksumComputer::ComputeCs8(message, message.size() - 1);
    }

    QByteArray GloNavDataStdMessage::ToByteArray() const
    {
        QByteArray result;
        if (!_isCorrect)
        {
            return result;
        }

        result.append(headToByteArray());

        _serializer.Serialize(_recSize, result);
        _serializer.Serialize(_dat, result);
        _serializer.Serialize(_cs, result);
        
        assert(result.size() == Size());
        return result;
    }
}

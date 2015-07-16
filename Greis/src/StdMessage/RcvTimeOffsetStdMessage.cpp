#include "RcvTimeOffsetStdMessage.h"
#include <cassert>
#include "Common/Logger.h"
#include "Greis/ChecksumComputer.h"

namespace Greis
{
    RcvTimeOffsetStdMessage::RcvTimeOffsetStdMessage( const char* pc_message, int p_length ) 
        : _id(pc_message, 2), _bodySize(p_length - HeadSize())
    {
        char* p_message = const_cast<char*>(pc_message);
        
        p_message += HeadSize();
    
        _serializer.Deserialize(p_message, _val);
        p_message += sizeof(_val);
        _serializer.Deserialize(p_message, _sval);
        p_message += sizeof(_sval);
        _serializer.Deserialize(p_message, _cs);
        p_message += sizeof(_cs);

        _isCorrect = (p_message - pc_message == p_length);
        if (!_isCorrect)
        {
            sLogger.Debug(QString("The message %1 is incorrect. Excepted size is %2 whilst the actual size is %3.")
                .arg(QString::fromStdString(ToString())).arg(p_length).arg(p_message - pc_message));
        }
    }
    
    RcvTimeOffsetStdMessage::RcvTimeOffsetStdMessage( const std::string& p_id, int p_size ) 
        : _id(p_id), _bodySize(p_size - HeadSize())
    {
        _isCorrect = true;
    }

    RcvTimeOffsetStdMessage::RcvTimeOffsetStdMessage()
    {
        _id = "TO";
        _bodySize = 17;
        _isCorrect = true;
    }

    RcvTimeOffsetStdMessage::RcvTimeOffsetStdMessage(const std::string& p_id)
    {
        _id = p_id;
        _bodySize = 17;
        _isCorrect = true;
    }

    const std::string RcvTimeOffsetStdMessage::Codes::Code_TO = "TO";

    std::string RcvTimeOffsetStdMessage::ToString() const
    {
        return toString("RcvTimeOffsetStdMessage");
    }
    
    bool RcvTimeOffsetStdMessage::Validate() const
    {
        if (!_isCorrect || !StdMessage::Validate())
        {
            return false;
        }

        auto message = ToByteArray();
        return validateChecksum8Bin(message.data(), message.size());
    }
    
    void RcvTimeOffsetStdMessage::RecalculateChecksum()
    {
        if (!_isCorrect)
        {
            return;
        }
        auto message = ToByteArray();
        _cs = ChecksumComputer::ComputeCs8(message, message.size() - 1);
    }

    QByteArray RcvTimeOffsetStdMessage::ToByteArray() const
    {
        QByteArray result;
        if (!_isCorrect)
        {
            return result;
        }

        result.append(headToByteArray());

        _serializer.Serialize(_val, result);
        _serializer.Serialize(_sval, result);
        _serializer.Serialize(_cs, result);
        
        assert(result.size() == Size());
        return result;
    }
}

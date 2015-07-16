#include "EpochEndStdMessage.h"
#include <cassert>
#include "Common/Logger.h"
#include "Greis/ChecksumComputer.h"

namespace Greis
{
    EpochEndStdMessage::EpochEndStdMessage( const char* pc_message, int p_length ) 
        : _id(pc_message, 2), _bodySize(p_length - HeadSize())
    {
        char* p_message = const_cast<char*>(pc_message);
        
        p_message += HeadSize();
    
        _serializer.Deserialize(p_message, _cs);
        p_message += sizeof(_cs);

        _isCorrect = (p_message - pc_message == p_length);
        if (!_isCorrect)
        {
            sLogger.Debug(QString("The message %1 is incorrect. Excepted size is %2 whilst the actual size is %3.")
                .arg(QString::fromStdString(ToString())).arg(p_length).arg(p_message - pc_message));
        }
    }
    
    EpochEndStdMessage::EpochEndStdMessage( const std::string& p_id, int p_size ) 
        : _id(p_id), _bodySize(p_size - HeadSize())
    {
        _isCorrect = true;
    }

    EpochEndStdMessage::EpochEndStdMessage()
    {
        _id = "||";
        _bodySize = 1;
        _isCorrect = true;
    }

    EpochEndStdMessage::EpochEndStdMessage(const std::string& p_id)
    {
        _id = p_id;
        _bodySize = 1;
        _isCorrect = true;
    }

    const std::string EpochEndStdMessage::Codes::Code = "||";

    std::string EpochEndStdMessage::ToString() const
    {
        return toString("EpochEndStdMessage");
    }
    
    bool EpochEndStdMessage::Validate() const
    {
        if (!_isCorrect || !StdMessage::Validate())
        {
            return false;
        }

        auto message = ToByteArray();
        return validateChecksum8Bin(message.data(), message.size());
    }
    
    void EpochEndStdMessage::RecalculateChecksum()
    {
        if (!_isCorrect)
        {
            return;
        }
        auto message = ToByteArray();
        _cs = ChecksumComputer::ComputeCs8(message, message.size() - 1);
    }

    QByteArray EpochEndStdMessage::ToByteArray() const
    {
        QByteArray result;
        if (!_isCorrect)
        {
            return result;
        }

        result.append(headToByteArray());

        _serializer.Serialize(_cs, result);
        
        assert(result.size() == Size());
        return result;
    }
}

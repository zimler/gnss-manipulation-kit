#include "HeadAndPitchStdMessage.h"
#include <cassert>
#include "Common/Logger.h"
#include "Greis/ChecksumComputer.h"

namespace Greis
{
    HeadAndPitchStdMessage::HeadAndPitchStdMessage( const char* pc_message, int p_length ) 
        : _id(pc_message, 2), _bodySize(p_length - HeadSize())
    {
        char* p_message = const_cast<char*>(pc_message);
        
        p_message += HeadSize();
    
        _serializer.Deserialize(p_message, _heading);
        p_message += sizeof(_heading);
        _serializer.Deserialize(p_message, _pitch);
        p_message += sizeof(_pitch);
        _serializer.Deserialize(p_message, _solType);
        p_message += sizeof(_solType);
        _serializer.Deserialize(p_message, _cs);
        p_message += sizeof(_cs);

        _isCorrect = (p_message - pc_message == p_length);
        if (!_isCorrect)
        {
            sLogger.Debug(QString("The message %1 is incorrect. Excepted size is %2 whilst the actual size is %3.")
                .arg(QString::fromStdString(ToString())).arg(p_length).arg(p_message - pc_message));
        }
    }
    
    HeadAndPitchStdMessage::HeadAndPitchStdMessage( const std::string& p_id, int p_size ) 
        : _id(p_id), _bodySize(p_size - HeadSize())
    {
        _isCorrect = true;
    }

    HeadAndPitchStdMessage::HeadAndPitchStdMessage()
    {
        _id = "ha";
        _bodySize = 10;
        _isCorrect = true;
    }

    HeadAndPitchStdMessage::HeadAndPitchStdMessage(const std::string& p_id)
    {
        _id = p_id;
        _bodySize = 10;
        _isCorrect = true;
    }

    const std::string HeadAndPitchStdMessage::Codes::Code_ha = "ha";

    std::string HeadAndPitchStdMessage::ToString() const
    {
        return toString("HeadAndPitchStdMessage");
    }
    
    bool HeadAndPitchStdMessage::Validate() const
    {
        if (!_isCorrect || !StdMessage::Validate())
        {
            return false;
        }

        auto message = ToByteArray();
        return validateChecksum8Bin(message.data(), message.size());
    }
    
    void HeadAndPitchStdMessage::RecalculateChecksum()
    {
        if (!_isCorrect)
        {
            return;
        }
        auto message = ToByteArray();
        _cs = ChecksumComputer::ComputeCs8(message, message.size() - 1);
    }

    QByteArray HeadAndPitchStdMessage::ToByteArray() const
    {
        QByteArray result;
        if (!_isCorrect)
        {
            return result;
        }

        result.append(headToByteArray());

        _serializer.Serialize(_heading, result);
        _serializer.Serialize(_pitch, result);
        _serializer.Serialize(_solType, result);
        _serializer.Serialize(_cs, result);
        
        assert(result.size() == Size());
        return result;
    }
}

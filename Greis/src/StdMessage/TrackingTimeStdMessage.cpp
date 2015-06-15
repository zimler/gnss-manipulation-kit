#include "TrackingTimeStdMessage.h"
#include <cassert>
#include "Common/Logger.h"
#include "Greis/ChecksumComputer.h"

namespace Greis
{
    TrackingTimeStdMessage::TrackingTimeStdMessage( const char* pc_message, int p_length ) 
        : _id(pc_message, 2), _bodySize(p_length - HeadSize())
    {
        char* p_message = const_cast<char*>(pc_message);
        
        p_message += HeadSize();
    
        _serializer.Deserialize(p_message, _tt);
        p_message += sizeof(_tt);
        _serializer.Deserialize(p_message, _cs);
        p_message += sizeof(_cs);

        _isCorrect = (p_message - pc_message == p_length);
        if (!_isCorrect)
        {
            sLogger.Debug(QString("The message %1 is incorrect. Excepted size is %2 whilst the actual size is %3.")
                .arg(QString::fromStdString(ToString())).arg(p_length).arg(p_message - pc_message));
        }
    }
    
    TrackingTimeStdMessage::TrackingTimeStdMessage( const std::string& p_id, int p_size ) 
        : _id(p_id), _bodySize(p_size - HeadSize())
    {
        _isCorrect = true;
    }

    TrackingTimeStdMessage::TrackingTimeStdMessage()
    {
        _id = "TT";
        _bodySize = 5;
        _isCorrect = true;
    }

    TrackingTimeStdMessage::TrackingTimeStdMessage(const std::string& p_id)
    {
        _id = p_id;
        _bodySize = 5;
        _isCorrect = true;
    }

    const std::string TrackingTimeStdMessage::Codes::Code_TT = "TT";

    std::string TrackingTimeStdMessage::ToString() const
    {
        return toString("TrackingTimeStdMessage");
    }
    
    bool TrackingTimeStdMessage::Validate() const
    {
        if (!_isCorrect || !StdMessage::Validate())
        {
            return false;
        }

        auto message = ToByteArray();
        return validateChecksum8Bin(message.data(), message.size());
    }
    
    void TrackingTimeStdMessage::RecalculateChecksum()
    {
        if (!_isCorrect)
        {
            return;
        }
        auto message = ToByteArray();
        _cs = ChecksumComputer::ComputeCs8(message, message.size() - 1);
    }

    QByteArray TrackingTimeStdMessage::ToByteArray() const
    {
        QByteArray result;
        if (!_isCorrect)
        {
            return result;
        }

        result.append(headToByteArray());

        _serializer.Serialize(_tt, result);
        _serializer.Serialize(_cs, result);
        
        assert(result.size() == Size());
        return result;
    }
}

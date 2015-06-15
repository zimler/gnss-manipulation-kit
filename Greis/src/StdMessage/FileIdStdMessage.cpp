#include "FileIdStdMessage.h"
#include <cassert>
#include "Common/Logger.h"
#include "Greis/ChecksumComputer.h"

namespace Greis
{
    FileIdStdMessage::FileIdStdMessage( const char* pc_message, int p_length ) 
        : _id(pc_message, 2), _bodySize(p_length - HeadSize())
    {
        char* p_message = const_cast<char*>(pc_message);
        
        p_message += HeadSize();
    
        _serializer.Deserialize(p_message, 5, _idField);
        p_message += 5;
        _serializer.Deserialize(p_message, 80, _description);
        p_message += 80;

        _isCorrect = (p_message - pc_message == p_length);
        if (!_isCorrect)
        {
            sLogger.Debug(QString("The message %1 is incorrect. Excepted size is %2 whilst the actual size is %3.")
                .arg(QString::fromStdString(ToString())).arg(p_length).arg(p_message - pc_message));
        }
    }
    
    FileIdStdMessage::FileIdStdMessage( const std::string& p_id, int p_size ) 
        : _id(p_id), _bodySize(p_size - HeadSize())
    {
        _isCorrect = true;
    }

    FileIdStdMessage::FileIdStdMessage()
    {
        _id = "JP";
        _bodySize = 85;
        _isCorrect = true;
    }

    FileIdStdMessage::FileIdStdMessage(const std::string& p_id)
    {
        _id = p_id;
        _bodySize = 85;
        _isCorrect = true;
    }

    const std::string FileIdStdMessage::Codes::Code_JP = "JP";

    std::string FileIdStdMessage::ToString() const
    {
        return toString("FileIdStdMessage");
    }
    
    bool FileIdStdMessage::Validate() const
    {
        if (!_isCorrect || !StdMessage::Validate())
        {
            return false;
        }

        return true;
    }
    
    void FileIdStdMessage::RecalculateChecksum()
    {
        if (!_isCorrect)
        {
            return;
        }
        
    }

    QByteArray FileIdStdMessage::ToByteArray() const
    {
        QByteArray result;
        if (!_isCorrect)
        {
            return result;
        }

        result.append(headToByteArray());

        _serializer.Serialize(_idField, result);
        _serializer.Serialize(_description, result);
        
        assert(result.size() == Size());
        return result;
    }
}

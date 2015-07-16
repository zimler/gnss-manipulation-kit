#include "CPStdMessage.h"
#include <cassert>
#include "Common/Logger.h"
#include "Greis/ChecksumComputer.h"

namespace Greis
{
    CPStdMessage::CPStdMessage( const char* pc_message, int p_length ) 
        : _id(pc_message, 2), _bodySize(p_length - HeadSize())
    {
        char* p_message = const_cast<char*>(pc_message);
        
        p_message += HeadSize();
    
        int arraySizeInUniformFillFields = (BodySize() - 1) / 8;

        _serializer.Deserialize(p_message, sizeof(std::vector<Types::f8>::value_type) * arraySizeInUniformFillFields, _cp);
        p_message += sizeof(std::vector<Types::f8>::value_type) * arraySizeInUniformFillFields;
        _serializer.Deserialize(p_message, _cs);
        p_message += sizeof(_cs);

        _isCorrect = (p_message - pc_message == p_length);
        if (!_isCorrect)
        {
            sLogger.Debug(QString("The message %1 is incorrect. Excepted size is %2 whilst the actual size is %3.")
                .arg(QString::fromStdString(ToString())).arg(p_length).arg(p_message - pc_message));
        }
    }
    
    CPStdMessage::CPStdMessage( const std::string& p_id, int p_size ) 
        : _id(p_id), _bodySize(p_size - HeadSize())
    {
        _isCorrect = true;
    }

    const std::string CPStdMessage::Codes::Code_PC = "PC";
    const std::string CPStdMessage::Codes::Code_P1 = "P1";
    const std::string CPStdMessage::Codes::Code_P2 = "P2";
    const std::string CPStdMessage::Codes::Code_P3 = "P3";
    const std::string CPStdMessage::Codes::Code_P5 = "P5";
    const std::string CPStdMessage::Codes::Code_Pl = "Pl";

    std::string CPStdMessage::ToString() const
    {
        return toString("CPStdMessage");
    }
    
    bool CPStdMessage::Validate() const
    {
        if (!_isCorrect || !StdMessage::Validate())
        {
            return false;
        }

        auto message = ToByteArray();
        return validateChecksum8Bin(message.data(), message.size());
    }
    
    void CPStdMessage::RecalculateChecksum()
    {
        if (!_isCorrect)
        {
            return;
        }
        auto message = ToByteArray();
        _cs = ChecksumComputer::ComputeCs8(message, message.size() - 1);
    }

    QByteArray CPStdMessage::ToByteArray() const
    {
        QByteArray result;
        if (!_isCorrect)
        {
            return result;
        }

        result.append(headToByteArray());

        _serializer.Serialize(_cp, result);
        _serializer.Serialize(_cs, result);
        
        assert(result.size() == Size());
        return result;
    }
}

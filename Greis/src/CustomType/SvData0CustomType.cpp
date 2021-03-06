#include "SvData0CustomType.h"
#include <cassert>
#include "Common/Logger.h"

namespace Greis
{
    SvData0CustomType::SvData0CustomType( const char* pc_message, int p_length )
        : _size(p_length)
    {
        char* p_message = const_cast<char*>(pc_message);
    
        _serializer.Deserialize(p_message, _prn);
        p_message += sizeof(_prn);
        _serializer.Deserialize(p_message, _cnt);
        p_message += sizeof(_cnt);
        _serializer.Deserialize(p_message, sizeof(std::vector<Types::u4>::value_type) * 10, _data);
        p_message += sizeof(std::vector<Types::u4>::value_type) * 10;

        _isCorrect = (p_message - pc_message == p_length);
        if (!_isCorrect)
        {
            sLogger.Debug(QString("The custom type %1 is incorrect. Excepted size is %2 whilst the actual size is %3.")
                .arg(IdNumber()).arg(p_length).arg(p_message - pc_message));
        }
    }
    
    SvData0CustomType::SvData0CustomType( int p_size ) 
        : _size(p_size)
    {
        _isCorrect = true;
    }

    QByteArray SvData0CustomType::ToByteArray() const
    {
        QByteArray result;
        if (!_isCorrect)
        {
            return result;
        }

        _serializer.Serialize(_prn, result);
        _serializer.Serialize(_cnt, result);
        _serializer.Serialize(_data, result);
        
        assert(result.size() == Size());
        return result;
    }
}

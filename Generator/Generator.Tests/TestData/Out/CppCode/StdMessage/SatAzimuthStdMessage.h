#ifndef SatAzimuthStdMessage_h__
#define SatAzimuthStdMessage_h__

#include <QtCore/QByteArray>
#include "StdMessage.h"
#include "EMessageId.h"

namespace Greis
{
    class SatAzimuthStdMessage : public StdMessage
    {
    public:
        SMART_PTR_T(SatAzimuthStdMessage);

        SatAzimuthStdMessage(const char* p_message, int p_length);
        SatAzimuthStdMessage(const std::string& p_id, int p_size);

        virtual std::string ToString() const;
        virtual std::string Id() const { return _id; }
        virtual EMessageId::Type IdNumber() const { return EMessageId::SatAzimuth; }
        virtual bool Validate() const;
        virtual bool IsCorrect() const { return _isCorrect; }
        virtual void RecalculateChecksum();
        virtual int BodySize() const { return _bodySize; }
        virtual QByteArray ToByteArray() const;
        
        // Azimuth angle [degrees*2] [0�180)
        const std::vector<Types::u1>& Azim() const { return _azim; }
        std::vector<Types::u1>& Azim() { return _azim; }

        // Checksum
        const Types::u1& Cs() const { return _cs; }
        Types::u1& Cs() { return _cs; }
    private:
        std::string _id;
        int _bodySize;
        bool _isCorrect;

        std::vector<Types::u1> _azim;
        Types::u1 _cs;
    };
}

#endif // SatAzimuthStdMessage_h__

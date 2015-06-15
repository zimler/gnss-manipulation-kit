#pragma once

#include <QtCore/QByteArray>
#include "Greis/StdMessage.h"
#include "Greis/EMessageId.h"

namespace Greis
{
    class PPSOffsetStdMessage : public StdMessage
    {
    public:
        SMART_PTR_T(PPSOffsetStdMessage);

        PPSOffsetStdMessage(const char* p_message, int p_length);
        PPSOffsetStdMessage(const std::string& p_id, int p_size);
        
        struct Codes
        {
            static const std::string Code_ZA;
            static const std::string Code_ZB;
        };
        
        virtual std::string ToString() const;
        virtual std::string Id() const { return _id; }
        virtual EMessageId::Type IdNumber() const { return EMessageId::PPSOffset; }
        virtual bool Validate() const;
        virtual bool IsCorrect() const { return _isCorrect; }
        virtual void RecalculateChecksum();
        virtual int BodySize() const { return _bodySize; }
        virtual QByteArray ToByteArray() const;
        
        // PPS offset in nanoseconds
        const Types::f4& Offs() const { return _offs; }
        Types::f4& Offs() { return _offs; }

        // Checksum
        const Types::u1& Cs() const { return _cs; }
        Types::u1& Cs() { return _cs; }
    private:
        std::string _id;
        int _bodySize;
        bool _isCorrect;

        Types::f4 _offs;
        Types::u1 _cs;
    };
}

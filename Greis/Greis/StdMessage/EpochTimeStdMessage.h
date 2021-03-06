#pragma once

#include <QtCore/QByteArray>
#include "Greis/StdMessage.h"
#include "Greis/EMessageId.h"

namespace Greis
{
    class EpochTimeStdMessage : public StdMessage
    {
    public:
        SMART_PTR_T(EpochTimeStdMessage);

        EpochTimeStdMessage(const char* p_message, int p_length);
        EpochTimeStdMessage(const std::string& p_id, int p_size);

        virtual std::string ToString() const;
        virtual std::string Id() const { return _id; }
        virtual EMessageId::Type IdNumber() const { return EMessageId::EpochTime; }
        virtual bool Validate() const;
        virtual bool IsCorrect() const { return _isCorrect; }
        virtual void RecalculateChecksum();
        virtual int BodySize() const { return _bodySize; }
        virtual QByteArray ToByteArray() const;
        
        // Tr modulo 1 day (86400000 ms) [ms]
        const Types::u4& Tod() const { return _tod; }
        Types::u4& Tod() { return _tod; }

        // Checksum
        const Types::u1& Cs() const { return _cs; }
        Types::u1& Cs() { return _cs; }
    private:
        std::string _id;
        int _bodySize;
        bool _isCorrect;

        Types::u4 _tod;
        Types::u1 _cs;
    };
}

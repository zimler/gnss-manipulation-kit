#pragma once

#include <QtCore/QByteArray>
#include "Greis/StdMessage.h"
#include "Greis/EMessageId.h"

namespace Greis
{
    class SRPRStdMessage : public StdMessage
    {
    public:
        SMART_PTR_T(SRPRStdMessage);

        SRPRStdMessage(const char* p_message, int p_length);
        SRPRStdMessage(const std::string& p_id, int p_size);
        
        struct Codes
        {
            static const std::string Code_1r;
            static const std::string Code_2r;
            static const std::string Code_3r;
            static const std::string Code_5r;
            static const std::string Code_lr;
        };
        
        virtual std::string ToString() const;
        virtual std::string Id() const { return _id; }
        virtual EMessageId::Type IdNumber() const { return EMessageId::SRPR; }
        virtual bool Validate() const;
        virtual bool IsCorrect() const { return _isCorrect; }
        virtual void RecalculateChecksum();
        virtual int BodySize() const { return _bodySize; }
        virtual QByteArray ToByteArray() const;
        
        // (PR[s] - CA/L1 PR[s] - 2*10-7) * 1011
        const std::vector<Types::i2>& Srpr() const { return _srpr; }
        std::vector<Types::i2>& Srpr() { return _srpr; }

        // Checksum
        const Types::u1& Cs() const { return _cs; }
        Types::u1& Cs() { return _cs; }
    private:
        std::string _id;
        int _bodySize;
        bool _isCorrect;

        std::vector<Types::i2> _srpr;
        Types::u1 _cs;
    };
}

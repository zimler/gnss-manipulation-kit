#pragma once

#include <QtCore/QByteArray>
#include "Greis/StdMessage.h"
#include "Greis/EMessageId.h"

namespace Greis
{
    class DPStdMessage : public StdMessage
    {
    public:
        SMART_PTR_T(DPStdMessage);

        DPStdMessage(const char* p_message, int p_length);
        DPStdMessage(const std::string& p_id, int p_size);

        virtual std::string ToString() const;
        virtual std::string Id() const { return _id; }
        virtual EMessageId::Type IdNumber() const { return EMessageId::DP; }
        virtual bool Validate() const;
        virtual bool IsCorrect() const { return _isCorrect; }
        virtual void RecalculateChecksum();
        virtual int BodySize() const { return _bodySize; }
        virtual QByteArray ToByteArray() const;
        
        // DP [Hz*10-4]
        const std::vector<Types::i4>& Dp() const { return _dp; }
        std::vector<Types::i4>& Dp() { return _dp; }

        // Checksum
        const Types::u1& Cs() const { return _cs; }
        Types::u1& Cs() { return _cs; }
    private:
        std::string _id;
        int _bodySize;
        bool _isCorrect;

        std::vector<Types::i4> _dp;
        Types::u1 _cs;
    };
}

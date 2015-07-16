#pragma once

#include <QtCore/QByteArray>
#include "Greis/StdMessage.h"
#include "Greis/EMessageId.h"

#include "Greis/CustomType/SmoothCustomType.h"

namespace Greis
{
    class SCStdMessage : public StdMessage
    {
    public:
        SMART_PTR_T(SCStdMessage);

        SCStdMessage(const char* p_message, int p_length);
        SCStdMessage(const std::string& p_id, int p_size);
        
        struct Codes
        {
            static const std::string Code_CC;
            static const std::string Code_C1;
            static const std::string Code_C2;
            static const std::string Code_C3;
            static const std::string Code_C5;
            static const std::string Code_Cl;
        };
        
        virtual std::string ToString() const;
        virtual std::string Id() const { return _id; }
        virtual EMessageId::Type IdNumber() const { return EMessageId::SC; }
        virtual bool Validate() const;
        virtual bool IsCorrect() const { return _isCorrect; }
        virtual void RecalculateChecksum();
        virtual int BodySize() const { return _bodySize; }
        virtual QByteArray ToByteArray() const;
        
        // PR smoothing
        const std::vector<SmoothCustomType::UniquePtr_t>& Smooth() const { return _smooth; }
        std::vector<SmoothCustomType::UniquePtr_t>& Smooth() { return _smooth; }

        // Checksum
        const Types::u1& Cs() const { return _cs; }
        Types::u1& Cs() { return _cs; }
    private:
        std::string _id;
        int _bodySize;
        bool _isCorrect;

        std::vector<SmoothCustomType::UniquePtr_t> _smooth;
        Types::u1 _cs;
    };
}

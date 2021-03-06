#pragma once

#include <QtCore/QByteArray>
#include "Greis/StdMessage.h"
#include "Greis/EMessageId.h"

namespace Greis
{
    class ParamsStdMessage : public StdMessage
    {
    public:
        SMART_PTR_T(ParamsStdMessage);

        ParamsStdMessage(const char* p_message, int p_length);
        ParamsStdMessage(const std::string& p_id, int p_size);

        virtual std::string ToString() const;
        virtual std::string Id() const { return _id; }
        virtual EMessageId::Type IdNumber() const { return EMessageId::Params; }
        virtual bool Validate() const;
        virtual bool IsCorrect() const { return _isCorrect; }
        virtual void RecalculateChecksum();
        virtual int BodySize() const { return _bodySize; }
        virtual QByteArray ToByteArray() const;
        
        // Parameters description
        const std::string& Params() const { return _params; }
        std::string& Params() { return _params; }

        // Checksum delimiter
        const std::string& Delim() const { return _delim; }
        std::string& Delim() { return _delim; }

        // Checksum formatted as hexadecimal
        const std::string& Cs() const { return _cs; }
        std::string& Cs() { return _cs; }
    private:
        std::string _id;
        int _bodySize;
        bool _isCorrect;

        std::string _params;
        std::string _delim;
        std::string _cs;
    };
}

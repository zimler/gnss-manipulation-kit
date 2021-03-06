#pragma once

#include <QtCore/QByteArray>
#include "Greis/StdMessage.h"
#include "Greis/EMessageId.h"

namespace Greis
{
    class MsgFmtStdMessage : public StdMessage
    {
    public:
        SMART_PTR_T(MsgFmtStdMessage);

        MsgFmtStdMessage(const char* p_message, int p_length);
        MsgFmtStdMessage(const std::string& p_id, int p_size);

        virtual std::string ToString() const;
        virtual std::string Id() const { return _id; }
        virtual EMessageId::Type IdNumber() const { return EMessageId::MsgFmt; }
        virtual bool Validate() const;
        virtual bool IsCorrect() const { return _isCorrect; }
        virtual void RecalculateChecksum();
        virtual int BodySize() const { return _bodySize; }
        virtual QByteArray ToByteArray() const;
        
        // JP identifier
        const std::string& IdField() const { return _idField; }
        std::string& IdField() { return _idField; }

        // Format major version as decimal (e.g., '01')
        const std::string& MajorVer() const { return _majorVer; }
        std::string& MajorVer() { return _majorVer; }

        // Format minor version as decimal
        const std::string& MinorVer() const { return _minorVer; }
        std::string& MinorVer() { return _minorVer; }

        // Bytes order
        // '0' � LSB first;
        // '1' � MSB first
        const Types::a1& Order() const { return _order; }
        Types::a1& Order() { return _order; }

        // Checksum formatted as hexadecimal
        const std::string& Cs() const { return _cs; }
        std::string& Cs() { return _cs; }
    private:
        std::string _id;
        int _bodySize;
        bool _isCorrect;

        std::string _idField;
        std::string _majorVer;
        std::string _minorVer;
        Types::a1 _order;
        std::string _cs;
    };
}

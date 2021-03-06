#pragma once

#include <QtCore/QByteArray>
#include "Greis/StdMessage.h"
#include "Greis/EMessageId.h"

namespace Greis
{
    class FileIdStdMessage : public StdMessage
    {
    public:
        SMART_PTR_T(FileIdStdMessage);

        FileIdStdMessage(const char* p_message, int p_length);
        FileIdStdMessage(const std::string& p_id, int p_size);

        virtual std::string ToString() const;
        virtual std::string Id() const { return _id; }
        virtual EMessageId::Type IdNumber() const { return EMessageId::FileId; }
        virtual bool Validate() const;
        virtual bool IsCorrect() const { return _isCorrect; }
        virtual void RecalculateChecksum();
        virtual int BodySize() const { return _bodySize; }
        virtual QByteArray ToByteArray() const;
        
        // File type identifier
        const std::string& IdField() const { return _idField; }
        std::string& IdField() { return _idField; }

        // Human-readable stream description
        const std::string& Description() const { return _description; }
        std::string& Description() { return _description; }
    private:
        std::string _id;
        int _bodySize;
        bool _isCorrect;

        std::string _idField;
        std::string _description;
    };
}

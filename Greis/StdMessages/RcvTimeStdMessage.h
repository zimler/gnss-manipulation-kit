#ifndef RcvTimeStdMessage_h__
#define RcvTimeStdMessage_h__

#include <QtCore/QByteArray>
#include "StdMessage.h"
#include "EMessageId.h"

namespace Greis
{
    class RcvTimeStdMessage : public StdMessage
    {
    public:
        SMART_PTR_T(RcvTimeStdMessage);

        RcvTimeStdMessage(const char* p_message, int p_length);
        RcvTimeStdMessage(const std::string& p_id, int p_bodySize);

        virtual std::string ToString() const;
        virtual std::string Id() const { return _id; }
        virtual EMessageId::Type IdNumber() const { return EMessageId::RcvTime; }
        virtual bool Validate() const;
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

        Types::u4 _tod;
        Types::u1 _cs;
    };
}

#endif // RcvTimeStdMessage_h__

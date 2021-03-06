#ifndef CNRStdMessage_h__
#define CNRStdMessage_h__

#include <QtCore/QByteArray>
#include "StdMessage.h"
#include "EMessageId.h"

namespace Greis
{
    class CNRStdMessage : public StdMessage
    {
    public:
        SMART_PTR_T(CNRStdMessage);

        CNRStdMessage(const char* p_message, int p_length);
        CNRStdMessage(const std::string& p_id, int p_size);

        virtual std::string ToString() const;
        virtual std::string Id() const { return _id; }
        virtual EMessageId::Type IdNumber() const { return EMessageId::CNR; }
        virtual bool Validate() const;
        virtual bool IsCorrect() const { return _isCorrect; }
        virtual void RecalculateChecksum();
        virtual int BodySize() const { return _bodySize; }
        virtual QByteArray ToByteArray() const;
        
        // C/N0 [dB*Hz]
        const std::vector<Types::u1>& Cnr() const { return _cnr; }
        std::vector<Types::u1>& Cnr() { return _cnr; }

        // Checksum
        const Types::u1& Cs() const { return _cs; }
        Types::u1& Cs() { return _cs; }
    private:
        std::string _id;
        int _bodySize;
        bool _isCorrect;

        std::vector<Types::u1> _cnr;
        Types::u1 _cs;
    };
}

#endif // CNRStdMessage_h__

#ifndef UtcOffsCustomType_h__
#define UtcOffsCustomType_h__

#include <QtCore/QByteArray>
#include "CustomType.h"
#include "ECustomTypeId.h"

namespace Greis
{
    class UtcOffsCustomType : public CustomType
    {
    public:
        SMART_PTR_T(UtcOffsCustomType);

        UtcOffsCustomType(const char* p_message, int p_length);
        UtcOffsCustomType(int p_size);
        
        virtual ECustomTypeId::Type IdNumber() const { return ECustomTypeId::UtcOffs; }
        virtual QByteArray ToByteArray() const;
        virtual int Size() const { return _size; }
        virtual bool IsCorrect() const { return _isCorrect; }

        // Constant term of polynomial [s]
        const Types::f8& A0() const { return _a0; }
        Types::f8& A0() { return _a0; }

        // First order term of polynomial [s/s]
        const Types::f4& A1() const { return _a1; }
        Types::f4& A1() { return _a1; }

        // Reference time of week [s]
        const Types::u4& Tot() const { return _tot; }
        Types::u4& Tot() { return _tot; }

        // Reference week number []
        const Types::u2& Wnt() const { return _wnt; }
        Types::u2& Wnt() { return _wnt; }

        // Delta time due to leap seconds [s]
        const Types::i1& Dtls() const { return _dtls; }
        Types::i1& Dtls() { return _dtls; }

        // 'Future' reference day number [1�7] []
        const Types::u1& Dn() const { return _dn; }
        Types::u1& Dn() { return _dn; }

        // 'Future' reference week number []
        const Types::u2& Wnlsf() const { return _wnlsf; }
        Types::u2& Wnlsf() { return _wnlsf; }

        // 'Future' delta time due to leap seconds [s]
        const Types::i1& Dtlsf() const { return _dtlsf; }
        Types::i1& Dtlsf() { return _dtlsf; }
    private:
        int _size;
        bool _isCorrect;

        Types::f8 _a0;
        Types::f4 _a1;
        Types::u4 _tot;
        Types::u2 _wnt;
        Types::i1 _dtls;
        Types::u1 _dn;
        Types::u2 _wnlsf;
        Types::i1 _dtlsf;
    };
}

#endif // UtcOffsCustomType_h__

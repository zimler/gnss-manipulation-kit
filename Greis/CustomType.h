#ifndef CustomType_h__
#define CustomType_h__

#include <vector>
#include <QtCore/QByteArray>
#include <boost/noncopyable.hpp>
#include "GreisTypes.h"
#include "ProjectBase/SmartPtr.h"
#include "GreisBinarySerializer.h"
#include "ProjectBase/NotImplementedException.h"
#include "ECustomTypeId.h"

namespace Greis
{
    class CustomType : private boost::noncopyable
    {
    public:
        SMART_PTR_T(CustomType);

        virtual ECustomTypeId::Type IdNumber() const = 0;
        virtual QByteArray ToByteArray() const = 0;
        virtual int Size() const = 0;
    protected:
        static GreisBinarySerializer _serializer;
    };
}

#endif // CustomType_h__

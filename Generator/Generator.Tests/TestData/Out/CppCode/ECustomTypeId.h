#ifndef ECustomTypeId_h__
#define ECustomTypeId_h__

namespace Greis
{
    struct ECustomTypeId
    {
        enum Type
        {
            Unknown,
            ClkOffs,
            ExtSpecData,
            GPSAlm1,
            GPSEphemeris1,
            GpsEphReqData,
            GpsNavData1,
            GpsRawNavData1,
            Header,
            IonoParams1,
            SlotRec,
            Smooth,
            SpecData,
            SvData0,
            SvData1,
            SvData2,
            UtcOffs
        };
    };
}

#endif // ECustomType_h__

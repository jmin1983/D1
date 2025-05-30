//
// D1Consts.h
//
// Library: D1Base
// Package: D1Base
// Module:  D1Base
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1BASE_CONSTS_H
#define _D1BASE_CONSTS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace BnD {
    namespace D1Consts {
        enum ID {
            ID_INVALID = -1,
            ID_USER_DEFINED = 0,
        };
        enum SERVICE_ID {
            SERVICE_ID_INVALID = ID_INVALID,

            // DISTRIBUTED SERVICES BEGIN   ///////////////////////////////////////////////////////
            SERVICE_ID_DISTRIBUTED_BEGIN = 0,

            SERVICE_ID_DCS_BEGIN = SERVICE_ID_DISTRIBUTED_BEGIN,
            SERVICE_ID_DCS_ALL = SERVICE_ID_DCS_BEGIN,
            SERVICE_ID_DCS_END = SERVICE_ID_DCS_BEGIN + 100 * 1000,

            SERVICE_ID_DUS_BEGIN = SERVICE_ID_DCS_END,
            SERVICE_ID_DUS_ALL = SERVICE_ID_DUS_BEGIN,
            SERVICE_ID_DUS_END = SERVICE_ID_DUS_BEGIN + 100 * 1000,

            SERVICE_ID_DSS_BEGIN = SERVICE_ID_DUS_END,
            SERVICE_ID_DSS_ALL = SERVICE_ID_DSS_BEGIN,
            SERVICE_ID_DSS_END = SERVICE_ID_DSS_BEGIN + 100 * 1000,

            SERVICE_ID_DISTRIBUTED_END = SERVICE_ID_DCS_BEGIN + 1000 * 1000,
            // DISTRIBUTED SERVICES END ///////////////////////////////////////////////////////////

            // LOCAL SERVICES BEGIN ///////////////////////////////////////////////////////////////
            SERVICE_ID_LOCAL_BEGIN = SERVICE_ID_DISTRIBUTED_END,

            SERVICE_ID_RS = SERVICE_ID_LOCAL_BEGIN + 1,

            SERVICE_ID_LOCAL_END = SERVICE_ID_LOCAL_BEGIN + 1000,
            // LOCAL SERVICES END   ///////////////////////////////////////////////////////////////

            // STAND_ALONE SERVICES BEGIN   ///////////////////////////////////////////////////////
            SERVICE_ID_STAND_ALONE_BEGIN = SERVICE_ID_LOCAL_END,

            SERVICE_ID_CENTRAL_RESERVED_BEGIN = SERVICE_ID_STAND_ALONE_BEGIN,
            SERVICE_ID_CCS,
            SERVICE_ID_CUS,
            SERVICE_ID_CSS,
            SERVICE_ID_CENTRAL_RESERVED_END = SERVICE_ID_CENTRAL_RESERVED_BEGIN + 10,

            SERVICE_ID_MS,  //  Monitoring Service.
            SERVICE_ID_ECS, //  External Communication Service.
            SERVICE_ID_DWS, //  Database Writing Service.
            SERVICE_ID_WAS, //  Web Assistant Service.
            SERVICE_ID_SMS, //  System Management Service.

            SERVICE_ID_STAND_ALONE_END = SERVICE_ID_STAND_ALONE_BEGIN + 1000,
            // STAND_ALONE SERVICES END ///////////////////////////////////////////////////////////

            // LOAD_BALANCE SERVICES BEGIN  ///////////////////////////////////////////////////////
            SERVICE_ID_LOAD_BALANCE_BEGIN = SERVICE_ID_STAND_ALONE_END,

            SERVICE_ID_LMS_BEGIN = SERVICE_ID_LOAD_BALANCE_BEGIN,
            SERVICE_ID_LMS_ALL = SERVICE_ID_LMS_BEGIN,
            SERVICE_ID_LMS_END = SERVICE_ID_LMS_BEGIN + 100,

            SERVICE_ID_LOAD_BALANCE_END = SERVICE_ID_LOAD_BALANCE_BEGIN + 1000,
            // LOAD_BALANCE SERVICES END    ///////////////////////////////////////////////////////

            // DEPENDENT SERVICES BEGIN ///////////////////////////////////////////////////////////
            SERVICE_ID_DEPENDENT_BEGIN = SERVICE_ID_LOAD_BALANCE_END,

            SERVICE_ID_FMS_BEGIN = SERVICE_ID_DEPENDENT_BEGIN,
            SERVICE_ID_FMS_ALL = SERVICE_ID_FMS_BEGIN,
            SERVICE_ID_FMS_END = SERVICE_ID_FMS_BEGIN + 100,

            SERVICE_ID_DEPENDENT_END = SERVICE_ID_DEPENDENT_BEGIN + 1000,
            // DEPENDENT SERVICES END   ///////////////////////////////////////////////////////////
        };
        enum RESERVED_UNIQUE_ID {
            RESERVED_UNIQUE_ID_INVALID = ID_INVALID,

            RESERVED_UNIQUE_ID_MS_BEGIN = 0,
            RESERVED_UNIQUE_ID_MS_END = RESERVED_UNIQUE_ID_MS_BEGIN + 1000 * 1000,
        };
        inline int32 toDCSIDFromDUSID(int32 dusID)
        {
            if (SERVICE_ID_DUS_BEGIN < dusID && dusID < SERVICE_ID_DUS_END) {
                return dusID - SERVICE_ID_DUS_BEGIN;
            }
            return SERVICE_ID_INVALID;
        }
        inline int32 toDUSIDFromDCSID(int32 dcsID)
        {
            if (SERVICE_ID_DCS_BEGIN < dcsID && dcsID < SERVICE_ID_DCS_END) {
                return dcsID + SERVICE_ID_DUS_BEGIN;
            }
            return SERVICE_ID_INVALID;
        }
    };
}   //  !BnD

#endif  // !_D1BASE_CONSTS_H

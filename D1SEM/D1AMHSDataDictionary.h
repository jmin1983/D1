//
// D1AMHSDataDictionary.h
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SEM_AMHS_DATA_DICTIONARY_H
#define _D1SEM_AMHS_DATA_DICTIONARY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1SECS2/B1SECS2Data.h>

#define DEFINE_AMHS_DATA(d, t) class D1AMHSData##d : public B1SECS2Data##t
#define DEFINE_AMHS_DATA_IMPL(d, t, v) DEFINE_AMHS_DATA(d, t)\
    { public: D1AMHSData##d() : B1SECS2Data##t(#d) {}; D1AMHSData##d(v v_) : B1SECS2Data##t(v_, #d) {};\
              virtual D1AMHSData##d* clone() const override { return new D1AMHSData##d(*this); }; };
#define DEFINE_AMHS_DATA_ASCII(d, l) DEFINE_AMHS_DATA(d, ASCII)\
    { public: D1AMHSData##d() : B1SECS2DataASCII(l, #d) {}; D1AMHSData##d(const B1String& v) : B1SECS2DataASCII(v, l, #d) {};\
              virtual D1AMHSData##d* clone() const override { return new D1AMHSData##d(*this); };};
#define DEFINE_AMHS_DATA_UINT8(d) DEFINE_AMHS_DATA_IMPL(d, UINT8, uint8)
#define DEFINE_AMHS_DATA_UINT16(d) DEFINE_AMHS_DATA_IMPL(d, UINT16, uint16)
#define DEFINE_AMHS_DATA_UINT32(d) DEFINE_AMHS_DATA_IMPL(d, UINT32, uint32)

#define DEFINE_AMHS_DATA_BEGIN(d, t) DEFINE_AMHS_DATA(d, t) { public: virtual D1AMHSData##d* clone() const override { return new D1AMHSData##d(*this); };
#define DEFINE_AMHS_DATA_END };
#define DEFINE_AMHS_DATA_BEGIN_ENUM(d, t) DEFINE_AMHS_DATA_BEGIN(d, t) enum VALUE {
#define DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(d)\
    DEFINE_AMHS_DATA_BEGIN(d, BIN) D1AMHSData##d() : B1SECS2DataBIN(#d) {}; D1AMHSData##d(uint8 v_) : B1SECS2DataBIN(v_, #d) {}; enum VALUE {
#define DEFINE_AMHS_DATA_END_ENUM DEFINE_AMHS_DATA_END };

//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  NOTICE: IF THE DATA TYPES USED BY THE NEW SITE ARE NOT THE TYPES BELOW, REMOVE IT COMPLETELY AND ADD EACH SEPARATELY TO THE DICTIONARY!
//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

namespace BnD {
    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(ACKC5)
        VALUE_ACCEPTED = 0,
        VALUE_ACCEPTED_ERROR = 1,       //  >0:Not accepted, error
    DEFINE_AMHS_DATA_END_ENUM;

    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(ACKC6)
        VALUE_ACCEPTED = 0,
        VALUE_NOT_ACCEPTED_ERROR = 1,   //  >0:Not accepted, error
    DEFINE_AMHS_DATA_END_ENUM;

    DEFINE_AMHS_DATA_BEGIN(ALCD, BIN)  //  (Bit8:1 set alarm, Bit8 : 0 clear alarm)
        D1AMHSDataALCD(bool set = true) : B1SECS2DataBIN("ALCD") { setAlarm(set); }
        void setAlarm(bool set) { _data.resize(1); _data[0] = set ? 1 << 7 : 0; }
        bool isSet() const { return _data.empty() != true ? (_data[0] >> 7) == 1 : false; }
    DEFINE_AMHS_DATA_END;

    DEFINE_AMHS_DATA_BEGIN(ALED, BIN)  //  (Bit8:1 enable alarm, Bit8:0 disable alarm)
        D1AMHSDataALED(bool enable = true) : B1SECS2DataBIN("ALED") { enableAlarm(enable); }
        void enableAlarm(bool enable) { _data.resize(1); _data[0] = enable ? 1 << 7 : 0; }
        bool isEnable() const { return _data.empty() != true ? (_data[0] >> 7) == 1 : false; }
    DEFINE_AMHS_DATA_END;

    //  ALID
    //  ALTX

    DEFINE_AMHS_DATA_IMPL(CEED, BOOL, bool)    //  (FALSE:Disable, TRUE:Enable)

    //  CEID

    DEFINE_AMHS_DATA_ASCII(CENAME, -1);

    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(CEPACK)
        VALUE_NO_ERROR = 0,
        VALUE_PARAMETER_NAME_DOES_NOT_EXIST = 1,        //  PARAMETER_NAME(CEPNAME)
        VALUE_ILLEGAL_VALUE_SPECIFIED_FOR_CEPVAL = 2,
        VALUE_ILLEGAL_FORMAT_SPECIFIED_FOR_CEPVAL = 3,
        VALUE_PARAMETER_NAME_NOT_VALID_AS_USED = 4,     //  PARAMETER_NAME(CPNAME)
    DEFINE_AMHS_DATA_END_ENUM;

    //  CEPVAL

    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(COMMACK)
        VALUE_ACCEPTED = 0,
        VALUE_DENIED_TRY_AGAIN = 1,
    DEFINE_AMHS_DATA_END_ENUM;

    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(CPACK)
        VALUE_NO_ERROR = 0,
        VALUE_PARAMETER_NAME_DOES_NOT_EXIST = 1,        //  PARAMETER_NAME(CPNAME)
        VALUE_ILLEGAL_VALUE_SPECIFIED_FOR_CPVAL = 2,
        VALUE_ILLEGAL_FORMAT_SPECIFIED_FOR_CPVAL = 3,
    DEFINE_AMHS_DATA_END_ENUM;

    DEFINE_AMHS_DATA_ASCII(CPNAME, -1);

    //  CPVAL

    DEFINE_AMHS_DATA_UINT32(DATAID);

    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(DRACK)
        VALUE_ACCEPTED = 0,
        VALUE_INSUFFCIENT_SPACE = 1,
        VALUE_INVALID_FORMAT = 2,
        VALUE_AT_LEAST_ONE_RPTID_ALREADY_DEFINED = 3,
        VALUE_AT_LEAST_VID_DOES_NOT_EXIST = 4,
    DEFINE_AMHS_DATA_END_ENUM;

    DEFINE_AMHS_DATA_ASCII(DVVALNAME, -1);

    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(EAC)
        VALUE_ACKNOWLEDGE = 0,
        VALUE_DENIED_AT_LEAST_ONE_CONSTANT_DOES_NOT_EXIST = 1,
        VALUE_DENIED_BUSY = 2,
        VALUE_DENIED_AT_LEAST_ONE_CONSTANT_OUT_OF_RANGE = 3,
    DEFINE_AMHS_DATA_END_ENUM;

    //  ECDEF
    //  ECID
    //  ECMAX
    //  ECMIN
    //  ECNAME
    //  ECV

    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(ERACK)
        VALUE_ACCEPTED = 0,
        VALUE_AT_LEAST_ONE_CEID_DOES_NOT_EXIST = 1,
    DEFINE_AMHS_DATA_END_ENUM;

    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(HCACK)
        VALUE_ACKNOWLEDGED_COMMAND_HAS_BEEN_PERFORMED = 0,
        VALUE_COMMAND_DOES_NOT_EXIST = 1,
        VALUE_CAN_NOT_PERFORM_NOW = 2,
        VALUE_AT_LEAST_ONE_PARAMETER_IS_INVALID = 3,
        VALUE_ACKNOWLEDGED_COMMAND_WILL_BE_PERFORMED_WITH_COMPLETION_SIGNALED_LATER_BY_AN_EVENT = 4,
        VALUE_REJECTED_ALREADY_IN_DESIRED_CONDITION = 5,
        VALUE_NO_SUCH_OBJECT_EXISTS = 6,
    DEFINE_AMHS_DATA_END_ENUM;

    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(LRACK)
        VALUE_ACCEPTED = 0,
        VALUE_INSUFFICIENT_SPACE = 1,
        VALUE_INVALID_FORMAT = 2,
        VALUE_AT_LEAST_ONE_CEID_LINK_IS_ALREADY_DEFINED = 3,
        VALUE_AT_LEAST_ONE_CEID_DOES_NOT_EXIST = 4,
        VALUE_AT_LEAST_ONE_RPTID_DOES_NOT_EXIST = 5,
    DEFINE_AMHS_DATA_END_ENUM;

    //  MDLN

    DEFINE_AMHS_DATA_ASCII(OBJSPEC, 0);

    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(OFLACK)
        VALUE_OFF_LINE_ACKNOWLEDGE = 0,
    DEFINE_AMHS_DATA_END_ENUM;

    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(ONLACK)
        VALUE_ON_LINE_ACCEPTED = 0,
        VALUE_ON_LINE_NOT_ALLOWED = 1,
        VALUE_EQ_ALREADY_ON_LINE = 2,
    DEFINE_AMHS_DATA_END_ENUM;

    DEFINE_AMHS_DATA_ASCII(RCMD, -1);

    //  RPTID
    //  SOFTREV
    //  SV
    //  SVID
    //  SVNAME

    DEFINE_AMHS_DATA_BEGIN_ENUM_BIN_SINGLE(TIACK)
        VALUE_OK = 0,
        VALUE_ERROR_NOT_DONE = 1,
    DEFINE_AMHS_DATA_END_ENUM;

    DEFINE_AMHS_DATA_ASCII(TIME, 16);  //  YYYYMMDDHHmmsscc
    DEFINE_AMHS_DATA_ASCII(UNITS, -1);

    //  V
    //  VID

}   //  !BnD

#endif  // !_D1SEM_AMHS_DATA_DICTIONARY_H

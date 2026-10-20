//
// D1MsgChatNtf.cpp
//
// Library: D1Message
// Package: AlarmEvent
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MsgChatNtf.h"

#include <B1Base/B1Time.h>

#include <D1Base/D1Consts.h>

using namespace BnD;

D1MsgChatNtf::D1MsgChatNtf(B1String&& userFrom, B1String&& addressFrom, B1String&& messageBody)
    : D1BaseMessage()
    , _userTo("UserTo", "")
    , _userFrom("UserFrom", userFrom)
    , _addressFrom("AddressFrom", addressFrom)
    , _encodedMessageBody("EncodedMessageBody", messageBody)
{
    _messageID.second = messageString().copy();
}

D1MsgChatNtf::D1MsgChatNtf(B1String&& userTo, B1String&& userFrom, B1String&& addressFrom, B1String&& messageBody)
    : D1BaseMessage()
    , _userTo("UserTo", userTo)
    , _userFrom("UserFrom", userFrom)
    , _addressFrom("AddressFrom", addressFrom)
    , _encodedMessageBody("EncodedMessageBody", messageBody)
{
    _messageID.second = messageString().copy();
}

D1MsgChatNtf::D1MsgChatNtf(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _userTo("UserTo", "")
    , _userFrom("UserFrom", "")
    , _addressFrom("AddressFrom", "")
    , _encodedMessageBody("EncodedMessageBody", "")
{
}

D1MsgChatNtf::~D1MsgChatNtf()
{
}

void D1MsgChatNtf::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_userTo, archive);
    writeDataToArchive(_userFrom, archive);
    writeDataToArchive(_addressFrom, archive);
    writeDataToArchive(_encodedMessageBody, archive);
}

void D1MsgChatNtf::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_userTo);
    readDataFromArchive(archive, &_userFrom);
    readDataFromArchive(archive, &_addressFrom);
    readDataFromArchive(archive, &_encodedMessageBody);
}

B1String D1MsgChatNtf::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", userTo[%s]", userTo().cString());
    str.appendf(", userFrom[%s]", userFrom().cString());
    str.appendf(", addressFrom[%s]", addressFrom().cString());
    str.appendf(", encodedMessageBody[%s]", encodedMessageBody().cString());
    return str;
}

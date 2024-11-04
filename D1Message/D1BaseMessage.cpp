//
// D1BaseMessage.cpp
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1BaseMessage.h"

#include <B1Base/B1Archive.h>
#include <B1Base/B1Time.h>

using namespace BnD;

const B1String D1BaseMessage::_messageDataKey("MessageData");

D1BaseMessage::D1BaseMessage()
    : B1Object()
    , _messageID("MessageID", "")
    , _baseTime("BaseTime", 0)
{
}

D1BaseMessage::D1BaseMessage(D1BaseMessage&& base) noexcept
    : B1Object()
    , _messageID(base._messageID.first.copy(), std::move(base._messageID.second))
    , _baseTime(base._baseTime.first.copy(), std::move(base._baseTime.second))
{
}

D1BaseMessage::~D1BaseMessage()
{
}

void D1BaseMessage::archiveTo(B1Archive* archive) const
{
    writeDataToArchive(_messageID, archive);
    B1Archive messageData;
    archiveMessage(&messageData);
    writeDataToArchive(_baseTime, &messageData);
    archive->addSubArchive(_messageDataKey, messageData);
}

void D1BaseMessage::unarchiveFrom(const B1Archive& archive)
{
    if (_messageID.second.isEmpty()) {
        readDataFromArchive(archive, &_messageID);
    }
    B1Archive messageData;
    archive.getSubArchive(_messageDataKey, &messageData);
    unarchiveMessage(messageData);
    readDataFromArchive(messageData, &_baseTime);        
}

B1String D1BaseMessage::toString() const
{
    if (baseTime() > 0) {
        B1String str = _messageID.second.copy();
        str.appendf(", baseTime[%s]", B1Time(baseTime()).toString().cString());
        return str;
    }
    else {
        return _messageID.second.copy();
    }
}

bool D1BaseMessage::composeToJson(B1String* json) const
{
    return archiveToString(json);
}

bool D1BaseMessage::composeToJsonWithBaseTime(B1String* json)
{
    B1Time::getCurrentTime(&_baseTime.second);
    return composeToJson(json);
}

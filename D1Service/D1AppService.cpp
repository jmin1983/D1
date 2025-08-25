//
// D1AppService.cpp
//
// Library: D1Service
// Package: D1Service
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Service.h"
#include "D1AppService.h"
#include "D1SMSClient.h"
#include "D1SMSClientSessionListener.h"

#include <B1Base/B1Thread.h>

using namespace BnD;

D1AppService::D1AppService(std::shared_ptr<D1ProductIdentifier> productIdentifier, int32 version, B1String&& buildDate, B1String&& systemName)
    : D1BaseService(productIdentifier, version, std::move(buildDate), std::move(systemName))
{
}

D1AppService::~D1AppService()
{
}

B1String D1AppService::getNetworkAddressesString() const
{
    B1String smsAddress;
    int32 smsPort;
    getSMSServerInfo(&smsAddress, &smsPort);
    if (smsAddress.isEmpty() || smsPort < 1) {
        return D1BaseService::getNetworkAddressesString();
    }

    struct TempListener : D1SMSClientSessionListener {
        TempListener() : _ready(false) {}
        bool _ready;
        B1Condition _waiter;
        std::vector<B1String> _addresses;
        void onClientSessionConnected() final
        {
            _ready = true;
        }
        void onSMSClientDisconnnected(int32 reason) final
        {
            _waiter.signal();
        }
        void onRecvSMSClientDataHostAddressesRsp(std::vector<B1String>&& addresses) final
        {
            _addresses.swap(addresses);
            _waiter.signal();
        }
        void wait() { _waiter.wait(); }
    } tl;

    B1String addressesString;
    D1SMSClient smsClient(serviceID());
    if (smsClient.initialize(smsAddress, smsPort, &tl)) {
        while (true) {
            if (tl._ready || smsClient.isDisconnected()) {
                break;
            }
            B1Thread::sleep(100);
        }
        if (tl._ready) {
            if (smsClient.sendHostAddressesReq()) {
                tl.wait();
                std::set<B1String> addresses(tl._addresses.begin(), tl._addresses.end());
                for (const auto& address : addresses) {
                    if (addressesString.isEmpty() != true) {
                        addressesString.append(" / ");
                    }
                    addressesString += address;
                }
            }
        }
    }
    smsClient.finalize();
    return addressesString.isEmpty() ? D1BaseService::getNetworkAddressesString() : addressesString;
}

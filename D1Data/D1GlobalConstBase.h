//
// D1GlobalConstBase.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_GLOBAL_CONST_BASE_H
#define _D1DATA_GLOBAL_CONST_BASE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1Object.h>

#include <map>

namespace BnD {
    class D1RedisClientInterface;
    class D1GlobalConstBase : public B1Object {
    public:
        D1GlobalConstBase(B1String&& processName, int32 id = -1) : _processName(processName), _id(id) {} //  not use id if id is less than zero.
    protected:
        class ItemBunch {
        public:
            ItemBunch(B1String&& itemBunchName) : _itemBunchName(itemBunchName) {}
            virtual ~ItemBunch() {}
        protected:
            const B1String _itemBunchName;
        protected:
            virtual bool implMakeRedisStringArgs(std::vector<B1String>* args) const { return false; }
            virtual void implLoadDynamicData(D1GlobalConstBase* owner, const std::map<B1String, B1String>& values, bool adjustValue) {} //  Reload during operation.
            virtual void implLoadStaticData(D1GlobalConstBase* owner, const std::map<B1String, B1String>& values, bool adjustValue) {}  //  Loaded once at first startup.
            virtual B1String implToString() const = 0;
        protected:
            B1String itemField(const B1String& field) const;
            B1String itemFieldAndValue(const DataInt32& itemData) const;
            B1String itemFieldAndValue(const DataFloat64& itemData) const;
            B1String itemFieldAndValue(const DataString& itemData) const;
            template <typename T>
            bool getData(D1GlobalConstBase* owner, const std::map<B1String, B1String>& values, T* data)
            {
                return owner->getData(values, itemField(data->first), &data->second);
            }
            bool getStringData(D1GlobalConstBase* owner, const std::map<B1String, B1String>& values, DataString* data)
            {
                return owner->getStringData(values, itemField(data->first), &data->second);
            }
        public:
            bool operator< (const ItemBunch& d) const { return _itemBunchName < d._itemBunchName; }
        public:
            bool makeRedisStringArgs(std::vector<B1String>* args) const { return implMakeRedisStringArgs(args); }
            void loadData(bool isDynamic, D1GlobalConstBase* owner, const std::map<B1String, B1String>& values, bool adjustValue) {
                if (isDynamic) {
                    implLoadDynamicData(owner, values, adjustValue);
                }
                else {
                    implLoadStaticData(owner, values, adjustValue);
                }
            }
            const B1String& itemBunchName() const { return _itemBunchName; }
            B1String toString() const { return implToString(); }
        };
    protected:
        const B1String _processName;
        const int32 _id;
        std::map<B1String, std::shared_ptr<ItemBunch> > _itemBunches;
    protected:
        virtual bool implAddAllItems() = 0;
    protected:
        B1String itemKey() const;
        void loadData(bool isDynamic, D1RedisClientInterface* redisClientInterface, const B1String& key, bool adjustValue = false);
        bool addItemBunch(std::shared_ptr<ItemBunch> itemBunch);
        template <typename T>
        std::shared_ptr<T> getItemBunch(const B1String& bunchName)
        {
            auto itr = _itemBunches.find(bunchName);
            if (itr == _itemBunches.end()) {
                assert(false);
                return std::shared_ptr<T>();
            }
            return std::dynamic_pointer_cast<T>(itr->second);
        }
    public:
        bool addAllItems();
        void loadAllData(D1RedisClientInterface* redisClientInterface);       //  After startup, use only once.
        void reloadDynamicData(D1RedisClientInterface* redisClientInterface); //  Use at any time during operation.
        void saveAllData(D1RedisClientInterface* redisClientInterface);
        B1String toString() const;
        bool getStringData(const std::map<B1String, B1String>& values, const B1String& key, B1String* data);
    public:
        template <typename T>
        bool getData(const std::map<B1String, B1String>& values, const B1String& key, T* data)
        {
            auto itr = values.find(key);
            if (itr == values.end()) {
                return false;
            }
            try {
                *data = static_cast<T>(itr->second.toInt32());
            }
            catch (...) {
                return false;
            }
            return true;
        }
        bool getData(const std::map<B1String, B1String>& values, const B1String& key, float64* data)
        {
            auto itr = values.find(key);
            if (itr == values.end()) {
                return false;
            }
            try {
                *data = static_cast<float64>(itr->second.toFloat64());
            }
            catch (...) {
                return false;
            }
            return true;
        }
    };
}

#endif  // !_D1DATA_GLOBAL_CONST_BASE_H

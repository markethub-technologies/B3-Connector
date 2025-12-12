/*
* Copyright Onix Solutions Limited [OnixS]. All rights reserved.
*
* This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
* and international copyright treaties.
*
* Access to and use of the software is governed by the terms of the applicable OnixS Software
* Services Agreement (the Agreement) and Customer end user license agreements granting
* a non-assignable, non-transferable and non-exclusive license to use the software
* for it's own data processing purposes under the terms defined in the Agreement.
*
* Except as otherwise granted within the terms of the Agreement, copying or reproduction of any part
* of this source code or associated reference material to any other location for further reproduction
* or redistribution, and any amendments to this copyright notice, are expressly prohibited.
*
* Any reproduction or redistribution for sale or hiring of the Software not in accordance with
* the terms of the Agreement is a violation of copyright law.
*/

#pragma once

//! [BookH]
#include <string>
#include <vector>
#include <map>

namespace Samples
{

// Collection of book entries (e.g., orders) currently manipulated by the trading client.
template <typename EntryType>
class Book
{
public:
    typedef std::map<ClOrdID, EntryType> BookEntries;
    typedef typename BookEntries::iterator EntryIter;

    // Adds an entry to the book.
    Book& store(const EntryType& entry);
    Book& store(const EntryType& entry, ClOrdID id);

    // Finds an instance of the entry by its identifier.
    // If there's no entry available, returns NULL.
    EntryType* find(ClOrdID id);

    typedef std::vector<EntryType*> EntryList;

    // Returns a collection of stored book entries.
    void getEntries(EntryList & list);

private:
    typedef Threading::Mutex Mutex;
    typedef Threading::Guard<Threading::Mutex> Guard;

    Mutex mutex_;
    BookEntries entries_;
};

template <typename EntryType>
Book<EntryType>& Book<EntryType>::store(const EntryType& newEntry)
{
    return store(newEntry, newEntry.id());
}

template <typename EntryType>
Book<EntryType>& Book<EntryType>::store(const EntryType& newEntry, ClOrdID id)
{
    const Guard guard(mutex_);

    const std::pair<EntryIter, bool> result = entries_.insert(std::make_pair(id, newEntry));

    if (!result.second)
    {
        std::stringstream ss;
        ss << "Book already has an entry registered under ID = '" << id << "'.";
        throw std::domain_error(ss.str());
    }

    return *this;
}

template <typename EntryType>
EntryType* Book<EntryType>::find(ClOrdID id)
{
    const Guard guard(mutex_);

    const EntryIter entry = entries_.find(id);
    return entry == entries_.end() ? ONIXS_B3_BOE_NULLPTR : &entry->second;
}

template <typename EntryType>
void Book<EntryType>::getEntries(Book<EntryType>::EntryList & list)
{
    const Guard guard(mutex_);

    for (EntryIter iter = entries_.begin(); iter != entries_.end(); ++iter)
        list.push_back(&iter->second);
}

}
//! [BookH]

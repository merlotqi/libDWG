/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

 #include <dwg/DxfFileToken_p.h>
 #include <dwg/DxfSubclassMarker_p.h>
#include <dwg/tables/TableEntry.h>
 #include <dwg/tables/collections/TableCollection.h>
 #include <dwg/CadDocument.h>
 #include <fmt/core.h>
 #include <assert.h>

namespace dwg {

TableCollection::TableCollection(CadDocument *document)
{
    _owner = document;
    document->registerCollection(this);
}
TableCollection::~TableCollection() {}

size_t TableCollection::count() const { return _entries.size(); }

std::string TableCollection::objectName() const{ return DxfFileToken::TableEntry_; }

std::string TableCollection::subclassMarker() const{ return DxfSubclassMarker::Table; }

TableEntry * TableCollection::operator[](const std::string &key) const
{ 
    auto itFind = _entries.find(key);
    if (itFind != _entries.end())
    {
        return itFind->second;
    }
    else
    {
        return nullptr;
    }
}

void TableCollection::add(TableEntry * entry)
{
    assert(entry);
    if(entry->name().empty())
    {
        entry->setName(createName());
    }
    addPrivate(entry->name(), entry);
}

bool TableCollection::contains(const std::string &key) const
{
    auto itFind = _entries.find(key);
    if(itFind == _entries.end())
        return false;
    else
        return true;
}

TableEntry * TableCollection::getValue(const std::string &key) const 
{
    auto itFind = _entries.find(key);
    if (itFind != _entries.end())
    {
        return itFind->second;
    }
    else
    {
        return nullptr;
    }
}

void TableCollection::createDefaultEntries() 
{
    auto&& names = defaultEntries();
    for(auto&& name : names)
    {
        if(contains(name))
            continue;

        add(createEntry(name));
    }
}

TableCollection::iterator TableCollection::begin() { return _entries.begin(); }

TableCollection::iterator TableCollection::end() { return _entries.end(); }

TableCollection::const_iterator TableCollection::begin() const { return _entries.begin(); }

TableCollection::const_iterator TableCollection::end() const { return _entries.end(); }

void TableCollection::addPrivate(const std::string &key, TableEntry * item)
{
    _entries.insert({key, item});
    item->setOwner(this);
    item->OnNameChanged.add(this, &TableCollection::onEntryNameChanged);
    OnAdd(item);
}

void TableCollection::addHandlePrefix(TableEntry *item)
{
    assert(item);
    item->setOwner(this);
    item->OnNameChanged.add(this, &TableCollection::onEntryNameChanged);

    OnAdd(item);

    std::string key = fmt::format("{}:{}", item->handle(), item->name());
    _entries.insert({key, item});
}

std::vector<std::string> TableCollection::defaultEntries() const { return std::vector<std::string>(); }

bool TableCollection::assertType(TableEntry * item) const
{
    (void)item;
    return true;
}
std::string TableCollection::createName() const
{
    std::string name = "unamed";
    int i = 0;
    while(contains(fmt::format("{}_{}", name, i)))
    {
        i++;
    }
    return fmt::format("{}_{}", name, i);
}

void TableCollection::onEntryNameChanged(const std::string &oldname, const std::string &newname) {}

}// namespace dwg
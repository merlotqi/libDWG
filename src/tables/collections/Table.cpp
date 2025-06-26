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

#include <dwg/CadDocument.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/tables/collections/Table.h>
#include <fmt/core.h>

namespace dwg {

Table::Table() {}

Table::Table(CadDocument *document)
{
    _owner = document;
    document->registerCollection(this);
}

Table::~Table() {}

std::string Table::objectName() const
{
    return DxfFileToken::TableEntry_;
}

std::string Table::subclassMarker() const
{
    return DxfSubclassMarker::Table;
}

std::vector<CadObject *> Table::rawCadObjects() const
{
    return std::vector<CadObject *>();
}

std::size_t Table::size() const
{
    return _entries.size();
}

Table::pointer Table::operator[](const std::string &key)
{
    auto _it = _entries.find(key);
    return (_it != _entries.end()) ? _it->second : nullptr;
}

void Table::add(pointer v)
{
    assert(v);
    if (v->name().empty())
        v->setName(createName());
    push_back(v->name(), v);
}

bool Table::contains(const std::string &key) const
{
    auto _it = _entries.find(key);
    return (_it != _entries.end()) ? true : false;
}

Table::pointer Table::value(const std::string &key) const
{
    auto _it = _entries.find(key);
    return (_it != _entries.end()) ? _it->second : nullptr;
}

void Table::createDefaultEntries()
{
    auto ns = defaultEntries();
    for (auto &&entry: ns)
    {
        if (contains(entry))
            continue;

        push_back(entry, createEntry(entry));
    }
}

void Table::addHandlePrefix(pointer v)
{
    assert(v);
    v->setOwner(this);
    v->OnNameChanged.add(this, &Table::onEntryNameChanged);

    OnAdd(v);

    std::string k = fmt::format("{}:{}", v->handle(), v->name());
    _entries.insert({k, v});
}

void Table::push_back(const std::string &n, pointer v)
{
    _entries.insert({n, v});
    v->setOwner(this);
    v->OnNameChanged.add(this, &Table::onEntryNameChanged);
    OnAdd(v);
}

std::vector<std::string> Table::defaultEntries() const
{
    return std::vector<std::string>();
}

std::string Table::createName() const
{
    std::string name = "unamed";
    int i = 0;
    while (contains(fmt::format("{}_{}", name, i)))
    {
        i++;
    }
    return fmt::format("{}_{}", name, i);
}

void Table::onEntryNameChanged(const std::string &oldname, const std::string &newname) {}

}// namespace dwg
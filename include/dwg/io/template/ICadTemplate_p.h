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

#pragma once

#include <vector>
#include <string>

namespace dwg {

class CadDocumentBuilder;
class CadObject;

class ICadTemplate
{
public:
    virtual ~ICadTemplate() = default;
    virtual void build(CadDocumentBuilder *builder) = 0;
};

class ICadObjectTemplate : public ICadTemplate
{
public:
    virtual ~ICadObjectTemplate() = default;
    virtual CadObject *rawCadObject() const = 0;
};

class ICadTableTemplate : public ICadObjectTemplate
{
public:
    virtual ~ICadTableTemplate() = default;
    virtual std::vector<unsigned long long> entryHandles() const = 0;
};

class ICadTableEntryTemplate : public ICadObjectTemplate
{
public:
    virtual ~ICadTableEntryTemplate() = default;
    virtual std::string type() const = 0;
    virtual std::string name() const = 0;
};

class ICadDictionaryTemplate : public ICadObjectTemplate
{
public:
    virtual ~ICadDictionaryTemplate() = default;
};

}// namespace dwg
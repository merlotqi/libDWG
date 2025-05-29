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

#include <dwg/io/template/CadTemplate_p.h>

namespace dwg {

CadTemplate::CadTemplate(CadObject *obj) {}

CadObject *CadTemplate::cadObject() const
{
    return nullptr;
}

void CadTemplate::setCadObject(CadObject *v) {}

std::optional<unsigned long long> CadTemplate::ownerHandle() const
{
    return std::nullopt;
}

void CadTemplate::setOwnerHandle(unsigned long long) {}

std::optional<unsigned long long> CadTemplate::xdictHandle() const
{
    return std::nullopt;
}

void CadTemplate::setXDictHandle(unsigned long long) {}


std::vector<unsigned long long> CadTemplate::reactorsHandles() const
{
    return _reactorsHandles;
}

std::vector<unsigned long long> &CadTemplate::reactorsHandles()
{
    return _reactorsHandles;
}

void CadTemplate::setReactorsHandles(const std::vector<unsigned long long> &value)
{
    _reactorsHandles = value;
}

std::map<unsigned long long, std::vector<ExtendedDataRecord *>> CadTemplate::edataTemplate() const
{
    return _edataTemplate;
}

std::map<unsigned long long, std::vector<ExtendedDataRecord *>> &CadTemplate::edataTemplate()
{
    return _edataTemplate;
}

std::map<unsigned long long, std::vector<ExtendedDataRecord *>> CadTemplate::edataTemplateByAppName() const
{
    return _edataTemplateByAppName;
}

std::map<unsigned long long, std::vector<ExtendedDataRecord *>> &CadTemplate::edataTemplateByAppName()
{
    return _edataTemplateByAppName;
}

void CadTemplate::build(CadDocumentBuilder *builder) {}

CadObject *CadTemplate::rawObject() const
{
    return _object;
}

}// namespace dwg
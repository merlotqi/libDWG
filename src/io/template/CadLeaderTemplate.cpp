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

#include <dwg/entities/Leader.h>
#include <dwg/io/template/CadLeaderTemplate_p.h>

namespace dwg {

CadLeaderTemplate::CadLeaderTemplate() : CadEntityTemplate(new Leader()) {}

CadLeaderTemplate::CadLeaderTemplate(Leader *leader) : CadEntityTemplate(leader) {}

void CadLeaderTemplate::build(CadDocumentBuilder *builder) {}

double CadLeaderTemplate::dimasz() const
{
    return _dimasz;
}

void CadLeaderTemplate::setDimasz(double value)
{
    _dimasz = value;
}

unsigned long long CadLeaderTemplate::DIMSTYLEHandle() const
{
    return _DIMSTYLEHandle;
}

void CadLeaderTemplate::setDIMSTYLEHandle(unsigned long long value)
{
    _DIMSTYLEHandle = value;
}

std::string CadLeaderTemplate::DIMSTYLEName() const
{
    return _DIMSTYLEName;
}

void CadLeaderTemplate::setDIMSTYLEName(const std::string &value)
{
    _DIMSTYLEName = value;
}

unsigned long long CadLeaderTemplate::annotationHandle() const
{
    return _annotationHandle;
}

void CadLeaderTemplate::setAnnotationHandle(unsigned long long value)
{
    _annotationHandle = value;
}

}// namespace dwg
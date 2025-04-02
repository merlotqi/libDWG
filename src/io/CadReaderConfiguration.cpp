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

#include <dwg/io/CadReaderConfiguration.h>

namespace dwg {

CadReaderConfiguration::CadReaderConfiguration()
    : _failsafe(true), _keepUnknownEntities(false), _keepUnknownNonGraphicalObjects(false)
{
}

CadReaderConfiguration::~CadReaderConfiguration() {}

bool CadReaderConfiguration::failsafe() const
{
    return _failsafe;
}

void CadReaderConfiguration::setFailsafe(bool value)
{
    _failsafe = value;
}

bool CadReaderConfiguration::keepUnknownEntities() const
{
    return _keepUnknownEntities;
}

void CadReaderConfiguration::setKeepUnknownEntities(bool value)
{
    _keepUnknownEntities = value;
}

bool CadReaderConfiguration::keepUnknownNonGraphicalObjects() const
{
    return _keepUnknownNonGraphicalObjects;
}

void CadReaderConfiguration::setKeepUnknownNonGraphicalObjects(bool value)
{
    _keepUnknownNonGraphicalObjects = value;
}

}// namespace dwg
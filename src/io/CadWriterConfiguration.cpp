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

#include <dwg/io/CadWriterConfiguration.h>

namespace dwg {

CadWriterConfiguration::CadWriterConfiguration() : _closeStream(true), _writeXRecords(false), _writeXData(true)
    , _resetDxfClasses(true), _updateDimensionsInBlocks(false), _updateDimensionsInModel(false) {}

CadWriterConfiguration::~CadWriterConfiguration() {}

bool CadWriterConfiguration::closeStream() const
{
    return _closeStream;
}

void CadWriterConfiguration::setCloseStream(bool value)
{
    _closeStream = value;
}

bool CadWriterConfiguration::resetDxfClasses() const
{
    return _resetDxfClasses;
}

void CadWriterConfiguration::setResetDxfClasses(bool value)
{
    _resetDxfClasses = value;
}

bool CadWriterConfiguration::updateDimensionsInBlocks() const
{
    return _updateDimensionsInBlocks;
}

void CadWriterConfiguration::setUpdateDimensionsInBlocks(bool value)
{
    _updateDimensionsInBlocks = value;
}

bool CadWriterConfiguration::updateDimensionsInModel() const
{
    return _updateDimensionsInModel;
}

void CadWriterConfiguration::setUpdateDimensionsInModel(bool value)
{
    _updateDimensionsInModel = value;
}

bool CadWriterConfiguration::writeXRecords() const
{
    return _writeXRecords;
}

void CadWriterConfiguration::setWriteXRecords(bool value)
{
    _writeXRecords = value;
}

bool CadWriterConfiguration::writeXData() const
{
    return _writeXData;
}

void CadWriterConfiguration::setWriteXData(bool value)
{
    _writeXData = value;
}

}// namespace dwg
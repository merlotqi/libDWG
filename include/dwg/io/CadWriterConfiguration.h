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

#include <dwg/exports.h>

namespace dwg {

class LIBDWG_API CadWriterConfiguration
{
public:
    CadWriterConfiguration();
    virtual ~CadWriterConfiguration();

    bool closeStream() const;
    void setCloseStream(bool value);

    bool resetDxfClasses() const;
    void setResetDxfClasses(bool);

    bool updateDimensionsInBlocks() const;
    void setUpdateDimensionsInBlocks(bool);

    bool updateDimensionsInModel() const;
    void setUpdateDimensionsInModel(bool);

    bool writeXRecords() const;
    void setWriteXRecords(bool value);

    bool writeXData() const;
    void setWriteXData(bool value);

private:
    bool _closeStream;
    bool _writeXRecords;
    bool _writeXData;
    bool _resetDxfClasses;
    bool _updateDimensionsInBlocks;
    bool _updateDimensionsInModel;
};

}// namespace dwg
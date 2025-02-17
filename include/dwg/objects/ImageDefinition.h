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

#include <dwg/Coordinate.h>
#include <dwg/objects/NonGraphicalObject.h>
#include <dwg/objects/ResolutionUnit.h>

namespace dwg {

class LIBDWG_API ImageDefinition : public NonGraphicalObject
{
public:
    ImageDefinition();
    ~ImageDefinition();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    int classVersion() const;
    void setClassVersion(int);

    std::string fileName() const;
    void setFileName(const std::string &);

    XY size() const;
    void setSize(const XY &);

    XY defaultSize() const;
    void setDefaultSize(const XY &);

    bool isLoaded() const;
    void setIsLoaded(bool);

    ResolutionUnit units() const;
    void setUnits(ResolutionUnit);

private:
    int _classVersion;
    XY _size;
    XY _defaultSize;
    bool _isLoaded;
    ResolutionUnit _units;
};

}// namespace dwg
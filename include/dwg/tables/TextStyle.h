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

#include <dwg/entities/TextMirrorFlag.h>
#include <dwg/tables/FontFlags.h>
#include <dwg/tables/StyleFlags.h>
#include <dwg/tables/TableCollection.h>
#include <dwg/tables/TableEntry.h>

namespace dwg {

class LIBDWG_API TextStyle : public TableEntry
{
public:
    TextStyle();
    TextStyle(const std::string &name);
    ~TextStyle();

    static constexpr auto DefaultName = "Standard";
    static TextStyle *Default();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    StyleFlags flags() const;
    void setFlags(StyleFlags);

    std::string filename() const;
    void setFilename(const std::string &);

    std::string bigFontFilename() const;
    void setBigFontFilename(const std::string &);

    double height() const;
    void setHeight(double);

    double width() const;
    void setWidth(double);

    double lastHeight() const;
    void setLastHeight(double);

    double obliqueAngle() const;
    void setObliqueAngle(double);

    TextMirrorFlag mirrorFlag() const;
    void setMirrorFlag(TextMirrorFlag);

    FontFlags trueType() const;
    void setTrueType(FontFlags);

    bool isShapeFile() const;

private:
    StyleFlags _flags = 0;
    std::string _filename;
    std::string _bigFontFilename;
    double _height = 0.0;
    double _width = 1.0;
    double _lastHeight = 0.0;
    double _obliqueAngle = 0.0;
    TextMirrorFlag _mirrorFlag = TextMirrorFlag::None;
    FontFlags _trueType = (int)FontFlag::Regular;
};

class LIBDWG_API TextStylesTable : public Table<TextStyle>
{
public:
    TextStylesTable() = default;
    ObjectType objectType() const override;

protected:
    std::vector<std::string> defaultEntries() const;
};

}// namespace dwg

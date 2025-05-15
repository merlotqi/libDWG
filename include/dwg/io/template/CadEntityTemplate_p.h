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

#include <dwg/entities/Entity.h>
#include <dwg/io/template/CadTemplate_p.h>

namespace dwg {

class CadEntityTemplate : public CadTemplateT<Entity *>
{
public:
    CadEntityTemplate(Entity *v);
    void build(CadDocumentBuilder *builder) override;
    void setUnlinkedReferences();

    unsigned char entityMode() const;
    void setEntityMode(unsigned char);

    std::optional<unsigned char> ltypeFlags() const;
    void setLtypeFlags(unsigned char);

    std::optional<unsigned long long> layerHandle() const;
    void setLayerHandle(unsigned long long);

    std::string layerName() const;
    void setLayerName(const std::string &);

    std::optional<unsigned long long> lineTypeHandle() const;
    void setLineTypeHandle(unsigned long long);

    std::string lineTypeName() const;
    void setLineTypeName(const std::string &);

    std::optional<unsigned long long> prevEntity() const;
    void setPrevEntity(unsigned long long);

    std::optional<unsigned long long> nextEntity() const;
    void setNextEntity(unsigned long long);

    std::optional<unsigned long long> colorHandle() const;
    void setColorHandle(unsigned long long);

    std::string bookColorName() const;
    void setBookColorName(const std::string &);

    std::optional<unsigned long long> materialHandle() const;
    void setMaterialHandle(unsigned long long);

protected:
    unsigned char _entityMode;
    std::optional<unsigned char> _ltypeFlags;
    std::optional<unsigned char> _layerHandle;
    std::string _layerName;
    std::optional<unsigned long long> _lineTypeHandle;
    std::string _lineTypeName;
    std::optional<unsigned long long> _prevEntity;
    std::optional<unsigned long long> _nextEntity;
    std::optional<unsigned long long> _colorHandle;
    std::string _bookColorName;
    std::optional<unsigned long long> _materialHandle;
};

}// namespace dwg
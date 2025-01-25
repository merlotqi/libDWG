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

#include <dwg/entities/ClipMode.h>
#include <dwg/entities/ClipType.h>
#include <dwg/entities/Entity.h>
#include <dwg/entities/ImageDisplayFlags.h>

namespace dwg {

class DG_ImageDefinition;
CPL_SMARTER_PTR(DG_ImageDefinition);

class DG_ImageDefinitionReactor;
CPL_SMARTER_PTR(DG_ImageDefinitionReactor);

class LIBDWG_API DG_CadImageBase : public DG_Entity
{
    int _classVersion;
    XYZ _insertPoint;
    XYZ _uvector;
    XYZ _vvector;
    XY _size;
    DG_ImageDisplayFlags _flags;
    bool _clippingState;
    unsigned char _brightness;
    unsigned char _contrast;
    unsigned char _fade;

    DG_ClipMode _clipMode;
    DG_ClipType _clipType;
    std::vector<XY> _clipBoundaryVertices;
    DG_ImageDefinitionWPtr _definition;
    DG_ImageDefinitionReactorWPtr _definitionReactor;

public:
    DG_CadImageBase();

    virtual ~DG_CadImageBase();

    int ClassVersion() const;
    void ClassVersion(int);

    XYZ InsertPoint() const;
    void InsertPoint(const XYZ &);

    XYZ UVector() const;
    void UVector(const XYZ &);

    XYZ VVector() const;
    void VVector(const XYZ &);

    XY Size() const;
    void Size(const XY &);

    DG_ImageDisplayFlags Flags() const;
    void Flags(DG_ImageDisplayFlags);

    bool ClippingState() const;
    void ClippingState(bool);

    unsigned char Brightness() const;
    void Brightness(unsigned char);

    unsigned char Contrast() const;
    void Contrast(unsigned char);

    unsigned char Fade() const;
    void Fade(unsigned char);

    DG_ClipMode ClipMode() const;
    void ClipMode(DG_ClipMode);

    DG_ClipType ClipType() const;
    void ClipType(DG_ClipType);

    std::vector<XY> ClipBoundaryVertices() const;
    void ClipBoundaryVertices(const std::vector<XY> &);

    DG_ImageDefinitionPtr Definition() const;
    void Definition(DG_ImageDefinition *);

    DG_ImageDefinitionReactorPtr DefinitionReactor() const;
    void DefinitionReactor(DG_ImageDefinitionReactor *);
};
CPL_SMARTER_PTR(DG_CadImageBase)

}// namespace dwg

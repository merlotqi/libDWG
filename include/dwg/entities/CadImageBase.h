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

class ImageDefinition;
CPL_SMARTER_PTR(ImageDefinition);

class ImageDefinitionReactor;
CPL_SMARTER_PTR(ImageDefinitionReactor);

class LIBDWG_API CadImageBase : public Entity
{
    int _classVersion;
    XYZ _insertPoint;
    XYZ _uvector;
    XYZ _vvector;
    XY _size;
    ImageDisplayFlags _flags;
    bool _clippingState;
    unsigned char _brightness;
    unsigned char _contrast;
    unsigned char _fade;

    ClipMode _clipMode;
    ClipType _clipType;
    std::vector<XY> _clipBoundaryVertices;
    ImageDefinitionWPtr _definition;
    ImageDefinitionReactorWPtr _definitionReactor;

public:
    CadImageBase();

    virtual ~CadImageBase();

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

    ImageDisplayFlags Flags() const;
    void Flags(ImageDisplayFlags);

    bool ClippingState() const;
    void ClippingState(bool);

    unsigned char Brightness() const;
    void Brightness(unsigned char);

    unsigned char Contrast() const;
    void Contrast(unsigned char);

    unsigned char Fade() const;
    void Fade(unsigned char);

    dwg::ClipMode ClipMode() const;
    void ClipMode(dwg::ClipMode);

    dwg::ClipType ClipType() const;
    void ClipType(dwg::ClipType);

    std::vector<XY> ClipBoundaryVertices() const;
    void ClipBoundaryVertices(const std::vector<XY> &);

    ImageDefinitionPtr Definition() const;
    void Definition(ImageDefinition *);

    ImageDefinitionReactorPtr DefinitionReactor() const;
    void DefinitionReactor(ImageDefinitionReactor *);
};
CPL_SMARTER_PTR(CadImageBase)

}// namespace dwg

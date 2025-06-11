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
class ImageDefinitionReactor;

class LIBDWG_API CadWipeoutBase : public Entity
{
    int _classVersion;                         ///< Internal version of the class for compatibility.
    XYZ _insertPoint;                          ///< Insertion point of the wipeout object.
    XYZ _uvector;                              ///< U-direction vector defining the orientation.
    XYZ _vvector;                              ///< V-direction vector defining the orientation.
    XY _size;                                  ///< Size of the wipeout object.
    ImageDisplayFlags _flags;                  ///< Display flags controlling image properties.
    bool _clippingState;                       ///< Indicates whether clipping is enabled.
    unsigned char _brightness;                 ///< Brightness level of the image.
    unsigned char _contrast;                   ///< Contrast level of the image.
    unsigned char _fade;                       ///< Fade level of the image.
    ClipMode _clipMode;                        ///< Clipping mode used for the wipeout.
    ClipType _clipType;                        ///< Type of clipping applied.
    std::vector<XY> _clipBoundaryVertices;     ///< Vertices defining the clipping boundary.
    ImageDefinition *_definition;              ///< Reference to the associated image definition.
    ImageDefinitionReactor *_definitionReactor;///< Reactor for image definition changes.

public:
    CadWipeoutBase();
    virtual ~CadWipeoutBase();

    int classVersion() const;
    void setClassVersion(int version);

    XYZ insertPoint() const;
    void setInsertPoint(const XYZ &point);

    XYZ UVector() const;
    void setUVector(const XYZ &vector);

    XYZ VVector() const;
    void setVVector(const XYZ &vector);

    XY size() const;
    void setSize(const XY &size);

    ImageDisplayFlags flags() const;
    void setFlags(ImageDisplayFlags flags);

    bool showImage() const;
    void setShowImage(bool value);

    bool clippingState() const;
    void setClippingState(bool state);

    unsigned char brightness() const;
    void setBrightness(unsigned char value);

    unsigned char contrast() const;
    void setContrast(unsigned char value);

    unsigned char fade() const;
    void setFade(unsigned char value);

    ClipMode clipMode() const;
    void setClipMode(ClipMode mode);

    ClipType clipType() const;
    void setClipType(ClipType type);

    std::vector<XY> clipBoundaryVertices() const;
    void setClipBoundaryVertices(const std::vector<XY> &vertices);

    ImageDefinition *definition() const;
    void setDefinition(ImageDefinition *definition);

    ImageDefinitionReactor *definitionReactor() const;
    void setDefinitionReactor(ImageDefinitionReactor *reactor);

    void unassignDocument() override;
    void assignDocument(CadDocument *document) override;

private:
    void imageDefinitionsOnRemove(CadObject *object);
};

}// namespace dwg
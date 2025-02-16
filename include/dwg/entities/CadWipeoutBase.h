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

/**
 * @class CadWipeoutBase
 * @brief Represents a wipeout entity in a DWG/DXF drawing.
 *
 * CadWipeoutBase is a base class for wipeout entities in CAD drawings. 
 * A wipeout is a drawing entity used to obscure or mask parts of the drawing by filling 
 * a specified region with a solid fill, effectively "wiping out" or hiding the area behind it. 
 * This class is derived from Entity and provides the necessary functionality to handle 
 * the specific properties of wipeout entities.
 */
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
    /**
     * @brief Constructs a CadWipeoutBase object with default values.
     */
    CadWipeoutBase();

    /**
     * @brief Destroys the CadWipeoutBase object.
     */
    virtual ~CadWipeoutBase();

    /**
     * @brief Gets the internal class version.
     * @return The class version.
     */
    int classVersion() const;

    /**
     * @brief Sets the internal class version.
     * @param version The new class version.
     */
    void setClassVersion(int version);

    /**
     * @brief Gets the insertion point of the wipeout.
     * @return The insertion point.
     */
    XYZ insertPoint() const;

    /**
     * @brief Sets the insertion point of the wipeout.
     * @param point The new insertion point.
     */
    void setInsertPoint(const XYZ &point);

    /**
     * @brief Gets the U-direction vector.
     * @return The U-direction vector.
     */
    XYZ UVector() const;

    /**
     * @brief Sets the U-direction vector.
     * @param vector The new U-direction vector.
     */
    void setUVector(const XYZ &vector);

    /**
     * @brief Gets the V-direction vector.
     * @return The V-direction vector.
     */
    XYZ VVector() const;

    /**
     * @brief Sets the V-direction vector.
     * @param vector The new V-direction vector.
     */
    void setVVector(const XYZ &vector);

    /**
     * @brief Gets the size of the wipeout.
     * @return The size.
     */
    XY size() const;

    /**
     * @brief Sets the size of the wipeout.
     * @param size The new size.
     */
    void setSize(const XY &size);

    /**
     * @brief Gets the display flags of the wipeout.
     * @return The display flags.
     */
    ImageDisplayFlags flags() const;

    /**
     * @brief Sets the display flags of the wipeout.
     * @param flags The new display flags.
     */
    void setFlags(ImageDisplayFlags flags);

    bool showImage() const;
    void setShowImage(bool value);

    /**
     * @brief Checks if clipping is enabled.
     * @return True if clipping is enabled, false otherwise.
     */
    bool clippingState() const;

    /**
     * @brief Sets the clipping state.
     * @param state True to enable clipping, false to disable it.
     */
    void setClippingState(bool state);

    /**
     * @brief Gets the brightness level.
     * @return The brightness value.
     */
    unsigned char brightness() const;

    /**
     * @brief Sets the brightness level.
     * @param value The new brightness value.
     */
    void setBrightness(unsigned char value);

    /**
     * @brief Gets the contrast level.
     * @return The contrast value.
     */
    unsigned char contrast() const;

    /**
     * @brief Sets the contrast level.
     * @param value The new contrast value.
     */
    void setContrast(unsigned char value);

    /**
     * @brief Gets the fade level.
     * @return The fade value.
     */
    unsigned char fade() const;

    /**
     * @brief Sets the fade level.
     * @param value The new fade value.
     */
    void setFade(unsigned char value);

    /**
     * @brief Gets the clipping mode.
     * @return The clipping mode.
     */
    ClipMode clipMode() const;

    /**
     * @brief Sets the clipping mode.
     * @param mode The new clipping mode.
     */
    void setClipMode(ClipMode mode);

    /**
     * @brief Gets the clipping type.
     * @return The clipping type.
     */
    ClipType clipType() const;

    /**
     * @brief Sets the clipping type.
     * @param type The new clipping type.
     */
    void setClipType(ClipType type);

    /**
     * @brief Gets the list of vertices defining the clipping boundary.
     * @return A vector containing the clipping boundary vertices.
     */
    std::vector<XY> clipBoundaryVertices() const;

    /**
     * @brief Sets the vertices defining the clipping boundary.
     * @param vertices The new clipping boundary vertices.
     */
    void setClipBoundaryVertices(const std::vector<XY> &vertices);

    /**
     * @brief Gets the associated image definition.
     * @return A pointer to the image definition.
     */
    ImageDefinition *definition() const;

    /**
     * @brief Sets the associated image definition.
     * @param definition A pointer to the new image definition.
     */
    void setDefinition(ImageDefinition *definition);

    /**
     * @brief Gets the associated image definition reactor.
     * @return A pointer to the image definition reactor.
     */
    ImageDefinitionReactor *definitionReactor() const;

    /**
     * @brief Sets the associated image definition reactor.
     * @param reactor A pointer to the new image definition reactor.
     */
    void setDefinitionReactor(ImageDefinitionReactor *reactor);
};

}// namespace dwg

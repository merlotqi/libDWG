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
#include <dwg/enums/entities/ClipMode.h>
#include <dwg/enums/entities/ClipType.h>
#include <dwg/enums/entities/ImageDisplayFlags.h>

#include <dwg/objects/ImageDefinition.h>
#include <dwg/objects/ImageDefinitionReactor.h>

namespace dwg {
namespace entities {

class CadImageBase : public Entity
{
public:
    int classVersion;// 90
    XYZ insertPoint; // 10, 20, 30
    XYZ uvector;     // 11, 21, 31
    XYZ vvector;     // 12, 22, 32
    XY size;         // 13, 23

    ImageDisplayFlags flags;// 70
    bool clippingState;     // 280

    unsigned char Brightness;// 281
    unsigned char Contrast;  // 282
    unsigned char Fade;      // 283

    ClipMode clipMode;// 290
    ClipType clipType;// 71

    // 91, 14, 24
    std::vector<XY> clipBoundaryVertices;

    ImageDefinition definition;// 340, handle

    ImageDefinitionReactor definitionReactor;// 360, handle
};

}// namespace entities

}// namespace dwg

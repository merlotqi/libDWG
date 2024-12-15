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
#include <dwg/tables/Layer.h>
#include <dwg/enums/entities/ViewportStatusFlags.h>

#include <dwg/enums/RenderMode.h>
#include <dwg/enums/OrthographicType.h>
#include <dwg/enums/objects/ShadePlotMode.h>
#include <dwg/objects/VisualStyle.h>
#include <dwg/enums/entities/LightingType.h>
#include <dwg/utils/Color.h>
#include <dwg/objects/Scale.h>

namespace dwg {
namespace entities {

class Viewport : public Entity
{
    public:
    Viewport();
    ~Viewport();

    static constexpr int PaperViewId = 1;
    static constexpr auto ASDK_XREC_ANNOTATION_SCALE_INFO = "ASDK_XREC_ANNOTATION_SCALE_INFO";

    XYZ center; // 10, 20, 30
    double width; // 40
    double height; // 50
    short Id; // 69

    XY viewCenter; // 12, 22
    XY snapBase; // 13, 23
    XY snapSpacing; // 14, 24
    XY gridSpacing; // 15, 25
    XYZ viewDirection; // 16, 26, 36
    XYZ viewTarget; // 17, 27, 37

    double lensLength; // 42
    double frontClipPlane; // 43
    double backClipPlane; // 44
    double viewHeight; // 45


    double viewWidth() const;

    double snapAngle; // 50
    double twistAngle; // 51
    short circleZoomPercent; // 72

    std::vector<tables::Layer*> frozonLayers; // 331 /ignored


ViewportStatusFlags status; // 90
Entity* boundary() const;


std::string styleSheetName; // 1
RenderMode renderMode; // 281

bool ucsPreViewport; // 71
bool displayUcsIcon; // 74

XYZ ucsOrigin; // 110, 120, 130
XYZ ucsXAxis; // 111, 121, 131
XYZ ucsYAxis; // 112, 122, 132

		//345

		//ID/handle of AcDbUCSTableRecord if UCS is a named UCS.If not present, then UCS is unnamed

		//346

		//ID/handle of AcDbUCSTableRecord of base UCS if UCS is orthographic(79 code is non-zero). If not present and 79 code is non-zero, then base UCS is taken to be WORLD

OrthographicType ucsOrthographicType; // 79

double elevation; // 146
objects::ShadePlotMode shadePlotMode; // 170

short MajorGridLineFrequency;  // 61
		//332	Background ID/Handle(optional)

		//333	Shade plot ID/Handle(optional)

        objects::VisualStyle* visualStyle; // 348


bool UseDefaultLighting; // 292
LightingType DefaultLightingType; // 282

double brightness; // 141
double contrast; // 142

utils::Color AmbientLightColor; // 63, 421, 431
		//361	Sun ID/Handle(optional)

		//335

		//Soft pointer reference to viewport object (for layer VP property override)
		//343

		//Soft pointer reference to viewport object (for layer VP property override)
		//344

		//Soft pointer reference to viewport object (for layer VP property override)
		//91

		//Soft pointer reference to viewport object (for layer VP property override)


objects::Scale* scale() const;


};

}// namespace entities
}// namespace dwg

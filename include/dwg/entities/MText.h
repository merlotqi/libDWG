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
#include <dwg/entities/IText.h>

#include <dwg/enums/entities/AttachmentPointType.h>
#include <dwg/enums/entities/BackgroundFillFlags.h>
#include <dwg/enums/entities/ColumnType.h>
#include <dwg/enums/entities/DrawingDirectionType.h>
#include <dwg/enums/entities/LineSpacingStyleType.h>
#include <dwg/tables/TextStyle.h>

#include <dwg/Transparency.h>
#include <dwg/utils/Color.h>

namespace dwg {
namespace entities {

class MText : public Entity, IText
{
public:
    struct Edge
    {
        int Start;
        int End;
        double Crease;

        Edge(int start, int end);
    };


    XYZ insertPoint;                      // 10, 20, 30
    XYZ normal;                           // 210, 220, 230
    double height;                        // 40;
    double rectangleWidth;                //41
    double rectangleHeight;               // 46
    AttachmentPointType attachmentPoint;  // 71
    DrawingDirectionType drawingDirection;// 72
    std::string value;                    // 1
    tables::TextStyle *textStyle;         // 7, name

    XYZ alignmentPoint;                    // 11, 21, 31
    double horizontalWidth;                // 42,
    double verticalHeight;                 // 43
    double rotation;                       // 50
    LineSpacingStyleType lineSpaicingStyle;// 73

    double lineSpacing;                     // 44
    BackgroundFillFlags backgroundFillFlags;// 90
    double backgroundScale;                 // 45


    utils::Color backgroundColor;       // 63, 420, 430
    Transparency backgroundTransparency;// 441；


public:
    struct TextColumn
    {
        ColumnType columnType;  // 75
        int columnCount;        // 76
        bool columnFlowReversed;// 78
        bool columnAutoHeight;  // 79
        double columnWidhth;    // 48
        double columnGutter;    // 49
        std::vector<double> columnHeights;
    };


public:
    TextColumn Column() const;
    void Column(TextColumn const &column);
    bool IsAnnotative() const;
    void IsAnnotative(bool isAnnotative);
};

}// namespace entities
}// namespace dwg
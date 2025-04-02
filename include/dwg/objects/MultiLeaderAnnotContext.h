/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General  License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General  License for more details.
 *
 * You should have received a copy of the GNU General  License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#pragma once

#include <dwg/Color.h>
#include <dwg/Coordinate.h>
#include <dwg/FlowDirectionType.h>
#include <dwg/LineSpacingStyle.h>
#include <dwg/LineWeightType.h>
#include <dwg/TextAlignmentType.h>
#include <dwg/TextAttachmentDirectionType.h>
#include <dwg/TextAttachmentPointType.h>
#include <dwg/TextAttachmentType.h>
#include <dwg/entities/BlockContentConnectionType.h>
#include <dwg/entities/MultiLeaderPathType.h>
#include <dwg/objects/LeaderLinePropertOverrideFlags.h>
#include <dwg/objects/NonGraphicalObject.h>

namespace dwg {

class TextStyle;
class LineType;
class BlockRecord;

class StartEndPointPair
{
    XYZ startPoint;
    XYZ endPoint;
};

class MultiLeaderAnnotContextLeaderLine;
class MultiLeaderAnnotContextLeaderRoot;
class LIBDWG_API MultiLeaderAnnotContext : public NonGraphicalObject
{
public:
    MultiLeaderAnnotContext();
    ~MultiLeaderAnnotContext();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    std::vector<MultiLeaderAnnotContextLeaderRoot> leaderRoots() const;

    double scaleFactor() const;
    void setScaleFactor(double);

    XYZ contentBasePoint() const;
    void setContentBasePoint(const XYZ &);

    double textHeight() const;
    void setTextHeight(double);

    double arrowheadSize() const;
    void setArrowheadSize(double);

    double landingGap() const;
    void setLandingGap(double);

    TextAttachmentType textLeftAttachment() const;
    void setTextLeftAttachment(TextAttachmentType);

    TextAttachmentType textRightAttachment() const;
    void setTextRightAttachment(TextAttachmentType);

    TextAlignmentType textAlignment() const;
    void setTextAlignment(TextAlignmentType);

    BlockContentConnectionType blockContentConnection() const;
    void setBlockContentConnection(BlockContentConnectionType);

    bool hasTextContents() const;
    void setHasTextContents(bool);

    std::string textLabel() const;
    void setTextLabel(const std::string &);

    XYZ textNormal() const;
    void setTextNormal(const XYZ &);

    TextStyle *textStyle();
    void setTextStyle(TextStyle *);

    XYZ textLocation() const;
    void setTextLocation(const XYZ &);

    XYZ direction() const;
    void setDirection(const XYZ &);

    double textRotation() const;
    void setTextRotation(double);

    double boundaryHeight() const;
    void setBoundaryHeight(double);

    double lineSpacingFactor() const;
    void setLineSpacingFactor(double);

    LineSpacingStyle lineSpacing() const;
    void setLineSpacing(LineSpacingStyle);

    Color textColor() const;
    void setTextColor(const Color &);

    TextAttachmentPointType textAttachmentPoint() const;
    void setTextAttachmentPoint(TextAttachmentPointType);

    FlowDirectionType flowDirection() const;
    void setFlowDirection(FlowDirectionType);

    Color backgroundFillColor() const;
    void setBackgroundFillColor(const Color &);

    double backgroundScaleFactor() const;
    void setBackgroundScaleFactor(double);

    int backgroundTransparency() const;
    void setBackgroundTransparency(int);

    bool backgroundFillEnabled() const;
    void setBackgroundFillEnabled(bool);

    bool backgroundMaskFillOn() const;
    void setBackgroundMaskFillOn(bool);

    short columnType() const;
    void setColumnType(short);

    bool textHeightAutomatic() const;
    void setTextHeightAutomatic(bool);

    double columnWidth() const;
    void setColumnWidth(double);

    double columnGutter() const;
    void setColumnGutter(double);

    bool columnFlowReversed() const;
    void setColumnFlowReversed(bool);

    std::vector<double> columnSizes() const;

    bool wordBreak() const;
    void setWordBreak(bool);

    bool hasContentsBlock() const;
    void setHasContentsBlock(bool);

    BlockRecord *blockContent() const;
    void setBlockContent(BlockRecord *);

    XYZ blockContentNormal() const;
    void setBlockContentNormal(const XYZ &);

    XYZ blockContentLocation() const;
    void setBlockContentLocation(const XYZ &);

    XYZ blockContentScale() const;
    void setBlockContentScale(const XYZ &);

    double blockContentRotation() const;
    void setBlockContentRotation(double);

    Color blockContentColor() const;
    void setBlockContentColor(const Color &);

    Matrix4 transformationMatrix() const;
    void setTransformationMatrix(const Matrix4 &);

    XYZ basePoint() const;
    void setBasePoint(const XYZ &);

    XYZ baseDirection() const;
    void setBaseDirection(const XYZ &);

    XYZ baseVertical() const;
    void setBaseVertical(const XYZ &);

    bool normalReversed() const;
    void setNormalReversed(bool);

    TextAttachmentType textTopAttachment() const;
    void setTextTopAttachment(TextAttachmentType);

    TextAttachmentType textBottomAttachment() const;
    void setTextBottomAttachment(TextAttachmentType);
};

class LIBDWG_API MultiLeaderAnnotContextLeaderLine
{
    std::vector<XYZ> points;
    int breakInfoCount;
    int segmentIndex;
    std::vector<StartEndPointPair> startEndPoints;
    int index;
    MultiLeaderPathType pathType;
    Color lineColor;
    LineType *lineType;
    LineweightType lineWeight;
    double arrowheadSize;
    BlockRecord *arrowHead;
    LeaderLinePropertOverrideFlags overrideFlags;
};

class LIBDWG_API MultiLeaderAnnotContextLeaderRoot
{
    bool contentValid;
    bool unknown;
    XYZ connectionPoint;
    XYZ direction;
    std::vector<StartEndPointPair> breakStartEndPointsPairs;
    int leaderIndex;
    double landingDistance;
    std::vector<LeaderLine> lines;
    TextAttachmentDirectionType textAttachmentDirection;
};

}// namespace dwg
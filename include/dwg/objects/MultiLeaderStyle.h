/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General License for more details.
 *
 * You should have received a copy of the GNU General License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#pragma once

#include <dwg/Color.h>
#include <dwg/Coordinate.h>
#include <dwg/LineWeightType.h>
#include <dwg/TextAlignmentType.h>
#include <dwg/TextAngleType.h>
#include <dwg/TextAttachmentDirectionType.h>
#include <dwg/TextAttachmentType.h>
#include <dwg/entities/BlockContentConnectionType.h>
#include <dwg/entities/MultiLeaderPathType.h>
#include <dwg/objects/LeaderContentType.h>
#include <dwg/objects/LeaderDrawOrderType.h>
#include <dwg/objects/MultiLeaderDrawOrderType.h>
#include <dwg/objects/NonGraphicalObject.h>

namespace dwg {

class LineType;
class BlockRecord;
class TextStyle;
class BlockRecord;
class CadDictionary;
class LIBDWG_API MultiLeaderStyle : public NonGraphicalObject
{
public:
    static constexpr auto DefaultName = "Standard";

    static MultiLeaderStyle *Default();

public:
    MultiLeaderStyle();
    MultiLeaderStyle(const std::string &name);
    ~MultiLeaderStyle();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    LeaderContentType contentType() const;
    void setContentType(LeaderContentType);

    MultiLeaderDrawOrderType multiLeaderDrawOrder() const;
    void setMultiLeaderDrawOrder(MultiLeaderDrawOrderType);

    LeaderDrawOrderType leaderDrawOrder() const;
    void setLeaderDrawOrder(LeaderDrawOrderType);

    int maxLeaderSegmentsPoints() const;
    void setMaxLeaderSegmentsPoints(int);

    double firstSegmentAngleConstraint() const;
    void setFirstSegmentAngleConstraint(double);

    double secondSegmentAngleConstraint() const;
    void setSecondSegmentAngleConstraint(double);

    MultiLeaderPathType pathType() const;
    void setPathType(MultiLeaderPathType);

    Color lineColor() const;
    void setLineColor(const Color &);

    LineType *leaderLineType() const;
    void setLeaderLineType(LineType *);

    LineweightType leaderLineWeight() const;
    void setLeaderLineWeight(LineweightType);

    bool enableLanding() const;
    void setEnableLanding(bool);

    double landingGap() const;
    void setLandingGap(double);

    bool enableDogleg() const;
    void setEnableDogleg(bool);

    double landingDistance() const;
    void setLandingDistance(double);

    std::string description() const;
    void setDescription(const std::string &);

    BlockRecord *arrowhead() const;
    void setArrowhead(BlockRecord *);

    double arrowheadSize() const;
    void setArrowheadSize(double);

    std::string defaultTextContents() const;
    void setDefaultTextContents(const std::string &);

    TextStyle *textStyle() const;
    void setTextStyle(TextStyle *);

    TextAttachmentType textLeftAttachment() const;
    void setTextLeftAttachment(TextAttachmentType);

    TextAngleType textAngle() const;
    void setTextAngle(TextAngleType);

    TextAlignmentType textAlignment() const;
    void setTextAlignment(TextAlignmentType);

    TextAlignmentType textRightAttachment() const;
    void setTextRightAttachment(TextAlignmentType);

    Color textColor() const;
    void setTextColor(const Color &);

    double textHeight() const;
    void setTextHeight(double);

    bool textFrame() const;
    void setTextFrame(bool);

    bool textAlignAlwaysLeft() const;
    void setTextAlignAlwaysLeft(bool);

    double alignSpace() const;
    void setAlignSpace(double);

    BlockRecord *blockContent() const;
    void setBlockContent(BlockRecord *);

    Color blockContentColor() const;
    void setBlockContentColor(const Color &);

    XYZ blockContentScale() const;
    void setBlockContentScale(const XYZ &);

    bool enableBlockContentScale() const;
    void setEnableBlockContentScale(bool);

    double blockContentRotation() const;
    void setBlockContentRotation(double);

    bool enableBlockContentRotation() const;
    void setEnableBlockContentRotation(bool);

    BlockContentConnectionType blockContentConnection() const;
    void setBlockContentConnection(BlockContentConnectionType);

    double scaleFactor() const;
    void setScaleFactor(double);

    bool overwritePropertyValue() const;
    void setOverwritePropertyValue(bool);

    bool isAnnotative() const;
    void setIsAnnotative(bool);

    double breakGapSize() const;
    void setBreakGapSize(double);

    TextAttachmentDirectionType textAttachmentDirection() const;
    void setTextAttachmentDirection(TextAttachmentDirectionType);

    TextAttachmentType textBottomAttachment() const;
    void setTextBottomAttachment(TextAttachmentType);

    TextAttachmentType textTopAttachment() const;
    void setTextTopAttachment(TextAttachmentType);

    bool unknownFlag298() const;
    void setUnknownFlag298(bool);

private:
    LeaderContentType _contentType;
    MultiLeaderDrawOrderType _multiLeaderDrawOrder;
    LeaderDrawOrderType _leaderDrawOrder;
    int _maxLeaderSegmentsPoints;
    double _firstSegmentAngleConstraint;
    double _secondSegmentAngleConstraint;
    MultiLeaderPathType _pathType;
    Color _lineColor;
    LineType *_leaderLineType;
    LineweightType _leaderLineWeight;
    bool _enableLanding;
    double _landingGap;
    bool _enableDogleg;
    double _landingDistance;
    std::string _description;
    BlockRecord *_arrowhead;
    double _arrowheadSize;
    std::string _defaultTextContents;
    TextStyle *_textStyle;
    TextAttachmentType _textLeftAttachment;
    TextAngleType _textAngle;
    TextAlignmentType _textAlignment;
    TextAlignmentType _textRightAttachment;
    Color _textColor;
    double _textHeight;
    bool _textFrame;
    bool _textAlignAlwaysLeft;
    double _alignSpace;
    BlockRecord *_blockContent;
    Color _blockContentColor;
    XYZ _blockContentScale;
    bool _enableBlockContentScale;
    double _blockContentRotation;
    bool _enableBlockContentRotation;
    BlockContentConnectionType _blockContentConnection;
    double _scaleFactor;
    bool _overwritePropertyValue;
    bool _isAnnotative;
    double _breakGapSize;
    TextAttachmentDirectionType _textAttachmentDirection;
    TextAttachmentType _textBottomAttachment;
    TextAttachmentType _textTopAttachment;
    bool _unknownFlag298;
};

}// namespace dwg
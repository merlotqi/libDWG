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

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/objects/MultiLeaderStyle.h>

namespace dwg {

MultiLeaderStyle *MultiLeaderStyle::Default()
{
    return new MultiLeaderStyle(DefaultName);
}

MultiLeaderStyle::MultiLeaderStyle() : MultiLeaderStyle("") {}

MultiLeaderStyle::MultiLeaderStyle(const std::string &name)
    : NonGraphicalObject(name), _lineColor(Color(short(0))), _textColor(Color(short(0))),
      _blockContentColor(Color(short(0)))
{
}

MultiLeaderStyle::~MultiLeaderStyle() {}

ObjectType MultiLeaderStyle::objectType() const
{
    return ObjectType::UNLISTED;
}

std::string MultiLeaderStyle::objectName() const
{
    return DxfFileToken::ObjectMLeaderStyle;
}

std::string MultiLeaderStyle::subclassMarker() const
{
    return DxfSubclassMarker::MLeaderStyle;
}

LeaderContentType MultiLeaderStyle::contentType() const
{
    return _contentType;
}

void MultiLeaderStyle::setContentType(LeaderContentType) {}

MultiLeaderDrawOrderType MultiLeaderStyle::multiLeaderDrawOrder() const
{
    return _multiLeaderDrawOrder;
}

void MultiLeaderStyle::setMultiLeaderDrawOrder(MultiLeaderDrawOrderType) {}

LeaderDrawOrderType MultiLeaderStyle::leaderDrawOrder() const
{
    return _leaderDrawOrder;
}

void MultiLeaderStyle::setLeaderDrawOrder(LeaderDrawOrderType) {}

int MultiLeaderStyle::maxLeaderSegmentsPoints() const
{
    return _maxLeaderSegmentsPoints;
}

void MultiLeaderStyle::setMaxLeaderSegmentsPoints(int) {}

double MultiLeaderStyle::firstSegmentAngleConstraint() const
{
    return _firstSegmentAngleConstraint;
}

void MultiLeaderStyle::setFirstSegmentAngleConstraint(double) {}

double MultiLeaderStyle::secondSegmentAngleConstraint() const
{
    return _secondSegmentAngleConstraint;
}

void MultiLeaderStyle::setSecondSegmentAngleConstraint(double) {}

MultiLeaderPathType MultiLeaderStyle::pathType() const
{
    return _pathType;
}

void MultiLeaderStyle::setPathType(MultiLeaderPathType) {}

Color MultiLeaderStyle::lineColor() const
{
    return _lineColor;
}

void MultiLeaderStyle::setLineColor(const Color &) {}

LineType *MultiLeaderStyle::leaderLineType() const
{
    return _leaderLineType;
}

void MultiLeaderStyle::setLeaderLineType(LineType *) {}

LineweightType MultiLeaderStyle::leaderLineWeight() const
{
    return _leaderLineWeight;
}

void MultiLeaderStyle::setLeaderLineWeight(LineweightType) {}

bool MultiLeaderStyle::enableLanding() const
{
    return _enableLanding;
}

void MultiLeaderStyle::setEnableLanding(bool) {}

double MultiLeaderStyle::landingGap() const
{
    return _landingGap;
}

void MultiLeaderStyle::setLandingGap(double) {}

bool MultiLeaderStyle::enableDogleg() const
{
    return _enableDogleg;
}

void MultiLeaderStyle::setEnableDogleg(bool) {}

double MultiLeaderStyle::landingDistance() const
{
    return _landingDistance;
}

void MultiLeaderStyle::setLandingDistance(double) {}

std::string MultiLeaderStyle::description() const
{
    return _description;
}

void MultiLeaderStyle::setDescription(const std::string &) {}

BlockRecord *MultiLeaderStyle::arrowhead() const
{
    return _arrowhead;
}

void MultiLeaderStyle::setArrowhead(BlockRecord *) {}

double MultiLeaderStyle::arrowheadSize() const
{
    return _arrowheadSize;
}

void MultiLeaderStyle::setArrowheadSize(double) {}

std::string MultiLeaderStyle::defaultTextContents() const
{
    return _defaultTextContents;
}

void MultiLeaderStyle::setDefaultTextContents(const std::string &) {}

TextStyle *MultiLeaderStyle::textStyle() const
{
    return _textStyle;
}

void MultiLeaderStyle::setTextStyle(TextStyle *) {}

TextAttachmentType MultiLeaderStyle::textLeftAttachment() const
{
    return _textLeftAttachment;
}

void MultiLeaderStyle::setTextLeftAttachment(TextAttachmentType) {}

TextAngleType MultiLeaderStyle::textAngle() const
{
    return _textAngle;
}

void MultiLeaderStyle::setTextAngle(TextAngleType) {}

TextAlignmentType MultiLeaderStyle::textAlignment() const
{
    return _textAlignment;
}

void MultiLeaderStyle::setTextAlignment(TextAlignmentType) {}

TextAlignmentType MultiLeaderStyle::textRightAttachment() const
{
    return _textRightAttachment;
}

void MultiLeaderStyle::setTextRightAttachment(TextAlignmentType) {}

Color MultiLeaderStyle::textColor() const
{
    return _textColor;
}

void MultiLeaderStyle::setTextColor(const Color &) {}

double MultiLeaderStyle::textHeight() const
{
    return _textHeight;
}

void MultiLeaderStyle::setTextHeight(double) {}

bool MultiLeaderStyle::textFrame() const
{
    return _textFrame;
}

void MultiLeaderStyle::setTextFrame(bool) {}

bool MultiLeaderStyle::textAlignAlwaysLeft() const
{
    return _textAlignAlwaysLeft;
}

void MultiLeaderStyle::setTextAlignAlwaysLeft(bool) {}

double MultiLeaderStyle::alignSpace() const
{
    return _alignSpace;
}

void MultiLeaderStyle::setAlignSpace(double) {}

BlockRecord *MultiLeaderStyle::blockContent() const
{
    return _blockContent;
}

void MultiLeaderStyle::setBlockContent(BlockRecord *) {}

Color MultiLeaderStyle::blockContentColor() const
{
    return _blockContentColor;
}

void MultiLeaderStyle::setBlockContentColor(const Color &) {}

XYZ MultiLeaderStyle::blockContentScale() const
{
    return _blockContentScale;
}

void MultiLeaderStyle::setBlockContentScale(const XYZ &) {}

bool MultiLeaderStyle::enableBlockContentScale() const
{
    return _enableBlockContentScale;
}

void MultiLeaderStyle::setEnableBlockContentScale(bool) {}

double MultiLeaderStyle::blockContentRotation() const
{
    return _blockContentRotation;
}

void MultiLeaderStyle::setBlockContentRotation(double) {}

bool MultiLeaderStyle::enableBlockContentRotation() const
{
    return _enableBlockContentRotation;
}

void MultiLeaderStyle::setEnableBlockContentRotation(bool) {}

BlockContentConnectionType MultiLeaderStyle::blockContentConnection() const
{
    return _blockContentConnection;
}

void MultiLeaderStyle::setBlockContentConnection(BlockContentConnectionType) {}

double MultiLeaderStyle::scaleFactor() const
{
    return _scaleFactor;
}

void MultiLeaderStyle::setScaleFactor(double) {}

bool MultiLeaderStyle::overwritePropertyValue() const
{
    return _overwritePropertyValue;
}

void MultiLeaderStyle::setOverwritePropertyValue(bool) {}

bool MultiLeaderStyle::isAnnotative() const
{
    return _isAnnotative;
}

void MultiLeaderStyle::setIsAnnotative(bool) {}

double MultiLeaderStyle::breakGapSize() const
{
    return _breakGapSize;
}

void MultiLeaderStyle::setBreakGapSize(double) {}

TextAttachmentDirectionType MultiLeaderStyle::textAttachmentDirection() const
{
    return _textAttachmentDirection;
}

void MultiLeaderStyle::setTextAttachmentDirection(TextAttachmentDirectionType) {}

TextAttachmentType MultiLeaderStyle::textBottomAttachment() const
{
    return _textBottomAttachment;
}

void MultiLeaderStyle::setTextBottomAttachment(TextAttachmentType) {}

TextAttachmentType MultiLeaderStyle::textTopAttachment() const
{
    return _textTopAttachment;
}

void MultiLeaderStyle::setTextTopAttachment(TextAttachmentType) {}

bool MultiLeaderStyle::unknownFlag298() const
{
    return _unknownFlag298;
}

void MultiLeaderStyle::setUnknownFlag298(bool value)
{
    _unknownFlag298 = value;
}

}// namespace dwg
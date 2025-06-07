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
#include <dwg/entities/MultiLeader.h>
#include <dwg/CadDocument.h>
#include <dwg/objects/MultiLeaderStyle.h>
#include <dwg/objects/MultiLeaderAnnotContext.h>
#include <dwg/objects/collections/MLeaderStyleCollection.h>

namespace dwg {

bool MultiLeader::BlockAttribute::operator==(const BlockAttribute &other) const
{
    return false;
}

bool MultiLeader::BlockAttribute::operator<(const BlockAttribute &other) const
{
    return false;
}


MultiLeader::MultiLeader() {}

MultiLeader::~MultiLeader() {}

ObjectType MultiLeader::objectType() const
{
    return ObjectType::UNLISTED;
}

std::string MultiLeader::objectName() const
{
    return DxfFileToken::EntityMultiLeader;
}

std::string MultiLeader::subclassMarker() const
{
    return DxfSubclassMarker::MultiLeader;
}

BlockRecord *MultiLeader::arrowhead() const
{
    return _arrowhead;
}

void MultiLeader::setArrowhead(BlockRecord *value)
{
    _arrowhead = value;
}

double MultiLeader::arrowheadSize() const
{
    return _arrowheadSize;
}

void MultiLeader::setArrowheadSize(double value)
{
    _arrowheadSize = value;
}

std::vector<MultiLeader::BlockAttribute> MultiLeader::blockAttributes() const
{
    return _blockAttributes;
}

void MultiLeader::setBlockAttributes(const std::vector<MultiLeader::BlockAttribute> &value)
{
    _blockAttributes = value;
}

LeaderContentType MultiLeader::contentType() const
{
    return _contentType;
}

void MultiLeader::setContentType(LeaderContentType value)
{
    _contentType = value;
}

MultiLeaderAnnotContext *MultiLeader::contextData() const
{
    return _contextData;
}

void MultiLeader::setContextData(MultiLeaderAnnotContext *value)
{
    _contextData = value;
}

bool MultiLeader::enableAnnotationScale() const
{
    return _enableAnnotationScale;
}

void MultiLeader::setEnableAnnotationScale(bool value)
{
    _enableAnnotationScale = value;
}

bool MultiLeader::enableDogleg() const
{
    return _enableDogleg;
}

void MultiLeader::setEnableDogleg(bool value)
{
    _enableDogleg = value;
}

bool MultiLeader::enableLanding() const
{
    return _enableLanding;
}

void MultiLeader::setEnableLanding(bool value)
{
    _enableLanding = value;
}

bool MultiLeader::extendedToText() const
{
    return _extendedToText;
}

void MultiLeader::setExtendedToText(bool value)
{
    _extendedToText = value;
}

double MultiLeader::landingDistance() const
{
    return _landingDistance;
}

void MultiLeader::setLandingDistance(double value)
{
    _landingDistance = value;
}

LineType *MultiLeader::leaderLineType() const
{
    return _leaderLineType;
}

void MultiLeader::setLeaderLineType(LineType *value)
{
    _leaderLineType = value;
}

LineweightType MultiLeader::leaderLineWeight() const
{
    return _leaderLineWeight;
}

void MultiLeader::setLeaderLineWeight(LineweightType value)
{
    _leaderLineWeight = value;
}

Color MultiLeader::lineColor() const
{
    return _lineColor;
}

void MultiLeader::setLineColor(const Color &value)
{
    _lineColor = value;
}

MultiLeaderPathType MultiLeader::pathType() const
{
    return _pathType;
}

void MultiLeader::setPathType(MultiLeaderPathType value)
{
    _pathType = value;
}

MultiLeaderPropertyOverrideFlags MultiLeader::propertyOverrideFlags() const
{
    return _propertyOverrideFlags;
}

void MultiLeader::setPropertyOverrideFlags(MultiLeaderPropertyOverrideFlags value)
{
    _propertyOverrideFlags = value;
}

double MultiLeader::scaleFactor() const
{
    return _scaleFactor;
}

void MultiLeader::setScaleFactor(double value)
{
    _scaleFactor = value;
}

MultiLeaderStyle *MultiLeader::style() const
{
    return _style;
}

void MultiLeader::setStyle(MultiLeaderStyle *value)
{
    if (_document)
    {
        _style = updateCollectionT<MultiLeaderStyle *>(value, _document->mleaderStyles());
    }
    else
    {
        _style = value;
    }
}

TextAlignmentType MultiLeader::textAlignment() const
{
    return _textAlignment;
}

void MultiLeader::setTextAlignment(TextAlignmentType value)
{
    _textAlignment = value;
}

TextAngleType MultiLeader::textAngle() const
{
    return _textAngle;
}

void MultiLeader::setTextAngle(TextAngleType value)
{
    _textAngle = value;
}

Color MultiLeader::textColor() const
{
    return _textColor;
}

void MultiLeader::setTextColor(const Color &value)
{
    _textColor = value;
}

bool MultiLeader::textFrame() const
{
    return _textFrame;
}

void MultiLeader::setTextFrame(bool value)
{
    _textFrame = value;
}

TextAttachmentType MultiLeader::textLeftAttachment() const
{
    return _textLeftAttachment;
}

void MultiLeader::setTextLeftAttachment(TextAttachmentType value)
{
    _textLeftAttachment = value;
}

TextAttachmentType MultiLeader::textRightAttachment() const
{
    return _textRightAttachment;
}

void MultiLeader::setTextRightAttachment(TextAttachmentType value)
{
    _textRightAttachment = value;
}

TextStyle *MultiLeader::textStyle() const
{
    return _textStyle;
}

void MultiLeader::setTextStyle(TextStyle *value)
{
    _textStyle = value;
}

LineweightType MultiLeader::leaderLineLength() const
{
    return _leaderLineLength;
}

void MultiLeader::setLeaderLineLength(LineweightType value)
{
    _leaderLineLength = value;
}

BlockRecord *MultiLeader::blockContent() const
{
    return _blockContent;
}

void MultiLeader::setBlockContent(BlockRecord *value)
{
    _blockContent = value;
}

Color MultiLeader::blockContentColor() const
{
    return _blockContentColor;
}

void MultiLeader::setBlockContentColor(const Color &value)
{
    _blockContentColor = value;
}

BlockContentConnectionType MultiLeader::blockContentConnection() const
{
    return _blockContentConnection;
}

void MultiLeader::setBlockContentConnection(BlockContentConnectionType value)
{
    _blockContentConnection = value;
}

double MultiLeader::blockContentRotation() const
{
    return _blockContentRotation;
}

void MultiLeader::setBlockContentRotation(double value)
{
    _blockContentRotation = value;
}

XYZ MultiLeader::blockContentScale() const
{
    return _blockContentScale;
}

void MultiLeader::setBlockContentScale(const XYZ &value)
{
    _blockContentScale = value;
}

short MultiLeader::textAligninIPE() const
{
    return _textAligninIPE;
}

void MultiLeader::setTextAligninIPE(short value)
{
    _textAligninIPE = value;
}

TextAttachmentDirectionType MultiLeader::textAttachmentDirection() const
{
    return _textAttachmentDirection;
}

void MultiLeader::setTextAttachmentDirection(TextAttachmentDirectionType value)
{
    _textAttachmentDirection = value;
}

TextAttachmentPointType MultiLeader::textAttachmentPoint() const
{
    return _textAttachmentPoint;
}

void MultiLeader::setTextAttachmentPoint(TextAttachmentPointType value)
{
    _textAttachmentPoint = value;
}

TextAttachmentType MultiLeader::textBottomAttachment() const
{
    return _textBottomAttachment;
}

void MultiLeader::setTextBottomAttachment(TextAttachmentType value)
{
    _textBottomAttachment = value;
}

bool MultiLeader::textDirectionNegative() const
{
    return _textDirectionNegative;
}

void MultiLeader::setTextDirectionNegative(bool value)
{
    _textDirectionNegative = value;
}

TextAttachmentType MultiLeader::textTopAttachment() const
{
    return _textTopAttachment;
}

void MultiLeader::setTextTopAttachment(TextAttachmentType value)
{
    _textTopAttachment = value;
}

void MultiLeader::assignDocument(CadDocument *document) 
{
    Entity::assignDocument(document);
    _style = updateCollectionT<MultiLeaderStyle *>(_style, document->mleaderStyles());

    _contextData->assignDocument(document);

}

void MultiLeader::unassignDocument() {}

void MultiLeader::tableOnRemove(CadObject *object) {}

}// namespace dwg
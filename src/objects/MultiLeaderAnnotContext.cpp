/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software{} you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation{} either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY{} without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program{} if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/objects/MultiLeaderAnnotContext.h>

namespace dwg {

MultiLeaderAnnotContext::MultiLeaderAnnotContext() {}

MultiLeaderAnnotContext::~MultiLeaderAnnotContext() {}

ObjectType MultiLeaderAnnotContext::objectType() const
{
    return ObjectType::UNLISTED;
}

std::string MultiLeaderAnnotContext::objectName() const
{
    return DxfFileToken::ObjectMLeaderContextData;
}

std::string MultiLeaderAnnotContext::subclassMarker() const
{
    return DxfSubclassMarker::MultiLeaderAnnotContext;
}

std::vector<MultiLeaderAnnotContext::LeaderRoot> MultiLeaderAnnotContext::leaderRoots() const
{
    return _leaderRoots;
}

double MultiLeaderAnnotContext::MultiLeaderAnnotContext::scaleFactor() const
{
    return _scaleFactor;
}

void MultiLeaderAnnotContext::setScaleFactor(double value)
{
    _scaleFactor = value;
}

XYZ MultiLeaderAnnotContext::contentBasePoint() const
{
    return _contentBasePoint;
}

void MultiLeaderAnnotContext::setContentBasePoint(const XYZ &value)
{
    _contentBasePoint = value;
}

double MultiLeaderAnnotContext::textHeight() const
{
    return _textHeight;
}

void MultiLeaderAnnotContext::setTextHeight(double value)
{
    _textHeight = value;
}

double MultiLeaderAnnotContext::arrowheadSize() const
{
    return _arrowheadSize;
}

void MultiLeaderAnnotContext::setArrowheadSize(double value)
{
    _arrowheadSize = value;
}

double MultiLeaderAnnotContext::landingGap() const
{
    return _landingGap;
}

void MultiLeaderAnnotContext::setLandingGap(double value)
{
    _landingGap = value;
}

TextAttachmentType MultiLeaderAnnotContext::textLeftAttachment() const
{
    return _textLeftAttachment;
}

void MultiLeaderAnnotContext::setTextLeftAttachment(TextAttachmentType value)
{
    _textLeftAttachment = value;
}

TextAttachmentType MultiLeaderAnnotContext::textRightAttachment() const
{
    return _textRightAttachment;
}

void MultiLeaderAnnotContext::setTextRightAttachment(TextAttachmentType value)
{
    _textRightAttachment = value;
}

TextAlignmentType MultiLeaderAnnotContext::textAlignment() const
{
    return _textAlignment;
}

void MultiLeaderAnnotContext::setTextAlignment(TextAlignmentType value)
{
    _textAlignment = value;
}

BlockContentConnectionType MultiLeaderAnnotContext::blockContentConnection() const
{
    return _blockContentConnection;
}

void MultiLeaderAnnotContext::setBlockContentConnection(BlockContentConnectionType value)
{
    _blockContentConnection = value;
}

bool MultiLeaderAnnotContext::MultiLeaderAnnotContext::hasTextContents() const
{
    return _hasTextContents;
}

void MultiLeaderAnnotContext::setHasTextContents(bool value)
{
    _hasTextContents = value;
}

std::string MultiLeaderAnnotContext::textLabel() const
{
    return _textLabel;
}

void MultiLeaderAnnotContext::setTextLabel(const std::string &value)
{
    _textLabel = value;
}

XYZ MultiLeaderAnnotContext::textNormal() const
{
    return _textNormal;
}

void MultiLeaderAnnotContext::setTextNormal(const XYZ &value)
{
    _textNormal = value;
}

TextStyle *MultiLeaderAnnotContext::textStyle()
{
    return nullptr;
}

void MultiLeaderAnnotContext::setTextStyle(TextStyle *value)
{
    _textStyle = value;
}

XYZ MultiLeaderAnnotContext::textLocation() const
{
    return _textLocation;
}

void MultiLeaderAnnotContext::setTextLocation(const XYZ &value)
{
    _textLocation = value;
}

XYZ MultiLeaderAnnotContext::direction() const
{
    return _direction;
}

void MultiLeaderAnnotContext::setDirection(const XYZ &value)
{
    _direction = value;
}

double MultiLeaderAnnotContext::textRotation() const
{
    return _textRotation;
}

void MultiLeaderAnnotContext::setTextRotation(double value)
{
    _textRotation = value;
}

double MultiLeaderAnnotContext::boundaryWidth() const
{
    return _boundaryWidth;
}

void MultiLeaderAnnotContext::setBoundaryWidth(double value)
{
    _boundaryWidth = value;
}

double MultiLeaderAnnotContext::boundaryHeight() const
{
    return _boundaryHeight;
}

void MultiLeaderAnnotContext::setBoundaryHeight(double value)
{
    _boundaryHeight = value;
}

double MultiLeaderAnnotContext::lineSpacingFactor() const
{
    return _lineSpacingFactor;
}

void MultiLeaderAnnotContext::setLineSpacingFactor(double value)
{
    _lineSpacingFactor = value;
}

LineSpacingStyle MultiLeaderAnnotContext::lineSpacing() const
{
    return _lineSpacing;
}

void MultiLeaderAnnotContext::setLineSpacing(LineSpacingStyle value)
{
    _lineSpacing = value;
}

Color MultiLeaderAnnotContext::textColor() const
{
    return _textColor;
}

void MultiLeaderAnnotContext::setTextColor(const Color &value)
{
    _textColor = value;
}

TextAttachmentPointType MultiLeaderAnnotContext::textAttachmentPoint() const
{
    return _textAttachmentPoint;
}

void MultiLeaderAnnotContext::setTextAttachmentPoint(TextAttachmentPointType value)
{
    _textAttachmentPoint = value;
}

FlowDirectionType MultiLeaderAnnotContext::flowDirection() const
{
    return _flowDirection;
}

void MultiLeaderAnnotContext::setFlowDirection(FlowDirectionType value)
{
    _flowDirection = value;
}

Color MultiLeaderAnnotContext::backgroundFillColor() const
{
    return _backgroundFillColor;
}

void MultiLeaderAnnotContext::setBackgroundFillColor(const Color &value)
{
    _backgroundFillColor = value;
}

double MultiLeaderAnnotContext::backgroundScaleFactor() const
{
    return _backgroundScaleFactor;
}

void MultiLeaderAnnotContext::setBackgroundScaleFactor(double value)
{
    _backgroundScaleFactor = value;
}

int MultiLeaderAnnotContext::backgroundTransparency() const
{
    return _backgroundTransparency;
}

void MultiLeaderAnnotContext::setBackgroundTransparency(int value)
{
    _backgroundTransparency = value;
}

bool MultiLeaderAnnotContext::MultiLeaderAnnotContext::backgroundFillEnabled() const
{
    return _backgroundFillEnabled;
}

void MultiLeaderAnnotContext::setBackgroundFillEnabled(bool value)
{
    _backgroundFillEnabled = value;
}

bool MultiLeaderAnnotContext::MultiLeaderAnnotContext::backgroundMaskFillOn() const
{
    return _backgroundMaskFillOn;
}

void MultiLeaderAnnotContext::setBackgroundMaskFillOn(bool value)
{
    _backgroundMaskFillOn = value;
}

short MultiLeaderAnnotContext::columnType() const
{
    return _columnType;
}

void MultiLeaderAnnotContext::setColumnType(short value)
{
    _columnType = value;
}

bool MultiLeaderAnnotContext::MultiLeaderAnnotContext::textHeightAutomatic() const
{
    return _textHeightAutomatic;
}

void MultiLeaderAnnotContext::setTextHeightAutomatic(bool value)
{
    _textHeightAutomatic = value;
}

double MultiLeaderAnnotContext::columnWidth() const
{
    return _columnWidth;
}

void MultiLeaderAnnotContext::setColumnWidth(double value)
{
    _columnWidth = value;
}

double MultiLeaderAnnotContext::columnGutter() const
{
    return _columnGutter;
}

void MultiLeaderAnnotContext::setColumnGutter(double value)
{
    _columnGutter = value;
}

bool MultiLeaderAnnotContext::columnFlowReversed() const
{
    return _columnFlowReversed;
}

void MultiLeaderAnnotContext::setColumnFlowReversed(bool value)
{
    _columnFlowReversed = value;
}

std::vector<double> MultiLeaderAnnotContext::columnSizes() const
{
    return _columnSizes;
}

std::vector<double> &MultiLeaderAnnotContext::columnSizes()
{
    return _columnSizes;
}

bool MultiLeaderAnnotContext::wordBreak() const
{
    return _wordBreak;
}

void MultiLeaderAnnotContext::setWordBreak(bool value)
{
    _wordBreak = value;
}

bool MultiLeaderAnnotContext::hasContentsBlock() const
{
    return _hasContentsBlock;
}

void MultiLeaderAnnotContext::setHasContentsBlock(bool value)
{
    _hasContentsBlock = value;
}

BlockRecord *MultiLeaderAnnotContext::blockContent() const
{
    return _blockContent;
}

void MultiLeaderAnnotContext::setBlockContent(BlockRecord *value)
{
    _blockContent = value;
}

XYZ MultiLeaderAnnotContext::blockContentNormal() const
{
    return _blockContentNormal;
}

void MultiLeaderAnnotContext::setBlockContentNormal(const XYZ &value)
{
    _blockContentNormal = value;
}

XYZ MultiLeaderAnnotContext::blockContentLocation() const
{
    return _blockContentLocation;
}

void MultiLeaderAnnotContext::setBlockContentLocation(const XYZ &value)
{
    _blockContentLocation = value;
}

XYZ MultiLeaderAnnotContext::blockContentScale() const
{
    return _blockContentScale;
}

void MultiLeaderAnnotContext::setBlockContentScale(const XYZ &value)
{
    _blockContentScale = value;
}

double MultiLeaderAnnotContext::blockContentRotation() const
{
    return _blockContentRotation;
}

void MultiLeaderAnnotContext::setBlockContentRotation(double value)
{
    _blockContentRotation = value;
}

Color MultiLeaderAnnotContext::blockContentColor() const
{
    return _blockContentColor;
}

void MultiLeaderAnnotContext::setBlockContentColor(const Color &value)
{
    _blockContentColor = value;
}

Matrix4 MultiLeaderAnnotContext::transformationMatrix() const
{
    return _transformationMatrix;
}

void MultiLeaderAnnotContext::setTransformationMatrix(const Matrix4 &value)
{
    _transformationMatrix = value;
}

XYZ MultiLeaderAnnotContext::basePoint() const
{
    return _basePoint;
}

void MultiLeaderAnnotContext::setBasePoint(const XYZ &value)
{
    _basePoint = value;
}

XYZ MultiLeaderAnnotContext::baseDirection() const
{
    return _baseDirection;
}

void MultiLeaderAnnotContext::setBaseDirection(const XYZ &value)
{
    _baseDirection = value;
}

XYZ MultiLeaderAnnotContext::baseVertical() const
{
    return _baseVertical;
}

void MultiLeaderAnnotContext::setBaseVertical(const XYZ &value)
{
    _baseVertical = value;
}

bool MultiLeaderAnnotContext::normalReversed() const
{
    return _normalReversed;
}

void MultiLeaderAnnotContext::setNormalReversed(bool value)
{
    _normalReversed = value;
}

TextAttachmentType MultiLeaderAnnotContext::textTopAttachment() const
{
    return _textTopAttachment;
}

void MultiLeaderAnnotContext::setTextTopAttachment(TextAttachmentType value)
{
    _textTopAttachment = value;
}

TextAttachmentType MultiLeaderAnnotContext::textBottomAttachment() const
{
    return _textBottomAttachment;
}

void MultiLeaderAnnotContext::setTextBottomAttachment(TextAttachmentType value)
{
    _textBottomAttachment = value;
}

void MultiLeaderAnnotContext::assignDocument(CadDocument *doc) {}

void MultiLeaderAnnotContext::unassignDocument() {}

}// namespace dwg
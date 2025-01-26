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

#include <dwg/Color.h>
#include <dwg/DxfSubclassMarker.h>
#include <dwg/LineWeightType.h>
#include <dwg/tables/ArcLengthSymbolPosition.h>
#include <dwg/tables/DimensionTextBackgroundFillMode.h>
#include <dwg/tables/DimensionTextHorizontalAlignment.h>
#include <dwg/tables/DimensionTextVerticalAlignment.h>
#include <dwg/tables/FractionFormat.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/tables/TextArrowFitType.h>
#include <dwg/tables/TextDirection.h>
#include <dwg/tables/TextMovement.h>
#include <dwg/tables/ToleranceAlignment.h>
#include <dwg/tables/ZeroHandling.h>
#include <dwg/units/AngularUnitFormat.h>
#include <dwg/units/LinearUnitFormat.h>

namespace dwg {

class LIBDWG_API DG_DimensionStyle : public DG_TableEntry
{
public:
    static constexpr auto DefaultName = "Standard";
    static CPL::SmarterPtr<DG_DimensionStyle> Default();

public:
    DG_DimensionStyle();
    DG_DimensionStyle(const char *name);
    ~DG_DimensionStyle();

    DG_ObjectType ObjectType() const override;
    CPL::String ObjectName() const override;
    CPL::String SubclassMarker() const override;

    CPL::String PostFix() const;
    void PostFix(const char *);
    
    CPL::String AlternateDimensioningSuffix() const;
    void AlternateDimensioningSuffix(const char *);
    
    bool GenerateTolerances() const;
    void GenerateTolerances(bool);
    
    bool LimitsGeneration() const;
    void LimitsGeneration(bool);
    
    bool TextInsideHorizontal() const;
    void TextInsideHorizontal(bool);
    
    bool TextOutsideHorizontal() const;
    void TextOutsideHorizontal(bool);
    
    bool SuppressFirstExtensionLine() const;
    void SuppressFirstExtensionLine(bool);
    
    bool SuppressSecondExtensionLine() const;
    void SuppressSecondExtensionLine(bool);

    DG_DimensionTextVerticalAlignment TextVerticalAlignment() const;
    void TextVerticalAlignment(DG_DimensionTextVerticalAlignment);
    
    DG_ZeroHandling ZeroHandling() const;
    void ZeroHandling(DG_ZeroHandling);

    bool AlternateUnitDimensioning() const;
    void AlternateUnitDimensioning(bool);
    
    short AlternateUnitDecimalPlaces() const;
    void AlternateUnitDecimalPlaces(short);

    bool TextOutsideExtensions() const;
    void TextOutsideExtensions(bool);
    
    bool SeparateArrowBlocks() const;
    void SeparateArrowBlocks(bool);
    
    bool TextInsideExtensions() const;
    void TextInsideExtensions(bool);
    
    bool SuppressOutsideExtensions() const;
    void SuppressOutsideExtensions(bool);

    short AngularDimensionDecimalPlaces() const;
    void AngularDimensionDecimalPlaces(short);

    DG_DimensionTextHorizontalAlignment TextHorizontalAlignment() const;
    void TextHorizontalAlignment(DG_DimensionTextHorizontalAlignment);
    
    bool SuppressFirstDimensionLine() const;
    void SuppressFirstDimensionLine(bool);
    
    bool SuppressSecondDimensionLine() const;
    void SuppressSecondDimensionLine(bool);
    
    DG_ToleranceAlignment ToleranceAlignment() const;
    void ToleranceAlignment(DG_ToleranceAlignment);

    DG_ZeroHandling ToleranceZeroHandling() const;
    void ToleranceZeroHandling(DG_ZeroHandling);
    
    DG_ZeroHandling AlternateUnitZeroHandling() const;
    void AlternateUnitZeroHandling(DG_ZeroHandling);

    short DimensionFit() const;
    void DimensionFit(short);

    bool CursorUpdate() const;
    void CursorUpdate(bool);

    DG_ZeroHandling AlternateUnitToleranceZeroHandling() const;
    void AlternateUnitToleranceZeroHandling(DG_ZeroHandling);

    short DimensionUnit() const;
    void DimensionUnit(short);
    
    DG_AngularUnitFormat AngularUnit() const;
    void AngularUnit(DG_AngularUnitFormat);

    short DecimalPlaces() const;
    void DecimalPlaces(short);

    short ToleranceDecimalPlaces() const;
    void ToleranceDecimalPlaces(short);

    DG_LinearUnitFormat AlternateUnitFormat() const;
    void AlternateUnitFormat(DG_LinearUnitFormat);

    short AlternateUnitToleranceDecimalPlaces() const;
    void AlternateUnitToleranceDecimalPlaces(short);
    
    double ScaleFactor() const;
    void ScaleFactor(double);
    
    double ArrowSize() const;
    void ArrowSize(double);

    double ExtensionLineOffset() const;
    void ExtensionLineOffset(double);
    
    double DimensionLineIncrement() const;
    void DimensionLineIncrement(double);

    double ExtensionLineExtension() const;
    void ExtensionLineExtension(double);
    
    double Rounding() const;
    void Rounding(double);

    double DimensionLineExtension() const;
    void DimensionLineExtension(double);
    
    double PlusTolerance() const;
    void PlusTolerance(double);
    
    double MinusTolerance() const;
    void MinusTolerance(double);

    double FixedExtensionLineLength() const;
    void FixedExtensionLineLength(double);

    double JoggedRadiusDimensionTransverseSegmentAngle() const;
    void JoggedRadiusDimensionTransverseSegmentAngle(double);
    
    DG_DimensionTextBackgroundFillMode TextBackgroundFillMode() const;
    void TextBackgroundFillMode(DG_DimensionTextBackgroundFillMode);
    
    DG_Color TextBackgroundColor() const;
    void TextBackgroundColor(const DG_Color &);
    
    DG_ZeroHandling AngularZeroHandling() const;
    void AngularZeroHandling(DG_ZeroHandling);
    
    DG_ArcLengthSymbolPosition ArcLengthSymbolPosition() const;
    void ArcLengthSymbolPosition(DG_ArcLengthSymbolPosition);
    
    double TextHeight() const;
    void TextHeight(double);
    
    double CenterMarkSize() const;
    void CenterMarkSize(double);
    
    double TickSize() const;
    void TickSize(double);
    
    double AlternateUnitScaleFactor() const;
    void AlternateUnitScaleFactor(double);
    
    double LinearScaleFactor() const;
    void LinearScaleFactor(double);
    
    double TextVerticalPosition() const;
    void TextVerticalPosition(double);
    
    double ToleranceScaleFactor() const;
    void ToleranceScaleFactor(double);
    
    double DimensionLineGap() const;
    void DimensionLineGap(double);
    
    double AlternateUnitRounding() const;
    void AlternateUnitRounding(double);
    
    DG_Color DimensionLineColor() const;
    void DimensionLineColor(const DG_Color &);
    
    DG_Color ExtensionLineColor() const;
    void ExtensionLineColor(const DG_Color &);
    
    DG_Color TextColor() const;
    void TextColor(const DG_Color &);
    
    DG_FractionFormat FractionFormat() const;
    void FractionFormat(DG_FractionFormat);
    
    DG_LinearUnitFormat LinearUnitFormat() const;
    void LinearUnitFormat(DG_LinearUnitFormat);
    
    char DecimalSeparator() const;
    void DecimalSeparator(char);

    DG_TextMovement TextMovement() const;
    void TextMovement(DG_TextMovement);
    
    bool IsExtensionLineLengthFixed() const;
    void IsExtensionLineLengthFixed(bool);
    
    DG_TextDirection TextDirection() const;
    void TextDirection(DG_TextDirection);
    
    DG_LineweightType DimensionLineWeight() const;
    void DimensionLineWeight(DG_LineweightType);
    
    DG_LineweightType ExtensionLineWeight() const;
    void ExtensionLineWeight(DG_LineweightType);
    
    DG_TextArrowFitType DimensionTextArrowFit() const;
    void DimensionTextArrowFit(DG_TextArrowFitType);
    
    DG_TextStylePtr Style() const;
    void Style(TextStyle *);

    DG_BlockRecordPtr LeaderArrow() const;
    void LeaderArrow(DG_BlockRecord *);
  
    DG_BlockRecordPtr ArrowBlock() const;
    void ArrowBlock(DG_BlockRecord *);  
  
    DG_BlockRecordPtr DimArrow1() const;
    void DimArrow1(DG_BlockRecord *);  
  
    DG_BlockRecordPtr DimArrow2() const;
    void DimArrow2(DG_BlockRecord *);  
};
CPL_SMARTER_PTR(DG_DimensionStyle)

class LIBDWG_API DG_DimensionStylesTable : public DG_Table
{
public:
    DG_DimensionStylesTable();

    DG_ObjectType ObjectType() const override;
    CPL::String ObjectName() const override;

protected:
    std::vector<CPL::String> defaultEntries() const;
};
CPL_SMARTER_PTR(DG_DimensionStylesTable)

}// namespace dwg
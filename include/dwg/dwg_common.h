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

#ifndef __DWG_COMMON_H__
#define __DWG_COMMON_H__

namespace DWG
{

/**
 * @enum ACadVersion
 * @brief Drawing format version.
 */
enum ACadVersion : short
{
  /**
   * @brief Version not identified.
   */
  Unknown = -1,
  /**
   * @brief Release 1.1
   */
  MC0_0,
  /**
   * @brief Release 1.2
   */
  AC1_2,
  /**
   * @brief Release 1.4
   */
  AC1_4,
  /**
   * @brief Release 2.0
   */
  AC1_50,
  /**
   * @brief Release 2.10
   */
  AC2_10,
  /**
   * @brief Release 2.5
   */
  AC1002,
  /**
   * @brief Release 2.6
   */
  AC1003,
  /**
   * @brief Release 9
   */
  AC1004,
  /**
   * @brief Release 10
   */
  AC1006,
  /**
   * @brief Release 11/12 (LT R1/R2)
   */
  AC1009,
  /**
   * @brief Release 13 (LT95)
   */
  AC1012 = 19,
  /**
   * @brief Release 14, 14.01 (LT97/LT98)
   */
  AC1014 = 21,
  /**
   * @brief Release 2000/2000i/2002
   */
  AC1015 = 23,
  /**
   * @brief Release 2004/2005/2006
   */
  AC1018 = 25,
  /**
   * @brief Release 2007/2008/2009
   */
  AC1021 = 27,
  /**
   * @brief Release 2010/2011/2012
   */
  AC1024 = 29,
  /**
   * @brief Release 2013/2014/2015/2016/2017
   */
  AC1027 = 31,
  /**
   * @brief Release 2018/2019/2020
   */
  AC1032 = 33
};

/**
 * @enum DxfCode
 * @brief Enumeration for DXF codes.
 */
enum DxfCode
{
  Invalid     = -9999,
  XDictionary = -6,

  /**
   * @brief APP: persistent reactor chain
   */
  PReactors = -5,

  /**
   * @brief APP: conditional operator (used only with ssget)
   */
  Operator = -4,

  /**
   * @brief APP: extended data (XDATA) sentinel (fixed)
   */
  XDataStart = -3,
  HeaderId   = -2,

  /**
   * @brief APP: entity name reference (fixed)
   */
  FirstEntityId = -2,

  /**
   * @brief APP: entity name. The name changes each time a drawing is opened. It
   * is never saved (fixed)
   */
  End = -1,

  /**
   * @brief Text string indicating the entity type (fixed)
   */
  Start    = 0,
  Text     = 1,
  XRefPath = 1,

  /**
   * @brief Name (attribute tag, block name, and so on)
   */
  ShapeName             = 2,
  BlockName             = 2,
  AttributeTag          = 2,
  SymbolTableName       = 2,
  MlineStyleName        = 2,
  SymbolTableRecordName = 2,

  /**
   * @brief Other text or name values
   */
  AttributePrompt = 3,
  DimStyleName    = 3,
  LinetypeProse   = 3,
  TextFontFile    = 3,
  Description     = 3,
  DimPostString   = 3,

  /**
   * @brief Other text or name values
   */
  TextBigFontFile                  = 4,
  DimensionAlternativePrefixSuffix = 4,
  CLShapeName                      = 4,
  SymbolTableRecordComments        = 4,

  /**
   * @brief Entity handle; text string of up to 16 hexadecimal digits (fixed)
   */
  Handle                       = 5,
  DimensionBlock               = 5,
  DimBlk1                      = 6,
  LinetypeName                 = 6,
  DimBlk2                      = 7,
  TextStyleName                = 7,
  LayerName                    = 8,
  CLShapeText                  = 9,
  XCoordinate                  = 10,
  YCoordinate                  = 20,
  ZCoordinate                  = 30,
  Elevation                    = 38,
  Thickness                    = 39,
  Real                         = 40,
  ViewportHeight               = 40,
  TxtSize                      = 40,
  TxtStyleXScale               = 41,
  ViewWidth                    = 41,
  ViewportAspect               = 41,
  TxtStylePSize                = 42,
  ViewLensLength               = 42,
  ViewFrontClip                = 43,
  ViewBackClip                 = 44,
  ShapeXOffset                 = 44,
  ShapeYOffset                 = 45,
  ViewHeight                   = 45,
  ShapeScale                   = 46,
  PixelScale                   = 47,
  LinetypeScale                = 48,
  DashLength                   = 49,
  MlineOffset                  = 49,
  LinetypeElement              = 49,
  Angle                        = 50,
  ViewportSnapAngle            = 50,
  ViewportTwist                = 51,
  Visibility                   = 60,
  LayerLinetype                = 61,
  Color                        = 62,
  HasSubentities               = 66,
  ViewportVisibility           = 67,
  ViewportActive               = 68,
  ViewportNumber               = 69,
  Int16                        = 70,
  ViewMode                     = 71,
  CircleSides                  = 72,
  ViewportZoom                 = 73,
  ViewportIcon                 = 74,
  ViewportSnap                 = 75,
  ViewportGrid                 = 76,
  ViewportSnapStyle            = 77,
  ViewportSnapPair             = 78,
  RegAppFlags                  = 71,
  TxtStyleFlags                = 71,
  LinetypeAlign                = 72,
  LinetypePdc                  = 73,
  Int32                        = 90,
  Subclass                     = 100,
  EmbeddedObjectStart          = 101,
  ControlString                = 102,
  DimVarHandle                 = 105,
  UcsOrg                       = 110,
  UcsOrientationX              = 111,
  UcsOrientationY              = 112,
  XReal                        = 140,
  ViewBrightness               = 141,
  ViewContrast                 = 142,
  Int64                        = 160,
  XInt16                       = 170,
  NormalX                      = 210,
  NormalY                      = 220,
  NormalZ                      = 230,
  XXInt16                      = 270,
  Int8                         = 280,
  RenderMode                   = 281,
  Bool                         = 290,
  XTextString                  = 300,
  BinaryChunk                  = 310,
  ArbitraryHandle              = 320,
  SoftPointerId                = 330,
  HardPointerId                = 340,
  SoftOwnershipId              = 350,
  HardOwnershipId              = 360,
  LineWeight                   = 370,
  PlotStyleNameType            = 380,
  PlotStyleNameId              = 390,
  ExtendedInt16                = 400,
  LayoutName                   = 410,
  ColorRgb                     = 420,
  ColorName                    = 430,
  Alpha                        = 440,
  GradientObjType              = 450,
  GradientPatType              = 451,
  GradientTintType             = 452,
  GradientColCount             = 453,
  GradientAngle                = 460,
  GradientShift                = 461,
  GradientTintVal              = 462,
  GradientColVal               = 463,
  GradientName                 = 470,
  Comment                      = 999,
  ExtendedDataAsciiString      = 1000,
  ExtendedDataRegAppName       = 1001,
  ExtendedDataControlString    = 1002,
  ExtendedDataLayerName        = 1003,
  ExtendedDataBinaryChunk      = 1004,
  ExtendedDataHandle           = 1005,
  ExtendedDataXCoordinate      = 1010,
  ExtendedDataYCoordinate      = 1020,
  ExtendedDataZCoordinate      = 1030,
  ExtendedDataWorldXCoordinate = 1011,
  ExtendedDataWorldYCoordinate = 1021,
  ExtendedDataWorldZCoordinate = 1031,
  ExtendedDataWorldXDisp       = 1012,
  ExtendedDataWorldYDisp       = 1022,
  ExtendedDataWorldZDisp       = 1032,
  ExtendedDataWorldXDir        = 1013,
  ExtendedDataWorldYDir        = 1023,
  ExtendedDataWorldZDir        = 1033,
  ExtendedDataReal             = 1040,
  ExtendedDataDist             = 1041,
  ExtendedDataScale            = 1042,
  ExtendedDataInteger16        = 1070,
  ExtendedDataInteger32        = 1071
};

/**
 * @enum FlowDirectionType
 * @brief Enumeration for flow direction types.
 */
enum FlowDirectionType : short
{
  Horizontal = 1,
  Vertical   = 3,
  ByStyle    = 6,
};

/**
 * @enum GroupCodeValueType
 * @brief Enumeration for group code value types.
 */
enum GroupCodeValueType
{
  None,

  /**
   * @brief String
   * @remarks Code range : 0-9
   */
  String,

  /**
   * @brief Double precision 3D point value
   * @remarks Code range : 10-39
   */
  Point3D,

  /**
   * @brief Double-precision floating-point value
   * @remarks Code range : 40-59 | 110-119 | 120-129 | 130-139 | 210-239
   */
  Double,

  Byte,

  Int16,

  Int32,

  Int64,

  /**
   * @brief String representing hexadecimal (hex) handle value
   * @remarks Code range : 105
   */
  Handle,

  ObjectId,

  Bool,

  Chunk,

  /**
   * @brief Comment (string)
   * @remarks Code range : 999
   */
  Comment,

  ExtendedDataString,
  ExtendedDataChunk,
  ExtendedDataHandle,
  ExtendedDataDouble,
  ExtendedDataInt16,
  ExtendedDataInt32,
};

/**
 * @enum LineSpacingStyle
 * @brief Enumeration for line spacing styles.
 */
enum LineSpacingStyle : short
{
  AtLeast = 1,
  Exactly = 2,
};

/**
 * @enum MultiLeaderPathType
 * @brief Enumeration for multi-leader path types.
 */
enum MultiLeaderPathType : short
{
  /**
   * @brief Invisible leader
   */
  Invisible = 0,

  /**
   * @brief Draws the leader line as a set of straight line segments
   */
  StraightLineSegments = 1,

  /**
   * @brief Draws the leader line as a spline
   */
  Spline = 2
};

/**
 * @enum TextAlignmentType
 * @brief Enumeration for text alignment types.
 */
enum TextAlignmentType : short
{
  Left   = 0,
  Center = 1,
  Right  = 2,
};

/**
 * @enum TextAngleType
 * @brief Enumeration for text angle types.
 */
enum TextAngleType : short
{
  /**
   * @brief Text angle is equal to last leader line segment angle
   */
  ParllelToLastLeaderLine = 0,

  /**
   * @brief Text is horizontal
   */
  Horizontal = 1,

  /**
   * @brief Text angle is equal to last leader line segment angle,
   * but potentially rotated by 180 degrees so the right side is up
   * for readability.
   */
  Optimized = 2,
};

/**
 * @enum TextAttachmentDirectionType
 * @brief Enumeration for text attachment direction types.
 */
enum TextAttachmentDirectionType : short
{
  Horizontal = 0,
  Vertical   = 1,
};

/**
 * @enum TextAttachmentPointType
 * @brief Enumeration for text attachment point types.
 */
enum TextAttachmentPointType : short
{
  Left   = 1,
  Center = 2,
  Right  = 3,
};

/**
 * @enum TextAttachmentType
 * @brief Enumeration for text attachment types.
 * @remarks
 * Values 0-8 are used for the left/right attachment points (attachment
 * direction is horizontal),
 * values 9-10 are used for the top/bottom attachment points (attachment
 * direction is vertical).
 */
enum TextAttachmentType : short
{
  /**
   * @brief Top of top text line.
   */
  TopOfTopLine = 0,

  /**
   * @brief Middle of top text line.
   */
  MiddleOfTopLine = 1,

  /**
   * @brief Middle of text.
   */
  MiddleOfText = 2,

  /**
   * @brief Middle of bottom text line.
   */
  MiddleOfBottomLine = 3,

  /**
   * @brief Bottom of bottom text line.
   */
  BottomOfBottomLine = 4,

  /**
   * @brief Bottom text line.
   */
  BottomLine = 5,

  /**
   * @brief Bottom of top text line. Underline bottom line.
   */
  BottomOfTopLineUnderlineBottomLine = 6,

  /**
   * @brief Bottom of top text line. Underline top line.
   */
  BottomOfTopLineUnderlineTopLine = 7,

  /**
   * @brief Bottom of top text line. Underline all content.
   */
  BottomofTopLineUnderlineAll = 8,

  /**
   * @brief Center of text (y-coordinate only).
   */
  CenterOfText = 9,

  /**
   * @brief Center of text (y-coordinate only), and overline top/underline
   * bottom content.
   */
  CenterOfTextOverline = 10,
};

} // namespace DWG

#endif /* __DWG_COMMON_H__ */

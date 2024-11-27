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

#ifndef __DWG_TYPE_H__
#define __DWG_TYPE_H__

namespace DWG
{
namespace Type
{

/**
 * @enum DwgReferenceType
 * @brief Enumeration for DWG reference types.
 */
enum DwgReferenceType
{
  Undefined = 0,

  /**
   * @brief Soft ownership reference: the owner does not need the owned object.
   * The owned object cannot exist by itself.
   */
  SoftOwnership = 2,

  /**
   * @brief Hard ownership reference: the owner needs the owned object. The
   * owned object cannot exist by itself.
   */
  HardOwnership = 3,

  /**
   * @brief Soft pointer reference: the referencing object does not need the
   * referenced object and vice versa.
   */
  SoftPointer = 4,

  /**
   * @brief Hard pointer reference: the referencing object needs the referenced
   * object, but both are owned by another object.
   */
  HardPointer = 5,
};

/**
 * @enum LineweightType
 * @brief Enumeration for lineweight types.
 */
enum LineweightType : short
{
  ByDIPs = -4,

  /**
   * @brief Default line weight.
   */
  Default = -3,

  /**
   * @brief Line weight defined by block.
   */
  ByBlock = -2,

  /**
   * @brief Line weight defined by layer.
   */
  ByLayer = -1,

  /**
   * @brief Line weight value 0.00 mm (hairline).
   */
  W0 = 0,

  /**
   * @brief Line weight value 0.05 mm.
   */
  W5 = 5,

  /**
   * @brief Line weight value 0.09 mm.
   */
  W9 = 9,
  /**
   * @brief Line weight value 0.13 mm.
   */
  W13 = 13,
  /**
   * @brief Line weight value 0.15 mm.
   */
  W15 = 15,
  /**
   * @brief Line weight value 0.18 mm.
   */
  W18 = 18,
  /**
   * @brief Line weight value 0.20 mm.
   */
  W20 = 20,
  /**
   * @brief Line weight value 0.25 mm.
   */
  W25 = 25,
  /**
   * @brief Line weight value 0.30 mm.
   */
  W30 = 30,
  /**
   * @brief Line weight value 0.35 mm.
   */
  W35 = 35,
  /**
   * @brief Line weight value 0.40 mm.
   */
  W40 = 40,
  /**
   * @brief Line weight value 0.50 mm.
   */
  W50 = 50,
  /**
   * @brief Line weight value 0.53 mm.
   */
  W53 = 53,
  /**
   * @brief Line weight value 0.60 mm.
   */
  W60 = 60,
  /**
   * @brief Line weight value 0.70 mm.
   */
  W70 = 70,
  /**
   * @brief Line weight value 0.80 mm.
   */
  W80 = 80,
  /**
   * @brief Line weight value 0.90 mm.
   */
  W90 = 90,
  /**
   * @brief Line weight value 1.00 mm.
   */
  W100 = 100,
  /**
   * @brief Line weight value 1.06 mm.
   */
  W106 = 106,
  /**
   * @brief Line weight value 1.20 mm.
   */
  W120 = 120,
  /**
   * @brief Line weight value 1.40 mm.
   */
  W140 = 140,
  /**
   * @brief Line weight value 1.58 mm.
   */
  W158 = 158,
  /**
   * @brief Line weight value 2.00 mm.
   */
  W200 = 200,
  /**
   * @brief Line weight value 2.11 mm.
   */
  W211 = 211
};

/**
 * @enum ObjectType
 * @brief Enumeration for object types.
 */
enum ObjectType : short
{
  UNLISTED  = -999,
  INVALID   = -1,
  UNDEFINED = 0,

  TEXT    = 1,
  ATTRIB  = 2,
  ATTDEF  = 3,
  BLOCK   = 4,
  ENDBLK  = 5,
  SEQEND  = 6,
  INSERT  = 7,
  MINSERT = 8,

  UNKNOW_9 = 9,

  VERTEX_2D          = 0x0A,
  VERTEX_3D          = 0x0B,
  VERTEX_MESH        = 0x0C,
  VERTEX_PFACE       = 0x0D,
  VERTEX_PFACE_FACE  = 0x0E,
  POLYLINE_2D        = 0x0F,
  POLYLINE_3D        = 0x10,
  ARC                = 0x11,
  CIRCLE             = 0x12,
  LINE               = 0x13,
  DIMENSION_ORDINATE = 0x14,
  DIMENSION_LINEAR   = 0x15,
  DIMENSION_ALIGNED  = 0x16,
  DIMENSION_ANG_3_Pt = 0x17,
  DIMENSION_ANG_2_Ln = 0x18,
  DIMENSION_RADIUS   = 0x19,
  DIMENSION_DIAMETER = 0x1A,
  POINT              = 0x1B,
  FACE3D             = 0x1C,
  POLYLINE_PFACE     = 0x1D,
  POLYLINE_MESH      = 0x1E,
  SOLID              = 0x1F,
  TRACE              = 0x20,
  SHAPE              = 0x21,
  VIEWPORT           = 0x22,
  ELLIPSE            = 0x23,
  SPLINE             = 0x24,
  REGION             = 0x25,
  SOLID3D            = 0x26,
  BODY               = 0x27,
  RAY                = 0x28,
  XLINE              = 0x29,
  DICTIONARY         = 0x2A,
  OLEFRAME           = 0x2B,
  MTEXT              = 0x2C,
  LEADER             = 0x2D,
  TOLERANCE          = 0x2E,
  MLINE              = 0x2F,
  BLOCK_CONTROL_OBJ  = 0x30,
  BLOCK_HEADER       = 0x31,
  LAYER_CONTROL_OBJ  = 0x32,
  LAYER              = 0x33,
  STYLE_CONTROL_OBJ  = 0x34,
  STYLE              = 0x35,

  UNKNOW_36 = 0x36,
  UNKNOW_37 = 0x37,

  LTYPE_CONTROL_OBJ = 0x38,
  LTYPE             = 0x39,

  UNKNOW_3A = 0x3A,
  UNKNOW_3B = 0x3B,

  VIEW_CONTROL_OBJ     = 0x3C,
  VIEW                 = 0x3D,
  UCS_CONTROL_OBJ      = 0x3E,
  UCS                  = 0x3F,
  VPORT_CONTROL_OBJ    = 0x40,
  VPORT                = 0x41,
  APPID_CONTROL_OBJ    = 0x42,
  APPID                = 0x43,
  DIMSTYLE_CONTROL_OBJ = 0x44,
  DIMSTYLE             = 0x45,
  VP_ENT_HDR_CTRL_OBJ  = 0x46,
  VP_ENT_HDR           = 0x47,
  GROUP                = 0x48,
  MLINESTYLE           = 0x49,
  OLE2FRAME            = 0x4A,
  DUMMY                = 0x4B,
  LONG_TRANSACTION     = 0x4C,
  LWPOLYLINE           = 0x4D,
  HATCH                = 0x4E,
  XRECORD              = 0x4F,
  ACDBPLACEHOLDER      = 0x50,
  VBA_PROJECT          = 0x51,
  LAYOUT               = 0x52,
  ACAD_PROXY_ENTITY    = 0x1f2,
  ACAD_PROXY_OBJECT    = 0x1f3,
};

/**
 * @enum OrthographicType
 * @brief Enumeration for orthographic types.
 */
enum OrthographicType
{
  /**
   * @brief None
   */
  None,
  /**
   * @brief Top
   */
  Top,
  /**
   * @brief Bottom
   */
  Bottom,
  /**
   * @brief Front
   */
  Front,
  /**
   * @brief Back
   */
  Back,
  /**
   * @brief Left
   */
  Left,
  /**
   * @brief Right
   */
  Right,
};

/**
 * @enum RenderMode
 * @brief Enumeration for render modes.
 */
enum RenderMode
{
  /**
   * @brief Classic 2D
   */
  Optimized2D,
  /**
   * @brief Wire frame
   */
  Wireframe,
  /**
   * @brief Hidden line
   */
  HiddenLine,
  /**
   * @brief Flat shaded
   */
  FlatShaded,
  /**
   * @brief Gouraud shaded
   */
  GouraudShaded,
  /**
   * @brief Flat shaded with wire frame
   */
  FlatShadedWithWireframe,
  /**
   * @brief Gouraud shaded with wireframe
   */
  GouraudShadedWithWireframe,
};

namespace Units
{
/**
 * @enum AngularDirection
 * @brief Enumeration for angular directions.
 */
enum AngularDirection : short
{
  /**
   * @brief Counterclockwise angles
   */
  CounterClockWise = 0,
  /**
   * @brief Clockwise angles
   */
  ClockWise = 1,
};

/**
 * @enum AngularUnitFormat
 * @brief Enumeration for angular unit formats.
 */
enum AngularUnitFormat : short
{
  /**
   * @brief Decimal degrees
   */
  DecimalDegrees,

  /**
   * @brief Degrees/minutes/seconds
   */
  DegreesMinutesSeconds,

  /**
   * @brief Gradians
   */
  Gradians,

  /**
   * @brief Radians
   */
  Radians,

  /**
   * @brief Surveyors units
   */
  SurveyorsUnits,
};

/**
 * @enum UnitsType
 * @brief Enumeration for units types.
 */
enum UnitsType : short
{
  /**
   * @brief Unitless.
   */
  Unitless = 0,
  /**
   * @brief Inches
   */
  Inches = 1,
  /**
   * @brief Feet
   */
  Feet = 2,
  /**
   * @brief Miles
   */
  Miles = 3,
  /**
   * @brief Millimeters
   */
  Millimeters = 4,
  /**
   * @brief Centimeters
   */
  Centimeters = 5,
  /**
   * @brief Meters
   */
  Meters = 6,
  /**
   * @brief Kilometers
   */
  Kilometers = 7,
  /**
   * @brief Microinches
   */
  Microinches = 8,
  /**
   * @brief Mils
   */
  Mils = 9,
  /**
   * @brief Yards
   */
  Yards = 10,
  /**
   * @brief Angstroms
   */
  Angstroms = 11,
  /**
   * @brief Nanometers
   */
  Nanometers = 12,
  /**
   * @brief Microns
   */
  Microns = 13,
  /**
   * @brief Decimeters
   */
  Decimeters = 14,
  /**
   * @brief Decameters
   */
  Decameters = 15,
  /**
   * @brief Hectometers
   */
  Hectometers = 16,
  /**
   * @brief Gigameters
   */
  Gigameters = 17,
  /**
   * @brief Astronomical units
   */
  AstronomicalUnits = 18,
  /**
   * @brief Light years
   */
  LightYears = 19,
  /**
   * @brief Parsecs
   */
  Parsecs = 20,
  /**
   * @brief US Survey Feet
   */
  USSurveyFeet = 21,
  /**
   * @brief US Survey Inches
   */
  USSurveyInches = 22,
  /**
   * @brief US Survey Yards
   */
  USSurveyYards = 23,
  /**
   * @brief US Survey Miles
   */
  USSurveyMiles = 24
};

} // namespace Units
} // namespace Type
} // namespace DWG

#endif /* __DWG_TYPE_H__ */

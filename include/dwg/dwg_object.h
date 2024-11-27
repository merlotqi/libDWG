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

#ifndef __DWG_OBJECT_H__
#define __DWG_OBJECT_H__

namespace DWG
{
namespace Object
{

/**
 * @enum PlotType
 * @brief Defines the portion of paper space to output to the media
 */
enum PlotType
{
  /**
   * @brief Last screen display
   */
  LastScreenDisplay = 0,

  /**
   * @brief Drawing extents
   */
  DrawingExtents = 1,

  /**
   * @brief Drawing limits
   */
  DrawingLimits = 2,

  /**
   * @brief View specified by the plot view name
   */
  View = 3,

  /**
   * @brief Window specified by the upper-right and bottom-left window corners
   */
  Window = 4,

  /**
   * @brief Layout information
   */
  LayoutInformation = 5
};

/**
 * @enum ScaledType
 * @brief Enumeration for scaled types.
 */
enum ScaledType
{
  /**
   * @brief Scaled to Fit
   */
  ScaledToFit = 0,

  /**
   * @brief 1/128"=1'
   */
  _1 = 1,

  /**
   * @brief 1/64"=1'
   */
  _2 = 2,

  /**
   * @brief 1/32"=1'
   */
  _3 = 3,

  /**
   * @brief 1/16"=1'
   */
  _4 = 4,

  /**
   * @brief 3/32"=1'
   */
  _5 = 5,

  /**
   * @brief 1/8"=1'
   */
  _6 = 6,

  /**
   * @brief 3/16"=1'
   */
  _7 = 7,

  /**
   * @brief 1/4"=1'
   */
  _8 = 8,

  /**
   * @brief 3/8"=1'
   */
  _9 = 9,

  /**
   * @brief 1/2"=1'
   */
  _10 = 10,

  /**
   * @brief 3/4"=1'
   */
  _11 = 11,

  /**
   * @brief 1"=1'
   */
  _12 = 12,

  /**
   * @brief 3"=1'
   */
  _13 = 13,

  /**
   * @brief 6"=1'
   */
  _14 = 14,

  /**
   * @brief 1'=1'
   */
  _15 = 15,

  /**
   * @brief 1:1
   */
  _16 = 16,

  /**
   * @brief 1:2
   */
  _17 = 17,

  /**
   * @brief 1:4
   */
  _18 = 18,

  /**
   * @brief 1:8
   */
  _19 = 19,

  /**
   * @brief 1:10
   */
  _20 = 20,

  /**
   * @brief 1:16
   */
  _21 = 21,

  /**
   * @brief 1:20
   */
  _22 = 22,

  /**
   * @brief 1:30
   */
  _23 = 23,

  /**
   * @brief 1:40
   */
  _24 = 24,

  /**
   * @brief 1:50
   */
  _25 = 25,

  /**
   * @brief 1:100
   */
  _26 = 26,

  /**
   * @brief 2:1
   */
  _27 = 27,

  /**
   * @brief 4:1
   */
  _28 = 28,

  /**
   * @brief 8:1
   */
  _29 = 29,

  /**
   * @brief 10:1
   */
  _30 = 30,

  /**
   * @brief 100:1
   */
  _31 = 31,

  /**
   * @brief 1000:1
   */
  _32 = 32,
};

} // namespace Object
} // namespace DWG

#endif /* __DWG_OBJECT_H__ */

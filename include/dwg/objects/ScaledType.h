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

namespace dwg {

enum class ScaledType
{
    ScaledToFit = 0,// Scaled to Fit
    _1 = 1,         //1/128"=1';
    _2 = 2,         //1/64"=1';
    _3 = 3,         //1/32"=1'
    _4 = 4,         //1/16"=1';
    _5 = 5,         //3/32"=1';
    _6 = 6,         //1/8"=1'
    _7 = 7,         //3/16"=1';
    _8 = 8,         //1/4"=1';
    _9 = 9,         //3/8"=1'
    _10 = 10,       // 1/2"=1';
    _11 = 11,       // 3/4"=1';
    _12 = 12,       // 1"=1'
    _13 = 13,       // 3"=1';
    _14 = 14,       // 6"=1';
    _15 = 15,       // 1'=1'
    _16 = 16,       // 1:1 ;
    _17 = 17,       // 1:2;
    _18 = 18,       // 1:4;
    _19 = 19,       // 1:8;
    _20 = 20,       // 1:10;
    _21 = 21,       // 1:16
    _22 = 22,       // 1:20;
    _23 = 23,       // 1:30;
    _24 = 24,       // 1:40;
    _25 = 25,       // 1:50;
    _26 = 26,       // 1:100
    _27 = 27,       // 2:1;
    _28 = 28,       // 4:1;
    _29 = 29,       // 8:1;
    _30 = 30,       // 10:1;
    _31 = 31,       // 100:1;
    _32 = 32,       // 1000:1
};

}// namespace dwg
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

#ifndef DWG_UTIL_COORDINATE_H
#define DWG_UTIL_COORDINATE_H

namespace dwg {

struct XYZ {
    double X;
    double Y;
    double Z;

    XYZ(double x, double y, double z) : X(x), Y(y), Z(z) {}
};

struct XY {
    double X;
    double Y;

    XY(double x, double y) : X(x), Y(y) {}
};

} // namespace dwg

#endif /* __DWG_UTIL_COORDINATE_H__ */
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

#include <base.h>

namespace dwg {

enum ProxyFlag : unsigned short
{
    /// None.
    None = 0,
    /// Erase allowed.
    EraseAllowed = 1,
    /// Transform allowed.
    TransformAllowed = 2,
    /// Clor change allowed.
    ColorChangeAllowed = 4,
    /// Layer change allowed.
    LayerChangeAllowed = 8,
    /// Line type change allowed.
    LinetypeChangeAllowed = 16,
    /// Line type scale change allowed.
    LinetypeScaleChangeAllowed = 32,
    /// Visibility change allowed.
    VisibilityChangeAllowed = 64,
    /// Cloning allowed.
    CloningAllowed = 128,
    /// Line weight change allowed.
    LineweightChangeAllowed = 256,
    /// Plot Style Name change allowed.
    PlotStyleNameChangeAllowed = 512,
    /// All operations except cloning allowed.
    AllOperationsExceptCloningAllowed = 895,
    /// All operations allowed.
    AllOperationsAllowed = 1023,
    /// Disables proxy warning dialog.
    DisablesProxyWarningDialog = 1024,
    /// R13 format proxy.
    R13FormatProxy = 32768,
};
DECLARE_FLAGS(ProxyFlags, ProxyFlag)

}// namespace dwg

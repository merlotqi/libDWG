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

#include <dwg/header/CadHeader.h>
#include <dwg/io/dxf/DxfWriterConfiguration.h>
#include <vector>

namespace dwg {

DxfWriterConfiguration::DxfWriterConfiguration()
{
    static std::vector<std::string> Variables = {
            "$ACADVER",  "$DWGCODEPAGE", "$LASTSAVEDBY", "$HANDSEED",  "$ANGBASE",    "$ANGDIR",    "$ATTMODE",
            "$AUNITS",   "$AUPREC",      "$CECOLOR",     "$CELTSCALE", "$CELTYPE",    "$CELWEIGHT", "$CLAYER",
            "$CMLJUST",  "$CMLSCALE",    "$CMLSTYLE",    "$DIMSTYLE",  "$TEXTSIZE",   "$TEXTSTYLE", "$LUNITS",
            "$LUPREC",   "$MIRRTEXT",    "$EXTNAMES",    "$INSBASE",   "$INSUNITS",   "$LTSCALE",   "$LWDISPLAY",
            "$PDMODE",   "$PDSIZE",      "$PLINEGEN",    "$PSLTSCALE", "$SPLINESEGS", "$SURFU",     "$SURFV",
            "$TDCREATE", "$TDUCREATE",   "$TDUPDATE",    "$TDUUPDATE", "$TDINDWG",
    };
    _headerVariables.insert(Variables.begin(), Variables.end());
}

DxfWriterConfiguration::~DxfWriterConfiguration() {}

bool DxfWriterConfiguration::writeAllHeaderVariables() const { return _writeAllHeaderVariables; }

void DxfWriterConfiguration::setWriteAllHeaderVariables(bool value) { _writeAllHeaderVariables = value; }

void DxfWriterConfiguration::addHeaderVariable(const std::string &name) {}

bool DxfWriterConfiguration::removeHeaderVariable(const std::string &name) {}

}// namespace dwg
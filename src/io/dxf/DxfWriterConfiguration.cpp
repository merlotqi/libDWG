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
#include <dwg/utils/StringHelp.h>
#include <vector>
#include <stdexcept>
#include <fmt/format.h>
#include <dwg/CadSystemVariables_p.h>

namespace dwg {

static std::vector<std::string> FixedVariables = {
        "$ACADVER",  "$DWGCODEPAGE", "$LASTSAVEDBY", "$HANDSEED",  "$ANGBASE",    "$ANGDIR",    "$ATTMODE",
        "$AUNITS",   "$AUPREC",      "$CECOLOR",     "$CELTSCALE", "$CELTYPE",    "$CELWEIGHT", "$CLAYER",
        "$CMLJUST",  "$CMLSCALE",    "$CMLSTYLE",    "$DIMSTYLE",  "$TEXTSIZE",   "$TEXTSTYLE", "$LUNITS",
        "$LUPREC",   "$MIRRTEXT",    "$EXTNAMES",    "$INSBASE",   "$INSUNITS",   "$LTSCALE",   "$LWDISPLAY",
        "$PDMODE",   "$PDSIZE",      "$PLINEGEN",    "$PSLTSCALE", "$SPLINESEGS", "$SURFU",     "$SURFV",
        "$TDCREATE", "$TDUCREATE",   "$TDUPDATE",    "$TDUUPDATE", "$TDINDWG",
};

DxfWriterConfiguration::DxfWriterConfiguration() : _writeAllHeaderVariables(false), _writeOptionalValues(true)
{
    _headerVariables.insert(FixedVariables.begin(), FixedVariables.end());
}

DxfWriterConfiguration::~DxfWriterConfiguration() {}

bool DxfWriterConfiguration::writeAllHeaderVariables() const
{
    return _writeAllHeaderVariables;
}

void DxfWriterConfiguration::setWriteAllHeaderVariables(bool value)
{
    _writeAllHeaderVariables = value;
}

bool DxfWriterConfiguration::writeOptionalValues() const
{
    return _writeOptionalValues;
}

void DxfWriterConfiguration::setWriteOptionalValues(bool value)
{
    _writeOptionalValues = value;
}

void DxfWriterConfiguration::addHeaderVariable(const std::string &name) 
{
    auto _map = CadSystemVariables::headerMap();
    if (_map.find(name) == _map.end())
    {
        throw std::runtime_error(fmt::format("The variable {} is not a valid header variable", name));
    }
    _headerVariables.insert(name);
}

bool DxfWriterConfiguration::removeHeaderVariable(const std::string &name)
{
    auto filter = [name](const std::string &str) { return StringHelp::icompare(str, name) == 0; };
    auto it = std::find_if(FixedVariables.begin(), FixedVariables.end(), filter);
    if (it != FixedVariables.end())
    {
        throw std::runtime_error(fmt::format("The variable {} cannot be removed from the set", name));
    }
    auto it2 = _headerVariables.find(name);
    if (it2 != _headerVariables.end())
    {
        _headerVariables.erase(it2);
        return true;
    }
    return false;
}

std::set<std::string> DxfWriterConfiguration::headerVariables() const
{
    return _headerVariables;
}

}// namespace dwg
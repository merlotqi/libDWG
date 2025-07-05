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

#include <dwg/attributes/CadSystemVariableAttribute_p.h>

namespace dwg {
CadSystemVariableAttribute::CadSystemVariableAttribute(const std::string &variable, bool isName,
                                                       const std::vector<int> &codes)
    : _isName(isName), _name(variable)
{
    for (const auto &code: codes)
    {
        _valueCodes.push_back(static_cast<DxfCode>(code));
    }
}

CadSystemVariableAttribute::CadSystemVariableAttribute(const std::string &variable, const std::vector<int> &codes)
    : _name(variable), _referenceType(DxfReferenceType::None)
{
    for (const auto &code: codes)
    {
        _valueCodes.push_back(static_cast<DxfCode>(code));
    }
}

CadSystemVariableAttribute::CadSystemVariableAttribute(DxfReferenceTypes rf, const std::string &variable,
                                                       const std::vector<int> &codes)
    : CadSystemVariableAttribute(variable, codes)
{
    _referenceType = rf;
}

std::vector<DxfCode> CadSystemVariableAttribute::valueCodes() const
{
    return _valueCodes;
}

DxfReferenceTypes CadSystemVariableAttribute::referenceType() const
{
    return _referenceType;
}

std::string CadSystemVariableAttribute::name() const
{
    return _name;
}

bool CadSystemVariableAttribute::isName() const
{
    return _isName;
}

}// namespace dwg
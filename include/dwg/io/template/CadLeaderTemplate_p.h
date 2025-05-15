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

#include <dwg/io/template/CadEntityTemplate_p.h>

namespace dwg {

class Leader;
class CadLeaderTemplate : public CadEntityTemplate
{
public:
    CadLeaderTemplate();
    CadLeaderTemplate(Leader *leader);
    void build(CadDocumentBuilder *builder) override;

    double dimasz() const;
    void setDimasz(double);

    unsigned long long DIMSTYLEHandle() const;
    void setDIMSTYLEHandle(unsigned long long);

    std::string DIMSTYLEName() const;
    void setDIMSTYLEName(const std::string &);

    unsigned long long annotationHandle() const;
    void setAnnotationHandle(unsigned long long);

private:
    double _dimasz;
    unsigned long long _DIMSTYLEHandle;
    std::string _DIMSTYLEName;
    unsigned long long _annotationHandle;
};

}// namespace dwg
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

#include <dwg/io/template/CadTemplate_p.h>
#include <dwg/tables/DimensionStyle.h>

namespace dwg {

class CadDimensionStyleTemplate : public CadTemplateT<DimensionStyle *>
{
public:
    CadDimensionStyleTemplate();
    CadDimensionStyleTemplate(DimensionStyle *);
    void build(CadDocumentBuilder *builder) override;

    std::string textStyle_Name() const;
    void setTextStyle_Name(const std::string &);

    std::string DIMBL_Name() const;
    void setDIMBL_Name(const std::string &);

    std::string DIMBLK1_Name() const;
    void setDIMBLK1_Name(const std::string &);

    std::string DIMBLK2_Name() const;
    void setDIMBLK2_Name(const std::string &);

    std::optional<unsigned long long> TextStyleHandle() const;
    void setTextStyleHandle(unsigned long long);

    std::optional<unsigned long long> DIMLDRBLK() const;
    void setDIMLDRBLK(unsigned long long);

    std::optional<unsigned long long> DIMBLK() const;
    void setDIMBLK(unsigned long long);

    std::optional<unsigned long long> DIMBLK1() const;
    void setDIMBLK1(unsigned long long);

    std::optional<unsigned long long> DIMBLK2() const;
    void setDIMBLK2(unsigned long long);

    unsigned long long Dimltype() const;
    void setDimltype(unsigned long long);

    unsigned long long Dimltex1() const;
    void setDimltex1(unsigned long long);

    unsigned long long Dimltex2() const;
    void setDimltex2(unsigned long long);

private:
    std::string _textStyle_Name;
    std::string _DIMBL_Name;
    std::string _DIMBLK1_Name;
    std::string _DIMBLK2_Name;
    std::optional<unsigned long long> _TextStyleHandle;
    std::optional<unsigned long long> _DIMLDRBLK;
    std::optional<unsigned long long> _DIMBLK;
    std::optional<unsigned long long> _DIMBLK1;
    std::optional<unsigned long long> _DIMBLK2;
    unsigned long long _Dimltype;
    unsigned long long _Dimltex1;
    unsigned long long _Dimltex2;
};

}// namespace dwg
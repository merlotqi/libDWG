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

namespace dwg {

class SortEntitiesTable;
class CadSortensTableTemplate : public CadTemplateT<SortEntitiesTable *>
{
public:
    CadSortensTableTemplate();
    CadSortensTableTemplate(SortEntitiesTable *);
    ~CadSortensTableTemplate();

    std::optional<unsigned long long> blockOwnerHandle() const;
    void setBlockOwnerHandle(const unsigned long long &);

    typedef std::optional<unsigned long long> optional_handle;
    typedef std::pair<optional_handle, optional_handle> optional_handle_pair;
    typedef std::vector<optional_handle_pair> optional_handle_vector;

    const optional_handle_vector &values() const;
    optional_handle_vector &values();

    void build(CadDocumentBuilder *builder) override;

private:
    std::optional<unsigned long long> _blockOwnerHandle;
    optional_handle_vector _values;
};

}// namespace dwg
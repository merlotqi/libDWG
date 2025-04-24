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

#include <dwg/io/template/ICadTemplate_p.h>
#include <optional>
#include <map>
#include <vector>
#include <type_traits>

namespace dwg {

class ExtendedDataRecord;
class Entity;

template<typename T>
class CadTemplate : public ICadObjectTemplate<T>
{
public:
    CadTemplate(T obj);
    virtual ~CadTemplate();

    void setCadObject(T v);

    std::optional<unsigned long long> ownerHandle() const;
    void setOwnerHandle(unsigned long long);

    std::optional<unsigned long long> xdictHandle() const;
    void setXDictHandle(unsigned long long);

    std::vector<unsigned long long> reactorsHandles() const;
    std::vector<unsigned long long> &reactorsHandles();
    void setReactorsHandles(const std::vector<unsigned long long> &);

    std::map<unsigned long long, std::vector<ExtendedDataRecord *>> edataTemplate() const;
    std::map<unsigned long long, std::vector<ExtendedDataRecord *>> &edataTemplate();

    std::map<unsigned long long, std::vector<ExtendedDataRecord *>> edataTemplateByAppName() const;
    std::map<unsigned long long, std::vector<ExtendedDataRecord *>> &edataTemplateByAppName();

    virtual void build(CadDocumentBuilder *builder) override;

    template<typename U>
    std::vector<U> getEntitiesCollection(CadDocumentBuilder *builder, unsigned long long firstHandle, unsigned long long endHandle)
    {
        return std::vector<U>();   
    }

    template<typename U>
    bool getTableReference(CadDocumentBuilder *build, std::optional<unsigned long long> handle, const std::string &name, T reference)
    {
        return false;
    }
    
};

}// namespace dwg
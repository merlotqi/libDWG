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

#include <dwg/io/CadDocumentBuilder_p.h>
#include <dwg/io/dwg/DwgReaderConfiguration.h>
#include <dwg/io/dwg/DwgHeaderHandlesCollection_p.h>

namespace dwg {

class Entity;
class CadBlockRecordTemplate;

class DwgDocumentBuilder : public CadDocumentBuilder
{
public:
    DwgDocumentBuilder(ACadVersion version, CadDocument *document, const DwgReaderConfiguration &configuration);
    ~DwgDocumentBuilder();

    DwgReaderConfiguration configuration() const; 

    DwgHeaderHandlesCollection headerHandles() const;
    void setHeaderHandles(const DwgHeaderHandlesCollection &headerHandles);

    std::vector<CadBlockRecordTemplate *> blockRecordTemplates() const;
    std::vector<CadBlockRecordTemplate *> &blockRecordTemplates();
    void setBlockRecordTemplates(const std::vector<CadBlockRecordTemplate *> &);

    std::vector<Entity *> paperSpaceEntities() const;
    std::vector<Entity *> &paperSpaceEntities();

    std::vector<Entity *> modelSpaceEntities() const;
    std::vector<Entity *> &modelSpaceEntities();

    bool keepUnknownEntities() const override;
    bool keepUnknownNonGraphicalObjects() const override;

    void buildDocument() override;

private:
    DwgReaderConfiguration _configuration;
    DwgHeaderHandlesCollection _headerHandles;

    std::vector<CadBlockRecordTemplate *> _blockRecordTemplates;
    std::vector<Entity *> _paperSpaceEntities;
    std::vector<Entity *> _modelSpaceEntities;
};

}// namespace dwg
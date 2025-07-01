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

#include <dwg/io/CadReaderBase.h>
#include <dwg/io/dxf/DxfReaderConfiguration.h>
#include <vector>
#include <dwg/ACadVersion.h>

namespace dwg {

class IDxfStreamReader;
class Entity;
class DxfDocumentBuilder;
class DxfClass;
class DxfClassCollection;

class LIBDWG_API DxfReader : public CadReaderBase<DxfReaderConfiguration>
{
public:
    DxfReader(const std::string &filename);
    DxfReader(std::fstream *stream);
    bool isBinary() const;
    CadDocument *read() override;
    CadHeader *readHeader() override;
    CadDocument *readTables();
    std::vector<Entity *> readEntities();

    static bool IsBinary(const std::string &filename);
    static bool IsBinary(std::iostream *stream, bool resetPos = false);

private:
    DxfClassCollection *readClasses();
    DxfClass *readClass();
    void readBlocks();
    void readEntitiesPrivate();
    void readObjects();
    void readThumbnailImage();
    IDxfStreamReader *getReader();
    IDxfStreamReader *goToSection(const std::string &sectionName);
    IDxfStreamReader *createReader(bool isBinary, bool isAC1009Format);
    void triggerNotification(const std::string &msg, Notification);

private:
    ACadVersion _version;
    DxfDocumentBuilder *_builder;
    IDxfStreamReader *_reader;
};

}// namespace dwg
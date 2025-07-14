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

#include <dwg/CadDocument.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/classes/DxfClass.h>
#include <dwg/classes/DxfClassCollection.h>
#include <dwg/io/dxf/writers/DxfClassesSectionWriter_p.h>
#include <dwg/io/dxf/writers/IDxfStreamWriter_p.h>

namespace dwg {

DxfClassesSectionWriter::DxfClassesSectionWriter(IDxfStreamWriter *writer, CadDocument *document,
                                                 CadObjectHolder *objectHolder,
                                                 const DxfWriterConfiguration &configuration)
    : DxfSectionWriterBase(writer, document, objectHolder, configuration)
{
}

DxfClassesSectionWriter::~DxfClassesSectionWriter() {}

std::string DxfClassesSectionWriter::sectionName() const
{
    return DxfFileToken::ClassesSection;
}

void DxfClassesSectionWriter::writeSection() 
{
    auto classes = _document->classes();

    for (auto it = classes->begin(); it != classes->end(); ++it)
    {
        auto c = it->second;
        _writer->write(0, DxfFileToken::ClassEntry);
        _writer->write(1, c->dxfName());
        _writer->write(2, c->cppClassName());
        _writer->write(3, c->applicationName());
        _writer->write(90, (int) c->proxyFlags());
        _writer->write(91, c->instanceCount());
        _writer->write(280, c->wasZombie());
        _writer->write(281, c->isAnEntity());
    }
}

}// namespace dwg
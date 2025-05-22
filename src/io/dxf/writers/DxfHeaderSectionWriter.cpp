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

#include <dwg/io/dxf/writers/DxfHeaderSectionWriter_p.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/CadSystemVariables_p.h>
#include <algorithm>

namespace dwg {

DxfHeaderSectionWriter::DxfHeaderSectionWriter(IDxfStreamWriter *writer, CadDocument *document,
                                               CadObjectHolder *objectHolder,
                                               const DxfWriterConfiguration &configuration)
    : DxfSectionWriterBase(writer, document, objectHolder, configuration)
{
}

DxfHeaderSectionWriter::~DxfHeaderSectionWriter() {}

std::string DxfHeaderSectionWriter::sectionName() const
{
    return DxfFileToken::HeaderSection;
}

void DxfHeaderSectionWriter::writeSection() 
{
    std::map<std::string, CadSystemVariableAttribute> mapAttr = CadSystemVariables::headerMap();
    for(auto it = mapAttr.begin(); it != mapAttr.end(); ++it)
    {
        // bool contains = false;
        // auto itFind = std::find_if(_configuration.headerVariables().begin(), _configuration.headerVariables().end(), it->first);
        // if(itFind != _configuration.headerVariables().end())
        //     contains = true;
        // if(!_configuration.writeAllHeaderVariables() && !contains)
        //     continue;

        // if(it->second.referenceType() & DxfReferenceType::Ignored)
        //     continue;

        // if(CadSystemVariables::value(it->first, header).isEmpty())
        //     continue;

        // _writer->write(DxfCode::CLShapeText, it->first);

        // if(it->first == "$HANDSEED") //Not very elegant but by now...
        // {
        //     _writer->write(DxfCode::Handle, _document->header()->handleSeed());
        //     continue;
        // }

        // if(it->first == "$CECOLOR")
        // {
        //     _writer->write(62, _document->header()->currentEntityColor().approxIndex());
        //     continue;
        // }

        // for(auto &&csv : it->second.dxfCodes())
        // {
        //     DwgVariant value = CadSystemVariables::value(it->first, csv, _document->header());
        //     if(value.isEmpty())
        //         continue;

        //     _writer->write((DxfCode)csv, value);
        // }
    }
}

}// namespace dwg
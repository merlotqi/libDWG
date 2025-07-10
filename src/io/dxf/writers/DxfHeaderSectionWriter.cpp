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

#include <algorithm>
#include <dwg/CadDocument.h>
#include <dwg/CadSystemVariables_p.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/attributes/CadSystemVariableAttribute_p.h>
#include <dwg/header/CadHeader.h>
#include <dwg/io/dxf/writers/DxfHeaderSectionWriter_p.h>
#include <dwg/io/dxf/writers/IDxfStreamWriter_p.h>

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
    auto && configue_variables = _configuration.headerVariables();
    for (auto &&[key, value]: mapAttr)
    {
        bool contains = false;
        auto itFind = configue_variables.find(key);
        if (itFind != configue_variables.end())
            contains = true;
        if (!_configuration.writeAllHeaderVariables() && !contains)
            continue;

        if (value.referenceType() & DxfReferenceType::Ignored)
            continue;

        if (CadSystemVariables::value(key, _document->header()).isEmpty())
            continue;

        _writer->write(DxfCode::CLShapeText, key);

        if (key == "$HANDSEED")//Not very elegant but by now...
        {
            _writer->write(DxfCode::Handle, _document->header()->handleSeed());
            continue;
        }

        if (key == "$CECOLOR")
        {
            _writer->write(62, _document->header()->currentEntityColor().approxIndex());
            continue;
        }

        for (auto &&csv: value.valueCodes())
        {
            DwgVariant value = CadSystemVariables::value(key, csv, _document->header());
            if (value.isEmpty())
                continue;

            _writer->write((DxfCode) csv, value);
        }
    }
}

}// namespace dwg
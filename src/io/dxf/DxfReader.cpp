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
#include <dwg/CadSummaryInfo.h>
#include <dwg/CadUtils.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/header/CadHeader.h>
#include <dwg/io/dxf/DxfDocumentBuilder_p.h>
#include <dwg/io/dxf/DxfReader.h>
#include <dwg/io/dxf/readers/DxfBinaryReaderAC1009_p.h>
#include <dwg/io/dxf/readers/DxfBinaryReader_p.h>
#include <dwg/io/dxf/readers/DxfTextReader_p.h>
#include <dwg/io/dxf/readers/IDxfStreamReader_p.h>
#include <dwg/utils/StreamWrapper.h>
#include <fmt/core.h>

namespace dwg {

DxfReader::DxfReader(const std::string &filename)
    : CadReaderBase<DxfReaderConfiguration>(filename), _builder(nullptr), _reader(nullptr),
      _version(ACadVersion::Unknown)
{
}

DxfReader::DxfReader(std::ifstream *stream)
    : CadReaderBase<DxfReaderConfiguration>(stream), _builder(nullptr), _reader(nullptr), _version(ACadVersion::Unknown)
{
}

bool DxfReader::isBinary() const
{
    return IsBinary(_fileStream);
}

CadDocument *DxfReader::read()
{
    _document = new CadDocument(false);
    _document->setSummaryInfo(new CadSummaryInfo());
    if (!_reader)
    {
        _reader = getReader();
    }
    _builder = new DxfDocumentBuilder(_version, _document, *this);
    _builder->OnNotification.add(this, &DxfReader::triggerNotification);
    while (_reader->valueAsString() != DxfFileToken::EndOfFile)
    {
        if (_reader->valueAsString() != DxfFileToken::BeginSection)
        {
            _reader->readNext();
            continue;
        }
        else
        {
            _reader->readNext();
        }

        std::string v = _reader->valueAsString();
        if (v == DxfFileToken::HeaderSection)
        {
            _document->setHeader(readHeader());
            _document->header()->setDocument(_document);
            _builder->setInitialHandSeed(_document->header()->handleSeed());
        }
        else if (v == DxfFileToken::ClassesSection)
        {
            _document->setClasses(readClasses());
        }
        else if (v == DxfFileToken::TablesSection)
        {
            readTables();
        }
        else if (v == DxfFileToken::BlocksSection)
        {
            readBlocks();
        }
        else if (v == DxfFileToken::EntitiesSection)
        {
            readEntities();
        }
        else if (v == DxfFileToken::ObjectsSection)
        {
            readObjects();
        }
        else
        {
            triggerNotification(fmt::format("Section not implemented {}", v), Notification::NotImplemented);
        }
        _reader->readNext();
    }

    if (!_document->header())
    {
        _document->setHeader(new CadHeader(_document));
    }
    _builder->buildDocument();

    return _document;
}

CadHeader *DxfReader::readHeader()
{
    return nullptr;
}

CadDocument *DxfReader::readTables()
{
    return nullptr;
}

std::vector<Entity *> DxfReader::readEntities()
{
    return std::vector<Entity *>();
}

bool DxfReader::IsBinary(const std::string &filename)
{
    std::ifstream ifs(filename);
    bool result = IsBinary(&ifs);
    ifs.close();
    return result;
}

bool DxfReader::IsBinary(std::istream *stream, bool resetPos)
{
    stream->seekg(std::ios::beg);
    InputStreamWrapper wrapper(stream);
    std::string sn = wrapper.readString(DxfBinaryReader::Sentinel.length());
    bool isBinary = (sn == DxfBinaryReader::Sentinel);

    if (resetPos)
    {
        stream->seekg(std::ios::beg);
    }
    return isBinary;
}

DxfClassCollection *DxfReader::readClasses()
{
    return nullptr;
}

DxfClass *DxfReader::readClass()
{
    return nullptr;
}

void DxfReader::readBlocks() {}

void DxfReader::readEntitiesPrivate() {}

void DxfReader::readObjects() {}

void DxfReader::readThumbnailImage() {}

IDxfStreamReader *DxfReader::getReader()
{
    InputStreamWrapper wrapper(_fileStream);
    IDxfStreamReader *tmpReader = nullptr;
    _version = ACadVersion::Unknown;

    bool isBinary = IsBinary(_fileStream, false);
    bool isA1009Format = false;

    if (isBinary && wrapper.readByte() != -1)
    {
        int flag = wrapper.readByte();
        if (flag != -1 && flag != 0)
        {
            isA1009Format = true;
        }
    }

    tmpReader = createReader(isBinary, isA1009Format);
    if (!tmpReader->find(DxfFileToken::HeaderSection))
    {
        _version = ACadVersion::Unknown;
        tmpReader->start();
        return tmpReader;
    }

    while (tmpReader->valueAsString() != DxfFileToken::EndSection)
    {
        if (tmpReader->valueAsString() == "$ACADVER")
        {
            tmpReader->readNext();
            _version = CadUtils::GetVersionFromName(tmpReader->valueAsString());
            if (_version > ACadVersion::AC1021)
            {
                _encoding = Encoding(CodePage::Utf8);
                break;
            }

            if (_version < ACadVersion::AC1002)
            {
                if (_version == ACadVersion::Unknown)
                {
                    throw std::runtime_error("Not support");
                }
                else
                {
                    throw std::runtime_error(
                            fmt::format("Not support version: {}", CadUtils::GetNameFromVersion(_version)));
                }
            }
        }
        else if (tmpReader->valueAsString() == "$DWGCODEPAGE")
        {
            tmpReader->readNext();
            std::string encoding = tmpReader->valueAsString();
            CodePage code = CadUtils::GetCodePageByString(encoding);
            _encoding = getListedEncoding((int) code);
            break;
        }

        tmpReader->readNext();
    }

    return createReader(isBinary, isA1009Format);
}

IDxfStreamReader *DxfReader::goToSection(const std::string &sectionName)
{
    if (!_reader)
    {
        _reader = getReader();
    }

    if (_reader->valueAsString() == sectionName)
        return _reader;

    _reader->find(sectionName);
    return _reader;
}

IDxfStreamReader *DxfReader::createReader(bool isBinary, bool isAC1009Format)
{
    Encoding encoding = _encoding;
    if (encoding.codePage() == CodePage::Unknown)
    {
        encoding = Encoding(CodePage::Usascii);
    }

    if (isBinary)
    {
        if (isAC1009Format)
        {
            return new DxfBinaryReaderAC1009(_fileStream, encoding);
        }
        else
        {
            return new DxfBinaryReader(_fileStream, encoding);
        }
    }
    else
    {
        return new DxfTextReader(_fileStream, encoding);
    }
}

void DxfReader::triggerNotification(const std::string &msg, Notification) {}

}// namespace dwg
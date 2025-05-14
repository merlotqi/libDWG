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

#include <dwg/CadSummaryInfo.h>
#include <dwg/io/Notification.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/readers/DwgSummaryInfoReader_p.h>
#include <dwg/io/dwg/readers/IDwgStreamReader_p.h>
#include <dwg/utils/StreamWrapper.h>
#include <dwg/utils/StringHelp.h>
namespace dwg {

DwgSummaryInfoReader::DwgSummaryInfoReader(ACadVersion version, IDwgStreamReader *reader) : DwgSectionIO(version)
{
    _reader = reader;
    if (version < ACadVersion::AC1021)
    {
        _readStringMethod = [this]() { return readUtf8String(); };
    }
    else
    {
        _readStringMethod = [this]() { return _reader->readTextUtf8(); };
    }
}

DwgSummaryInfoReader::~DwgSummaryInfoReader() {}

std::string DwgSummaryInfoReader::sectionName() const
{
    return DwgSectionDefinition::SummaryInfo;
}

CadSummaryInfo *DwgSummaryInfoReader::read()
{
    CadSummaryInfo *summary = new CadSummaryInfo();
    try
    {//This section contains summary information about the drawing.
        //Strings are encoded as a 16-bit length, followed by the character bytes (0-terminated).

        //String	2 + n	Title
        summary->setTitle(_readStringMethod());
        //String	2 + n	Subject
        summary->setSubject(_readStringMethod());
        //String	2 + n	Author
        summary->setAuthor(_readStringMethod());
        //String	2 + n	Keywords
        summary->setKeywords(_readStringMethod());
        //String	2 + n	Comments
        summary->setComments(_readStringMethod());
        //String	2 + n	LastSavedBy
        summary->setLastSavedBy(_readStringMethod());
        //String	2 + n	RevisionNumber
        summary->setRevisionNumber(_readStringMethod());
        //String	2 + n	RevisionNumber
        summary->setHyperlinkBase(_readStringMethod());

        //?	8	Total editing time(ODA writes two zero Int32’s)
        _reader->readInt();
        _reader->readInt();

        //Julian date	8	Create date time
        summary->setCreatedDate(_reader->read8BitJulianDate());

        //Julian date	8	Modified date timez
        summary->setModifiedDate(_reader->read8BitJulianDate());

        //Int16	2 + 2 * (2 + n)	Property count, followed by PropertyCount key/value string pairs.
        short nproperties = _reader->readShort();
        for (int i = 0; i < nproperties; i++)
        {
            std::string propName = _readStringMethod();
            std::string propValue = _readStringMethod();

            //Add the property
            try
            {
                summary->properties().insert({propName, propValue});
            }
            catch (const std::exception &e)
            {
                notify("[SummaryInfo] An error ocurred while adding a property in the SummaryInfo",
                       Notification::Error);
            }
        }

        //Int32	4	Unknown(write 0)
        _reader->readInt();
        //Int32	4	Unknown(write 0)
        _reader->readInt();
    }
    catch (const std::exception &e)
    {
        auto &&stream = _reader->stream();
        InputStreamWrapper wrapper(stream);
        if (wrapper.pos() != wrapper.length())
        {
            notify("[SummaryInfo] An error occurred while reading the Summary Info", Notification::Error);
        }
    }
    return summary;
}

std::string DwgSummaryInfoReader::readUtf8String()
{
    auto &&stream = _reader->stream();
    InputStreamWrapper wrapper(stream);
    short textLength = wrapper.readT<short, LittleEndianConverter>();
    std::string value;
    if (textLength == 0)
    {
        value = std::string();
    }
    else
    {
        //Read the string and get rid of the empty bytes
        value = wrapper.readString(textLength, Encoding(CodePage::Windows1252));
        value = StringHelp::replace(value, "\0", "");
    }

    return value;
}

}// namespace dwg
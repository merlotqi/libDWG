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

#include <dwg/xdata/ExtendedData.h>
#include <dwg/xdata/ExtendedDataRecord.h>

namespace dwg {

ExtendedData::ExtendedData() {}

ExtendedData::~ExtendedData()
{
    for (auto &&record: _records)
    {
        delete record;
    }
    _records.clear();
}

void ExtendedData::addControlStrings()
{
    if (_records.empty())
    {
        _records.push_back(ExtendedDataControlString::Open());
        _records.push_back(ExtendedDataControlString::Close());
        return;
    }

    auto first = _records.front();
    auto firstControl = dynamic_cast<ExtendedDataControlString *>(first);
    if (!firstControl)
    {
        _records.insert(_records.begin(), ExtendedDataControlString::Open());
    }
    else if (firstControl->isClosing())
    {
        _records.insert(_records.begin(), ExtendedDataControlString::Open());
    }

    auto last = _records.back();
    auto lastControl = dynamic_cast<ExtendedDataControlString *>(last);
    if (!lastControl)
    {
        _records.push_back(ExtendedDataControlString::Close());
    }
    else if (lastControl->isClosing())
    {
        _records.push_back(ExtendedDataControlString::Close());
    }
}

std::vector<ExtendedDataRecord *> ExtendedData::records() const
{
    return _records;
}

std::vector<ExtendedDataRecord *> &ExtendedData::records()
{
    return _records;
}

}// namespace dwg
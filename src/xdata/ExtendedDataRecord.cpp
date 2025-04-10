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

#include <dwg/xdata/ExtendedDataRecord.h>

namespace dwg {

/* --------------------------- ExtendedDataRecord --------------------------- */
DxfCode ExtendedDataRecord::code() const
{
    return _code;
}

DwgVariant ExtendedDataRecord::rawValue() const
{
    return _value;
}

ExtendedDataRecord::ExtendedDataRecord(DxfCode code, const DwgVariant &value) : _code(code), _value(value)
{}

/* ------------------------- ExtendedDataBinaryChunk ------------------------ */
ExtendedDataBinaryChunk::ExtendedDataBinaryChunk(const std::vector<unsigned char> &chunk)
    : ExtendedDataRecordT<std::vector<unsigned char>>(DxfCode::ExtendedDataBinaryChunk, chunk)
{}

/* ------------------------ ExtendedDataControlString ----------------------- */
ExtendedDataControlString::ExtendedDataControlString(bool close)
    : ExtendedDataRecord(DxfCode::ExtendedDataControlString, close ? '}' : '{'), _isClosing(close)
{}

char ExtendedDataControlString::value() const { return _isClosing ? '}' : '{'; }

bool ExtendedDataControlString::isClosing() const { return _isClosing; }

ExtendedDataControlString *ExtendedDataControlString::Open()
{
    return new ExtendedDataControlString(false);
}

ExtendedDataControlString *ExtendedDataControlString::Close()
{
    return new ExtendedDataControlString(true);
}

/* ------------------------- ExtendedDataCoordinate ------------------------- */
ExtendedDataCoordinate::ExtendedDataCoordinate(const XYZ coordinate)
    : ExtendedDataRecordT<XYZ>(DxfCode::ExtendedDataXCoordinate, coordinate)
{
}

/* -------------------------- ExtendedDataDirection ------------------------- */
ExtendedDataDirection::ExtendedDataDirection(const XYZ direction) : ExtendedDataRecordT<XYZ>(DxfCode::ExtendedDataWorldXDir, direction) {}

/* ------------------------ ExtendedDataDisplacement ------------------------ */
ExtendedDataDisplacement::ExtendedDataDisplacement(const XYZ displacement)
    : ExtendedDataRecordT<XYZ>(DxfCode::ExtendedDataWorldXDisp, displacement)
{
}

/* ----------------------- ExtendedDataWorldCoordinate ---------------------- */
ExtendedDataWorldCoordinate::ExtendedDataWorldCoordinate(const XYZ &coordinate)
    : ExtendedDataRecordT<XYZ>(DxfCode::ExtendedDataWorldXCoordinate, coordinate)
{
}

/* -------------------------- ExtendedDataDistance -------------------------- */
ExtendedDataDistance::ExtendedDataDistance(double value) : ExtendedDataRecordT<double>(DxfCode::ExtendedDataDist, value) {}

/* -------------------------- ExtendedDataInteger16 ------------------------- */
ExtendedDataInteger16::ExtendedDataInteger16(short value) : ExtendedDataRecordT<short>(DxfCode::ExtendedDataInteger16, value) {}

/* -------------------------- ExtendedDataInteger32 ------------------------- */
ExtendedDataInteger32::ExtendedDataInteger32(int value) : ExtendedDataRecordT<int>(DxfCode::ExtendedDataInteger32, value) {}

/* ---------------------------- ExtendedDataReal ---------------------------- */
ExtendedDataReal::ExtendedDataReal(double value) : ExtendedDataRecordT<double>(DxfCode::ExtendedDataReal, value) {}

/* ---------------------------- ExtendedDataScale --------------------------- */
ExtendedDataScale::ExtendedDataScale(double value) : ExtendedDataRecordT<double>(DxfCode::ExtendedDataScale, value) {}

/* --------------------------- ExtendedDataString --------------------------- */
ExtendedDataString::ExtendedDataString(const std::string &value) : ExtendedDataRecordT<std::string>(DxfCode::ExtendedDataAsciiString, value)
{
}

}// namespace dwg
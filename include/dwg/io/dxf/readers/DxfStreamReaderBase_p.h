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

#include <dwg/io/dxf/readers/IDxfStreamReader_p.h>
#include <iostream>

namespace dwg {

class DxfStreamReaderBase : public IDxfStreamReader
{
public:
    DxfStreamReaderBase();
    virtual ~DxfStreamReaderBase();

    DxfCode dxfCode() const override;
    GroupCodeValueType groupCodeValue() const override;
    int code() const override;
    DwgVariant value() const override;
    size_t position() const override;
    std::string valueRaw() const override;

    std::string valueAsString() const override;
    bool valueAsBool() const override;
    short valueAsShort() const override;
    unsigned short valueAsUShort() const override;
    int valueAsInt() const override;
    unsigned int valueAsUInt() const override;
    long long valueAsLongLong() const override;
    unsigned long long valueAsHandle() const override;
    double valueAsDouble() const override;
    double valueAsAngle() const override;
    std::vector<unsigned char> valueAsBinaryChunk() const override;

    void readNext() override;
    bool find(const std::string &) override;
    void expectedCode(int code) override;
    std::string toString() const;

    void start() override;

    virtual DxfCode readCode() = 0;
    virtual std::string readStringLine() = 0;
    virtual double lineAsDouble() = 0;
    virtual short lineAsShort() = 0;
    virtual int lineAsInt() = 0;
    virtual long long lineAsLong() = 0;
    virtual unsigned long long lineAsHandle() = 0;
    virtual std::vector<unsigned char> lineAsBinaryChunk() = 0;
    virtual bool lineAsBool() = 0;

    DwgVariant transformValue(GroupCodeValueType code);

protected:
    void setDxfCode(DxfCode);
    void setGroupCodeValue(GroupCodeValueType);
    void setPosition(size_t);
    void setValueRaw(const std::string &);

protected:
    DxfCode _dxfcode;
    GroupCodeValueType _groupCodeValue;
    DwgVariant _value;
    std::size_t _position;/// Current line or offset in the file
    std::string _valueRaw;
};

}// namespace dwg
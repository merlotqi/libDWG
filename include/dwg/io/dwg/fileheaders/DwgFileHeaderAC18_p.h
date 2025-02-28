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

#include <dwg/io/dwg/fileheaders/DwgFileHeaderAC15_p.h>

namespace dwg {

class DwgFileHeaderAC18 : public DwgFileHeaderAC15
{
public:
    DwgFileHeaderAC18();
    DwgFileHeaderAC18(ACadVersion version);
    virtual ~DwgFileHeaderAC18();

    void addSection(const std::string &name) override;
    void addSection(const DwgSectionDescriptor &descriptor);
    DwgSectionDescriptor &getDescriptor(const std::string &name) override;

    unsigned char dwgVersion() const;
    void setDwgVersion(unsigned char);

    unsigned char appReleaseVersion() const;
    void setAppReleaseVersion(unsigned char);

    long long summaryInfoAddr() const;
    void setSummaryInfoAddr(long long);

    long long securityType() const;
    void setSecurityType(long long);

    long long vbaProjectAddr() const;
    void setVbaProjectAddr(long long);

    int rootTreeNodeGap() const;
    void setRootTreeNodeGap(int);

    unsigned int gapArraySize() const;
    void setGapArraySize(unsigned int);

    unsigned int CRCSeed() const;
    void setCRCSeed(unsigned int);

    int lastPageId() const;
    void setLastPageId(int);

    unsigned long long lastSectionAddr() const;
    void setLastSectionAddr(unsigned long long);

    unsigned long long secondHeaderAddr() const;
    void setSecondHeaderAddr(unsigned long long);

    unsigned int gapAmount() const;
    void setGapAmount(unsigned int);

    unsigned int sectionAmount() const;
    void setSectionAmount(unsigned int);

    unsigned int sectionPageMapId() const;
    void setSectionPageMapId(unsigned int);

    unsigned long long pageMapAddress() const;
    void setPageMapAddress(long long unsigned);

    unsigned int sectionMapId() const;
    void setSectionMapId(unsigned int);

    unsigned int sectionArrayPageSize() const;
    void setSectionArrayPageSize(unsigned int);

    int rigthGap() const;
    void setRigthGap(int);

    int leftGap() const;
    void setLeftGap(int);

    std::map<std::string, DwgSectionDescriptor> descriptors() const;
    std::map<std::string, DwgSectionDescriptor> descriptors();
    void setDescriptors(const std::map<std::string, DwgSectionDescriptor> &);

private:
    unsigned char _dwgVersion = 0;
    unsigned char _appReleaseVersion = 0;
    long long _summaryInfoAddr = 0;
    long long _securityType = 0;
    long long _vbaProjectAddr = 0;
    int _rootTreeNodeGap = 0;
    unsigned int _gapArraySize = 0;
    unsigned int _CRCSeed = 0;
    int _lastPageId = 0;
    unsigned long long _lastSectionAddr = 0;
    unsigned long long _secondHeaderAddr = 0;
    unsigned int _gapAmount = 0;
    unsigned int _sectionAmount = 0;
    unsigned int _sectionPageMapId = 0;
    unsigned long long _pageMapAddress = 0;
    unsigned int _sectionMapId = 0;
    unsigned int _sectionArrayPageSize = 0;
    int _rigthGap = 0;
    int _leftGap = 0;
    std::map<std::string, DwgSectionDescriptor> _descriptors;
};

}// namespace dwg
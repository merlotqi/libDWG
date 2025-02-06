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

#include "DwgFileHeaderAC15.h"

namespace dwg {

class DwgFileHeaderAC18 : public DwgFileHeaderAC15
{
public:
    DwgFileHeaderAC18();
    DwgFileHeaderAC18(ACadVersion version);
    virtual ~DwgFileHeaderAC18();
    
    void AddSection(const std::string &name) override;
    void AddSection(const DwgSectionDescriptor &descriptor);
    DwgSectionDescriptor &GetDescriptor(const std::string &name) override;

    unsigned char DwgVersion() const;
    void DwgVersion(unsigned char);

    unsigned char AppReleaseVersion() const;
    void AppReleaseVersion(unsigned char);

    long long SummaryInfoAddr() const;
    void SummaryInfoAddr(long long);
    
    long long SecurityType() const;
    void SecurityType(long long);

    long long VbaProjectAddr() const;
    void VbaProjectAddr(long long);

    int RootTreeNodeGap() const;
    void RootTreeNodeGap(int);

    unsigned int GapArraySize() const;
    void GapArraySize(unsigned int);

    unsigned int CRCSeed() const;
    void CRCSeed(unsigned int);

    int LastPageId() const;
    void LastPageId(int);

    long long LastSectionAddr() const;
    void LastSectionAddr(long long);

    long long SecondHeaderAddr() const;
    void SecondHeaderAddr(long long);

    unsigned int GapAmount() const;
    void GapAmount(unsigned int);

    unsigned int SectionAmount() const;
    void SectionAmount(unsigned int);

    unsigned int SectionPageMapId() const;
    void SectionPageMapId(unsigned int);

    long long PageMapAddress() const;
    void PageMapAddress(long long);

    unsigned int SectionMapId() const;
    void SectionMapId(unsigned int);

    unsigned int SectionArrayPageSize() const;
    void SectionArrayPageSize(unsigned int);

    int RigthGap() const;
    void RigthGap(int);

    int LeftGap() const;
    void LeftGap(int);

    std::map<std::string, DwgSectionDescriptor> Descriptors() const;
    void Descriptors(const std::map<std::string, DwgSectionDescriptor> &);
};

}// namespace dwg
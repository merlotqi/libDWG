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

#include <dwg/io/dwg/fileheaders/DwgFileHeaderAC18_p.h>

namespace dwg {
    
DwgFileHeaderAC18::DwgFileHeaderAC18() {}

DwgFileHeaderAC18::DwgFileHeaderAC18(ACadVersion version) : DwgFileHeaderAC15(version) {}

DwgFileHeaderAC18::~DwgFileHeaderAC18() {}

void DwgFileHeaderAC18::addSection(const std::string &name) { _descriptors.insert({name, DwgSectionDescriptor(name)}); }

void DwgFileHeaderAC18::addSection(const DwgSectionDescriptor &descriptor)
{
    _descriptors.insert({descriptor.name(), descriptor});
}

DwgSectionDescriptor &DwgFileHeaderAC18::getDescriptor(const std::string &name) { return _descriptors.at(name); }

unsigned char DwgFileHeaderAC18::dwgVersion() const { return _dwgVersion; }

void DwgFileHeaderAC18::setDwgVersion(unsigned char value) { _dwgVersion = value; }

unsigned char DwgFileHeaderAC18::appReleaseVersion() const { return _appReleaseVersion; }

void DwgFileHeaderAC18::setAppReleaseVersion(unsigned char value) { _appReleaseVersion = value; }

long long DwgFileHeaderAC18::summaryInfoAddr() const { return _summaryInfoAddr; }

void DwgFileHeaderAC18::setSummaryInfoAddr(long long value) { _summaryInfoAddr = value; }

long long DwgFileHeaderAC18::securityType() const { return _securityType; }

void DwgFileHeaderAC18::setSecurityType(long long value) { _securityType = value; }

long long DwgFileHeaderAC18::vbaProjectAddr() const { return _vbaProjectAddr; }

void DwgFileHeaderAC18::setVbaProjectAddr(long long value) { _vbaProjectAddr = value; }

int DwgFileHeaderAC18::rootTreeNodeGap() const { return _rootTreeNodeGap; }

void DwgFileHeaderAC18::setRootTreeNodeGap(int value) { _rootTreeNodeGap = value; }

unsigned int DwgFileHeaderAC18::gapArraySize() const { return _gapArraySize; }

void DwgFileHeaderAC18::setGapArraySize(unsigned int value) { _gapArraySize = value; }

unsigned int DwgFileHeaderAC18::CRCSeed() const { return _CRCSeed; }

void DwgFileHeaderAC18::setCRCSeed(unsigned int value) { _CRCSeed = value; }

int DwgFileHeaderAC18::lastPageId() const { return _lastPageId; }

void DwgFileHeaderAC18::setLastPageId(int value) { _lastPageId = value; }

unsigned long long DwgFileHeaderAC18::lastSectionAddr() const { return _lastSectionAddr; }

void DwgFileHeaderAC18::setLastSectionAddr(unsigned long long value) { _lastSectionAddr = value; }

unsigned long long DwgFileHeaderAC18::secondHeaderAddr() const { return _secondHeaderAddr; }

void DwgFileHeaderAC18::setSecondHeaderAddr(unsigned long long value) { _secondHeaderAddr = value; }

unsigned int DwgFileHeaderAC18::gapAmount() const { return _gapAmount; }

void DwgFileHeaderAC18::setGapAmount(unsigned int value) { _gapAmount = value; }

unsigned int DwgFileHeaderAC18::sectionAmount() const { return _sectionAmount; }

void DwgFileHeaderAC18::setSectionAmount(unsigned int value) { _sectionAmount = value; }

unsigned int DwgFileHeaderAC18::sectionPageMapId() const { return _sectionPageMapId; }

void DwgFileHeaderAC18::setSectionPageMapId(unsigned int value) { _sectionPageMapId = value; }

unsigned long long DwgFileHeaderAC18::pageMapAddress() const { return _pageMapAddress; }

void DwgFileHeaderAC18::setPageMapAddress(long long unsigned value) { _pageMapAddress = value; }

unsigned int DwgFileHeaderAC18::sectionMapId() const { return _sectionMapId; }

void DwgFileHeaderAC18::setSectionMapId(unsigned int value) { _sectionMapId = value; }

unsigned int DwgFileHeaderAC18::sectionArrayPageSize() const { return _sectionArrayPageSize; }

void DwgFileHeaderAC18::setSectionArrayPageSize(unsigned int value) { _sectionArrayPageSize = value; }

int DwgFileHeaderAC18::rigthGap() const { return _rigthGap; }

void DwgFileHeaderAC18::setRigthGap(int value) { _rigthGap = value; }

int DwgFileHeaderAC18::leftGap() const { return _leftGap; }

void DwgFileHeaderAC18::setLeftGap(int value) { _leftGap = value; }

std::map<std::string, DwgSectionDescriptor> DwgFileHeaderAC18::descriptors() const { return _descriptors; }

std::map<std::string, DwgSectionDescriptor> &DwgFileHeaderAC18::descriptors() { return _descriptors; }

void DwgFileHeaderAC18::setDescriptors(const std::map<std::string, DwgSectionDescriptor> &value)
{
    _descriptors = value;
}

}// namespace dwg
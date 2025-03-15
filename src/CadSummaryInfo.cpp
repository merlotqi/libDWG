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

namespace dwg {

CadSummaryInfo::CadSummaryInfo() {}

CadSummaryInfo::~CadSummaryInfo() {}

std::string CadSummaryInfo::title() const { return _title; }

void CadSummaryInfo::setTitle(const std::string &value) { _title = value; }

std::string CadSummaryInfo::subject() const { return _subject; }

void CadSummaryInfo::setSubject(const std::string &value) { _subject = value; }

std::string CadSummaryInfo::author() const { return _author; }

void CadSummaryInfo::setAuthor(const std::string &value) { _author = value; }

std::string CadSummaryInfo::keywords() const { return _keywords; }

void CadSummaryInfo::setKeywords(const std::string &value) { _keywords = value; }

std::string CadSummaryInfo::comments() const { return _comments; }

void CadSummaryInfo::setComments(const std::string &value) { _comments = value; }

std::string CadSummaryInfo::revisionNumber() const { return _revisionNumber; }

void CadSummaryInfo::setRevisionNumber(const std::string &value) { _revisionNumber = value; }

std::string CadSummaryInfo::lastSavedBy() const { return _lastSavedBy; }

void CadSummaryInfo::setLastSavedBy(const std::string &value) { _lastSavedBy = value; }

std::string CadSummaryInfo::hyperlinkBase() const { return _hyperlinkBase; }

void CadSummaryInfo::setHyperlinkBase(const std::string &value) { _hyperlinkBase = value; }

DateTime CadSummaryInfo::createdDate() const { return _createdDate; }

void CadSummaryInfo::setCreatedDate(const DateTime &value) { _createdDate = value; }

DateTime CadSummaryInfo::modifiedDate() const { return _modifiedDate; }

void CadSummaryInfo::setModifiedDate(const DateTime &value) { _modifiedDate = value; }

std::map<std::string, std::string> CadSummaryInfo::properties() const { return _properties; }

std::map<std::string, std::string> &CadSummaryInfo::properties() { return _properties; }

void CadSummaryInfo::setProperties(const std::map<std::string, std::string> &value) { _properties = value; }

}// namespace dwg
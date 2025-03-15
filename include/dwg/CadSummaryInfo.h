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

#include <dwg/exports.h>
#include <dwg/utils/DateTime.h>
#include <map>
#include <string>

namespace dwg {

/**
 * @class CadSummaryInfo
 * @brief Represents metadata information about a CAD document.
 *
 * This class stores various metadata properties such as title, author, keywords, 
 * and timestamps for creation and modification.
 */
class LIBDWG_API CadSummaryInfo
{
public:
    CadSummaryInfo();
    ~CadSummaryInfo();

    std::string title() const;
    void setTitle(const std::string &value);

    std::string subject() const;
    void setSubject(const std::string &value);

    std::string author() const;
    void setAuthor(const std::string &value);

    std::string keywords() const;
    void setKeywords(const std::string &value);

    std::string comments() const;
    void setComments(const std::string &value);

    std::string revisionNumber() const;
    void setRevisionNumber(const std::string &value);

    std::string lastSavedBy() const;
    void setLastSavedBy(const std::string &value);

    std::string hyperlinkBase() const;
    void setHyperlinkBase(const std::string &value);

    DateTime createdDate() const;
    void setCreatedDate(const DateTime &value);

    DateTime modifiedDate() const;
    void setModifiedDate(const DateTime &value);

    std::map<std::string, std::string> properties() const;
    std::map<std::string, std::string> &properties();
    void setProperties(const std::map<std::string, std::string> &value);

private:
    std::string _title;
    std::string _subject;
    std::string _author;
    std::string _keywords;
    std::string _comments;
    std::string _lastSavedBy;
    std::string _revisionNumber;
    std::string _hyperlinkBase;
    DateTime _createdDate;
    DateTime _modifiedDate;
    std::map<std::string, std::string> _properties;
};

}// namespace dwg
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

#include <ctime>
#include <map>
#include <string>

namespace dwg {

class CadSummaryInfo
{
    std::string m_title;
    std::string m_subject;
    std::string m_author;
    std::string m_keywords;
    std::string m_comments;
    std::string m_lastSavedBy;
    std::string m_hyperlinkBase;
    time_t m_createDate;
    time_t m_modifiedDate;
    std::map<std::string, std::string> m_properties;

public:
    CadSummaryInfo();

    std::string getTitle() const;
    void setTitle(const std::string &value);

    std::string getSubject() const;
    void stSubject(const std::string &value);

    std::string getAuthor() const;
    void setAuthor(const std::string &value);

    std::string getKeywords() const;
    void setKeywords(const std::string &value);

    std::string getComments() const;
    void setComments(const std::string &value);

    std::string getLastSavedBy() const;
    void setLastSavedBy(const std::string &value);

    std::string getHyperlinkBase() const;
    void setHyperlinkBase(const std::string &value);

    time_t getCreatedDate() const;
    void setCreatedDate(time_t value);

    time_t getModifiedDate() const;
    void setModifiedDate(time_t value);

    std::map<std::string, std::string> getProperties() const;
    void setProperties(const std::map<std::string, std::string> &value);
};

}
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

#include <cpl_ports.h>
#include <dwg/exports.h>

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
    /**
     * @brief Default constructor.
     */
    CadSummaryInfo();

    /**
     * @brief Destructor.
     */
    ~CadSummaryInfo();

    /**
     * @brief Get the title of the CAD document.
     * @return A string representing the title.
     */
    std::string Title() const;

    /**
     * @brief Set the title of the CAD document.
     * @param title A string containing the new title.
     */
    void Title(const std::string &title);

    /**
     * @brief Get the subject of the CAD document.
     * @return A string representing the subject.
     */
    std::string Subject() const;

    /**
     * @brief Set the subject of the CAD document.
     * @param subject A string containing the new subject.
     */
    void Subject(const std::string &subject);

    /**
     * @brief Get the author of the CAD document.
     * @return A string representing the author.
     */
    std::string Author() const;

    /**
     * @brief Set the author of the CAD document.
     * @param author A string containing the new author.
     */
    void Author(const std::string &author);

    /**
     * @brief Get the keywords associated with the CAD document.
     * @return A string containing the keywords.
     */
    std::string Keywords() const;

    /**
     * @brief Set the keywords for the CAD document.
     * @param keywords A string containing the new keywords.
     */
    void Keywords(const std::string &keywords);

    /**
     * @brief Get the comments or description of the CAD document.
     * @return A string containing the comments.
     */
    std::string Comments() const;

    /**
     * @brief Set the comments for the CAD document.
     * @param comments A string containing the new comments.
     */
    void Comments(const std::string &comments);

    /**
     * @brief Get the name of the last user who saved the document.
     * @return A string containing the last saved by user name.
     */
    std::string LastSavedBy() const;

    /**
     * @brief Set the name of the last user who saved the document.
     * @param lastSavedBy A string containing the new user name.
     */
    void LastSavedBy(const std::string &lastSavedBy);

    /**
     * @brief Get the base URL for hyperlinks in the document.
     * @return A string containing the hyperlink base.
     */
    std::string HyperlinkBase() const;

    /**
     * @brief Set the base URL for hyperlinks in the document.
     * @param hyperlinkBase A string containing the new hyperlink base.
     */
    void HyperlinkBase(const std::string &hyperlinkBase);

    /**
     * @brief Get the creation date of the CAD document.
     * @return A CPL::DateTime object representing the creation date.
     */
    CPL::DateTime CreateDate() const;

    /**
     * @brief Set the creation date of the CAD document.
     * @param createDate A CPL::DateTime object containing the new creation date.
     */
    void CreateDate(const CPL::DateTime &createDate);

    /**
     * @brief Get the last modification date of the CAD document.
     * @return A CPL::DateTime object representing the modification date.
     */
    CPL::DateTime ModifiedDate() const;

    /**
     * @brief Set the last modification date of the CAD document.
     * @param modifiedDate A CPL::DateTime object containing the new modification date.
     */
    void ModifiedDate(const CPL::DateTime &modifiedDate);

    /**
     * @brief Get the custom properties associated with the CAD document.
     * @return A map containing key-value pairs of custom properties.
     */
    std::map<std::string, std::string> Properties() const;

    /**
     * @brief Set the custom properties for the CAD document.
     * @param properties A map containing key-value pairs of custom properties.
     */
    void Properties(const std::map<std::string, std::string> &properties);
};

}// namespace dwg
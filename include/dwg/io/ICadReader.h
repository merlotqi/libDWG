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

#include <dwg/CadDocument.h>
#include <dwg/CadHander.h>
#include <dwg/utils/StreamIO.h>

#include <type_traits>

namespace dwg {
namespace io {

class ICadReader {
public:
    ICadReader() = default;
    virtual ~ICadReader() = default;
    virtual CadDocument* Read() = 0;
    virtual CadHander& ReadHeader() = 0;
};

class CadReaderConfiguration
{
    bool m_failsafe;
    bool m_keepUnknownEntities;
    bool m_keepUnknownNonGraphicalObjects;

public:
    CadReaderConfiguration()
    {
        m_failsafe = true;
        m_keepUnknownEntities = false;
        m_keepUnknownNonGraphicalObjects = false;
    }
    virtual ~CadReaderConfiguration() = default;

    bool Failsafe() const;
    void Failsafe(bool value);

    bool KeepUnknownEntities() const;
    void KeepUnknownEntities(bool value);

    bool KeepUnknownNonGraphicalObjects() const;
    void KeepUnknownNonGraphicalObjects(bool value);
};

template<class T>
class CadReaderBase : public ICadReader
{
    static_assert(std::is_base_of_v<CadReaderConfiguration, T>, "";)

public:
    virtual ~CadReaderBase();

protected:
    CadReaderBase() = default;
    CadReaderBase(const std::string& filename);
    CadReaderBase(std::ifstream* stream);

protected:
    T* m_configuration = nullptr;
    CadDocument* m_document;
    InputStream* m_fileStream;
};

} // namespace io
} // namespace dwg
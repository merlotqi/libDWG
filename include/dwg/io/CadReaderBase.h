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

#include <dwg/io/CadReaderConfiguration.h>
#include <dwg/io/ICadReader.h>
#include <dwg/io/Notification.h>
#include <dwg/utils/Delegate.h>
#include <string>
#include <type_traits>

namespace dwg {

template<class T>
class LIBDWG_API CadReaderBase : public ICadReader, protected T
{
    static_assert(std::is_base_of<CadReaderConfiguration, T>::value, "T must is base CadReaderConfiguration");

public:
    virtual ~CadReaderBase();
    Delegate<void(const std::string &, Notification)> OnNotification;

protected:
    CadReaderBase();
    CadReaderBase(const std::string &filename);
    CadReaderBase(std::ifstream *stream);

protected:
    CadDocument *_document;
    std::ifstream *_fileStream;
};


template<class T>
inline CadReaderBase<T>::~CadReaderBase()
{
}

template<class T>
inline CadReaderBase<T>::CadReaderBase() : _fileStream(nullptr), _document(nullptr)
{
}

template<class T>
inline CadReaderBase<T>::CadReaderBase(const std::string &filename)
    : _fileStream(new std::ifstream(filename)), _document(nullptr)
{
}

template<class T>
inline CadReaderBase<T>::CadReaderBase(std::ifstream *stream) : _fileStream(stream), _document(nullptr)
{
}

}// namespace dwg
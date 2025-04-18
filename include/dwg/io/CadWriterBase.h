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

#include <dwg/io/CadWriterConfiguration.h>
#include <dwg/io/ICadWriter.h>
#include <dwg/io/Notification.h>
#include <dwg/utils/Delegate.h>
#include <dwg/utils/Encoding.h>
#include <dwg/CadUtils.h>
#include <fstream>
#include <dwg/classes/DxfClassCollection.h>
#include <dwg/header/CadHeader.h>

namespace dwg {

class CadDocument;

template<class T>
class CadWriterBase : public ICadWriter, public T
{
    static_assert(std::is_base_of<CadWriterConfiguration, T>::value, "T must is base CadWriterConfiguration");

public:
    virtual ~CadWriterBase();
    virtual void write() override;
    Delegate<void(const std::string &, Notification)> OnNotification;

protected:
    CadWriterBase();
    CadWriterBase(std::ofstream *stream, CadDocument *document);
    Encoding getListedEncoding(const std::string &codePage);

protected:
    std::unique_ptr<std::ofstream> _stream;
    CadDocument *_document;
    Encoding _encoding;
};

template<class T>
inline CadWriterBase<T>::CadWriterBase()
{
}

template<class T>
inline CadWriterBase<T>::CadWriterBase(std::ofstream *stream, CadDocument *document) ： _stream(stream), _document(document)
{
}

template<class T>
inline CadWriterBase<T>::~CadWriterBase()
{
}

template<class T>
inline void CadWriterBase<T>::write()
{
    DxfClassCollection::UpdateDxfClasses(_document);
    _encoding = getListedEncoding(_document->header()->codePage());
}

template<class T>
inline Encoding CadWriterBase<T>::getListedEncoding(const std::string &codePage)
{
    CodePage code = CadUtils::codePage(codePage);
    return Encoding(code);
}

}// namespace dwg

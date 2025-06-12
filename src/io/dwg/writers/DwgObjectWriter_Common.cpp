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
#include <dwg/CadObject.h>
#include <dwg/CadUtils.h>
#include <dwg/classes/DxfClass.h>
#include <dwg/classes/DxfClassCollection.h>
#include <dwg/entities/Entity.h>
#include <dwg/io/dwg/CRC8StreamHandler_p.h>
#include <dwg/io/dwg/writers/DwgObjectWriter_p.h>
#include <dwg/io/dwg/writers/IDwgStreamWriter_p.h>
#include <dwg/objects/BookColor.h>
#include <dwg/objects/CadDictionary.h>
#include <dwg/objects/CadDictionaryWithDefault.h>
#include <dwg/tables/AppId.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/Layer.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/utils/EndianConverter.h>
#include <dwg/utils/StreamWrapper.h>
#include <dwg/xdata/ExtendedData.h>
#include <dwg/xdata/ExtendedDataDictionary.h>
#include <dwg/xdata/ExtendedDataRecord.h>
#include <fmt/core.h>
#include <fstream>
#include <stdexcept>

namespace dwg {

void DwgObjectWriter::registerObject(CadObject *cadObject)
{
    _writer->writeSpearShift();

    //Set the position to the entity to find
    long long position = _stream->tellp();
    CRC8StreamHandler crc(_stream, 0xC0C1);
    StreamWrapper msmain_wrapper(&_msmain);

    //MS : Size of object, not including the CRC
    unsigned int size = (unsigned int) _msmain.tellp();
    long sizeb = (msmain_wrapper.length() << 3) - _writer->savedPositionInBits();
    writeSize(&crc, size);

    //R2010+:
    if (R2010Plus)
    {
        //MC : Size in bits of the handle stream (unsigned, 0x40 is not interpreted as sign).
        //This includes the padding bits at the end of the handle stream
        //(the padding bits make sure the object stream ends on a unsigned char boundary).
        writeSizeInBits(&crc, (unsigned long long) sizeb);
    }

    //Write the object in the stream
    crc.write(msmain_wrapper.buffer(), 0, (int) msmain_wrapper.length());
    _stream->write(reinterpret_cast<const char *>(LittleEndianConverter::instance()->bytes(crc.seed()).data()), 2);

    _map.insert({cadObject->handle(), position});
}

void DwgObjectWriter::writeSize(CRC8StreamHandler *stream, unsigned int size)
{
    // This value is only read in IDwgStreamReader.ReadModularShort()
    // this should do the trick to write the modular short

    if (size >= 0b1000000000000000)
    {
        stream->writeByte((unsigned char) (size & 0b11111111));
        stream->writeByte((unsigned char) (((size >> 8) & 0b1111111) | 0b10000000));
        stream->writeByte((unsigned char) ((size >> 15) & 0b11111111));
        stream->writeByte((unsigned char) ((size >> 23) & 0b11111111));
    }
    else
    {
        stream->writeByte((unsigned char) (size & 0b11111111));
        stream->writeByte((unsigned char) ((size >> 8) & 0b11111111));
    }
}

void DwgObjectWriter::writeSizeInBits(CRC8StreamHandler *stream, unsigned long long size)
{
    // This value is only read in IDwgStreamReader.ReadModularChar()
    // this should do the trick to write the modular char

    if (size == 0)
    {
        stream->writeByte(0);
        return;
    }

    unsigned long long shift = size >> 7;
    while (size != 0)
    {
        unsigned char b = (unsigned char) (size & 0b1111111);
        if (shift != 0)
        {
            b = (unsigned char) (b | 0b10000000);
        }

        stream->writeByte(b);
        size = shift;
        shift = size >> 7;
    }
}

void DwgObjectWriter::writeXrefDependantBit(TableEntry *entry)
{
    if (R2007Plus)
    {
        //xrefindex+1 BS 70 subtract one from this value when read.
        //After that, -1 indicates that this reference did not come from an xref,
        //otherwise this value indicates the index of the blockheader for the xref from which this came.
        _writer->writeBitShort((short) ((entry->flags() & StandardFlag::XrefDependent) ? 0b100000000 : 0));
    }
    else
    {
        //64-flag B 70 The 64-bit of the 70 group.
        _writer->writeBit(entry->flags() & StandardFlag::Referenced);

        //xrefindex + 1 BS 70 subtract one from this value when read.
        //After that, -1 indicates that this reference did not come from an xref,
        //otherwise this value indicates the index of the blockheader for the xref from which this came.
        _writer->writeBitShort(0);

        //Xdep B 70 dependent on an xref. (16 bit)
        _writer->writeBit(entry->flags() & StandardFlag::XrefDependent);
    }
}

void DwgObjectWriter::writeCommonData(CadObject *cadObject)
{
    //Reset the current stream to re-write a new object in it
    _writer->resetStream();

    switch (cadObject->objectType())
    {
        case ObjectType::UNLISTED:
            {
                DxfClass *dxfClass = _document->classes()->getByName(cadObject->objectName());
                if (dxfClass)
                {
                    _writer->writeObjectType(dxfClass->classNumber());
                }
                else
                {
                    notify("Dxf Class not found for {cadObject.ObjectType} fullname: {cadObject.GetType().FullName}",
                           Notification::Warning);
                    return;
                }
                break;
            }
        case ObjectType::INVALID:
        case ObjectType::UNDEFINED:
            {
                notify("CadObject type: {cadObject.ObjectType} fullname: {cadObject.GetType().FullName}",
                       Notification::NotImplemented);
                return;
            }
        default:
            _writer->writeObjectType(cadObject->objectType());
            break;
    }

    if (_version >= ACadVersion::AC1015 && _version < ACadVersion::AC1024)
        //Obj size RL size of object in bits, not including end handles
        _writer->savePositonForSize();

    //Common:
    //Handle H 5 code 0, length followed by the handle bytes.
    _writer->main()->handleReference(cadObject);

    //Extended object data, if any
    writeExtendedData(cadObject->extendedData());
}

void DwgObjectWriter::writeCommonNonEntityData(CadObject *cadObject)
{
    writeCommonData(cadObject);

    //R13-R14 Only:
    //Obj size RL size of object in bits, not including end handles
    if (R13_14Only)
        _writer->savePositonForSize();

    //[Owner ref handle (soft pointer)]
    _writer->handleReference(DwgReferenceType::SoftPointer, cadObject->owner()->handle());

    //write the cad object reactors
    writeReactorsAndDictionaryHandle(cadObject);
}

void DwgObjectWriter::writeCommonEntityData(Entity *entity)
{
    writeCommonData(entity);

    //Graphic present Flag B 1 if a graphic is present
    _writer->writeBit(false);

    //R13 - R14 Only:
    if (_version >= ACadVersion::AC1012 && _version <= ACadVersion::AC1014)
    {
        _writer->savePositonForSize();
    }

    writeEntityMode(entity);
}

void DwgObjectWriter::writeEntityMode(Entity *entity)
{
    //FE: Entity mode(entmode). Generally, this indicates whether or not the owner
    //relative handle reference is present.The values go as follows:

    //00 : The owner relative handle reference is present.
    //Applies to the following:
    //VERTEX, ATTRIB, and SEQEND.
    //BLOCK, ENDBLK, and the defining entities in all
    //block defs except *MODEL_SPACE and *PAPER_SPACE.

    //01 : PSPACE entity without a owner relative handle ref.
    //10 : MSPACE entity without a owner relative handle ref.
    //11 : Not used.
    unsigned char entmode = getEntMode(entity);
    _writer->write2Bits(entmode);
    if (entmode == 0)
    {
        _writer->handleReference(DwgReferenceType::SoftPointer, entity->layer());
    }

    writeReactorsAndDictionaryHandle(entity);

    //R13-R14 Only:
    if (R13_14Only)
    {
        //8 LAYER (hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, entity->layer());

        //Isbylayerlt B 1 if bylayer linetype, else 0
        bool isbylayerlt = (entity->lineType()->name() == LineType::ByLayerName);
        _writer->writeBit(isbylayerlt);
        if (isbylayerlt)
            //6 [LTYPE (hard pointer)] (present if Isbylayerlt is 0)
            _writer->handleReference(DwgReferenceType::HardPointer, entity->lineType());
    }

    //R13-R2000 Only:
    //previous/next handles present if Nolinks is 0.
    //Nolinks B 1 if major links are assumed +1, -1, else 0 For R2004+this always has value 1 (links are not used)
    bool hasLinks = true;
    if (!R2004Plus)
    {
        hasLinks = _prev != nullptr && _prev->handle() == entity->handle() - 1 && _next != nullptr &&
                   _next->handle() == entity->handle() + 1;

        _writer->writeBit(hasLinks);

        //[PREVIOUS ENTITY (relative soft pointer)]
        _writer->handleReference(DwgReferenceType::SoftPointer, _prev);
        //[NEXT ENTITY (relative soft pointer)]
        _writer->handleReference(DwgReferenceType::SoftPointer, _next);
    }

    //Color	CMC(B)	62
    _writer->writeEnColor(entity->color(), entity->transparency(), entity->bookColor() != nullptr);

    //R2004+:
    if ((_version >= ACadVersion::AC1018) && entity->bookColor() != nullptr)
    {
        //[Color book color handle (hard pointer)]
        _writer->handleReference(DwgReferenceType::HardPointer, entity->bookColor());
    }

    //Ltype scale	BD	48
    _writer->writeBitDouble(entity->linetypeScale());

    if (!(_version >= ACadVersion::AC1015))
    {
        //Common:
        //Invisibility BS 60
        _writer->writeBitShort((short) (entity->isInvisible() ? 0 : 1));

        return;
    }

    //R2000+:
    //8 LAYER (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, entity->layer());

    if (entity->lineType()->name() == LineType::ByLayerName)
    {
        //Ltype flags BB 00 = bylayer,
        _writer->write2Bits(0b00);
    }
    else if (entity->lineType()->name() == LineType::ByBlockName)
    {
        //01 = byblock,
        _writer->write2Bits(0b01);
    }
    else if (entity->lineType()->name() == LineType::ContinuousName)
    {
        //10 = continous,
        _writer->write2Bits(0b10);
    }
    else
    {
        //11 = linetype handle present at end of object
        _writer->write2Bits(0b11);
        //6 [LTYPE (hard pointer)] present if linetype flags were 11
        _writer->handleReference(DwgReferenceType::HardPointer, entity->lineType());
    }

    //R2007+:
    if (R2007Plus)
    {
        //Material flags BB 00 = bylayer, 01 = byblock, 11 = material handle present at end of object
        _writer->write2Bits(0b00);

        //Shadow flags RC
        _writer->writeByte(0);
    }

    //R2000 +:
    //Plotstyle flags	BB	00 = bylayer, 01 = byblock, 11 = plotstyle handle present at end of object
    _writer->write2Bits(0b00);
    {
        //PLOTSTYLE (hard pointer) present if plotstyle flags were 11
    }

    //R2007 +:
    if (_version > ACadVersion::AC1021)
    {
        //Material flags BB 00 = bylayer, 01 = byblock, 11 = material handle present at end of object
        _writer->writeBit(false);
        {
            //If has full visual style, the full visual style handle (hard pointer).
        }
        _writer->writeBit(false);
        {
            //If has full visual style, the full visual style handle (hard pointer).
        }
        //Shadow flags RC
        _writer->writeBit(false);
        {
            //If has full visual style, the full visual style handle (hard pointer).
        }
    }

    //Common:
    //Invisibility BS 60
    _writer->writeBitShort((short) (entity->isInvisible() ? 1 : 0));

    //R2000+:
    //Lineweight RC 370
    _writer->writeByte(CadUtils::ToIndex(entity->lineweight()));
}

void DwgObjectWriter::writeExtendedData(ExtendedDataDictionary *data)
{
    if (writeXData())
    {
        //EED size BS size of extended entity data, if any
        for (auto it = data->begin(); it != data->end(); ++it)
        {
            writeExtendedDataEntry(it->first, it->second);
        }
    }

    _writer->writeBitShort(0);
}

void DwgObjectWriter::writeExtendedDataEntry(AppId *app, ExtendedData *entry)
{
    std::ostringstream stream;
    StreamWrapper mstream(&stream);

    for (auto &&record: entry->records())
    {
        //Each data item has a 1-unsigned char code (DXF group code minus 1000) followed by the value.
        mstream.writeByte((unsigned char) ((int) record->code() - 1000));
        auto &&binaryChunk = dynamic_cast<ExtendedDataBinaryChunk *>(record);
        if (binaryChunk)
        {
            mstream.writeByte((unsigned char) binaryChunk->value().size());
            mstream.write(binaryChunk->value(), 0, binaryChunk->value().size());
        }
        auto &&control = dynamic_cast<ExtendedDataControlString *>(record);
        if (control)
        {
            mstream.writeByte((unsigned char) (control->value() == '}' ? 1 : 0));
        }
        auto &&s16 = dynamic_cast<ExtendedDataInteger16 *>(record);
        if (s16)
        {
            mstream.write(LittleEndianConverter::instance()->bytes(s16->value()), 0, 2);
        }
        auto &&s32 = dynamic_cast<ExtendedDataInteger32 *>(record);
        if (s32)
        {
            mstream.write(LittleEndianConverter::instance()->bytes(s32->value()), 0, 4);
        }
        auto &&real = dynamic_cast<ExtendedDataReal *>(record);
        if (real)
        {
            mstream.write(LittleEndianConverter::instance()->bytes(real->value()), 0, 8);
        }
        auto &&scale = dynamic_cast<ExtendedDataScale *>(record);
        if (scale)
        {
            mstream.write(LittleEndianConverter::instance()->bytes(scale->value()), 0, 8);
        }
        auto &&dist = dynamic_cast<ExtendedDataDistance *>(record);
        if (dist)
        {
            mstream.write(LittleEndianConverter::instance()->bytes(dist->value()), 0, 8);
        }
        auto &&dir = dynamic_cast<ExtendedDataDirection *>(record);
        if (dir)
        {
            mstream.write(LittleEndianConverter::instance()->bytes(dir->value().X), 0, 8);
            mstream.write(LittleEndianConverter::instance()->bytes(dir->value().Y), 0, 8);
            mstream.write(LittleEndianConverter::instance()->bytes(dir->value().Z), 0, 8);
        }
        auto &&disp = dynamic_cast<ExtendedDataDisplacement *>(record);
        if (disp)
        {
            mstream.write(LittleEndianConverter::instance()->bytes(disp->value().X), 0, 8);
            mstream.write(LittleEndianConverter::instance()->bytes(disp->value().Y), 0, 8);
            mstream.write(LittleEndianConverter::instance()->bytes(disp->value().Z), 0, 8);
        }
        auto &&coord = dynamic_cast<ExtendedDataCoordinate *>(record);
        if (coord)
        {
            mstream.write(LittleEndianConverter::instance()->bytes(coord->value().X), 0, 8);
            mstream.write(LittleEndianConverter::instance()->bytes(coord->value().Y), 0, 8);
            mstream.write(LittleEndianConverter::instance()->bytes(coord->value().Z), 0, 8);
        }
        auto &&wcoord = dynamic_cast<ExtendedDataWorldCoordinate *>(record);
        if (wcoord)
        {
            mstream.write(LittleEndianConverter::instance()->bytes(wcoord->value().X), 0, 8);
            mstream.write(LittleEndianConverter::instance()->bytes(wcoord->value().Y), 0, 8);
            mstream.write(LittleEndianConverter::instance()->bytes(wcoord->value().Z), 0, 8);
        }
        auto &&handle = dynamic_cast<IExtendedDataHandleReference *>(record);
        if (handle)
        {
            unsigned long long h = handle->value();
            if (handle->resolveReference(_document) == nullptr)
            {
                h = 0;
            }
            mstream.write(BigEndianConverter::instance()->bytes(h), 0, 8);
        }
        auto &&str = dynamic_cast<ExtendedDataString *>(record);
        if (str)
        {
            if (R2007Plus)
            {
                mstream.write(LittleEndianConverter::instance()->bytes((unsigned short) str->value().size() + 1), 0, 2);
                std::vector<unsigned char> bytes = Encoding::Utf8().bytes(str->value());

                mstream.write(bytes, 0, bytes.size());
                mstream.writeByte(0);
                mstream.writeByte(0);
            }
            else
            {
                std::vector<unsigned char> bytes = _writer->encoding().bytes(str->value());
                mstream.write(LittleEndianConverter::instance()->bytes((unsigned short) str->value().length() + 1), 0,
                              2);
                mstream.write(bytes, 0, bytes.size());
                mstream.writeByte(0);
            }
        }

        throw std::runtime_error("ExtendedDataRecord of type {record.GetType().FullName} not supported.");
    }

    _writer->writeBitShort((short) mstream.length());

    _writer->main()->handleReference(DwgReferenceType::HardPointer, app->handle());

    _writer->writeBytes(mstream.buffer(), 0, (int) mstream.length());
}

void DwgObjectWriter::writeReactorsAndDictionaryHandle(CadObject *cadObject)
{
    //Numreactors S number of reactors in this object
    cadObject->clearReactors();
    _writer->writeBitLong(cadObject->reactors().size());
    for (auto &&item: cadObject->reactors())
    {
        //[Reactors (soft pointer)]
        _writer->handleReference(DwgReferenceType::SoftPointer, item);
    }

    bool noDictionary = (cadObject->xdictionary() == nullptr);

    //R2004+:
    if (R2004Plus)
    {
        _writer->writeBit(noDictionary);
        if (!noDictionary)
        {
            _writer->handleReference(DwgReferenceType::HardOwnership, cadObject->xdictionary());
        }
    }
    else
    {
        //xdicobjhandle(hard owner)
        _writer->handleReference(DwgReferenceType::HardOwnership, cadObject->xdictionary());
    }

    //R2013+:
    if (R2013Plus)
    {
        //Has DS binary data B If 1 then this object has associated binary data stored in the data store
        _writer->writeBit(false);
    }

    if (!noDictionary)
    {
        _dictionaries.insert({cadObject->xdictionary()->handle(), cadObject->xdictionary()});
        _objects.push(cadObject->xdictionary());
    }
}

unsigned char DwgObjectWriter::getEntMode(Entity *entity)
{
    if (entity->owner() == nullptr)
    {
        return 0;
    }

    if (entity->owner()->handle() == _document->paperSpace()->handle())
    {
        return 0b01;
    }

    if (entity->owner()->handle() == _document->modelSpace()->handle())
    {
        return 0b10;
    }

    return 0;
}

}// namespace dwg
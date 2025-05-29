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

#include <dwg/io/dwg/writers/DwgObjectWriter_p.h>
#include <dwg/io/dwg/writers/IDwgStreamWriter_p.h>

namespace dwg {

void DwgObjectWriter::registerObject(CadObject *cadObject)
{
    _writer->writeSpearShift();

    //Set the position to the entity to find
    long position = _stream.Position;
    CRC8StreamHandler crc = new CRC8StreamHandler(_stream, 0xC0C1);

    //MS : Size of object, not including the CRC
    uint size = (uint) _msmain.Length;
    long sizeb = (_msmain.Length << 3) - _writer->SavedPositionInBits;
    writeSize(crc, size);

    //R2010+:
    if (R2010Plus)
    {
        //MC : Size in bits of the handle stream (unsigned, 0x40 is not interpreted as sign).
        //This includes the padding bits at the end of the handle stream
        //(the padding bits make sure the object stream ends on a unsigned char boundary).
        writeSizeInBits(crc, (unsigned long long) sizeb);
    }

    //Write the object in the stream
    crc.Write(_msmain.GetBuffer(), 0, (int) _msmain.Length);
    _stream.Write(LittleEndianConverter.Instance.GetBytes(crc.Seed), 0, 2);

    Map.Add(cadObject.Handle, position);
}

void DwgObjectWriter::writeSize(std::ostream stream, unsigned int size)
{
    // This value is only read in IDwgStreamReader.ReadModularShort()
    // this should do the trick to write the modular short

    if (size >= 0b1000000000000000)
    {
        stream.WriteByte((unsigned char) (size & 0b11111111));
        stream.WriteByte((unsigned char) (((size >> 8) & 0b1111111) | 0b10000000));
        stream.WriteByte((unsigned char) ((size >> 15) & 0b11111111));
        stream.WriteByte((unsigned char) ((size >> 23) & 0b11111111));
    }
    else
    {
        stream.WriteByte((unsigned char) (size & 0b11111111));
        stream.WriteByte((unsigned char) ((size >> 8) & 0b11111111));
    }
}

void DwgObjectWriter::writeSizeInBits(std::ostream *stream, unsigned long long size)
{
    // This value is only read in IDwgStreamReader.ReadModularChar()
    // this should do the trick to write the modular char

    if (size == 0)
    {
        stream.WriteByte(0);
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

        stream.WriteByte(b);
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
        _writer->writeBitShort((short) (entry.Flags.HasFlag(StandardFlags.XrefDependent) ? 0b100000000 : 0));
    }
    else
    {
        //64-flag B 70 The 64-bit of the 70 group.
        _writer->writeBit(entry.Flags.HasFlag(StandardFlags.Referenced));

        //xrefindex + 1 BS 70 subtract one from this value when read.
        //After that, -1 indicates that this reference did not come from an xref,
        //otherwise this value indicates the index of the blockheader for the xref from which this came.
        _writer->writeBitShort(0);

        //Xdep B 70 dependent on an xref. (16 bit)
        _writer->writeBit(entry.Flags.HasFlag(StandardFlags.XrefDependent));
    }
}

void DwgObjectWriter::writeCommonData(CadObject *cadObject)
{
    //Reset the current stream to re-write a new object in it
    _writer->ResetStream();

    switch (cadObject.ObjectType)
    {
        case ACadVersion::UNLISTED:
            if (_document.Classes.TryGetByName(cadObject.ObjectName, out DxfClass dxfClass))
            {
                _writer->writeObjectType(dxfClass.ClassNumber);
            }
            else
            {
                notify($ "Dxf Class not found for {cadObject.ObjectType} fullname: {cadObject.GetType().FullName}",
                       Notification::Warning);
                return;
            }
            break;
        case ACadVersion::INVALID:
        case ACadVersion::UNDEFINED:
            notify($ "CadObject type: {cadObject.ObjectType} fullname: {cadObject.GetType().FullName}",
                   Notification::NotImplemented);
            return;
        default:
            _writer->writeObjectType(cadObject.ObjectType);
            break;
    }

    if (_version >= ACadVersion::AC1015 && _version < ACadVersion::AC1024)
        //Obj size RL size of object in bits, not including end handles
        _writer->SavePositonForSize();

    //Common:
    //Handle H 5 code 0, length followed by the handle bytes.
    _writer->main()->handleReference(cadObject);

    //Extended object data, if any
    writeExtendedData(cadObject.ExtendedData);
}

void DwgObjectWriter::writeCommonNonEntityData(CadObject *cadObject)
{
    writeCommonData(cadObject);

    //R13-R14 Only:
    //Obj size RL size of object in bits, not including end handles
    if (R13_14Only)
        _writer->SavePositonForSize();

    //[Owner ref handle (soft pointer)]
    _writer->handleReference(DwgReferenceType.SoftPointer, cadObject.Owner.Handle);

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
        _writer->SavePositonForSize();
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
        _writer->handleReference(DwgReferenceType.SoftPointer, entity.Owner);
    }

    writeReactorsAndDictionaryHandle(entity);

    //R13-R14 Only:
    if (R13_14Only)
    {
        //8 LAYER (hard pointer)
        _writer->handleReference(DwgReferenceType.HardPointer, entity.Layer);

        //Isbylayerlt B 1 if bylayer linetype, else 0
        bool isbylayerlt = entity.LineType.Name == LineType.ByLayerName;
        _writer->writeBit(isbylayerlt);
        if (isbylayerlt)
            //6 [LTYPE (hard pointer)] (present if Isbylayerlt is 0)
            _writer->handleReference(DwgReferenceType.HardPointer, entity.LineType);
    }

    //R13-R2000 Only:
    //previous/next handles present if Nolinks is 0.
    //Nolinks B 1 if major links are assumed +1, -1, else 0 For R2004+this always has value 1 (links are not used)
    bool hasLinks = true;
    if (!R2004Plus)
    {
        hasLinks = _prev != null && _prev.Handle == entity.Handle - 1 && _next != null &&
                   _next.Handle == entity.Handle + 1;

        _writer->writeBit(hasLinks);

        //[PREVIOUS ENTITY (relative soft pointer)]
        _writer->handleReference(DwgReferenceType.SoftPointer, _prev);
        //[NEXT ENTITY (relative soft pointer)]
        _writer->handleReference(DwgReferenceType.SoftPointer, _next);
    }

    //Color	CMC(B)	62
    _writer->writeEnColor(entity.Color, entity.Transparency, entity.BookColor != null);

    //R2004+:
    if ((_version >= ACadVersion::AC1018) && entity.BookColor != null)
    {
        //[Color book color handle (hard pointer)]
        _writer->handleReference(DwgReferenceType.HardPointer, entity.BookColor);
    }

    //Ltype scale	BD	48
    _writer->writeBitDouble(entity.LinetypeScale);

    if (!(_version >= ACadVersion::AC1015))
    {
        //Common:
        //Invisibility BS 60
        _writer->writeBitShort((short) (entity.IsInvisible ? 0 : 1));

        return;
    }

    //R2000+:
    //8 LAYER (hard pointer)
    _writer->handleReference(DwgReferenceType.HardPointer, entity.Layer);

    if (entity.LineType.Name == LineType.ByLayerName)
    {
        //Ltype flags BB 00 = bylayer,
        _writer->write2Bits(0b00);
    }
    else if (entity.LineType.Name == LineType.ByBlockName)
    {
        //01 = byblock,
        _writer->write2Bits(0b01);
    }
    else if (entity.LineType.Name == LineType.ContinuousName)
    {
        //10 = continous,
        _writer->write2Bits(0b10);
    }
    else
    {
        //11 = linetype handle present at end of object
        _writer->write2Bits(0b11);
        //6 [LTYPE (hard pointer)] present if linetype flags were 11
        _writer->handleReference(DwgReferenceType.HardPointer, entity.LineType);
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
    _writer->writeBitShort((short) (entity.IsInvisible ? 1 : 0));

    //R2000+:
    //Lineweight RC 370
    _writer->writeByte(CadUtils.ToIndex(entity.LineWeight));
}

void DwgObjectWriter::writeExtendedData(ExtendedDataDictionary *data)
{
    if (WriteXData)
    {
        //EED size BS size of extended entity data, if any
        foreach (var item in data)
        {
            writeExtendedDataEntry(item.Key, item.Value);
        }
    }

    _writer->writeBitShort(0);
}

void DwgObjectWriter::writeExtendedDataEntry(AppId *app, ExtendedData *entry)
{
    using(MemoryStream mstream = new MemoryStream())
    {
        foreach (ExtendedDataRecord record in entry.Records)
        {
            //Each data item has a 1-unsigned char code (DXF group code minus 1000) followed by the value.
            mstream.WriteByte((unsigned char) (record.Code - 1000));

            switch (record)
            {
                case ExtendedDataBinaryChunk binaryChunk:
                    mstream.WriteByte((unsigned char) binaryChunk.Value.Length);
                    mstream.Write(binaryChunk.Value, 0, binaryChunk.Value.Length);
                    break;
                case ExtendedDataControlString control:
                    mstream.WriteByte((unsigned char) (control.Value == '}' ? 1 : 0));
                    break;
                case ExtendedDataInteger16 s16:
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(s16.Value), 0, 2);
                    break;
                case ExtendedDataInteger32 s32:
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(s32.Value), 0, 4);
                    break;
                case ExtendedDataReal real:
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(real.Value), 0, 8);
                    break;
                case ExtendedDataScale scale:
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(scale.Value), 0, 8);
                    break;
                case ExtendedDataDistance dist:
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(dist.Value), 0, 8);
                    break;
                case ExtendedDataDirection dir:
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(dir.Value.X), 0, 8);
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(dir.Value.Y), 0, 8);
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(dir.Value.Z), 0, 8);
                    break;
                case ExtendedDataDisplacement disp:
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(disp.Value.X), 0, 8);
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(disp.Value.Y), 0, 8);
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(disp.Value.Z), 0, 8);
                    break;
                case ExtendedDataCoordinate coord:
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(coord.Value.X), 0, 8);
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(coord.Value.Y), 0, 8);
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(coord.Value.Z), 0, 8);
                    break;
                case ExtendedDataWorldCoordinate wcoord:
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(wcoord.Value.X), 0, 8);
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(wcoord.Value.Y), 0, 8);
                    mstream.Write(LittleEndianConverter.Instance.GetBytes(wcoord.Value.Z), 0, 8);
                    break;
                case IExtendedDataHandleReference handle:
                    unsigned long long h = handle.Value;
                    if (handle.ResolveReference(_document) == null)
                    {
                        h = 0;
                    }
                    mstream.Write(BigEndianConverter.Instance.GetBytes(h), 0, 8);
                    break;
                case ExtendedDataString str:
                    //same as ReadTextUnicode()
                    if (R2007Plus)
                    {
                        mstream.Write(LittleEndianConverter.Instance.GetBytes((ushort) str.Value.Length + 1), 0, 2);
                        unsigned char[] bytes = Encoding.Unicode.GetBytes(str.Value);

                        mstream.Write(bytes, 0, bytes.Length);
                        mstream.WriteByte(0);
                        mstream.WriteByte(0);
                    }
                    else
                    {
                        unsigned char[] bytes =
                                _writer->Encoding.GetBytes(string.IsNullOrEmpty(str.Value) ? string.Empty : str.Value);
                        mstream.Write(LittleEndianConverter.Instance.GetBytes((ushort) str.Value.Length + 1), 0, 2);
                        mstream.Write(bytes, 0, bytes.Length);
                        mstream.WriteByte(0);
                    }
                    break;
                default:
                    throw new System.NotSupportedException(
                            $ "ExtendedDataRecord of type {record.GetType().FullName} not supported.");
            }
        }

        _writer->writeBitShort((short) mstream.Length);

        _writer->Main.HandleReference(DwgReferenceType.HardPointer, app.Handle);

        _writer->writeBytes(mstream.GetBuffer(), 0, (int) mstream.Length);
    }
}

void DwgObjectWriter::writeReactorsAndDictionaryHandle(CadObject *cadObject)
{
    //Numreactors S number of reactors in this object
    cadObject.CleanReactors();
    _writer->writeBitLong(cadObject.Reactors.Count());
    foreach (var item in cadObject.Reactors)
    {
        //[Reactors (soft pointer)]
        _writer->handleReference(DwgReferenceType.SoftPointer, item);
    }

    bool noDictionary = cadObject.XDictionary == null;

    //R2004+:
    if (R2004Plus)
    {
        _writer->writeBit(noDictionary);
        if (!noDictionary)
        {
            _writer->handleReference(DwgReferenceType.HardOwnership, cadObject.XDictionary);
        }
    }
    else
    {
        //xdicobjhandle(hard owner)
        _writer->handleReference(DwgReferenceType.HardOwnership, cadObject.XDictionary);
    }

    //R2013+:
    if (R2013Plus)
    {
        //Has DS binary data B If 1 then this object has associated binary data stored in the data store
        _writer->writeBit(false);
    }

    if (!noDictionary)
    {
        _dictionaries.Add(cadObject.XDictionary.Handle, cadObject.XDictionary);
        _objects.Enqueue(cadObject.XDictionary);
    }
}

unsigned char DwgObjectWriter::getEntMode(Entity *entity)
{
    if (entity.Owner == null)
    {
        return 0;
    }

    if (entity.Owner.Handle == _document.PaperSpace.Handle)
    {
        return 0b01;
    }

    if (entity.Owner.Handle == _document.ModelSpace.Handle)
    {
        return 0b10;
    }

    return 0;
}

}// namespace dwg
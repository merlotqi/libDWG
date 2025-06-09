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
#include <dwg/CadUtils.h>
#include <dwg/blocks/Block.h>
#include <dwg/blocks/BlockEnd.h>
#include <dwg/entities/Insert.h>
#include <dwg/entities/collection/EntityCollection.h>
#include <dwg/header/CadHeader.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/writers/DwgObjectWriter_p.h>
#include <dwg/io/dwg/writers/IDwgStreamWriter_p.h>
#include <dwg/objects/CadDictionary.h>
#include <dwg/objects/Layout.h>
#include <dwg/tables/AppId.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/DimensionStyle.h>
#include <dwg/tables/Layer.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/TextStyle.h>
#include <dwg/tables/UCS.h>
#include <dwg/tables/VPort.h>
#include <dwg/tables/View.h>
#include <dwg/tables/collections/TextStylesTable.h>
#include <dwg/tables/collections/UCSTable.h>
#include <dwg/tables/collections/ViewsTable.h>
#include <dwg/utils/EndianConverter.h>

namespace dwg {

DwgObjectWriter::DwgObjectWriter(std::ostream *stream, CadDocument *document, Encoding encoding, bool writeXRecords,
                                 bool writeXData)
    : DwgSectionIO(document->header()->version())
{
}
DwgObjectWriter::~DwgObjectWriter() {}

std::string DwgObjectWriter::sectionName() const
{
    return DwgSectionDefinition::AcDbObjects;
}

void DwgObjectWriter::write()
{
    //For R18 and later the section data (right after the page header) starts with a
    //RL value of 0x0dca (meaning unknown).
    if (R2004Plus)
    {
        std::vector<unsigned char> arr = LittleEndianConverter::instance()->bytes((int) 0xDCA);
        _stream->write(reinterpret_cast<const char *>(arr.data()), arr.size());
    }

    _objects.push(_document->rootDictionary());

    writeBlockControl();
    writeLayers(_document->layers());
    writeTextStyles(_document->textStyles());
    writeLTypeControlObject();
    writeViews(_document->views());
    writeUCSs(_document->UCSs());
    writeVPorts(_document->vports());
    writeAppIds(_document->appIds());
    //For some reason the dimension must be writen the last
    writeDimensionStyles(_document->dimensionStyles());

    writeBlockEntities();
    writeObjects();
}

std::map<unsigned long long, long long> DwgObjectWriter::handleMap() const
{
    return std::map<unsigned long long, long long>();
}

bool DwgObjectWriter::writeXRecords() const
{
    return false;
}

bool DwgObjectWriter::writeXData() const
{
    return false;
}

void DwgObjectWriter::writeLTypeControlObject() {}

void DwgObjectWriter::writeBlockControl() {}

void DwgObjectWriter::writeLayers(LayersTable *layers) {}

void DwgObjectWriter::writeTextStyles(TextStylesTable *textStyles) {}

void DwgObjectWriter::writeViews(ViewsTable *views) {}

void DwgObjectWriter::writeUCSs(UCSTable *ucss) {}

void DwgObjectWriter::writeVPorts(VPortsTable *vports) {}

void DwgObjectWriter::writeAppIds(AppIdsTable *appids) {}

void DwgObjectWriter::writeDimensionStyles(DimensionStylesTable *dimStyles) {}

void DwgObjectWriter::writeEntries() {}

void DwgObjectWriter::writeBlockEntities() {}

void DwgObjectWriter::writeAppId(AppId *app)
{
    writeCommonNonEntityData(app);

    //Common:
    //Entry name TV 2
    _writer->writeVariableText(app->name());

    writeXrefDependantBit(app);

    //Unknown RC 71 Undoc'd 71-group; doesn't even appear in DXF or an entget if it's 0.
    _writer->writeByte(0);

    //External reference block handle(hard pointer)	??
    _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);

    registerObject(app);
}

void DwgObjectWriter::writeBlockRecord(BlockRecord *blkRecord)
{
    writeBlockHeader(blkRecord);
}

void DwgObjectWriter::writeBlockHeader(BlockRecord *record)
{
    writeCommonNonEntityData(record);

    //Common:
    //Entry name TV 2
    if (record->flags() & BlockTypeFlag::Anonymous)
    {
        //Warning: anonymous blocks do not write the full name, only *{type character}
        _writer->writeVariableText(record->name().substr(0, 2));
    }
    else
    {
        _writer->writeVariableText(record->name());
    }

    writeXrefDependantBit(record);

    //Anonymous B 1 if this is an anonymous block (1 bit)
    _writer->writeBit(record->flags() & BlockTypeFlag::Anonymous);

    //Hasatts B 1 if block contains attdefs (2 bit)
    _writer->writeBit(record->hasAttributes());

    //Blkisxref B 1 if block is xref (4 bit)
    _writer->writeBit(record->flags() & BlockTypeFlag::XRef);

    //Xrefoverlaid B 1 if an overlaid xref (8 bit)
    _writer->writeBit(record->flags() & BlockTypeFlag::XRefOverlay);

    //R2000+:
    if (R2000Plus)
    {
        //Loaded Bit B 0 indicates loaded for an xref
        _writer->writeBit(record->flags() & BlockTypeFlag::XRef);
    }

    //R2004+:
    if ((R2004Plus && !(record->flags() & BlockTypeFlag::XRef)) && !(record->flags() & BlockTypeFlag::XRefOverlay))
    {
        //Owned Object Count BL Number of objects owned by this object.
        _writer->writeBitLong(record->entities()->size());
    }

    //Common:
    //Base pt 3BD 10 Base point of block.
    _writer->write3BitDouble(record->blockEntity()->basePoint());
    //Xref pname TV 1 Xref pathname. That's right: DXF 1 AND 3!
    //3 1 appears in a tblnext/ search elist; 3 appears in an entget.
    _writer->writeVariableText(record->blockEntity()->xrefPath());

    //R2000+:
    if (R2000Plus)
    {
        //Insert Count RC A sequence of zero or more non-zero RC's, followed by a terminating 0 RC.The total number of these indicates how many insert handles will be present.
        for (auto item = record->entities()->begin(); item != record->entities()->end(); ++item)
        {
            auto insert = dynamic_cast<Insert *>(*item);
            if (insert && insert->block()->name() == record->name())
            {
                _writer->writeByte(1);
            }
        }

        _writer->writeByte(0);

        //Block Description TV 4 Block description.
        _writer->writeVariableText(record->blockEntity()->comments());

        //Size of preview data BL Indicates number of bytes of data following.
        _writer->writeBitLong(0);
    }

    //R2007+:
    if (R2007Plus)
    {
        //Insert units BS 70
        _writer->writeBitShort((short) record->units());
        //Explodable B 280
        _writer->writeBit(record->isExplodable());
        //Block scaling RC 281
        _writer->writeByte((unsigned char) (record->canScale() ? 1 : 0));
    }

    //NULL(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
    //BLOCK entity. (hard owner)
    //Block begin object
    _writer->handleReference(DwgReferenceType::HardOwnership, record->blockEntity());

    //R13-R2000:
    if (_version >= ACadVersion::AC1012 && _version <= ACadVersion::AC1015 &&
        !(record->flags() & BlockTypeFlag::XRef) && !(record->flags() & BlockTypeFlag::XRefOverlay))
    {
        if (!record->entities()->empty())
        {
            //first entity in the def. (soft pointer)
            _writer->handleReference(DwgReferenceType::SoftPointer, record->entities()->front());
            //last entity in the def. (soft pointer)
            _writer->handleReference(DwgReferenceType::SoftPointer, record->entities()->back());
        }
        else
        {
            _writer->handleReference(DwgReferenceType::SoftPointer, 0ULL);
            _writer->handleReference(DwgReferenceType::SoftPointer, 0ULL);
        }
    }

    //R2004+:
    if (R2004Plus)
    {
        for (auto it = record->entities()->begin(); it != record->entities()->end(); ++it)
        {
            //H[ENTITY(hard owner)] Repeats "Owned Object Count" times.
            _writer->handleReference(DwgReferenceType::HardOwnership, *it);
        }
    }

    //Common:
    //ENDBLK entity. (hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, record->blockEnd());

    //R2000+:
    if (R2000Plus)
    {
        for (auto item = record->entities()->begin(); item != record->entities()->end(); ++item)
        {
            auto insert = dynamic_cast<Insert *>(*item);
            if (insert && insert->block()->name() == record->name())
            {
                _writer->handleReference(DwgReferenceType::SoftPointer, *item);
            }
        }

        //Layout Handle H(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, record->layout());
    }

    registerObject(record);
}

void DwgObjectWriter::writeBlockBegin(Block *block)
{
    writeCommonEntityData(block);

    //Common:
    //Entry name TV 2
    _writer->writeVariableText(block->name());

    registerObject(block);
}

void DwgObjectWriter::writeBlockEnd(BlockEnd *blkEnd)
{
    writeCommonEntityData(blkEnd);

    registerObject(blkEnd);
}

void DwgObjectWriter::writeLayer(Layer *layer)
{
    writeCommonNonEntityData(layer);

    //Common:
    //Entry name TV 2
    _writer->writeVariableText(layer->name());

    writeXrefDependantBit(layer);

    //R13-R14 Only:
    if (R13_14Only)
    {
        //Frozen B 70 if frozen (1 bit)
        _writer->writeBit(layer->flags() & LayerFlag::Frozen);
        //On B if on.
        _writer->writeBit(layer->isOn());
        //Frz in new B 70 if frozen by default in new viewports (2 bit)
        _writer->writeBit(layer->flags() & LayerFlag::FrozenNewViewports);
        //Locked B 70 if locked (4 bit)
        _writer->writeBit(layer->flags() & LayerFlag::Locked);
    }

    //R2000+:
    if (R2000Plus)
    {
        //and lineweight (mask with 0x03E0)
        short values = (short) (CadUtils::ToIndex(layer->lineWeight()) << 5);

        //contains frozen (1 bit),
        if (layer->flags() & LayerFlag::Frozen)
            values |= 0b1;

        //on (2 bit)
        if (!layer->isOn())
            values |= 0b10;

        //frozen by default in new viewports (4 bit)
        if (layer->flags() & LayerFlag::Frozen)
            values |= 0b100;

        //locked (8 bit)
        if (layer->flags() & LayerFlag::Locked)
            values |= 0b1000;

        //plotting flag (16 bit),
        if (layer->plotFlag())
            values |= 0b10000;

        //Values BS 70,290,370
        _writer->writeBitShort(values);
    }

    //Common:
    //Color CMC 62
    _writer->writeCmColor(layer->color());

    //External reference block handle(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, nullptr);

    //R2000+:
    if (R2000Plus)
    {
        //H 390 Plotstyle (hard pointer), by default points to PLACEHOLDER with handle 0x0f.
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
    }

    //R2007+:
    if (R2007Plus)
    {
        //H 347 Material
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
    }

    //Common:
    //H 6 linetype (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, layer->lineType()->handle());

    if (R2013Plus)
    {
        //H Unknown handle (hard pointer). Always seems to be NULL.
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
    }

    registerObject(layer);
}

void DwgObjectWriter::writeLineType(LineType *ltype)
{
    writeCommonNonEntityData(ltype);

    //Common:
    //Entry name TV 2
    _writer->writeVariableText(ltype->name());

    writeXrefDependantBit(ltype);

    //Description TV 3
    _writer->writeVariableText(ltype->description());
    //Pattern Len BD 40
    _writer->writeBitDouble(ltype->patternLen());
    //Alignment RC 72 Always 'A'.
    _writer->writeByte((unsigned char) ltype->alignment());

    //Numdashes RC 73 The number of repetitions of the 49...74 data.
    _writer->writeByte((unsigned char) ltype->segments().size());
    bool isText = false;
    for (auto &&segment: ltype->segments())
    {
        //Dash length BD 49 Dash or dot specifier.
        _writer->writeBitDouble(segment.length);
        //Complex shapecode BS 75 Shape number if shapeflag is 2, or index into the string area if shapeflag is 4.
        _writer->writeBitShort(segment.shapeNumber);

        //X - offset RD 44 (0.0 for a simple dash.)
        //Y - offset RD 45(0.0 for a simple dash.)
        _writer->writeRawDouble(segment.offset.X);
        _writer->writeRawDouble(segment.offset.Y);

        //Scale BD 46 (1.0 for a simple dash.)
        _writer->writeBitDouble(segment.scale);
        //Rotation BD 50 (0.0 for a simple dash.)
        _writer->writeBitDouble(segment.rotation);
        //Shapeflag BS 74 bit coded:
        _writer->writeBitShort((short) segment.shapeFlag);

        if (segment.shapeFlag.testFlag(LinetypeShapeFlag::Text))
            isText = true;
    }

    //R2004 and earlier:
    if (_version <= ACadVersion::AC1018)
    {
        //Strings area X 9 256 bytes of text area. The complex dashes that have text use this area via the 75-group indices. It's basically a pile of 0-terminated strings.
        //First unsigned char is always 0 for R13 and data starts at unsigned char 1.
        //In R14 it is not a valid data start from unsigned char 0.
        //(The 9 - group is undocumented.)
        for (int i = 0; i < 256; i++)
        {
            //TODO: Write the line type text area
            _writer->writeByte(0);
        }
    }

    //R2007+:
    if (R2007Plus && isText)
    {
        for (int i = 0; i < 512; i++)
        {
            //TODO: Write the line type text area
            _writer->writeByte(0);
        }
    }

    //Common:
    //External reference block handle(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);

    for (auto &&segment: ltype->segments())
    {
        //340 shapefile for dash/shape (1 each) (hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, segment.style);
    }

    registerObject(ltype);
}

void DwgObjectWriter::writeTextStyle(TextStyle *style)
{
    writeCommonNonEntityData(style);

    //Common:
    //Entry name TV 2
    if (style->isShapeFile())
    {
        _writer->writeVariableText("");
    }
    else
    {
        _writer->writeVariableText(style->name());
    }

    writeXrefDependantBit(style);

    //shape file B 1 if a shape file rather than a font (1 bit)
    _writer->writeBit(style->flags().testFlag(StyleFlag::IsShape));

    //Vertical B 1 if vertical (4 bit of flag)
    _writer->writeBit(style->flags().testFlag(StyleFlag::VerticalText));
    //Fixed height BD 40
    _writer->writeBitDouble(style->height());
    //Width factor BD 41
    _writer->writeBitDouble(style->width());
    //Oblique ang BD 50
    _writer->writeBitDouble(style->obliqueAngle());
    //Generation RC 71 Generation flags (not bit-pair coded).
    _writer->writeByte((unsigned char) style->mirrorFlag());
    //Last height BD 42
    _writer->writeBitDouble(style->lastHeight());
    //Font name TV 3
    _writer->writeVariableText(style->filename());
    //Bigfont name TV 4
    _writer->writeVariableText(style->bigFontFilename());

    _writer->handleReference(DwgReferenceType::HardPointer, _document->textStyles());

    registerObject(style);
}

void DwgObjectWriter::writeUCS(UCS *ucs)
{
    writeCommonNonEntityData(ucs);

    //Common:
    //Entry name TV 2
    _writer->writeVariableText(ucs->name());

    writeXrefDependantBit(ucs);

    //Origin 3BD 10
    _writer->write3BitDouble(ucs->origin());
    //X - direction 3BD 11
    _writer->write3BitDouble(ucs->xAxis());
    //Y - direction 3BD 12
    _writer->write3BitDouble(ucs->yAxis());

    //R2000+:
    if (R2000Plus)
    {
        //Elevation BD 146
        _writer->writeBitDouble(ucs->elevation());
        //OrthographicViewType BS 79	//dxf docs: 79	Always 0
        _writer->writeBitShort((short) ucs->orthographicViewType());
        //OrthographicType BS 71
        _writer->writeBitShort((short) ucs->orthographicType());
    }

    //Common:
    //Handle refs H ucs control object (soft pointer)
    _writer->handleReference(DwgReferenceType::SoftPointer, _document->UCSs());

    //R2000 +:
    if (R2000Plus)
    {
        //Base UCS Handle H 346 hard pointer
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //Named UCS Handle H -hard pointer, not present in DXF
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
    }

    registerObject(ucs);
}

void DwgObjectWriter::writeView(View *view)
{
    writeCommonNonEntityData(view);

    //Common:
    //Entry name TV 2
    _writer->writeVariableText(view->name());

    writeXrefDependantBit(view);

    //View height BD 40
    _writer->writeBitDouble(view->height());
    //View width BD 41
    _writer->writeBitDouble(view->width());
    //View center 2RD 10(Not bit - pair coded.)
    _writer->write2RawDouble(view->center());
    //Target 3BD 12
    _writer->write3BitDouble(view->target());
    //View dir 3BD 11 DXF doc suggests from target toward camera.
    _writer->write3BitDouble(view->direction());
    //Twist angle BD 50 Radians
    _writer->writeBitDouble(view->angle());
    //Lens length BD 42
    _writer->writeBitDouble(view->lensLength());
    //Front clip BD 43
    _writer->writeBitDouble(view->frontClipping());
    //Back clip BD 44
    _writer->writeBitDouble(view->backClipping());

    //View mode X 71 4 bits: 0123
    //Note that only bits 0, 1, 2, and 4 of the 71 can be specified -- not bit 3 (8).
    //0 : 71's bit 0 (1)
    _writer->writeBit(view->viewMode().testFlag(ViewModeType::PerspectiveView));
    //1 : 71's bit 1 (2)
    _writer->writeBit(view->viewMode().testFlag(ViewModeType::FrontClipping));
    //2 : 71's bit 2 (4)
    _writer->writeBit(view->viewMode().testFlag(ViewModeType::BackClipping));
    //3 : OPPOSITE of 71's bit 4 (16)
    _writer->writeBit(view->viewMode().testFlag(ViewModeType::FrontClippingZ));

    //R2000+:
    if (R2000Plus)
    {
        //Render Mode RC 281
        _writer->writeByte((unsigned char) view->renderMode());
    }

    //R2007+:
    if (R2007Plus)
    {
        //Use default lights B ? Default value is true
        _writer->writeBit(true);
        //Default lighting RC ? Default value is 1
        _writer->writeByte(1);
        //Brightness BD ? Default value is 0
        _writer->writeBitDouble(0.0);
        //Contrast BD ? Default value is 0
        _writer->writeBitDouble(0.0);
        //Abient color CMC? Default value is indexed color 250
        _writer->writeCmColor(Color((short) 250));
    }

    //Common:
    //Pspace flag B 70 Bit 0(1) of the 70 - group.
    _writer->writeBit(view->flags().testFlag((StandardFlag) 0b1));

    if (R2000Plus)
    {
        _writer->writeBit(view->isUcsAssociated());
        if (view->isUcsAssociated())
        {
            //Origin 3BD 10 This and next 4 R2000 items are present only if 72 value is 1.
            _writer->write3BitDouble(view->ucsOrigin());
            //X-direction 3BD 11
            _writer->write3BitDouble(view->ucsXAxis());
            //Y-direction 3BD 12
            _writer->write3BitDouble(view->ucsYAxis());
            //Elevation BD 146
            _writer->writeBitDouble(view->ucsElevation());
            //OrthographicViewType BS 79
            _writer->writeBitShort((short) view->ucsOrthographicType());
        }
    }

    //Common:
    //Handle refs H view control object (soft pointer)
    _writer->handleReference(DwgReferenceType::SoftPointer, _document->views());

    //R2007+:
    if (R2007Plus)
    {
        //Camera plottable B 73
        _writer->writeBit(view->isPlottable());

        //Background handle H 332 soft pointer
        _writer->handleReference(DwgReferenceType::SoftPointer, 0ULL);
        //Visual style H 348 hard pointer
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //Sun H 361 hard owner
        _writer->handleReference(DwgReferenceType::HardOwnership, 0ULL);
    }

    if (R2000Plus && view->isUcsAssociated())
    {
        //TODO: Implement ucs reference for view
        //Base UCS Handle H 346 hard pointer
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //Named UCS Handle H 345 hard pointer
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
    }

    //R2007+:
    if (R2007Plus)
    {
        //Live section H 334 soft pointer
        _writer->handleReference(DwgReferenceType::SoftPointer, 0ULL);
    }

    registerObject(view);
}

void DwgObjectWriter::writeDimensionStyle(DimensionStyle *dimStyle)
{
    writeCommonNonEntityData(dimStyle);

    //Common:
    //Entry name TV 2
    _writer->writeVariableText(dimStyle->name());

    writeXrefDependantBit(dimStyle);

    //R13 & R14 Only:
    if (R13_14Only)
    {
        //DIMTOL B 71
        _writer->writeBit(dimStyle->generateTolerances());
        //DIMLIM B 72
        _writer->writeBit(dimStyle->limitsGeneration());
        //DIMTIH B 73
        _writer->writeBit(dimStyle->textOutsideHorizontal());
        //DIMTOH B 74
        _writer->writeBit(dimStyle->suppressFirstExtensionLine());
        //DIMSE1 B 75
        _writer->writeBit(dimStyle->suppressSecondExtensionLine());
        //DIMSE2 B 76
        _writer->writeBit(dimStyle->textInsideHorizontal());
        //DIMALT B 170
        _writer->writeBit(dimStyle->alternateUnitDimensioning());
        //DIMTOFL B 172
        _writer->writeBit(dimStyle->textOutsideExtensions());
        //DIMSAH B 173
        _writer->writeBit(dimStyle->separateArrowBlocks());
        //DIMTIX B 174
        _writer->writeBit(dimStyle->textInsideExtensions());
        //DIMSOXD B 175
        _writer->writeBit(dimStyle->suppressOutsideExtensions());
        //DIMALTD RC 171
        _writer->writeByte((unsigned char) dimStyle->alternateUnitDecimalPlaces());
        //DIMZIN RC 78
        _writer->writeByte((unsigned char) dimStyle->zeroHandling());
        //DIMSD1 B 281
        _writer->writeBit(dimStyle->suppressFirstDimensionLine());
        //DIMSD2 B 282
        _writer->writeBit(dimStyle->suppressSecondDimensionLine());
        //DIMTOLJ RC 283
        _writer->writeByte((unsigned char) dimStyle->toleranceAlignment());
        //DIMJUST RC 280
        _writer->writeByte((unsigned char) dimStyle->textHorizontalAlignment());
        //DIMFIT RC 287
        _writer->writeByte((unsigned char) dimStyle->dimensionFit());
        //DIMUPT B 288
        _writer->writeBit(dimStyle->cursorUpdate());
        //DIMTZIN RC 284
        _writer->writeByte((unsigned char) dimStyle->toleranceZeroHandling());
        //DIMALTZ RC 285
        _writer->writeByte((unsigned char) dimStyle->alternateUnitZeroHandling());
        //DIMALTTZ RC 286
        _writer->writeByte((unsigned char) dimStyle->alternateUnitToleranceZeroHandling());
        //DIMTAD RC 77
        _writer->writeByte((unsigned char) dimStyle->textVerticalAlignment());
        //DIMUNIT BS 270
        _writer->writeBitShort(dimStyle->dimensionUnit());
        //DIMAUNIT BS 275
        _writer->writeBitShort((short) dimStyle->angularUnit());
        //DIMDEC BS 271
        _writer->writeBitShort(dimStyle->decimalPlaces());
        //DIMTDEC BS 272
        _writer->writeBitShort(dimStyle->toleranceDecimalPlaces());
        //DIMALTU BS 273
        _writer->writeBitShort((short) dimStyle->alternateUnitFormat());
        //DIMALTTD BS 274
        _writer->writeBitShort(dimStyle->alternateUnitToleranceDecimalPlaces());
        //DIMSCALE BD 40
        _writer->writeBitDouble(dimStyle->scaleFactor());
        //DIMASZ BD 41
        _writer->writeBitDouble(dimStyle->arrowSize());
        //DIMEXO BD 42
        _writer->writeBitDouble(dimStyle->extensionLineOffset());
        //DIMDLI BD 43
        _writer->writeBitDouble(dimStyle->dimensionLineIncrement());
        //DIMEXE BD 44
        _writer->writeBitDouble(dimStyle->extensionLineExtension());
        //DIMRND BD 45
        _writer->writeBitDouble(dimStyle->rounding());
        //DIMDLE BD 46
        _writer->writeBitDouble(dimStyle->dimensionLineExtension());
        //DIMTP BD 47
        _writer->writeBitDouble(dimStyle->plusTolerance());
        //DIMTM BD 48
        _writer->writeBitDouble(dimStyle->minusTolerance());
        //DIMTXT BD 140
        _writer->writeBitDouble(dimStyle->textHeight());
        //DIMCEN BD 141
        _writer->writeBitDouble(dimStyle->centerMarkSize());
        //DIMTSZ BD 142
        _writer->writeBitDouble(dimStyle->tickSize());
        //DIMALTF BD 143
        _writer->writeBitDouble(dimStyle->alternateUnitScaleFactor());
        //DIMLFAC BD 144
        _writer->writeBitDouble(dimStyle->linearScaleFactor());
        //DIMTVP BD 145
        _writer->writeBitDouble(dimStyle->textVerticalPosition());
        //DIMTFAC BD 146
        _writer->writeBitDouble(dimStyle->toleranceScaleFactor());
        //DIMGAP BD 147
        _writer->writeBitDouble(dimStyle->dimensionLineGap());

        //DIMPOST T 3
        _writer->writeVariableText(dimStyle->postFix());
        //DIMAPOST T 4
        _writer->writeVariableText(dimStyle->alternateDimensioningSuffix());

        //DIMBLK T 5
        _writer->writeVariableText(dimStyle->arrowBlock()->name());
        //DIMBLK1 T 6
        _writer->writeVariableText(dimStyle->dimArrow1()->name());
        //DIMBLK2 T 7
        _writer->writeVariableText(dimStyle->dimArrow1()->name());

        //DIMCLRD BS 176
        _writer->writeCmColor(dimStyle->dimensionLineColor());
        //DIMCLRE BS 177
        _writer->writeCmColor(dimStyle->extensionLineColor());
        //DIMCLRT BS 178
        _writer->writeCmColor(dimStyle->textColor());
    }

    //R2000+:
    if (R2000Plus)
    {
        //DIMPOST TV 3
        _writer->writeVariableText(dimStyle->postFix());
        //DIMAPOST TV 4
        _writer->writeVariableText(dimStyle->alternateDimensioningSuffix());
        //DIMSCALE BD 40
        _writer->writeBitDouble(dimStyle->scaleFactor());
        //DIMASZ BD 41
        _writer->writeBitDouble(dimStyle->arrowSize());
        //DIMEXO BD 42
        _writer->writeBitDouble(dimStyle->extensionLineOffset());
        //DIMDLI BD 43
        _writer->writeBitDouble(dimStyle->dimensionLineIncrement());
        //DIMEXE BD 44
        _writer->writeBitDouble(dimStyle->extensionLineExtension());
        //DIMRND BD 45
        _writer->writeBitDouble(dimStyle->rounding());
        //DIMDLE BD 46
        _writer->writeBitDouble(dimStyle->dimensionLineExtension());
        //DIMTP BD 47
        _writer->writeBitDouble(dimStyle->plusTolerance());
        //DIMTM BD 48
        _writer->writeBitDouble(dimStyle->minusTolerance());
    }

    //R2007+:
    if (R2007Plus)
    {
        //DIMFXL BD 49
        _writer->writeBitDouble(dimStyle->fixedExtensionLineLength());
        //DIMJOGANG BD 50
        _writer->writeBitDouble(dimStyle->joggedRadiusDimensionTransverseSegmentAngle());
        //DIMTFILL BS 69
        _writer->writeBitShort((short) dimStyle->textBackgroundFillMode());
        //DIMTFILLCLR CMC 70
        _writer->writeCmColor(dimStyle->textBackgroundColor());
    }

    //R2000+:
    if (R2000Plus)
    {
        //DIMTOL B 71
        _writer->writeBit(dimStyle->generateTolerances());
        //DIMLIM B 72
        _writer->writeBit(dimStyle->limitsGeneration());
        //DIMTIH B 73
        _writer->writeBit(dimStyle->textInsideHorizontal());
        //DIMTOH B 74
        _writer->writeBit(dimStyle->textOutsideHorizontal());
        //DIMSE1 B 75
        _writer->writeBit(dimStyle->suppressFirstExtensionLine());
        //DIMSE2 B 76
        _writer->writeBit(dimStyle->suppressSecondExtensionLine());
        //DIMTAD BS 77
        _writer->writeBitShort((short) dimStyle->textVerticalAlignment());
        //DIMZIN BS 78
        _writer->writeBitShort((short) dimStyle->zeroHandling());
        //DIMAZIN BS 79
        _writer->writeBitShort((short) dimStyle->angularZeroHandling());
    }

    //R2007 +:
    if (R2007Plus)
    {
        //DIMARCSYM BS 90
        _writer->writeBitShort((short) dimStyle->arcLengthSymbolPosition());
    }

    //R2000 +:
    if (R2000Plus)
    {
        //DIMTXT BD 140
        _writer->writeBitDouble(dimStyle->textHeight());
        //DIMCEN BD 141
        _writer->writeBitDouble(dimStyle->centerMarkSize());
        //DIMTSZ BD 142
        _writer->writeBitDouble(dimStyle->tickSize());
        //DIMALTF BD 143
        _writer->writeBitDouble(dimStyle->alternateUnitScaleFactor());
        //DIMLFAC BD 144
        _writer->writeBitDouble(dimStyle->linearScaleFactor());
        //DIMTVP BD 145
        _writer->writeBitDouble(dimStyle->textVerticalPosition());
        //DIMTFAC BD 146
        _writer->writeBitDouble(dimStyle->toleranceScaleFactor());
        //DIMGAP BD 147
        _writer->writeBitDouble(dimStyle->dimensionLineGap());
        //DIMALTRND BD 148
        _writer->writeBitDouble(dimStyle->alternateUnitRounding());
        //DIMALT B 170
        _writer->writeBit(dimStyle->alternateUnitDimensioning());
        //DIMALTD BS 171
        _writer->writeBitShort(dimStyle->alternateUnitDecimalPlaces());
        //DIMTOFL B 172
        _writer->writeBit(dimStyle->textOutsideExtensions());
        //DIMSAH B 173
        _writer->writeBit(dimStyle->separateArrowBlocks());
        //DIMTIX B 174
        _writer->writeBit(dimStyle->textInsideExtensions());
        //DIMSOXD B 175
        _writer->writeBit(dimStyle->suppressOutsideExtensions());
        //DIMCLRD BS 176
        _writer->writeCmColor(dimStyle->dimensionLineColor());
        //DIMCLRE BS 177
        _writer->writeCmColor(dimStyle->extensionLineColor());
        //DIMCLRT BS 178
        _writer->writeCmColor(dimStyle->textColor());
        //DIMADEC BS 179
        _writer->writeBitShort(dimStyle->angularDimensionDecimalPlaces());
        //DIMDEC BS 271
        _writer->writeBitShort(dimStyle->decimalPlaces());
        //DIMTDEC BS 272
        _writer->writeBitShort(dimStyle->toleranceDecimalPlaces());
        //DIMALTU BS 273
        _writer->writeBitShort((short) dimStyle->alternateUnitFormat());
        //DIMALTTD BS 274
        _writer->writeBitShort(dimStyle->alternateUnitToleranceDecimalPlaces());
        //DIMAUNIT BS 275
        _writer->writeBitShort((short) dimStyle->angularUnit());
        //DIMFRAC BS 276
        _writer->writeBitShort((short) dimStyle->fractionFormat());
        //DIMLUNIT BS 277
        _writer->writeBitShort((short) dimStyle->linearUnitFormat());
        //DIMDSEP BS 278
        _writer->writeBitShort((short) dimStyle->decimalSeparator());
        //DIMTMOVE BS 279
        _writer->writeBitShort((short) dimStyle->textMovement());
        //DIMJUST BS 280
        _writer->writeBitShort((short) dimStyle->textHorizontalAlignment());
        //DIMSD1 B 281
        _writer->writeBit(dimStyle->suppressFirstDimensionLine());
        //DIMSD2 B 282
        _writer->writeBit(dimStyle->suppressSecondDimensionLine());
        //DIMTOLJ BS 283
        _writer->writeBitShort((short) dimStyle->toleranceAlignment());
        //DIMTZIN BS 284
        _writer->writeBitShort((short) dimStyle->toleranceZeroHandling());
        //DIMALTZ BS 285
        _writer->writeBitShort((short) dimStyle->alternateUnitZeroHandling());
        //DIMALTTZ BS 286
        _writer->writeBitShort((short) dimStyle->alternateUnitToleranceZeroHandling());
        //DIMUPT B 288
        _writer->writeBit(dimStyle->cursorUpdate());
        //DIMFIT BS 287
        _writer->writeBitShort(3);
    }

    //R2007+:
    if (R2007Plus)
    {
        //DIMFXLON B 290
        _writer->writeBit(dimStyle->isExtensionLineLengthFixed());
    }

    //R2010+:
    if (R2010Plus)
    {
        //DIMTXTDIRECTION B 295
        _writer->writeBit(dimStyle->textDirection() == TextDirection::RightToLeft);
        //DIMALTMZF BD ?
        _writer->writeBitDouble(dimStyle->altMzf());
        //DIMALTMZS T ?
        _writer->writeVariableText(dimStyle->altMzs());
        //DIMMZF BD ?
        _writer->writeBitDouble(dimStyle->mzf());
        //DIMMZS T ?
        _writer->writeVariableText(dimStyle->mzs());
    }

    //R2000+:
    if (R2000Plus)
    {
        //DIMLWD BS 371
        _writer->writeBitShort((short) dimStyle->dimensionLineWeight());
        //DIMLWE BS 372
        _writer->writeBitShort((short) dimStyle->extensionLineWeight());
    }

    //Common:
    //Unknown B 70 Seems to set the 0 - bit(1) of the 70 - group.
    _writer->writeBit(false);

    //Handle refs H Dimstyle control(soft pointer)
    //[Reactors(soft pointer)]
    //xdicobjhandle(hard owner)

    //External reference block handle(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);

    //340 shapefile(DIMTXSTY)(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, dimStyle->style());

    //R2000+:
    if (R2000Plus)
    {
        //341 leader block(DIMLDRBLK) (hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, dimStyle->leaderArrow());
        //342 dimblk(DIMBLK)(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, dimStyle->arrowBlock());
        //343 dimblk1(DIMBLK1)(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, dimStyle->dimArrow1());
        //344 dimblk2(DIMBLK2)(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, dimStyle->dimArrow2());
    }

    //R2007+:
    if (R2007Plus)
    {
        //345 dimltype(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, dimStyle->lineType());
        //346 dimltex1(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, dimStyle->lineTypeExt1());
        //347 dimltex2(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, dimStyle->lineTypeExt2());
    }

    registerObject(dimStyle);
}

void DwgObjectWriter::writeVPort(VPort *vport)
{
    writeCommonNonEntityData(vport);

    //Common:
    //Entry name TV 2
    _writer->writeVariableText(vport->name());

    writeXrefDependantBit(vport);

    //View height BD 40
    _writer->writeBitDouble(vport->viewHeight());
    //Aspect ratio BD 41 The number stored here is actually the aspect ratio times the view height (40),
    //so this number must be divided by the 40-value to produce the aspect ratio that entget gives.
    //(R13 quirk; R12 has just the aspect ratio.)
    _writer->writeBitDouble(vport->aspectRatio() * vport->viewHeight());
    //View Center 2RD 12 DCS. (If it's plan view, add the view target (17) to get the WCS coordinates.
    //Careful! Sometimes you have to SAVE/OPEN to update the .dwg file.) Note that it's WSC in R12.
    _writer->write2RawDouble(vport->center());
    //View target 3BD 17
    _writer->write3BitDouble(vport->target());
    //View dir 3BD 16
    _writer->write3BitDouble(vport->direction());
    //View twist BD 51
    _writer->writeBitDouble(vport->twistAngle());
    //Lens length BD 42
    _writer->writeBitDouble(vport->lensLength());
    //Front clip BD 43
    _writer->writeBitDouble(vport->frontClippingPlane());
    //Back clip BD 44
    _writer->writeBitDouble(vport->backClippingPlane());

    //View mode X 71 4 bits: 0123
    //Note that only bits 0, 1, 2, and 4 are given here; see UCSFOLLOW below for bit 3(8) of the 71.
    //0 : 71's bit 0 (1)
    _writer->writeBit(vport->viewMode().testFlag(ViewModeType::PerspectiveView));
    //1 : 71's bit 1 (2)
    _writer->writeBit(vport->viewMode().testFlag(ViewModeType::FrontClipping));
    //2 : 71's bit 2 (4)
    _writer->writeBit(vport->viewMode().testFlag(ViewModeType::BackClipping));
    //3 : OPPOSITE of 71's bit 4 (16)
    _writer->writeBit(vport->viewMode().testFlag(ViewModeType::FrontClippingZ));

    //R2000+:
    if (R2000Plus)
    {
        //Render Mode RC 281
        _writer->writeByte((unsigned char) vport->renderMode());
    }

    //R2007+:
    if (R2007Plus)
    {
        //Use default lights B 292
        _writer->writeBit(vport->useDefaultLighting());
        //Default lighting type RC 282
        _writer->writeByte((unsigned char) vport->defaultLighting());
        //Brightness BD 141
        _writer->writeBitDouble(vport->brightness());
        //Constrast BD 142
        _writer->writeBitDouble(vport->contrast());
        //Ambient Color CMC 63
        _writer->writeCmColor(vport->ambientColor());
    }

    //Common:
    //Lower left 2RD 10 In fractions of screen width and height.
    _writer->write2RawDouble(vport->bottomLeft());
    //Upper right 2RD 11 In fractions of screen width and height.
    _writer->write2RawDouble(vport->topRight());

    //UCSFOLLOW B 71 UCSFOLLOW. Bit 3 (8) of the 71-group.
    _writer->writeBit(vport->viewMode().testFlag(ViewModeType::Follow));

    //Circle zoom BS 72 Circle zoom percent.
    _writer->writeBitShort(vport->circleZoomPercent());

    //Fast zoom B 73
    _writer->writeBit(true);

    //UCSICON X 74 2 bits: 01
    //0 : 74's bit 0 (1)
    _writer->writeBit(vport->ucsIconDisplay() & UscIconType::OnLower);

    //1 : 74's bit 1 (2)
    _writer->writeBit(vport->ucsIconDisplay() & UscIconType::OnOrigin);

    //Grid on/off B 76
    _writer->writeBit(vport->showGrid());
    //Grd spacing 2RD 15
    _writer->write2RawDouble(vport->gridSpacing());
    //Snap on/off B 75
    _writer->writeBit(vport->snapOn());

    //Snap style B 77
    _writer->writeBit(vport->isometricSnap());

    //Snap isopair BS 78
    _writer->writeBitShort(vport->snapIsoPair());
    //Snap rot BD 50
    _writer->writeBitDouble(vport->snapRotation());
    //Snap base 2RD 13
    _writer->write2RawDouble(vport->snapBasePoint());
    //Snp spacing 2RD 14
    _writer->write2RawDouble(vport->snapSpacing());

    //R2000+:
    if (R2000Plus)
    {
        //Unknown B
        _writer->writeBit(false);

        //UCS per Viewport B 71
        _writer->writeBit(true);
        //UCS Origin 3BD 110
        _writer->write3BitDouble(vport->origin());
        //UCS X Axis 3BD 111
        _writer->write3BitDouble(vport->xAxis());
        //UCS Y Axis 3BD 112
        _writer->write3BitDouble(vport->yAxis());
        //UCS Elevation BD 146
        _writer->writeBitDouble(vport->elevation());
        //UCS Orthographic type BS 79
        _writer->writeBitShort((short) vport->orthographicType());
    }

    //R2007+:
    if (R2007Plus)
    {
        //Grid flags BS 60
        _writer->writeBitShort((short) vport->gridFlags());
        //Grid major BS 61
        _writer->writeBitShort(vport->minorGridLinesPerMajorGridLine());
    }

    //Common:
    //External reference block handle(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);

    //R2007+:
    if (R2007Plus)
    {
        //Background handle H 332 soft pointer
        _writer->handleReference(DwgReferenceType::SoftPointer, 0ULL);
        //Visual Style handle H 348 hard pointer
        _writer->handleReference(DwgReferenceType::SoftPointer, 0ULL);
        //Sun handle H 361 hard owner
        _writer->handleReference(DwgReferenceType::SoftPointer, 0ULL);
    }

    //R2000+:
    if (R2000Plus)
    {
        if (vport->orthographicType() == OrthographicType::None)
        {
            //Named UCS Handle H 345 hard pointer
            _writer->handleReference(DwgReferenceType::HardPointer, vport->namedUcs());
            //Base UCS Handle H 346 hard pointer
            _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        }
        else
        {
            //Named UCS Handle H 345 hard pointer
            _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
            //Base UCS Handle H 346 hard pointer
            _writer->handleReference(DwgReferenceType::HardPointer, vport->baseUcs());
        }
    }

    registerObject(vport);
}

}// namespace dwg
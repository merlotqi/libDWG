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

#include <dwg/CadUtils.h>
#include <dwg/GroupCodeValue.h>
#include <dwg/entities/Entity.h>
#include <dwg/entities/Viewport.h>
#include <dwg/io/dwg/writers/DwgObjectWriter_p.h>
#include <dwg/io/dwg/writers/IDwgStreamWriter_p.h>
#include <dwg/objects/BookColor.h>
#include <dwg/objects/CadDictionary.h>
#include <dwg/objects/CadDictionaryWithDefault.h>
#include <dwg/objects/DictionaryVariable.h>
#include <dwg/objects/GeoData.h>
#include <dwg/objects/Group.h>
#include <dwg/objects/ImageDefinition.h>
#include <dwg/objects/ImageDefinitionReactor.h>
#include <dwg/objects/Layout.h>
#include <dwg/objects/MLineStyle.h>
#include <dwg/objects/MultiLeaderStyle.h>
#include <dwg/objects/NonGraphicalObject.h>
#include <dwg/objects/PlotSettings.h>
#include <dwg/objects/Scale.h>
#include <dwg/objects/SortEntitiesTable.h>
#include <dwg/objects/XRecord.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/UCS.h>
#include <dwg/utils/EndianConverter.h>
#include <dwg/utils/StreamWrapper.h>

namespace dwg {

void DwgObjectWriter::writeObjects() {}

void DwgObjectWriter::writeObject(CadObject *obj) {}

void DwgObjectWriter::writeAcdbPlaceHolder(AcdbPlaceHolder *acdbPlaceHolder) {}

void DwgObjectWriter::writeBookColor(BookColor *color)
{
    _writer->writeBitShort(0);

    if (R2004Plus)
    {
        unsigned char arr[4] = {color->color().blue(), color->color().green(), color->color().red(), 0b11000010};

        unsigned int rgb = LittleEndianConverter::instance()->toUInt32(arr);

        _writer->writeBitLong((int) rgb);

        unsigned char flags = 0;
        if (!color->colorName().empty())
        {
            flags = (unsigned char) (flags | 1u);
        }

        if (!color->bookName().empty())
        {
            flags = (unsigned char) (flags | 2u);
        }

        _writer->writeByte(flags);
        if (!color->colorName().empty())
        {
            _writer->writeVariableText(color->colorName());
        }

        if (!color->bookName().empty())
        {
            _writer->writeVariableText(color->bookName());
        }
    }
}

void DwgObjectWriter::writeCadDictionaryWithDefault(CadDictionaryWithDefault *dictionary)
{
    writeDictionary(dictionary);

    //H 7 Default entry (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, dictionary->defaultEntry());
}

void DwgObjectWriter::writeDictionary(CadDictionary *dictionary)
{
    //Common:
    //Numitems L number of dictionary items
    std::vector<NonGraphicalObject *> entries;
    for (auto &&item: dictionary)
    {
        if (item is XRecord && !WriteXRecords)
        {
            continue;
        }

        if (item is UnknownNonGraphicalObject)
        {
            continue;
        }

        entries.Add(item);
    }

    _writer->writeBitLong(entries.Count);

    //R14 Only:
    if (_version == ACadVersion::AC1014)
    {
        //Unknown R14 RC Unknown R14 unsigned char, has always been 0
        _writer->writeByte(0);
    }

    //R2000 +:
    if (R2000Plus)
    {
        //Cloning flag BS 281
        _writer->writeBitShort((short) dictionary.ClonningFlags);
        _writer->writeByte((unsigned char) (dictionary.HardOwnerFlag ? 1u : 0u));
    }

    //Common:
    for (auto &&item in entries)
    {
        if (item is XRecord && !WriteXRecords)
        {
            continue;
        }

        if (item is UnknownNonGraphicalObject)
        {
            continue;
        }

        _writer->writeVariableText(item.Name);
        _writer->handleReference(DwgReferenceType::SoftOwnership, item.Handle);
    }

    addEntriesToWriter(dictionary);
}

void DwgObjectWriter::addEntriesToWriter(CadDictionary *dictionary)
{
    for (CadObject *e: dictionary)
    {
        _objects.push(e);
    }
}

void DwgObjectWriter::writeDictionaryVariable(DictionaryVariable *dictionaryVariable)
{
    //Intval RC an integer value
    _writer->writeByte(0);

    //BS a string
    _writer->writeVariableText(dictionaryVariable->value());
}

void DwgObjectWriter::writeGeoData(GeoData *geodata)
{
    //BL Object version formats
    _writer->writeBitLong((int) geodata->version());

    //H Soft pointer to host block
    _writer->handleReference(DwgReferenceType::SoftPointer, geodata->hostBlock());

    //BS Design coordinate type
    _writer->writeBitShort((short) geodata->coordinatesType());

    switch (geodata->version())
    {
        case GeoDataVersion::R2009:
            //3BD  Reference point
            _writer->write3BitDouble(geodata->referencePoint());

            //BL  Units value horizontal
            _writer->writeBitLong((int) geodata->horizontalUnits());

            //3BD  Design point
            _writer->write3BitDouble(geodata->designPoint());

            //3BD  Obsolete, ODA writes (0, 0, 0)
            _writer->write3BitDouble(XYZ::Zero);

            //3BD  Up direction
            _writer->write3BitDouble(geodata->upDirection());

            //BD Angle of north direction (radians, angle measured clockwise from the (0, 1) vector).
            _writer->writeBitDouble(M_PI / 2.0 - geodata->northDirection().angle());

            //3BD  Obsolete, ODA writes(1, 1, 1)
            _writer->write3BitDouble(XYZ(1, 1, 1));

            //VT  Coordinate system definition. In AutoCAD 2009 this is a "Well known text" (WKT)string containing a projected coordinate system(PROJCS).
            _writer->writeVariableText(geodata->coordinateSystemDefinition());
            //VT  Geo RSS tag.
            _writer->writeVariableText(geodata->geoRssTag());

            //BD Unit scale factor horizontal
            _writer->writeBitDouble(geodata->horizontalUnitScale());
            geodata->setVerticalUnitScale(geodata->horizontalUnitScale());

            //VT  Obsolete, coordinate system datum name
            _writer->writeVariableText("");
            //VT  Obsolete: coordinate system WKT
            _writer->writeVariableText("");
            break;
        case GeoDataVersion::R2010:
        case GeoDataVersion::R2013:
            //3BD  Design point
            _writer->write3BitDouble(geodata->designPoint());
            //3BD  Reference point
            _writer->write3BitDouble(geodata->referencePoint());
            //BD  Unit scale factor horizontal
            _writer->writeBitDouble(geodata->horizontalUnitScale());
            //BL  Units value horizontal
            _writer->writeBitLong((int) geodata->horizontalUnits());
            //BD  Unit scale factor vertical
            _writer->writeBitDouble(geodata->verticalUnitScale());
            //BL  Units value vertical
            _writer->writeBitLong((int) geodata->horizontalUnits());
            //3RD  Up direction
            _writer->write3BitDouble(geodata->upDirection());
            //3RD  North direction
            _writer->write2RawDouble(geodata->northDirection());
            //BL Scale estimation method.
            _writer->writeBitLong((int) geodata->scaleEstimationMethod());
            //BD  User specified scale factor
            _writer->writeBitDouble(geodata->userSpecifiedScaleFactor());
            //B  Do sea level correction
            _writer->writeBit(geodata->enableSeaLevelCorrection());
            //BD  Sea level elevation
            _writer->writeBitDouble(geodata->seaLevelElevation());
            //BD  Coordinate projection radius
            _writer->writeBitDouble(geodata->coordinateProjectionRadius());
            //VT  Coordinate system definition . In AutoCAD 2010 this is a map guide XML string.
            _writer->writeVariableText(geodata->coordinateSystemDefinition());
            //VT  Geo RSS tag.
            _writer->writeVariableText(geodata->geoRssTag());
            break;
        default:
            break;
    }

    //VT  Observation from tag
    _writer->writeVariableText(geodata->observationFromTag());
    //VT  Observation to tag
    _writer->writeVariableText(geodata->observationToTag());
    //VT  Observation coverage tag
    _writer->writeVariableText(geodata->observationCoverageTag());

    //BL Number of geo mesh points
    _writer->writeBitLong(geodata->points().size());
    for (auto &&pt: geodata->points())
    {
        //2RD Source point
        _writer->write2RawDouble(pt.source);
        //2RD Destination point
        _writer->write2RawDouble(pt.destination);
    }

    //BL Number of geo mesh faces
    _writer->writeBitLong(geodata->faces().size());
    for (auto &&face: geodata->faces())
    {
        //BL Face index 1
        _writer->writeBitLong(face.index1);
        //BL Face index 2
        _writer->writeBitLong(face.index2);
        //BL Face index 3
        _writer->writeBitLong(face.index3);
    }
}

void DwgObjectWriter::writeGroup(Group *group)
{
    //Str TV name of group
    _writer->writeVariableText(group->description());

    //Unnamed BS 1 if group has no name
    _writer->writeBitShort((short) (group->isUnnamed() ? 1 : 0));
    //Selectable BS 1 if group selectable
    _writer->writeBitShort((short) (group->selectable() ? 1 : 0));

    //Numhandles BL # objhandles in this group
    _writer->writeBitLong(group->entities().size());
    for (auto &&e: group->entities())
    {
        //the entries in the group(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, e);
    }
}

void DwgObjectWriter::writeImageDefinitionReactor(ImageDefinitionReactor *definitionReactor)
{
    //Common:
    //Classver BL 90 class version
    _writer->writeBitLong(definitionReactor->classVersion());
}

void DwgObjectWriter::writeImageDefinition(ImageDefinition *definition)
{
    //Common:
    //Clsver BL 0 class version
    _writer->writeBitLong(definition->classVersion());
    //Imgsize 2RD 10 size of image in pixels
    _writer->write2RawDouble(definition->size());
    //Filepath TV 1 path to file
    _writer->writeVariableText(definition->fileName());
    //Isloaded B 280 0==no, 1==yes
    _writer->writeBit(definition->isLoaded());
    //Resunits RC 281 0==none, 2==centimeters, 5==inches
    _writer->writeByte((unsigned char) definition->units());
    //Pixelsize 2RD 11 size of one pixel in AutoCAD units
    _writer->write2RawDouble(definition->defaultSize());
}

void DwgObjectWriter::writeLayout(Layout *layout)
{
    writePlotSettings(layout);

    //Common:
    //Layout name TV 1 layout name
    _writer->writeVariableText(layout->name());
    //Tab order BL 71 layout tab order
    _writer->writeBitLong(layout->tabOrder());
    //Flag BS 70 layout flags
    _writer->writeBitShort((short) layout->layoutFlags());
    //Ucs origin 3BD 13 layout ucs origin
    _writer->write3BitDouble(layout->origin());
    //Limmin 2RD 10 layout minimum limits
    _writer->write2RawDouble(layout->minLimits());
    //Limmax 2RD 11 layout maximum limits
    _writer->write2RawDouble(layout->minLimits());
    //Inspoint 3BD 12 layout insertion base point
    _writer->write3BitDouble(layout->insertionBasePoint());
    _writer->write3BitDouble(layout->xAxis());
    _writer->write3BitDouble(layout->yAxis());
    _writer->writeBitDouble(layout->elevation());
    _writer->writeBitShort((short) layout->ucsOrthographicType());
    _writer->write3BitDouble(layout->minExtents());
    _writer->write3BitDouble(layout->maxExtents());

    //R2004 +:
    if (R2004Plus)
    {
        //Viewport count RL # of viewports in this layout
        _writer->writeBitLong(layout->viewports().size());
    }

    //Common:
    //330 associated paperspace block record handle(soft pointer)
    _writer->handleReference(DwgReferenceType::SoftPointer, layout->associatedBlock());
    //331 last active viewport handle(soft pointer)
    _writer->handleReference(DwgReferenceType::SoftPointer, layout->viewport());

    //If not present and 76 code is non-zero, then base UCS is taken to be WORLD
    if (layout->ucsOrthographicType() == OrthographicType::None)
    {
        //346 base ucs handle(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, nullptr);
        //345 named ucs handle(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, layout->ucs());
    }
    else
    {
        //346 base ucs handle(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, layout->baseUCS());
        //345 named ucs handle(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, nullptr);
    }

    //R2004+:
    if (R2004Plus)
    {
        for (auto &&viewport: layout->viewports())
        {
            //Viewport handle(repeats Viewport count times) (soft pointer)
            _writer->handleReference(DwgReferenceType::SoftPointer, viewport);
        }
    }
}

void DwgObjectWriter::writeMLineStyle(MLineStyle *mlineStyle)
{
    //Common:
    //Name TV Name of this style
    _writer->writeVariableText(mlineStyle->name());
    //Desc TV Description of this style
    _writer->writeVariableText(mlineStyle->description());

    short flags = 0;
    if (mlineStyle->flags() & MLineStyleFlag::DisplayJoints)
    {
        flags = (short) (flags | 1U);
    }
    if (mlineStyle->flags() & MLineStyleFlag::FillOn)
    {
        flags = (short) (flags | 2U);
    }
    if (mlineStyle->flags() & MLineStyleFlag::StartSquareCap)
    {
        flags = (short) (flags | 16U);
    }
    if (mlineStyle->flags() & MLineStyleFlag::StartRoundCap)
    {
        flags = (short) (flags | 0x20);
    }
    if (mlineStyle->flags() & MLineStyleFlag::StartInnerArcsCap)
    {
        flags = (short) (flags | 0x40);
    }
    if (mlineStyle->flags() & MLineStyleFlag::EndSquareCap)
    {
        flags = (short) (flags | 0x100);
    }
    if (mlineStyle->flags() & MLineStyleFlag::EndRoundCap)
    {
        flags = (short) (flags | 0x200);
    }
    if (mlineStyle->flags() & MLineStyleFlag::EndInnerArcsCap)
    {
        flags = (short) (flags | 0x400);
    }

    //Flags BS A short which reconstitutes the mlinestyle flags as defined in DXF.
    _writer->writeBitShort(flags);

    //fillcolor CMC Fill color for this style
    _writer->writeCmColor(mlineStyle->fillColor());
    //startang BD Start angle
    _writer->writeBitDouble(mlineStyle->startAngle());
    //endang BD End angle
    _writer->writeBitDouble(mlineStyle->endAngle());

    //linesinstyle RC Number of lines in this style
    _writer->writeByte((unsigned char) mlineStyle->elements().size());
    for (auto &&element: mlineStyle->elements())
    {
        //Offset BD Offset of this segment
        _writer->writeBitDouble(element.offset);
        //Color CMC Color of this segment
        _writer->writeCmColor(element.color);
        //R2018+:
        if (R2018Plus)
        {
            //Line type handle H Line type handle (hard pointer)
            _writer->handleReference(DwgReferenceType::HardPointer, element.lineType);
        }
        //Before R2018:
        else
        {
            //TODO: Fix the Linetype index for dwgReader and DwgWriter
            //Ltindex BS Linetype index (yes, index)
            _writer->writeBitShort(0);
        }
    }
}

void DwgObjectWriter::writeMultiLeaderStyle(MultiLeaderStyle *mLeaderStyle)
{
    if (R2010Plus)
    {
        //	BS	179	Version expected: 2
        _writer->writeBitShort(2);
    }

    //	BS	170	Content type (see paragraph on LEADER for more details).
    _writer->writeBitShort((short) mLeaderStyle->contentType());
    //	BS	171	Draw multi-leader order (0 = draw content first, 1 = draw leader first)
    _writer->writeBitShort((short) mLeaderStyle->multiLeaderDrawOrder());
    //	BS	172	Draw leader order (0 = draw leader head first, 1 = draw leader tail first)
    _writer->writeBitShort((short) mLeaderStyle->leaderDrawOrder());
    //	BL	90	Maximum number of points for leader
    _writer->writeBitLong((short) mLeaderStyle->maxLeaderSegmentsPoints());
    //	BD	40	First segment angle (radians)
    _writer->writeBitDouble(mLeaderStyle->firstSegmentAngleConstraint());
    //	BD	41	Second segment angle (radians)
    _writer->writeBitDouble(mLeaderStyle->secondSegmentAngleConstraint());
    //	BS	173	Leader type (see paragraph on LEADER for more details).
    _writer->writeBitShort((short) mLeaderStyle->pathType());
    //	CMC	91	Leader line color
    _writer->writeCmColor(mLeaderStyle->lineColor());

    //	H	340	Leader line type handle (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, mLeaderStyle->leaderLineType());

    //	BL	92	Leader line weight
    _writer->writeBitLong((short) mLeaderStyle->leaderLineWeight());
    //	B	290	Is landing enabled?
    _writer->writeBit(mLeaderStyle->enableLanding());
    //	BD	42	Landing gap
    _writer->writeBitDouble(mLeaderStyle->landingGap());
    //	B	291	Auto include landing (is dog-leg enabled?)
    _writer->writeBit(mLeaderStyle->enableDogleg());
    //	BD	43	Landing distance
    _writer->writeBitDouble(mLeaderStyle->landingDistance());
    //	TV	3	Style description
    _writer->writeVariableText(mLeaderStyle->description());

    //	H	341	Arrow head block handle (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, mLeaderStyle->arrowhead());

    //	BD	44	Arrow head size
    _writer->writeBitDouble(mLeaderStyle->arrowheadSize());
    //	TV	300	Text default
    _writer->writeVariableText(mLeaderStyle->defaultTextContents());

    //	H	342	Text style handle (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, mLeaderStyle->textStyle());

    //	BS	174	Left attachment (see paragraph on LEADER for more details).
    _writer->writeBitShort((short) mLeaderStyle->textLeftAttachment());
    //	BS	178	Right attachment (see paragraph on LEADER for more details).
    _writer->writeBitShort((short) mLeaderStyle->textRightAttachment());
    //	BS	175	Text angle type (see paragraph on LEADER for more details).
    _writer->writeBitShort((short) mLeaderStyle->textAngle());
    //	BS	176	Text alignment type
    _writer->writeBitShort((short) mLeaderStyle->textAlignment());
    //	CMC	93	Text color
    _writer->writeCmColor(mLeaderStyle->textColor());
    //	BD	45	Text height
    _writer->writeBitDouble(mLeaderStyle->textHeight());
    //	B	292	Text frame enabled
    _writer->writeBit(mLeaderStyle->textFrame());
    //	B	297	Always align text left
    _writer->writeBit(mLeaderStyle->textAlignAlwaysLeft());
    //	BD	46	Align space
    _writer->writeBitDouble(mLeaderStyle->alignSpace());

    //	H	343	Block handle (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, mLeaderStyle->blockContent());

    //	CMC	94	Block color
    _writer->writeCmColor(mLeaderStyle->blockContentColor());
    //	3BD	47,49,140	Block scale vector
    _writer->write3BitDouble(mLeaderStyle->blockContentScale());
    //	B	293	Is block scale enabled
    _writer->writeBit(mLeaderStyle->enableBlockContentScale());
    //	BD	141	Block rotation (radians)
    _writer->writeBitDouble(mLeaderStyle->blockContentRotation());
    //	B	294	Is block rotation enabled
    _writer->writeBit(mLeaderStyle->enableBlockContentRotation());
    //	BS	177	Block connection type (0 = MLeader connects to the block extents, 1 = MLeader connects to the block base point)
    _writer->writeBitShort((short) mLeaderStyle->blockContentConnection());
    //	BD	142	Scale factor
    _writer->writeBitDouble(mLeaderStyle->scaleFactor());
    //	B	295	Property changed, meaning not totally clear
    //	might be set to true if something changed after loading,
    //	or might be used to trigger updates in dependent MLeaders.
    //	sequence seems to be different in DXF
    _writer->writeBit(mLeaderStyle->overwritePropertyValue());
    //	B	296	Is annotative?
    _writer->writeBit(mLeaderStyle->isAnnotative());
    //	BD	143	Break size
    _writer->writeBitDouble(mLeaderStyle->breakGapSize());

    if (R2010Plus)
    {
        //	BS	271	Attachment direction (see paragraph on LEADER for more details).
        _writer->writeBitShort((short) mLeaderStyle->textAttachmentDirection());
        //	BS	273	Top attachment (see paragraph on LEADER for more details).
        _writer->writeBitShort((short) mLeaderStyle->textBottomAttachment());
        //	BS	272	Bottom attachment (see paragraph on LEADER for more details).
        _writer->writeBitShort((short) mLeaderStyle->textTopAttachment());
    }

    if (R2013Plus)
    {
        //	B	298 Undocumented, found in DXF
        _writer->writeBit(mLeaderStyle->unknownFlag298());
    }
}

void DwgObjectWriter::writePlotSettings(PlotSettings *plot)
{
    //Common:
    //Page setup name TV 1 plotsettings page setup name
    _writer->writeVariableText(plot->pageName());
    //Printer / Config TV 2 plotsettings printer or configuration file
    _writer->writeVariableText(plot->systemPrinterName());
    //Plot layout flags BS 70 plotsettings plot layout flag
    _writer->writeBitShort((short) plot->flags());

    //Left Margin BD 40 plotsettings left margin in millimeters
    _writer->writeBitDouble(plot->unprintableMargin().Left);
    //Bottom Margin BD 41 plotsettings bottom margin in millimeters
    _writer->writeBitDouble(plot->unprintableMargin().Bottom);
    //Right Margin BD 42 plotsettings right margin in millimeters
    _writer->writeBitDouble(plot->unprintableMargin().Right);
    //Top Margin BD 43 plotsettings top margin in millimeters
    _writer->writeBitDouble(plot->unprintableMargin().Top);

    //Paper Width BD 44 plotsettings paper width in millimeters
    _writer->writeBitDouble(plot->paperWidth());
    //Paper Height BD 45 plotsettings paper height in millimeters
    _writer->writeBitDouble(plot->paperHeight());

    //Paper Size TV 4 plotsettings paper size
    _writer->writeVariableText(plot->paperSize());

    //Plot origin 2BD 46,47 plotsettings origin offset in millimeters
    _writer->writeBitDouble(plot->plotOriginX());
    _writer->writeBitDouble(plot->plotOriginY());

    //Paper units BS 72 plotsettings plot paper units
    _writer->writeBitShort((short) plot->paperUnits());
    //Plot rotation BS 73 plotsettings plot rotation
    _writer->writeBitShort((short) plot->paperRotation());
    //Plot type BS 74 plotsettings plot type
    _writer->writeBitShort((short) plot->plotType());

    //Window min 2BD 48,49 plotsettings plot window area lower left
    _writer->writeBitDouble(plot->windowLowerLeftX());
    _writer->writeBitDouble(plot->windowLowerLeftY());
    //Window max 2BD 140,141 plotsettings plot window area upper right
    _writer->writeBitDouble(plot->windowUpperLeftX());
    _writer->writeBitDouble(plot->windowUpperLeftY());

    //R13 - R2000 Only:
    if (_version >= ACadVersion::AC1012 && _version <= ACadVersion::AC1015)
    {
        //Plot view name T 6 plotsettings plot view name
        _writer->writeVariableText(plot->plotViewName());
    }

    //Common:
    //Real world units BD 142 plotsettings numerator of custom print scale
    _writer->writeBitDouble(plot->numeratorScale());
    //Drawing units BD 143 plotsettings denominator of custom print scale
    _writer->writeBitDouble(plot->denominatorScale());
    //Current style sheet TV 7 plotsettings current style sheet
    _writer->writeVariableText(plot->styleSheet());
    //Scale type BS 75 plotsettings standard scale type
    _writer->writeBitShort((short) plot->scaledFit());
    //Scale factor BD 147 plotsettings scale factor
    _writer->writeBitDouble(plot->standardScale());
    //Paper image origin 2BD 148,149 plotsettings paper image origin
    _writer->write2BitDouble(plot->paperImageOrigin());

    //R2004+:
    if (R2004Plus)
    {
        //Shade plot mode BS 76
        _writer->writeBitShort((short) plot->shadePlotMode());
        //Shade plot res.Level BS 77
        _writer->writeBitShort((short) plot->shadePlotResolutionMode());
        //Shade plot custom DPI BS 78
        _writer->writeBitShort(plot->shadePlotDPI());

        //6 plot view handle(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, nullptr);
    }

    //R2007 +:
    if (R2007Plus)
    {
        //Visual Style handle(soft pointer)
        _writer->handleReference(DwgReferenceType::SoftPointer, nullptr);
    }
}

void DwgObjectWriter::writeScale(Scale *scale)
{
    //BS	70	Unknown(ODA writes 0).
    _writer->writeBitShort(0);
    //TV	300	Name
    _writer->writeVariableText(scale->name());
    //BD	140	Paper units(numerator)
    _writer->writeBitDouble(scale->paperUnits());
    //BD	141	Drawing units(denominator, divided by 10).
    _writer->writeBitDouble(scale->drawingUnits());
    //B	290	Has unit scale
    _writer->writeBit(scale->isUnitScale());
}

void DwgObjectWriter::writeSortEntitiesTable(SortEntitiesTable *sortEntitiesTable)
{
    //parenthandle (soft pointer)
    _writer->handleReference(DwgReferenceType::SoftPointer, sortEntitiesTable->blockOwner());

    //Common:
    //Numentries BL number of entries
    _writer->writeBitLong(sortEntitiesTable->sorters().size());

    for (auto &&item: sortEntitiesTable->sorters())
    {
        //Sort handle(numentries of these, CODE 0, i.e.part of the main bit stream, not of the handle bit stream!).
        //The sort handle does not have to point to an entity (but it can).
        //This is just the handle used for determining the drawing order of the entity specified by the entity handle in the handle bit stream.
        //When the sortentstable doesn't have a
        //mapping from entity handle to sort handle, then the entity's own handle is used for sorting.
        _writer->handleReference(item.handle);
        _writer->handleReference(DwgReferenceType::SoftPointer, item.entity);
    }
}

void DwgObjectWriter::writeXRecord(XRecord *xrecord)
{
    std::unique_ptr<std::ostringstream> stream = std::make_unique<std::ostringstream>();
    OutputStreamWrapper ms(stream.get());

    for (auto &&entry: xrecord->entries())
    {
        if (entry.value.isEmpty())
        {
            continue;
        }

        ms.write<short>((short) entry.code);
        GroupCodeValueType groupValueType = GroupCodeValue::transformValue(entry.code);

        switch (groupValueType)
        {
            case GroupCodeValueType::Byte:
            case GroupCodeValueType::Bool:
                ms.writeByte(entry.value.asChar());
                break;
            case GroupCodeValueType::Int16:
            case GroupCodeValueType::ExtendedDataInt16:
                ms.write<short>(entry.value.asShort());
                break;
            case GroupCodeValueType::Int32:
            case GroupCodeValueType::ExtendedDataInt32:
                ms.write<int>(entry.value.asInt());
                break;
            case GroupCodeValueType::Int64:
                ms.write<long>(entry.value.asLongLong());
                break;
            case GroupCodeValueType::Double:
            case GroupCodeValueType::ExtendedDataDouble:
                ms.write<double>(entry.value.asDouble());
                break;
            case GroupCodeValueType::Point3D:
                XYZ xyz = entry.value.asCoord3D();
                ms.write<double>(xyz.X);
                ms.write<double>(xyz.Y);
                ms.write<double>(xyz.Z);
                break;
            case GroupCodeValueType::Chunk:
            case GroupCodeValueType::ExtendedDataChunk:
                auto chunk = entry.value.asBlob();
                ms.write((unsigned char) chunk.size());
                break;
            case GroupCodeValueType::String:
            case GroupCodeValueType::ExtendedDataString:
            case GroupCodeValueType::Handle:
                std::string text = entry.value.asString();
                if (R2007Plus)
                {
                    if (text.empty())
                    {
                        ms.write<short, LittleEndianConverter>(0);
                        return;
                    }

                    ms.write<short, LittleEndianConverter>((short) text.length());
                    ms.write(text, Encoding::Utf8());
                }
                else if (text.empty())
                {
                    ms.write<short, LittleEndianConverter>(0);
                    ms.write((unsigned char) CadUtils::GetCodeIndex((CodePage) _writer->encoding().codePage()));
                }
                else
                {
                    ms.write<short, LittleEndianConverter>((short) text.length());
                    ms.write((unsigned char) CadUtils::GetCodeIndex((CodePage) _writer->encoding().codePage()));
                    ms.write(text, _writer->encoding());
                }
                break;
            case GroupCodeValueType::ObjectId:
            case GroupCodeValueType::ExtendedDataHandle:
                unsigned long long u = entry.value.asULongLong();
                ms.write<unsigned long long, LittleEndianConverter>(u);
                break;
            default:
                break;
        }
    }

    //Common:
    //Numdatabytes BL number of databytes
    _writer->writeBitLong((int) ms.length());
    _writer->writeBytes(ms.buffer());

    //R2000+:
    if (R2000Plus)
    {
        //Cloning flag BS 280
        _writer->writeBitShort((short) xrecord->cloningFlags());
    }
}


}// namespace dwg
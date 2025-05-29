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
#include <dwg/objects/BookColor.h>
#include <dwg/objects/CadDictionary.h>
#include <dwg/objects/CadDictionaryWithDefault.h>
#include <dwg/objects/NonGraphicalObject.h>
#include <dwg/utils/EndianConverter.h>

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
    for (auto &&item : dictionary)
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
    for (CadObject e in dictionary)
    {
        _objects.Enqueue(e);
    }
}

void DwgObjectWriter::writeDictionaryVariable(DictionaryVariable *dictionaryVariable)
{
    //Intval RC an integer value
    _writer->writeByte(0);

    //BS a string
    _writer->writeVariableText(dictionaryVariable.Value);
}

void DwgObjectWriter::writeGeoData(GeoData *geodata)
{
    //BL Object version formats
    _writer->writeBitLong((int) geodata.Version);

    //H Soft pointer to host block
    _writer->handleReference(DwgReferenceType::SoftPointer, geodata.HostBlock);

    //BS Design coordinate type
    _writer->writeBitShort((short) geodata.CoordinatesType);

    switch (geodata.Version)
    {
        case GeoDataVersion.R2009:
            //3BD  Reference point
            _writer->write3BitDouble(geodata.ReferencePoint);

            //BL  Units value horizontal
            _writer->writeBitLong((int) geodata.HorizontalUnits);

            //3BD  Design point
            _writer->write3BitDouble(geodata.DesignPoint);

            //3BD  Obsolete, ODA writes (0, 0, 0)
            _writer->write3BitDouble(XYZ.Zero);

            //3BD  Up direction
            _writer->write3BitDouble(geodata.UpDirection);

            //BD Angle of north direction (radians, angle measured clockwise from the (0, 1) vector).
            _writer->writeBitDouble(System.Math.PI / 2.0 - geodata.NorthDirection.GetAngle());

            //3BD  Obsolete, ODA writes(1, 1, 1)
            _writer->write3BitDouble(new XYZ(1, 1, 1));

            //VT  Coordinate system definition. In AutoCAD 2009 this is a “Well known text” (WKT)string containing a projected coordinate system(PROJCS).
            _writer->writeVariableText(geodata.CoordinateSystemDefinition);
            //VT  Geo RSS tag.
            _writer->writeVariableText(geodata.GeoRssTag);

            //BD Unit scale factor horizontal
            _writer->writeBitDouble(geodata.HorizontalUnitScale);
            geodata.VerticalUnitScale = geodata.HorizontalUnitScale;

            //VT  Obsolete, coordinate system datum name
            _writer->writeVariableText(string.Empty);
            //VT  Obsolete: coordinate system WKT
            _writer->writeVariableText(string.Empty);
            break;
        case GeoDataVersion.R2010:
        case GeoDataVersion.R2013:
            //3BD  Design point
            _writer->write3BitDouble(geodata.DesignPoint);
            //3BD  Reference point
            _writer->write3BitDouble(geodata.ReferencePoint);
            //BD  Unit scale factor horizontal
            _writer->writeBitDouble(geodata.HorizontalUnitScale);
            //BL  Units value horizontal
            _writer->writeBitLong((int) geodata.HorizontalUnits);
            //BD  Unit scale factor vertical
            _writer->writeBitDouble(geodata.VerticalUnitScale);
            //BL  Units value vertical
            _writer->writeBitLong((int) geodata.HorizontalUnits);
            //3RD  Up direction
            _writer->write3BitDouble(geodata.UpDirection);
            //3RD  North direction
            _writer->write2RawDouble(geodata.NorthDirection);
            //BL Scale estimation method.
            _writer->writeBitLong((int) geodata.ScaleEstimationMethod);
            //BD  User specified scale factor
            _writer->writeBitDouble(geodata.UserSpecifiedScaleFactor);
            //B  Do sea level correction
            _writer->writeBit(geodata.EnableSeaLevelCorrection);
            //BD  Sea level elevation
            _writer->writeBitDouble(geodata.SeaLevelElevation);
            //BD  Coordinate projection radius
            _writer->writeBitDouble(geodata.CoordinateProjectionRadius);
            //VT  Coordinate system definition . In AutoCAD 2010 this is a map guide XML string.
            _writer->writeVariableText(geodata.CoordinateSystemDefinition);
            //VT  Geo RSS tag.
            _writer->writeVariableText(geodata.GeoRssTag);
            break;
        default:
            break;
    }

    //VT  Observation from tag
    _writer->writeVariableText(geodata.ObservationFromTag);
    //VT  Observation to tag
    _writer->writeVariableText(geodata.ObservationToTag);
    //VT  Observation coverage tag
    _writer->writeVariableText(geodata.ObservationCoverageTag);

    //BL Number of geo mesh points
    _writer->writeBitLong(geodata.Points.Count);
    for (auto &&pt in geodata.Points)
    {
        //2RD Source point
        _writer->write2RawDouble(pt.Source);
        //2RD Destination point
        _writer->write2RawDouble(pt.Destination);
    }

    //BL Number of geo mesh faces
    _writer->writeBitLong(geodata.Faces.Count);
    for (auto &&face in geodata.Faces)
    {
        //BL Face index 1
        _writer->writeBitLong(face.Index1);
        //BL Face index 2
        _writer->writeBitLong(face.Index2);
        //BL Face index 3
        _writer->writeBitLong(face.Index3);
    }
}

void DwgObjectWriter::writeGroup(Group *group)
{
    //Str TV name of group
    _writer->writeVariableText(group.Description);

    //Unnamed BS 1 if group has no name
    _writer->writeBitShort((short) (group.IsUnnamed ? 1 : 0));
    //Selectable BS 1 if group selectable
    _writer->writeBitShort((short) (group.Selectable ? 1 : 0));

    //Numhandles BL # objhandles in this group
    _writer->writeBitLong(group.Entities.Count());
    for (auto &&e in group.Entities)
    {
        //the entries in the group(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, e);
    }
}

void DwgObjectWriter::writeImageDefinitionReactor(ImageDefinitionReactor *definitionReactor)
{
    //Common:
    //Classver BL 90 class version
    _writer->writeBitLong(definitionReactor.ClassVersion);
}

void DwgObjectWriter::writeImageDefinition(ImageDefinition *definition)
{
    //Common:
    //Clsver BL 0 class version
    _writer->writeBitLong(definition.ClassVersion);
    //Imgsize 2RD 10 size of image in pixels
    _writer->write2RawDouble(definition.Size);
    //Filepath TV 1 path to file
    _writer->writeVariableText(definition.FileName);
    //Isloaded B 280 0==no, 1==yes
    _writer->writeBit(definition.IsLoaded);
    //Resunits RC 281 0==none, 2==centimeters, 5==inches
    _writer->writeByte((unsigned char) definition.Units);
    //Pixelsize 2RD 11 size of one pixel in AutoCAD units
    _writer->write2RawDouble(definition.DefaultSize);
}

void DwgObjectWriter::writeLayout(Layout *layout)
{
    writePlotSettings(layout);

    //Common:
    //Layout name TV 1 layout name
    _writer->writeVariableText(layout.Name);
    //Tab order BL 71 layout tab order
    _writer->writeBitLong(layout.TabOrder);
    //Flag BS 70 layout flags
    _writer->writeBitShort((short) layout.LayoutFlags);
    //Ucs origin 3BD 13 layout ucs origin
    _writer->write3BitDouble(layout.Origin);
    //Limmin 2RD 10 layout minimum limits
    _writer->write2RawDouble(layout.MinLimits);
    //Limmax 2RD 11 layout maximum limits
    _writer->write2RawDouble(layout.MinLimits);
    //Inspoint 3BD 12 layout insertion base point
    _writer->write3BitDouble(layout.InsertionBasePoint);
    _writer->write3BitDouble(layout.XAxis);
    _writer->write3BitDouble(layout.YAxis);
    _writer->writeBitDouble(layout.Elevation);
    _writer->writeBitShort((short) layout.UcsOrthographicType);
    _writer->write3BitDouble(layout.MinExtents);
    _writer->write3BitDouble(layout.MaxExtents);

    //R2004 +:
    if (R2004Plus)
    {
        //Viewport count RL # of viewports in this layout
        _writer->writeBitLong(layout.Viewports.Count());
    }

    //Common:
    //330 associated paperspace block record handle(soft pointer)
    _writer->handleReference(DwgReferenceType::SoftPointer, layout.AssociatedBlock);
    //331 last active viewport handle(soft pointer)
    _writer->handleReference(DwgReferenceType::SoftPointer, layout.Viewport);

    //If not present and 76 code is non-zero, then base UCS is taken to be WORLD
    if (layout.UcsOrthographicType == OrthographicType.None)
    {
        //346 base ucs handle(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, nullptr);
        //345 named ucs handle(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, layout.UCS);
    }
    else
    {
        //346 base ucs handle(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, layout.BaseUCS);
        //345 named ucs handle(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, nullptr);
    }

    //R2004+:
    if (R2004Plus)
    {
        for (Entities.Viewport viewport in layout.Viewports)
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
    _writer->writeVariableText(mlineStyle.Name);
    //Desc TV Description of this style
    _writer->writeVariableText(mlineStyle.Description);

    short flags = 0;
    if (mlineStyle.Flags.HasFlag(MLineStyleFlags.DisplayJoints))
    {
        flags = (short) (flags | 1U);
    }
    if (mlineStyle.Flags.HasFlag(MLineStyleFlags.FillOn))
    {
        flags = (short) (flags | 2U);
    }
    if (mlineStyle.Flags.HasFlag(MLineStyleFlags.StartSquareCap))
    {
        flags = (short) (flags | 16U);
    }
    if (mlineStyle.Flags.HasFlag(MLineStyleFlags.StartRoundCap))
    {
        flags = (short) (flags | 0x20);
    }
    if (mlineStyle.Flags.HasFlag(MLineStyleFlags.StartInnerArcsCap))
    {
        flags = (short) (flags | 0x40);
    }
    if (mlineStyle.Flags.HasFlag(MLineStyleFlags.EndSquareCap))
    {
        flags = (short) (flags | 0x100);
    }
    if (mlineStyle.Flags.HasFlag(MLineStyleFlags.EndRoundCap))
    {
        flags = (short) (flags | 0x200);
    }
    if (mlineStyle.Flags.HasFlag(MLineStyleFlags.EndInnerArcsCap))
    {
        flags = (short) (flags | 0x400);
    }

    //Flags BS A short which reconstitutes the mlinestyle flags as defined in DXF.
    _writer->writeBitShort(flags);

    //fillcolor CMC Fill color for this style
    _writer->writeCmColor(mlineStyle.FillColor);
    //startang BD Start angle
    _writer->writeBitDouble(mlineStyle.StartAngle);
    //endang BD End angle
    _writer->writeBitDouble(mlineStyle.EndAngle);

    //linesinstyle RC Number of lines in this style
    _writer->writeByte((unsigned char) mlineStyle.Elements.Count);
    for (MLineStyle.Element element in mlineStyle.Elements)
    {
        //Offset BD Offset of this segment
        _writer->writeBitDouble(element.Offset);
        //Color CMC Color of this segment
        _writer->writeCmColor(element.Color);
        //R2018+:
        if (R2018Plus)
        {
            //Line type handle H Line type handle (hard pointer)
            _writer->handleReference(DwgReferenceType::HardPointer, element.LineType);
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
    _writer->writeBitShort((short) mLeaderStyle.ContentType);
    //	BS	171	Draw multi-leader order (0 = draw content first, 1 = draw leader first)
    _writer->writeBitShort((short) mLeaderStyle.MultiLeaderDrawOrder);
    //	BS	172	Draw leader order (0 = draw leader head first, 1 = draw leader tail first)
    _writer->writeBitShort((short) mLeaderStyle.LeaderDrawOrder);
    //	BL	90	Maximum number of points for leader
    _writer->writeBitLong((short) mLeaderStyle.MaxLeaderSegmentsPoints);
    //	BD	40	First segment angle (radians)
    _writer->writeBitDouble(mLeaderStyle.FirstSegmentAngleConstraint);
    //	BD	41	Second segment angle (radians)
    _writer->writeBitDouble(mLeaderStyle.SecondSegmentAngleConstraint);
    //	BS	173	Leader type (see paragraph on LEADER for more details).
    _writer->writeBitShort((short) mLeaderStyle.PathType);
    //	CMC	91	Leader line color
    _writer->writeCmColor(mLeaderStyle.LineColor);

    //	H	340	Leader line type handle (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, mLeaderStyle.LeaderLineType);

    //	BL	92	Leader line weight
    _writer->writeBitLong((short) mLeaderStyle.LeaderLineWeight);
    //	B	290	Is landing enabled?
    _writer->writeBit(mLeaderStyle.EnableLanding);
    //	BD	42	Landing gap
    _writer->writeBitDouble(mLeaderStyle.LandingGap);
    //	B	291	Auto include landing (is dog-leg enabled?)
    _writer->writeBit(mLeaderStyle.EnableDogleg);
    //	BD	43	Landing distance
    _writer->writeBitDouble(mLeaderStyle.LandingDistance);
    //	TV	3	Style description
    _writer->writeVariableText(mLeaderStyle.Description);

    //	H	341	Arrow head block handle (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, mLeaderStyle.Arrowhead);

    //	BD	44	Arrow head size
    _writer->writeBitDouble(mLeaderStyle.ArrowheadSize);
    //	TV	300	Text default
    _writer->writeVariableText(mLeaderStyle.DefaultTextContents);

    //	H	342	Text style handle (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, mLeaderStyle.TextStyle);

    //	BS	174	Left attachment (see paragraph on LEADER for more details).
    _writer->writeBitShort((short) mLeaderStyle.TextLeftAttachment);
    //	BS	178	Right attachment (see paragraph on LEADER for more details).
    _writer->writeBitShort((short) mLeaderStyle.TextRightAttachment);
    //	BS	175	Text angle type (see paragraph on LEADER for more details).
    _writer->writeBitShort((short) mLeaderStyle.TextAngle);
    //	BS	176	Text alignment type
    _writer->writeBitShort((short) mLeaderStyle.TextAlignment);
    //	CMC	93	Text color
    _writer->writeCmColor(mLeaderStyle.TextColor);
    //	BD	45	Text height
    _writer->writeBitDouble(mLeaderStyle.TextHeight);
    //	B	292	Text frame enabled
    _writer->writeBit(mLeaderStyle.TextFrame);
    //	B	297	Always align text left
    _writer->writeBit(mLeaderStyle.TextAlignAlwaysLeft);
    //	BD	46	Align space
    _writer->writeBitDouble(mLeaderStyle.AlignSpace);

    //	H	343	Block handle (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, mLeaderStyle.BlockContent);

    //	CMC	94	Block color
    _writer->writeCmColor(mLeaderStyle.BlockContentColor);
    //	3BD	47,49,140	Block scale vector
    _writer->write3BitDouble(mLeaderStyle.BlockContentScale);
    //	B	293	Is block scale enabled
    _writer->writeBit(mLeaderStyle.EnableBlockContentScale);
    //	BD	141	Block rotation (radians)
    _writer->writeBitDouble(mLeaderStyle.BlockContentRotation);
    //	B	294	Is block rotation enabled
    _writer->writeBit(mLeaderStyle.EnableBlockContentRotation);
    //	BS	177	Block connection type (0 = MLeader connects to the block extents, 1 = MLeader connects to the block base point)
    _writer->writeBitShort((short) mLeaderStyle.BlockContentConnection);
    //	BD	142	Scale factor
    _writer->writeBitDouble(mLeaderStyle.ScaleFactor);
    //	B	295	Property changed, meaning not totally clear
    //	might be set to true if something changed after loading,
    //	or might be used to trigger updates in dependent MLeaders.
    //	sequence seems to be different in DXF
    _writer->writeBit(mLeaderStyle.OverwritePropertyValue);
    //	B	296	Is annotative?
    _writer->writeBit(mLeaderStyle.IsAnnotative);
    //	BD	143	Break size
    _writer->writeBitDouble(mLeaderStyle.BreakGapSize);

    if (R2010Plus)
    {
        //	BS	271	Attachment direction (see paragraph on LEADER for more details).
        _writer->writeBitShort((short) mLeaderStyle.TextAttachmentDirection);
        //	BS	273	Top attachment (see paragraph on LEADER for more details).
        _writer->writeBitShort((short) mLeaderStyle.TextBottomAttachment);
        //	BS	272	Bottom attachment (see paragraph on LEADER for more details).
        _writer->writeBitShort((short) mLeaderStyle.TextTopAttachment);
    }

    if (R2013Plus)
    {
        //	B	298 Undocumented, found in DXF
        _writer->writeBit(mLeaderStyle.UnknownFlag298);
    }
}

void DwgObjectWriter::writePlotSettings(PlotSettings *plot)
{
    //Common:
    //Page setup name TV 1 plotsettings page setup name
    _writer->writeVariableText(plot.PageName);
    //Printer / Config TV 2 plotsettings printer or configuration file
    _writer->writeVariableText(plot.SystemPrinterName);
    //Plot layout flags BS 70 plotsettings plot layout flag
    _writer->writeBitShort((short) plot.Flags);

    //Left Margin BD 40 plotsettings left margin in millimeters
    _writer->writeBitDouble(plot.UnprintableMargin.Left);
    //Bottom Margin BD 41 plotsettings bottom margin in millimeters
    _writer->writeBitDouble(plot.UnprintableMargin.Bottom);
    //Right Margin BD 42 plotsettings right margin in millimeters
    _writer->writeBitDouble(plot.UnprintableMargin.Right);
    //Top Margin BD 43 plotsettings top margin in millimeters
    _writer->writeBitDouble(plot.UnprintableMargin.Top);

    //Paper Width BD 44 plotsettings paper width in millimeters
    _writer->writeBitDouble(plot.PaperWidth);
    //Paper Height BD 45 plotsettings paper height in millimeters
    _writer->writeBitDouble(plot.PaperHeight);

    //Paper Size TV 4 plotsettings paper size
    _writer->writeVariableText(plot.PaperSize);

    //Plot origin 2BD 46,47 plotsettings origin offset in millimeters
    _writer->writeBitDouble(plot.PlotOriginX);
    _writer->writeBitDouble(plot.PlotOriginY);

    //Paper units BS 72 plotsettings plot paper units
    _writer->writeBitShort((short) plot.PaperUnits);
    //Plot rotation BS 73 plotsettings plot rotation
    _writer->writeBitShort((short) plot.PaperRotation);
    //Plot type BS 74 plotsettings plot type
    _writer->writeBitShort((short) plot.PlotType);

    //Window min 2BD 48,49 plotsettings plot window area lower left
    _writer->writeBitDouble(plot.WindowLowerLeftX);
    _writer->writeBitDouble(plot.WindowLowerLeftY);
    //Window max 2BD 140,141 plotsettings plot window area upper right
    _writer->writeBitDouble(plot.WindowUpperLeftX);
    _writer->writeBitDouble(plot.WindowUpperLeftY);

    //R13 - R2000 Only:
    if (_version >= ACadVersion::AC1012 && _version <= ACadVersion::AC1015)
    {
        //Plot view name T 6 plotsettings plot view name
        _writer->writeVariableText(plot.PlotViewName);
    }

    //Common:
    //Real world units BD 142 plotsettings numerator of custom print scale
    _writer->writeBitDouble(plot.NumeratorScale);
    //Drawing units BD 143 plotsettings denominator of custom print scale
    _writer->writeBitDouble(plot.DenominatorScale);
    //Current style sheet TV 7 plotsettings current style sheet
    _writer->writeVariableText(plot.StyleSheet);
    //Scale type BS 75 plotsettings standard scale type
    _writer->writeBitShort((short) plot.ScaledFit);
    //Scale factor BD 147 plotsettings scale factor
    _writer->writeBitDouble(plot.StandardScale);
    //Paper image origin 2BD 148,149 plotsettings paper image origin
    _writer->write2BitDouble(plot.PaperImageOrigin);

    //R2004+:
    if (R2004Plus)
    {
        //Shade plot mode BS 76
        _writer->writeBitShort((short) plot.ShadePlotMode);
        //Shade plot res.Level BS 77
        _writer->writeBitShort((short) plot.ShadePlotResolutionMode);
        //Shade plot custom DPI BS 78
        _writer->writeBitShort(plot.ShadePlotDPI);

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
    _writer->writeVariableText(scale.Name);
    //BD	140	Paper units(numerator)
    _writer->writeBitDouble(scale.PaperUnits);
    //BD	141	Drawing units(denominator, divided by 10).
    _writer->writeBitDouble(scale.DrawingUnits);
    //B	290	Has unit scale
    _writer->writeBit(scale.IsUnitScale);
}

void DwgObjectWriter::writeSortEntitiesTable(SortEntitiesTable *sortEntitiesTable)
{
    //parenthandle (soft pointer)
    _writer->handleReference(DwgReferenceType::SoftPointer, sortEntitiesTable.BlockOwner);

    //Common:
    //Numentries BL number of entries
    _writer->writeBitLong(sortEntitiesTable.Sorters.Count());

    for (auto &&item in sortEntitiesTable.Sorters)
    {
        //Sort handle(numentries of these, CODE 0, i.e.part of the main bit stream, not of the handle bit stream!).
        //The sort handle does not have to point to an entity (but it can).
        //This is just the handle used for determining the drawing order of the entity specified by the entity handle in the handle bit stream.
        //When the sortentstable doesn’t have a
        //mapping from entity handle to sort handle, then the entity’s own handle is used for sorting.
        _writer->handleReference(item.Handle);
        _writer->handleReference(DwgReferenceType::SoftPointer, item.Entity);
    }
}

void DwgObjectWriter::writeXRecord(XRecord *xrecord)
{
    MemoryStream stream = new MemoryStream();
    StreamIO ms = new StreamIO(stream);
    ms.EndianConverter = new LittleEndianConverter();

    for (XRecord.Entry entry in xrecord.Entries)
    {
        if (entry.Value == nullptr)
        {
            continue;
        }

        ms.Write<short>((short) entry.Code);
        GroupCodeValueType groupValueType = GroupCodeValue.TransformValue(entry.Code);

        switch (groupValueType)
        {
            case GroupCodeValueType.Byte:
            case GroupCodeValueType.Bool:
                ms.Write(Convert.ToByte(entry.Value, System.Globalization.CultureInfo.InvariantCulture));
                break;
            case GroupCodeValueType.Int16:
            case GroupCodeValueType.ExtendedDataInt16:
                ms.Write(Convert.ToInt16(entry.Value, System.Globalization.CultureInfo.InvariantCulture));
                break;
            case GroupCodeValueType.Int32:
            case GroupCodeValueType.ExtendedDataInt32:
                ms.Write(Convert.ToInt32(entry.Value, System.Globalization.CultureInfo.InvariantCulture));
                break;
            case GroupCodeValueType.Int64:
                ms.Write(Convert.ToInt64(entry.Value, System.Globalization.CultureInfo.InvariantCulture));
                break;
            case GroupCodeValueType.Double:
            case GroupCodeValueType.ExtendedDataDouble:
                        double d = (entry.Value as double?).Value;
                        ms.Write<double, LittleEndianConverter>(d);
                        break;
            case GroupCodeValueType.Point3D:
                        XYZ xyz = (entry.Value as XYZ?).Value;
                        ms.Write<double, LittleEndianConverter>(xyz.X);
                        ms.Write<double, LittleEndianConverter>(xyz.Y);
                        ms.Write<double, LittleEndianConverter>(xyz.Z);
                        break;
            case GroupCodeValueType.Chunk:
            case GroupCodeValueType.ExtendedDataChunk:
                unsigned char[] array = (unsigned char[]) entry.Value;
                ms.Write((unsigned char) array.Length);
                ms.WriteBytes(array);
                break;
            case GroupCodeValueType.String:
            case GroupCodeValueType.ExtendedDataString:
            case GroupCodeValueType.Handle:
                string text = (string) entry.Value;

                if (R2007Plus)
                {
                    if (string.IsNullOrEmpty(text))
                    {
                        ms.Write<short, LittleEndianConverter>(0);
                        return;
                    }

                    ms.Write<short, LittleEndianConverter>((short) text.Length);
                    ms.Write(text, System.Text.Encoding.Unicode);
                }
                else if (string.IsNullOrEmpty(text))
                {
                    ms.Write<short, LittleEndianConverter>(0);
                    ms.Write((unsigned char) CadUtils.GetCodeIndex((CodePage) _writer.Encoding.CodePage));
                }
                else
                {
                    ms.Write<short, LittleEndianConverter>((short) text.Length);
                    ms.Write((unsigned char) CadUtils.GetCodeIndex((CodePage) _writer.Encoding.CodePage));
                    ms.Write(text, _writer.Encoding);
                }
                break;
            case GroupCodeValueType.ObjectId:
            case GroupCodeValueType.ExtendedDataHandle:
                        ulong u = (entry.Value as ulong?).Value;
                        ms.Write<ulong, LittleEndianConverter>(u);
                        break;
            default:
                throw new NotSupportedException();
        }
    }

    //Common:
    //Numdatabytes BL number of databytes
    _writer->writeBitLong((int) ms.Length);
    _writer->writeBytes(stream.GetBuffer());

    //R2000+:
    if (R2000Plus)
    {
        //Cloning flag BS 280
        _writer->writeBitShort((short) xrecord.CloningFlags);
    }
}


}// namespace dwg
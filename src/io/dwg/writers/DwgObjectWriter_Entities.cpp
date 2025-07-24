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

#include <dwg/entities/Arc.h>
#include <dwg/entities/AttributeBase.h>
#include <dwg/entities/AttributeDefinition.h>
#include <dwg/entities/AttributeEntity.h>
#include <dwg/entities/CadWipeoutBase.h>
#include <dwg/entities/Circle.h>
#include <dwg/entities/Dimension.h>
#include <dwg/entities/DimensionAligned.h>
#include <dwg/entities/DimensionAngular2Line.h>
#include <dwg/entities/DimensionAngular3Pt.h>
#include <dwg/entities/DimensionDiameter.h>
#include <dwg/entities/DimensionLinear.h>
#include <dwg/entities/DimensionOrdinate.h>
#include <dwg/entities/DimensionRadius.h>
#include <dwg/entities/Ellipse.h>
#include <dwg/entities/Face3D.h>
#include <dwg/entities/Hatch.h>
#include <dwg/entities/HatchBoundaryPath.h>
#include <dwg/entities/HatchGradientPattern.h>
#include <dwg/entities/HatchPattern.h>
#include <dwg/entities/Insert.h>
#include <dwg/entities/Leader.h>
#include <dwg/entities/Line.h>
#include <dwg/entities/LwPolyline.h>
#include <dwg/entities/MLine.h>
#include <dwg/entities/MText.h>
#include <dwg/entities/MultiLeader.h>
#include <dwg/entities/Point.h>
#include <dwg/entities/PolyfaceMesh.h>
#include <dwg/entities/Ray.h>
#include <dwg/entities/Seqend.h>
#include <dwg/entities/Shape.h>
#include <dwg/entities/Solid.h>
#include <dwg/entities/Spline.h>
#include <dwg/entities/TextEntity.h>
#include <dwg/entities/Tolerance.h>
#include <dwg/entities/Viewport.h>
#include <dwg/entities/XLine.h>
#include <dwg/entities/collection/AttributeEntitySeqendCollection.h>
#include <dwg/entities/collection/VertexFaceRecordCollection.h>
#include <dwg/entities/collection/VertexSeqendCollection.h>
#include <dwg/io/dwg/writers/DwgObjectWriter_p.h>
#include <dwg/io/dwg/writers/IDwgStreamWriter_p.h>
#include <dwg/objects/ImageDefinition.h>
#include <dwg/objects/MLineStyle.h>
#include <dwg/objects/MultiLeaderAnnotContext.h>
#include <dwg/objects/MultiLeaderStyle.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/DimensionStyle.h>
#include <dwg/tables/Layer.h>
#include <dwg/tables/LineType.h>

namespace dwg {

void DwgObjectWriter::writeEntity(Entity *entity) {}

void DwgObjectWriter::writeArc(Arc *arc)
{
    writeCircle(arc);
    _writer->writeBitDouble(arc->startAngle());
    _writer->writeBitDouble(arc->endAngle());
}

void DwgObjectWriter::writeAttribute(AttributeEntity *att)
{
    writeCommonAttData(att);
}

void DwgObjectWriter::writeAttDefinition(AttributeDefinition *attdef)
{
    writeCommonAttData(attdef);

    //R2010+:
    if (R2010Plus)
        //Version RC ?		Repeated??
        _writer->writeByte(attdef->version());

    //Common:
    //Prompt TV 3
    _writer->writeVariableText(attdef->prompt());
}

void DwgObjectWriter::writeCommonAttData(AttributeBase *att)
{
    writeTextEntity(att);

    //R2010+:
    if (R2010Plus)
    {
        //Version RC ?
        _writer->writeByte(att->version());
    }

    //R2018+:
    if (R2018Plus)
    {
        _writer->writeByte((unsigned char) att->attributeType());

        if (att->attributeType() == AttributeBase::AttributeType::MultiLine ||
            att->attributeType() == AttributeBase::AttributeType::ConstantMultiLine)
        {
            writeEntityMode(att->mtext());

            writeMText(att->mtext());

            //TODO: Write attribute MText data
            _writer->writeBitShort(0);
        }
    }

    //Common:
    //Tag TV 2
    _writer->writeVariableText(att->tag());
    //Field length BS 73 unused
    _writer->writeBitShort(0);
    //Flags RC 70 NOT bit-pair - coded.
    _writer->writeByte((unsigned char) att->flags());

    //R2007 +:
    if (R2007Plus)
    {
        //Lock position flag B 280
        _writer->writeBit(att->isReallyLocked());
    }
}

void DwgObjectWriter::writeCircle(Circle *circle)
{
    _writer->write3BitDouble(circle->center());
    _writer->writeBitDouble(circle->radius());
    _writer->writeBitThickness(circle->thickness());
    _writer->writeBitExtrusion(circle->normal());
}

void DwgObjectWriter::writeCommonDimensionData(Dimension *dimension)
{
    //R2010:
    if (R2010Plus)
    {
        //Version RC 280 0 = R2010
        _writer->writeByte(dimension->version());
    }

    //Common:
    //Extrusion 3BD 210
    _writer->write3BitDouble(dimension->normal());
    //Text midpt 2RD 11 See DXF documentation.
    _writer->write2RawDouble(dimension->textMiddlePoint().to2D());
    //Elevation BD 11 Z - coord for the ECS points(11, 12, 16).
    //12 (The 16 remains (0,0,0) in entgets of this entity,
    //since the 16 is not used in this type of dimension
    //and is not present in the binary form here.)
    _writer->writeBitDouble(dimension->insertionPoint().Z);

    unsigned char flags = 0;
    flags |= dimension->isTextUserDefinedLocation() ? (unsigned char) 0b00 : (unsigned char) 0b01;
    _writer->writeByte(flags);
    //User text TV 1
    _writer->writeVariableText(dimension->text());
    //Text rot BD 53 See DXF documentation.
    _writer->writeBitDouble(dimension->textRotation());
    //Horiz dir BD 51 See DXF documentation.
    _writer->writeBitDouble(dimension->horizontalDirection());
    //Ins X - scale BD 41 Undoc'd. These apply to the insertion of the
    //Ins Y - scale BD 42 anonymous block. None of them can be
    //Ins Z - scale BD 43 dealt with via entget/entmake/entmod.
    _writer->write3BitDouble(XYZ::Zero);
    //Ins rotation BD 54 The last 2(43 and 54) are reported by DXFOUT(when not default values).
    //ALL OF THEM can be set via DXFIN, however.
    _writer->writeBitDouble(0);

    //R2000 +:
    if (R2000Plus)
    {
        //Attachment Point BS 71
        _writer->writeBitShort((short) dimension->attachmentPoint());
        //Linespacing Style BS 72
        _writer->writeBitShort((short) dimension->lineSpacingStyle());
        //Linespacing Factor BD 41
        _writer->writeBitDouble(dimension->lineSpacingFactor());
        //Actual Measurement BD 42
        _writer->writeBitDouble(dimension->measurement());
    }
    //R2007 +:
    if (R2007Plus)
    {
        //Unknown B 73
        _writer->writeBit(false);
        //Flip arrow1 B 74
        _writer->writeBit(false);
        //Flip arrow2 B 75
        _writer->writeBit(false);
    }
    //Common:
    //12 - pt 2RD 12 See DXF documentation.
    _writer->write2RawDouble(dimension->insertionPoint().to2D());

    //Common Entity Handle Data
    //H 3 DIMSTYLE(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, dimension->style());
    //H 2 anonymous BLOCK(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, dimension->block());
}

void DwgObjectWriter::writeDimensionLinear(DimensionLinear *dimension)
{
    writeDimensionAligned(dimension);

    //Dim rot BD 50 Linear dimension rotation; see DXF documentation.
    _writer->writeBitDouble(dimension->rotation());
}

void DwgObjectWriter::writeDimensionAligned(DimensionAligned *dimension)
{
    //Common:
    //13 - pt 3BD 13 See DXF documentation.
    _writer->write3BitDouble(dimension->firstPoint());
    //14 - pt 3BD 14 See DXF documentation.
    _writer->write3BitDouble(dimension->secondPoint());
    //10 - pt 3BD 10 See DXF documentation.
    _writer->write3BitDouble(dimension->definitionPoint());

    //Ext ln rot BD 52 Extension line rotation; see DXF documentation.
    _writer->writeBitDouble(dimension->extLineRotation());
}

void DwgObjectWriter::writeDimensionRadius(DimensionRadius *dimension)
{
    //Common:
    //10 - pt 3BD 10 See DXF documentation.
    _writer->write3BitDouble(dimension->definitionPoint());
    //15-pt 3BD 15 See DXF documentation.
    _writer->write3BitDouble(dimension->angleVertex());
    //Leader len D 40 Leader length.
    _writer->writeBitDouble(dimension->leaderLength());
}

void DwgObjectWriter::writeDimensionAngular2Line(DimensionAngular2Line *dimension)
{
    //Common:
    //16-pt 2RD 16 See DXF documentation.
    _writer->write2RawDouble(dimension->dimensionArc().to2D());

    //13 - pt 3BD 13 See DXF documentation.
    _writer->write3BitDouble(dimension->firstPoint());
    //14 - pt 3BD 14 See DXF documentation.
    _writer->write3BitDouble(dimension->secondPoint());
    //15-pt 3BD 15 See DXF documentation.
    _writer->write3BitDouble(dimension->angleVertex());
    //10 - pt 3BD 10 See DXF documentation.
    _writer->write3BitDouble(dimension->definitionPoint());
}

void DwgObjectWriter::writeDimensionAngular3Pt(DimensionAngular3Pt *dimension)
{
    //Common:
    //10 - pt 3BD 10 See DXF documentation.
    _writer->write3BitDouble(dimension->definitionPoint());
    //13 - pt 3BD 13 See DXF documentation.
    _writer->write3BitDouble(dimension->firstPoint());
    //14 - pt 3BD 14 See DXF documentation.
    _writer->write3BitDouble(dimension->secondPoint());
    //15-pt 3BD 15 See DXF documentation.
    _writer->write3BitDouble(dimension->angleVertex());
}

void DwgObjectWriter::writeDimensionDiameter(DimensionDiameter *dimension)
{
    //Common:
    //10 - pt 3BD 10 See DXF documentation.
    _writer->write3BitDouble(dimension->definitionPoint());
    //15-pt 3BD 15 See DXF documentation.
    _writer->write3BitDouble(dimension->angleVertex());
    //Leader len D 40 Leader length.
    _writer->writeBitDouble(dimension->leaderLength());
}

void DwgObjectWriter::writeDimensionOrdinate(DimensionOrdinate *dimension)
{
    //Common:
    //10 - pt 3BD 10 See DXF documentation.
    _writer->write3BitDouble(dimension->definitionPoint());
    //13 - pt 3BD 13 See DXF documentation.
    _writer->write3BitDouble(dimension->featureLocation());
    //14 - pt 3BD 14 See DXF documentation.
    _writer->write3BitDouble(dimension->leaderEndpoint());

    unsigned char flag = (unsigned char) (dimension->isOrdinateTypeX() ? 1 : 0);
    _writer->writeByte(flag);
}

void DwgObjectWriter::writeEllipse(Ellipse *ellipse)
{
    _writer->write3BitDouble(ellipse->center());
    _writer->write3BitDouble(ellipse->endPoint());
    _writer->write3BitDouble(ellipse->normal());
    _writer->writeBitDouble(ellipse->radiusRatio());
    _writer->writeBitDouble(ellipse->startParameter());
    _writer->writeBitDouble(ellipse->endParameter());
}

void DwgObjectWriter::writeInsert(Insert *insert)
{
    //Ins pt 3BD 10
    _writer->write3BitDouble(insert->insertPoint());

    //R13-R14 Only:
    if (R13_14Only)
    {
        //X Scale BD 41
        _writer->writeBitDouble(insert->XScale());
        //Y Scale BD 42
        _writer->writeBitDouble(insert->YScale());
        //Z Scale BD 43
        _writer->writeBitDouble(insert->ZScale());
    }

    //R2000 + Only:
    if (R2000Plus)
    {
        //Data flags BB
        //Scale Data Varies with Data flags:
        if (insert->XScale() == 1.0 && insert->YScale() == 1.0 && insert->ZScale() == 1.0)
        {
            //11 - scale is (1.0, 1.0, 1.0), no data stored.
            _writer->write2Bits(3);
        }
        else if (insert->XScale() == insert->YScale() && insert->XScale() == insert->ZScale())
        {
            //10 - 41 value stored as a RD, and 42 & 43 values are not stored, assumed equal to 41 value.
            _writer->write2Bits(2);
            _writer->writeRawDouble(insert->XScale());
        }
        else if (insert->XScale() == 1.0)
        {
            //01 - 41 value is 1.0, 2 DD's are present, each using 1.0 as the default value, representing the 42 and 43 values.
            _writer->write2Bits(1);
            _writer->writeBitDoubleWithDefault(insert->YScale(), 1.0);
            _writer->writeBitDoubleWithDefault(insert->ZScale(), 1.0);
        }
        else
        {
            //00 - 41 value stored as a RD, followed by a 42 value stored as DD (use 41 for default value), and a 43 value stored as a DD(use 41 value for default value).
            _writer->write2Bits(0);
            _writer->writeRawDouble(insert->XScale());
            _writer->writeBitDoubleWithDefault(insert->YScale(), insert->XScale());
            _writer->writeBitDoubleWithDefault(insert->ZScale(), insert->XScale());
        }
    }

    //Common:
    //Rotation BD 50
    _writer->writeBitDouble(insert->rotation());
    //Extrusion 3BD 210
    _writer->write3BitDouble(insert->normal());
    //Has ATTRIBs B 66 Single bit; 1 if ATTRIBs follow.
    _writer->writeBit(insert->hasAttributes());

    //R2004+:
    if (R2004Plus && insert->hasAttributes())
    {
        //Owned Object Count BL Number of objects owned by this object.
        _writer->writeBitLong(insert->attributes()->size());
    }

    if (insert->isMultiple())
    {
        //Common:
        //Numcols BS 70
        _writer->writeBitShort((short) insert->columnCount());
        //Numrows BS 71
        _writer->writeBitShort((short) insert->rowCount());
        //Col spacing BD 44
        _writer->writeBitDouble(insert->columnSpacing());
        //Row spacing BD 45
        _writer->writeBitDouble(insert->rowSpacing());
    }

    //Common:
    //Common Entity Handle Data
    //H 2 BLOCK HEADER(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, insert->block());

    if (!insert->hasAttributes())
    {
        return;
    }

    //R13 - R2000:
    if (_version >= ACadVersion::AC1012 && _version <= ACadVersion::AC1015)
    {
        _writer->handleReference(DwgReferenceType::SoftPointer, insert->attributes()->front());
        _writer->handleReference(DwgReferenceType::SoftPointer, insert->attributes()->back());
    }
    //R2004+:
    else if (R2004Plus)
    {
        for (auto att = insert->attributes()->begin(); att != insert->attributes()->end(); ++att)
        {
            //H[ATTRIB(hard owner)] Repeats "Owned Object Count" times.
            _writer->handleReference(DwgReferenceType::HardOwnership, *att);
        }
    }

    //Common:
    //H[SEQEND(hard owner)] if 66 bit set
    _writer->handleReference(DwgReferenceType::HardOwnership, insert->attributes()->seqend());
}

void DwgObjectWriter::writeFace3D(Face3D *face)
{
    //R13 - R14 Only:
    if (R13_14Only)
    {
        //1st corner 3BD 10
        _writer->write3BitDouble(face->firstCorner());
        //2nd corner 3BD 11
        _writer->write3BitDouble(face->secondCorner());
        //3rd corner 3BD 12
        _writer->write3BitDouble(face->thirdCorner());
        //4th corner 3BD 13
        _writer->write3BitDouble(face->fourthCorner());
        //Invis flags BS 70 Invisible edge flags
        _writer->writeBitShort((short) face->flags());
    }

    //R2000 +:
    if (R2000Plus)
    {
        bool noFlags = face->flags() == (int) InvisibleEdgeFlag::None;
        //Has no flag ind. B
        _writer->writeBit(noFlags);

        bool zIsZero = face->firstCorner().Z == 0.0;
        //Z is zero bit B
        _writer->writeBit(zIsZero);

        //1st corner x RD 10
        _writer->writeRawDouble(face->firstCorner().X);
        //1st corner y RD 20
        _writer->writeRawDouble(face->firstCorner().Y);

        if (!zIsZero)
        {
            //1st corner z RD 30 Present only if "Z is zero bit" is 0.
            _writer->writeRawDouble(face->firstCorner().Z);
        }

        //2nd corner 3DD 11 Use 10 value as default point
        _writer->write3BitDoubleWithDefault(face->secondCorner(), face->firstCorner());
        //3rd corner 3DD 12 Use 11 value as default point
        _writer->write3BitDoubleWithDefault(face->thirdCorner(), face->secondCorner());
        //4th corner 3DD 13 Use 12 value as default point
        _writer->write3BitDoubleWithDefault(face->fourthCorner(), face->thirdCorner());

        //Invis flags BS 70 Present it "Has no flag ind." is 0.
        if (!noFlags)
        {
            _writer->writeBitShort((short) face->flags());
        }
    }
}

void DwgObjectWriter::writeMLine(MLine *mline)
{
    //Scale BD 40
    _writer->writeBitDouble(mline->scaleFactor());
    //Just EC top (0), bottom(2), or center(1)
    _writer->writeByte((unsigned char) mline->justification());
    //Base point 3BD 10
    _writer->write3BitDouble(mline->startPoint());
    //Extrusion 3BD 210 etc.
    _writer->write3BitDouble(mline->normal());

    //Openclosed BS open (1), closed(3)
    _writer->writeBitShort((short) (mline->flags() & (MLineFlag::Closed) ? 3 : 1));

    int nlines = 0;
    if (mline->vertices().size() > 0)
    {
        nlines = mline->vertices().front().Segments.size();
    }
    //Linesinstyle RC 73
    _writer->writeByte((unsigned char) nlines);

    //Numverts BS 72
    _writer->writeBitShort((short) mline->vertices().size());

    for (auto v: mline->vertices())
    {
        //vertex 3BD
        _writer->write3BitDouble(v.Position);
        //vertex direction 3BD
        _writer->write3BitDouble(v.Direction);
        //miter direction 3BD
        _writer->write3BitDouble(v.Miter);

        // All the Vertices must have the same number of segments
        for (int i = 0; i < nlines; i++)
        {
            auto &&element = v.Segments[i];

            //numsegparms BS
            _writer->writeBitShort((short) element.Parameters.size());
            for (double p: element.Parameters)
            {
                //segparm BD segment parameter
                _writer->writeBitDouble(p);
            }

            //numareafillparms BS
            _writer->writeBitShort((short) element.AreaFillParameters.size());
            for (double afp: element.AreaFillParameters)
            {
                //areafillparm BD area fill parameter
                _writer->writeBitDouble(afp);
            }
        }
    }

    //H mline style oject handle (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, mline->style());
}

void DwgObjectWriter::writeLwPolyline(LwPolyline *lwPolyline)
{
    bool nbulges = false;
    bool ndiffwidth = false;
    for (auto &&item: lwPolyline->vertices())
    {
        if (!nbulges && item.Bulge != 0.0)
        {
            nbulges = true;
        }
        if (!ndiffwidth && (item.StartWidth != 0.0 || item.EndWidth != 0.0))
        {
            ndiffwidth = true;
        }
    }

    short flags = 0;

    if (lwPolyline->flags() & LwPolylineFlag::Plinegen)
    {
        flags = (short) (flags | 0x100);
    }

    if (lwPolyline->flags() & LwPolylineFlag::Closed)
    {
        flags = (short) (flags | 0x200);
    }

    if (lwPolyline->constantWidth() != 0.0)
    {
        flags = (short) (flags | 0x4);
    }

    if (lwPolyline->elevation() != 0.0)
    {
        flags = (short) (flags | 0x8);
    }

    if (lwPolyline->thickness() != 0.0)
    {
        flags = (short) (flags | 2);
    }

    if (lwPolyline->normal() != XYZ::AxisZ)
    {
        flags = (short) (flags | 1);
    }

    if (nbulges)
    {
        flags = (short) (flags | 0x10);
    }
    //Skip ids, not necessary
    if (ndiffwidth)
    {
        flags = (short) (flags | 0x20);
    }

    //B : bytes containing the LWPOLYLINE entity data.
    //This excludes the common entity data.
    //More specifically: it starts at the LWPOLYLINE flags (BS), and ends with the width array (BD).
    _writer->writeBitShort(flags);

    if (lwPolyline->constantWidth() != 0.0)
    {
        _writer->writeBitDouble(lwPolyline->constantWidth());
    }
    if (lwPolyline->elevation() != 0.0)
    {
        _writer->writeBitDouble(lwPolyline->elevation());
    }
    if (lwPolyline->thickness() != 0.0)
    {
        _writer->writeBitDouble(lwPolyline->thickness());
    }
    if (lwPolyline->normal() != XYZ::AxisZ)
    {
        _writer->write3BitDouble(lwPolyline->normal());
    }

    _writer->writeBitLong(lwPolyline->vertices().size());

    if (nbulges)
    {
        _writer->writeBitLong(lwPolyline->vertices().size());
    }

    if (ndiffwidth)
    {
        _writer->writeBitLong(lwPolyline->vertices().size());
    }

    if (R13_14Only)
    {
        for (int i = 0; i < lwPolyline->vertices().size(); i++)
        {
            _writer->write2RawDouble(lwPolyline->vertices()[i].Location);
        }
    }

    if (R2000Plus && lwPolyline->vertices().size() > 0)
    {
        auto &&last = lwPolyline->vertices().at(0);
        _writer->write2RawDouble(last.Location);
        for (int j = 1; j < lwPolyline->vertices().size(); j++)
        {
            auto &&curr = lwPolyline->vertices().at(j);
            _writer->write2BitDoubleWithDefault(curr.Location, last.Location);
            last = curr;
        }
    }

    if (nbulges)
    {
        for (int k = 0; k < lwPolyline->vertices().size(); k++)
        {
            _writer->writeBitDouble(lwPolyline->vertices()[k].Bulge);
        }
    }

    if (ndiffwidth)
    {
        for (int l = 0; l < lwPolyline->vertices().size(); l++)
        {
            _writer->writeBitDouble(lwPolyline->vertices()[l].StartWidth);
            _writer->writeBitDouble(lwPolyline->vertices()[l].EndWidth);
        }
    }
}

void DwgObjectWriter::writeHatch(Hatch *hatch)
{
    //R2004+:
    if (R2004Plus)
    {
        HatchGradientPattern *gradient = hatch->gradientColor();//TODO: set default ?? HatchGradientPattern.Default;

        //Is Gradient Fill BL 450 Non-zero indicates a gradient fill is used.
        _writer->writeBitLong(gradient->enabled() ? 1 : 0);

        //Reserved BL 451
        _writer->writeBitLong(gradient->reserved());
        //Gradient Angle BD 460
        _writer->writeBitDouble(gradient->angle());
        //Gradient Shift BD 461
        _writer->writeBitDouble(gradient->shift());
        //Single Color Grad.BL 452
        _writer->writeBitLong(gradient->isSingleColorGradient() ? 1 : 0);
        //Gradient Tint BD 462
        _writer->writeBitDouble(gradient->colorTint());

        //# of Gradient Colors BL 453
        _writer->writeBitLong(gradient->colors().size());
        for (auto &&color: gradient->colors())
        {
            //Gradient Value double BD 463
            _writer->writeBitDouble(color.value);
            //RGB Color
            _writer->writeCmColor(color.color);
        }

        //Gradient Name TV 470
        _writer->writeVariableText(gradient->name());
    }

    //Common:
    //Z coord BD 30 X, Y always 0.0
    _writer->writeBitDouble(hatch->elevation());
    //Extrusion 3BD 210
    _writer->write3BitDouble(hatch->normal());
    //Name TV 2 name of hatch
    _writer->writeVariableText(hatch->pattern()->name());
    //Solidfill B 70 1 if solidfill, else 0
    _writer->writeBit(hatch->isSolid());
    //Associative B 71 1 if associative, else 0
    _writer->writeBit(hatch->isAssociative());

    //Numpaths BL 91 Number of paths enclosing the hatch
    _writer->writeBitLong(hatch->paths().size());
    bool hasDerivedBoundary = false;
    for (auto &&boundaryPath: hatch->paths())
    {
        //Pathflag BL 92 Path flag
        _writer->writeBitLong((int) boundaryPath->flags());

        if (boundaryPath->flags() & BoundaryPathFlag::Derived)
        {
            hasDerivedBoundary = true;
        }

        if (boundaryPath->flags() & BoundaryPathFlag::Polyline)
        {
            HatchBoundaryPath::HBP_Polyline *pline =
                    dynamic_cast<HatchBoundaryPath::HBP_Polyline *>(boundaryPath->edges().front());

            //bulgespresent B 72 bulges are present if 1
            _writer->writeBit(pline->hasBulge());
            //closed B 73 1 if closed
            _writer->writeBit(pline->isClosed());

            //numpathsegs BL 91 number of path segments
            _writer->writeBitLong(pline->vertices().size());
            for (auto &&i = 0; i < pline->vertices().size(); ++i)
            {
                auto &&vertex = pline->vertices().at(i);

                _writer->write2RawDouble(XY(vertex.X, vertex.Y));
                if (pline->hasBulge())
                {
                    _writer->writeBitDouble(vertex.Z);
                }
            }
        }
        else
        {
            //Numpathsegs BL 93 number of segments in this path
            _writer->writeBitLong(boundaryPath->edges().size());
            for (auto &&edge: boundaryPath->edges())
            {
                //pathtypestatus RC 72 type of path
                auto et = edge->type();
                _writer->writeByte((unsigned char) edge->type());

                switch (et)
                {
                    case HatchBoundaryPath::HBP_EdgeType::HBP_Line:
                        {
                            auto line = dynamic_cast<HatchBoundaryPath::HBP_Line *>(edge);
                            //pt0 2RD 10 first endpoint
                            _writer->write2RawDouble(line->start());
                            //pt1 2RD 11 second endpoint
                            _writer->write2RawDouble(line->end());
                            break;
                        }
                    case HatchBoundaryPath::HBP_EdgeType::HBP_CircularArc:
                        {
                            auto arc = dynamic_cast<HatchBoundaryPath::HBP_Arc *>(edge);
                            //pt0 2RD 10 center
                            _writer->write2RawDouble(arc->center());
                            //radius BD 40 radius
                            _writer->writeBitDouble(arc->radius());
                            //startangle BD 50 start angle
                            _writer->writeBitDouble(arc->startAngle());
                            //endangle BD 51 endangle
                            _writer->writeBitDouble(arc->endAngle());
                            //isccw B 73 1 if counter clockwise, otherwise 0
                            _writer->writeBit(arc->counterClockWise());
                            break;
                        }
                    case HatchBoundaryPath::HBP_EdgeType::HBP_EllipticArc:
                        {
                            auto ellipse = dynamic_cast<HatchBoundaryPath::HBP_Ellipse *>(edge);
                            //pt0 2RD 10 center
                            _writer->write2RawDouble(ellipse->center());
                            //endpoint 2RD 11 endpoint of major axis
                            _writer->write2RawDouble(ellipse->majorAxisEndPoint());
                            //minormajoratio BD 40 ratio of minor to major axis
                            _writer->writeBitDouble(ellipse->minorToMajorRatio());
                            //startangle BD 50 start angle
                            _writer->writeBitDouble(ellipse->startAngle());
                            //endangle BD 51 endangle
                            _writer->writeBitDouble(ellipse->endAngle());
                            //isccw B 73 1 if counter clockwise; otherwise 0
                            _writer->writeBit(ellipse->counterClockWise());
                            break;
                        }
                    case HatchBoundaryPath::HBP_EdgeType::HBP_Spline:
                        {
                            auto splineEdge = dynamic_cast<HatchBoundaryPath::HBP_Spline *>(edge);
                            //degree BL 94 degree of the spline
                            _writer->writeBitLong(splineEdge->degree());
                            //isrational B 73 1 if rational(has weights), else 0
                            _writer->writeBit(splineEdge->rational());
                            //isperiodic B 74 1 if periodic, else 0
                            _writer->writeBit(splineEdge->periodic());

                            //numknots BL 95 number of knots
                            _writer->writeBitLong(splineEdge->knots().size());
                            //numctlpts BL 96 number of control points
                            _writer->writeBitLong(splineEdge->controlPoints().size());
                            for (auto k: splineEdge->knots())
                            {
                                //knot BD 40 knot value
                                _writer->writeBitDouble(k);
                            }

                            for (int p = 0; p < splineEdge->controlPoints().size(); ++p)
                            {
                                //pt0 2RD 10 control point
                                _writer->write2RawDouble(splineEdge->controlPoints().at(p).to2D());

                                if (splineEdge->rational())
                                    //weight BD 40 weight
                                    _writer->writeBitDouble(splineEdge->controlPoints().at(p).Z);
                            }

                            //R24:
                            if (R2010Plus)
                            {
                                //Numfitpoints BL 97 number of fit points
                                _writer->writeBitLong(splineEdge->fitPoints().size());
                                if (!splineEdge->fitPoints().empty())
                                {
                                    for (auto &&fp: splineEdge->fitPoints())
                                    {
                                        //Fitpoint 2RD 11
                                        _writer->write2RawDouble(fp);
                                    }

                                    //Start tangent 2RD 12
                                    _writer->write2RawDouble(splineEdge->startTangent());
                                    //End tangent 2RD 13
                                    _writer->write2RawDouble(splineEdge->endTangent());
                                }
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        //numboundaryobjhandles BL 97 Number of boundary object handles for this path
        _writer->writeBitLong(boundaryPath->entities().size());
        for (auto &&e: boundaryPath->entities())
        {
            //boundaryhandle H 330 boundary handle(soft pointer)
            _writer->handleReference(DwgReferenceType::SoftPointer, e);
        }
    }

    //style BS 75 style of hatch 0==odd parity, 1==outermost, 2==whole area
    _writer->writeBitShort((short) hatch->style());
    //patterntype BS 76 pattern type 0==user-defined, 1==predefined, 2==custom
    _writer->writeBitShort((short) hatch->patternType());

    if (!hatch->isSolid())
    {
        HatchPattern *pattern = hatch->pattern();
        _writer->writeBitDouble(hatch->patternAngle());
        _writer->writeBitDouble(hatch->patternScale());
        _writer->writeBit(hatch->isDouble());

        _writer->writeBitShort((short) pattern->lines().size());
        for (auto &&line: pattern->lines())
        {
            //angle BD 53 line angle
            _writer->writeBitDouble(line.Angle);
            //pt0 2BD 43 / 44 pattern through this point(X, Y)
            _writer->write2BitDouble(line.BasePoint);
            //offset 2BD 45 / 56 pattern line offset
            _writer->write2BitDouble(line.Offset);

            //  numdashes BS 79 number of dash length items
            _writer->writeBitShort((short) line.DashLengths.size());
            for (auto &&dl: line.DashLengths)
            {
                //dashlength BD 49 dash length
                _writer->writeBitDouble(dl);
            }
        }
    }

    if (hasDerivedBoundary)
    {
        //pixelsize BD 47 pixel size
        _writer->writeBitDouble(hatch->pixelSize());
    }

    //numseedpoints BL 98 number of seed points
    _writer->writeBitLong(hatch->seedPoints().size());
    for (auto sp: hatch->seedPoints())
    {
        //pt0 2RD 10 seed point
        _writer->write2RawDouble(sp);
    }
}

void DwgObjectWriter::writeLeader(Leader *leader)
{
    //Unknown bit B --- Always seems to be 0.
    _writer->writeBit(false);

    //Annot type BS --- Annotation type (NOT bit-coded):
    _writer->writeBitShort((short) leader->creationType());
    //path type BS ---
    _writer->writeBitShort((short) leader->pathType());

    //numpts BL --- number of points
    _writer->writeBitLong(leader->vertices().size());
    for (XYZ v: leader->vertices())
    {
        //point 3BD 10 As many as counter above specifies.
        _writer->write3BitDouble(v);
    }

    //Origin 3BD --- The leader plane origin (by default it's the first point).
    _writer->write3BitDouble(leader->vertices().empty() ? XYZ::Zero : leader->vertices().front());
    //Extrusion 3BD 210
    _writer->write3BitDouble(leader->normal());
    //x direction 3BD 211
    _writer->write3BitDouble(leader->horizontalDirection());
    //offsettoblockinspt 3BD 212 Used when the BLOCK option is used. Seems to be an unused feature.
    _writer->write3BitDouble(leader->blockOffset());

    //R14+:
    if (_version >= ACadVersion::AC1014)
    {
        //Endptproj 3BD --- A non-planar leader gives a point that projects the endpoint back to the annotation.
        _writer->write3BitDouble(leader->annotationOffset());
    }

    //R13-R14 Only:
    if (R13_14Only)
    {
        //DIMGAP BD --- The value of DIMGAP in the associated DIMSTYLE at the time of creation, multiplied by the dimscale in that dimstyle.
        _writer->writeBitDouble(leader->style()->dimensionLineGap());
    }


    //Common:
    if (_version <= ACadVersion::AC1021)
    {
        //Box height BD 40 MTEXT extents height. (A text box is slightly taller, probably by some DIMvar amount.)
        _writer->writeBitDouble(leader->textHeight());
        //Box width BD 41 MTEXT extents width. (A text box is slightly wider, probably by some DIMvar amount.)
        _writer->writeBitDouble(leader->textWidth());
    }

    //Hooklineonxdir B hook line is on x direction if 1
    _writer->writeBit(leader->hookLineDirection() == HookLineDirection::Same);
    //Arrowheadon B arrowhead on indicator
    _writer->writeBit(leader->arrowHeadEnabled());

    //R13-R14 Only:
    if (R13_14Only)
    {
        //Arrowheadtype BS arrowhead type
        _writer->writeBitShort(0);
        //Dimasz BD DIMASZ at the time of creation, multiplied by DIMSCALE
        _writer->writeBitDouble(leader->style()->arrowSize() * leader->style()->scaleFactor());
        //Unknown B
        _writer->writeBit(false);
        //Unknown B
        _writer->writeBit(false);
        //Unknown BS
        _writer->writeBitShort(0);
        //Byblockcolor BS
        _writer->writeBitShort(0);
        //Unknown B
        _writer->writeBit(false);
        //Unknown B
        _writer->writeBit(false);
    }

    //R2000+:
    if (R2000Plus)
    {
        //Unknown BS
        _writer->writeBitShort(0);
        //Unknown B
        _writer->writeBit(false);
        //Unknown B
        _writer->writeBit(false);
    }

    //H 340 Associated annotation
    _writer->handleReference(DwgReferenceType::HardPointer, nullptr);
    //H 2 DIMSTYLE (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, leader->style());
}

void DwgObjectWriter::writeMultiLeader(MultiLeader *multiLeader)
{
    if (R2010Plus)
    {
        //	270 Version, expected to be 2
        _writer->writeBitShort(2);
    }

    writeMultiLeaderAnnotContext(multiLeader->contextData());

    //	Multileader Common data
    //	340 Leader StyleId (handle)
    _writer->handleReference(DwgReferenceType::HardPointer, multiLeader->style());
    //	90  Property Override Flags (int32)
    _writer->writeBitLong((int) multiLeader->propertyOverrideFlags());
    //	170 LeaderLineType (short)
    _writer->writeBitShort((short) multiLeader->pathType());
    //	91  Leader LineColor (Color)
    _writer->writeCmColor(multiLeader->lineColor());
    //	341 LeaderLineTypeID (handle/LineType)
    _writer->handleReference(DwgReferenceType::HardPointer, multiLeader->leaderLineType());
    //	171 LeaderLine Weight
    _writer->writeBitLong((short) multiLeader->leaderLineWeight());

    //  290 Enable Landing
    _writer->writeBit(multiLeader->enableLanding());
    //  291 Enable Dogleg
    _writer->writeBit(multiLeader->enableDogleg());

    //  41  Dogleg Length / Landing distance
    _writer->writeBitDouble(multiLeader->landingDistance());
    //  342 Arrowhead ID
    _writer->handleReference(DwgReferenceType::HardPointer, multiLeader->arrowhead());
    //template.ArrowheadHandle = handleReference();
    //  42  Arrowhead Size
    _writer->writeBitDouble(multiLeader->arrowheadSize());
    //  172 Content Type
    _writer->writeBitShort((short) multiLeader->contentType());
    //  343 Text Style ID (handle/TextStyle)
    _writer->handleReference(DwgReferenceType::HardPointer, multiLeader->textStyle());//	Hard/soft??
                                                                                      //  173 Text Left Attachment Type
    _writer->writeBitShort((short) multiLeader->textLeftAttachment());
    //  95  Text Right Attachement Type
    _writer->writeBitShort((short) multiLeader->textRightAttachment());
    //  174 Text Angle Type
    _writer->writeBitShort((short) multiLeader->textAngle());
    //  175 Text Alignment Type
    _writer->writeBitShort((short) multiLeader->textAlignment());
    //  92  Text Color
    _writer->writeCmColor(multiLeader->textColor());
    //  292 Enable Frame Text
    _writer->writeBit(multiLeader->textFrame());
    //  344 Block Content ID
    _writer->handleReference(DwgReferenceType::HardPointer, multiLeader->blockContent());//	Hard/soft??
                                                                                         //  93  Block Content Color
    _writer->writeCmColor(multiLeader->blockContentColor());
    //  10  Block Content Scale
    _writer->write3BitDouble(multiLeader->blockContentScale());
    //  43  Block Content Rotation
    _writer->writeBitDouble(multiLeader->blockContentRotation());
    //  176 Block Content Connection Type
    _writer->writeBitShort((short) multiLeader->blockContentConnection());
    //  293 Enable Annotation Scale/Is annotative
    _writer->writeBit(multiLeader->enableAnnotationScale());

    //	R2007pre not supported

    //	BL Number of Block Labels
    int blockLabelCount = multiLeader->blockAttributes().size();
    _writer->writeBitLong(blockLabelCount);
    for (int bl = 0; bl < blockLabelCount; bl++)
    {
        //  330 Block Attribute definition handle (hard pointer)
        MultiLeader::BlockAttribute blockAttribute = multiLeader->blockAttributes().at(bl);
        _writer->handleReference(DwgReferenceType::HardPointer, blockAttribute.attributeDefinition);
        //  302 Block Attribute Text String
        _writer->writeVariableText(blockAttribute.text);
        //  177 Block Attribute Index
        _writer->writeBitShort(blockAttribute.index);
        //  44  Block Attribute Width
        _writer->writeBitDouble(blockAttribute.width);
    }

    //  294 Text Direction Negative
    _writer->writeBit(multiLeader->textDirectionNegative());
    //  178 Text Align in IPE
    _writer->writeBitShort(multiLeader->textAligninIPE());
    //  179 Text Attachment Point
    _writer->writeBitShort((short) multiLeader->textAttachmentPoint());
    //	45	BD	ScaleFactor
    _writer->writeBitDouble(multiLeader->scaleFactor());

    if (R2010Plus)
    {
        //  271 Text attachment direction for MText contents
        _writer->writeBitShort((short) multiLeader->textAttachmentDirection());
        //  272 Bottom text attachment direction (sequence my be interchanged)
        _writer->writeBitShort((short) multiLeader->textBottomAttachment());
        //  273 Top text attachment direction
        _writer->writeBitShort((short) multiLeader->textTopAttachment());
    }

    if (R2013Plus)
    {
        //	295 Leader extended to text
        _writer->writeBit(multiLeader->extendedToText());
    }
}

void DwgObjectWriter::writeMultiLeaderAnnotContext(MultiLeaderAnnotContext *annotContext)
{
    auto writeLeaderLine = [&](MultiLeaderAnnotContext::LeaderLine leaderLine) {
        //	Points
        //	BL	-	Number of points
        //	3BD		10		Point
        _writer->writeBitLong(leaderLine.points.size());
        for (auto &&point: leaderLine.points)
        {
            //	3BD		10		Point
            _writer->write3BitDouble(point);
        }

        //	Add optional Break Info (one or more)
        //	BL	Break info count
        _writer->writeBitLong(leaderLine.breakInfoCount);
        if (leaderLine.breakInfoCount > 0)
        {
            //	BL	90		Segment index
            _writer->writeBitLong(leaderLine.segmentIndex);

            //	Start/end point pairs
            //	3BD	12	End point
            _writer->writeBitLong(leaderLine.startEndPoints.size());
            for (auto &&sep: leaderLine.startEndPoints)
            {
                //	3BD	11	Start Point
                _writer->write3BitDouble(sep.startPoint);
                _writer->write3BitDouble(sep.endPoint);
            }
        }

        //	BL	91	Leader line index
        _writer->writeBitLong(leaderLine.index);

        if (R2010Plus)
        {
            //	BS	170	Leader type(0 = invisible leader, 1 = straight leader, 2 = spline leader)
            _writer->writeBitShort((short) leaderLine.pathType);
            //	CMC	92	Line color
            _writer->writeCmColor(leaderLine.lineColor);
            //	H	340	Line type handle(hard pointer)
            _writer->handleReference(DwgReferenceType::HardPointer, leaderLine.lineType);
            //	BL	171	Line weight
            _writer->writeBitLong((short) leaderLine.lineWeight);
            //	BD	40	Arrow size
            _writer->writeBitDouble(leaderLine.arrowheadSize);
            //	H	341	Arrow symbol handle(hard pointer)
            _writer->handleReference(DwgReferenceType::HardPointer, leaderLine.arrowHead);

            //	BL	93	Override flags (1 = leader type, 2 = line color, 4 = line type, 8 = line weight, 16 = arrow size, 32 = arrow symbol(handle)
            _writer->writeBitLong((short) leaderLine.overrideFlags);
        }
    };

    auto writeLeaderRoot = [&](MultiLeaderAnnotContext::LeaderRoot leaderRoot) {
        //	B		290		Is content valid(ODA writes true)/DXF: Has Set Last Leader Line Point
        _writer->writeBit(leaderRoot.contentValid);
        //	B		291		Unknown(ODA writes true)/DXF: Has Set Dogleg Vector
        _writer->writeBit(true);
        //	3BD		10		Connection point/DXF: Last Leader Line Point
        _writer->write3BitDouble(leaderRoot.connectionPoint);
        //	3BD		11		Direction/DXF: Dogleg vector
        _writer->write3BitDouble(leaderRoot.direction);

        //	Break start/end point pairs
        //	BL		Number of break start / end point pairs
        //	3BD		12		Break start point
        //	3BD		13		Break end point
        _writer->writeBitLong(leaderRoot.breakStartEndPointsPairs.size());
        for (auto &&startEndPointPair: leaderRoot.breakStartEndPointsPairs)
        {
            _writer->write3BitDouble(startEndPointPair.startPoint);
            _writer->write3BitDouble(startEndPointPair.endPoint);
        }

        //	BL		90		Leader index
        _writer->writeBitLong(leaderRoot.leaderIndex);
        //	BD		40		Landing distance
        _writer->writeBitDouble(leaderRoot.landingDistance);

        //	Leader lines
        //	BL		Number of leader lines
        _writer->writeBitLong(leaderRoot.lines.size());
        for (auto &&leaderLine: leaderRoot.lines)
        {
            writeLeaderLine(leaderLine);
        }

        if (R2010Plus)
        {
            //	BS	271	Attachment direction(0 = horizontal, 1 = vertical, default is 0)
            _writer->writeBitShort((short) leaderRoot.textAttachmentDirection);
        }
    };


    //	BL	-	Number of leader roots
    int leaderRootCount = annotContext->leaderRoots().size();
    _writer->writeBitLong(leaderRootCount);
    for (int i = 0; i < leaderRootCount; i++)
    {
        writeLeaderRoot(annotContext->leaderRoots().at(i));
    }

    //	Common
    //	BD	40	Overall scale
    _writer->writeBitDouble(annotContext->scaleFactor());
    //	3BD	10	Content base point
    _writer->write3BitDouble(annotContext->contentBasePoint());
    //	BD	41	Text height
    _writer->writeBitDouble(annotContext->textHeight());
    //	BD	140	Arrow head size
    _writer->writeBitDouble(annotContext->arrowheadSize());
    //  BD	145	Landing gap
    _writer->writeBitDouble(annotContext->landingGap());
    //	BS	174	Style left text attachment type. See also MLEADER style left text attachment type for values. Relevant if mleader attachment direction is horizontal.
    _writer->writeBitShort((short) annotContext->textLeftAttachment());
    //	BS	175	Style right text attachment type. See also MLEADER style left text attachment type for values. Relevant if mleader attachment direction is horizontal.
    _writer->writeBitShort((short) annotContext->textRightAttachment());
    //	BS	176	Text align type (0 = left, 1 = center, 2 = right)
    _writer->writeBitShort((short) annotContext->textAlignment());
    //	BS	177	Attachment type (0 = content extents, 1 = insertion point).
    _writer->writeBitShort((short) annotContext->blockContentConnection());
    //	B	290	Has text contents
    _writer->writeBit(annotContext->hasTextContents());
    if (annotContext->hasTextContents())
    {
        //	TV	304	Text label
        _writer->writeVariableText(annotContext->textLabel());
        //	3BD	11	Normal vector
        _writer->write3BitDouble(annotContext->textNormal());
        //	H	340	Text style handle (hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, annotContext->textStyle());
        //	3BD	12	Location
        _writer->write3BitDouble(annotContext->textLocation());
        //	3BD	13	Direction
        _writer->write3BitDouble(annotContext->direction());
        //	BD	42	Rotation (radians)
        _writer->writeBitDouble(annotContext->textRotation());
        //	BD	43	Boundary width
        _writer->writeBitDouble(annotContext->boundaryWidth());
        //	BD	44	Boundary height
        _writer->writeBitDouble(annotContext->boundaryHeight());
        //	BD	45	Line spacing factor
        _writer->writeBitDouble(annotContext->lineSpacingFactor());
        //	BS	170	Line spacing style (1 = at least, 2 = exactly)
        _writer->writeBitShort((short) annotContext->lineSpacing());
        //	CMC	90	Text color
        _writer->writeCmColor(annotContext->textColor());
        //	BS	171	Alignment (1 = left, 2 = center, 3 = right)
        _writer->writeBitShort((short) annotContext->textAttachmentPoint());
        //	BS	172	Flow direction (1 = horizontal, 3 = vertical, 6 = by style)
        _writer->writeBitShort((short) annotContext->flowDirection());
        //	CMC	91	Background fill color
        _writer->writeCmColor(annotContext->backgroundFillColor());
        //	BD	141	Background scale factor
        _writer->writeBitDouble(annotContext->backgroundScaleFactor());
        //	BL	92	Background transparency
        _writer->writeBitLong(annotContext->backgroundTransparency());
        //	B	291	Is background fill enabled
        _writer->writeBit(annotContext->backgroundFillEnabled());
        //	B	292	Is background mask fill on
        _writer->writeBit(annotContext->backgroundMaskFillOn());
        //	BS	173	Column type (ODA writes 0), *TODO: what meaning for values?
        _writer->writeBitShort(annotContext->columnType());
        //	B	293	Is text height automatic?
        _writer->writeBit(annotContext->textHeightAutomatic());
        //	BD	142	Column width
        _writer->writeBitDouble(annotContext->columnWidth());
        //	BD	143	Column gutter
        _writer->writeBitDouble(annotContext->columnGutter());
        //	B	294	Column flow reversed
        _writer->writeBit(annotContext->columnFlowReversed());

        //	Column sizes
        //  BD	144	Column size
        int columnSizesCount = annotContext->columnSizes().size();
        _writer->writeBitLong(columnSizesCount);
        for (auto &&columnSize: annotContext->columnSizes())
        {
            _writer->writeBitDouble(columnSize);
        }

        //	B	295	Word break
        _writer->writeBit(annotContext->wordBreak());
        //	B	Unknown
        _writer->writeBit(false);
    }

    else if (annotContext->hasContentsBlock())
    {
        _writer->writeBit(annotContext->hasContentsBlock());

        //B	296	Has contents block
        //IF Has contents block
        //	H	341	AcDbBlockTableRecord handle (soft pointer)
        _writer->handleReference(DwgReferenceType::SoftPointer, annotContext->blockContent());
        //	3BD	14	Normal vector
        _writer->write3BitDouble(annotContext->blockContentNormal());
        //	3BD	15	Location
        _writer->write3BitDouble(annotContext->blockContentLocation());
        //	3BD	16	Scale vector
        _writer->write3BitDouble(annotContext->blockContentScale());
        //	BD	46	Rotation (radians)
        _writer->writeBitDouble(annotContext->blockContentRotation());
        //  CMC	93	Block color
        _writer->writeCmColor(annotContext->blockContentColor());
        //	BD (16)	47	16 doubles containing the complete transformation
        //	matrix. Order of transformation is:
        //	- Rotation,
        //	- OCS to WCS (using normal vector),
        //	- Scaling (using scale vector)
        //	- Translation (using location)
        auto &&m4 = annotContext->transformationMatrix();
        _writer->writeBitDouble(m4.m00);
        _writer->writeBitDouble(m4.m10);
        _writer->writeBitDouble(m4.m20);
        _writer->writeBitDouble(m4.m30);

        _writer->writeBitDouble(m4.m01);
        _writer->writeBitDouble(m4.m11);
        _writer->writeBitDouble(m4.m21);
        _writer->writeBitDouble(m4.m31);

        _writer->writeBitDouble(m4.m02);
        _writer->writeBitDouble(m4.m12);
        _writer->writeBitDouble(m4.m22);
        _writer->writeBitDouble(m4.m32);

        _writer->writeBitDouble(m4.m03);
        _writer->writeBitDouble(m4.m13);
        _writer->writeBitDouble(m4.m23);
        _writer->writeBitDouble(m4.m33);
    }
    //END IF Has contents block
    //END IF Has text contents

    //	3BD	110	Base point
    _writer->write3BitDouble(annotContext->basePoint());
    //	3BD	111	Base direction
    _writer->write3BitDouble(annotContext->baseDirection());
    //	3BD	112	Base vertical
    _writer->write3BitDouble(annotContext->baseVertical());
    //	B	297	Is normal reversed?
    _writer->writeBit(annotContext->normalReversed());

    if (R2010Plus)
    {
        //	BS	273	Style top attachment
        _writer->writeBitShort((short) annotContext->textTopAttachment());
        //	BS	272	Style bottom attachment
        _writer->writeBitShort((short) annotContext->textBottomAttachment());
    }
}

void DwgObjectWriter::writeLine(Line *line)
{
    //R13-R14 Only:
    if (R13_14Only)
    {
        //Start pt 3BD 10
        _writer->write3BitDouble(line->startPoint());
        //End pt 3BD 11
        _writer->write3BitDouble(line->endPoint());
    }


    //R2000+:
    if (R2000Plus)
    {
        //Z's are zero bit B
        bool flag = line->startPoint().Z == 0.0 && line->endPoint().Z == 0.0;
        _writer->writeBit(flag);

        //Start Point x RD 10
        _writer->writeRawDouble(line->startPoint().X);
        //End Point x DD 11 Use 10 value for default
        _writer->writeBitDoubleWithDefault(line->endPoint().X, line->startPoint().X);
        //Start Point y RD 20
        _writer->writeRawDouble(line->startPoint().Y);
        //End Point y DD 21 Use 20 value for default
        _writer->writeBitDoubleWithDefault(line->endPoint().Y, line->startPoint().Y);

        if (!flag)
        {
            //Start Point z RD 30 Present only if "Z's are zero bit" is 0
            _writer->writeRawDouble(line->startPoint().Z);
            //End Point z DD 31 Present only if "Z's are zero bit" is 0, use 30 value for default.
            _writer->writeBitDoubleWithDefault(line->endPoint().Z, line->startPoint().Z);
        }
    }

    //Common:
    //Thickness BT 39
    _writer->writeBitThickness(line->thickness());
    //Extrusion BE 210
    _writer->writeBitExtrusion(line->normal());
}

void DwgObjectWriter::writePoint(Point *point)
{
    //Point 3BD 10
    _writer->write3BitDouble(point->location());
    //Thickness BT 39
    _writer->writeBitThickness(point->thickness());
    //Extrusion BE 210
    _writer->writeBitExtrusion(point->normal());
    //X - axis ang BD 50 See DXF documentation
    _writer->writeBitDouble(point->rotation());
}

void DwgObjectWriter::writePolyfaceMesh(PolyfaceMesh *fm)
{
    //Numverts BS 71 Number of vertices in the mesh.
    _writer->writeBitShort((short) fm->vertices()->size());
    //Numfaces BS 72 Number of faces
    _writer->writeBitShort((short) fm->faces()->size());

    //R2004 +:
    if (R2004Plus)
    {
        //Owned Object Count BL Number of objects owned by this object.
        _writer->writeBitLong(fm->vertices()->size() + fm->faces()->size());
        for (auto v = fm->vertices()->begin(); v != fm->vertices()->end(); ++v)
        {
            //H[VERTEX(soft pointer)] Repeats "Owned Object Count" times.
            _writer->handleReference(DwgReferenceType::SoftPointer, *v);
        }
        for (auto f = fm->faces()->begin(); f != fm->faces()->end(); ++f)
        {
            _writer->handleReference(DwgReferenceType::SoftPointer, *f);
        }
    }

    //R13 - R2000:
    if (R13_15Only)
    {
        std::vector<CadObject *> child;
        child.insert(child.end(), fm->faces()->begin(), fm->faces()->end());
        CadObject *first = nullptr, *last = nullptr;
        if (!child.empty())
        {
            first = child.front();
            last = child.back();
        }

        //H first VERTEX(soft pointer)
        _writer->handleReference(DwgReferenceType::SoftPointer, first);
        //H last VERTEX(soft pointer)
        _writer->handleReference(DwgReferenceType::SoftPointer, last);
    }

    //Common:
    //H SEQEND(hard owner)
    _writer->handleReference(DwgReferenceType::SoftPointer, fm->vertices()->seqend());
}

void DwgObjectWriter::writePolyline2D(Polyline2D *pline)
{
    //Flags BS 70
    _writer->writeBitShort((short) pline->flags());
    //Curve type BS 75 Curve and smooth surface type.
    _writer->writeBitShort((short) pline->smoothSurface());
    //Start width BD 40 Default start width
    _writer->writeBitDouble(pline->startWidth());
    //End width BD 41 Default end width
    _writer->writeBitDouble(pline->endWidth());
    //Thickness BT 39
    _writer->writeBitThickness(pline->thickness());
    //Elevation BD 10 The 10-pt is (0,0,elev)
    _writer->writeBitDouble(pline->elevation());
    //Extrusion BE 210
    _writer->writeBitExtrusion(pline->normal());

    int count = pline->vertices()->size();
    //R2004+:
    if (R2004Plus)
    {
        //Owned Object Count BL Number of objects owned by this object.
        _writer->writeBitLong(count);
        for (int i = 0; i < count; i++)
        {
            _writer->handleReference(DwgReferenceType::HardOwnership, pline->vertices()->at(i));
        }
    }

    //R13-R2000:
    if (_version >= ACadVersion::AC1012 && _version <= ACadVersion::AC1015)
    {
        if (pline->vertices()->empty())
        {
            //H first VERTEX (soft pointer)
            _writer->handleReference(DwgReferenceType::SoftPointer, nullptr);
            //H last VERTEX (soft pointer)
            _writer->handleReference(DwgReferenceType::SoftPointer, nullptr);
        }
        else
        {
            //H first VERTEX (soft pointer)
            _writer->handleReference(DwgReferenceType::SoftPointer, pline->vertices()->front());
            //H last VERTEX (soft pointer)
            _writer->handleReference(DwgReferenceType::SoftPointer, pline->vertices()->back());
        }
    }

    //Common:
    //H SEQEND(hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, pline->vertices()->seqend());
}

void DwgObjectWriter::writePolyline3D(Polyline3D *pline)
{
    //Flags RC 70 NOT DIRECTLY THE 75. Bit-coded (76543210):
    //75 0 : Splined(75 value is 5)
    //1 : Splined(75 value is 6)
    //Should assign pline->SmoothSurface ??
    _writer->writeByte(0);

    //Flags RC 70 NOT DIRECTLY THE 70. Bit-coded (76543210):
    //0 : Closed(70 bit 0(1))
    //(Set 70 bit 3(8) because this is a 3D POLYLINE.)
    _writer->writeByte((unsigned char) (pline->flags() & PolylineFlag::ClosedPolylineOrClosedPolygonMeshInM) ? 1 : 0);

    //R2004+:
    if (R2004Plus)
    {
        //Owned Object Count BL Number of objects owned by this object.
        _writer->writeBitLong(pline->vertices()->size());

        for (auto vertex = pline->vertices()->begin(); vertex != pline->vertices()->end(); ++vertex)
        {
            _writer->handleReference(DwgReferenceType::HardOwnership, *vertex);
        }
    }

    //R13-R2000:
    if (_version >= ACadVersion::AC1012 && _version <= ACadVersion::AC1015)
    {
        if (pline->vertices()->empty())
        {
            _writer->handleReference(DwgReferenceType::SoftPointer, nullptr);
            _writer->handleReference(DwgReferenceType::SoftPointer, nullptr);
        }
        {
            //H first VERTEX (soft pointer)
            _writer->handleReference(DwgReferenceType::SoftPointer, pline->vertices()->front());
            //H last VERTEX (soft pointer)
            _writer->handleReference(DwgReferenceType::SoftPointer, pline->vertices()->back());
        }
    }

    //Common:
    //H SEQEND(hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, pline->vertices()->seqend());
}

void DwgObjectWriter::writeSeqend(Seqend *seqend)
{
    //for empty list seqend is nullptr
    if (seqend == nullptr)
        return;

    //Seqend does not have links for AC1015 or before (causes errors)
    Entity *prevHolder = _prev;
    Entity *nextHolder = _next;
    _prev = nullptr;
    _next = nullptr;

    writeCommonEntityData(seqend);
    registerObject(seqend);

    _prev = prevHolder;
    _next = nextHolder;
}

void DwgObjectWriter::writeShape(Shape *shape)
{
    //Ins pt 3BD 10
    _writer->write3BitDouble(shape->insertionPoint());
    //Scale BD 40 Scale factor, default value 1.
    _writer->writeBitDouble(shape->size());
    //Rotation BD 50 Rotation in radians, default value 0.
    _writer->writeBitDouble(shape->rotation());
    //Width factor BD 41 Width factor, default value 1.
    _writer->writeBitDouble(shape->relativeXScale());
    //Oblique BD 51 Oblique angle in radians, default value 0.
    _writer->writeBitDouble(shape->obliqueAngle());
    //Thickness BD 39
    _writer->writeBitDouble(shape->thickness());

    //Shapeno BS 2
    //This is the shape index.
    //In DXF the shape name is stored.
    //When reading from DXF, the shape is found by iterating over all the text styles
    //(SHAPEFILE, see paragraph 20.4.56) and when the text style contains a shape file,
    //iterating over all the shapes until the one with the matching name is found.
    _writer->writeBitShort((short) shape->shapeIndex());

    //Extrusion 3BD 210
    _writer->write3BitDouble(shape->normal());

    //H SHAPEFILE (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, nullptr);
}

void DwgObjectWriter::writeSolid(Solid *solid)
{
    //Thickness BT 39
    _writer->writeBitThickness(solid->thickness());

    //Elevation BD ---Z for 10 - 13.
    _writer->writeBitDouble((double) solid->firstCorner().Z);

    //1st corner 2RD 10
    _writer->writeRawDouble(solid->firstCorner().X);
    _writer->writeRawDouble(solid->firstCorner().Y);
    //2nd corner 2RD 11
    _writer->writeRawDouble(solid->secondCorner().X);
    _writer->writeRawDouble(solid->secondCorner().Y);
    //3rd corner 2RD 12
    _writer->writeRawDouble(solid->thirdCorner().X);
    _writer->writeRawDouble(solid->thirdCorner().Y);
    //4th corner 2RD 13
    _writer->writeRawDouble(solid->firstCorner().X);
    _writer->writeRawDouble(solid->firstCorner().Y);

    //Extrusion BE 210
    _writer->writeBitExtrusion(solid->normal());
}

void DwgObjectWriter::writeSolid3D(Solid3D *solid) {}

void DwgObjectWriter::writeCadImage(CadWipeoutBase *image)
{
    _writer->writeBitLong(image->classVersion());

    _writer->write3BitDouble(image->insertPoint());
    _writer->write3BitDouble(image->UVector());
    _writer->write3BitDouble(image->VVector());

    _writer->write2RawDouble(image->size());

    _writer->writeBitShort((short) image->flags());
    _writer->writeBit(image->clippingState());
    _writer->writeByte(image->brightness());
    _writer->writeByte(image->contrast());
    _writer->writeByte(image->fade());

    if (R2010Plus)
    {
        _writer->writeBit(image->clipMode() == ClipMode::Inside);
    }

    _writer->writeBitShort((short) image->clipType());


    switch (image->clipType())
    {
        case ClipType::Rectangular:
            _writer->write2RawDouble(image->clipBoundaryVertices().at(0));
            _writer->write2RawDouble(image->clipBoundaryVertices().at(1));
            break;
        case ClipType::Polygonal:
            _writer->writeBitLong(image->clipBoundaryVertices().size());
            for (auto &&v: image->clipBoundaryVertices())
            {
                _writer->write2RawDouble(v);
            }
            break;
    }

    _writer->handleReference(DwgReferenceType::HardPointer, image->definition());
    //Reactor, not needed
    _writer->handleReference(nullptr);
}

void DwgObjectWriter::writeSpline(Spline *spline)
{
    int scenario;
    //R2013+:
    if (R2013Plus)
    {
        //The scenario flag becomes 1 if the knot parameter is Custom or has no fit data, otherwise 2.
        if (spline->knotParameterization() == KnotParameterization::Custom || spline->fitPoints().size() == 0)
        {
            scenario = 1;
        }
        else
        {
            scenario = 2;
        }

        _writer->writeBitLong(scenario);
        _writer->writeBitLong((int) spline->flags1());
        _writer->writeBitLong((int) spline->knotParameterization());
    }
    else
    {
        scenario = (spline->fitPoints().size() <= 0) ? 1 : 2;
        if (scenario == 2 && spline->knotParameterization() != KnotParameterization::Chord)
        {
            scenario = 1;
        }

        //Scenario BL a flag which is 2 for fitpts only, 1 for ctrlpts/knots.
        _writer->writeBitLong(scenario);
    }

    //Common:
    //Degree BL degree of this spline
    _writer->writeBitLong(spline->degree());

    bool flag = spline->weights().size() > 0;
    switch (scenario)
    {
        case 1:
            {
                //Rational B flag bit 2
                _writer->writeBit(spline->flags() & SplineFlag::Rational);
                //Closed B flag bit 0
                _writer->writeBit(spline->flags() & SplineFlag::Closed);
                //Periodic B flag bit 1
                _writer->writeBit(spline->flags() & SplineFlag::Periodic);

                //Knot tol BD 42
                _writer->writeBitDouble(spline->knotTolerance());
                //Ctrl tol BD 43
                _writer->writeBitDouble(spline->controlPointTolerance());

                //Numknots BL 72 This is stored as a LONG
                _writer->writeBitLong(spline->knots().size());
                //Numctrlpts BL 73 Number of 10's (and 41's, if weighted) that follow.
                _writer->writeBitLong(spline->controlPoints().size());

                //Weight B Seems to be an echo of the 4 bit on the flag for "weights present".
                _writer->writeBit(flag);

                for (auto k: spline->knots())
                {
                    //Knot BD knot value
                    _writer->writeBitDouble(k);
                }

                for (int i = 0; i < spline->controlPoints().size(); i++)
                {
                    //Control pt 3BD 10
                    _writer->write3BitDouble(spline->controlPoints().at(i));
                    if (flag)
                    {
                        //Weight D 41 if present as indicated by 4 bit on flag
                        _writer->writeBitDouble(spline->weights().at(i));
                    }
                }
                break;
            }
        case 2:
            {
                //Fit Tol BD 44
                _writer->writeBitDouble(spline->fitTolerance());
                //Beg tan vec 3BD 12 Beginning tangent direction vector (normalized).
                _writer->write3BitDouble(spline->startTangent());
                //End tan vec 3BD 13 Ending tangent direction vector (normalized).
                _writer->write3BitDouble(spline->endTangent());
                //num fit pts BL 74 Number of fit points.
                _writer->writeBitLong(spline->fitPoints().size());

                for (auto &&fp: spline->fitPoints())
                {
                    //Fit pt 3BD
                    _writer->write3BitDouble(fp);
                }
                break;
            }
    }
}

void DwgObjectWriter::writeRay(Ray *ray)
{
    //Point 3BD 10
    _writer->write3BitDouble(ray->startPoint());
    //Vector 3BD 11
    _writer->write3BitDouble(ray->direction());
}

void DwgObjectWriter::writeTextEntity(TextEntity *text)
{
    //R13-14 Only:
    if (R13_14Only)
    {
        //Elevation BD ---
        _writer->writeBitDouble(text->insertPoint().Z);
        //Insertion pt 2RD 10
        _writer->writeRawDouble(text->insertPoint().X);
        _writer->writeRawDouble(text->insertPoint().Y);

        //Alignment pt 2RD 11
        _writer->writeRawDouble(text->alignmentPoint().X);
        _writer->writeRawDouble(text->alignmentPoint().Y);

        //Extrusion 3BD 210
        _writer->write3BitDouble(text->normal());
        //Thickness BD 39
        _writer->writeBitDouble(text->thickness());
        //Oblique ang BD 51
        _writer->writeBitDouble(text->obliqueAngle());
        //Rotation ang BD 50
        _writer->writeBitDouble(text->rotation());
        //Height BD 40
        _writer->writeBitDouble(text->height());
        //Width factor BD 41
        _writer->writeBitDouble(text->widthFactor());
        //Text value TV 1
        _writer->writeVariableText(text->value());
        //Generation BS 71
        _writer->writeBitShort((short) text->mirror());
        //Horiz align. BS 72
        _writer->writeBitShort((short) text->horizontalAlignment());
        //Vert align. BS 73
        _writer->writeBitShort((short) text->verticalAlignment());
    }
    else
    {
        //DataFlags RC Used to determine presence of subsquent data
        unsigned char dataFlags = 0;

        if (text->insertPoint().Z == 0.0)
        {
            dataFlags = (unsigned char) (dataFlags | 0b1);
        }
        if (text->alignmentPoint() == XYZ::Zero)
        {
            dataFlags = (unsigned char) (dataFlags | 0b10);
        }
        if (text->obliqueAngle() == 0.0)
        {
            dataFlags = (unsigned char) (dataFlags | 0b100);
        }
        if (text->rotation() == 0.0)
        {
            dataFlags = (unsigned char) (dataFlags | 0b1000);
        }
        if (text->widthFactor() == 1.0)
        {
            dataFlags = (unsigned char) (dataFlags | 0b10000);
        }
        if (text->mirror() == TextMirrorFlag::None)
        {
            dataFlags = (unsigned char) (dataFlags | 0b100000);
        }
        if (text->horizontalAlignment() == TextHorizontalAlignment::Left)
        {
            dataFlags = (unsigned char) (dataFlags | 0b1000000);
        }
        if (text->verticalAlignment() == TextVerticalAlignment::Baseline)
        {
            dataFlags = (unsigned char) (dataFlags | 0b10000000);
        }

        _writer->writeByte(dataFlags);

        //Elevation RD --- present if !(DataFlags & 0x01)
        if ((dataFlags & 0b1) == 0)
            _writer->writeRawDouble(text->insertPoint().Z);

        //Insertion pt 2RD 10
        _writer->writeRawDouble(text->insertPoint().X);
        _writer->writeRawDouble(text->insertPoint().Y);

        //Alignment pt 2DD 11 present if !(DataFlags & 0x02), use 10 & 20 values for 2 default values.
        if ((dataFlags & 0x2) == 0)
        {
            _writer->writeBitDoubleWithDefault(text->alignmentPoint().X, text->insertPoint().X);
            _writer->writeBitDoubleWithDefault(text->alignmentPoint().Y, text->insertPoint().Y);
        }

        //Extrusion BE 210
        _writer->writeBitExtrusion(text->normal());
        //Thickness BT 39
        _writer->writeBitThickness(text->thickness());

        //Oblique ang RD 51 present if !(DataFlags & 0x04)
        if ((dataFlags & 0x4) == 0)
            _writer->writeRawDouble(text->obliqueAngle());
        //Rotation ang RD 50 present if !(DataFlags & 0x08)
        if ((dataFlags & 0x8) == 0)
            _writer->writeRawDouble(text->rotation());

        //Height RD 40
        _writer->writeRawDouble(text->height());

        //Width factor RD 41 present if !(DataFlags & 0x10)
        if ((dataFlags & 0x10) == 0)
            _writer->writeRawDouble(text->widthFactor());

        //Text value TV 1
        _writer->writeVariableText(text->value());

        //Generation BS 71 present if !(DataFlags & 0x20)
        if ((dataFlags & 0x20) == 0)
            _writer->writeBitShort((short) text->mirror());
        //Horiz align. BS 72 present if !(DataFlags & 0x40)
        if ((dataFlags & 0x40) == 0)
            _writer->writeBitShort((short) text->horizontalAlignment());
        //Vert align. BS 73 present if !(DataFlags & 0x80)
        if ((dataFlags & 0x80) == 0)
            _writer->writeBitShort((short) text->verticalAlignment());
    }

    //Common:
    //Common Entity Handle Data H 7 STYLE(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, text->style());
}

void DwgObjectWriter::writeMText(MText *mtext)
{
    //Insertion pt3 BD 10 First picked point. (Location relative to text depends on attachment point (71).)
    _writer->write3BitDouble(mtext->insertPoint());
    //Extrusion 3BD 210 Undocumented; appears in DXF and entget, but ACAD doesn't even bother to adjust it to unit length.
    _writer->write3BitDouble(mtext->normal());
    //X-axis dir 3BD 11 Apparently the text x-axis vector. (Why not just a rotation?) ACAD maintains it as a unit vector.
    _writer->write3BitDouble(mtext->alignmentPoint());
    //Rect width BD 41 Reference rectangle width (width picked by the user).
    _writer->writeBitDouble(mtext->rectangleWidth());

    //R2007+:
    if (R2007Plus)
    {
        //Rect height BD 46 Reference rectangle height.
        _writer->writeBitDouble(mtext->rectangleHeight());
    }

    //Common:
    //Text height BD 40 Undocumented
    _writer->writeBitDouble(mtext->height());
    //Attachment BS 71 Similar to justification; see DXF doc
    _writer->writeBitShort((short) mtext->attachmentPoint());
    //Drawing dir BS 72 Left to right, etc.; see DXF doc
    _writer->writeBitShort((short) mtext->drawingDirection());

    //Extents ht BD ---Undocumented and not present in DXF or entget
    _writer->writeBitDouble(0);
    //Extents wid BD ---Undocumented and not present in DXF or entget
    _writer->writeBitDouble(0);

    //Text TV 1 All text in one long string
    _writer->writeVariableText(mtext->value());

    //H 7 STYLE (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, mtext->style());

    //R2000+:
    if (R2000Plus)
    {
        //Linespacing Style BS 73
        _writer->writeBitShort((short) mtext->lineSpacingStyle());
        //Linespacing Factor BD 44
        _writer->writeBitDouble(mtext->lineSpacing());
        //Unknown bit B
        _writer->writeBit(false);
    }

    //R2004+:
    if (R2004Plus)
    {
        //Background flags BL 90 0 = no background, 1 = background fill, 2 = background fill with drawing fill color, 0x10 = text frame (R2018+)
        _writer->writeBitLong((int) mtext->backgroundFillFlags());

        //background flags has bit 0x01 set, or in case of R2018 bit 0x10:
        if ((mtext->backgroundFillFlags() & BackgroundFillFlag::UseBackgroundFillColor) !=
                    (int) BackgroundFillFlag::None ||
            _version > ACadVersion::AC1027 && (mtext->backgroundFillFlags() & BackgroundFillFlag::TextFrame) > 0)
        {
            //Background scale factor	BL 45 default = 1.5
            _writer->writeBitDouble(mtext->backgroundScale());
            //Background color CMC 63
            _writer->writeCmColor(mtext->backgroundColor());
            //Background transparency BL 441
            _writer->writeBitLong(mtext->backgroundTransparency().value());
        }
    }

    //R2018+
    if (!R2018Plus)
    {
        return;
    }

    //Is NOT annotative B
    _writer->writeBit(!mtext->isAnnotative());

    //IF MTEXT is not annotative
    if (mtext->isAnnotative())
    {
        return;
    }

    //Version BS Default 0
    _writer->writeBitShort(4);
    //Default flag B Default true
    _writer->writeBit(true);

    //BEGIN REDUNDANT FIELDS(see above for descriptions)
    //Registered application H Hard pointer
    _writer->handleReference(DwgReferenceType::HardPointer, nullptr);

    //Attachment point BL
    _writer->writeBitLong((int) mtext->attachmentPoint());
    //X - axis dir 3BD 10
    _writer->write3BitDouble(mtext->alignmentPoint());
    //Insertion point 3BD 11
    _writer->write3BitDouble(mtext->insertPoint());
    //Rect width BD 40
    _writer->writeBitDouble(mtext->rectangleWidth());
    //Rect height BD 41 -> wrong code, should be 46, undocumented
    _writer->writeBitDouble(mtext->rectangleHeight());
    //Extents width BD 42
    _writer->writeBitDouble(mtext->horizontalWidth());
    //Extents height BD 43
    _writer->writeBitDouble(mtext->verticalHeight());
    //END REDUNDANT FIELDS

    //Column type BS 71 0 = No columns, 1 = static columns, 2 = dynamic columns
    _writer->writeBitShort((short) mtext->column().columnType);

    //IF Has Columns data(column type is not 0)
    if (mtext->column().columnType != ColumnType::NoColumns)
    {
        //Column height count BL 72
        _writer->writeBitLong(mtext->column().columnCount);
        //Columnn width BD 44
        _writer->writeBitDouble(mtext->column().columnWidth);
        //Gutter BD 45
        _writer->writeBitDouble(mtext->column().columnGutter);
        //Auto height? B 73
        _writer->writeBit(mtext->column().columnAutoHeight);
        //Flow reversed? B 74
        _writer->writeBit(mtext->column().columnFlowReversed);

        //IF not auto height and column type is dynamic columns
        if (!mtext->column().columnAutoHeight && mtext->column().columnType == ColumnType::DynamicColumns)
        {
            for (double h: mtext->column().columnHeights)
            {
                //Column height BD 46
                _writer->writeBitDouble(h);
            }
        }
    }
}

void DwgObjectWriter::writeFaceRecord(VertexFaceRecord *face)
{
    //Vert index BS 71 1 - based vertex index(see DXF doc)
    _writer->writeBitShort(face->index1());
    //Vert index BS 72 1 - based vertex index(see DXF doc)
    _writer->writeBitShort(face->index2());
    //Vert index BS 73 1 - based vertex index(see DXF doc)
    _writer->writeBitShort(face->index3());
    //Vert index BS 74 1 - based vertex index(see DXF doc)
    _writer->writeBitShort(face->index4());
}

void DwgObjectWriter::writeVertex2D(Vertex2D *vertex)
{
    //Flags EC 70 NOT bit-pair-coded.
    _writer->writeByte((unsigned char) (vertex->flags()));

    //Point 3BD 10 NOTE THAT THE Z SEEMS TO ALWAYS BE 0.0! The Z must be taken from the 2D POLYLINE elevation.
    _writer->writeBitDouble(vertex->location().X);
    _writer->writeBitDouble(vertex->location().Y);
    _writer->writeBitDouble(0.0);

    //Start width BD 40 If it's negative, use the abs val for start AND end widths (and note that no end width will be present).
    //This is a compression trick for cases where the start and end widths are identical and non-0.
    if (vertex->startWidth() != 0.0 && vertex->endWidth() == vertex->startWidth())
    {
        _writer->writeBitDouble(0.0 - (double) vertex->startWidth());
    }
    else
    {
        _writer->writeBitDouble(vertex->startWidth());
        //End width BD 41 Not present if the start width is < 0.0; see above.
        _writer->writeBitDouble(vertex->endWidth());
    }

    //Bulge BD 42
    _writer->writeBitDouble(vertex->bulge());

    //R2010+:
    if (R2010Plus)
    {
        //Vertex ID BL 91
        _writer->writeBitLong(vertex->id());
    }

    //Common:
    //Tangent dir BD 50
    _writer->writeBitDouble(vertex->curveTangent());
}

void DwgObjectWriter::writeVertex(Vertex *vertex)
{
    //Flags EC 70 NOT bit-pair-coded.
    _writer->writeByte((unsigned char) vertex->flags());
    //Point 3BD 10
    _writer->write3BitDouble(vertex->location());
}

void DwgObjectWriter::writeTolerance(Tolerance *tolerance)
{
    //R13 - R14 Only:
    if (R13_14Only)
    {
        //Unknown short S
        _writer->writeBitShort(0);
        //Height BD --
        _writer->writeBitDouble(0.0);
        //Dimgap(?) BD dimgap at time of creation, *dimscale
        _writer->writeBitDouble(0.0);
    }

    //Common:
    //Ins pt 3BD 10
    _writer->write3BitDouble(tolerance->insertionPoint());
    //X direction 3BD 11
    _writer->write3BitDouble(tolerance->direction());
    //Extrusion 3BD 210 etc.
    _writer->write3BitDouble(tolerance->normal());
    //Text string BS 1
    _writer->writeVariableText(tolerance->text());

    //Common Entity Handle Data
    //H DIMSTYLE(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, tolerance->style());
}

void DwgObjectWriter::writeViewport(Viewport *viewport)
{
    //Center 3BD 10
    _writer->write3BitDouble(viewport->center());
    //Width BD 40
    _writer->writeBitDouble(viewport->width());
    //Height BD 41
    _writer->writeBitDouble(viewport->height());

    //R2000 +:
    if (R2000Plus)
    {
        //View Target 3BD 17
        _writer->write3BitDouble(viewport->viewTarget());
        //View Direction 3BD 16
        _writer->write3BitDouble(viewport->viewDirection());
        //View Twist Angle BD 51
        _writer->writeBitDouble(viewport->twistAngle());
        //View Height BD 45
        _writer->writeBitDouble(viewport->viewHeight());
        //Lens Length BD 42
        _writer->writeBitDouble(viewport->lensLength());
        //Front Clip Z BD 43
        _writer->writeBitDouble(viewport->frontClipPlane());
        //Back Clip Z BD 44
        _writer->writeBitDouble(viewport->backClipPlane());
        //Snap Angle BD 50
        _writer->writeBitDouble(viewport->snapAngle());
        //View Center 2RD 12
        _writer->write2RawDouble(viewport->viewCenter());
        //Snap Base 2RD 13
        _writer->write2RawDouble(viewport->snapBase());
        //Snap Spacing 2RD 14
        _writer->write2RawDouble(viewport->snapSpacing());
        //Grid Spacing 2RD 15
        _writer->write2RawDouble(viewport->gridSpacing());
        //Circle Zoom BS 72
        _writer->writeBitShort(viewport->circleZoomPercent());
    }

    //R2007 +:
    if (R2007Plus)
    {
        //Grid Major BS 61
        _writer->writeBitShort(viewport->majorGridLineFrequency());
    }

    //R2000 +:
    if (R2000Plus)
    {
        //Frozen Layer Count BL
        _writer->writeBitLong(viewport->frozenLayers().size());
        //Status Flags BL 90
        _writer->writeBitLong((int) viewport->status());
        //Style Sheet TV 1
        _writer->writeVariableText(std::string());//This is never used
                                                  //Render Mode RC 281
        _writer->writeByte((unsigned char) viewport->renderMode());
        //UCS at origin B 74
        _writer->writeBit(viewport->displayUcsIcon());
        //UCS per Viewport B 71
        _writer->writeBit(viewport->ucsPerViewport());
        //UCS Origin 3BD 110
        _writer->write3BitDouble(viewport->ucsOrigin());
        //UCS X Axis 3BD 111
        _writer->write3BitDouble(viewport->ucsXAxis());
        //UCS Y Axis 3BD 112
        _writer->write3BitDouble(viewport->ucsYAxis());
        //UCS Elevation BD 146
        _writer->writeBitDouble(viewport->elevation());
        //UCS Ortho View Type BS 79
        _writer->writeBitShort((short) viewport->ucsOrthographicType());
    }

    //R2004 +:
    if (R2004Plus)
    {
        //ShadePlot Mode BS 170
        _writer->writeBitShort((short) viewport->shadePlotMode());
    }

    //R2007 +:
    if (R2007Plus)
    {
        //Use def. lights B 292
        _writer->writeBit(viewport->useDefaultLighting());
        //Def.lighting type RC 282
        _writer->writeByte((unsigned char) viewport->defaultLightingType());
        //Brightness BD 141
        _writer->writeBitDouble(viewport->brightness());
        //Contrast BD 142
        _writer->writeBitDouble(viewport->contrast());
        //Ambient light color CMC 63
        _writer->writeCmColor(viewport->ambientLightColor());
    }

    //R13 - R14 Only:
    if (R13_14Only)
    {
        _writer->handleReference(DwgReferenceType::HardPointer, nullptr);
    }

    //R2000 +:
    if (R2000Plus)
    {
        for (auto &&layer: viewport->frozenLayers())
        {
            if (R2004Plus)
            {
                //H 341 Frozen Layer Handles(use count from above)
                //(hard pointer until R2000, soft pointer from R2004 onwards)
                _writer->handleReference(DwgReferenceType::SoftPointer, layer);
            }
            else
            {
                _writer->handleReference(DwgReferenceType::HardPointer, layer);
            }
        }

        //H 340 Clip boundary handle(soft pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, viewport->boundary());
    }

    //R2000:
    if (_version == ACadVersion::AC1015)
    {
        //H VIEWPORT ENT HEADER((hard pointer))
        _writer->handleReference(DwgReferenceType::HardPointer, nullptr);
    }

    //R2000 +:
    if (R2000Plus)
    {
        //TODO: Implement viewport UCS
        _writer->handleReference(DwgReferenceType::HardPointer, nullptr);
        _writer->handleReference(DwgReferenceType::HardPointer, nullptr);
    }

    //R2007 +:
    if (R2007Plus)
    {
        //H 332 Background(soft pointer)
        _writer->handleReference(DwgReferenceType::SoftPointer, nullptr);
        //H 348 Visual Style(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, nullptr);
        //H 333 Shadeplot ID(soft pointer)
        _writer->handleReference(DwgReferenceType::SoftPointer, nullptr);
        //H 361 Sun(hard owner)
        _writer->handleReference(DwgReferenceType::HardOwnership, nullptr);
    }
}

void DwgObjectWriter::writeXLine(XLine *xline)
{
    //3 RD: a point on the construction line
    _writer->write3BitDouble(xline->firstPoint());
    //3 RD : another point
    _writer->write3BitDouble(xline->direction());
}

void DwgObjectWriter::writeChildEntities(const std::vector<Entity *> &entities, Seqend *seqend)
{
    if (entities.empty())
        return;

    Entity *prevHolder = _prev;
    Entity *nextHolder = _next;
    _prev = nullptr;
    _next = nullptr;

    Entity *curr = entities.front();
    for (int i = 1; i < entities.size(); i++)
    {
        _next = entities.at(i);
        writeEntity(curr);
        _prev = curr;
        curr = _next;
    }

    _next = nullptr;
    writeEntity(curr);

    _prev = prevHolder;
    _next = nextHolder;

    if (seqend != nullptr)
    {
        writeSeqend(seqend);
    }
}

}// namespace dwg
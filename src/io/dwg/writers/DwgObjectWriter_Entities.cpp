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
#include <dwg/entities/Arc.h>
#include <dwg/entities/Circle.h>
#include <dwg/io/dwg/writers/IDwgStreamWriter_p.h>
#include <dwg/entities/AttributeEntity.h>
#include <dwg/entities/AttributeDefinition.h>
#include <dwg/entities/AttributeBase.h>
#include <dwg/entities/MText.h>
#include <dwg/entities/Dimension.h>
#include <dwg/tables/DimensionStyle.h>
#include <dwg/entities/DimensionLinear.h>
#include <dwg/entities/DimensionAligned.h>
#include <dwg/entities/DimensionRadius.h>
#include <dwg/entities/DimensionAngular2Line.h>
#include <dwg/entities/DimensionAngular3Pt.h>
#include <dwg/entities/DimensionDiameter.h>
#include <dwg/entities/DimensionOrdinate.h>
#include <dwg/entities/Ellipse.h>
#include <dwg/entities/Insert.h>
#include <dwg/entities/Viewport.h>
#include <dwg/entities/XLine.h>
#include <dwg/entities/Ray.h>
#include <dwg/entities/Line.h>
#include <dwg/entities/Point.h>
#include <dwg/tables/Layer.h>
#include <dwg/tables/BlockRecord.h>

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
	flags |= dimension->isTextUserDefinedLocation() ? (unsigned char)0b00 : (unsigned char)0b01;
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
		_writer->writeBitShort((short)dimension->attachmentPoint());
		//Linespacing Style BS 72
		_writer->writeBitShort((short)dimension->lineSpacingStyle());
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
	_writer->handleReference(DwgReferenceType::HardPointer, dimension->dimStyle());
	//H 2 anonymous BLOCK(hard pointer)
	//TODO: fix annotative dimensions
	//_writer->handleReference(DwgReferenceType::HardPointer, dimension->Block);
	_writer->handleReference(DwgReferenceType::HardPointer, nullptr);
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

	unsigned char flag = (unsigned char)(dimension->isOrdinateTypeX() ? 1 : 0);
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
					//10 – 41 value stored as a RD, and 42 & 43 values are not stored, assumed equal to 41 value.
					_writer->write2Bits(2);
					_writer->writeRawDouble(insert->XScale());
				}
				else if (insert->XScale() == 1.0)
				{
					//01 – 41 value is 1.0, 2 DD’s are present, each using 1.0 as the default value, representing the 42 and 43 values.
					_writer->write2Bits(1);
					_writer->writeBitDoubleWithDefault(insert->YScale(), 1.0);
					_writer->writeBitDoubleWithDefault(insert->ZScale(), 1.0);
				}
				else
				{
					//00 – 41 value stored as a RD, followed by a 42 value stored as DD (use 41 for default value), and a 43 value stored as a DD(use 41 value for default value).
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
				_writer->writeBitLong(insert->attributes().size());
			}

			if (insert->isMultiple())
			{
				//Common:
				//Numcols BS 70
				_writer->writeBitShort((short)insert->columnCount());
				//Numrows BS 71
				_writer->writeBitShort((short)insert->rowCount());
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
				_writer->handleReference(DwgReferenceType::SoftPointer, insert->attributes().front());
				_writer->handleReference(DwgReferenceType::SoftPointer, insert->attributes().back());
			}
			//R2004+:
			else if (R2004Plus)
			{
				for (auto &&att : insert->attributes())
				{
					//H[ATTRIB(hard owner)] Repeats “Owned Object Count” times.
					_writer->handleReference(DwgReferenceType::HardOwnership, att);
				}
			}

			//Common:
			//H[SEQEND(hard owner)] if 66 bit set
			_writer->handleReference(DwgReferenceType::HardOwnership, insert->attributes().seqend());
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
				_writer->writeBitShort((short)face->flags());
			}

			//R2000 +:
			if (R2000Plus)
			{
				bool noFlags = face->flags() == InvisibleEdgeFlags::None;
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
					//1st corner z RD 30 Present only if “Z is zero bit” is 0.
					_writer->writeRawDouble(face->firstCorner().Z);
				}

				//2nd corner 3DD 11 Use 10 value as default point
				_writer->write3BitDoubleWithDefault(face->secondCorner(), face->FirstCorner());
				//3rd corner 3DD 12 Use 11 value as default point
				_writer->write3BitDoubleWithDefault(face->thirdCorner(), face->secondCorner());
				//4th corner 3DD 13 Use 12 value as default point
				_writer->write3BitDoubleWithDefault(face->fourthCorner(), face->thirdCorner());

				//Invis flags BS 70 Present it “Has no flag ind.” is 0.
				if (!noFlags)
				{
					_writer->writeBitShort((short)face->flags());
				}
			}
}

void DwgObjectWriter::writeMLine(MLine *mline) 
{
			//Scale BD 40
			_writer->writeBitDouble(mline->scaleFactor());
			//Just EC top (0), bottom(2), or center(1)
			_writer->writeByte((unsigned char)mline->justification());
			//Base point 3BD 10
			_writer->write3BitDouble(mline->startPoint());
			//Extrusion 3BD 210 etc.
			_writer->write3BitDouble(mline->normal());

			//Openclosed BS open (1), closed(3)
			_writer->writeBitShort((short)(mline->Flags() & (MLineFlag::Closed) ? 3 : 1));

			int nlines = 0;
			if (mline->vertices().size() > 0)
			{
				nlines = mline->vertices().front().segments().size();
			}
			//Linesinstyle RC 73
			_writer->writeByte((unsigned char)nlines);

			//Numverts BS 72
			_writer->writeBitShort((short)mline->vertices().size());

			for (auto v : mline->vertices())
			{
				//vertex 3BD
				_writer->write3BitDouble(v.position());
				//vertex direction 3BD
				_writer->write3BitDouble(v.direction());
				//miter direction 3BD
				_writer->write3BitDouble(v.miter());

				// All the Vertices must have the same number of segments
				for (int i = 0; i < nlines; i++)
				{
					auto&& element = v->segments[i];

					//numsegparms BS
					_writer->writeBitShort((short)element.Parameters.Count);
					for (double p in element.Parameters)
					{
						//segparm BD segment parameter
						_writer->writeBitDouble(p);
					}

					//numareafillparms BS
					_writer->writeBitShort((short)element.AreaFillParameters.Count);
					for (double afp : element.AreaFillParameters)
					{
						//areafillparm BD area fill parameter
						_writer->writeBitDouble(afp);
					}
				}
			}

			//H mline style oject handle (hard pointer)
			_writer->handleReference(DwgReferenceType::HardPointer, mline->Style);
}

void DwgObjectWriter::writeLwPolyline(LwPolyline *lwPolyline) 
{
			bool nbulges = false;
			bool ndiffwidth = false;
			for (LwPolyline.Vertex item in lwPolyline.Vertices)
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

			if (lwPolyline.Flags.HasFlag(LwPolylineFlags.Plinegen))
			{
				flags = (short)(flags | 0x100);
			}

			if (lwPolyline.Flags.HasFlag(LwPolylineFlags.Closed))
			{
				flags = (short)(flags | 0x200);
			}

			if (lwPolyline.ConstantWidth != 0.0)
			{
				flags = (short)(flags | 0x4);
			}

			if (lwPolyline.Elevation != 0.0)
			{
				flags = (short)(flags | 0x8);
			}

			if (lwPolyline.Thickness != 0.0)
			{
				flags = (short)(flags | 2);
			}

			if (lwPolyline.Normal != XYZ.AxisZ)
			{
				flags = (short)(flags | 1);
			}

			if (nbulges)
			{
				flags = (short)(flags | 0x10);
			}
			//Skip ids, not necessary
			if (ndiffwidth)
			{
				flags = (short)(flags | 0x20);
			}

			//B : bytes containing the LWPOLYLINE entity data.
			//This excludes the common entity data.
			//More specifically: it starts at the LWPOLYLINE flags (BS), and ends with the width array (BD).
			_writer->writeBitShort(flags);

			if (lwPolyline.ConstantWidth != 0.0)
			{
				_writer->writeBitDouble(lwPolyline.ConstantWidth);
			}
			if (lwPolyline.Elevation != 0.0)
			{
				_writer->writeBitDouble(lwPolyline.Elevation);
			}
			if (lwPolyline.Thickness != 0.0)
			{
				_writer->writeBitDouble(lwPolyline.Thickness);
			}
			if (lwPolyline.Normal != XYZ.AxisZ)
			{
				_writer->write3BitDouble(lwPolyline.Normal);
			}

			_writer->writeBitLong(lwPolyline.Vertices.Count);

			if (nbulges)
			{
				_writer->writeBitLong(lwPolyline.Vertices.Count);
			}

			if (ndiffwidth)
			{
				_writer->writeBitLong(lwPolyline.Vertices.Count);
			}

			if (R13_14Only)
			{
				for (int i = 0; i < lwPolyline.Vertices.Count; i++)
				{
					_writer->write2RawDouble(lwPolyline.Vertices[i].Location);
				}
			}

			if (R2000Plus && lwPolyline.Vertices.Count > 0)
			{
				LwPolyline.Vertex last = lwPolyline.Vertices[0];
				_writer->write2RawDouble(last.Location);
				for (int j = 1; j < lwPolyline.Vertices.Count; j++)
				{
					LwPolyline.Vertex curr = lwPolyline.Vertices[j];
					_writer->write2BitDoubleWithDefault(curr.Location, last.Location);
					last = curr;
				}
			}

			if (nbulges)
			{
				for (int k = 0; k < lwPolyline.Vertices.Count; k++)
				{
					_writer->writeBitDouble(lwPolyline.Vertices[k].Bulge);
				}
			}

			if (ndiffwidth)
			{
				for (int l = 0; l < lwPolyline.Vertices.Count; l++)
				{
					_writer->writeBitDouble(lwPolyline.Vertices[l].StartWidth);
					_writer->writeBitDouble(lwPolyline.Vertices[l].EndWidth);
				}
			}
}

void DwgObjectWriter::writeHatch(Hatch *hatch) 
{
			//R2004+:
			if (R2004Plus)
			{
				HatchGradientPattern gradient = hatch.GradientColor; //TODO: set default ?? HatchGradientPattern.Default;

				//Is Gradient Fill BL 450 Non-zero indicates a gradient fill is used.
				_writer->writeBitLong(gradient.Enabled ? 1 : 0);

				//Reserved BL 451
				_writer->writeBitLong(gradient.Reserved);
				//Gradient Angle BD 460
				_writer->writeBitDouble(gradient.Angle);
				//Gradient Shift BD 461
				_writer->writeBitDouble(gradient.Shift);
				//Single Color Grad.BL 452
				_writer->writeBitLong(gradient.IsSingleColorGradient ? 1 : 0);
				//Gradient Tint BD 462
				_writer->writeBitDouble(gradient.ColorTint);

				//# of Gradient Colors BL 453
				_writer->writeBitLong(gradient.Colors.Count);
				for (GradientColor color in gradient.Colors)
				{
					//Gradient Value double BD 463
					_writer->writeBitDouble(color.Value);
					//RGB Color
					_writer->writeCmColor(color.Color);
				}

				//Gradient Name TV 470
				_writer->writeVariableText(gradient.Name);
			}

			//Common:
			//Z coord BD 30 X, Y always 0.0
			_writer->writeBitDouble(hatch.Elevation);
			//Extrusion 3BD 210
			_writer->write3BitDouble(hatch.Normal);
			//Name TV 2 name of hatch
			_writer->writeVariableText(hatch.Pattern.Name);
			//Solidfill B 70 1 if solidfill, else 0
			_writer->writeBit(hatch.IsSolid);
			//Associative B 71 1 if associative, else 0
			_writer->writeBit(hatch.IsAssociative);

			//Numpaths BL 91 Number of paths enclosing the hatch
			_writer->writeBitLong(hatch.Paths.Count);
			bool hasDerivedBoundary = false;
			for (Hatch.BoundaryPath boundaryPath in hatch.Paths)
			{
				//Pathflag BL 92 Path flag
				_writer->writeBitLong((int)boundaryPath.Flags);

				if (boundaryPath.Flags.HasFlag(BoundaryPathFlags.Derived))
				{
					hasDerivedBoundary = true;
				}

				if (boundaryPath.Flags.HasFlag(BoundaryPathFlags.Polyline))
				{
					Hatch.BoundaryPath.Polyline pline = boundaryPath.Edges.First() as Hatch.BoundaryPath.Polyline;

					//bulgespresent B 72 bulges are present if 1
					_writer->writeBit(pline.HasBulge);
					//closed B 73 1 if closed
					_writer->writeBit(pline.IsClosed);

					//numpathsegs BL 91 number of path segments
					_writer->writeBitLong(pline.Vertices.Count);
					for (auto && i = 0; i < pline.Vertices.Count; ++i)
					{
						auto && vertex = pline.Vertices[i];

						_writer->write2RawDouble(new XY(vertex.X, vertex.Y));
						if (pline.HasBulge)
						{
							_writer->writeBitDouble(vertex.Z);
						}
					}
				}
				else
				{
					//Numpathsegs BL 93 number of segments in this path
					_writer->writeBitLong(boundaryPath.Edges.Count);
					for (auto && edge in boundaryPath.Edges)
					{
						//pathtypestatus RC 72 type of path
						_writer->writeByte((unsigned char)edge.Type);

						switch (edge)
						{
							case Hatch.BoundaryPath.Line line:
								//pt0 2RD 10 first endpoint
								_writer->write2RawDouble(line.Start);
								//pt1 2RD 11 second endpoint
								_writer->write2RawDouble(line.End);
								break;
							case Hatch.BoundaryPath.Arc arc:
								//pt0 2RD 10 center
								_writer->write2RawDouble(arc.Center);
								//radius BD 40 radius
								_writer->writeBitDouble(arc.Radius);
								//startangle BD 50 start angle
								_writer->writeBitDouble(arc.StartAngle);
								//endangle BD 51 endangle
								_writer->writeBitDouble(arc.EndAngle);
								//isccw B 73 1 if counter clockwise, otherwise 0
								_writer->writeBit(arc.CounterClockWise);
								break;
							case Hatch.BoundaryPath.Ellipse ellispe:
								//pt0 2RD 10 center
								_writer->write2RawDouble(ellispe.Center);
								//endpoint 2RD 11 endpoint of major axis
								_writer->write2RawDouble(ellispe.MajorAxisEndPoint);
								//minormajoratio BD 40 ratio of minor to major axis
								_writer->writeBitDouble(ellispe.MinorToMajorRatio);
								//startangle BD 50 start angle
								_writer->writeBitDouble(ellispe.StartAngle);
								//endangle BD 51 endangle
								_writer->writeBitDouble(ellispe.EndAngle);
								//isccw B 73 1 if counter clockwise; otherwise 0
								_writer->writeBit(ellispe.IsCounterclockwise);
								break;
							case Hatch.BoundaryPath.Spline splineEdge:
								//degree BL 94 degree of the spline
								_writer->writeBitLong(splineEdge.Degree);
								//isrational B 73 1 if rational(has weights), else 0
								_writer->writeBit(splineEdge.Rational);
								//isperiodic B 74 1 if periodic, else 0
								_writer->writeBit(splineEdge.Periodic);

								//numknots BL 95 number of knots
								_writer->writeBitLong(splineEdge.Knots.Count);
								//numctlpts BL 96 number of control points
								_writer->writeBitLong(splineEdge.ControlPoints.Count);
								for (double k in splineEdge.Knots)
								{
									//knot BD 40 knot value
									_writer->writeBitDouble(k);
								}

								for (int p = 0; p < splineEdge.ControlPoints.Count; ++p)
								{
									//pt0 2RD 10 control point
									_writer->write2RawDouble((XY)splineEdge.ControlPoints[p]);

									if (splineEdge.Rational)
										//weight BD 40 weight
										_writer->writeBitDouble(splineEdge.ControlPoints[p].Z);
								}

								//R24:
								if (R2010Plus)
								{
									//Numfitpoints BL 97 number of fit points
									_writer->writeBitLong(splineEdge.FitPoints.Count);
									if (splineEdge.FitPoints.Any())
									{
										for (XY fp in splineEdge.FitPoints)
										{
											//Fitpoint 2RD 11
											_writer->write2RawDouble(fp);
										}

										//Start tangent 2RD 12
										_writer->write2RawDouble(splineEdge.StartTangent);
										//End tangent 2RD 13
										_writer->write2RawDouble(splineEdge.EndTangent);
									}
								}
								break;
							default:
								throw new ArgumentException($"Unrecognized Boundary type: {boundaryPath.GetType().FullName}");
						}
					}
				}

				//numboundaryobjhandles BL 97 Number of boundary object handles for this path
				_writer->writeBitLong(boundaryPath.Entities.Count);
				for (Entity e in boundaryPath.Entities)
				{
					//boundaryhandle H 330 boundary handle(soft pointer)
					_writer->handleReference(DwgReferenceType::SoftPointer, e);
				}
			}

			//style BS 75 style of hatch 0==odd parity, 1==outermost, 2==whole area
			_writer->writeBitShort((short)hatch.Style);
			//patterntype BS 76 pattern type 0==user-defined, 1==predefined, 2==custom
			_writer->writeBitShort((short)hatch.PatternType);

			if (!hatch.IsSolid)
			{
				HatchPattern pattern = hatch.Pattern;
				_writer->writeBitDouble(hatch.PatternAngle);
				_writer->writeBitDouble(hatch.PatternScale);
				_writer->writeBit(hatch.IsDouble);

				_writer.WriteBitShort((short)pattern.Lines.Count);
				for (auto && line in pattern.Lines)
				{
					//angle BD 53 line angle
					_writer.WriteBitDouble(line.Angle);
					//pt0 2BD 43 / 44 pattern through this point(X, Y)
					_writer.Write2BitDouble(line.BasePoint);
					//offset 2BD 45 / 56 pattern line offset
					_writer.Write2BitDouble(line.Offset);

					//  numdashes BS 79 number of dash length items
					_writer.WriteBitShort((short)line.DashLengths.Count);
					for (double dl in line.DashLengths)
					{
						//dashlength BD 49 dash length
						_writer.WriteBitDouble(dl);
					}
				}
			}

			if (hasDerivedBoundary)
			{
				//pixelsize BD 47 pixel size
				_writer->writeBitDouble(hatch.PixelSize);
			}

			//numseedpoints BL 98 number of seed points
			_writer->writeBitLong(hatch.SeedPoints.Count);
			for (XY sp in hatch.SeedPoints)
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
			_writer->writeBitShort((short)leader.CreationType);
			//path type BS ---
			_writer->writeBitShort((short)leader.PathType);

			//numpts BL --- number of points
			_writer->writeBitLong(leader.Vertices.Count);
			for (XYZ v in leader.Vertices)
			{
				//point 3BD 10 As many as counter above specifies.
				_writer->write3BitDouble(v);
			}

			//Origin 3BD --- The leader plane origin (by default it’s the first point).
			_writer->write3BitDouble(leader.Vertices.FirstOrDefault());
			//Extrusion 3BD 210
			_writer->write3BitDouble(leader.Normal);
			//x direction 3BD 211
			_writer->write3BitDouble(leader.HorizontalDirection);
			//offsettoblockinspt 3BD 212 Used when the BLOCK option is used. Seems to be an unused feature.
			_writer->write3BitDouble(leader.BlockOffset);

			//R14+:
			if (_version >= ACadVersion::AC1014)
			{
				//Endptproj 3BD --- A non-planar leader gives a point that projects the endpoint back to the annotation.
				_writer->write3BitDouble(leader.AnnotationOffset);
			}

			//R13-R14 Only:
			if (R13_14Only)
			{
				//DIMGAP BD --- The value of DIMGAP in the associated DIMSTYLE at the time of creation, multiplied by the dimscale in that dimstyle.
				_writer->writeBitDouble(leader.Style.DimensionLineGap);
			}


			//Common:
			if (_version <= ACadVersion::AC1021)
			{
				//Box height BD 40 MTEXT extents height. (A text box is slightly taller, probably by some DIMvar amount.)
				_writer->writeBitDouble(leader.TextHeight);
				//Box width BD 41 MTEXT extents width. (A text box is slightly wider, probably by some DIMvar amount.)
				_writer->writeBitDouble(leader.TextWidth);
			}

			//Hooklineonxdir B hook line is on x direction if 1
			_writer->writeBit(leader.HookLineDirection == HookLineDirection.Same);
			//Arrowheadon B arrowhead on indicator
			_writer->writeBit(leader.ArrowHeadEnabled);

			//R13-R14 Only:
			if (R13_14Only)
			{
				//Arrowheadtype BS arrowhead type
				_writer->writeBitShort(0);
				//Dimasz BD DIMASZ at the time of creation, multiplied by DIMSCALE
				_writer->writeBitDouble(leader.Style.ArrowSize * leader.Style.ScaleFactor);
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
			_writer->handleReference(DwgReferenceType::HardPointer, leader.Style);
}

void DwgObjectWriter::writeMultiLeader(MultiLeader *multiLeader) 
{
			if (R2010Plus)
			{
				//	270 Version, expected to be 2
				_writer->writeBitShort(2);
			}

			writeMultiLeaderAnnotContext(multiLeader.ContextData);

			//	Multileader Common data
			//	340 Leader StyleId (handle)
			_writer->handleReference(DwgReferenceType::HardPointer, multiLeader.Style);
			//	90  Property Override Flags (int32)
			_writer->writeBitLong((int)multiLeader.PropertyOverrideFlags);
			//	170 LeaderLineType (short)
			_writer->writeBitShort((short)multiLeader.PathType);
			//	91  Leader LineColor (Color)
			_writer->writeCmColor(multiLeader.LineColor);
			//	341 LeaderLineTypeID (handle/LineType)
			_writer->handleReference(DwgReferenceType::HardPointer, multiLeader.LeaderLineType);
			//	171 LeaderLine Weight
			_writer->writeBitLong((short)multiLeader.LeaderLineWeight);

			//  290 Enable Landing
			_writer->writeBit(multiLeader.EnableLanding);
			//  291 Enable Dogleg
			_writer->writeBit(multiLeader.EnableDogleg);

			//  41  Dogleg Length / Landing distance
			_writer->writeBitDouble(multiLeader.LandingDistance);
			//  342 Arrowhead ID
			_writer->handleReference(DwgReferenceType::HardPointer, multiLeader.Arrowhead);
			//template.ArrowheadHandle = handleReference();
			//  42  Arrowhead Size
			_writer->writeBitDouble(multiLeader.ArrowheadSize);
			//  172 Content Type
			_writer->writeBitShort((short)multiLeader.ContentType);
			//  343 Text Style ID (handle/TextStyle)
			_writer->handleReference(DwgReferenceType::HardPointer, multiLeader.TextStyle); //	Hard/soft??
																							   //  173 Text Left Attachment Type
			_writer->writeBitShort((short)multiLeader.TextLeftAttachment);
			//  95  Text Right Attachement Type
			_writer->writeBitShort((short)multiLeader.TextRightAttachment);
			//  174 Text Angle Type
			_writer->writeBitShort((short)multiLeader.TextAngle);
			//  175 Text Alignment Type
			_writer->writeBitShort((short)multiLeader.TextAlignment);
			//  92  Text Color
			_writer->writeCmColor(multiLeader.TextColor);
			//  292 Enable Frame Text
			_writer->writeBit(multiLeader.TextFrame);
			//  344 Block Content ID
			_writer->handleReference(DwgReferenceType::HardPointer, multiLeader.BlockContent); //	Hard/soft??
																								  //  93  Block Content Color
			_writer->writeCmColor(multiLeader.BlockContentColor);
			//  10  Block Content Scale
			_writer->write3BitDouble(multiLeader.BlockContentScale);
			//  43  Block Content Rotation
			_writer->writeBitDouble(multiLeader.BlockContentRotation);
			//  176 Block Content Connection Type
			_writer->writeBitShort((short)multiLeader.BlockContentConnection);
			//  293 Enable Annotation Scale/Is annotative
			_writer->writeBit(multiLeader.EnableAnnotationScale);

			//	R2007pre not supported

			//	BL Number of Block Labels 
			int blockLabelCount = multiLeader.BlockAttributes.Count;
			_writer->writeBitLong(blockLabelCount);
			for (int bl = 0; bl < blockLabelCount; bl++)
			{
				//  330 Block Attribute definition handle (hard pointer)
				MultiLeader.BlockAttribute blockAttribute = multiLeader.BlockAttributes[bl];
				_writer->handleReference(DwgReferenceType::HardPointer, blockAttribute.AttributeDefinition);
				//  302 Block Attribute Text String
				_writer->writeVariableText(blockAttribute.Text);
				//  177 Block Attribute Index
				_writer->writeBitShort(blockAttribute.Index);
				//  44  Block Attribute Width
				_writer->writeBitDouble(blockAttribute.Width);
			}

			//  294 Text Direction Negative
			_writer->writeBit(multiLeader.TextDirectionNegative);
			//  178 Text Align in IPE
			_writer->writeBitShort(multiLeader.TextAligninIPE);
			//  179 Text Attachment Point
			_writer->writeBitShort((short)multiLeader.TextAttachmentPoint);
			//	45	BD	ScaleFactor
			_writer->writeBitDouble(multiLeader.ScaleFactor);

			if (R2010Plus)
			{
				//  271 Text attachment direction for MText contents
				_writer->writeBitShort((short)multiLeader.TextAttachmentDirection);
				//  272 Bottom text attachment direction (sequence my be interchanged)
				_writer->writeBitShort((short)multiLeader.TextBottomAttachment);
				//  273 Top text attachment direction
				_writer->writeBitShort((short)multiLeader.TextTopAttachment);
			}

			if (R2013Plus)
			{
				//	295 Leader extended to text
				_writer->writeBit(multiLeader.ExtendedToText);
			}
}

void DwgObjectWriter::writeMultiLeaderAnnotContext(MultiLeaderAnnotContext *annotContext) 
{
	auto writeLeaderLine = [&](MultiLeaderAnnotContext::LeaderLine leaderLine) {
			//	Points
			//	BL	-	Number of points
			//	3BD		10		Point
			_writer->writeBitLong(leaderLine.Points.Count);
			for (XYZ point in leaderLine.Points)
			{
				//	3BD		10		Point
				_writer->write3BitDouble(point);
			}

			//	Add optional Break Info (one or more)
			//	BL	Break info count
			_writer->writeBitLong(leaderLine.BreakInfoCount);
			if (leaderLine.BreakInfoCount > 0)
			{
				//	BL	90		Segment index
				_writer->writeBitLong(leaderLine.SegmentIndex);

				//	Start/end point pairs
				//	3BD	12	End point
				_writer->writeBitLong(leaderLine.StartEndPoints.Count);
				for (MultiLeaderAnnotContext.StartEndPointPair sep in leaderLine.StartEndPoints)
				{
					//	3BD	11	Start Point
					_writer->write3BitDouble(sep.StartPoint);
					_writer->write3BitDouble(sep.EndPoint);
				}
			}

			//	BL	91	Leader line index
			_writer->writeBitLong(leaderLine.Index);

			if (R2010Plus)
			{
				//	BS	170	Leader type(0 = invisible leader, 1 = straight leader, 2 = spline leader)
				_writer->writeBitShort((short)leaderLine.PathType);
				//	CMC	92	Line color
				_writer->writeCmColor(leaderLine.LineColor);
				//	H	340	Line type handle(hard pointer)
				_writer->handleReference(DwgReferenceType::HardPointer, leaderLine.LineType);
				//	BL	171	Line weight
				_writer->writeBitLong((short)leaderLine.LineWeight);
				//	BD	40	Arrow size
				_writer->writeBitDouble(leaderLine.ArrowheadSize);
				//	H	341	Arrow symbol handle(hard pointer)
				_writer->handleReference(DwgReferenceType::HardPointer, leaderLine.Arrowhead);

				//	BL	93	Override flags (1 = leader type, 2 = line color, 4 = line type, 8 = line weight, 16 = arrow size, 32 = arrow symbol(handle)
				_writer->writeBitLong((short)leaderLine.OverrideFlags);
			}
	};

	auto writeLeaderRoot = [&](MultiLeaderAnnotContext::LeaderRoot leaderRoot) {
			//	B		290		Is content valid(ODA writes true)/DXF: Has Set Last Leader Line Point
			_writer->writeBit(leaderRoot.ContentValid);
			//	B		291		Unknown(ODA writes true)/DXF: Has Set Dogleg Vector
			_writer->writeBit(true);
			//	3BD		10		Connection point/DXF: Last Leader Line Point
			_writer->write3BitDouble(leaderRoot.ConnectionPoint);
			//	3BD		11		Direction/DXF: Dogleg vector
			_writer->write3BitDouble(leaderRoot.Direction);

			//	Break start/end point pairs
			//	BL		Number of break start / end point pairs
			//	3BD		12		Break start point
			//	3BD		13		Break end point
			_writer->writeBitLong(leaderRoot.BreakStartEndPointsPairs.Count);
			for (MultiLeaderAnnotContext.StartEndPointPair startEndPointPair in leaderRoot.BreakStartEndPointsPairs)
			{
				_writer->write3BitDouble(startEndPointPair.StartPoint);
				_writer->write3BitDouble(startEndPointPair.EndPoint);
			}

			//	BL		90		Leader index
			_writer->writeBitLong(leaderRoot.LeaderIndex);
			//	BD		40		Landing distance
			_writer->writeBitDouble(leaderRoot.LandingDistance);

			//	Leader lines
			//	BL		Number of leader lines
			_writer->writeBitLong(leaderRoot.Lines.Count);
			for (MultiLeaderAnnotContext.LeaderLine leaderLine in leaderRoot.Lines)
			{
				writeLeaderLine(leaderLine);
			}

			if (R2010Plus)
			{
				//	BS	271	Attachment direction(0 = horizontal, 1 = vertical, default is 0)
				_writer->writeBitShort((short)leaderRoot.TextAttachmentDirection);
			}
	};


			//	BL	-	Number of leader roots
			int leaderRootCount = annotContext.LeaderRoots.Count;
			_writer->writeBitLong(leaderRootCount);
			for (int i = 0; i < leaderRootCount; i++)
			{
				writeLeaderRoot(annotContext.LeaderRoots[i]);
			}

			//	Common
			//	BD	40	Overall scale
			_writer->writeBitDouble(annotContext.ScaleFactor);
			//	3BD	10	Content base point
			_writer->write3BitDouble(annotContext.ContentBasePoint);
			//	BD	41	Text height
			_writer->writeBitDouble(annotContext.TextHeight);
			//	BD	140	Arrow head size
			_writer->writeBitDouble(annotContext.ArrowheadSize);
			//  BD	145	Landing gap
			_writer->writeBitDouble(annotContext.LandingGap);
			//	BS	174	Style left text attachment type. See also MLEADER style left text attachment type for values. Relevant if mleader attachment direction is horizontal.
			_writer->writeBitShort((short)annotContext.TextLeftAttachment);
			//	BS	175	Style right text attachment type. See also MLEADER style left text attachment type for values. Relevant if mleader attachment direction is horizontal.
			_writer->writeBitShort((short)annotContext.TextRightAttachment);
			//	BS	176	Text align type (0 = left, 1 = center, 2 = right)
			_writer->writeBitShort((short)annotContext.TextAlignment);
			//	BS	177	Attachment type (0 = content extents, 1 = insertion point).
			_writer->writeBitShort((short)annotContext.BlockContentConnection);
			//	B	290	Has text contents
			_writer->writeBit(annotContext.HasTextContents);
			if (annotContext.HasTextContents)
			{
				//	TV	304	Text label
				_writer->writeVariableText(annotContext.TextLabel);
				//	3BD	11	Normal vector
				_writer->write3BitDouble(annotContext.TextNormal);
				//	H	340	Text style handle (hard pointer)
				_writer->handleReference(DwgReferenceType::HardPointer, annotContext.TextStyle);
				//	3BD	12	Location
				_writer->write3BitDouble(annotContext.TextLocation);
				//	3BD	13	Direction
				_writer->write3BitDouble(annotContext.Direction);
				//	BD	42	Rotation (radians)
				_writer->writeBitDouble(annotContext.TextRotation);
				//	BD	43	Boundary width
				_writer->writeBitDouble(annotContext.BoundaryWidth);
				//	BD	44	Boundary height
				_writer->writeBitDouble(annotContext.BoundaryHeight);
				//	BD	45	Line spacing factor
				_writer->writeBitDouble(annotContext.LineSpacingFactor);
				//	BS	170	Line spacing style (1 = at least, 2 = exactly)
				_writer->writeBitShort((short)annotContext.LineSpacing);
				//	CMC	90	Text color
				_writer->writeCmColor(annotContext.TextColor);
				//	BS	171	Alignment (1 = left, 2 = center, 3 = right)
				_writer->writeBitShort((short)annotContext.TextAttachmentPoint);
				//	BS	172	Flow direction (1 = horizontal, 3 = vertical, 6 = by style)
				_writer->writeBitShort((short)annotContext.FlowDirection);
				//	CMC	91	Background fill color
				_writer->writeCmColor(annotContext.BackgroundFillColor);
				//	BD	141	Background scale factor
				_writer->writeBitDouble(annotContext.BackgroundScaleFactor);
				//	BL	92	Background transparency
				_writer->writeBitLong(annotContext.BackgroundTransparency);
				//	B	291	Is background fill enabled
				_writer->writeBit(annotContext.BackgroundFillEnabled);
				//	B	292	Is background mask fill on
				_writer->writeBit(annotContext.BackgroundMaskFillOn);
				//	BS	173	Column type (ODA writes 0), *TODO: what meaning for values?
				_writer->writeBitShort(annotContext.ColumnType);
				//	B	293	Is text height automatic?
				_writer->writeBit(annotContext.TextHeightAutomatic);
				//	BD	142	Column width
				_writer->writeBitDouble(annotContext.ColumnWidth);
				//	BD	143	Column gutter
				_writer->writeBitDouble(annotContext.ColumnGutter);
				//	B	294	Column flow reversed
				_writer->writeBit(annotContext.ColumnFlowReversed);

				//	Column sizes
				//  BD	144	Column size
				int columnSizesCount = annotContext.ColumnSizes.Count;
				_writer->writeBitLong(columnSizesCount);
				for (int i = 0; i < columnSizesCount; i++)
				{
					_writer->writeBitDouble(annotContext.ColumnSizes[i]);
				}

				//	B	295	Word break
				_writer->writeBit(annotContext.WordBreak);
				//	B	Unknown
				_writer->writeBit(false);
			}

			else if (annotContext.HasContentsBlock)
			{
				_writer->writeBit(annotContext.HasContentsBlock);

				//B	296	Has contents block
				//IF Has contents block
				//	H	341	AcDbBlockTableRecord handle (soft pointer)
				_writer->handleReference(DwgReferenceType::SoftPointer, annotContext.BlockContent);
				//	3BD	14	Normal vector
				_writer->write3BitDouble(annotContext.BlockContentNormal);
				//	3BD	15	Location
				_writer->write3BitDouble(annotContext.BlockContentLocation);
				//	3BD	16	Scale vector
				_writer->write3BitDouble(annotContext.BlockContentScale);
				//	BD	46	Rotation (radians)
				_writer->writeBitDouble(annotContext.BlockContentRotation);
				//  CMC	93	Block color
				_writer->writeCmColor(annotContext.BlockContentColor);
				//	BD (16)	47	16 doubles containing the complete transformation
				//	matrix. Order of transformation is:
				//	- Rotation,
				//	- OCS to WCS (using normal vector),
				//	- Scaling (using scale vector)
				//	- Translation (using location)
				auto && m4 = annotContext.TransformationMatrix;
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
			_writer->write3BitDouble(annotContext.BasePoint);
			//	3BD	111	Base direction
			_writer->write3BitDouble(annotContext.BaseDirection);
			//	3BD	112	Base vertical
			_writer->write3BitDouble(annotContext.BaseVertical);
			//	B	297	Is normal reversed?
			_writer->writeBit(annotContext.NormalReversed);

			if (R2010Plus)
			{
				//	BS	273	Style top attachment
				_writer->writeBitShort((short)annotContext.TextTopAttachment);
				//	BS	272	Style bottom attachment
				_writer->writeBitShort((short)annotContext.TextBottomAttachment);
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
				//Z’s are zero bit B
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
					//Start Point z RD 30 Present only if “Z’s are zero bit” is 0
					_writer->writeRawDouble(line->startPoint().Z);
					//End Point z DD 31 Present only if “Z’s are zero bit” is 0, use 30 value for default.
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
			_writer->writeBitShort((short)fm.Vertices.Count);
			//Numfaces BS 72 Number of faces
			_writer->writeBitShort((short)fm.Faces.Count);

			//R2004 +:
			if (R2004Plus)
			{
				//Owned Object Count BL Number of objects owned by this object.
				_writer->writeBitLong(fm.Vertices.Count + fm.Faces.Count);
				for (auto && v in fm.Vertices)
				{
					//H[VERTEX(soft pointer)] Repeats “Owned Object Count” times.
					_writer->handleReference(DwgReferenceType::SoftPointer, v);
				}
				for (auto && f in fm.Faces)
				{
					_writer->handleReference(DwgReferenceType::SoftPointer, f);
				}
			}

			//R13 - R2000:
			if (R13_15Only)
			{
				List<CadObject> child = new List<CadObject>(fm.Vertices);
				child.AddRange(fm.Faces);

				CadObject first = child.FirstOrDefault();
				CadObject last = child.LastOrDefault();

				//H first VERTEX(soft pointer)
				_writer->handleReference(DwgReferenceType::SoftPointer, first);
				//H last VERTEX(soft pointer)
				_writer->handleReference(DwgReferenceType::SoftPointer, last);
			}

			//Common:
			//H SEQEND(hard owner)
			_writer->handleReference(DwgReferenceType::SoftPointer, fm.Vertices.Seqend);
}

void DwgObjectWriter::writePolyline2D(Polyline2D *pline) 
{
			//Flags BS 70
			_writer->writeBitShort((short)pline.Flags);
			//Curve type BS 75 Curve and smooth surface type.
			_writer->writeBitShort((short)pline.SmoothSurface);
			//Start width BD 40 Default start width
			_writer->writeBitDouble(pline.StartWidth);
			//End width BD 41 Default end width
			_writer->writeBitDouble(pline.EndWidth);
			//Thickness BT 39
			_writer->writeBitThickness(pline.Thickness);
			//Elevation BD 10 The 10-pt is (0,0,elev)
			_writer->writeBitDouble(pline.Elevation);
			//Extrusion BE 210
			_writer->writeBitExtrusion(pline.Normal);

			int count = pline.Vertices.Count;
			//R2004+:
			if (R2004Plus)
			{
				//Owned Object Count BL Number of objects owned by this object.
				_writer->writeBitLong(count);
				for (int i = 0; i < count; i++)
				{
					_writer->handleReference(DwgReferenceType::HardOwnership, pline.Vertices[i]);
				}
			}

			//R13-R2000:
			if (_version >= ACadVersion::AC1012 && _version <= ACadVersion::AC1015)
			{
				//H first VERTEX (soft pointer)
				_writer->handleReference(DwgReferenceType::SoftPointer, pline.Vertices.FirstOrDefault());
				//H last VERTEX (soft pointer)
				_writer->handleReference(DwgReferenceType::SoftPointer, pline.Vertices.LastOrDefault());
			}

			//Common:
			//H SEQEND(hard owner)
			_writer->handleReference(DwgReferenceType::HardOwnership, pline.Vertices.Seqend);
}

void DwgObjectWriter::writePolyline3D(Polyline3D *pline) 
{
			//Flags RC 70 NOT DIRECTLY THE 75. Bit-coded (76543210):
			//75 0 : Splined(75 value is 5)
			//1 : Splined(75 value is 6)
			//Should assign pline.SmoothSurface ??
			_writer->writeByte(0);

			//Flags RC 70 NOT DIRECTLY THE 70. Bit-coded (76543210):
			//0 : Closed(70 bit 0(1))
			//(Set 70 bit 3(8) because this is a 3D POLYLINE.)
			_writer->writeByte((unsigned char)(pline.Flags.HasFlag(PolylineFlags.ClosedPolylineOrClosedPolygonMeshInM) ? 1 : 0));

			//R2004+:
			if (R2004Plus)
			{
				//Owned Object Count BL Number of objects owned by this object.
				_writer->writeBitLong(pline.Vertices.Count);

				for (auto && vertex in pline.Vertices)
				{
					_writer->handleReference(DwgReferenceType::HardOwnership, vertex);
				}
			}

			//R13-R2000:
			if (_version >= ACadVersion::AC1012 && _version <= ACadVersion::AC1015)
			{
				//H first VERTEX (soft pointer)
				_writer->handleReference(DwgReferenceType::SoftPointer, pline.Vertices.FirstOrDefault());
				//H last VERTEX (soft pointer)
				_writer->handleReference(DwgReferenceType::SoftPointer, pline.Vertices.LastOrDefault());
			}

			//Common:
			//H SEQEND(hard owner)
			_writer->handleReference(DwgReferenceType::HardOwnership, pline.Vertices.Seqend);
}

void DwgObjectWriter::writeSeqend(Seqend *seqend) 
{
			//for empty list seqend is nullptr
			if (seqend == nullptr)
				return;

			//Seqend does not have links for AC1015 or before (causes errors)
			Entity prevHolder = _prev;
			Entity nextHolder = _next;
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
			_writer->write3BitDouble(shape.InsertionPoint);
			//Scale BD 40 Scale factor, default value 1.
			_writer->writeBitDouble(shape.Size);
			//Rotation BD 50 Rotation in radians, default value 0.
			_writer->writeBitDouble(shape.Rotation);
			//Width factor BD 41 Width factor, default value 1.
			_writer->writeBitDouble(shape.RelativeXScale);
			//Oblique BD 51 Oblique angle in radians, default value 0.
			_writer->writeBitDouble(shape.ObliqueAngle);
			//Thickness BD 39
			_writer->writeBitDouble(shape.Thickness);

			//Shapeno BS 2
			//This is the shape index.
			//In DXF the shape name is stored.
			//When reading from DXF, the shape is found by iterating over all the text styles
			//(SHAPEFILE, see paragraph 20.4.56) and when the text style contains a shape file,
			//iterating over all the shapes until the one with the matching name is found.
			_writer->writeBitShort((short)shape.ShapeIndex);

			//Extrusion 3BD 210
			_writer->write3BitDouble(shape.Normal);

			//H SHAPEFILE (hard pointer)
			_writer->handleReference(DwgReferenceType::HardPointer, nullptr);
}

void DwgObjectWriter::writeSolid(Solid *solid) 
{
			//Thickness BT 39
			_writer->writeBitThickness(solid.Thickness);

			//Elevation BD ---Z for 10 - 13.
			_writer->writeBitDouble((double)solid.FirstCorner.Z);

			//1st corner 2RD 10
			_writer->writeRawDouble(solid.FirstCorner.X);
			_writer->writeRawDouble(solid.FirstCorner.Y);
			//2nd corner 2RD 11
			_writer->writeRawDouble(solid.SecondCorner.X);
			_writer->writeRawDouble(solid.SecondCorner.Y);
			//3rd corner 2RD 12
			_writer->writeRawDouble(solid.ThirdCorner.X);
			_writer->writeRawDouble(solid.ThirdCorner.Y);
			//4th corner 2RD 13
			_writer->writeRawDouble(solid.FirstCorner.X);
			_writer->writeRawDouble(solid.FirstCorner.Y);

			//Extrusion BE 210
			_writer->writeBitExtrusion(solid.Normal);
}

void DwgObjectWriter::writeSolid3D(Solid3D *solid) {}

void DwgObjectWriter::writeCadImage(CadWipeoutBase *image) 
{
			_writer->writeBitLong(image.ClassVersion);

			_writer->write3BitDouble(image.InsertPoint);
			_writer->write3BitDouble(image.UVector);
			_writer->write3BitDouble(image.VVector);

			_writer->write2RawDouble(image.Size);

			_writer->writeBitShort((short)image.Flags);
			_writer->writeBit(image.ClippingState);
			_writer->writeByte(image.Brightness);
			_writer->writeByte(image.Contrast);
			_writer->writeByte(image.Fade);

			if (R2010Plus)
			{
				_writer->writeBit(image.ClipMode == ClipMode.Inside);
			}

			_writer->writeBitShort((short)image.ClipType);


			switch (image.ClipType)
			{
				case ClipType.Rectangular:
					_writer->write2RawDouble(image.ClipBoundaryVertices[0]);
					_writer->write2RawDouble(image.ClipBoundaryVertices[1]);
					break;
				case ClipType.Polygonal:
					_writer->writeBitLong(image.ClipBoundaryVertices.Count);
					for (int i = 0; i < image.ClipBoundaryVertices.Count; i++)
					{
						_writer->write2RawDouble(image.ClipBoundaryVertices[i]);
					}
					break;
			}

			_writer->handleReference(DwgReferenceType::HardPointer, image.Definition);
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
				if (spline.KnotParameterization == KnotParameterization.Custom || spline.FitPoints.Count == 0)
				{
					scenario = 1;
				}
				else
				{
					scenario = 2;
				}

				_writer->writeBitLong(scenario);
				_writer->writeBitLong((int)spline.Flags1);
				_writer->writeBitLong((int)spline.KnotParameterization);
			}
			else
			{
				scenario = (spline.FitPoints.Count <= 0) ? 1 : 2;
				if (scenario == 2 && spline.KnotParameterization != 0)
				{
					scenario = 1;
				}

				//Scenario BL a flag which is 2 for fitpts only, 1 for ctrlpts/knots.
				_writer->writeBitLong(scenario);
			}

			//Common:
			//Degree BL degree of this spline
			_writer->writeBitLong(spline.Degree);

			bool flag = spline.Weights.Count > 0;
			switch (scenario)
			{
				case 1:
					{
						//Rational B flag bit 2
						_writer->writeBit(spline.Flags.HasFlag(SplineFlags.Rational));
						//Closed B flag bit 0
						_writer->writeBit(spline.Flags.HasFlag(SplineFlags.Closed));
						//Periodic B flag bit 1
						_writer->writeBit(spline.Flags.HasFlag(SplineFlags.Periodic));

						//Knot tol BD 42
						_writer->writeBitDouble(spline.KnotTolerance);
						//Ctrl tol BD 43
						_writer->writeBitDouble(spline.ControlPointTolerance);

						//Numknots BL 72 This is stored as a LONG
						_writer->writeBitLong(spline.Knots.Count);
						//Numctrlpts BL 73 Number of 10's (and 41's, if weighted) that follow.
						_writer->writeBitLong(spline.ControlPoints.Count);

						//Weight B Seems to be an echo of the 4 bit on the flag for "weights present".
						_writer->writeBit(flag);

						for (double k in spline.Knots)
						{
							//Knot BD knot value
							_writer->writeBitDouble(k);
						}

						for (int i = 0; i < spline.ControlPoints.Count; i++)
						{
							//Control pt 3BD 10
							_writer->write3BitDouble(spline.ControlPoints[i]);
							if (flag)
							{
								//Weight D 41 if present as indicated by 4 bit on flag
								_writer->writeBitDouble(spline.Weights[i]);
							}
						}
						break;
					}
				case 2:
					{
						//Fit Tol BD 44
						_writer->writeBitDouble(spline.FitTolerance);
						//Beg tan vec 3BD 12 Beginning tangent direction vector (normalized).
						_writer->write3BitDouble(spline.StartTangent);
						//End tan vec 3BD 13 Ending tangent direction vector (normalized).
						_writer->write3BitDouble(spline.EndTangent);
						//num fit pts BL 74 Number of fit points.
						_writer->writeBitLong(spline.FitPoints.Count);

						for (XYZ fp in spline.FitPoints)
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
				_writer->writeBitDouble(text.InsertPoint.Z);
				//Insertion pt 2RD 10
				_writer->writeRawDouble(text.InsertPoint.X);
				_writer->writeRawDouble(text.InsertPoint.Y);

				//Alignment pt 2RD 11
				_writer->writeRawDouble(text.AlignmentPoint.X);
				_writer->writeRawDouble(text.AlignmentPoint.Y);

				//Extrusion 3BD 210
				_writer->write3BitDouble(text.Normal);
				//Thickness BD 39
				_writer->writeBitDouble(text.Thickness);
				//Oblique ang BD 51
				_writer->writeBitDouble(text.ObliqueAngle);
				//Rotation ang BD 50
				_writer->writeBitDouble(text.Rotation);
				//Height BD 40
				_writer->writeBitDouble(text.Height);
				//Width factor BD 41
				_writer->writeBitDouble(text.WidthFactor);
				//Text value TV 1
				_writer->writeVariableText(text.Value);
				//Generation BS 71
				_writer->writeBitShort((short)text.Mirror);
				//Horiz align. BS 72
				_writer->writeBitShort((short)text.HorizontalAlignment);
				//Vert align. BS 73
				_writer->writeBitShort((short)text.VerticalAlignment);

			}
			else
			{
				//DataFlags RC Used to determine presence of subsquent data
				unsigned char dataFlags = 0;

				if (text.InsertPoint.Z == 0.0)
				{
					dataFlags = (unsigned char)(dataFlags | 0b1);
				}
				if (text.AlignmentPoint == XYZ.Zero)
				{
					dataFlags = (unsigned char)(dataFlags | 0b10);
				}
				if (text.ObliqueAngle == 0.0)
				{
					dataFlags = (unsigned char)(dataFlags | 0b100);
				}
				if (text.Rotation == 0.0)
				{
					dataFlags = (unsigned char)(dataFlags | 0b1000);
				}
				if (text.WidthFactor == 1.0)
				{
					dataFlags = (unsigned char)(dataFlags | 0b10000);
				}
				if (text.Mirror == TextMirrorFlag.None)
				{
					dataFlags = (unsigned char)(dataFlags | 0b100000);
				}
				if (text.HorizontalAlignment == TextHorizontalAlignment.Left)
				{
					dataFlags = (unsigned char)(dataFlags | 0b1000000);
				}
				if (text.VerticalAlignment == TextVerticalAlignmentType.Baseline)
				{
					dataFlags = (unsigned char)(dataFlags | 0b10000000);
				}

				_writer->writeByte(dataFlags);

				//Elevation RD --- present if !(DataFlags & 0x01)
				if ((dataFlags & 0b1) == 0)
					_writer->writeRawDouble(text.InsertPoint.Z);

				//Insertion pt 2RD 10
				_writer->writeRawDouble(text.InsertPoint.X);
				_writer->writeRawDouble(text.InsertPoint.Y);

				//Alignment pt 2DD 11 present if !(DataFlags & 0x02), use 10 & 20 values for 2 default values.
				if ((dataFlags & 0x2) == 0)
				{
					_writer->writeBitDoubleWithDefault(text.AlignmentPoint.X, text.InsertPoint.X);
					_writer->writeBitDoubleWithDefault(text.AlignmentPoint.Y, text.InsertPoint.Y);
				}

				//Extrusion BE 210
				_writer->writeBitExtrusion(text.Normal);
				//Thickness BT 39
				_writer->writeBitThickness(text.Thickness);

				//Oblique ang RD 51 present if !(DataFlags & 0x04)
				if ((dataFlags & 0x4) == 0)
					_writer->writeRawDouble(text.ObliqueAngle);
				//Rotation ang RD 50 present if !(DataFlags & 0x08)
				if ((dataFlags & 0x8) == 0)
					_writer->writeRawDouble(text.Rotation);

				//Height RD 40
				_writer->writeRawDouble(text.Height);

				//Width factor RD 41 present if !(DataFlags & 0x10)
				if ((dataFlags & 0x10) == 0)
					_writer->writeRawDouble(text.WidthFactor);

				//Text value TV 1
				_writer->writeVariableText(text.Value);

				//Generation BS 71 present if !(DataFlags & 0x20)
				if ((dataFlags & 0x20) == 0)
					_writer->writeBitShort((short)text.Mirror);
				//Horiz align. BS 72 present if !(DataFlags & 0x40)
				if ((dataFlags & 0x40) == 0)
					_writer->writeBitShort((short)text.HorizontalAlignment);
				//Vert align. BS 73 present if !(DataFlags & 0x80)
				if ((dataFlags & 0x80) == 0)
					_writer->writeBitShort((short)text.VerticalAlignment);
			}

			//Common:
			//Common Entity Handle Data H 7 STYLE(hard pointer)
			_writer->handleReference(DwgReferenceType::HardPointer, text.Style);
}

void DwgObjectWriter::writeMText(MText *mtext) 
{
			//Insertion pt3 BD 10 First picked point. (Location relative to text depends on attachment point (71).)
			_writer->write3BitDouble(mtext.InsertPoint);
			//Extrusion 3BD 210 Undocumented; appears in DXF and entget, but ACAD doesn't even bother to adjust it to unit length.
			_writer->write3BitDouble(mtext.Normal);
			//X-axis dir 3BD 11 Apparently the text x-axis vector. (Why not just a rotation?) ACAD maintains it as a unit vector.
			_writer->write3BitDouble(mtext.AlignmentPoint);
			//Rect width BD 41 Reference rectangle width (width picked by the user).
			_writer->writeBitDouble(mtext.RectangleWidth);

			//R2007+:
			if (R2007Plus)
			{
				//Rect height BD 46 Reference rectangle height.
				_writer->writeBitDouble(mtext.RectangleHeight);
			}

			//Common:
			//Text height BD 40 Undocumented
			_writer->writeBitDouble(mtext.Height);
			//Attachment BS 71 Similar to justification; see DXF doc
			_writer->writeBitShort((short)mtext.AttachmentPoint);
			//Drawing dir BS 72 Left to right, etc.; see DXF doc
			_writer->writeBitShort((short)mtext.DrawingDirection);

			//Extents ht BD ---Undocumented and not present in DXF or entget
			_writer->writeBitDouble(0);
			//Extents wid BD ---Undocumented and not present in DXF or entget
			_writer->writeBitDouble(0);

			//Text TV 1 All text in one long string
			_writer->writeVariableText(mtext.Value);

			//H 7 STYLE (hard pointer)
			_writer->handleReference(DwgReferenceType::HardPointer, mtext.Style);

			//R2000+:
			if (R2000Plus)
			{
				//Linespacing Style BS 73
				_writer->writeBitShort((short)mtext.LineSpacingStyle);
				//Linespacing Factor BD 44
				_writer->writeBitDouble(mtext.LineSpacing);
				//Unknown bit B
				_writer->writeBit(false);
			}

			//R2004+:
			if (R2004Plus)
			{
				//Background flags BL 90 0 = no background, 1 = background fill, 2 = background fill with drawing fill color, 0x10 = text frame (R2018+)
				_writer->writeBitLong((int)mtext.BackgroundFillFlags);

				//background flags has bit 0x01 set, or in case of R2018 bit 0x10:
				if ((mtext.BackgroundFillFlags & BackgroundFillFlags.UseBackgroundFillColor)
					!= BackgroundFillFlags.None
					|| _version > ACadVersion::AC1027
					&& (mtext.BackgroundFillFlags & BackgroundFillFlags.TextFrame) > 0)
				{
					//Background scale factor	BL 45 default = 1.5
					_writer->writeBitDouble(mtext.BackgroundScale);
					//Background color CMC 63
					_writer->writeCmColor(mtext.BackgroundColor);
					//Background transparency BL 441
					_writer->writeBitLong(mtext.BackgroundTransparency.Value);
				}
			}

			//R2018+
			if (!R2018Plus)
			{
				return;
			}

			//Is NOT annotative B
			_writer->writeBit(!mtext.IsAnnotative);

			//IF MTEXT is not annotative
			if (mtext.IsAnnotative)
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
			_writer->writeBitLong((int)mtext.AttachmentPoint);
			//X - axis dir 3BD 10
			_writer->write3BitDouble(mtext.AlignmentPoint);
			//Insertion point 3BD 11
			_writer->write3BitDouble(mtext.InsertPoint);
			//Rect width BD 40
			_writer->writeBitDouble(mtext.RectangleWidth);
			//Rect height BD 41 -> wrong code, should be 46, undocumented
			_writer->writeBitDouble(mtext.RectangleHeight);
			//Extents width BD 42
			_writer->writeBitDouble(mtext.HorizontalWidth);
			//Extents height BD 43
			_writer->writeBitDouble(mtext.VerticalHeight);
			//END REDUNDANT FIELDS

			//Column type BS 71 0 = No columns, 1 = static columns, 2 = dynamic columns
			_writer->writeBitShort((short)mtext.Column.ColumnType);

			//IF Has Columns data(column type is not 0)
			if (mtext.Column.ColumnType != ColumnType.NoColumns)
			{
				//Column height count BL 72
				_writer->writeBitLong(mtext.Column.ColumnCount);
				//Columnn width BD 44
				_writer->writeBitDouble(mtext.Column.ColumnWidth);
				//Gutter BD 45
				_writer->writeBitDouble(mtext.Column.ColumnGutter);
				//Auto height? B 73
				_writer->writeBit(mtext.Column.ColumnAutoHeight);
				//Flow reversed? B 74
				_writer->writeBit(mtext.Column.ColumnFlowReversed);

				//IF not auto height and column type is dynamic columns
				if (!mtext.Column.ColumnAutoHeight && mtext.Column.ColumnType == ColumnType.DynamicColumns)
				{
					for (double h in mtext.Column.ColumnHeights)
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
			_writer->writeBitShort(face.Index1);
			//Vert index BS 72 1 - based vertex index(see DXF doc)
			_writer->writeBitShort(face.Index2);
			//Vert index BS 73 1 - based vertex index(see DXF doc)
			_writer->writeBitShort(face.Index3);
			//Vert index BS 74 1 - based vertex index(see DXF doc)
			_writer->writeBitShort(face.Index4);
}

void DwgObjectWriter::writeVertex2D(Vertex2D *vertex) 
{
			//Flags EC 70 NOT bit-pair-coded.
			_writer->writeByte((unsigned char)(vertex.Flags));

			//Point 3BD 10 NOTE THAT THE Z SEEMS TO ALWAYS BE 0.0! The Z must be taken from the 2D POLYLINE elevation.
			_writer->writeBitDouble(vertex.Location.X);
			_writer->writeBitDouble(vertex.Location.Y);
			_writer->writeBitDouble(0.0);

			//Start width BD 40 If it's negative, use the abs val for start AND end widths (and note that no end width will be present).
			//This is a compression trick for cases where the start and end widths are identical and non-0.
			if (vertex.StartWidth != 0.0 && vertex.EndWidth == vertex.StartWidth)
			{
				_writer->writeBitDouble(0.0 - (double)vertex.StartWidth);
			}
			else
			{
				_writer->writeBitDouble(vertex.StartWidth);
				//End width BD 41 Not present if the start width is < 0.0; see above.
				_writer->writeBitDouble(vertex.EndWidth);
			}

			//Bulge BD 42
			_writer->writeBitDouble(vertex.Bulge);

			//R2010+:
			if (R2010Plus)
			{
				//Vertex ID BL 91
				_writer->writeBitLong(vertex.Id);
			}

			//Common:
			//Tangent dir BD 50
			_writer->writeBitDouble(vertex.CurveTangent);
}

void DwgObjectWriter::writeVertex(Vertex *vertex) 
{
			//Flags EC 70 NOT bit-pair-coded.
			_writer->writeByte((unsigned char)vertex.Flags);
			//Point 3BD 10
			_writer->write3BitDouble(vertex.Location);
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
			_writer->write3BitDouble(tolerance.InsertionPoint);
			//X direction 3BD 11
			_writer->write3BitDouble(tolerance.Direction);
			//Extrusion 3BD 210 etc.
			_writer->write3BitDouble(tolerance.Normal);
			//Text string BS 1
			_writer->writeVariableText(tolerance.Text);

			//Common Entity Handle Data
			//H DIMSTYLE(hard pointer)
			_writer->handleReference(DwgReferenceType::HardPointer, tolerance.Style);
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
				_writer->writeBitLong((int)viewport->status());
				//Style Sheet TV 1
				_writer->writeVariableText(std::string());   //This is never used
																//Render Mode RC 281
				_writer->writeByte((unsigned char)viewport->renderMode());
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
				_writer->writeBitShort((short)viewport->ucsOrthographicType());
			}

			//R2004 +:
			if (R2004Plus)
			{
				//ShadePlot Mode BS 170
				_writer->writeBitShort((short)viewport->shadePlotMode());
			}

			//R2007 +:
			if (R2007Plus)
			{
				//Use def. lights B 292
				_writer->writeBit(viewport->useDefaultLighting());
				//Def.lighting type RC 282
				_writer->writeByte((unsigned char)viewport->defaultLightingType());
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
				for (auto &&layer : viewport->frozenLayers())
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

			Entity prevHolder = _prev;
			Entity nextHolder = _next;
			_prev = nullptr;
			_next = nullptr;

			Entity curr = entities.First();
			for (int i = 1; i < entities.Count(); i++)
			{
				_next = entities.ElementAt(i);
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
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
	//_writer->handleReference(DwgReferenceType.HardPointer, dimension->Block);
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
			if (this.R13_14Only)
			{
				//X Scale BD 41
				_writer->writeBitDouble(insert->XScale());
				//Y Scale BD 42
				_writer->writeBitDouble(insert->YScale());
				//Z Scale BD 43
				_writer->writeBitDouble(insert->ZScale());
			}

			//R2000 + Only:
			if (this.R2000Plus)
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
			_writer->write3BitDouble(insert->mormal());
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
			else if (this.R2004Plus)
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

void DwgObjectWriter::writeFace3D(Face3D *face) {}

void DwgObjectWriter::writeMLine(MLine *mline) {}

void DwgObjectWriter::writeLwPolyline(LwPolyline *lwPolyline) {}

void DwgObjectWriter::writeHatch(Hatch *hatch) {}

void DwgObjectWriter::writeLeader(Leader *leader) {}

void DwgObjectWriter::writeMultiLeader(MultiLeader *multiLeader) {}

void DwgObjectWriter::writeMultiLeaderAnnotContext(MultiLeaderAnnotContext *annotContext) {}

void DwgObjectWriter::writeLine(Line *line) {}

void DwgObjectWriter::writePoint(Point *point) {}

void DwgObjectWriter::writePolyfaceMesh(PolyfaceMesh *fm) {}

void DwgObjectWriter::writePolyline2D(Polyline2D *pline) {}

void DwgObjectWriter::writePolyline3D(Polyline3D *pline) {}

void DwgObjectWriter::writeSeqend(Seqend *seqend) {}

void DwgObjectWriter::writeShape(Shape *shape) {}

void DwgObjectWriter::writeSolid(Solid *solid) {}

void DwgObjectWriter::writeSolid3D(Solid3D *solid) {}

void DwgObjectWriter::writeCadImage(CadWipeoutBase *image) {}

void DwgObjectWriter::writeSpline(Spline *spline) {}

void DwgObjectWriter::writeRay(Ray *ray) {}

void DwgObjectWriter::writeTextEntity(TextEntity *text) {}

void DwgObjectWriter::writeMText(MText *mtext) {}

void DwgObjectWriter::writeFaceRecord(VertexFaceRecord *face) {}

void DwgObjectWriter::writeVertex2D(Vertex2D *vertex) {}

void DwgObjectWriter::writeVertex(Vertex *vertex) {}

void DwgObjectWriter::writeTolerance(Tolerance *tolerance) {}

void DwgObjectWriter::writeViewport(Viewport *viewport) {}

void DwgObjectWriter::writeXLine(XLine *xline) {}

void DwgObjectWriter::writeChildEntities(const std::vector<Entity *> &entities, Seqend *seqend) {}

}// namespace dwg
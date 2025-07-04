/**
 * libDWG - A C++ library for reading and writing DWG and DXF files : CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed : the hope that it will be useful,
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
#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/header/CadHeader.h>
#include <dwg/io/dxf/writers/DxfSectionWriterBase_p.h>
#include <dwg/io/dxf/writers/IDxfStreamWriter_p.h>
#include <dwg/entities/Arc.h>
#include <dwg/entities/Circle.h>
#include <dwg/entities/Entity.h>
#include <dwg/entities/Dimension.h>
#include <dwg/entities/DimensionAligned.h>
#include <dwg/entities/DimensionLinear.h>
#include <dwg/entities/DimensionRadius.h>
#include <dwg/entities/DimensionDiameter.h>
#include <dwg/entities/DimensionAngular2Line.h>
#include <dwg/entities/DimensionAngular3Pt.h>
#include <dwg/entities/DimensionOrdinate.h>
#include <dwg/entities/Hatch.h>
#include <dwg/entities/Ellipse.h>
#include <dwg/entities/Face3D.h>
#include <dwg/entities/Insert.h>
#include <dwg/entities/Leader.h>
#include <dwg/entities/Line.h>
#include <dwg/entities/Mesh.h>
#include <dwg/entities/MText.h>
#include <dwg/entities/MultiLeader.h>
#include <dwg/entities/LwPolyline.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/DimensionStyle.h>
#include <dwg/objects/MultiLeaderAnnotContext.h>
#include <dwg/tables/TextStyle.h>
#include <dwg/entities/Face3D.h>
#include <dwg/entities/collection/AttributeEntitySeqendCollection.h>
#include <algorithm>
#include <dwg/tables/LineType.h>
#include <dwg/objects/MultiLeaderStyle.h>
#include <dwg/entities/Point.h>
#include <dwg/entities/MLine.h>
#include <dwg/entities/Seqend.h>
#include <dwg/tables/Layer.h>
#include <dwg/objects/MLineStyle.h>
#include <dwg/entities/Ray.h>
#include <dwg/entities/Shape.h>
#include <dwg/entities/Spline.h>

namespace dwg {

void DxfSectionWriterBase::writeEntity(Entity *entity) {}

void DxfSectionWriterBase::writeArc(Arc *arc) 
{
    writeCircle(arc);

    _writer->write(DxfCode::Subclass, DxfSubclassMarker::Arc);

    _writer->write(50, arc->startAngle());
    _writer->write(51, arc->endAngle());
}

void DxfSectionWriterBase::writeCircle(Circle *circle) 
{
    _writer->write(DxfCode::Subclass, DxfSubclassMarker::Circle);

    _writer->write(10, circle->center());

    _writer->write(39, circle->thickness());
    _writer->write(40, circle->radius());

    _writer->write(210, circle->normal());
}

void DxfSectionWriterBase::writeDimension(Dimension *dim) 
{
    _writer->write(DxfCode::Subclass, DxfSubclassMarker::Dimension);

    _writer->writeName(2, dim->block());

    _writer->write(10, dim->definitionPoint());
    _writer->write(11, dim->textMiddlePoint());

    _writer->write(53, dim->textRotation());
    _writer->write(70, static_cast<short>(dim->flags()));
    _writer->write(71, static_cast<short>(dim->attachmentPoint()));
    _writer->write(72, static_cast<short>(dim->lineSpacingStyle()));
	_writer->write(41, dim->lineSpacingFactor());

    if (dim->text().empty())
    {
        _writer->write(1, dim->text());
    }

    _writer->write(210, dim->normal());

    _writer->writeName(3, dim->dimStyle());

    DimensionAligned *aligned = dynamic_cast<DimensionAligned *>(dim);
    DimensionRadius *radius = dynamic_cast<DimensionRadius *>(dim);
    DimensionDiameter *diameter = dynamic_cast<DimensionDiameter *>(dim);
    DimensionAngular2Line *angular2Line = dynamic_cast<DimensionAngular2Line *>(dim);
    DimensionAngular3Pt *angular3Pt = dynamic_cast<DimensionAngular3Pt *>(dim);
    DimensionOrdinate *ordinate = dynamic_cast<DimensionOrdinate *>(dim);
    if (aligned)
    {
        writeDimensionAligned(aligned);
    }
    else if(radius)
    {
        writeDimensionRadius(radius);
    }
    else if(diameter)
    {
        writeDimensionDiameter(diameter);
    }
    else if(angular2Line)
    {
        writeDimensionAngular2Line(angular2Line);
    }
    else if(angular3Pt)
    {
        writeDimensionAngular3Pt(angular3Pt);
    }
    else if(ordinate)
    {
        writeDimensionOrdinate(ordinate);
    }
    else
    {
        throw std::runtime_error("Dimension type not implemented");
    }
}

void DxfSectionWriterBase::writeDimensionAligned(DimensionAligned *aligned) 
{
    _writer->write(DxfCode::Subclass, DxfSubclassMarker::AlignedDimension);

    _writer->write(13, aligned->firstPoint());
	_writer->write(14, aligned->secondPoint());

    DimensionLinear *linear = dynamic_cast<DimensionLinear *>(aligned);
	if (linear)
	{
		writeDimensionLinear(linear);
	}
}

void DxfSectionWriterBase::writeDimensionLinear(DimensionLinear *linear) 
{
    _writer->write(50, linear->rotation());

    _writer->write(DxfCode::Subclass, DxfSubclassMarker::LinearDimension);
}

void DxfSectionWriterBase::writeDimensionRadius(DimensionRadius *radius) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::RadialDimension);

	_writer->write(15, radius->angleVertex());

	_writer->write(40, radius->leaderLength());
}

void DxfSectionWriterBase::writeDimensionDiameter(DimensionDiameter *diameter) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::DiametricDimension);

	_writer->write(15, diameter->angleVertex());

	_writer->write(40, diameter->leaderLength());
}

void DxfSectionWriterBase::writeDimensionAngular2Line(DimensionAngular2Line *angular2Line) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::Angular2LineDimension);

	_writer->write(13, angular2Line->firstPoint());
	_writer->write(14, angular2Line->secondPoint());
	_writer->write(15, angular2Line->angleVertex());
	_writer->write(16, angular2Line->dimensionArc());
}

void DxfSectionWriterBase::writeDimensionAngular3Pt(DimensionAngular3Pt *angular3Pt) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::Angular3PointDimension);

	_writer->write(13, angular3Pt->firstPoint());
	_writer->write(14, angular3Pt->secondPoint());
	_writer->write(15, angular3Pt->angleVertex());
}

void DxfSectionWriterBase::writeDimensionOrdinate(DimensionOrdinate *ordinate) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::OrdinateDimension);

	_writer->write(13, ordinate->featureLocation());
	_writer->write(14, ordinate->leaderEndpoint());
}

void DxfSectionWriterBase::writeHatch(Hatch *hatch) {}

void DxfSectionWriterBase::writeBoundaryPath(HatchBoundaryPath *path) {}

void DxfSectionWriterBase::writeHatchBoundaryPathEdge(HatchBoundaryPathEdge *edge) {}

void DxfSectionWriterBase::writeHatchPattern(Hatch *hatch, HatchPattern *pattern) {}

void DxfSectionWriterBase::writeEllipse(Ellipse *ellipse) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::Ellipse);

	_writer->write(10, ellipse->center());

	_writer->write(11, ellipse->endPoint());

	_writer->write(210, ellipse->normal());

	_writer->write(39, ellipse->thickness());
	_writer->write(40, ellipse->radiusRatio());
	_writer->write(41, ellipse->startParameter());
	_writer->write(42, ellipse->endParameter());
}

void DxfSectionWriterBase::writeFace3D(Face3D *face) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::Face3d);

	_writer->write(10, face->firstCorner());
	_writer->write(11, face->secondCorner());
	_writer->write(12, face->thirdCorner());
	_writer->write(13, face->fourthCorner());

	_writer->write(70, (short)face->flags());
}

void DxfSectionWriterBase::writeInsert(Insert *insert) 
{
	_writer->write(DxfCode::Subclass, insert->subclassMarker());

	_writer->writeName(2, insert->block());

	_writer->write(10, insert->insertPoint());

	_writer->write(41, insert->XScale());
	_writer->write(42, insert->YScale());
	_writer->write(43, insert->ZScale());

	_writer->write(50, insert->rotation());


	_writer->write(70, (short)insert->columnCount());
	_writer->write(71, (short)insert->rowCount());

	_writer->write(44, insert->columnSpacing());
	_writer->write(45, insert->rowSpacing());

	_writer->write(210, insert->normal());

	if (insert->hasAttributes())
	{
		_writer->write(66, 1);

		//WARNING: Write extended data before attributes

        auto attrs = insert->attributes();
        for (auto it = attrs->begin(); it != attrs->end(); ++it)
        {
            writeEntity(*it);
        }

		writeSeqend(insert->attributes()->seqend());
	}
}

void DxfSectionWriterBase::writeLeader(Leader *leader) 
{
    _writer->write(DxfCode::Subclass, DxfSubclassMarker::Leader);

    _writer->writeName(3, leader->style());

	_writer->write(71, leader->arrowHeadEnabled() ? (short)1 : (short)0);
	_writer->write(72, (short)leader->pathType());
	_writer->write(73, (short)leader->creationType());
	_writer->write(74, leader->hookLineDirection() == HookLineDirection::Same ? (short)1 : (short)0());
	_writer->write(75, leader->hasHookline() ? (short)1 : (short)0());

	_writer->write(40, leader->textHeight());
	_writer->write(41, leader->textWidth());

	_writer->write(76, leader->vertices().size());
	for (auto &&vertex : leader->vertices())
	{
		_writer->write(10, vertex);
	}

	_writer->write(210, leader->normal());

	_writer->write(211, leader->horizontalDirection());
	_writer->write(212, leader->blockOffset());
	_writer->write(213, leader->annotationOffset());
}

void DxfSectionWriterBase::writeLine(Line *line) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::Line);

	_writer->write(10, line->startPoint());

	_writer->write(11, line->endPoint());

	_writer->write(39, line->thickness());

	_writer->write(210, line->normal());
}

void DxfSectionWriterBase::writeLwPolyline(LwPolyline *polyline) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::LwPolyline);

	_writer->write(90, polyline->vertices().size());
	_writer->write(70, (short)polyline->flags());

	_writer->write(38, polyline->elevation());
	_writer->write(39, polyline->thickness());

	for (auto &&v : polyline->vertices())
    {
		_writer->write(10, v.Location);
		_writer->write(40, v.StartWidth);
		_writer->write(41, v.EndWidth);
		_writer->write(42, v.Bulge);
	}

	_writer->write(210, polyline->normal());
}

void DxfSectionWriterBase::writeMesh(Mesh *mesh) 
{
    _writer->write(DxfCode::Subclass, DxfSubclassMarker::Mesh);

	_writer->write(71, (short)mesh->version());
	_writer->write(72, (short)(mesh->blendCrease() ? 1 : 0));

	_writer->write(91, mesh->subdivisionLevel());

	_writer->write(92, mesh->vertices().size());
	for (auto &&vertex : mesh->vertices())
	{
		_writer->write(10, vertex);
	}

	int nFaces = mesh->faces().size();
    std::for_each(mesh->faces().begin(), mesh->faces().end(), [&](const std::vector<int> &f) {
        nFaces += f.size();
    });

	_writer->write(93, nFaces);
	for (auto &&face : mesh->faces())
	{
		_writer->write(90, face.size());
		for (int index : face)
		{
			_writer->write(90, index);
		}
	}

	_writer->write(94, mesh->edges().size());
	for (auto &&edge : mesh->edges())
	{
		_writer->write(90, edge.start);
		_writer->write(90, edge.end);
	}

	_writer->write(95, mesh->edges().size());
	for (auto &&edge : mesh->edges())
	{
        _writer->write(140, edge.crease.has_value() ? edge.crease.value() : DwgVariant());
	}

	_writer->write(90, 0);
}

void DxfSectionWriterBase::writeMLine(MLine *mLine) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::MLine);

	//Style has two references
	_writer->writeName(2, mLine->style());
	_writer->writeHandle(340, mLine->style());

	_writer->write(40, mLine->scaleFactor());

	_writer->write(70, (short)mLine->justification());
	_writer->write(71, (short)mLine->flags());
	_writer->write(72, (short)mLine->vertices().size());

	if (mLine->style())
	{
		_writer->write(73, (short)mLine->style()->elements().size());
	}

	_writer->write(10, mLine->startPoint());

	_writer->write(210, mLine->normal());

	for (auto &&v : mLine->vertices())
	{
		_writer->write(11, v.Position);
		_writer->write(12, v.Direction);
		_writer->write(13, v.Miter);

        for (auto&& s : v.Segments)
		{
			_writer->write(74, (short)s.Parameters.size());
			for (auto &&parameter : s.Parameters)
			{
				_writer->write(41, parameter);
			}
			_writer->write(75, (short)s.AreaFillParameters.size());
			for (auto &&areaFillParameter : s.AreaFillParameters)
			{
				_writer->write(42, areaFillParameter);
			}
		}
	}
}

void DxfSectionWriterBase::writeMText(MText *mtext, bool writeSubclass) 
{
	if (writeSubclass)
	{
		_writer->write(DxfCode::Subclass, DxfSubclassMarker::MText);
	}

	_writer->write(10, mtext->insertPoint());

	_writer->write(40, mtext->height());
	_writer->write(41, mtext->rectangleWidth());
	_writer->write(44, mtext->lineSpacing());

	if (version() >= ACadVersion::AC1021)
	{
		_writer->write(46, mtext->rectangleHeight());
	}

	_writer->write(71, (short)mtext->attachmentPoint());
	_writer->write(72, (short)mtext->drawingDirection());

	writeLongTextValue(1, 3, mtext->value());

	_writer->writeName(7, mtext->style());

	_writer->write(73, (short)mtext->lineSpacingStyle());

	_writer->write(11, mtext->alignmentPoint());

	_writer->write(210, mtext->normal());
}

void DxfSectionWriterBase::writeMultiLeader(MultiLeader *multiLeader) 
{
    MultiLeaderAnnotContext *contextData = multiLeader->contextData();

	_writer->write(100, "AcDbMLeader");

	//	version
	//	if (Version > ACadVersion.
	_writer->write(270, 2);

	writeMultiLeaderAnnotContext(contextData);

	//	MultiLeader properties
	_writer->writeHandle(340, multiLeader->style());
	_writer->write(90, multiLeader->propertyOverrideFlags());
	_writer->write(170, (short)multiLeader->pathType());

	_writer->writeCmColor(91, multiLeader->lineColor());

	_writer->writeHandle(341, multiLeader->lineType());
	_writer->write(171, (short)multiLeader->leaderLineWeight());
	_writer->write(290, multiLeader->enableLanding());
	_writer->write(291, multiLeader->enableDogleg());
	_writer->write(41, multiLeader->landingDistance());
	_writer->write(42, multiLeader->arrowheadSize());
	_writer->write(172, (short)multiLeader->contentType());
	_writer->writeHandle(343, multiLeader->textStyle());
	_writer->write(173, (short)multiLeader->textLeftAttachment());
	_writer->write(95, (short)multiLeader->textRightAttachment());
	_writer->write(174, (short)multiLeader->textAngle());
	_writer->write(175, (short)multiLeader->textAlignment());

	_writer->writeCmColor(92, multiLeader->textColor());

	_writer->write(292, multiLeader->textFrame());

	_writer->writeCmColor(93, multiLeader->blockContentColor());

	_writer->write(10, multiLeader->blockContentScale());

	_writer->write(43, multiLeader->blockContentRotation());
	_writer->write(176, (short)multiLeader->blockContentConnection());
	_writer->write(293, multiLeader->enableAnnotationScale());
	_writer->write(294, multiLeader->textDirectionNegative());
	_writer->write(178, multiLeader->textAligninIPE());
	_writer->write(179, (short)multiLeader->textAttachmentPoint());
	_writer->write(45, multiLeader->scaleFactor());
	_writer->write(271, (short)multiLeader->textAttachmentDirection());
	_writer->write(272, (short)multiLeader->textBottomAttachment());
	_writer->write(273, (short)multiLeader->textTopAttachment());
	_writer->write(295, 0);
}

void DxfSectionWriterBase::writeMultiLeaderAnnotContext(MultiLeaderAnnotContext *contextData) 
{

    auto writeLeaderLine = [&](const MultiLeaderAnnotContext::LeaderLine &leaderLine) {
		_writer->write(304, "LEADER_LINE{");

		for (auto &&point : leaderLine.points)
		{
			_writer->write(10, point);
		}
		_writer->write(91, leaderLine.index);

		_writer->write(305, "}");   //	LEADER_Line
    };

    auto writeLeaderRoot = [&](const MultiLeaderAnnotContext::LeaderRoot &leaderRoot) {
		_writer->write(302, "LEADER{");

		// TODO: true is placeholder
		_writer->write(290, true ? (short)1 : (short)0); // Has Set Last Leader Line Point
		_writer->write(291, true ? (short)1 : (short)0); // Has Set Dogleg Vector

		_writer->write(10, leaderRoot.connectionPoint);
    };

	_writer->write(300, "CONTEXT_DATA{");
	_writer->write(40, contextData->scaleFactor());
	_writer->write(10, contextData->contentBasePoint());
	_writer->write(41, contextData->textHeight());
	_writer->write(140, contextData->arrowheadSize());
	_writer->write(145, contextData->landingGap());
	_writer->write(174, (short)contextData->textLeftAttachment());
	_writer->write(175, (short)contextData->textRightAttachment());
	_writer->write(176, (short)contextData->textAlignment());
	_writer->write(177, (short)contextData->blockContentConnection());
	_writer->write(290, contextData->hasTextContents());
	_writer->write(304, contextData->textLabel());

	_writer->write(11, contextData->textNormal());

	_writer->writeHandle(340, contextData->textStyle());

	_writer->write(12, contextData->textLocation());

	_writer->write(13, contextData->direction());

	_writer->write(42, contextData->textRotation());
	_writer->write(43, contextData->boundaryWidth());
	_writer->write(44, contextData->boundaryHeight());
	_writer->write(45, contextData->lineSpacingFactor());
	_writer->write(170, (short)contextData->lineSpacing());

	_writer->writeCmColor(90, contextData->textColor());

	_writer->write(171, (short)contextData->textAttachmentPoint());
	_writer->write(172, (short)contextData->flowDirection());

	_writer->writeCmColor(91, contextData->backgroundFillColor());

	_writer->write(141, contextData->backgroundScaleFactor());
	_writer->write(92, contextData->backgroundTransparency());
	_writer->write(291, contextData->backgroundFillEnabled());
	_writer->write(292, contextData->backgroundMaskFillOn());
	_writer->write(173, contextData->columnType());
	_writer->write(293, contextData->textHeightAutomatic());
	_writer->write(142, contextData->columnWidth());
	_writer->write(143, contextData->columnGutter());
	_writer->write(294, contextData->columnFlowReversed());
	_writer->write(295, contextData->wordBreak());

	_writer->write(296, contextData->hasContentsBlock());

	_writer->write(110, contextData->basePoint());

	_writer->write(111, contextData->baseDirection());

	_writer->write(112, contextData->baseVertical());

	_writer->write(297, contextData->normalReversed());

	for (auto &&leaderRoot : contextData->leaderRoots())
	{
		writeLeaderRoot(leaderRoot);
	}

	_writer->write(272, (short)contextData->textBottomAttachment());
	_writer->write(273, (short)contextData->textTopAttachment());
	_writer->write(301, "}");       //	CONTEXT_DATA
}

void DxfSectionWriterBase::writePoint(Point *line) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::Point);

	_writer->write(10, line->location());

	_writer->write(39, line->thickness());

	_writer->write(210, line->normal());

	_writer->write(50, line->rotation());
}

void DxfSectionWriterBase::writePolyline(Polyline *polyline) {}

void DxfSectionWriterBase::writeSeqend(Seqend *seqend) 
{
	_writer->write(0, seqend->objectName());
	_writer->write(5, seqend->handle());
	_writer->write(330, seqend->owner()->handle());
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::Entity);
	_writer->write(8, seqend->layer()->name());
}

void DxfSectionWriterBase::writeRay(Ray *ray) 
{
	_writer->write(10, ray->startPoint());

	_writer->write(11, ray->direction());
}

void DxfSectionWriterBase::writeShape(Shape *shape) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::Shape);

	_writer->write(39, shape->thickness());

	_writer->write(10, shape->insertionPoint());

	_writer->write(40, shape->size());

	_writer->writeName(2, shape->shapeStyle());

	_writer->write(50, shape->rotation());

	_writer->write(41, shape->relativeXScale());
	_writer->write(51, shape->obliqueAngle());

	_writer->write(210, shape->normal());
}

void DxfSectionWriterBase::writeSolid(Solid *solid) {}

void DxfSectionWriterBase::writeSpline(Spline *spline) 
{
	_writer->write(DxfCode::Subclass, DxfSubclassMarker::Spline);

	if (spline->flags().testFlag(SplineFlag::Planar))
	{
		_writer->write(210, spline->normal());
	}

	_writer->write(70, (short)spline->flags());
	_writer->write(71, (short)spline->degree());
	_writer->write(72, (short)spline->knots().size());
	_writer->write(73, (short)spline->controlPoints().size());

	if (!spline.fitPoints().empty())
	{
		_writer->write(74, (short)spline->fitPoints().size());
	}

	_writer->write(42, spline->knotTolerance());
	_writer->write(43, spline->controlPointTolerance());
	_writer->write(44, spline->fitTolerance());

	_writer->write(12, spline->startTangent());
	_writer->write(13, spline->endTangent());

	for (auto &&knot : spline->lnots())
	{
		_writer->write(40, knot);
	}
	for (auto &&weight : spline->weights())
	{
		_writer->write(41, weight);
	}
	for (auto &&cp : spline->controlPoints())
	{
		_writer->write(10, cp);
	}
	for (auto &&fp : spline->fitPoints())
	{
		_writer->write(11, fp);
	}
}

void DxfSectionWriterBase::writeTextEntity(TextEntity *text) {}

void DxfSectionWriterBase::writeTolerance(Tolerance *tolerance) {}

void DxfSectionWriterBase::writeAttributeBase(AttributeBase *att) {}

void DxfSectionWriterBase::writeVertex(Vertex *v) {}

void DxfSectionWriterBase::writeViewport(Viewport *vp) {}

void DxfSectionWriterBase::writeCadImage(CadWipeoutBase *image) {}

void DxfSectionWriterBase::writeXLine(XLine *xline) {}

}// namespace dwg
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
#include <dwg/header/CadHeader.h>
#include <dwg/io/dxf/writers/DxfSectionWriterBase_p.h>
#include <dwg/io/dxf/writers/IDxfStreamWriter_p.h>
#include <dwg/DxfFileToken_p.h>

namespace dwg {

DxfSectionWriterBase::DxfSectionWriterBase(IDxfStreamWriter *writer, CadDocument *document, CadObjectHolder *holder,
                                           DxfWriterConfiguration configuration)
    : _writer(writer), _document(document), _holder(holder), _configuration(configuration)
{
}

DxfSectionWriterBase::~DxfSectionWriterBase() {}

void DxfSectionWriterBase::write() 
{
    _writer->write(DxfCode::Start, DxfFileToken::BeginSection);
    _writer->write(DxfCode::SymbolTableName, sectionName());

    writeSection();

    _writer->write(DxfCode::Start, DxfFileToken::EndSection);
}

ACadVersion DxfSectionWriterBase::version() const
{
    return _document->header()->version();
}

CadObjectHolder *DxfSectionWriterBase::holder()
{
    return _holder;
}

void DxfSectionWriterBase::writeCommonObjectData(CadObject *object) {}

void DxfSectionWriterBase::writeExtendedData(ExtendedDataDictionary *xdata) {}

void DxfSectionWriterBase::writeCommonEntityData(Entity *entity) {}

void DxfSectionWriterBase::writeLongTextValue(int code, int subcode, const std::string &text) {}

void DxfSectionWriterBase::writeEntity(Entity *entity) {}

void DxfSectionWriterBase::writeArc(Arc *arc) {}

void DxfSectionWriterBase::writeCircle(Circle *circle) {}

void DxfSectionWriterBase::writeDimension(Dimension *dim) {}

void DxfSectionWriterBase::writeDimensionAligned(DimensionAligned *aligned) {}

void DxfSectionWriterBase::writeDimensionLinear(DimensionLinear *linear) {}

void DxfSectionWriterBase::writeDimensionRadius(DimensionRadius *radius) {}

void DxfSectionWriterBase::writeDimensionDiameter(DimensionDiameter *diameter) {}

void DxfSectionWriterBase::writeDimensionAngular2Line(DimensionAngular2Line *angular2Line) {}

void DxfSectionWriterBase::writeDimensionAngular3Pt(DimensionAngular3Pt *angular3Pt) {}

void DxfSectionWriterBase::writeDimensionOrdinate(DimensionOrdinate *ordinate) {}

void DxfSectionWriterBase::writeHatch(Hatch *hatch) {}

void DxfSectionWriterBase::writeBoundaryPath(HatchBoundaryPath *path) {}

void DxfSectionWriterBase::writeHatchBoundaryPathEdge(HatchBoundaryPathEdge *edge) {}

void DxfSectionWriterBase::writeHatchPattern(Hatch *hatch, HatchPattern *pattern) {}

void DxfSectionWriterBase::writeEllipse(Ellipse *ellipse) {}

void DxfSectionWriterBase::writeFace3D(Face3D *face) {}

void DxfSectionWriterBase::writeInsert(Insert *insert) {}

void DxfSectionWriterBase::writeLeader(Leader *leader) {}

void DxfSectionWriterBase::writeLine(Line *line) {}

void DxfSectionWriterBase::writeLwPolyline(LwPolyline *polyline) {}

void DxfSectionWriterBase::writeMesh(Mesh *mesh) {}

void DxfSectionWriterBase::writeMLine(MLine *mLine) {}

void DxfSectionWriterBase::writeMText(MText *mtext, bool writeSubclass) {}

void DxfSectionWriterBase::writeMultiLeader(MultiLeader *multiLeader) {}

void DxfSectionWriterBase::writeMultiLeaderAnnotContext(MultiLeaderAnnotContext *contextData) {}

void DxfSectionWriterBase::writeLeaderRoot(MultiLeaderAnnotContextLeaderRoot *leaderRoot) {}

void DxfSectionWriterBase::writeLeaderLine(MultiLeaderAnnotContextLeaderLine *leaderLine) {}

void DxfSectionWriterBase::writePoint(Point *line) {}

void DxfSectionWriterBase::writePolyline(Polyline *polyline) {}

void DxfSectionWriterBase::writeSeqend(Seqend *seqend) {}

void DxfSectionWriterBase::writeRay(Ray *ray) {}

void DxfSectionWriterBase::writeShape(Shape *shape) {}

void DxfSectionWriterBase::writeSolid(Solid *solid) {}

void DxfSectionWriterBase::writeSpline(Spline *spline) {}

void DxfSectionWriterBase::writeTextEntity(TextEntity *text) {}

void DxfSectionWriterBase::writeTolerance(Tolerance *tolerance) {}

void DxfSectionWriterBase::writeAttributeBase(AttributeBase *att) {}

void DxfSectionWriterBase::writeVertex(Vertex *v) {}

void DxfSectionWriterBase::writeViewport(Viewport *vp) {}

void DxfSectionWriterBase::writeCadImage(CadWipeoutBase *image) {}

void DxfSectionWriterBase::writeXLine(XLine *xline) {}

}// namespace dwg
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

namespace dwg {

void DwgObjectWriter::writeEntity(Entity *entity) {}
void DwgObjectWriter::writeArc(Arc *arc) {}
void DwgObjectWriter::writeAttribute(AttributeEntity *att) {}
void DwgObjectWriter::writeAttDefinition(AttributeDefinition *attdef) {}
void DwgObjectWriter::writeCommonAttData(AttributeBase *att) {}
void DwgObjectWriter::writeCircle(Circle *circle) {}
void DwgObjectWriter::writeCommonDimensionData(Dimension *dimension) {}
void DwgObjectWriter::writeDimensionLinear(DimensionLinear *dimension) {}
void DwgObjectWriter::writeDimensionAligned(DimensionAligned *dimension) {}
void DwgObjectWriter::writeDimensionRadius(DimensionRadius *dimension) {}
void DwgObjectWriter::writeDimensionAngular2Line(DimensionAngular2Line *dimension) {}
void DwgObjectWriter::writeDimensionAngular3Pt(DimensionAngular3Pt *dimension) {}
void DwgObjectWriter::writeDimensionDiameter(DimensionDiameter *dimension) {}
void DwgObjectWriter::writeDimensionOrdinate(DimensionOrdinate *dimension) {}
void DwgObjectWriter::writeEllipse(Ellipse *ellipse) {}
void DwgObjectWriter::writeInsert(Insert *insert) {}
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
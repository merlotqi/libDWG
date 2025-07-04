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

#pragma once

#include <dwg/ACadVersion.h>
#include <dwg/io/dxf/DxfWriterConfiguration.h>

namespace dwg {

class IDxfStreamWriter;
class CadDocument;
class CadObjectHolder;
class CadObject;
class Entity;
class ExtendedDataDictionary;
class Arc;
class Circle;
class Dimension;
class DimensionAligned;
class DimensionLinear;
class DimensionRadius;
class DimensionDiameter;
class DimensionAngular2Line;
class DimensionAngular3Pt;
class DimensionOrdinate;
class Hatch;
class HatchBoundaryPath;
class HatchPattern;
class Ellipse;
class Face3D;
class Insert;
class Leader;
class Line;
class LwPolyline;
class Mesh;
class MLine;
class MText;
class MultiLeader;
class MultiLeaderAnnotContext;
class Point;
class Polyline;
class Seqend;
class Ray;
class Shape;
class Solid;
class Spline;
class TextEntity;
class Tolerance;
class AttributeBase;
class Vertex;
class Viewport;
class CadWipeoutBase;
class XLine;

class DxfSectionWriterBase
{
public:
    DxfSectionWriterBase(IDxfStreamWriter *writer, CadDocument *document, CadObjectHolder *holder,
                         DxfWriterConfiguration configuration);
    virtual ~DxfSectionWriterBase();
    virtual std::string sectionName() const = 0;

    void write();
    ACadVersion version() const;
    CadObjectHolder *holder();

protected:
    virtual void writeSection() = 0;
    void writeCommonObjectData(CadObject *object);
    void writeExtendedData(ExtendedDataDictionary *xdata);
    void writeCommonEntityData(Entity *entity);
    void writeLongTextValue(int code, int subcode, const std::string &text);
    void writeEntity(Entity *entity);

private:
    void writeArc(Arc *arc);
    void writeCircle(Circle *circle);
    void writeDimension(Dimension *dim);
    void writeDimensionAligned(DimensionAligned *aligned);
    void writeDimensionLinear(DimensionLinear *linear);
    void writeDimensionRadius(DimensionRadius *radius);
    void writeDimensionDiameter(DimensionDiameter *diameter);
    void writeDimensionAngular2Line(DimensionAngular2Line *angular2Line);
    void writeDimensionAngular3Pt(DimensionAngular3Pt *angular3Pt);
    void writeDimensionOrdinate(DimensionOrdinate *ordinate);
    void writeHatch(Hatch *hatch);
    void writeBoundaryPath(HatchBoundaryPath *path);
    void writeHatchPattern(Hatch *hatch, HatchPattern *pattern);
    void writeEllipse(Ellipse *ellipse);
    void writeFace3D(Face3D *face);
    void writeInsert(Insert *insert);
    void writeLeader(Leader *leader);
    void writeLine(Line *line);
    void writeLwPolyline(LwPolyline *polyline);
    void writeMesh(Mesh *mesh);
    void writeMLine(MLine *mLine);
    void writeMText(MText *mtext, bool writeSubclass = true);
    void writeMultiLeader(MultiLeader *multiLeader);
    void writeMultiLeaderAnnotContext(MultiLeaderAnnotContext *contextData);
    void writePoint(Point *line);
    void writePolyline(Polyline *polyline);
    void writeSeqend(Seqend *seqend);
    void writeRay(Ray *ray);
    void writeShape(Shape *shape);
    void writeSolid(Solid *solid);
    void writeSpline(Spline *spline);
    void writeTextEntity(TextEntity *text);
    void writeTolerance(Tolerance *tolerance);
    void writeAttributeBase(AttributeBase *att);
    void writeVertex(Vertex *v);
    void writeViewport(Viewport *vp);
    void writeCadImage(CadWipeoutBase *image);
    void writeXLine(XLine *xline);

protected:
    IDxfStreamWriter *_writer;
    CadDocument *_document;
    CadObjectHolder *_holder;
    DxfWriterConfiguration _configuration;
};

}// namespace dwg
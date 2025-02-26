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

#include <dwg/io/dwg/DwgSectionIO_p.h>
#include <dwg/utils/Encoding.h>
#include <map>
#include <queue>
#include <sstream>

namespace dwg {

class IDwgStreamWriter;
class CadDocument;
class CadHeader;
class CadObject;
class TableEntry;
class Entity;
class ExtendedDataDictionary;
class AppId;
class ExtendedData;
class BlockRecord;
class Block;
class BlockEnd;
class Layer;
class LineType;
class TextStyle;
class UCS;
class View;
class VPort;
class DimensionStyle;
class Arc;
class AttributeEntity;
class AttributeDefinition;
class AttributeBase;
class Circle;
class Dimension;
class DimensionLinear;
class DimensionAligned;
class DimensionRadius;
class DimensionAngular2Line;
class DimensionAngular3Pt;
class DimensionDiameter;
class DimensionOrdinate;
class Ellipse;
class Insert;
class Face3D;
class MLine;
class LwPolyline;
class Hatch;
class Leader;
class MultiLeader;
class MultiLeaderAnnotContext;
class LeaderRoot;
class LeaderLine;
class Line;
class Point;
class PolyfaceMesh;
class Polyline2D;
class Polyline3D;
class Seqend;
class Shape;
class Solid;
class Solid3D;
class CadWipeoutBase;
class Spline;
class Ray;
class TextEntity;
class MText;
class VertexFaceRecord;
class Vertex2D;
class Vertex;
class Tolerance;
class Viewport;
class XLine;
class AcdbPlaceHolder;
class BookColor;
class CadDictionaryWithDefault;
class Dictionary;
class DictionaryVariable;
class GeoData;
class Group;
class ImageDefinitionReactor;
class ImageDefinition;
class Layout;
class MLineStyle;
class MultiLeaderStyle;
class PlotSettings;
class Scale;
class SortEntitiesTable;
class XRecord;
class CadDictionary;

class DwgObjectWriter : public DwgSectionIO
{
public:
    DwgObjectWriter(std::ostream *stream, CadDocument *document, Encoding encoding, bool writeXRecords = true,
                    bool writeXData = true);
    ~DwgObjectWriter();
    std::string sectionName() const;
    void write();

    std::map<unsigned long long, long long> handleMap() const;
    bool writeXRecords() const;
    bool writeXData() const;

private:
    void registerObject(CadObject *cadObject);
    void writeSize(std::ostream stream, unsigned int size);
    void writeSizeInBits(std::ostream *stream, unsigned long long size);
    void writeXrefDependantBit(TableEntry *entry);
    void writeCommonData(CadObject *cadObject);
    void writeCommonNonEntityData(CadObject *cadObject);
    void writeCommonEntityData(Entity *entity);
    void writeEntityMode(Entity *entity);
    void writeExtendedData(ExtendedDataDictionary *data);
    void writeExtendedDataEntry(AppId *app, ExtendedData *entry);
    void writeReactorsAndDictionaryHandle(CadObject *cadObject);
    unsigned char getEntMode(Entity *entity);

private:
    void writeLTypeControlObject();
    void writeBlockControl();
    void writeTable();
    void writeEntries();
    void writeBlockEntities();
    void writeAppId(AppId *app);
    void writeBlockRecord(BlockRecord *blkRecord);
    void writeBlockHeader(BlockRecord *record);
    void writeBlockBegin(Block *block);
    void writeBlockEnd(BlockEnd *blkEnd);
    void writeLayer(Layer *layer);
    void writeLineType(LineType *ltype);
    void writeTextStyle(TextStyle *style);
    void writeUCS(UCS *ucs);
    void writeView(View *view);
    void writeDimensionStyle(DimensionStyle *dimStyle);
    void writeVPort(VPort *vport);

private:
    /*
 */
    void writeEntity(Entity *entity);
    void writeArc(Arc *arc);
    void writeAttribute(AttributeEntity *att);
    void writeAttDefinition(AttributeDefinition *attdef);
    void writeCommonAttData(AttributeBase *att);
    void writeCircle(Circle *circle);
    void writeCommonDimensionData(Dimension *dimension);
    void writeDimensionLinear(DimensionLinear *dimension);
    void writeDimensionAligned(DimensionAligned *dimension);
    void writeDimensionRadius(DimensionRadius *dimension);
    void writeDimensionAngular2Line(DimensionAngular2Line *dimension);
    void writeDimensionAngular3Pt(DimensionAngular3Pt *dimension);
    void writeDimensionDiameter(DimensionDiameter *dimension);
    void writeDimensionOrdinate(DimensionOrdinate *dimension);
    void writeEllipse(Ellipse *ellipse);
    void writeInsert(Insert *insert);
    void writeFace3D(Face3D *face);
    void writeMLine(MLine *mline);
    void writeLwPolyline(LwPolyline *lwPolyline);
    void writeHatch(Hatch *hatch);
    void writeLeader(Leader *leader);
    void writeMultiLeader(MultiLeader *multiLeader);
    void writeMultiLeaderAnnotContext(MultiLeaderAnnotContext *annotContext);
    void writeLine(Line *line);
    void writePoint(Point *point);
    void writePolyfaceMesh(PolyfaceMesh *fm);
    void writePolyline2D(Polyline2D *pline);
    void writePolyline3D(Polyline3D *pline);
    void writeSeqend(Seqend *seqend);
    void writeShape(Shape *shape);
    void writeSolid(Solid *solid);
    void writeSolid3D(Solid3D *solid);
    void writeCadImage(CadWipeoutBase *image);
    void writeSpline(Spline *spline);
    void writeRay(Ray *ray);
    void writeTextEntity(TextEntity *text);
    void writeMText(MText *mtext);
    void writeFaceRecord(VertexFaceRecord *face);
    void writeVertex2D(Vertex2D *vertex);
    void writeVertex(Vertex *vertex);
    void writeTolerance(Tolerance *tolerance);
    void writeViewport(Viewport *viewport);
    void writeXLine(XLine *xline);
    void writeChildEntities(const std::vector<Entity *> &entities, Seqend *seqend);

private:
    void writeObjects();
    void writeObject(CadObject *obj);
    void writeAcdbPlaceHolder(AcdbPlaceHolder *acdbPlaceHolder);
    void writeBookColor(BookColor *color);
    void writeCadDictionaryWithDefault(CadDictionaryWithDefault *dictionary);
    void writeDictionary(CadDictionary *dictionary);
    void addEntriesToWriter(CadDictionary *dictionary);
    void writeDictionaryVariable(DictionaryVariable *dictionaryVariable);
    void writeGeoData(GeoData *geodata);
    void writeGroup(Group *group);
    void writeImageDefinitionReactor(ImageDefinitionReactor *definitionReactor);
    void writeImageDefinition(ImageDefinition *definition);
    void writeLayout(Layout *layout);
    void writeMLineStyle(MLineStyle *mlineStyle);
    void writeMultiLeaderStyle(MultiLeaderStyle *mLeaderStyle);
    void writePlotSettings(PlotSettings *plot);
    void writeScale(Scale *scale);
    void writeSortEntitiesTable(SortEntitiesTable *sortEntitiesTable);
    void writeXRecord(XRecord *xrecord);

private:
    std::map<unsigned long long, CadDictionary *> _dictionaries;
    std::queue<CadObject *> _objects;
    std::ostringstream _msmain;
    IDwgStreamWriter *_writers;
    CadDocument *_document;
    Entity *_prev;
    Entity *_next;
    std::ostream *_stream;
};

}// namespace dwg
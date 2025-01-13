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

#include <dwg/io/dwg/DwgSectionIO.h>
#include <dwg/CadDocument.h>
#include <base.h>
#include <dwg/tables/TableEntry.h>
#include <map>

#include <dwg/io/dwg/fileheaders/DwgSectionDefinition.h>

namespace dwg {
namespace io {


class DwgObjectWriter : public DwgSectionIO
{
    std::map<unsigned long long, long long> _map;

public:
    DwgObjectWriter(std::ostream *stream, CadDocument *document,
                    Encoding encoding, bool writeXRecords = true)
        : DwgSectionIO(document->Header.Version)
    {
    }

    void Write();
    CPL::String SectionName() const override { return DwgSectionDefinition::AcDbObjects; }

private:
    void writeLTypeControlObject();
    void writeBlockControl();
    template<class T>
    void writeTable(tables::Table<T> table);
    template<class T>
    void writeEntries(tables::Table<T> table);

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
    void writeEntity(Entity *entity);
    void writeArc(Arc *arc);
    void writeAttribute(AttributeEntity att);
    void writeAttDefinition(AttributeDefinition attdef);
    void writeCommonAttData(AttributeBase att);
    void writeCircle(Circle circle);
    void writeCommonDimensionData(Dimension dimension);
    void writeDimensionLinear(DimensionLinear dimension);
    void writeDimensionAligned(DimensionAligned dimension);
    void writeDimensionRadius(DimensionRadius dimension);
    void writeDimensionAngular2Line(DimensionAngular2Line dimension);
    void writeDimensionAngular3Pt(DimensionAngular3Pt dimension);
    void writeDimensionDiameter(DimensionDiameter dimension);
    void writeDimensionOrdinate(DimensionOrdinate dimension);
    void writeEllipse(Ellipse ellipse);
    void writeInsert(Insert insert);
    void writeFace3D(Face3D face);
    void writeMLine(MLine mline);
    void writeLwPolyline(LwPolyline lwPolyline);
    void writeHatch(Hatch hatch);
    void writeLeader(Leader leader);
    void writeMultiLeader(MultiLeader multiLeader);
    void writeMultiLeaderAnnotContext(MultiLeaderAnnotContext annotContext);
    void writeLeaderRoot(MultiLeaderAnnotContext.LeaderRoot leaderRoot);
    void writeLeaderLine(MultiLeaderAnnotContext.LeaderLine leaderLine);
    void writeLine(Line line);
    void writePoint(Point point);
    void writePolyfaceMesh(PolyfaceMesh fm);
    void writePolyline2D(Polyline2D pline);
    void writePolyline3D(Polyline3D pline);
    void writeSeqend(Seqend seqend);
    void writeShape(Shape shape);
    void writeSolid(Solid solid);
    void writeSolid3D(Solid3D solid);
    void writeCadImage(CadImageBase image);
    void writeSpline(Spline spline);
    void writeRay(Ray ray);
    void writeTextEntity(TextEntity text);
    void writeMText(MText mtext);
    void writeFaceRecord(VertexFaceRecord face);
    void writeVertex2D(Vertex2D vertex);
    void writeVertex(Vertex vertex);
    void writeTolerance(Tolerance tolerance);
    void writeViewport(Viewport viewport);
    void writeXLine(XLine xline);
    void writeChildEntities(IEnumerable<Entity> entities, Seqend seqend);

    void writeObjects();
    void writeObject(CadObject obj);
    void writeAcdbPlaceHolder(AcdbPlaceHolder acdbPlaceHolder);
    void writeBookColor(BookColor color);
    void writeCadDictionaryWithDefault(CadDictionaryWithDefault dictionary);
    void writeDictionary(CadDictionary dictionary);
    void addEntriesToWriter(CadDictionary dictionary);
    void writeDictionaryVariable(DictionaryVariable dictionaryVariable);
    void writeGroup(Group group);
    void writeImageDefinitionReactor(ImageDefinitionReactor definitionReactor);
    void writeImageDefinition(ImageDefinition definition);
    void writeLayout(Layout layout);
    void writeMLineStyle(MLineStyle mlineStyle);
    void writeMultiLeaderStyle(MultiLeaderStyle mLeaderStyle);
    void writePlotSettings(PlotSettings plot);
    void writeScale(Scale scale);
    void writeSortEntitiesTable(SortEntitiesTable sortEntitiesTable);
    void writeXRecord(XRecord xrecord);
};

}// namespace io
}// namespace dwg
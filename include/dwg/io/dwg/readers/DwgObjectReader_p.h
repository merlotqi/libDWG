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

#include <dwg/ObjectType.h>
#include <dwg/io/dwg/DwgSectionIO_p.h>
#include <map>
#include <queue>
#include <vector>

namespace dwg {

class CadHeader;
class IDwgStreamReader;
class DwgHeaderHandlesCollection;
class DwgDocumentBuilder;
class DxfClassCollection;
class CadTemplate;
class CadEntityTemplate;
class ExtendedDataRecord;
class TableEntry;
class CadEvaluationExpressionTemplate;
class CadBlockElementTemplate;
class CadBlockParameterTemplate;
class CadBlock1PtParameterTemplate;
class DxfClass;
class CadTextEntityTemplate;
class CadAttributeTemplate;
class CadInsertTemplate;
class CadDimensionTemplate;
class CadDictionaryTemplate;
class CadMLeaderTemplate;
class MultiLeaderAnnotContext;
class MultiLeaderAnnotContextLeaderRoot;
class MultiLeaderAnnotContextLeaderLine;
class CadWipeoutBase;
class PlotSettings;
class Vertex;
class StateTemplate;

class DwgObjectReader : public DwgSectionIO
{
public:
    DwgObjectReader(ACadVersion version, DwgDocumentBuilder *builder, IDwgStreamReader *reader,
                    const std::queue<unsigned long long> &handles,
                    const std::map<unsigned long long, long long> &handleMap, DxfClassCollection *classes);

    ~DwgObjectReader();

    std::string sectionName() const override;

    void read();

private:
    ObjectType getEntityType(long long offset);

#pragma region Common entity data

    unsigned long long handleReference();
    unsigned long long handleReference(unsigned long long);
    void readCommonData(CadTemplate *temp);
    void readCommonEntityData(CadEntityTemplate *temp);
    void readEntityMode(CadEntityTemplate *temp);
    void readCommonNonEntityData(CadTemplate *temp);
    void readXrefDependantBit(TableEntry *entry);
    void readExtendedData(CadTemplate *temp);
    std::vector<ExtendedDataRecord *> readExtendedDataRecords(long long endPos);
    void readReactorsAndDictionaryHandle(CadTemplate *temp);
    void updateHandleReader();

#pragma endregion Common entity data

#pragma region Evaluation Graph, Enhanced Block etc.
    CadTemplate *readEvaluationGraph();
    void readEvaluationExpression(CadEvaluationExpressionTemplate *temp);
    void readBlockElement(CadBlockElementTemplate *temp);
    void readBlockParameter(CadBlockParameterTemplate *temp);
    void readBlock1PtParameter(CadBlock1PtParameterTemplate *temp);
    CadTemplate *readBlockVisibilityParameter();
    StateTemplate *readState();
#pragma endregion Evaluation Graph, Enhanced Block etc.

#pragma region Text entities
    CadTemplate *readUnknownEntity(DxfClass *dxfClass);
    CadTemplate *readUnknownNonGraphicalObject(DxfClass *dxfClass);
    CadTemplate *readText();
    CadTemplate *readAttribute();
    CadTemplate *readAttributeDefinition();
    void readCommonTextData(CadTextEntityTemplate *temp);
    void readCommonAttData(CadAttributeTemplate *temp);
#pragma endregion Text entities

#pragma region Insert methods
    CadTemplate *readInsert();
    CadTemplate *readMInsert();
    void readInsertCommonData(CadInsertTemplate *temp);
    void readInsertCommonHandles(CadInsertTemplate *temp);
#pragma endregion Insert methods

#pragma region Dimensions
    CadTemplate *readDimOrdinate();
    CadTemplate *readDimLinear();
    CadTemplate *readDimAligned();
    CadTemplate *readDimAngular3pt();
    CadTemplate *readDimLine2pt();
    CadTemplate *readDimRadius();
    CadTemplate *readDimDiameter();
    void readCommonDimensionData(CadDimensionTemplate *temp);
    void readCommonDimensionAlignedData(CadDimensionTemplate *temp);
#pragma endregion Dimensions

#pragma region Object readers
    CadTemplate *readObject(ObjectType type);
    CadTemplate *readUnlistedType(short classNumber);
    // CadTemplate *readDocumentTable<T>(Table<T> table);
    // CadTemplate *readDocumentTable<T>(CadTableTemplate<T> temp);
    CadTemplate *readBlock();
    CadTemplate *readEndBlock();
    CadTemplate *readSeqend();
    CadTemplate *readVertex2D();
    CadTemplate *readVertex3D(Vertex *vertex);
    CadTemplate *readPfaceVertex();
    CadTemplate *readPolyline2D();
    CadTemplate *readPolyline3D();
    CadTemplate *readArc();
    CadTemplate *readCircle();
    CadTemplate *readLine();
    CadTemplate *readPoint();
    CadTemplate *read3dFace();
    CadTemplate *readPolyfaceMesh();
    CadTemplate *readPolylineMesh();
    CadTemplate *readSolid();
    CadTemplate *readShape();
    CadTemplate *readViewport();
    CadTemplate *readEllipse();
    CadTemplate *readSpline();
    CadTemplate *readRay();
    CadTemplate *readXLine();
    CadTemplate *readDictionaryWithDefault();
    CadTemplate *readDictionary();
    void readCommonDictionary(CadDictionaryTemplate *temp);
    CadTemplate *readDictionaryVar();
    CadTemplate *readMText();
    CadTemplate *readMText(CadTextEntityTemplate *temp, bool readCommonData);
    CadTemplate *readLeader();
    CadTemplate *readMultiLeader();
    MultiLeaderAnnotContext *readMultiLeaderAnnotContext(MultiLeaderAnnotContext *annotContext,
                                                         CadMLeaderTemplate *temp);
    MultiLeaderAnnotContextLeaderRoot *readLeaderRoot(CadMLeaderTemplate *temp);
    MultiLeaderAnnotContextLeaderLine *readLeaderLine(CadMLeaderTemplate *temp);
    CadTemplate *readMultiLeaderStyle();
    CadTemplate *readTolerance();
    CadTemplate *readMLine();
    CadTemplate *readBlockControlObject();
    CadTemplate *readBlockHeader();
    CadTemplate *readLayer();
    CadTemplate *readTextStyle();
    CadTemplate *readLTypeControlObject();
    CadTemplate *readLType();
    CadTemplate *readView();
    CadTemplate *readUcs();
    CadTemplate *readVPort();
    CadTemplate *readAppId();
    CadTemplate *readDimStyle();
    CadTemplate *readViewportEntityControl();
    CadTemplate *readViewportEntityHeader();
    CadTemplate *readGeoData();
    CadTemplate *readGroup();
    CadTemplate *readMLineStyle();
    CadTemplate *readLWPolyline();
    CadTemplate *readHatch();
    CadTemplate *readSortentsTable();
    CadTemplate *readVisualStyle();
    CadTemplate *readCadImage(CadWipeoutBase *image);
    CadTemplate *readImageDefinition();
    CadTemplate *readImageDefinitionReactor();
    CadTemplate *readXRecord();
    CadTemplate *readMesh();
    CadTemplate *readPlaceHolder();
    CadTemplate *readPdfDefinition();
    CadTemplate *readPdfUnderlay();
    CadTemplate *readScale();
    CadTemplate *readLayout();
    void readPlotSettings(PlotSettings *plot);
#pragma endregion Object readers

    CadTemplate *readDbColor();

private:
    IDwgStreamReader *_sreader;
    CadHeader *_header;
};

}// namespace dwg
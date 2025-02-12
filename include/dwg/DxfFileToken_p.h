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

namespace dwg {

class DxfFileToken
{
public:
    static constexpr auto Undefined = "";
    static constexpr auto BeginSection = "SECTION";
    static constexpr auto EndSection = "ENDSEC";
    static constexpr auto EndSequence = "SEQEND";
    static constexpr auto EndOfFile = "EOF";
    static constexpr auto HeaderSection = "HEADER";
    static constexpr auto ClassesSection = "CLASSES";
    static constexpr auto ClassEntry = "CLASS";

    /// Object reactors, list of handles
    static constexpr auto ReactorsToken = "{ACAD_REACTORS";

    /// Handle for the xdictionary
    static constexpr auto DictionaryToken = "{ACAD_XDICTIONARY";

    /// Block references
    static constexpr auto BlkRefToken = "{BLKREFS";

    static constexpr auto TablesSection = "TABLES";
    static constexpr auto TableEntry = "TABLE";
    static constexpr auto EndTable = "ENDTAB";
    static constexpr auto TableAppId = "APPID";
    static constexpr auto TableBlockRecord = "BLOCK_RECORD";
    static constexpr auto TableDimstyle = "DIMSTYLE";
    static constexpr auto TableGroup = "GROUP";
    static constexpr auto TableLayer = "LAYER";
    static constexpr auto TableLinetype = "LTYPE";
    static constexpr auto TableStyle = "STYLE";
    static constexpr auto TableUcs = "UCS";
    static constexpr auto TableView = "VIEW";
    static constexpr auto TableVport = "VPORT";

    static constexpr auto BlocksSection = "BLOCKS";
    static constexpr auto Block = "BLOCK";
    static constexpr auto EndBlock = "ENDBLK";

    static constexpr auto EntitiesSection = "ENTITIES";
    static constexpr auto Entity3DFace = "3DFACE";
    static constexpr auto Entity3DSolid = "3DSOLID";
    static constexpr auto EntityProxyEntity = "ACAD_PROXY_ENTITY";
    static constexpr auto EntityArc = "ARC";
    static constexpr auto EntityAttributeDefinition = "ATTDEF";
    static constexpr auto EntityAttribute = "ATTRIB";
    static constexpr auto EntityBody = "BODY";
    static constexpr auto EntityCircle = "CIRCLE";
    static constexpr auto EntityCoordinationModel = "COORDINATION MODEL";
    static constexpr auto EntityDimension = "DIMENSION";
    static constexpr auto EntityEllipse = "ELLIPSE";
    static constexpr auto EntityHatch = "HATCH";
    static constexpr auto EntityHelix = "HELIX";
    static constexpr auto EntityImage = "IMAGE";
    static constexpr auto EntityInsert = "INSERT";
    static constexpr auto EntityLeader = "LEADER";
    static constexpr auto EntityLight = "LIGHT";
    static constexpr auto EntityLine = "LINE";
    static constexpr auto EntityLwPolyline = "LWPOLYLINE";
    static constexpr auto EntityMesh = "MESH";
    static constexpr auto EntityMultiLeader = "MULTILEADER";
    static constexpr auto EntityMLine = "MLINE";
    static constexpr auto EntityMText = "MTEXT";
    static constexpr auto EntityOleFrame = "OLEFRAME";
    static constexpr auto EntityOle2Frame = "OLE2FRAME";
    static constexpr auto EntityPdfUnderlay = "PDFUNDERLAY";
    static constexpr auto EntityPoint = "POINT";
    static constexpr auto EntityPolyline = "POLYLINE";
    static constexpr auto EntityPolyFaceMesh = "PFACE";
    static constexpr auto EntityRay = "RAY";
    static constexpr auto EntityRegion = "REGION";
    static constexpr auto EntitySection = "SECTION";
    static constexpr auto EntitySeqend = "SEQEND";
    static constexpr auto EntityShape = "SHAPE";
    static constexpr auto EntitySolid = "SOLID";
    static constexpr auto EntitySpline = "SPLINE";
    static constexpr auto EntitySun = "SUN";
    static constexpr auto EntitySurface = "SURFACE";
    static constexpr auto EntityTable = "TABLE";
    static constexpr auto EntityText = "TEXT";
    static constexpr auto EntityTolerance = "TOLERANCE";
    static constexpr auto EntityTrace = "TRACE";
    static constexpr auto EntityUnderlay = "UNDERLAY";
    static constexpr auto EntityVertex = "VERTEX";
    static constexpr auto EntityViewport = "VIEWPORT";
    static constexpr auto EntityWipeout = "WIPEOUT";
    static constexpr auto EntityXline = "XLINE";

    static constexpr auto ObjectsSection = "OBJECTS";
    static constexpr auto ObjectDictionary = "DICTIONARY";
    static constexpr auto ObjectDictionaryWithDefault = "ACDBDICTIONARYWDFLT";
    static constexpr auto ObjectAcdbPlaceHolder = "ACDBPLACEHOLDER";
    static constexpr auto ObjectDictionaryVar = "DICTIONARYVAR";
    static constexpr auto ObjectDBColor = "DBCOLOR";
    static constexpr auto ObjectPlotSettings = "PLOTSETTINGS";
    static constexpr auto ObjectPlaceholder = "ACDBPLACEHOLDER";
    static constexpr auto ObjectLayout = "LAYOUT";
    static constexpr auto ObjectMLeaderStyle = "MLEADERSTYLE";
    static constexpr auto ObjectImageDefinition = "IMAGEDEF";
    static constexpr auto ObjectImageDefinitionReactor = "IMAGEDEF_REACTOR";
    static constexpr auto ObjectMaterial = "MATERIAL";
    static constexpr auto ObjectMLineStyle = "MLINESTYLE";
    static constexpr auto ObjectPdfDefinition = "PDFDEFINITION";
    static constexpr auto ObjectVisualStyle = "VISUALSTYLE";
    static constexpr auto ObjectScale = "SCALE";
    static constexpr auto ObjectSortEntsTable = "SORTENTSTABLE";
    static constexpr auto ObjectXRecord = "XRECORD";
    static constexpr auto ObjectMLeaderContextData = "CONTEXT_DATA";
    static constexpr auto ObjectEvalGraph = "ACAD_EVALUATION_GRAPH";
    static constexpr auto ObjectBlockVisibilityParameter = "BLOCKVISIBILITYPARAMETER";
};

}// namespace dwg

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

class DxfSubclassMarker
{
    static constexpr auto ApplicationId = "AcDbRegAppTableRecord";
    static constexpr auto AcDbPlaceHolder = "AcDbPlaceHolder";
    static constexpr auto Table = "AcDbSymbolTable";
    static constexpr auto TableRecord = "AcDbSymbolTableRecord";
    static constexpr auto Layer = "AcDbLayerTableRecord";
    static constexpr auto VPort = "AcDbViewportTableRecord";
    static constexpr auto View = "AcDbViewTableRecord";
    static constexpr auto Linetype = "AcDbLinetypeTableRecord";
    static constexpr auto TextStyle = "AcDbTextStyleTableRecord";
    static constexpr auto MLineStyle = "AcDbMlineStyle";
    static constexpr auto DimensionStyleTable = "AcDbDimStyleTable";
    static constexpr auto DimensionStyle = "AcDbDimStyleTableRecord";
    static constexpr auto Ucs = "AcDbUCSTableRecord";
    static constexpr auto Dimension = "AcDbDimension";
    static constexpr auto AlignedDimension = "AcDbAlignedDimension";
    static constexpr auto LinearDimension = "AcDbRotatedDimension";
    static constexpr auto RadialDimension = "AcDbRadialDimension";
    static constexpr auto DiametricDimension = "AcDbDiametricDimension";
    static constexpr auto Angular3PointDimension = "AcDb3PointAngularDimension";
    static constexpr auto Angular2LineDimension = "AcDb2LineAngularDimension";
    static constexpr auto OrdinateDimension = "AcDbOrdinateDimension";
    static constexpr auto BlockRecord = "AcDbBlockTableRecord";
    static constexpr auto BlockBegin = "AcDbBlockBegin";
    static constexpr auto BlockEnd = "AcDbBlockEnd";
    static constexpr auto Entity = "AcDbEntity";
    static constexpr auto Arc = "AcDbArc";
    static constexpr auto Circle = "AcDbCircle";
    static constexpr auto Ellipse = "AcDbEllipse";
    static constexpr auto Spline = "AcDbSpline";
    static constexpr auto Face3d = "AcDbFace";
    static constexpr auto Helix = "AcDbHelix";
    static constexpr auto Insert = "AcDbBlockReference";
    static constexpr auto Line = "AcDbLine";
    static constexpr auto Ray = "AcDbRay";
    static constexpr auto XLine = "AcDbXline";
    static constexpr auto MLine = "AcDbMline";
    static constexpr auto ModelerGeometry = "AcDbModelerGeometry";
    static constexpr auto Point = "AcDbPoint";
    static constexpr auto Vertex = "AcDbVertex";
    static constexpr auto Polyline = "AcDb2dPolyline";
    static constexpr auto Leader = "AcDbLeader";
    static constexpr auto Material = "AcDbMaterial";
    static constexpr auto MultiLeader = "AcDbMLeader";
    static constexpr auto MLeaderStyle = "AcDbMLeaderStyle";
    static constexpr auto MultiLeaderAnnotContext =
            "AcDbMultiLeaderAnnotContext";
    static constexpr auto LwPolyline = "AcDbPolyline";
    static constexpr auto PolylineVertex = "AcDb2dVertex";
    static constexpr auto Polyline3d = "AcDb3dPolyline";
    static constexpr auto Polyline3dVertex = "AcDb3dPolylineVertex";
    static constexpr auto PolyfaceMesh = "AcDbPolyFaceMesh";
    static constexpr auto PolyfaceMeshVertex = "AcDbPolyFaceMeshVertex";
    static constexpr auto PolyfaceMeshFace = "AcDbFaceRecord";
    static constexpr auto Shape = "AcDbShape";
    static constexpr auto Solid = "AcDbTrace";
    static constexpr auto Trace = "AcDbTrace";
    static constexpr auto Text = "AcDbText";
    static constexpr auto Tolerance = "AcDbFcf";
    static constexpr auto Wipeout = "AcDbWipeout";
    static constexpr auto Mesh = "AcDbSubDMesh";
    static constexpr auto MText = "AcDbMText";
    static constexpr auto Hatch = "AcDbHatch";
    static constexpr auto Underlay = "AcDbUnderlayReference";
    static constexpr auto UnderlayDefinition = "AcDbUnderlayDefinition";
    static constexpr auto Viewport = "AcDbViewport";
    static constexpr auto Attribute = "AcDbAttribute";
    static constexpr auto AttributeDefinition = "AcDbAttributeDefinition";
    static constexpr auto Dictionary = "AcDbDictionary";
    static constexpr auto DictionaryWithDefault = "AcDbDictionaryWithDefault";
    static constexpr auto VisualStyle = "AcDbVisualStyle";
    static constexpr auto XRecord = "AcDbXrecord";
    static constexpr auto RasterImage = "AcDbRasterImage";
    static constexpr auto RasterImageDef = "AcDbRasterImageDef";
    static constexpr auto RasterImageDefReactor = "AcDbRasterImageDefReactor";
    static constexpr auto RasterVariables = "AcDbRasterVariables";
    static constexpr auto SortentsTable = "AcDbSortentsTable";
    static constexpr auto Group = "AcDbGroup";
    static constexpr auto Layout = "AcDbLayout";
    static constexpr auto PlotSettings = "AcDbPlotSettings";
    static constexpr auto DictionaryVariables = "DictionaryVariables";
    static constexpr auto Scale = "AcDbScale";
    static constexpr auto EvalGraph = "AcDbEvalGraph";
    static constexpr auto BlockVisibilityParameter =
            "AcDbBlockVisibilityParameter";
    static constexpr auto DbColor = "AcDbColor";
};

}// namespace dwg
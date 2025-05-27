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

void DwgObjectWriter::writeObjects() {}

void DwgObjectWriter::writeObject(CadObject *obj) {}

void DwgObjectWriter::writeAcdbPlaceHolder(AcdbPlaceHolder *acdbPlaceHolder) {}

void DwgObjectWriter::writeBookColor(BookColor *color) {}

void DwgObjectWriter::writeCadDictionaryWithDefault(CadDictionaryWithDefault *dictionary) {}

void DwgObjectWriter::writeDictionary(CadDictionary *dictionary) {}

void DwgObjectWriter::addEntriesToWriter(CadDictionary *dictionary) {}

void DwgObjectWriter::writeDictionaryVariable(DictionaryVariable *dictionaryVariable) {}

void DwgObjectWriter::writeGeoData(GeoData *geodata) {}

void DwgObjectWriter::writeGroup(Group *group) {}

void DwgObjectWriter::writeImageDefinitionReactor(ImageDefinitionReactor *definitionReactor) {}

void DwgObjectWriter::writeImageDefinition(ImageDefinition *definition) {}

void DwgObjectWriter::writeLayout(Layout *layout) {}

void DwgObjectWriter::writeMLineStyle(MLineStyle *mlineStyle) {}

void DwgObjectWriter::writeMultiLeaderStyle(MultiLeaderStyle *mLeaderStyle) {}

void DwgObjectWriter::writePlotSettings(PlotSettings *plot) {}

void DwgObjectWriter::writeScale(Scale *scale) {}

void DwgObjectWriter::writeSortEntitiesTable(SortEntitiesTable *sortEntitiesTable) {}

void DwgObjectWriter::writeXRecord(XRecord *xrecord) {}

}// namespace dwg
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
#include <dwg/io/dwg/writers/DwgObjectWriter_p.h>
#include <dwg/table/Layer.h>
#include <dwg/table/AppId.h>

namespace dwg {

DwgObjectWriter::DwgObjectWriter(std::ostream *stream, CadDocument *document, Encoding encoding, bool writeXRecords,
                                 bool writeXData)
    : DwgSectionIO(document->header()->version())
{
}
DwgObjectWriter::~DwgObjectWriter() {}

std::string DwgObjectWriter::sectionName() const
{
    return std::string();
}

void DwgObjectWriter::write() {}

std::map<unsigned long long, long long> DwgObjectWriter::handleMap() const
{
    return std::map<unsigned long long, long long>();
}

bool DwgObjectWriter::writeXRecords() const
{
    return false;
}

bool DwgObjectWriter::writeXData() const
{
    return false;
}

void DwgObjectWriter::writeLTypeControlObject() {}

void DwgObjectWriter::writeBlockControl() {}

void DwgObjectWriter::writeTable() {}

void DwgObjectWriter::writeEntries() {}

void DwgObjectWriter::writeBlockEntities() {}

void DwgObjectWriter::writeAppId(AppId *app) 
{
    writeCommonNonEntityData(app);

    //Common:
    //Entry name TV 2
    _writer->writeVariableText(app->name());

    writeXrefDependantBit(app);

    //Unknown RC 71 Undoc'd 71-group; doesn't even appear in DXF or an entget if it's 0.
    _writer->writeByte(0);

	//External reference block handle(hard pointer)	??
	_writer->handleReference(DwgReferenceType::HardPointer, 0);

	registerObject(app);
}

void DwgObjectWriter::writeBlockRecord(BlockRecord *blkRecord) 
{
    writeBlockHeader(blkRecord);
}

void DwgObjectWriter::writeBlockHeader(BlockRecord *record) 
{
    writeCommonNonEntityData(record);

    //Common:
    // Entry name TV 2
    if(record->flags().testFlag(Block))
}

void DwgObjectWriter::writeBlockBegin(Block *block) {}

void DwgObjectWriter::writeBlockEnd(BlockEnd *blkEnd) {}

void DwgObjectWriter::writeLayer(Layer *layer) 
{
			writeCommonNonEntityData(layer);

			//Common:
			//Entry name TV 2
			_writer->writeVariableText(layer->name());

			writeXrefDependantBit(layer);

			//R13-R14 Only:
			if (R13_14Only)
			{
				//Frozen B 70 if frozen (1 bit)
				_writer->writeBit(layer->flags().testFlag(LayerFlags::Frozen));
				//On B if on.
				_writer->writeBit(layer->isOn());
				//Frz in new B 70 if frozen by default in new viewports (2 bit)
				_writer->writeBit(layer->flags().testFlag(LayerFlags::FrozenNewViewports));
				//Locked B 70 if locked (4 bit)
				_writer->writeBit(layer->flags().testFlag(LayerFlags::Locked));
			}

			//R2000+:
			if (R2000Plus)
			{
				//and lineweight (mask with 0x03E0)
				short values = (short)(CadUtils.toIndex(layer->LineWeight) << 5);

				//contains frozen (1 bit),
				if (layer->flags().testFlag(LayerFlags::Frozen))
					values |= 0b1;

				//on (2 bit)
				if (!layer->IsOn)
					values |= 0b10;

				//frozen by default in new viewports (4 bit)
				if (layer->flags().HasFlag(LayerFlags::Frozen))
					values |= 0b100;

				//locked (8 bit)
				if (layer->flags().HasFlag(LayerFlags::Locked))
					values |= 0b1000;

				//plotting flag (16 bit),
				if (layer->plotFlag())
					values |= 0b10000;

				//Values BS 70,290,370
				_writer->writeBitShort(values);
			}

			//Common:
			//Color CMC 62
			_writer->writeCmColor(layer->color());

			//External reference block handle(hard pointer)
			_writer->handleReference(DwgReferenceType::HardPointer, nullptr);

			//R2000+:
			if (R2000Plus)
			{
				//H 390 Plotstyle (hard pointer), by default points to PLACEHOLDER with handle 0x0f.
				_writer->handleReference(DwgReferenceType::HardPointer, 0);
			}

			//R2007+:
			if (R2007Plus)
			{
				//H 347 Material
				_writer->handleReference(DwgReferenceType::HardPointer, 0);
			}

			//Common:
			//H 6 linetype (hard pointer)
			_writer->handleReference(DwgReferenceType::HardPointer, layer->lineType()->handle());

			if (R2013Plus)
			{
				//H Unknown handle (hard pointer). Always seems to be NULL.
				_writer->handleReference(DwgReferenceType::HardPointer, 0);
			}

			registerObject(layer);
}

void DwgObjectWriter::writeLineType(LineType *ltype) {}

void DwgObjectWriter::writeTextStyle(TextStyle *style) {}

void DwgObjectWriter::writeUCS(UCS *ucs) {}

void DwgObjectWriter::writeView(View *view) {}

void DwgObjectWriter::writeDimensionStyle(DimensionStyle *dimStyle) {}

void DwgObjectWriter::writeVPort(VPort *vport) {}

}// namespace dwg
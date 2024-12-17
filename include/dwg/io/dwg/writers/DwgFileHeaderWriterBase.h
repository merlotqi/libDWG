/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General  License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General  License for more details.
 *
 * You should have received a copy of the GNU General  License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#pragma once

#include <dwg/io/dwg/IDwgFileHeaderWriter.h>

namespace dwg {
namespace io {

class DwgFileHeaderWriterBase : public IDwgFileHeaderWriter
{
		abstract int HandleSectionOffset { get; }

		 abstract int _fileHeaderSize { get; }

		 DwgFileHeader _fileHeader { get; }

		 ACadVersion _version;

		 Encoding _encoding;

		 Stream _stream;

		 CadDocument _document;

		 DwgFileHeaderWriterBase(Stream stream, Encoding encoding, CadDocument model)
		{
			if (!stream.CanSeek || !stream.CanWrite)
			{
				throw new ArgumentException();
			}

			this._document = model;
			this._stream = stream;
			this._version = model.Header.Version;
			this._encoding = encoding;
		}

		 abstract void AddSection(string name, MemoryStream stream, bool isCompressed, int decompsize = 0x7400);

		 abstract void WriteFile();

		 ushort getFileCodePage()
		{
			ushort codePage = (ushort)CadUtils.GetCodeIndex(CadUtils.GetCodePage(_document.Header.CodePage));
			if (codePage < 1)
			{
				return 30;
			}
			else
			{
				return codePage;
			}
		}

		 void applyMask(byte[] buffer, int offset, int length)
		{
			byte[] bytes = LittleEndianConverter.Instance.GetBytes(0x4164536B ^ (int)this._stream.Position);
			int diff = offset + length;
			while (offset < diff)
			{
				for (int i = 0; i < 4; i++)
				{
					buffer[offset + i] ^= bytes[i];
				}

				offset += 4;
			}
		}

		 bool checkEmptyBytes(byte[] buffer, ulong offset, ulong spearBytes)
		{
			bool result = true;
			ulong num = offset + spearBytes;

			for (ulong i = offset; i < num; i++)
			{
				if (buffer[i] != 0)
				{
					result = false;
					break;
				}
			}

			return result;
		}

		 void writeMagicNumber()
		{
			for (int i = 0; i < (int)(this._stream.Position % 0x20); i++)
			{
				this._stream.WriteByte(DwgCheckSumCalculator.MagicSequence[i]);
			}
		}

		 void applyMagicSequence(MemoryStream stream)
		{
			byte[] buffer = stream.GetBuffer();
			for (int i = 0; i < (int)stream.Length; i++)
			{
				buffer[i] ^= DwgCheckSumCalculator.MagicSequence[i];
			}
		}
};

}
}
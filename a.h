#pragma region Read the data section map
    //Set the positon of the map
    sreader.Position = fileheader.Records[(int) fileheader.SectionMapId].Seeker;
    //Get the page size
    this.getPageHeaderData(sreader, out _, out decompressedSize, out _, out _, out _);
    StreamIO decompressedStream = new StreamIO(DwgLZ77AC18Decompressor.Decompress(sreader.Stream, decompressedSize));
    decompressedStream.Encoding = TextEncoding.GetListedEncoding(CodePage.Windows1252);

    //0x00	4	Number of section descriptions(NumDescriptions)
    int ndescriptions = decompressedStream.ReadInt<LittleEndianConverter>();
    //0x04	4	0x02 (long)
    decompressedStream.ReadInt<LittleEndianConverter>();
    //0x08	4	0x00007400 (long)
    decompressedStream.ReadInt<LittleEndianConverter>();
    //0x0C	4	0x00 (long)
    decompressedStream.ReadInt<LittleEndianConverter>();
    //0x10	4	Unknown (long), ODA writes NumDescriptions here.
    decompressedStream.ReadInt<LittleEndianConverter>();

    for (int i = 0; i < ndescriptions; ++i)
    {
        DwgSectionDescriptor descriptor = new DwgSectionDescriptor();
        //0x00	8	Size of section(OdUInt64)
        descriptor.CompressedSize = decompressedStream.ReadULong();
        /*0x08	4	Page count(PageCount). Note that there can be more pages than PageCount,
							as PageCount is just the number of pages written to file.
							If a page contains zeroes only, that page is not written to file.
							These “zero pages” can be detected by checking if the page’s start 
							offset is bigger than it should be based on the sum of previously read pages 
							decompressed size(including zero pages).After reading all pages, if the total 
							decompressed size of the pages is not equal to the section’s size, add more zero 
							pages to the section until this condition is met.
				*/
        descriptor.PageCount = decompressedStream.ReadInt<LittleEndianConverter>();
        //0x0C	4	Max Decompressed Size of a section page of this type(normally 0x7400)
        descriptor.DecompressedSize = (ulong) decompressedStream.ReadInt<LittleEndianConverter>();
        //0x10	4	Unknown(long)
        decompressedStream.ReadInt<LittleEndianConverter>();
        //0x14	4	Compressed(1 = no, 2 = yes, normally 2)
        descriptor.CompressedCode = decompressedStream.ReadInt<LittleEndianConverter>();
        //0x18	4	Section Id(starts at 0). The first section(empty section) is numbered 0, consecutive sections are numbered descending from(the number of sections – 1) down to 1.
        descriptor.SectionId = decompressedStream.ReadInt<LittleEndianConverter>();
        //0x1C	4	Encrypted(0 = no, 1 = yes, 2 = unknown)
        descriptor.Encrypted = decompressedStream.ReadInt<LittleEndianConverter>();
        //0x20	64	Section Name(string)
        descriptor.Name = decompressedStream.ReadString(64).Split('\0')[0];

        //Following this, the following (local) section page map data will be present
        for (int j = 0; j < descriptor.PageCount; ++j)
        {
            DwgLocalSectionMap localmap = new DwgLocalSectionMap();
            //0x00	4	Page number(index into SectionPageMap), starts at 1
            localmap.PageNumber = decompressedStream.ReadInt<LittleEndianConverter>();
            //0x04	4	Data size for this page(compressed size).
            localmap.CompressedSize = (ulong) decompressedStream.ReadInt<LittleEndianConverter>();
            //0x08	8	Start offset for this page(OdUInt64).If this start offset is smaller than the sum of the decompressed size of all previous pages, then this page is to be preceded by zero pages until this condition is met.
            localmap.Offset = decompressedStream.ReadULong();

            //same decompressed size and seeker (temporal values)
            localmap.DecompressedSize = descriptor.DecompressedSize;
            localmap.Seeker = fileheader.Records[localmap.PageNumber].Seeker;

            //Maximum section page size appears to be 0x7400 bytes in the normal case.
            //If a logical section of the file (the database objects, for example) exceeds this size, then it is broken up into pages of size 0x7400.

            descriptor.LocalSections.Add(localmap);
        }

        //Get the final size for the local section
        uint sizeLeft = (uint) (descriptor.CompressedSize % descriptor.DecompressedSize);
        if (sizeLeft > 0U && descriptor.LocalSections.Count > 0)
            descriptor.LocalSections[descriptor.LocalSections.Count - 1].DecompressedSize = sizeLeft;

        fileheader.Descriptors.Add(descriptor.Name, descriptor);
    }
#pragma endregion
/**
@mainpage libDWG Documentation

@section intro Introduction

libDWG is a modern C++ library for reading and writing DWG and DXF CAD files, providing comprehensive support for AutoCAD file formats.

@section features Features

- Read and write DWG files (AutoCAD native format)
- Read and write DXF files (AutoCAD exchange format)
- Support for various AutoCAD versions
- Cross-platform compatibility (Windows, Linux, macOS)
- Modern C++17 API
- Comprehensive documentation
- Permissive MIT license

@section getting_started Getting Started

To use libDWG in your project, follow these steps:

1. Include the necessary headers:
   @code{.cpp}
   #include <dwg/CadDocument.h>
   #include <dwg/io/DxfReader.h>
   @endcode

2. Read a DWG or DXF file:
   @code{.cpp}
   dwg::CadDocument doc;
   dwg::io::DxfReader reader("example.dxf");
   reader.Read(doc);
   @endcode

3. Access document data:
   @code{.cpp}
   // Get all entities in the model space
   auto entities = doc.modelSpaceEntities();
   
   // Iterate through entities
   for (const auto& entity : entities) {
       // Process entity
   }
   @endcode

@section examples Examples

See the examples directory for more detailed usage examples.

@section license License

libDWG is released under the MIT license. See the LICENSE.txt file for details.
*/
*/

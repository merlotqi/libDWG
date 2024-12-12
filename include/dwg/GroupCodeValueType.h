#ifndef GROUPCODEVALUETYPE_H
#define GROUPCODEVALUETYPE_H

namespace dwg {

enum GroupCodeValueType {
    None,

    /// \brief String
    /// \remarks Code range : 0-9
    String,

    /// \brief Double precision 3D point value
    /// \remarks Code range : 10-39
    Point3D,

    /// \brief Double-precision floating-point value
    /// \remarks Code range : 40-59 | 110-119 | 120-129 | 130-139 | 210-239
    Double,
    Byte,
    Int16,
    Int32,
    Int64,

    /// \brief String representing hexadecimal (hex) handle value
    /// \remarks Code range : 105
    Handle,
    ObjectId,
    Bool,
    Chunk,

    /// \brief Comment (string)
    /// \remarks Code range : 999
    Comment,

    ExtendedDataString,
    ExtendedDataChunk,
    ExtendedDataHandle,
    ExtendedDataDouble,
    ExtendedDataInt16,
    ExtendedDataInt32,
};

} // namespace dwg

#endif /* GROUPCODEVALUETYPE_H */
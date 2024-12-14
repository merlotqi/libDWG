#ifndef DXF_REFERENCE_TYPE_H
#define DXF_REFERENCE_TYPE_H

namespace dwg {

enum DxfReferenceType : unsigned char {
    
    /// No reference, the value is a primitive

    None = 0,

    
    /// Handle reference, the value is a handle pointing to an object

    Handle = 1,

    
    /// Name reference, the value is a name pointing to an object

    Name = 2,

    
    /// Counter reference, the value is a list with multiple elements referenced
    /// to it

    Count = 4,

    
    /// Optional value

    Optional = 8,

    
    /// Value will be ignored by the reader and writer

    Ignored = 16,

    
    /// Value is an angle and must be converted when convinient

    IsAngle = 32,

    Unprocess = 64
};

} // namespace dwg

#endif /* DXF_REFERENCE_TYPE_H */
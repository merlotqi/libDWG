#ifndef DWG_REFERENCE_TYPE_H
#define DWG_REFERENCE_TYPE_H

namespace dwg {

enum DwgReferenceType {
    Undefined = 0,

    /// Soft ownership reference: the owner does not need the owned object. The
    /// owned object cannot exist by itself.
    SoftOwnership = 2,

    /// Hard ownership reference: the owner needs the owned object. The owned
    /// object cannot exist by itself.
    HardOwnership = 3,

    /// Soft pointer reference: the referencing object does not need the
    /// referenced object and vice versa.
    SoftPointer = 4,

    /// Hard pointer reference: the referencing object needs the referenced
    /// object, but both are owned by another object.
    HardPointer = 5,
};

} // namespace dwg

#endif /* DWG_REFERENCE_TYPE_H */
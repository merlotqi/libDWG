#ifndef DWG_REFERENCE_TYPE_H
#define DWG_REFERENCE_TYPE_H

namespace DWG
{
namespace Common
{

enum DwgReferenceType
{
  Undefined = 0,

  /// <summary>
  /// Soft ownership reference: the owner does not need the owned object. The
  /// owned object cannot exist by itself.
  /// </summary>
  SoftOwnership = 2,

  /// <summary>
  /// Hard ownership reference: the owner needs the owned object. The owned
  /// object cannot exist by itself.
  /// </summary>
  HardOwnership = 3,

  /// <summary>
  /// Soft pointer reference: the referencing object does not need the
  /// referenced object and vice versa.
  /// </summary>
  SoftPointer = 4,

  /// <summary>
  /// Hard pointer reference: the referencing object needs the referenced
  /// object, but both are owned by another object.
  /// </summary>
  HardPointer = 5,
};

} // namespace Common
} // namespace DWG

#endif /* DWG_REFERENCE_TYPE_H */


namespace dwg {
namespace Tables {

/// Standard flags for tables
public
enum StandardFlags : short {
    /// <summary>
    /// None
    /// </summary>
    None = 0,

    /// <summary>
    /// If set, table entry is externally dependent on an xRef
    /// </summary>
    XrefDependent = 16,

    /// <summary>
    /// If both this bit and bit 16 are set, the externally dependent xRef has
    /// been successfully resolved
    /// </summary>
    XrefResolved = 32,

    /// <summary>
    /// If set, the table entry was referenced by at least one entity in the
    /// drawing the last time the drawing was edited.
    /// </summary>
    Referenced = 64,
};

} // namespace Tables
} // namespace dwg
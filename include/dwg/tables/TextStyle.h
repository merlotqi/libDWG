

namespace dwg {
namespace Tables {

/// Represent the font character formatting, such as italic, bold, or regular.
public
enum FontFlags {
    /// <summary>
    /// Regular.
    /// </summary>
    Regular = 0,
    /// <summary>
    /// Italic or oblique.
    /// </summary>
    Italic = 1,
    /// <summary>
    /// Bold.
    /// </summary>
    Bold = 2
};

/// <summary>
/// Standard layer flags (bit-coded values).
/// </summary>
enum StyleFlags {
    /// <summary>
    /// Default
    /// </summary>
    None = 0,

    /// <summary>
    /// If set, this entry describes a shape
    /// </summary>
    IsShape = 1,

    /// <summary>
    /// Vertical text
    /// </summary>
    VerticalText = 4,

    /// <summary>
    /// If set, table entry is externally dependent on an xRef.
    /// </summary>
    XrefDependent = 16,

    /// <summary>
    /// If both this bit and bit 16 are set, the externally dependent xRef has
    /// been successfully resolved.
    /// </summary>
    XrefResolved = 32,

    /// <summary>
    /// If set, the table entry was referenced by at least one entity in the
    /// drawing the last time the drawing was edited.
    /// </summary>
    Referenced = 64
};

} // namespace Tables
} // namespace dwg
namespace dwg {
namespace Entities {
enum AttributeFlags {
    /// <summary>
    /// No flags.
    /// </summary>
    None = 0,
    /// <summary>
    /// Attribute is invisible (does not appear).
    /// </summary>
    Hidden = 1,
    /// <summary>
    /// This is a constant attribute.
    /// </summary>
    Constant = 2,
    /// <summary>
    /// Verification is required on input of this attribute.
    /// </summary>
    Verify = 4,
    /// <summary>
    /// Attribute is preset (no prompt during insertion).
    /// </summary>
    Preset = 8
};

}
} // namespace dwg
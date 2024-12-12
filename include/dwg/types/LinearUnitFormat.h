#ifndef LINEAR_UNIT_FORMAT_H
#define LINEAR_UNIT_FORMAT_H

namespace dwg {
namespace Type {

/// <summary>
/// Units format for decimal numbers
/// </summary>
enum LinearUnitFormat : short {
    /// <summary>
    /// None
    /// </summary>
    None = 0,
    /// <summary>
    /// Scientific
    /// </summary>
    Scientific = 1,
    /// <summary>
    /// Decimal
    /// </summary>
    Decimal = 2,
    /// <summary>
    /// Engineering
    /// </summary>
    Engineering = 3,
    /// <summary>
    /// Architectural
    /// </summary>
    Architectural = 4,
    /// <summary>
    /// Fractional
    /// </summary>
    Fractional = 5,
    /// <summary>
    /// Windows desktop
    /// </summary>
    WindowsDesktop = 6,
};

} // namespace Type

} // namespace dwg

#endif
#ifndef ANGULARDIRECTION_H
#define ANGULARDIRECTION_H

namespace dwg {
namespace Type {

/// <summary>
/// Represents angular direction.
/// </summary>
enum AngularDirection : short {
    /// <summary>
    /// Counterclockwise angles
    /// </summary>
    CounterClockWise = 0,
    /// <summary>
    /// Clockwise angles
    /// </summary>
    ClockWise = 1,
};

} // namespace Type
} // namespace dwg

#endif
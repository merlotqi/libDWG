namespace dwg {
namespace Entities {

/// Controls the way the leader is drawn.
/// </summary>
enum LeaderPathType {
    /// <summary>
    /// Draws the leader line as a set of straight line segments
    /// </summary>
    StraightLineSegments = 0,

    /// <summary>
    /// Draws the leader line as a spline
    /// </summary>
    Spline = 1
};

/// Leader creation type
/// </summary>
enum LeaderCreationType : short {
    /// <summary>
    /// Created with text annotation
    /// </summary>
    CreatedWithTextAnnotation = 0,

    /// <summary>
    /// Created with tolerance annotation
    /// </summary>
    CreatedWithToleranceAnnotation = 1,

    /// <summary>
    /// Created with block reference annotation
    /// </summary>
    CreatedWithBlockReferenceAnnotation = 2,

    /// <summary>
    /// Created without any annotation
    /// </summary>
    CreatedWithoutAnnotation = 3
};

class Leader {};

} // namespace Entities
} // namespace dwg
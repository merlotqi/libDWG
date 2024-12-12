

namespace dwg {
namespace Entities {

/// Hatch pattern style.
/// </summary>
enum HatchStyleType {
    /// <summary>
    /// Hatch "odd parity" area.
    /// </summary>
    Normal = 0,
    /// <summary>
    /// Hatch outermost area only.
    /// </summary>
    Outer = 1,
    /// <summary>
    /// Hatch through entire area.
    /// </summary>
    Ignore = 2
};

/// Hatch pattern fill type.
/// </summary>
enum HatchPatternType {
    /// <summary>
    /// Pattern fill.
    /// </summary>
    PatternFill = 0,
    /// <summary>
    /// Solid fill.
    /// </summary>
    SolidFill = 1,
    /// <summary>
    /// Custom hatch pattern from a pattern file.
    /// </summary>
    Custom = 2,
};

struct GradientColor {
    double value;
    Color color;
};

class Hatch {
public:
    class Edge {
        enum EdgeType {
            Polyline,
            Line,
            CircularArc,
            EllipticArc,
            Spline,
        };
    };
};

} // namespace Entities
} // namespace dwg
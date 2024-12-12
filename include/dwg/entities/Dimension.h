
namespace dwg {
namespace Entities {

enum DimensionType {
    /// Rotated, horizontal, or vertical
    Linear = 0,

    /// Aligned
    Aligned = 1,

    /// Angular 2 lines
    Angular = 2,

    /// Diameter
    Diameter = 3,

    /// Radius
    Radius = 4,

    /// Angular 3 points
    Angular3Point = 5,

    /// Ordinate
    Ordinate = 6,

    /// Indicates that the block reference(group code 2) is referenced by this
    /// dimension only
    BlockReference = 32,

    /// Ordinate type. If set, ordinate is X-type; if not set, ordinate is
    /// Y-type
    OrdinateTypeX = 64,

    /// Indicates if the dimension text has been positioned at a user-defined
    /// location rather than at the default location
    TextUserDefinedLocation = 128
};

class Dimension : public Entity {
public:
    Dimension();
    DimensionType getFlags() const;
};

} // namespace Entities
} // namespace dwg
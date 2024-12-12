namespace dwg {
namespace Entities {
/// Multiline text drawing direction.
enum DrawingDirectionType : short {
    /// \brief Left to right.
    LeftToRight = 1,

    /// \brief Right to left.
    RightToLeft = 2,

    /// \brief Top to bottom.
    TopToBottom = 3,

    /// \brief Bottom to top.
    BottomToTop = 4,

    /// \brief By Style.
    ByStyle = 5,
};
} // namespace Entities
} // namespace dwg
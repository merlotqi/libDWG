namespace dwg {
namespace Entities {

enum MultiLeaderPropertyOverrideFlags : int {

    /// No Flag: No property to be overridden
    None = 0,

    /// Override <see cref="MultiLeaderStyle.PathType"/> property.
    PathType = 0x1,

    /// Override <see cref="MultiLeaderStyle.LineColor" /> property.
    LineColor = 0x2,

    /// Override <see cref="MultiLeaderStyle.LeaderLineType" /> property.
    LeaderLineType = 0x4,

    /// Override <see cref="MultiLeaderStyle.LeaderLineWeight" /> property.
    LeaderLineWeight = 0x8,

    /// Override <see cref="MultiLeaderStyle.EnableLanding" /> property.
    EnableLanding = 0x10,

    /// Override <see cref="MultiLeaderStyle.LandingGap"/> property.
    LandingGap = 0x20,

    /// Override <see cref="MultiLeaderStyle.EnableDogleg"/> property.
    EnableDogleg = 0x40,

    /// Override <see cref="MultiLeaderStyle.LandingDistance"/> property.
    LandingDistance = 0x80,

    /// Override <see cref="MultiLeaderStyle.Arrowhead"/> property.
    Arrowhead = 0x100,

    /// Override <see cref="MultiLeaderStyle.ArrowheadSize"/> property.
    ArrowheadSize = 0x200,

    /// Override <see cref="MultiLeaderStyle.ContentType"/> property.
    ContentType = 0x400,

    /// Override <see cref="MultiLeaderStyle.TextStyle"/> property.
    TextStyle = 0x800,

    /// Override <see cref="MultiLeaderStyle.TextLeftAttachment"/> property.
    TextLeftAttachment = 0x1000,

    /// Override <see cref="MultiLeaderStyle.TextAngle"/> property.

    TextAngle = 0x2000,

    /// Override <see cref="MultiLeaderStyle.TextAlignment"/> property.

    TextAlignment = 0x4000,

    /// Override <see cref="MultiLeaderStyle.TextColor"/> property.

    TextColor = 0x8000,

    /// Override <see cref="MultiLeaderStyle.TextHeight" /> property.

    TextHeight = 0x10000,

    /// Override <see cref="MultiLeaderStyle.TextFrame"/> property.

    TextFrame = 0x20000,

    /// Override <see cref="MultiLeaderStyle.??" /> property.

    EnableUseDefaultMText = 0x40000,

    /// Override <see cref="MultiLeaderStyle.BlockContent"/> property.

    BlockContent = 0x80000,

    /// Override <see cref="MultiLeaderStyle.BlockContentColor"/> property.

    BlockContentColor = 0x100000,

    /// Override <see cref="MultiLeaderStyle.BlockContentScale"/> property.

    BlockContentScale = 0x200000,

    /// Override <see cref="MultiLeaderStyle.BlockContentRotation"/> property.

    BlockContentRotation = 0x400000,

    /// Override <see cref="MultiLeaderStyle.BlockContentConnection"/> property.

    BlockContentConnection = 0x800000,

    /// Override <see cref="MultiLeaderStyle.ScaleFactor"/> property.

    ScaleFactor = 0x1000000,

    ///	Override <see cref="MultiLeaderStyle.TextRightAttachment"/> property.

    TextRightAttachment = 0x2000000,

    ///	Override <see cref="MultiLeaderStyle.?? which"/> property.

    TextSwitchAlignmentType = 0x4000000,

    /// Override <see cref="MultiLeaderStyle.TextAttachmentDirection"/>
    /// property.

    TextAttachmentDirection = 0x8000000,

    /// Override <see cref="MultiLeaderStyle.TextTopAttachment"/> property.

    TextTopAttachment = 0x10000000,

    /// Override <see cref="MultiLeaderStyle.TextBottomAttachment"/> property.

    TextBottomAttachment = 0x20000000
};

class MultiLeader : public Entity {};
} // namespace Entities
} // namespace dwg
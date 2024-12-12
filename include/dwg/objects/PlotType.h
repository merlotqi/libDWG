#ifndef PLOTTYPE_H
#define PLOTTYPE_H

namespace dwg {
namespace Object {

/// <summary>
/// Defines the portion of paper space to output to the media
/// </summary>
enum PlotType {
    /// <summary>
    /// Last screen display
    /// </summary>
    LastScreenDisplay = 0,

    /// <summary>
    /// Drawing extents
    /// </summary>
    DrawingExtents = 1,

    /// <summary>
    /// Drawing limits
    /// </summary>
    DrawingLimits = 2,

    /// <summary>
    /// View specified by the plot view name
    /// </summary>
    View = 3,

    /// <summary>
    /// Window specified by the upper-right and bottom-left window corners
    /// </summary>
    Window = 4,

    /// <summary>
    /// Layout information
    /// </summary>
    LayoutInformation = 5
};

} // namespace Object

} // namespace dwg

#endif
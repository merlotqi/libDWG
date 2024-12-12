#ifndef RENDERMODE_H
#define RENDERMODE_H

namespace dwg {

/// Viewport render mode

enum RenderMode {

    /// Classic 2D
    Optimized2D,

    /// Wire frame
    Wireframe,

    /// Hidden line
    HiddenLine,

    /// Flat shaded
    FlatShaded,

    /// Gouraud shaded
    GouraudShaded,

    /// Flat shaded with wire frame
    FlatShadedWithWireframe,

    /// Gouraud shaded with wireframe
    GouraudShadedWithWireframe,
};

} // namespace dwg

#endif /* RENDERMODE_H */
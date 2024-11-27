#ifndef RENDERMODE_H
#define RENDERMODE_H

namespace DWG
{
namespace Common
{

/// <summary>
/// Viewport render mode
/// </summary>
enum RenderMode
{
  /// <summary>
  /// Classic 2D
  /// </summary>
  Optimized2D,
  /// <summary>
  /// Wire frame
  /// </summary>
  Wireframe,
  /// <summary>
  /// Hidden line
  /// </summary>
  HiddenLine,
  /// <summary>
  /// Flat shaded
  /// </summary>
  FlatShaded,
  /// <summary>
  /// Gouraud shaded
  /// </summary>
  GouraudShaded,
  /// <summary>
  /// Flat shaded with wire frame
  /// </summary>
  FlatShadedWithWireframe,
  /// <summary>
  /// Gouraud shaded with wireframe
  /// </summary>
  GouraudShadedWithWireframe,
};

} // namespace Common
} // namespace DWG

#endif /* RENDERMODE_H */
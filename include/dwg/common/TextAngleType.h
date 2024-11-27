#ifndef TEXTANGLETYPE_H
#define TEXTANGLETYPE_H

namespace DWG
{
namespace Common
{
    
/**
 * @enum TextAngleType
 * @brief Enumeration for text angle types.
 */
enum TextAngleType : short
{
  /**
   * @brief Text angle is equal to last leader line segment angle
   */
  ParllelToLastLeaderLine = 0,

  /**
   * @brief Text is horizontal
   */
  Horizontal = 1,

  /**
   * @brief Text angle is equal to last leader line segment angle,
   * but potentially rotated by 180 degrees so the right side is up
   * for readability.
   */
  Optimized = 2,
};

} // namespace Common
} // namespace DWG

#endif
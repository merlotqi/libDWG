#ifndef MULTILEADERPATHTYPE_H
#define MULTILEADERPATHTYPE_H

namespace DWG
{
namespace Common
{

/**
 * @enum MultiLeaderPathType
 * @brief Enumeration for multi-leader path types.
 */
enum MultiLeaderPathType : short
{
  /**
   * @brief Invisible leader
   */
  Invisible = 0,

  /**
   * @brief Draws the leader line as a set of straight line segments
   */
  StraightLineSegments = 1,

  /**
   * @brief Draws the leader line as a spline
   */
  Spline = 2
};

} // namespace Common
} // namespace DWG

#endif /* MULTILEADERPATHTYPE_H */
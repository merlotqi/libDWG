#ifndef ANGULAR_UNIT_FORMAT_H
#define ANGULAR_UNIT_FORMAT_H

namespace DWG
{
namespace Type
{

/// <summary>
/// Angular unit format
/// </summary>
enum AngularUnitFormat : short
{
  /// <summary>
  /// Decimal degrees
  /// </summary>
  DecimalDegrees,

  /// <summary>
  /// Degrees/minutes/seconds
  /// </summary>
  DegreesMinutesSeconds,

  /// <summary>
  /// Gradians
  /// </summary>
  Gradians,

  /// <summary>
  /// Radians
  /// </summary>
  Radians,

  /// <summary>
  /// Surveyors units
  /// </summary>
  SurveyorsUnits,
};

} // namespace Type
} // namespace DWG

#endif
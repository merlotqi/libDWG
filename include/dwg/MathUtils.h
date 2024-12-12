#ifndef DWG_MATHUTILS_H
#define DWG_MATHUTILS_H

#include <math.h>
#include <dwg/util/Coordinate.h>

namespace dwg {

class MathUtils {
public:
    static constexpr double RadToDegFactor = (180.0 / M_PI);
    static constexpr double DegToRadFactor = (M_PI / 180.0);

    static constexpr double Epsilon = 1e-12;
    static constexpr double TwoPI = M_PI * 2;

    static bool IsZero(double number);
    static bool IsZero(double number, double threshold);
    static double FixZero(double number);
    static double FixZero(double number, double threshold);
    static double RadToDeg(double value);
    static double DegToRad(double value);

    static Util::XY GetCenter(Util::XY start, Util::XY end, double bulge);
    static Util::XY GetCenter(Util::XY start, Util::XY end, double bulge,
                              double &radius);
};

} // namespace dwg

#endif /* DWG_MATHUTILS_H */
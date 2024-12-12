#ifndef LIBDWG_COLOR_H
#define LIBDWG_COLOR_H

#include <dwg/exports.h>
#include <vector>

namespace dwg {

class LIBDWG_API Color {

    static const unsigned char indexRgb[][3];

    const int m_maxTrueColor = 0b0001'0000'0000'0000'0000'0000'0000;
    const int m_trueColorFlag = 0b0100'0000'0000'0000'0000'0000'0000'0000;

    unsigned int m_color;

    Color(unsigned int trueColor);

public:
    Color(short index);
    Color(unsigned char r, unsigned char g, unsigned char b);
    Color(const std::vector<unsigned char> rgb);

    static Color ByLayer();
    static Color ByBlock();
    static Color ByEntity();
    static Color FromTrueColor(unsigned int color);
    static unsigned char ApproxIndex(unsigned char r, unsigned char g,
                                     unsigned char b);

    bool IsByLayer() const;
    bool IsByBlock() const;
    short Index() const;
    int TrueColor() const;
    bool IsTrueColor() const;
    unsigned char R() const;
    unsigned char G() const;
    unsigned char B() const;
    unsigned char GetApproxIndex() const;

    friend bool operator==(const Color &lhs, const Color &rhs);
    friend bool operator!=(const Color &lhs, const Color &rhs);
};

} // namespace dwg

#endif // LIBDWG_COLOR_H
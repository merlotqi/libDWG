#ifndef DWG_TRANSPARENCY_H
#define DWG_TRANSPARENCY_H

namespace dwg {

class Transparency {
    short m_value;

public:
    Transparency(short value);
public
    bool isByLayer() const;
public
    bool isByBlock() const;
public
    short getValue() const;
    void setValue(short value);

    static int ToAlphaValue(Transparency transparency);
    static Transparency FromAlphaValue(int value);
    static Transparency ByLayer();
    static Transparency ByBlock();
    static Transparency Opaque();
};

} // namespace dwg

#endif /* DWG_TRANSPARENCY_H */
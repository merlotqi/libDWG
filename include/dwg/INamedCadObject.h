#ifndef DWG_INAMEDCADOBJECT_H
#define DWG_INAMEDCADOBJECT_H

#include <dwg/util/delegate.h>

namespace dwg {

class INamedCadObject {
public:
    INamedCadObject() = default;
    virtual ~INamedCadObject() = default;

    std::string getName() const;

    Delegate<void(const std::string &, const std::string &)> OnNameChanged;
};

} // namespace dwg

#endi /* DWG_INAMEDCADOBJECT_H */
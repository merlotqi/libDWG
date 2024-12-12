#ifndef LIBDWG_DXFCLASSMAP_H
#define LIBDWG_DXFCLASSMAP_H

#include <dwg/exports.h>
#include <string>
#include <map>

namespace dwg {

class LIBDWG_API DxfMapBase {
    std::string m_name;
    std::map<int, DxfProperty> m_dxfProperties;
};

} // namespace dwg

#endif // LIBDWG_DXFCLASSMAP_H
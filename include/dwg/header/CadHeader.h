#ifndef LIBDWG_CADHEADER_H
#define LIBDWG_CADHEADER_H

#include <dwg/exports.h>
#include <dwg/Common/ACadVersion.h>

namespace dwg {

class LIBDWG_API CadHeader {

public:
    CadHeader(CadDocument *document);
    CadHeader(ACadVersion version);
};

} // namespace dwg

#endif // LIBDWG_CADHEADER_H
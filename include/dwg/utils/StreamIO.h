#ifndef LIBDWG_STREAMIO_H
#define LIBDWG_STREAMIO_H

#include <iostream>
#include <dwg/exports.h>

namespace dwg {
namespace utils {

class LIBDWG_API InputStream {
    std::istream *m_stream;

public:
};

class LIBDWG_API OutputStream {
    std::ostream *m_stream;

public:
};

} // namespace utils
} // namespace dwg

#endif // LIBDWG_STREAMIO_H
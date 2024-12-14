#include <sstream>

namespace dwg {
namespace io {

class CRC32StreamHandler
{
};

class CRC32StreamInputHandler : public std::istringstream
{
};

class CRC32StreamOutputHandler : public std::ostringstream
{
};

} // namespace io
} // namespace dwg

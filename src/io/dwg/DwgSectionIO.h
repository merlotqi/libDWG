#include <dwg/ACadVersion.h>

namespace dwg {
namespace io {

class IDwgStreamReader;
class DwgSectionIO
{
protected:
    ACadVersion m_version;
    bool R13_14Only;
    bool R13_15Only;
    bool R2000Plus;
    bool R2004Pre;
    bool R2007Pre;
    bool R2004Plus;
    bool R2007Plus;
    bool R2010Plus;
    bool R2013Plus;
    bool R2018Plus;

public:
    DwgSectionIO(ACadVersion version)
    {
        m_version = version;

		R13_14Only = version == ACadVersion::AC1014 || version == ACadVersion::AC1012;
		R13_15Only = version >= ACadVersion::AC1012 && version <= ACadVersion::AC1015;
		R2000Plus = version >= ACadVersion::AC1015;
		R2004Pre = version < ACadVersion::AC1018;
		R2007Pre = version <= ACadVersion::AC1021;
		R2004Plus = version >= ACadVersion::AC1018;
		R2007Plus = version >= ACadVersion::AC1021;
		R2010Plus = version >= ACadVersion::AC1024;
		R2013Plus = version >= ACadVersion::AC1027;
		R2018Plus = version >= ACadVersion::AC1032;
    }

    static bool CheckSentinel(const std::vector<unsigned char>& actual, const std::vector<unsigned char>& expected);
    bool CheckSentinel(IDwgStreamReader* sreader, const std::vector<unsigned char>& expected);

    virtual std::string SectionName() const = 0;

};




}
}
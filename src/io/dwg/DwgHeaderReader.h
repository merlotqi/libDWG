


namespace dwg {
namespace io {

class DwgHeaderReader : public DwgSectionIO
{
public:
    DwgHeaderReader();

    std::string SectionName() const
    {
        static constexpr auto name = "AcDb:Header";
        return name;
    }
};

}
}

#include <dwg/IO/ICadWriter.h>
#include <dwg/Common/CadDocument.h>

namespace dwg {
namespace IO {

class CadWriterConfiguration {
public:
    CadWriterConfiguration() = default;
    virtual ~CadWriterConfiguration() = default;

    bool CloseStream() const { return m_closeStream; }
    void CloseStream(bool value) { m_closeStream = value; }

    bool WriteXRords() const { return m_writeXRords; }
    void WriteXRords(bool value) { m_writeXRords = value; }

protected:
    bool m_closeStream;
    bool m_writeXRords;
};

template <class T>
class CadWriterBase : public ICadWriter {
    static_cast(
        std::is_base_v<CadWriterConfiguration, T>,
        "Class CadWriterBase template must based CadWriterConfiguration");

public:
    using pointer = T *;
    using reference = T &;

    T *Configuration() const { return m_configuration; }

    void Configuration(const T *value) { m_configuration = value; }

protected:
    T *m_configuration;
    std::iostream *m_stream;
    Common::CadDocument *m_document;
    // encoding
}

} // namespace IO
} // namespace dwg
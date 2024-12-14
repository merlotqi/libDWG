#include <ctime>
#include <map>
#include <string>


class CadSummaryInfo
{
    std::string m_title;
    std::string m_subject;
    std::string m_author;
    std::string m_keywords;
    std::string m_comments;
    std::string m_lastSavedBy;
    std::string m_hyperlinkBase;
    time_t m_createDate;
    time_t m_modifiedDate;
    std::map<std::string, std::string> m_properties;

public:
    CadSummaryInfo();

    std::string getTitle() const;
    void setTitle(const std::string &value);

    std::string getSubject() const;
    void stSubject(const std::string &value);

    std::string getAuthor() const;
    void setAuthor(const std::string &value);

    std::string getKeywords() const;
    void setKeywords(const std::string &value);

    std::string getComments() const;
    void setComments(const std::string &value);

    std::string getLastSavedBy() const;
    void setLastSavedBy(const std::string &value);

    std::string getHyperlinkBase() const;
    void setHyperlinkBase(const std::string &value);

    time_t getCreatedDate() const;
    void setCreatedDate(time_t value);

    time_t getModifiedDate() const;
    void setModifiedDate(time_t value);

    std::map<std::string, std::string> getProperties() const;
    void setProperties(const std::map<std::string, std::string> &value);
};
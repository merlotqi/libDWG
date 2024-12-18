

namespace dwg {
namespace objects {


template<class>
class ObjectDictionaryCollection ： IHandledCadObject
{
    static_assert(std::is_base_of_v<T, NonGraphicalObject>,
                  "T must is base of NonGraphicalObject");

    CadDictionary _dictionary;

public:
    unsigned long long Handle() const { return _dictionary.Handle(); }

    T operator[](const std::string &name) const { return (T) _dictionary[key]; }

protected:
    ObjectDictionaryCollection(const CadDictionary &dictionary);

    virtual void Add(T entry);
    bool ContainsKey(const std::string &key);
    bool tryGetValue(const std::string &name, T &entry);
    bool Remove(const std::string &name);
    bool Remove(const std::string &name, T &entry);
    void Clear();
};

}// namespace objects
}// namespace dwg
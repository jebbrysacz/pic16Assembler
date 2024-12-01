#ifndef CONSTPREFIX_HH
#define CONSTPREFIX_HH

#include <string>
#include <unordered_map>

class ConstPrefix {
public:
    ConstPrefix(const std::string& name);
    std::string get_name() const;

    static const ConstPrefix& get(const std::string& name);
    static void add(const std::string& name);

private:
    std::string name;
    static std::unordered_map<std::string, ConstPrefix> const_prefixes;
};

#endif

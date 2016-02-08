#include <sstream>
#include <string>

enum empties_t
{
    empties_ok = 0,
    no_empties
};

template <typename Container>
Container& split_str(
        Container&                                 result,
        const typename Container::value_type&      s,
        typename Container::value_type::value_type delimiter,
        empties_t                           empties = empties_t::empties_ok )
{
    result.clear();
    std::istringstream ss( s );
    while (!ss.eof())
    {
        typename Container::value_type field;
        getline( ss, field, delimiter );
        if ((empties == empties_t::no_empties) && field.empty()) continue;
        result.push_back( field );
    }
    return result;
}

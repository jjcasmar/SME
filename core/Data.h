#ifndef DATA_H
#define DATA_H

#include <string>

namespace SME
{
namespace core
{

class BaseData
{
public:
    BaseData();
    virtual ~BaseData() = 0;

    void setName(const std::string &name);
    void setDescription(const std::string &descriptor);

private:
    std::string _variableName;
    std::string _variableDescriptor;
    bool _lock;
};

template <class T>
class Data : public BaseData
{
public:
    Data(){}
    virtual ~Data(){}

    T value() const{return _value;}
    void setValue(const T& value) {_value = value;}

protected:
    T _value;
};

}
}

#endif // DATA_H

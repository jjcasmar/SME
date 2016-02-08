#ifndef ASSETLIBRARY_H
#define ASSETLIBRARY_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <core/Data.h>

namespace tinyxml2
{
class XMLElement;
}

namespace SME
{
namespace core
{
class IAsset
{
public:
    IAsset(const std::string &type);
    const std::string &name() const {return _name;}
    const std::string &type() const {return _type;}
    virtual ~IAsset() = 0;

    virtual void configure(tinyxml2::XMLElement *element) = 0;

    void setName(const std::string &name){_name = name;}
    inline void initData(BaseData *data, const std::string variableName, const std::string variableDescriptor = "")
    {
        auto it = _data.find(variableName);
        if (it != _data.end())
        {
            std::cerr << "Variable already exist" << std::endl;
            return;
        }
        data->setName(variableName);
        data->setDescription(variableDescriptor);
        _data[variableName] = data;
    }

    template<class T>
    inline BaseData *addData(const std::string &variable)
    {
        auto it = _data.find(variable);
        if (it == _data.end())
        {
            Data<T> *dat = new Data<T>();
            dat->setName(variable);
            _data[variable] = dat;
            return dat;
        }
        std::cerr << "Variable " << variable << " is already a variable for this asset. Cant create another variable with the same name" << std::endl;
        return nullptr;
    }

    inline BaseData *data(const std::string &variable) const
    {
        auto it = _data.find(variable);
        if (it != _data.end())
            return it->second;

        std::cerr << "Variable " << variable << " is not registered as visible from outside the plugin. Access forbidden" << std::endl;
        return nullptr;
    }

protected:
    std::map<std::string, BaseData*> _data;
    static std::string _type;
    std::string _name;
};

class AssetLibrary
{
public:
    AssetLibrary();

    inline IAsset *getAsset(const std::string &name)
    {
        for (auto it = _assets.begin();
             it != _assets.end(); ++it)
        {
            if ((*it)->name() == name)
                return *it;
        }
        return nullptr;
    }

    template<class T>
    std::vector<T*> getAssets()
    {
        std::vector<T*> result;
        T *a;
        for (auto it = _assets.begin();
             it != _assets.end(); ++it)
        {

            if ((a = dynamic_cast<T*>((*it))) != nullptr)
                result.push_back(a);
        }
        return result;
    }

    bool addAsset(IAsset *asset);

private:
    std::vector<IAsset*> _assets;
};

}
}


#endif // ASSETLIBRARY_H

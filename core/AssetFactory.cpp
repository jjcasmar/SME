#include "AssetFactory.h"

SME::core::AssetFactory *SME::core::AssetFactory::_instance = nullptr;

SME::core::AssetFactory::AssetFactory()
{

}

SME::core::AssetFactory::~AssetFactory()
{

}

bool SME::core::AssetFactory::registerType(const std::string &type, AssetCreatorFunctor creator, std::string &report)
{
    if (_creators.find(type) != _creators.end())
    {
        report = "There is already an asset with this typename";
        return false;
    }
  _creators[type] = creator;
  return true;
}

SME::core::IAsset *SME::core::AssetFactory::create(std::string type) const
{
  auto it = _creators.find(type);
  if (it != _creators.end())
    return it->second();
  return nullptr;
}

std::list<std::string> SME::core::AssetFactory::types() const
{
  std::list<std::string> assets;
  for (auto it = _creators.begin(); it != _creators.end(); ++it)
    assets.push_back(it->first);
  return assets;
}

SME::core::AssetFactory *SME::core::AssetFactory::get()
{
  if (_instance == nullptr)
    _instance = new SME::core::AssetFactory;
  return _instance;
}

#include "AssetLibrary.h"

#include <iostream>

using namespace SME::core;

std::string IAsset::_type = "Default";

IAsset::~IAsset()
{
}

AssetLibrary::AssetLibrary()
{

}

bool SME::core::AssetLibrary::addAsset(SME::core::IAsset *asset)
{
  if (getAsset(asset->name()) == nullptr)
  {
    _assets.push_back(asset);
    return true;
  }
  else
  {
    std::cerr << "There is already an asset with this name" << std::endl;
    return false;
  }
}

IAsset::IAsset(const std::string &type)
{
  _type = type;
}

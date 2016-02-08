#include "TetraMesh.h"

#include <iostream>

using namespace SME::asset;

SME::asset::TetraMesh::TetraMesh(const std::string &type) :
    SME::core::IAsset(type)
{
    initData(&_points, "points", "");
    initData(&_tetras, "tetras", "");
}

TetraMesh::~TetraMesh()
{

}

void TetraMesh::configure(tinyxml2::XMLElement *element)
{

}

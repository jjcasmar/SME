#include "Data.h"

using namespace SME::core;

BaseData::BaseData()
{
    _lock = false;
}

void BaseData::setName(const std::string &name)
{
    if (_lock)
        return;
    _variableName = name;
}

void BaseData::setDescription(const std::string &descriptor)
{
    if (_lock)
        return;
    _variableDescriptor =descriptor;
    _lock = true;
}

#include "SMEApplication.h"

#include "core/World.h"

SMEApplication::SMEApplication(int &argc, char **argv) :
    QApplication(argc, argv)
{

}

void SMEApplication::worldLoop()
{
    SME::core::World::get()->loop();
}

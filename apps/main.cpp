#include <core/World.h>
#include <core/SceneLoader.h>

#include <Eigen/Geometry>
#include <Eigen/Core>
#include <iostream>
#include "SMEApplication.h"

using namespace SME::core;

int main(int argc, char **argv)
{
    SMEApplication *app = new SMEApplication(argc, argv);

    QTimer *t = new QTimer;
    QObject::connect(t, SIGNAL(timeout()), app, SLOT(worldLoop()));

    t->setInterval(0);
    t->start();

  World *world = World::get();
  world->initWorld();

  SME::core::SceneLoader::load("/home/jjcasmar/SME/build/samples/World.xml");

  app->exec();
  world->cleanUp();
  delete world;

  return 0;
}

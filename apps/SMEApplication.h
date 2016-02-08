#ifndef SMEAPPLICATION_H
#define SMEAPPLICATION_H

#include <QApplication>
#include <QTimer>
#include "core/World.h"

class SMEApplication : public QApplication
{
    Q_OBJECT
public:
    SMEApplication(int &argc, char** argv);

public slots:
    void worldLoop();

private:
    QTimer *t;
};

#endif // SMEAPPLICATION_H

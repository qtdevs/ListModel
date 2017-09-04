#ifndef QTMODELSMODULE_H
#define QTMODELSMODULE_H

#include <QQmlEngine>

class QtModelsModule
{
public:
    static void initialize();
    static void initEngine(QQmlEngine *engine);
};

#endif // QTMODELSMODULE_H

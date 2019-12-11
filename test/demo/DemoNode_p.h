#ifndef DEMONODE_P_H
#define DEMONODE_P_H

#include "DemoNode.h"

class DemoNodePrivate
{
    Q_DECLARE_PUBLIC(DemoNode)

public:
    DemoNodePrivate();
    virtual ~DemoNodePrivate();
protected:
    DemoNode *q_ptr;

protected:
    QString text;
};

#endif // DEMONODE_P_H

#ifndef DEMOCORE_P_H
#define DEMOCORE_P_H

#include "DemoCore.h"
#include "QCxxListModel.h"
#include "DemoNode.h"

class DemoCorePrivate
{
    Q_DECLARE_PUBLIC(DemoCore)

public:
    DemoCorePrivate();
    virtual ~DemoCorePrivate();
protected:
    DemoCore *q_ptr;

protected:
    QCxxListModel<DemoNode> nodes;
};

#endif // DEMOCORE_P_H

#include "DemoCore.h"
#include "DemoCore_p.h"

// class DemoCore

DemoCore::DemoCore(QObject *parent)
    : QObject(parent)
    , d_ptr(new DemoCorePrivate())
{
    d_ptr->q_ptr = this;

    for (int i = 0; i < 3; ++i) {
        DemoNode *node = new DemoNode(this);
        node->setText(QString::number(i));
        d_ptr->nodes.append(node);
    }
}

DemoCore::~DemoCore()
{
}

QAbstractListModel *DemoCore::nodes() const
{
    Q_D(const DemoCore);

    return const_cast<QCxxListModel<DemoNode> *>(&d->nodes);
}

void DemoCore::move(int from, int to)
{
    Q_D(DemoCore);

    d->nodes.move(from, to);
}

// class DemoCorePrivate

DemoCorePrivate::DemoCorePrivate()
    : q_ptr(nullptr)
{
}

DemoCorePrivate::~DemoCorePrivate()
{
}

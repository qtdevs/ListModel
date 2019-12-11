#include "DemoCore.h"
#include "DemoCore_p.h"

#include <QTimer>

// class DemoCore

DemoCore::DemoCore(QObject *parent)
    : QObject(parent)
    , d_ptr(new DemoCorePrivate())
{
    d_ptr->q_ptr = this;
    Q_D(DemoCore);

    for (int i = 0; i < 3; ++i) {
        DemoNode *node = new DemoNode(this);
        node->setText(QString::number(i));
        d->nodes.append(node);

        d->points.append(QPointF(i * 100, i * 120));
    }

    QTimer *timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->setInterval(500);
    connect(timer, &QTimer::timeout,
            this, [d] {
        int x = qrand() % 200;
        int y = qrand() % 200;

        d->points.replace(qrand() % 3, QPointF(x, y));
    });
    timer->start();
}

DemoCore::~DemoCore()
{
}

QAbstractListModel *DemoCore::nodes() const
{
    Q_D(const DemoCore);

    return const_cast<QCxxListModel<DemoNode *> *>(&d->nodes);
}

QAbstractListModel *DemoCore::points() const
{
    Q_D(const DemoCore);

    return const_cast<QCxxListModel<QPointF> *>(&d->points);
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

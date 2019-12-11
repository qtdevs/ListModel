#include "DemoNode.h"
#include "DemoNode_p.h"

// class DemoNode

DemoNode::DemoNode(QObject *parent)
    : QObject(parent)
    , d_ptr(new DemoNodePrivate())
{
    d_ptr->q_ptr = this;
}

DemoNode::~DemoNode()
{
}

void DemoNode::setText(const QString &text)
{
    Q_D(DemoNode);

    if (text != d->text) {
        d->text = text;
        emit textChanged();
    }
}

QString DemoNode::text() const
{
    Q_D(const DemoNode);

    return d->text;
}

// class DemoNodePrivate

DemoNodePrivate::DemoNodePrivate()
    : q_ptr(nullptr)
{
}

DemoNodePrivate::~DemoNodePrivate()
{
}

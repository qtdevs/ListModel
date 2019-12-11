#ifndef DEMOCORE_H
#define DEMOCORE_H

#include <QObject>
#include <QAbstractListModel>

class DemoNode;
class DemoCorePrivate;
class DemoCore : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DemoCore)

    Q_PROPERTY(QAbstractListModel *nodes READ nodes CONSTANT)

public:
    explicit DemoCore(QObject *parent = nullptr);
    virtual ~DemoCore();
protected:
    QScopedPointer<DemoCorePrivate> d_ptr;

public:
    QAbstractListModel *nodes() const;

public slots:
    void move(int from, int to);
};

#endif // DEMOCORE_H

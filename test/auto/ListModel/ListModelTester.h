#ifndef LISTMODELTESTER_H
#define LISTMODELTESTER_H

#include <QObject>

#include "QCxxListModel.h"

class ListModelTesterPrivate;
class ListModelTester : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ListModelTester)

public:
    ListModelTester(Internal::QCxxListModel *model, QObject *parent = nullptr);
protected:
    QScopedPointer<ListModelTesterPrivate> d_ptr;
public:
    virtual ~ListModelTester();

public:
    int count() const;

    void resetCount();

private:
    void onCountChanged();

public:
    int changedSize() const;
    bool isChanged(int index, int from, int to) const;
    void resetChangedList();

private:
    void onDataChanged(const QModelIndex &tl, const QModelIndex &br, const QVector<int> &roles);
};

#endif // LISTMODELTESTER_H

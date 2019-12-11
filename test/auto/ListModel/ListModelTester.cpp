#include "ListModelTester.h"
#include "ListModelTester_p.h"

#include <QAbstractItemModelTester>

// class ListModelTester

ListModelTester::ListModelTester(Internal::QCxxListModel *model, QObject *parent)
    : QObject(parent ? parent : model)
    , d_ptr(new ListModelTesterPrivate())
{
    d_ptr->q_ptr = this;
    Q_CHECK_PTR(model);

    new QAbstractItemModelTester(model, this);

    connect(model, &Internal::QCxxListModel::countChanged,
            this, &ListModelTester::onCountChanged);
    connect(model, &Internal::QCxxListModel::dataChanged,
            this, &ListModelTester::onDataChanged);
}

ListModelTester::~ListModelTester()
{
}

int ListModelTester::count() const
{
    Q_D(const ListModelTester);

    return d->count;
}

void ListModelTester::resetCount()
{
    Q_D(ListModelTester);

    d->count = 0;
}

void ListModelTester::onCountChanged()
{
    Q_D(ListModelTester);

    ++d->count;
}

int ListModelTester::changedSize() const
{
    Q_D(const ListModelTester);

    return d->changedList.count();
}

bool ListModelTester::isChanged(int index, int from, int to) const
{
    Q_D(const ListModelTester);

    ListModelChanged changed = d->changedList.at(index);
    return ((from == changed.first) && (to == changed.second));
}

void ListModelTester::resetChangedList()
{
    Q_D(ListModelTester);

    d->changedList.clear();
}

void ListModelTester::onDataChanged(const QModelIndex &tl, const QModelIndex &br, const QVector<int> &roles)
{
    Q_D(ListModelTester);

    Q_ASSERT(tl.column() == 0);
    Q_ASSERT(br.column() == 0);
    Q_ASSERT(roles.count() == 1);
    Q_ASSERT(roles.at(0) == Internal::QCxxListModel::ModelDataRole);

    d->changedList.append(ListModelChanged(tl.row(), br.row()));
}

// class ListModelTesterPrivate

ListModelTesterPrivate::ListModelTesterPrivate()
    : q_ptr(nullptr)
    , model(nullptr)
    , count(0)
{
}

ListModelTesterPrivate::~ListModelTesterPrivate()
{
}

#include "QCxxListModel.h"
#include "QCxxListModel_p.h"

namespace Internal {

// class QCxxListModel

QCxxListModel::QCxxListModel(QObject *parent)
    : QAbstractListModel(parent)
    , d_ptr(new QCxxListModelPrivate())
{
    d_ptr->q_ptr = this;
}

QCxxListModel::~QCxxListModel()
{
}

QHash<int, QByteArray> QCxxListModel::roleNames() const
{
#ifdef Q_COMPILER_INITIALIZER_LISTS
    QHash<int, QByteArray> roleNames { { QCxxListModel::ModelDataRole, "modelData" } };
#else
    QHash<int, QByteArray> roleNames;
    roleNames[QCxxListModel::ModelDataRole] = "modelData";
#endif // Q_COMPILER_INITIALIZER_LISTS

    return roleNames;
}

void QCxxListModel::_q_resetCount()
{
    Q_D(QCxxListModel);

    if (d->countEnabled) {
        int count = rowCount();
        if (count != d->count) {
            d->count = count;
            emit countChanged();
        }
    }
}

bool QCxxListModel::isCountEnabled() const
{
    Q_D(const QCxxListModel);

    return d->countEnabled;
}

void QCxxListModel::setCountEnabled(bool y)
{
    Q_D(QCxxListModel);

    if (y != d->countEnabled) {
        d->countEnabled = y;
        if (!d->countEnabled) {
            d->count = -1;
        }
        emit countEnabledChanged();
    }
}

// class QCxxListModelPrivate

QCxxListModelPrivate::QCxxListModelPrivate()
    : q_ptr(nullptr)
    , countEnabled(false)
    , count(-1)
{
}

QCxxListModelPrivate::~QCxxListModelPrivate()
{
}

} // namespace Internal


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
    return QCxxListModelPrivate::roleNames;
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

void QCxxListModel::_q_sync(const QModelIndex &tl, const QModelIndex &br)
{
    emit dataChanged(tl, br, QCxxListModelPrivate::modelDataRole);
}

// class QCxxListModelPrivate

QMutex QCxxListModelPrivate::internalGuard;

#ifdef Q_COMPILER_INITIALIZER_LISTS

QVector<int> QCxxListModelPrivate::modelDataRole {
    QCxxListModel::ModelDataRole
};

QHash<int, QByteArray> QCxxListModelPrivate::roleNames {
    { QCxxListModel::ModelDataRole, "modelData" }
};

#endif // Q_COMPILER_INITIALIZER_LISTS

QCxxListModelPrivate::QCxxListModelPrivate()
    : q_ptr(nullptr)
    , countEnabled(false)
    , count(-1)
{
#ifndef Q_COMPILER_INITIALIZER_LISTS

    if (modelDataRole.isEmpty()
            || roleNames.isEmpty()) {
        QMutexLocker locker(&internalGuard);

        if (modelDataRole.isEmpty()) {
            modelDataRole.append(QCxxListModel::ModelDataRole);
        }

        if (roleNames.isEmpty()) {
            roleNames.insert(QCxxListModel::ModelDataRole, "modelData");
        }
    }

#endif // Q_COMPILER_INITIALIZER_LISTS
}

QCxxListModelPrivate::~QCxxListModelPrivate()
{
}

} // namespace Internal


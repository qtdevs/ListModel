#include "QListModel.h"

namespace QtModels {

const QVector<int>           ListModel::_roles{ ListModel::ModelDataRole };
const QHash<int, QByteArray> ListModel::_roleNames{ { ListModel::ModelDataRole, "modelData" } };

ListModel::ListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    return _roleNames;
}

} // namespace QtModels

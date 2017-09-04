#ifndef QLISTMODEL_H
#define QLISTMODEL_H

#include <QAbstractListModel>

namespace QtModels {

class ListModel : public QAbstractListModel
{
    Q_OBJECT

protected:
    ListModel(QObject *parent);

public:
    enum ModelDataRoles { ModelDataRole = Qt::UserRole + 1 };
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

protected:
    static const QVector<int>           _roles;
    static const QHash<int, QByteArray> _roleNames;
};

} // namespace QtModels

template <typename T>
class QListModel : public QtModels::ListModel, public QList<T>
{
public:
    QListModel(const QList<T> &l, QObject *parent = Q_NULLPTR)
        : QtModels::ListModel(parent), QList<T>(l) { }
    explicit QListModel(QObject *parent = Q_NULLPTR)
        : QtModels::ListModel(parent) { }

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

public:
    T value(const QModelIndex &index) const;
    T value(const QModelIndex &index, const T &defaultValue) const;

    T value(int i) const;
    T value(int i, const T &defaultValue) const;

public:
    void append(const QList<T> &l);

    void prepend(const T &t);
    void append(const T &t);

    void push_front(const T &t);
    void push_back(const T &t);

    void replace(int i, const T &t);
    void insert(int i, const T &t);

    bool removeOne(const T &t);
    int removeAll(const T &t);
    //
    void pop_front();
    void pop_back();

    void removeAt(int i);
    void removeFirst();
    void removeLast();

    T takeAt(int i);
    T takeFirst();
    T takeLast();

    void swap(int i, int j);
    void swap(QList<T> &list);
    void move(int from, int to);

    void clear();

public: // Extra methods
    void deleteAll();

public: // Disabled stl methods
    typedef typename QList<T>::iterator         Iterator;
    typedef typename QList<T>::reverse_iterator ReverseIterator;

    Iterator begin(); // Not Implemented
    Iterator end(); // Not Implemented

    ReverseIterator rbegin(); // Not Implemented
    ReverseIterator rend(); // Not Implemented

    Iterator insert(Iterator before, const T &t); // Not Implemented
    Iterator erase(Iterator pos); // No impl
    Iterator erase(Iterator begin, Iterator end); // Not Implemented

public:
    QListModel<T> &operator=(const QList<T> &l);
    inline QList<T> operator+(const QList<T> &l) const
    { QList<T> nt = *this; nt += l; return nt; }

    inline bool operator==(const QList<T> &other) const
    { return QList<T>::operator ==(other); }
    inline bool operator!=(const QList<T> &other) const
    { return QList<T>::operator !=(other); }

    inline QListModel<T> &operator+=(const QList<T> &l)
    { append(l); return *this; }
    inline QListModel<T> &operator<<(const QList<T> &l)
    { append(l); return *this; }

    inline QListModel<T> &operator+=(const T &o)
    { append(o); return *this; }
    inline QListModel<T> &operator<<(const T &o)
    { append(o); return *this; }
};

template <typename T>
int QListModel<T>::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : QList<T>::count();
}

template <typename T>
QVariant QListModel<T>::data(const QModelIndex &index, int role) const
{
    if (ModelDataRole != role) {
        return QVariant();
    } else if (!index.isValid() || index.model() != this) {
        return QVariant();
    } else if (QList<T>::count() <= index.row()) {
        return QVariant();
    }

    return QVariant::fromValue(QList<T>::at(index.row()));
}

template<typename T>
T QListModel<T>::value(const QModelIndex &index) const
{
    return QList<T>::value(index.row());
}

template<typename T>
T QListModel<T>::value(const QModelIndex &index, const T &defaultValue) const
{
    return QList<T>::value(index.row(), defaultValue);
}

template<typename T>
T QListModel<T>::value(int i) const
{
    return QList<T>::value(i);
}

template<typename T>
T QListModel<T>::value(int i, const T &defaultValue) const
{
    return QList<T>::value(i, defaultValue);
}

template <typename T>
void QListModel<T>::append(const QList<T> &l)
{
    if (l.isEmpty())
        return;

    int f = QList<T>::count();
    int t = f + l.count() - 1;
    beginInsertRows(QModelIndex(), f, t);
    QList<T>::append(l);
    endInsertRows();
}

template <typename T>
void QListModel<T>::prepend(const T &t)
{
    beginInsertRows(QModelIndex(), 0, 0);
    QList<T>::prepend(t);
    endInsertRows();
}

template <typename T>
void QListModel<T>::append(const T &t)
{
    int r = QList<T>::count();
    beginInsertRows(QModelIndex(), r, r);
    QList<T>::append(t);
    endInsertRows();
}

template <typename T>
void QListModel<T>::push_front(const T &t)
{
    beginInsertRows(QModelIndex(), 0, 0);
    QList<T>::push_front(t);
    endInsertRows();
}

template <typename T>
void QListModel<T>::push_back(const T &t)
{
    int r = QList<T>::count();
    beginInsertRows(QModelIndex(), r, r);
    QList<T>::push_back(t);
    endInsertRows();
}

template <typename T>
void QListModel<T>::replace(int i, const T &t)
{
    QModelIndex ii = this->index(i);
    if (!ii.isValid())
        return;

    QList<T>::replace(i, t);

    emit dataChanged(ii, ii, _roles);
}

template <typename T>
void QListModel<T>::insert(int i, const T &t)
{
    int r = qMax(0, qMin(i, QList<T>::count()));
    beginInsertRows(QModelIndex(), r, r);
    QList<T>::insert(i, t);
    endInsertRows();
}

template <typename T>
bool QListModel<T>::removeOne(const T &t)
{
    QObjectList::iterator p = QList<T>::begin();
    QObjectList::iterator end = QList<T>::end();

    for (int i = 0; p != end; ++p, ++i) {
        if (t == *p) {
            beginRemoveRows(QModelIndex(), i, i);
            QList<T>::erase(p);
            endRemoveRows();

            return true;
        }
    }

    return false;
}

template <typename T>
int QListModel<T>::removeAll(const T &t)
{
    QObjectList::iterator null;
    QObjectList::iterator f = null;
    QObjectList::iterator l = null;
    QObjectList::iterator p = QList<T>::begin();
    QObjectList::iterator end = QList<T>::end();

    int c = 0;
    int fpos = 0;
    int lpos = 0;

    for (int i = 0; p != end; ++p, ++i) {
        if (t == *p) {
            if (f == null) {
                fpos = i;
                f = p;
            }
            lpos = i;
            l = p;

        } else if (f != null) {
            beginRemoveRows(QModelIndex(), fpos - c, lpos - c);
            QList<T>::erase(f, l);
            endRemoveRows();

            c += lpos - fpos + 1;

            f = null;
            l = null;
        }
    }

    if (f != null) {
        beginRemoveRows(QModelIndex(), fpos - c, lpos - c);
        QList<T>::erase(f, l);
        endRemoveRows();

        c += lpos - fpos + 1;
    }

    return c;
}

template <typename T>
void QListModel<T>::pop_front()
{
    beginRemoveRows(QModelIndex(), 0, 0);
    QList<T>::pop_front();
    endRemoveRows();
}

template <typename T>
void QListModel<T>::pop_back()
{
    int r = QList<T>::count() - 1;
    beginRemoveRows(QModelIndex(), r, r);
    QList<T>::removeLast();
    endRemoveRows();
}

template <typename T>
void QListModel<T>::removeAt(int i)
{
    beginRemoveRows(QModelIndex(), i, i);
    QList<T>::removeAt(i);
    endRemoveRows();
}

template <typename T>
void QListModel<T>::removeFirst()
{
    beginRemoveRows(QModelIndex(), 0, 0);
    QList<T>::removeFirst();
    endRemoveRows();
}

template <typename T>
void QListModel<T>::removeLast()
{
    int r = QList<T>::count() - 1;
    beginRemoveRows(QModelIndex(), r, r);
    QList<T>::removeLast();
    endRemoveRows();
}

template <typename T>
T QListModel<T>::takeAt(int i)
{
    beginRemoveRows(QModelIndex(), i, i);
    T t = QList<T>::takeAt(i);
    endRemoveRows();

    return t;
}

template <typename T>
T QListModel<T>::takeFirst()
{
    beginRemoveRows(QModelIndex(), 0, 0);
    T t = QList<T>::takeFirst();
    endRemoveRows();

    return t;
}

template <typename T>
T QListModel<T>::takeLast()
{
    int r = QList<T>::count() - 1;
    beginRemoveRows(QModelIndex(), r, r);
    T t = QList<T>::takeLast();
    endRemoveRows();

    return t;
}

template <typename T>
void QListModel<T>::swap(int i, int j)
{
    QList<T>::swap(i, j);

    QModelIndex ii = index(i);
    QModelIndex ji = index(j);

    emit dataChanged(ii, ii, _roles);
    emit dataChanged(ji, ji, _roles);
}

template <typename T>
void QListModel<T>::swap(QList<T> &list)
{
    beginResetModel();
    QList<T>::swap(list);
    endResetModel();
}

template <typename T>
void QListModel<T>::move(int from, int to)
{
    beginMoveRows(QModelIndex(), from, from, QModelIndex(), to);
    QList<T>::move(from, to);
    endMoveRows();
}

template<typename T>
void QListModel<T>::clear()
{
    beginResetModel();
    QList<T>::clear();
    endResetModel();
}

template<typename T>
void QListModel<T>::deleteAll()
{
    beginResetModel();
    qDeleteAll(*this);
    QList<T>::clear();
    endResetModel();
}

template<typename T>
QListModel<T> &QListModel<T>::operator=(const QList<T> &l)
{
    beginResetModel();
    QList<T> tmp(l);
    tmp.swap(*this);
    endResetModel();

    return *this;
}

#endif // QLISTMODEL_H

#ifndef QCXXLISTMODEL_H
#define QCXXLISTMODEL_H

#include <QAbstractListModel>

#if defined(QT_TESTLIB_LIB)
#  define QCXXLISTMODEL_ASSERT(x)
#else
#  define QCXXLISTMODEL_ASSERT(x) Q_ASSERT(x)
#endif

namespace Internal {

template <typename T>
struct QCxxListGuard
{
};

class QCxxListModelPrivate;
class QCxxListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QCxxListModel)
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(bool countEnabled READ isCountEnabled NOTIFY countEnabledChanged)

public:
    explicit QCxxListModel(QObject *parent = nullptr);
    virtual ~QCxxListModel();
protected:
    QScopedPointer<QCxxListModelPrivate> d_ptr;

public:
    enum ModelDataRoles {
        ModelDataRole = Qt::UserRole + 1,
    };
    QHash<int, QByteArray> roleNames() const override;

signals:
    void countChanged();
protected:
    void _q_resetCount();

signals:
    void countEnabledChanged();
public:
    bool isCountEnabled() const;
public:
    void setCountEnabled(bool y);

protected:
    void _q_sync(const QModelIndex &tl, const QModelIndex &br);
};

} // namespace Internal

template <typename T>
class QCxxListModel : public Internal::QCxxListModel, public QList<T*>
{
    typedef T *V;
    typedef Internal::QCxxListGuard<T> Guard;

public:
    QCxxListModel(const QList<V> &l, QObject *parent = nullptr)
        : Internal::QCxxListModel(parent), QList<V>(l) { }
    explicit QCxxListModel(QObject *parent = nullptr)
        : Internal::QCxxListModel(parent) { }

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

public:
    V value(const QModelIndex &index) const;
    V value(const QModelIndex &index, const V &defaultValue) const;

    V value(int i) const;
    V value(int i, const V &defaultValue) const;

public:
    void append(const QList<V> &l);

    void prepend(const V &v);
    void append(const V &v);

    void push_front(const V &v);
    void push_back(const V &v);

    void replace(int i, const V &v);
    void insert(int i, const V &v);

    bool removeOne(const V &v);
    int removeAll(const V &v);

    void pop_front();
    void pop_back();

    void removeAt(int i);
    void removeFirst();
    void removeLast();

    V takeAt(int i);
    V takeFirst();
    V takeLast();

    void swap(int i, int j);
    void swap(QList<V> &list);
    void move(int from, int to);

    void clear();

public: // Extra methods
    void deleteAll();

public: // Disabled stl methods
    typedef typename QList<V>::iterator         Iterator;
    typedef typename QList<V>::reverse_iterator ReverseIterator;

    Iterator begin(); // Not Implemented
    Iterator end(); // Not Implemented

    ReverseIterator rbegin(); // Not Implemented
    ReverseIterator rend(); // Not Implemented

    Iterator insert(Iterator before, const V &t); // Not Implemented
    Iterator erase(Iterator pos); // No Implemented
    Iterator erase(Iterator begin, Iterator end); // Not Implemented

public:
    QCxxListModel<T> &operator=(const QList<V> &l);
    inline QList<V> operator+(const QList<V> &others) const
    { QList<V> l = *this; l.append(others); return l; }

    inline bool operator==(const QList<V> &other) const
    { return QList<V>::operator==(other); }
    inline bool operator!=(const QList<V> &other) const
    { return QList<V>::operator!=(other); }

    inline QCxxListModel<T> &operator+=(const QList<V> &l)
    { append(l); return *this; }
    inline QCxxListModel<T> &operator<<(const QList<V> &l)
    { append(l); return *this; }

    inline QCxxListModel<T> &operator+=(const V &o)
    { append(o); return *this; }
    inline QCxxListModel<T> &operator<<(const V &o)
    { append(o); return *this; }

public:
    inline const QList<V> &ref() const { return *this; }
};

template <typename T>
int QCxxListModel<T>::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : QList<V>::count();
}

template <typename T>
QVariant QCxxListModel<T>::data(const QModelIndex &index, int role) const
{
    if ((ModelDataRole != role)
            || !index.isValid()
            || (index.model() != this)
            || (index.row() >= QList<V>::count())) {
        return QVariant();
    }

    return QVariant::fromValue(QList<V>::at(index.row()));
}

template<typename T>
QModelIndex QCxxListModel<T>::index(int row, int column, const QModelIndex &parent) const
{
    if ((row < 0)
            || (column != 0)
            || (row >= QList<V>::count())
            || parent.isValid()) {
        return QModelIndex();
    }

    return createIndex(row, 0, QList<V>::at(row));
}

template<typename T>
typename QCxxListModel<T>::V QCxxListModel<T>::value(const QModelIndex &index) const
{
    QCXXLISTMODEL_ASSERT(index.model() == this);

    return QList<V>::value(index.row());
}

template<typename T>
typename QCxxListModel<T>::V QCxxListModel<T>::value(const QModelIndex &index, const V &defaultValue) const
{
    QCXXLISTMODEL_ASSERT(index.model() == this);

    return QList<V>::value(index.row(), defaultValue);
}

template<typename T>
typename QCxxListModel<T>::V QCxxListModel<T>::value(int i) const
{
    return QList<V>::value(i);
}

template<typename T>
typename QCxxListModel<T>::V QCxxListModel<T>::value(int i, const V &defaultValue) const
{
    return QList<V>::value(i, defaultValue);
}

template <typename T>
void QCxxListModel<T>::append(const QList<V> &l)
{
    if (l.isEmpty())
        return;

    int f = QList<V>::count();
    int t = f + l.count() - 1;
    beginInsertRows(QModelIndex(), f, t);
    QList<V>::append(l);
    endInsertRows();
    _q_resetCount();
}

template <typename T>
void QCxxListModel<T>::prepend(const V &v)
{
    beginInsertRows(QModelIndex(), 0, 0);
    QList<V>::prepend(v);
    endInsertRows();
    _q_resetCount();
}

template <typename T>
void QCxxListModel<T>::append(const V &v)
{
    int r = QList<V>::count();
    beginInsertRows(QModelIndex(), r, r);
    QList<V>::append(v);
    endInsertRows();
    _q_resetCount();
}

template <typename T>
void QCxxListModel<T>::push_front(const V &v)
{
    beginInsertRows(QModelIndex(), 0, 0);
    QList<V>::push_front(v);
    endInsertRows();
    _q_resetCount();
}

template <typename T>
void QCxxListModel<T>::push_back(const V &v)
{
    int r = QList<V>::count();
    beginInsertRows(QModelIndex(), r, r);
    QList<V>::push_back(v);
    endInsertRows();
    _q_resetCount();
}

template <typename T>
void QCxxListModel<T>::replace(int i, const V &v)
{
    QCXXLISTMODEL_ASSERT(i >= 0);
    QCXXLISTMODEL_ASSERT(i < QList<V>::count());

    QModelIndex x = index(i, 0);
    if (!x.isValid()) {
        return;
    }

    QList<V>::replace(i, v); _q_sync(x, x);
}

template <typename T>
void QCxxListModel<T>::insert(int i, const V &v)
{
    QCXXLISTMODEL_ASSERT(i >= 0);
    QCXXLISTMODEL_ASSERT(i <= QList<V>::count());

    beginInsertRows(QModelIndex(), i, i);
    QList<V>::insert(i, v);
    endInsertRows();
    _q_resetCount();
}

template <typename T>
bool QCxxListModel<T>::removeOne(const V &v)
{
    typename QList<V>::iterator p = QList<V>::begin();
    typename QList<V>::iterator end = QList<V>::end();

    for (int i = 0; p != end; ++p, ++i) {
        if (*p == v) {
            beginRemoveRows(QModelIndex(), i, i);
            QList<V>::erase(p);
            endRemoveRows();
            _q_resetCount();

            return true;
        }
    }

    return false;
}

template <typename T>
int QCxxListModel<T>::removeAll(const V &v)
{
    typename QList<V>::iterator null;
    typename QList<V>::iterator f = null;
    typename QList<V>::iterator l = null;
    typename QList<V>::iterator p = QList<V>::begin();
    typename QList<V>::iterator end = QList<V>::end();

    int c = 0;
    int fpos = 0;
    int lpos = 0;

    for (int i = 0; p != end; ++p, ++i) {
        if (v == *p) {
            if (f == null) {
                fpos = i;
                f = p;
            }
            lpos = i;
            l = p;

        } else if (f != null) {
            beginRemoveRows(QModelIndex(), fpos - c, lpos - c);
            QList<V>::erase(f, ++l);
            endRemoveRows();

            c += lpos - fpos + 1;

            f = null;
            l = null;
        }
    }

    if (f != null) {
        beginRemoveRows(QModelIndex(), fpos - c, lpos - c);
        QList<V>::erase(f, ++l);
        endRemoveRows();

        c += lpos - fpos + 1;
    }

    _q_resetCount();

    return c;
}

template <typename T>
void QCxxListModel<T>::pop_front()
{
    QCXXLISTMODEL_ASSERT(QList<V>::count() > 0);

    beginRemoveRows(QModelIndex(), 0, 0);
    QList<V>::pop_front();
    endRemoveRows();
    _q_resetCount();
}

template <typename T>
void QCxxListModel<T>::pop_back()
{
    QCXXLISTMODEL_ASSERT(QList<V>::count() > 0);

    int r = QList<V>::count() - 1;
    beginRemoveRows(QModelIndex(), r, r);
    QList<V>::pop_back();
    endRemoveRows();
    _q_resetCount();
}

template <typename T>
void QCxxListModel<T>::removeAt(int i)
{
    QCXXLISTMODEL_ASSERT(i >= 0);
    QCXXLISTMODEL_ASSERT(i < QList<V>::count());

    beginRemoveRows(QModelIndex(), i, i);
    QList<V>::removeAt(i);
    endRemoveRows();
    _q_resetCount();
}

template <typename T>
void QCxxListModel<T>::removeFirst()
{
    QCXXLISTMODEL_ASSERT(QList<V>::count() > 0);

    beginRemoveRows(QModelIndex(), 0, 0);
    QList<V>::removeFirst();
    endRemoveRows();
    _q_resetCount();
}

template <typename T>
void QCxxListModel<T>::removeLast()
{
    QCXXLISTMODEL_ASSERT(QList<V>::count() > 0);

    int r = QList<V>::count() - 1;
    beginRemoveRows(QModelIndex(), r, r);
    QList<V>::removeLast();
    endRemoveRows();
    _q_resetCount();
}

template <typename T>
typename QCxxListModel<T>::V QCxxListModel<T>::takeAt(int i)
{
    QCXXLISTMODEL_ASSERT(i >= 0);
    QCXXLISTMODEL_ASSERT(i < QList<V>::count());

    beginRemoveRows(QModelIndex(), i, i);
    V v = QList<V>::takeAt(i);
    endRemoveRows();
    _q_resetCount();

    return v;
}

template <typename T>
typename QCxxListModel<T>::V QCxxListModel<T>::takeFirst()
{
    QCXXLISTMODEL_ASSERT(QList<V>::count() > 0);

    beginRemoveRows(QModelIndex(), 0, 0);
    V v = QList<V>::takeFirst();
    endRemoveRows();
    _q_resetCount();

    return v;
}

template <typename T>
typename QCxxListModel<T>::V QCxxListModel<T>::takeLast()
{
    QCXXLISTMODEL_ASSERT(QList<V>::count() > 0);

    int r = QList<V>::count() - 1;
    beginRemoveRows(QModelIndex(), r, r);
    V v = QList<V>::takeLast();
    endRemoveRows();
    _q_resetCount();

    return v;
}

template <typename T>
void QCxxListModel<T>::swap(int i, int j)
{
    if (i == j) {
        return;
    }

    QCXXLISTMODEL_ASSERT(i >= 0);
    QCXXLISTMODEL_ASSERT(i < QList<V>::count());

    QCXXLISTMODEL_ASSERT(J >= 0);
    QCXXLISTMODEL_ASSERT(j < QList<V>::count());

    QList<V>::swap(i, j);

    QModelIndex ii = index(i, 0); _q_sync(ii, ii);
    QModelIndex ji = index(j, 0); _q_sync(ji, ji);
}

template <typename T>
void QCxxListModel<T>::swap(QList<V> &l)
{
    /*
    if (l.d == this->d) {
        return *this;
    }
    */

    beginResetModel();
    QList<V>::swap(l);
    endResetModel();
    _q_resetCount();
}

template <typename T>
void QCxxListModel<T>::move(int from, int to)
{
    if (from == to) {
        return;
    }

    QCXXLISTMODEL_ASSERT(from >= 0);
    QCXXLISTMODEL_ASSERT(from < QList<V>::count());

    QCXXLISTMODEL_ASSERT(to >= 0);
    QCXXLISTMODEL_ASSERT(to < QList<V>::count());

    QModelIndex p;
    int t = (from < to) ? (to + 1) : to;
    if (beginMoveRows(p, from, from, p, t)) {
        QList<V>::move(from, to);
        endMoveRows();
    }
}

template<typename T>
void QCxxListModel<T>::clear()
{
    if (isEmpty()) {
        return;
    }

    beginResetModel();
    QList<V>::clear();
    endResetModel();
    _q_resetCount();
}

template<typename T>
void QCxxListModel<T>::deleteAll()
{
    if (isEmpty()) {
        return;
    }

    beginResetModel();
    qDeleteAll(ref());
    QList<V>::clear();
    endResetModel();
    _q_resetCount();
}

template<typename T>
QCxxListModel<T> &QCxxListModel<T>::operator=(const QList<V> &l)
{
    /*
    if (l.d == this->d) {
        return *this;
    }
    */

    beginResetModel();
    QList<V> tmp(l);
    tmp.swap(*this);
    endResetModel();
    _q_resetCount();

    return *this;
}

#endif // QCXXLISTMODEL_H

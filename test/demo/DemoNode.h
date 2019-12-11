#ifndef DEMONODE_H
#define DEMONODE_H

#include <QObject>

class DemoNodePrivate;
class DemoNode : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DemoNode)

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    explicit DemoNode(QObject *parent = nullptr);
    virtual ~DemoNode();
protected:
    QScopedPointer<DemoNodePrivate> d_ptr;

signals:
    void textChanged();
public:
    void setText(const QString &text);
public:
    QString text() const;
};

#endif // DEMONODE_H

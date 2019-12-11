# 用于 QML 的 C++ 列表模型

本项目维护了一个用于 QML 工程的 C++ 列表模型 `QCxxListModel`。它继承自 `QList` 和 `QAbstractListModel`，这将提供一种新的方式：在 C++ 中，将其作为 `QList` 来使用；在 QML 中，将其作为 `QAbstractListModel` 来展示。

### 使用方式：
在 C++ 中，`QCxxListModel` 与 `QList` 的使用方式基本一致：
``` cpp
QList<DemoNode *>         nodeList;
QCxxListModel<DemoNode *> nodeModel;
...
nodeList.append(node);
nodeModel.append(node);
...
nodeList.removeOne(node);
nodeModel.removeOne(node);
...
DemoNode *node = nodeList.value(0);
DemoNode *node = nodeModel.value(0);
...
```
由于迭代器操作无法触发模型的方法、信号，列表模型屏蔽了所有与迭代器操作相关的方法。这也导致了 C++11 的 for 循环无法直接使用。如果需要遍历列表模型，可以通过 `QCxxListModel::ref()` 方法，获取一个列表容器的引用：
``` cpp
for (DemoNode *node : nodeModel.ref()) {
    node ...
}
```
如果想将列表模型当做类属性，暴露给 QML，可以参考下面的写法：
```cpp
class DemoCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel *nodes READ nodes CONSTANT)
    ...
    QAbstractListModel *nodes() const
    {
        return const_cast<QCxxListModel<DemoNode *> *>(&nodeModel);
    }
    ...
    QCxxListModel<DemoNode *> nodeModel;
};
```

这样，在 QML 中，我们就可以将其作为一个模型来使用了：
```qml
Item {
    DemoCore {
        id: core
    }
    ListView {
        model: core.nodes
        delegate: Item {
            text: modelData.text // modelData -> DemoNode *
        }
    }
}

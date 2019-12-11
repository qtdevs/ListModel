#include "ListModelTest.h"

#include <QtCore>
#include <QtTest>

#include "QCxxListModel.h"
#include "ListModelTester.h"

// Macros

#define InitModel() \
    QCxxListModel<QObject *> model; \
    model.setCountEnabled(true); \
    auto tester = new ListModelTester(&model)

#define VerifyCountSignal(value) QVERIFY(tester->count() == value)
#define VerifyChangedSize(value) QVERIFY(tester->changedSize() == value)
#define VerifyRowsChanged(i, from, to) QVERIFY(tester->isChanged(i, from, to))

ListModelTest::ListModelTest()
{
    for (int i = 0; i < 100; ++i) {
        objects.append(new QObject(this));
    }
}

void ListModelTest::appendListCase()
{
    InitModel();

    QObjectList list1 { objects[0], objects[1] };
    QObjectList list2 { objects[2], objects[3] };

    model.append(list1);
    VerifyCountSignal(1);
    model.append(list2);
    VerifyCountSignal(2);

    QVERIFY(model.count() == 4);

    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);
    QVERIFY(model.value(2) == objects[2]);
    QVERIFY(model.value(3) == objects[3]);
}

void ListModelTest::prependCase()
{
    InitModel();

    model.prepend(objects[0]);
    VerifyCountSignal(1);
    model.prepend(objects[1]);
    VerifyCountSignal(2);
    model.prepend(objects[2]);
    VerifyCountSignal(3);

    QVERIFY(model.count() == 3);

    QVERIFY(model.value(0) == objects[2]);
    QVERIFY(model.value(1) == objects[1]);
    QVERIFY(model.value(2) == objects[0]);
}

void ListModelTest::appendCase()
{
    InitModel();

    model.append(objects[0]);
    VerifyCountSignal(1);
    model.append(objects[1]);
    VerifyCountSignal(2);
    model.append(objects[2]);
    VerifyCountSignal(3);

    QVERIFY(model.count() == 3);

    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);
    QVERIFY(model.value(2) == objects[2]);
}

void ListModelTest::push_frontCase()
{
    InitModel();

    model.push_front(objects[0]);
    VerifyCountSignal(1);
    model.push_front(objects[1]);
    VerifyCountSignal(2);
    model.push_front(objects[2]);
    VerifyCountSignal(3);

    QVERIFY(model.count() == 3);

    QVERIFY(model.value(0) == objects[2]);
    QVERIFY(model.value(1) == objects[1]);
    QVERIFY(model.value(2) == objects[0]);
}

void ListModelTest::push_backCase()
{
    InitModel();

    model.push_back(objects[0]);
    VerifyCountSignal(1);
    model.push_back(objects[1]);
    VerifyCountSignal(2);
    model.push_back(objects[2]);
    VerifyCountSignal(3);

    QVERIFY(model.count() == 3);

    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);
    QVERIFY(model.value(2) == objects[2]);
}

void ListModelTest::replaceCase()
{
    InitModel();

    for (int i = 0; i < 3; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    model.replace(0, objects[3]);
    VerifyCountSignal(0);
    QVERIFY(model.value(0) == objects[3]);
    model.replace(1, objects[4]);
    VerifyCountSignal(0);
    QVERIFY(model.value(1) == objects[4]);
    model.replace(2, objects[5]);
    VerifyCountSignal(0);
    QVERIFY(model.value(2) == objects[5]);

    QVERIFY(model.count() == 3);

    QVERIFY(model.value(0) == objects[3]);
    QVERIFY(model.value(1) == objects[4]);
    QVERIFY(model.value(2) == objects[5]);
}

void ListModelTest::insertCase()
{
    InitModel();

    for (int i = 0; i < 3; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    model.insert(0, objects[3]);
    VerifyCountSignal(1);
    QVERIFY(model.value(0) == objects[3]);
    model.insert(2, objects[4]);
    VerifyCountSignal(2);
    QVERIFY(model.value(2) == objects[4]);
    model.insert(4, objects[5]);
    VerifyCountSignal(3);
    QVERIFY(model.value(4) == objects[5]);

    QVERIFY(model.count() == 6);

    QVERIFY(model.value(0) == objects[3]);
    QVERIFY(model.value(1) == objects[0]);
    QVERIFY(model.value(2) == objects[4]);
    QVERIFY(model.value(3) == objects[1]);
    QVERIFY(model.value(4) == objects[5]);
    QVERIFY(model.value(5) == objects[2]);
}

void ListModelTest::removeOneCase()
{
    InitModel();

    for (int i = 0; i < 6; ++i) {
        model.append(objects[i]);
        model.append(objects[i]);
    }
    tester->resetCount();

    model.removeOne(objects[0]);
    VerifyCountSignal(1);
    model.removeOne(objects[2]);
    VerifyCountSignal(2);
    model.removeOne(objects[4]);
    VerifyCountSignal(3);

    QVERIFY(model.count() == 9);

    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);
    QVERIFY(model.value(2) == objects[1]);
    QVERIFY(model.value(3) == objects[2]);
    QVERIFY(model.value(4) == objects[3]);
    QVERIFY(model.value(5) == objects[3]);
    QVERIFY(model.value(6) == objects[4]);
    QVERIFY(model.value(7) == objects[5]);
    QVERIFY(model.value(8) == objects[5]);
}

void ListModelTest::removeAllCase()
{
    InitModel();

    for (int i = 0; i < 6; ++i) {
        model.append(objects[i]);
    }
    for (int i = 0; i < 6; ++i) {
        model.append(objects[i]);
        model.append(objects[i]);
    }
    for (int i = 0; i < 6; ++i) {
        model.append(objects[i]);
        model.append(objects[i]);
        model.append(objects[i]);
    }
    tester->resetCount();

    model.removeAll(objects[0]);
    VerifyCountSignal(1);
    model.removeAll(objects[2]);
    VerifyCountSignal(2);
    model.removeAll(objects[4]);
    VerifyCountSignal(3);

    QVERIFY(model.count() == 18);

    QVERIFY(model.value( 0) == objects[1]);
    QVERIFY(model.value( 1) == objects[3]);
    QVERIFY(model.value( 2) == objects[5]);
    QVERIFY(model.value( 3) == objects[1]);
    QVERIFY(model.value( 4) == objects[1]);
    QVERIFY(model.value( 5) == objects[3]);
    QVERIFY(model.value( 6) == objects[3]);
    QVERIFY(model.value( 7) == objects[5]);
    QVERIFY(model.value( 8) == objects[5]);
    QVERIFY(model.value( 9) == objects[1]);
    QVERIFY(model.value(10) == objects[1]);
    QVERIFY(model.value(11) == objects[1]);
    QVERIFY(model.value(12) == objects[3]);
    QVERIFY(model.value(13) == objects[3]);
    QVERIFY(model.value(14) == objects[3]);
    QVERIFY(model.value(15) == objects[5]);
    QVERIFY(model.value(16) == objects[5]);
    QVERIFY(model.value(17) == objects[5]);
}

void ListModelTest::pop_frontCase()
{
    InitModel();

    for (int i = 0; i < 3; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    model.pop_front();
    VerifyCountSignal(1);
    QVERIFY(model.value(0) == objects[1]);
    QVERIFY(model.value(1) == objects[2]);
    model.pop_front();
    VerifyCountSignal(2);
    QVERIFY(model.value(0) == objects[2]);
    model.pop_front();
    VerifyCountSignal(3);

    QVERIFY(model.count() == 0);
}

void ListModelTest::pop_backCase()
{
    InitModel();

    for (int i = 0; i < 3; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    model.pop_back();
    VerifyCountSignal(1);
    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);
    model.pop_back();
    VerifyCountSignal(2);
    QVERIFY(model.value(0) == objects[0]);
    model.pop_back();
    VerifyCountSignal(3);

    QVERIFY(model.count() == 0);
}

void ListModelTest::removeAtCase()
{
    InitModel();

    for (int i = 0; i < 6; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    model.removeAt(0);
    VerifyCountSignal(1);
    model.removeAt(1);
    VerifyCountSignal(2);
    model.removeAt(2);
    VerifyCountSignal(3);

    QVERIFY(model.count() == 3);

    QVERIFY(model.value(0) == objects[1]);
    QVERIFY(model.value(1) == objects[3]);
    QVERIFY(model.value(2) == objects[5]);
}

void ListModelTest::removeFirstCase()
{
    InitModel();

    for (int i = 0; i < 3; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    model.removeFirst();
    VerifyCountSignal(1);
    QVERIFY(model.value(0) == objects[1]);
    QVERIFY(model.value(1) == objects[2]);
    model.removeFirst();
    VerifyCountSignal(2);
    QVERIFY(model.value(0) == objects[2]);
    model.removeFirst();
    VerifyCountSignal(3);

    QVERIFY(model.count() == 0);
}

void ListModelTest::removeLastCase()
{
    InitModel();

    for (int i = 0; i < 3; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    model.removeLast();
    VerifyCountSignal(1);
    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);
    model.removeLast();
    VerifyCountSignal(2);
    QVERIFY(model.value(0) == objects[0]);
    model.removeLast();
    VerifyCountSignal(3);

    QVERIFY(model.count() == 0);
}

void ListModelTest::takeAtCase()
{
    InitModel();

    for (int i = 0; i < 6; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    QVERIFY(model.takeAt(0) == objects[0]);
    VerifyCountSignal(1);
    QVERIFY(model.takeAt(1) == objects[2]);
    VerifyCountSignal(2);
    QVERIFY(model.takeAt(2) == objects[4]);
    VerifyCountSignal(3);

    QVERIFY(model.count() == 3);

    QVERIFY(model.value(0) == objects[1]);
    QVERIFY(model.value(1) == objects[3]);
    QVERIFY(model.value(2) == objects[5]);
}

void ListModelTest::takeFirstCase()
{
    InitModel();

    for (int i = 0; i < 3; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    QVERIFY(model.takeFirst() == objects[0]);
    VerifyCountSignal(1);
    QVERIFY(model.value(0) == objects[1]);
    QVERIFY(model.value(1) == objects[2]);

    QVERIFY(model.takeFirst() == objects[1]);
    VerifyCountSignal(2);
    QVERIFY(model.value(0) == objects[2]);

    QVERIFY(model.takeFirst() == objects[2]);
    VerifyCountSignal(3);

    QVERIFY(model.count() == 0);
}

void ListModelTest::takeLastCase()
{
    InitModel();

    for (int i = 0; i < 3; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    QVERIFY(model.takeLast() == objects[2]);
    VerifyCountSignal(1);
    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);

    QVERIFY(model.takeLast() == objects[1]);
    VerifyCountSignal(2);
    QVERIFY(model.value(0) == objects[0]);

    QVERIFY(model.takeLast() == objects[0]);
    VerifyCountSignal(3);

    QVERIFY(model.count() == 0);
}

void ListModelTest::swapCase()
{
    InitModel();

    for (int i = 0; i < 6; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    model.swap(0, 1);
    QVERIFY(model.value(0) == objects[1]);
    QVERIFY(model.value(1) == objects[0]);
    model.swap(1, 2);
    QVERIFY(model.value(1) == objects[2]);
    QVERIFY(model.value(2) == objects[0]);
    model.swap(4, 5);
    QVERIFY(model.value(4) == objects[5]);
    QVERIFY(model.value(5) == objects[4]);

    VerifyCountSignal(0);

    QVERIFY(model.value(0) == objects[1]);
    QVERIFY(model.value(1) == objects[2]);
    QVERIFY(model.value(2) == objects[0]);
    QVERIFY(model.value(3) == objects[3]);
    QVERIFY(model.value(4) == objects[5]);
    QVERIFY(model.value(5) == objects[4]);

    QVERIFY(model.count() == 6);
}

void ListModelTest::swapListCase()
{
    InitModel();

    QObjectList list { objects[0], objects[1], objects[2] };

    for (int i = 0; i < 6; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    model.swap(list);

    VerifyCountSignal(1);

    QVERIFY(list.value(0) == objects[0]);
    QVERIFY(list.value(1) == objects[1]);
    QVERIFY(list.value(2) == objects[2]);
    QVERIFY(list.value(3) == objects[3]);
    QVERIFY(list.value(4) == objects[4]);
    QVERIFY(list.value(5) == objects[5]);

    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);
    QVERIFY(model.value(2) == objects[2]);

    QVERIFY(model.count() == 3);
}

void ListModelTest::moveCase()
{
    InitModel();

    for (int i = 0; i < 6; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    model.move(0, 1);
    QVERIFY(model.value(0) == objects[1]);
    QVERIFY(model.value(1) == objects[0]);
    model.move(1, 2);
    QVERIFY(model.value(1) == objects[2]);
    QVERIFY(model.value(2) == objects[0]);
    model.move(4, 5);
    QVERIFY(model.value(4) == objects[5]);
    QVERIFY(model.value(5) == objects[4]);

    model.move(5, 4);
    QVERIFY(model.value(4) == objects[4]);
    QVERIFY(model.value(5) == objects[5]);
    model.move(2, 1);
    QVERIFY(model.value(1) == objects[0]);
    QVERIFY(model.value(2) == objects[2]);
    model.move(1, 0);
    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);

    VerifyCountSignal(0);

    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);
    QVERIFY(model.value(2) == objects[2]);
    QVERIFY(model.value(3) == objects[3]);
    QVERIFY(model.value(4) == objects[4]);
    QVERIFY(model.value(5) == objects[5]);

    QVERIFY(model.count() == 6);
}

void ListModelTest::clearCase()
{
    InitModel();

    int destroies = 0;
    for (int i = 0; i < 6; ++i) {
        model.append(objects[i]);
        connect(objects[i], &QObject::destroyed,
                this, [&] { ++destroies; });
    }
    tester->resetCount();

    model.clear();
    VerifyCountSignal(1);

    QTRY_COMPARE(destroies, 0);
    QVERIFY(model.count() == 0);
}

void ListModelTest::deleteAllCase()
{
    InitModel();

    int destroies = 0;
    for (int i = 0; i < 6; ++i) {
        QObject *o = new QObject(this);
        model.append(o);
        connect(o, &QObject::destroyed,
                this, [&] { ++destroies; });
    }
    tester->resetCount();

    model.deleteAll();
    VerifyCountSignal(1);

    QTRY_COMPARE(destroies, 6);
    QVERIFY(model.count() == 0);
}

void ListModelTest::operatorAssignmentCase()
{
    InitModel();

    QObjectList list { objects[0], objects[1], objects[2] };

    for (int i = 0; i < 6; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    model = list;

    VerifyCountSignal(1);

    QVERIFY(list.value(0) == objects[0]);
    QVERIFY(list.value(1) == objects[1]);
    QVERIFY(list.value(2) == objects[2]);

    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);
    QVERIFY(model.value(2) == objects[2]);

    QVERIFY(model.count() == 3);
}

void ListModelTest::operatorAdditionCase()
{
    InitModel();

    QObjectList list { objects[0], objects[1], objects[2] };

    for (int i = 0; i < 3; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    list = model + list;

    VerifyCountSignal(0);

    QVERIFY(list.value(0) == objects[0]);
    QVERIFY(list.value(1) == objects[1]);
    QVERIFY(list.value(2) == objects[2]);
    QVERIFY(list.value(3) == objects[0]);
    QVERIFY(list.value(4) == objects[1]);
    QVERIFY(list.value(5) == objects[2]);

    QVERIFY(list.count() == 6);
}

void ListModelTest::operatorEqualToCase()
{
    InitModel();

    QObjectList list { objects[0], objects[1], objects[2] };

    for (int i = 0; i < 3; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    QVERIFY(model == list);
    VerifyCountSignal(0);
}

void ListModelTest::operatorNotEqualCase()
{
    InitModel();

    QObjectList list { objects[1], objects[1], objects[2] };

    for (int i = 0; i < 3; ++i) {
        model.append(objects[i]);
    }
    tester->resetCount();

    QVERIFY(model != list);
    VerifyCountSignal(0);
}

void ListModelTest::operatorAdditionAssignmentListCase()
{
    InitModel();

    QObjectList list { objects[0], objects[1], objects[2] };

    model += list;
    VerifyCountSignal(1);
    model += list;
    VerifyCountSignal(2);

    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);
    QVERIFY(model.value(2) == objects[2]);
    QVERIFY(model.value(3) == objects[0]);
    QVERIFY(model.value(4) == objects[1]);
    QVERIFY(model.value(5) == objects[2]);

    QVERIFY(model.count() == 6);
}

void ListModelTest::operatorLeftShiftListCase()
{
    InitModel();

    QObjectList list { objects[0], objects[1], objects[2] };

    model << list;
    VerifyCountSignal(1);
    model << list;
    VerifyCountSignal(2);

    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);
    QVERIFY(model.value(2) == objects[2]);
    QVERIFY(model.value(3) == objects[0]);
    QVERIFY(model.value(4) == objects[1]);
    QVERIFY(model.value(5) == objects[2]);

    QVERIFY(model.count() == 6);
}

void ListModelTest::operatorAdditionAssignmentCase()
{
    InitModel();

    model += objects[0];
    VerifyCountSignal(1);
    model += objects[1];
    VerifyCountSignal(2);

    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);

    QVERIFY(model.count() == 2);
}

void ListModelTest::operatorLeftShiftCase()
{
    InitModel();

    model << objects[0];
    VerifyCountSignal(1);
    model << objects[1];
    VerifyCountSignal(2);

    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);

    QVERIFY(model.count() == 2);
}

void ListModelTest::modelMethodsCase()
{
    InitModel();
    Q_UNUSED(tester);

    QObject *o = (QObject *)1;

    for (int i = 0; i < 3; ++i) {
        model.append(objects[i]);
    }
    model.append(nullptr);
    model.append(o);

    QModelIndex index0 = model.index(0, 0);
    QModelIndex index1 = model.index(1, 0);
    QModelIndex index2 = model.index(2, 0);
    QModelIndex index3 = model.index(3, 0);
    QModelIndex index4 = model.index(4, 0);
    QModelIndex index5 = model.index(5, 0);

    QVERIFY(index0.row() == 0);
    QVERIFY(index1.row() == 1);
    QVERIFY(index2.row() == 2);
    QVERIFY(index3.row() == 3);
    QVERIFY(index4.row() == 4);
    QVERIFY(index5.row() ==-1);

    QVERIFY(index0.column() == 0);
    QVERIFY(index1.column() == 0);
    QVERIFY(index2.column() == 0);
    QVERIFY(index3.column() == 0);
    QVERIFY(index4.column() == 0);
    QVERIFY(index5.column() ==-1);

    QVERIFY(model.value(index0) == objects[0]);
    QVERIFY(model.value(index1) == objects[1]);
    QVERIFY(model.value(index2) == objects[2]);
    QVERIFY(model.value(index3) == nullptr);
    QVERIFY(model.value(index4) == o);
    QVERIFY(model.value(index5) == nullptr);

    QVERIFY(model.value(index0, nullptr) == objects[0]);
    QVERIFY(model.value(index1, nullptr) == objects[1]);
    QVERIFY(model.value(index2, nullptr) == objects[2]);
    QVERIFY(model.value(index3, nullptr) == nullptr);
    QVERIFY(model.value(index4, nullptr) == o);
    QVERIFY(model.value(index5, nullptr) == nullptr);

    QVERIFY(model.value(0) == objects[0]);
    QVERIFY(model.value(1) == objects[1]);
    QVERIFY(model.value(2) == objects[2]);
    QVERIFY(model.value(3) == nullptr);
    QVERIFY(model.value(4) == o);
    QVERIFY(model.value(5) == nullptr);

    QVERIFY(model.value(0, nullptr) == objects[0]);
    QVERIFY(model.value(1, nullptr) == objects[1]);
    QVERIFY(model.value(2, nullptr) == objects[2]);
    QVERIFY(model.value(3, nullptr) == nullptr);
    QVERIFY(model.value(4, nullptr) == o);
    QVERIFY(model.value(5, nullptr) == nullptr);
}

QTEST_APPLESS_MAIN(ListModelTest)

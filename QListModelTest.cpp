#include "QListModelTest.h"

#include <QtTest>

#include "src/QListModel.h"

QTEST_APPLESS_MAIN(OLModelTest)

void OLModelTest::testCase001()
{
    QListModel<int> listModel;
    QList<int> list {0, 1, 2};

    listModel.append(list);
    listModel = list;

    QVERIFY(listModel.count() == 3);
    QVERIFY(listModel.at(0) == 0);
    QVERIFY(listModel.at(1) == 1);
    QVERIFY(listModel.at(2) == 2);

    QVERIFY(list == listModel);
}

void OLModelTest::testCase002()
{
    QListModel<int> listModel;
    QList<int> list {0, 1, 2};

    listModel.append(list);
    listModel += list;

    QVERIFY(listModel.count() == 6);
    QVERIFY(listModel.at(0) == 0);
    QVERIFY(listModel.at(1) == 1);
    QVERIFY(listModel.at(2) == 2);
    QVERIFY(listModel.at(3) == 0);
    QVERIFY(listModel.at(4) == 1);
    QVERIFY(listModel.at(5) == 2);
}

void OLModelTest::testCase003()
{
    QListModel<int> listModel;
    QList<int> list {0, 1, 2};

    listModel.append(list);
    listModel << list;

    QVERIFY(listModel.count() == 6);
    QVERIFY(listModel.at(0) == 0);
    QVERIFY(listModel.at(1) == 1);
    QVERIFY(listModel.at(2) == 2);
    QVERIFY(listModel.at(3) == 0);
    QVERIFY(listModel.at(4) == 1);
    QVERIFY(listModel.at(5) == 2);
}

void OLModelTest::testCase004()
{
    QListModel<int> listModel;

    listModel.append(0);
    listModel += 1;

    QVERIFY(listModel.count() == 2);
    QVERIFY(listModel.at(0) == 0);
    QVERIFY(listModel.at(1) == 1);
}

void OLModelTest::testCase005()
{
    QListModel<int> listModel;

    listModel.append(0);
    listModel << 1;

    QVERIFY(listModel.count() == 2);
    QVERIFY(listModel.at(0) == 0);
    QVERIFY(listModel.at(1) == 1);
}

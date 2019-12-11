#ifndef LISTMODELTEST_H
#define LISTMODELTEST_H

#include <QObject>

class ListModelTest : public QObject
{
    Q_OBJECT

public:
    ListModelTest();

private slots:
    void appendListCase();

    void prependCase();
    void appendCase();

    void push_frontCase();
    void push_backCase();

    void replaceCase();
    void insertCase();

    void removeOneCase();
    void removeAllCase();

    void pop_frontCase();
    void pop_backCase();

    void removeAtCase();
    void removeFirstCase();
    void removeLastCase();

    void takeAtCase();
    void takeFirstCase();
    void takeLastCase();

    void swapCase();
    void swapListCase();
    void moveCase();

    void clearCase();

private slots: // Extra methods
    void deleteAllCase();

private slots: // Operators
    void operatorAssignmentCase();
    void operatorAdditionCase();

    void operatorEqualToCase();
    void operatorNotEqualCase();

    void operatorAdditionAssignmentListCase();
    void operatorLeftShiftListCase();

    void operatorAdditionAssignmentCase();
    void operatorLeftShiftCase();

private slots:
    void modelMethodsCase();

private:
    QObjectList objects;
};

#endif // LISTMODELTEST_H

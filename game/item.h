#ifndef ITEM_H
#define ITEM_H
#include <QString>

class Item
{
public:
    Item();
    Item(QString,QString);
    QString getStr();
    int getAmount();
    void setAmount(int);

private:
    QString str{""};
    QString Name;
    int Amount{0};
};

#endif // ITEM_H

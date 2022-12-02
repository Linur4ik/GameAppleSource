#include "item.h"

Item::Item()
{

}

Item::Item(QString aName,QString aStr)
{
    str=aStr;
    Name=aName;
}

QString Item:: getStr()
{
    return str;
}

int Item:: getAmount()
{
    return Amount;
}

void Item:: setAmount(int aAmount)
{
    Amount=aAmount;
}

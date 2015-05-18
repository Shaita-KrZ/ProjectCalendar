#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <QtWidgets>
#include <iostream>

class CalendarException{
public:
    CalendarException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

#endif // EXCEPTION_H


#pragma once

#include "core/NodeWidget/nodewidget.h"
#include <QLabel>

class NLabel : public QLabel, public NodeWidget
{
    Q_OBJECT
    NODEWIDGET_IMPLEMENTATIONS(QLabel)
public:
    using QLabel::QLabel; //inherit all constructors of QLabel
    Q_INVOKABLE QObject *newInstance()
    {
        return NLabel::staticMetaObject.newInstance();
    }
};

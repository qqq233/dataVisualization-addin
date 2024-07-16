#ifndef DATA_PREPROCESS_H
#define DATA_PREPROCESS_H

#include <qobject.h>

class data_preprocess : public QObject
{
    Q_OBJECT
public:
    explicit data_preprocess(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DATA_PREPROCESS_H

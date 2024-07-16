#ifndef LINES_VIEW_H
#define LINES_VIEW_H

#include <QObject>
#include <QChartView>
#include <QChart>
#include <QDebug>
#include <QScatterSeries>
#include <QLineSeries>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QLineEdit>

QT_CHARTS_USE_NAMESPACE

class lines_view : public QChartView
{
public:
    explicit lines_view(QWidget *parent = nullptr);
    ~lines_view();

    void set_data(QMap<QString, QList<QVariant> > data, QString data_name);

private:
    void init();

    bool data_check(QMap<QString, QList<QVariant> > data);

    void refresh();

    void clean();

    double min(double x, double y);
    double max(double x, double y);

    QMap<QString, QList<QVariant> > m_data;

    QString m_data_name;

    QChart *m_chart;

    QLineEdit *m_value_label;

private slots:
    void slot_point_hover(const QPointF &point, bool state);
};

#endif // LINES_VIEW_H

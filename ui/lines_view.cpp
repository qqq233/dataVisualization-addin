#include "lines_view.h"

lines_view::lines_view(QWidget *parent) : QChartView(parent)
{
    init();
}

lines_view::~lines_view()
{
    delete m_chart;
}

void lines_view::set_data(QMap<QString, QList<QVariant> > data, QString data_name)
{
    if(!data_check(data)){
        qDebug() << "model 数据校验失败";
        return;
    }

    clean();

    m_data = data;
    m_data_name = data_name;

    refresh();
}

void lines_view::init()
{
    m_chart = new QChart();
    this->setChart(m_chart);

    m_value_label = new QLineEdit;
}

bool lines_view::data_check(QMap<QString, QList<QVariant> > data)
{
    int time_len = data["time"].size();
    int price_len = data["price"].size();

    if(time_len <= 0 || price_len <= 0 || time_len != price_len)
        return false;
    else
        return true;
}

void lines_view::refresh()
{
    QList<QVariant> time_list = m_data["time"];
    QList<QVariant> price_list = m_data["price"];

    // 离散点
    QScatterSeries *series_point = new QScatterSeries();
    series_point->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series_point->setBorderColor(Qt::blue);
    series_point->setMarkerSize(10);
    connect(series_point, &QScatterSeries::hovered, this, &lines_view::slot_point_hover);

    // 折线图
    QLineSeries *series = new QLineSeries();
    series->setColor(Qt::darkGreen);
    series->setName(m_data_name);

    // 绘制
    double price_max = 0.0;
    double price_min = price_list[0].toDouble();
    for(qreal i=0; i<time_list.size(); i++){
        QString date = time_list[i].toString();
        QDateTime datetime = QDateTime::fromString(date, "yyyy-MM-dd hh:mm:ss");

        qreal price = price_list[i].toDouble();
        series->append(datetime.toMSecsSinceEpoch(), price);
        series_point->append(datetime.toMSecsSinceEpoch(), price);


        if(price_list[i].toDouble() > price_max)
            price_max = price_list[i].toDouble();

        if(price_list[i].toDouble() < price_min)
            price_min = price_list[i].toDouble();

    }

    // 坐标轴
    QDateTimeAxis *axis_x = new QDateTimeAxis();
    axis_x->setTickCount(3);
    axis_x->setFormat("yyyy-MM-dd hh:mm:ss");

    QDateTime start_time = QDateTime::fromString(time_list[0].toString(), "yyyy-MM-dd hh:mm:ss");
    QDateTime end_time = QDateTime::fromString(time_list[time_list.size() - 1].toString(), "yyyy-MM-dd hh:mm:ss");
    axis_x->setRange(start_time.addSecs(-5000), end_time.addSecs(5000));


    QValueAxis *axis_y = new QValueAxis();

    axis_y->setRange(max(0, price_min - 0.5), price_max + 0.5);

    m_chart->addSeries(series);
    m_chart->addSeries(series_point);
    m_chart->setAxisX(axis_x, series);
    m_chart->setAxisX(axis_x, series_point);
    m_chart->setAxisY(axis_y, series);
    m_chart->setAxisY(axis_y, series_point);

//    this->setChart(m_chart);
}

void lines_view::clean()
{
    m_chart->removeAllSeries();
    foreach(auto axis, m_chart->axes()){
        m_chart->removeAxis(axis);
    }

    m_data.clear();
}

double lines_view::min(double x, double y)
{
    return (x < y) ? x : y;
}

double lines_view::max(double x, double y)
{
    return (x > y) ? x : y;
}

void lines_view::slot_point_hover(const QPointF &point, bool state)
{
    if(state){
        m_value_label->setText(QString("%1 \n当前价格:%2 G").arg(QDateTime::fromMSecsSinceEpoch(point.x()).toString("yyyy-MM-dd hh:mm:ss")).arg(point.y()));
        QPoint cur_pos = QCursor::pos();
        m_value_label->move(cur_pos.x() + 50, cur_pos.y() + 50);
        m_value_label->show();
    }
    else{
        m_value_label->hide();
    }
}

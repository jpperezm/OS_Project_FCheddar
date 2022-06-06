#include "graph.h"
#include <iostream>


Graph::Graph(int task_num, int hyperperiod,
             QVector<QString> name_vect,
             QVector<int> arrivalT_vect,
             QVector<int> period_vect,
             QVector<int> execT_vect)
{
    hyperperiod_ = hyperperiod;
    task_num_ = task_num;

    axisX = new QValueAxis;
    axisY = new QCategoryAxis();

    // Initialize graph
    chart = new QChart();
    chart->legend()->hide();

    // Customize chart title
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle("FCheddar");

    // Customize axis label font
    QFont labelsFont;
    labelsFont.setPixelSize(12);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

    // Customize axis colors
    QPen axisPen(QRgb(0xd18952));
    axisPen.setWidth(2);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    // Customize axis label colors
    QBrush axisBrush(Qt::black);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    // Customize grid lines and shades
    axisX->setGridLineVisible(true);
    axisY->setGridLineVisible(false);
    axisY->setShadesPen(Qt::NoPen);
    axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
    axisY->setShadesVisible(false);

    axisX->setRange(0, hyperperiod_);
    axisX->setLabelFormat("%d");

    axisY->setRange(0, task_num_);

    axisX->setTickCount((hyperperiod_ / 5) + 1);
    axisY->setTickCount(task_num_);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    for(int i = 0; i < task_num_; i++) {
        taskLines_.push_back(new QLineSeries());

        *taskLines_[i] << QPointF(0, 0.5 + i) << QPointF(hyperperiod_, 0.5 + i);
        taskLines_[i]->setPen(taskPen);
        axisY->append(name_vect[i], i+1);
        chart->addSeries(taskLines_[i]);
        taskLines_[i]->attachAxis(axisX);
        taskLines_[i]->attachAxis(axisY);
    }



/*
    QLineSeries *series = new QLineSeries();
    QLineSeries *seriesTask = new QLineSeries();
    *series << QPointF(0, 0.75) << QPointF(120, 0.75);
    *seriesTask << QPointF(1, 0.75) << QPointF(5, 0.75);

    series->setPen(taskPen);
    seriesTask->setPen(activeTaskPen);

    chart->addSeries(series);
    chart->addSeries(seriesTask);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    seriesTask->attachAxis(axisX);
    seriesTask->attachAxis(axisY);
*/
}

Graph::~Graph()
{
    if(axisX) delete axisX;
    if(axisY) delete axisY;  //check before delete
    for (int i = 0; i < taskLines_.size(); i++) {
        if(taskLines_[i]) delete taskLines_[i];
    }
    if(chart) delete chart;
}

QChart* Graph::get_chart(void) {
    return chart;
}

void Graph::setTaskPen(QColor color, int width) {
    taskPen.setColor(color);
    taskPen.setWidth(width);
}

void Graph::setActiveTaskPen(QColor color, int width) {
    activeTaskPen.setColor(color);
    activeTaskPen.setWidth(width);
}


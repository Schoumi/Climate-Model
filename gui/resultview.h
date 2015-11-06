#ifndef RESULTVIEW_H
#define RESULTVIEW_H

#include <QWidget>

#include "graphview.h"
#include <QGridLayout>

class ResultView : public QWidget
{
    Q_OBJECT
public:
    explicit ResultView(QWidget *parent = 0);
    void startSimulation();
    void addSimulation();

private slots:
    void hideSimu(bool show);

private:
    GraphView view;
    GraphView view1;
    GraphView view2;
    GraphView view3;

    QGridLayout legendLayout;

};

#endif // RESULTVIEW_H

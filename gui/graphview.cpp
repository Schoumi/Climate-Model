#include "graphview.h"

#include <QVBoxLayout>

GraphView::GraphView(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(&graphType);
    layout->addWidget(&plot);
    plot.setAutoFillBackground(true);
    QPalette palette = plot.palette();
    palette.setColor(QPalette::Background,QColor(Qt::black));
    palette.setColor(QPalette::Text,QColor(Qt::white));
    plot.setPalette(palette);
    plot.setBackgroundRole(QPalette::Background);
    plot.setAutoReplot(true);

    this->setLayout(layout);

    graphType.addItem(trUtf8("Temperature (°C)"));
    graphType.addItem(trUtf8("Sea Level (meter)"));
    graphType.addItem(trUtf8("Calotte Latitude(degre)"));
    graphType.addItem(trUtf8("CO2 Concentration (ppm)"));
    graphType.addItem(trUtf8("CO2 Emission(Gt/yr)"));
    graphType.addItem(trUtf8("Albedo (%)"));

    connect(&graphType,SIGNAL(currentIndexChanged(int)),this,SLOT(changeGraphType(int)));

}

void GraphView::addNewCurve(int id)
{
  QwtPlotCurve* curve = new QwtPlotCurve(experience_values.get_simulation(id).nom_simulation.c_str());
  curves.append(curve);
  QPen pen;
  pen.setColor(getColor(id));
  curve->setPen(pen);
  curve->attach(&plot);
  changeGraphType(graphType.currentIndex());
}

QColor GraphView::getColor(int id)
{
    int color = id % 10;
    QColor ret;
    switch(color)
    {
        case 0:
            ret = QColor(Qt::green);
            break;
        case 1:
            ret = QColor(Qt::red);
            break;
        case 2:
            ret = QColor(Qt::blue);
            break;
        case 3:
            ret = QColor(Qt::cyan);
            break;
        case 4:
            ret = QColor(Qt::magenta);
            break;
        case 5:
            ret = QColor(Qt::darkGreen);
            break;
        case 6:
            ret = QColor(Qt::darkRed);
            break;
        case 7:
            ret = QColor(Qt::darkBlue);
            break;
        case 8:
            ret = QColor(Qt::darkCyan);
            break;
        case 9:
            ret = QColor(Qt::darkMagenta);
            break;

    }
    return ret;
}

void GraphView::clean()
{
    while(!curves.empty())
    {
        delete curves.back();
        curves.pop_back();
    }
}

void GraphView::setPosition(int position)
{

}

void GraphView::showCurve(int id)
{
    if(id < curves.size())
      curves.at(id)->setVisible(true);
}

void GraphView::hideCurve(int id)
{
    if(id < curves.size())
      curves.at(id)->setVisible(false);
}

void GraphView::changeGraphType(int type)
{
    graphType.setCurrentIndex(type);
    for(int i = 0; i < curves.size();i++)
    {
        tableau t = getDataForType(i,type);
        QVector<QPointF> data;
        double xoffset = experience_values.get_simulation(i).annee_debut;
        experience_values.indice_max();
        for(int j = 0; j <experience_values.indice_max(); j++)
        {
            double x = xoffset + j * experience_values.temps_elem();
            double y = t[j];
            data.append(QPointF(x,y));
        }
        curves.at(i)->setSamples(data);
    }
}

tableau GraphView::getDataForType(int id, int type)
{
    tableau data;
    switch(type)
    {
        case TEMPERATURE:
            data = experience_values.get_simulation(id).temperature_data;
        break;
        case WATERLEVEL:
            data = experience_values.get_simulation(id).niveau_mer_data;
        break;
        case CALOTTESLEVEL:
            data = experience_values.get_simulation(id).niveau_calottes_data;
        break;
        case CONCENTRATION_CO2:
            data = experience_values.get_simulation(id).concentrations_coo_data;
        break;
        case EMISSIONS_CO2:
            data = experience_values.get_simulation(id).emissions_coo_data;
        break;
        case ALBEDO:
            data = experience_values.get_simulation(id).albedo_data;
        break;
    }
    return data;
}

#include "resultview.h"
#include "graphview.h"
#include "newsimulation.h"
#include "paramview.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

ResultView::ResultView(QWidget *parent) :
    QWidget(parent)
{
    view.changeGraphType(TEMPERATURE);
    view1.changeGraphType(WATERLEVEL);
    view2.changeGraphType(CONCENTRATION_CO2);
    view3.changeGraphType(CALOTTESLEVEL);

    QHBoxLayout* headerLayout = new QHBoxLayout;
    headerLayout->addStretch();
    headerLayout->addLayout(&legendLayout);

    QGridLayout *graphLayout = new QGridLayout();
    graphLayout->addWidget(&view,0,0);
    graphLayout->addWidget(&view1,0,1);
    graphLayout->addWidget(&view2,1,0);
    graphLayout->addWidget(&view3,1,1);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(graphLayout);
    this->setLayout(mainLayout);
}

void ResultView::startSimulation()
{
    NewSimulation simulation;
    if(simulation.exec())
    {
        view.clean();
        view1.clean();
        view2.clean();
        view3.clean();
        addSimulation();
    }
}

void ResultView::addSimulation()
{
    experience_values.push_back_simulation();
    ParamView params;
    params.exec();
    SimulationValues& sv = experience_values.back();
    sv.nom_simulation = sv.generate_name();
    modele_execute();
    int nb_sim = experience_values.nb_simulations()-1;
    view.addNewCurve(nb_sim);
    view1.addNewCurve(nb_sim);
    view2.addNewCurve(nb_sim);
    view3.addNewCurve(nb_sim);
    QLabel* colorItem = new QLabel();
    QPixmap pixmap(10,10);
    pixmap.fill(view.getColor(nb_sim));
    colorItem->setPixmap(pixmap);
    QPushButton* legendButton = new QPushButton(QIcon(pixmap),sv.nom_simulation.c_str());
    legendButton->setCheckable(true);
    connect(legendButton,SIGNAL(toggled(bool)),this,SLOT(hideSimu(bool)));
    legendButton->setFlat(true);
    legendLayout.addWidget(legendButton,nb_sim%3,(nb_sim-(nb_sim%3))/3);
    legendButton->toggle();
}

void ResultView::hideSimu(bool show)
{
    QPushButton* button = qobject_cast<QPushButton*> (sender());
    int idSimu = legendLayout.indexOf(button);

    if(show)
    {
        view.showCurve(idSimu);
        view1.showCurve(idSimu);
        view2.showCurve(idSimu);
        view3.showCurve(idSimu);
    }
    else
    {
        view.hideCurve(idSimu);
        view1.hideCurve(idSimu);
        view2.hideCurve(idSimu);
        view3.hideCurve(idSimu);
    }

}

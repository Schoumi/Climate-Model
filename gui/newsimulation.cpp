#include "newsimulation.h"
#include "globals.h"

#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>

#include <QFileDialog>
#include <QApplication>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>

NewSimulation::NewSimulation(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(trUtf8("New Simulation"));
    QVBoxLayout* mainLayout = new QVBoxLayout;
    file = new QLabel;
    previousSimu = new QComboBox;

    bt1750.setText(trUtf8("1750"));
    bt21century.setText(trUtf8("21th Century"));
    btOldSimulation.setText(trUtf8("Previous Simulation : "));
    btSimulationInProgress.setText(trUtf8("Simulation in Progress"));
    bt1750.setChecked(true);

    group.addButton(&bt1750);
    group.addButton(&bt21century);
    group.addButton(&btOldSimulation);
    group.addButton(&btSimulationInProgress);
    connect(&group,SIGNAL(buttonClicked(int)),this,SLOT(buttonClicked()));

    simulationName.setPlaceholderText(trUtf8("Simulation Name"));
    mainLayout->addWidget(&simulationName);

    QHBoxLayout* oldLayout = new QHBoxLayout;
    oldLayout->addWidget(&btOldSimulation);
    oldLayout->addWidget(file);
    QPushButton* openFile = new QPushButton(trUtf8("Open"));
    oldLayout->addWidget(openFile);
    connect(openFile,SIGNAL(clicked()),this,SLOT(openFile()));

    QHBoxLayout* progressLayout = new QHBoxLayout;
    progressLayout->addWidget(&btSimulationInProgress);
    progressLayout->addWidget(previousSimu);

    for(int i = 0; i < experience_values.nb_simulations(); i++)
    {
        previousSimu->addItem(experience_values.get_simulation(i).nom_simulation.c_str());
    }

    if(previousSimu->count() == 0)
        btSimulationInProgress.setEnabled(false);

    mainLayout->addWidget(&bt1750);
    mainLayout->addWidget(&bt21century);
    mainLayout->addLayout(oldLayout);
    mainLayout->addLayout(progressLayout);

    QLabel *labelDuration = new QLabel(trUtf8("Simulation Duration"));
    duration.setMinimum(10);
    duration.setMaximum(500);
    duration.setValue(250);

    QDialogButtonBox* btbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(btbox->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(startSimulation()));
    connect(btbox->button(QDialogButtonBox::Cancel),SIGNAL(clicked()),this,SLOT(reject()));

    mainLayout->addWidget(labelDuration);
    mainLayout->addWidget(&duration);
    mainLayout->addWidget(btbox);
    setLayout(mainLayout);
}

void NewSimulation::startSimulation()
{
    int echeance = duration.value();
    QString name;
    if(simulationName.text().isEmpty())
        name = trUtf8("No Title");
    else
        name = simulationName.text();
    if(bt1750.isChecked())
        experience_values.set_etat_initial(create_etat_1750(),echeance);
    else if(bt21century.isChecked())
        experience_values.set_etat_initial(create_etat_2007(),100);
        //experience_values.set_etat_initial(create_etat_21century,100);
    else if(btOldSimulation.isChecked())
    {
        if(!filename.isEmpty())
            experience_values.set_etat_initial(filename.toStdString(),echeance);
        else
            return;
    }
    else
    {
        int idx = previousSimu->currentIndex();
        experience_values.set_etat_initial(experience_values.get_simulation(idx),echeance);
    }
    accept();
}


void NewSimulation::openFile()
{
    filename = QFileDialog::getOpenFileName(this,trUtf8("Open a simulation"),QApplication::applicationDirPath());
    if(filename.contains("/"))
        file->setText(filename.mid(filename.lastIndexOf("/")+1));
    else if (filename.contains("\\"))
        file->setText(filename.mid(filename.lastIndexOf("\\")+1));
}

void NewSimulation::buttonClicked()
{
    if(bt21century.isChecked())
        duration.setEnabled(false);
    else
        duration.setEnabled(true);

}

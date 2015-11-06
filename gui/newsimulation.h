#ifndef NEWSIMULATION_H
#define NEWSIMULATION_H

#include <QDialog>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>

class NewSimulation : public QDialog
{
    Q_OBJECT
public:
    NewSimulation(QWidget *parent = 0);

private slots:
    void startSimulation();
    void openFile();
    void buttonClicked();

private:
    QLineEdit simulationName;
    QButtonGroup group;
    QRadioButton bt1750;
    QRadioButton bt21century;
    QRadioButton btOldSimulation;
    QRadioButton btSimulationInProgress;
    QSpinBox duration;
    QComboBox *previousSimu;
    QString filename;
    QLabel *file;
};

#endif // NEWSIMULATION_H

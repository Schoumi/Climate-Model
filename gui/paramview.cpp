#include "paramview.h"
#include "ui_paramview.h"

ParamView::ParamView(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::ParamView)
{
    ui->setupUi(this);
}

ParamView::~ParamView()
{
    delete ui;
}

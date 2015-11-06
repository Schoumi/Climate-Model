#ifndef PARAMVIEW_H
#define PARAMVIEW_H

#include <QWizard>

namespace Ui {
class ParamView;
}

class ParamView : public QWizard
{
    Q_OBJECT

public:
    explicit ParamView(QWidget *parent = 0);
    ~ParamView();

private:
    Ui::ParamView *ui;
};

#endif // PARAMVIEW_H

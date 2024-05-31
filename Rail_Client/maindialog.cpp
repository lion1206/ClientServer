#include "maindialog.h"
#include "ui_maindialog.h"
#include "client.h"
#include "trainwidget.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    loadTrains();
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::loadTrains()
{
    QList<QVariantMap> trains = Client::instance()->getTrains();
    foreach (const QVariantMap &train, trains) {
        TrainWidget *widget = new TrainWidget(this);
        widget->setTrainData(train);
        ui->trainsLayout->addWidget(widget);
    }
}

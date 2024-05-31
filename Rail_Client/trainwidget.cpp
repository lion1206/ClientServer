#include "trainwidget.h"
#include "ui_trainwidget.h"
#include "client.h"
#include <QMessageBox>

TrainWidget::TrainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainWidget)
{
    ui->setupUi(this);
    connect(ui->buyButton, &QPushButton::clicked, this, &TrainWidget::buyTicket);
}

TrainWidget::~TrainWidget()
{
    delete ui;
}

void TrainWidget::setTrainData(const QVariantMap &data)
{
    m_trainData = data;
    ui->trainNumberLabel->setText(data["train_number"].toString());
    ui->departureTimeLabel->setText(data["departure_time"].toString());
    ui->arrivalTimeLabel->setText(data["arrival_time"].toString());
    ui->availableSeatsLabel->setText(QString::number(data["available_seats"].toInt()));
}

void TrainWidget::buyTicket()
{

    QString userId = Client::instance()->id;
    int trainId = m_trainData["id"].toInt();

    if (Client::instance()->buyTicket(userId, trainId)) {
        QMessageBox::information(this, "Purchase", QString("Number of Yuor ticket is %1:%2").arg(m_trainData["train_number"].toString()).arg(userId));
    } else {
        QMessageBox::warning(this, "Purchase", "Failed to purchase ticket.");
    }
}

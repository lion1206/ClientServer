#ifndef TRAINWIDGET_H
#define TRAINWIDGET_H

#include <QWidget>
#include <QVariantMap>

namespace Ui {
class TrainWidget;
}

class TrainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrainWidget(QWidget *parent = nullptr);
    ~TrainWidget();
    void setTrainData(const QVariantMap &data);

private slots:
    void buyTicket();

private:
    Ui::TrainWidget *ui;
    QVariantMap m_trainData;
};

#endif // TRAINWIDGET_H

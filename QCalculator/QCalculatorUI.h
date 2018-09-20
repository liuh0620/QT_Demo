#ifndef QCALCULATORUI_H
#define QCALCULATORUI_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <ICalculator.h>

class QCalculatorUI : public QWidget
{
    Q_OBJECT
protected:
    QLineEdit* m_le;
    QPushButton* m_button[20];
    ICalculator* m_ical;

    QCalculatorUI();
    bool construct();
protected slots:
    void onButtonClicked();
public:
    static QCalculatorUI* NewInstance();
    void setCalculator(ICalculator* cal);
    ICalculator* getCalculator();
    ~QCalculatorUI();
};

#endif // QCALCULATORUI_H

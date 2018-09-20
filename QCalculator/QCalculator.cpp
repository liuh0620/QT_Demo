#include "QCalculator.h"

QCalculator::QCalculator()
{

}

bool QCalculator::construct()
{
    calc_ui = QCalculatorUI::NewInstance();
    if(calc_ui != NULL)
    {
        calc_ui->setCalculator(&calc_dec);
    }
    return (calc_ui != NULL);
}

QCalculator* QCalculator::NewInstan()
{
    QCalculator* ret = new QCalculator();
    if((ret == NULL) || !ret->construct())
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

void QCalculator::show()
{
    calc_ui->show();
}

QCalculator::~QCalculator()
{
    delete calc_ui;
}

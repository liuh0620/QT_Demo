#ifndef QCALCULATOR_H
#define QCALCULATOR_H
#include "QCalculatorUI.h"
#include "QCalculatorDec.h"

class QCalculator
{
private:
   QCalculatorUI* calc_ui;
   QCalculatorDec calc_dec;

   QCalculator();
   bool construct();
public:
   static QCalculator* NewInstan();
   void show();
   ~QCalculator();
};

#endif // QCALCULATOR_H

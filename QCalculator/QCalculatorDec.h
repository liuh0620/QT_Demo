#ifndef QCALCULATORDEC_H
#define QCALCULATORDEC_H
#include <QString>
#include <QQueue>

#include <ICalculator.h>

class QCalculatorDec : public ICalculator
{
protected:
    QString m_exp;
    QString m_result;

    bool isDigitOrDot(QChar c);
    bool isSymbol(QChar c);
    bool isSign(QChar c);
    bool isOperator(QString s);

    bool isNumber(QString s);
    bool isLeft(QString s);
    bool isRight(QString s);
    int priority(QString s);

    bool match(QQueue<QString>& exp);
    bool transform(QQueue<QString> exp, QQueue<QString>& output);
    QString calculator(QQueue<QString>& exp);
    QString calculator(QString lp, QString op, QString rp);
    QQueue<QString> split(const QString& exp);

    bool expression(const QString& exp);
    QString result();
public:
    QCalculatorDec();
    ~QCalculatorDec();
};

#endif // QCALCULATORDEC_H

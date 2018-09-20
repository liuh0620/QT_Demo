#include "QCalculatorDec.h"
#include <QDebug>
#include <QStack>
#include "ICalculator.h"

QCalculatorDec::QCalculatorDec()
{
    m_exp = "";
    m_result = "";
}

bool QCalculatorDec::isDigitOrDot(QChar c)
{
    return (('0' <= c) && (c <= '9')) || (c == '.');
}

bool QCalculatorDec::isSymbol(QChar c)
{
    return isOperator(c) || (c == '(') || (c == ')');
}

bool QCalculatorDec::isSign(QChar c)
{
    return (c == '+') || (c == '-');
}

bool QCalculatorDec::isOperator(QString s)
{
    return (s == "+") || (s == "-") || (s == "*") || (s == "/");
}

bool QCalculatorDec::isNumber(QString s)
{
    bool ret = false;
    s.toDouble(&ret);
    return ret;
}

bool QCalculatorDec::isLeft(QString s)
{
    return (s == "(");
}

bool QCalculatorDec::isRight(QString s)
{
    return (s == ")");
}

int QCalculatorDec::priority(QString s)
{
    int ret = 0;
    if((s == "+") || (s == "-"))
    {
        ret = 1;
    }
    if((s == "*") || (s == "/"))
    {
        ret = 2;
    }
    return ret;
}

bool QCalculatorDec::match(QQueue<QString>& exp)
{
    bool ret = true;
    int len = exp.length();
    QStack<QString> stack;

    stack.clear();
    for(int i=0; i<len; i++)
    {
        if(isLeft(exp[i]))
        {
            stack.push(exp[i]);
        }
        else if(isRight(exp[i]))
        {
            if(!stack.isEmpty() && isLeft(stack.top()))
            {
                stack.pop();
            }
            else
            {
                ret = false;
            }
        }

    }
    return ret && stack.isEmpty();
}

bool QCalculatorDec::transform(QQueue<QString> exp, QQueue<QString>& output)
{
    bool ret = match(exp);
    QStack<QString> stack;
    int len = exp.length();
    output.clear();

    for(int i=0; i<len; i++)
    {

        if(isNumber(exp[i]))
        {
            output.enqueue(exp[i]);
        }
        else if(isLeft(exp[i]))
        {
            stack.push(exp[i]);
        }
        else if(isRight(exp[i]))
        {
            while(!isLeft(stack.top()) && !stack.isEmpty())
            {
               output.enqueue(stack.pop());
            }
            if(!stack.isEmpty())
            {
                stack.pop();
            }
        }
        else if(isOperator(exp[i]))
        {
            while(!stack.isEmpty() && (priority(exp[i]) <= priority(stack.top())))
            {
                output.enqueue(stack.pop());
            }
            stack.push(exp[i]);
        }
        else
        {
            ret = false;
        }

    }
    while(!stack.isEmpty())
    {
        output.enqueue(stack.pop());
    }
    if(!ret)
    {
        output.clear();
    }
    return ret;
}

QQueue<QString> QCalculatorDec::split(const QString& exp)
{
    QQueue<QString> ret;
    QString num = "";
    QString pre = "";

    ret.clear();
    for(int i=0; i<exp.length(); i++)
    {
        if(isDigitOrDot(exp[i]))
        {
            num += exp[i];
            pre = exp[i];
        }
        else if(isSymbol(exp[i]))
        {
            if(!num.isEmpty())
            {
                ret.enqueue(num);
                num.clear();
            }

            if(isSign(exp[i]) && (isOperator(pre) || (pre == "(") || (pre == "")))
            {
                num += exp[i];
            }
            else
            {
                ret.enqueue(exp[i]);
            }
            pre = exp[i];
        }
    }
    if(!num.isEmpty())
    {
        ret.enqueue(num);
    }
    return ret;
}

QString QCalculatorDec::calculator(QString lp, QString op, QString rp)
{
    QString ret = "Error";
    if(isNumber(lp) && isNumber(rp) && isOperator(op))
    {
        double l = lp.toDouble();
        double r = rp.toDouble();
        if(op == "+")
        {
            ret.sprintf("%f",l + r);
        }
        else if(op == "-")
        {
            ret.sprintf("%f", l - r);
        }
        else if(op == "*")
        {
            ret.sprintf("%f", l * r);
        }
        else if(op == "/")
        {
            const double precision = 0.0000000000000001;
            if((-precision < r) && (r < precision))
            {
                ret.sprintf("%f", l/r);
            }
            else
            {
                ret = "Error";
            }
        }
        else
        {
            ret = "Error";
        }
    }
    return ret;
}

QString QCalculatorDec::calculator(QQueue<QString>& exp)
{
    QString ret = "Error";
    QStack<QString> stack;
    stack.clear();

    while(!exp.isEmpty())
    {
        QString e = exp.dequeue();
        if(isNumber(e))
        {
            stack.push(e);
        }
        else if(isOperator(e))
        {
            QString op = e;
            QString rp = stack.pop();
            QString lp = stack.pop();
            qDebug() << lp << op << rp;
            QString result = calculator(lp, op, rp);
            if(result != "Error")
            {
                stack.push(result);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(exp.isEmpty() && (stack.size() == 1) && isNumber(stack.top()))
    {
        ret = stack.pop();
    }
    return ret;
}

bool QCalculatorDec::expression(const QString& exp)
{
    qDebug() << exp;
    bool ret = false;
    QQueue<QString> spExp = split(exp);
    QQueue<QString> postExp;
    m_exp = exp;

    if(transform(spExp, postExp))
    {
        m_result = calculator(postExp);
        ret = (m_result != "Error");
    }
    else
    {
        m_result = "Error";
    }
    return ret;
}
QString QCalculatorDec::result()
{
    return m_result;
}

QCalculatorDec::~QCalculatorDec()
{
}

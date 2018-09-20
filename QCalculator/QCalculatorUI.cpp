#include "QCalculatorUI.h"
#include <QWidget>
#include <QLineEdit>
#include <QDebug>

QCalculatorUI::QCalculatorUI() : QWidget(NULL, Qt::MSWindowsFixedSizeDialogHint)
{
}

bool QCalculatorUI::construct()
{
    bool ret = false;
    const QString btn_text[20] =
    {
        "7", "8", "9", "+", "(",
        "4", "5", "6", "-", ")",
        "1", "2", "3", "*", "<-",
        "0", ".", "=", "/", "C",
    };
    /*Line Edit初始化*/
    m_le = new QLineEdit(this);
    if(m_le != NULL)
    {
        m_le->move(10, 10);
        m_le->resize(240, 40);
        m_le->setAlignment(Qt::AlignRight);
        m_le->setReadOnly(true);

        ret = true;
    }
#if 1
    /*button 初始化*/
    for(int i=0; (i<4) && ret; i++)
    {
        for(int j=0; j<5; j++)
        {
            m_button[i*5 + j] = new QPushButton(this);
            if(m_button[i*5 + j] != NULL)
            {
                m_button[i*5 + j]->move(10+(40+10)*j, 60+(40+10)*i);
                m_button[i*5 + j]->resize(40, 40);
                m_button[i*5 + j]->setText(btn_text[i*5 + j]);
                connect(m_button[i*5+j], SIGNAL(clicked()), this, SLOT(onButtonClicked()));
            }
            else
            {
                ret = false;
                qDebug() << "Error";
            }

        }
    }
#endif

    return ret;
}

QCalculatorUI* QCalculatorUI::NewInstance()
{
    QCalculatorUI* ret = new QCalculatorUI();
    if(!ret || !ret->construct())
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

void QCalculatorUI::onButtonClicked()
{
    QPushButton* btn = (QPushButton*)sender();
    QString btn_text = btn->text();
    QString le_text = m_le->text();

    if(btn_text == "C")
    {
        m_le->setText("");
    }
    else if(btn_text == "<-")
    {
        if(le_text.length() > 0)
        {
            le_text.remove(le_text.length()-1, 1);
            m_le->setText(le_text);
        }
    }
    else if(btn_text == "=")
    {
        if(m_ical != NULL)
        {
            qDebug() << m_le->text();
            m_ical->expression(m_le->text());
            m_le->setText(m_ical->result());
        }
    }
    else
    {
        m_le->setText(le_text + btn_text);
    }

}

void QCalculatorUI::setCalculator(ICalculator* cal)
{
    m_ical = cal;
}

ICalculator* QCalculatorUI::getCalculator()
{
    return m_ical;
}

QCalculatorUI::~QCalculatorUI()
{
}

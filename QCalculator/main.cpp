#include <QApplication>
#include "QCalculator.h"

int main(int argc, char *argv[])
{
    int ret = -1;
    QApplication a(argc, argv);

    QCalculator* cal = QCalculator::NewInstan();

    if(cal != NULL)
    {
        cal->show();
        ret = a.exec();
    }

    return ret;
}

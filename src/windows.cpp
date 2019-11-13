#include "windows.hpp"

windows::windows(char *filename)
{
    QLabel *imglb=new QLabel();
    gridlyou=new QGridLayout;
    groupbox=new QGroupBox();
    fftBut=new QPushButton(QObject::tr("2dfft"));
    avgfilterBut=new QPushButton(QObject::tr("均值滤波"));
    midfilterBut=new QPushButton(QObject::tr("中值滤波"));
    openBut=new QPushButton(QObject::tr("开运算"));
    closeBut=new QPushButton(QObject::tr("闭运算"));
    equalyBut=new QPushButton(QObject::tr("直方图均衡"));

    QObject::connect(fftBut,SIGNAL(released()),gridlyou,SLOT(handleBut(QObject::tr("886"))));

    imglb->setPixmap(QPixmap(tr(filename)));

    groupbox->setAlignment(Qt::AlignHCenter);
    gridlyou->addWidget(imglb,1,0,1,3);
    gridlyou->addWidget(fftBut,2,0);
    gridlyou->addWidget(avgfilterBut,2,1);
    gridlyou->addWidget(midfilterBut,2,2);
    gridlyou->addWidget(openBut,3,0);
    gridlyou->addWidget(closeBut,3,1);
    gridlyou->addWidget(equalyBut,3,2);
    groupbox->setLayout(gridlyou);

}
void windows::show()
{
    groupbox->show();
}

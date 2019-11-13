#include "mainwindow.hpp"

mainwindow::mainwindow(char *filename)
{
    gridlyou=new QGridLayout;
    groupbox=new QGroupBox();
    img=new matrics(filename);
    QLabel *source=new QLabel();
    QLabel *mycanny=new QLabel();
    QLabel *cvcanny=new QLabel();
    QLabel *mycorner=new QLabel();
    QLabel *cvcorner=new QLabel();

    source->setPixmap(Mat2Pixmap(img->gray));
    mycanny->setPixmap(Mat2Pixmap(img->doubleArray2Mat(img->Infinal)));
    cvcanny->setPixmap(Mat2Pixmap(img->gray));
    mycorner->setPixmap(Mat2Pixmap(img->gray));
    cvcorner->setPixmap(Mat2Pixmap(img->gray));

    gridlyou->addWidget(source,0,0,2,2);
    gridlyou->addWidget(mycanny,1,0);
    gridlyou->addWidget(cvcanny,1,1);
    gridlyou->addWidget(mycorner,2,0);
    gridlyou->addWidget(cvcorner,2,1);

    groupbox->setLayout(gridlyou);

}
QPixmap mainwindow::Mat2Pixmap(Mat mat)
{
    return QPixmap::fromImage(QImage(mat.data,mat.cols,mat.rows,mat.step,QImage::Format_Grayscale8));
}
void mainwindow::show()
{
    groupbox->show();
}

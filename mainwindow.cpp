#include "mainwindow.hpp"

mainwindow::mainwindow(char *filename)
{
    QLabel *imglb=new QLabel();
    gridlyou=new QGridLayout;
    groupbox=new QGroupBox();

    img=new matrics(filename);


}
void mainwindow::show()
{
    groupbox->show();
}
void mainwindow::showgray(Mat img)
{
    QLabel *imglb=new QLabel();
    imglb->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8)));
    //print(img);
    imglb->show();
}

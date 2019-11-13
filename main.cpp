#include <QApplication>
#include <opencv2/highgui.hpp>

#include "mainwindow.hpp"

int main(int argc,char *argv[])
{
    /*
    QApplication a(argc,argv);
    mainwindow *window=new mainwindow(argv[1]);
    window->show();

    return a.exec();
    */
    matrics temp("/root/123.jpg");

    temp.gausblur(3);

    temp.enhance(matrics::sobel);
	//imshow("abc",temp.GauBlurMat);
	temp.nonmaximaSupress();
    temp.doubleTholdNlink(150,300);
	//imshow("abc",temp.GauBlurMat);
    imshow("open",temp.doubleArray2Mat(temp.Infinal));
    waitKey();
    return 0;
}

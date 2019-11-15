#include <QApplication>
#include <iostream>
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
    int rows,cols;
    matrics temp("/root/123.jpg");

    temp.gausblur(3);

    temp.enhance(matrics::sobel);
	//imshow("abc",temp.GauBlurMat);
	temp.nonmaximaSupress();
	do{
	   std::cin>>rows>>cols;
    temp.doubleTholdNlink(rows,cols);
    imshow("open",temp.doubleArray2Mat(temp.Infinal));
    waitKey();
	}while(1);
	//imshow("abc",temp.GauBlurMat);
    return 0;
}

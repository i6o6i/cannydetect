#include <QtWidgets>
#include <QString>
#include <QObject>
#include <QPixmap>
#include "matrics.hpp"

class mainwindow :public QWidget
{
    //Q_OBJECT
    public:
	mainwindow(QWidget *parent=nullptr);
	mainwindow(char* filename);
	void show();
	void showrgb(bool morph_flag,matrics* imgmatrix,Mat (matrics::*fun_ptr)(int));
	void showrgb(Mat img);
	void showgray(Mat img);
    private:
    matrics *img;
    QGridLayout *gridlyou;
    QGroupBox *groupbox;
    QPushButton *fftBut;
    QPushButton *medianfilterBut;
    QPushButton *avgfilterBut;
    QPushButton *openBut;
    QPushButton *closeBut;
    QPushButton *equalyBut;
};

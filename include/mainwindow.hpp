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
	QPixmap Mat2Pixmap(Mat mat);
    private:
    matrics *img;
    QGridLayout *gridlyou;
    QGroupBox *groupbox;
};

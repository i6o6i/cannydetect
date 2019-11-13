#include <QtWidgets>
#include <QString>

class windows :public QWidget
{
    Q_OBJECT
    public:
	windows(char* filename);
	void show();
    private:
    QGridLayout *gridlyou;
    QGroupBox *groupbox;
    QPushButton *fftBut;
    QPushButton *avgfilterBut;
    QPushButton *midfilterBut;
    QPushButton *openBut;
    QPushButton *closeBut;
    QPushButton *equalyBut;
};

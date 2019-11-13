#include <opencv2/imgcodecs.hpp>
#include <boost/multi_array.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#define oneighthPI (3.141592654/8.)

using namespace cv;
using namespace std;
class Point0{
    public:
	int x;
	int y;
	Point0(int x,int y);
};
class matrics
{
    public:
	int rows;
	int cols;
	Mat bgr;
	Mat gray;
	Mat GauBlurMat;
	typedef boost::multi_array<double,3> Esn0;
	typedef boost::multi_array<double,2> thinMat;
	thinMat In;
	thinMat Infinal;
	Esn0 es0;
	enum {strength,tangent};
	enum operators {oper2x2,sobel};
	matrics(const char *filename);
	Mat doubleArray2Mat(thinMat);
	thinMat triTo2d(Esn0 es0);
	void gausblur(int i);
	void enhance(operators op);
	void nonmaximaSupress();
	void doubleTholdNlink(double th,double tl);
};


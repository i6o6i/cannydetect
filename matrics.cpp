#include "matrics.hpp"

matrics::matrics(const char *filename)
{
	bgr = imread(filename, IMREAD_COLOR);
	cvtColor(bgr, gray, COLOR_BGR2GRAY);
	rows = bgr.rows;
	cols = bgr.cols;
}
void matrics::gausblur(int i)
{

	GauBlurMat = Mat();
	GaussianBlur(gray, GauBlurMat, Size(i, i), 0, 0);
}

void matrics::enhance(operators op)
{
	double jx, jy;
	float hypotenuse;
	es0.resize(boost::extents[rows - 2][cols - 2][2]);
	es0 = Esn0(boost::extents[rows - 2][cols - 2][2]);

	for(size_t i = 1; i < rows - 2; i++)
		for(size_t j = 1; j < cols - 2; j++)
		{
			switch(op) {
			case oper2x2: {
				jx = -GauBlurMat.at<uchar>(i, j) + GauBlurMat.at<uchar>(i, j + 1)
					 - GauBlurMat.at<uchar>(i + 1, j) + GauBlurMat.at<uchar>(i + 1, j + 1);
				jy = GauBlurMat.at<uchar>(i, j) + GauBlurMat.at<uchar>(i, j + 1)
					 - GauBlurMat.at<uchar>(i + 1, j) - GauBlurMat.at<uchar>(i + 1, j + 1);
			}break;
			case sobel: {
				jx = GauBlurMat.at<uchar>(i - 1, j + 1) + 2 * GauBlurMat.at<uchar>(i, j + 1) + GauBlurMat.at<uchar>(i + 1, j + 1)
					 - (GauBlurMat.at<uchar>(i - 1, j - 1) + 2 * GauBlurMat.at<uchar>(i, j - 1) + GauBlurMat.at<uchar>(i + 1, j - 1));
				jy = GauBlurMat.at<uchar>(i + 1, j - 1) + 2 * GauBlurMat.at<uchar>(i + 1, j) + GauBlurMat.at<uchar>(i + 1, j + 1)
					 - (GauBlurMat.at<uchar>(i - 1, j - 1) + 2 * GauBlurMat.at<uchar>(i - 1, j) + GauBlurMat.at<uchar>(i - 1, j + 1));
			}break;
			}
			es0[i - 1][j - 1][strength] = sqrt(jx * jx + jy * jy);
			es0[i - 1][j - 1][tangent] = jy / jx;
		}

}
matrics::thinMat matrics::triTo2d(Esn0 es0)
{
	thinMat a(boost::extents[es0.shape()[0]][es0.shape()[1]]);
	for(size_t i = 0; i < es0.shape()[0]; i++)
		for(size_t j = 0; j < es0.shape()[1]; j++)
			a[i][j] = es0[i][j][strength];
	return a;
}

Mat matrics::doubleArray2Mat(thinMat boostarr)
{
	Mat res = Mat::zeros(Size(boostarr.shape()[0], boostarr.shape()[1]), CV_64F);

	for(size_t i = 0; i < boostarr.shape()[0]; i++)
		for(size_t j = 0; j < boostarr.shape()[1]; j++)
		{
			res.at<double>(i, j) = boostarr[i][j];
		}

	normalize(res, res, 0, 1, NORM_MINMAX);
	std::cout << res.rows << " " << res.cols;
	return res;
}

void matrics::nonmaximaSupress()
{
	enum direction {horizenal, oblique45, vertical, oblique135};
	double tangen[4];
	double tmp;
	int es0rows=es0.shape()[0],es0cols=es0.shape()[1];
	direction dir;

	In.resize(boost::extents[es0rows - 2][es0cols - 2]);
	In = thinMat(boost::extents[es0rows - 2][es0cols - 2]);
	for(int i = 0; i < 4; i++)
		tangen[i] = tan(2 * i * oneighthPI + oneighthPI);

	for(size_t i = 1; i < es0rows - 2; i++)
		for(size_t j = 1; j < es0cols - 2; j++)
		{
			tmp = es0[i][j][tangent];
			dir = (tmp > tangen[3]) ? horizenal : (direction) ((tmp > tangen[2]) + (tmp > tangen[1]) + (tmp > tangen[0]));
			std::cout<<tmp<<std::endl;
			if(dir==oblique135)std::cout<<(int)dir<<std::endl;

			switch(dir)
			{
			case horizenal:
				In[i - 1][j - 1] = (es0[i - 1][j][strength] < es0[i][j][strength]
									&& es0[i][j][strength] > es0[i + 1][j][strength])
								   ? es0[i][j][strength] : 0;break;
			case oblique45:
				In[i - 1][j - 1] = (es0[i - 1][j - 1][strength] < es0[i][j][strength]
									&& es0[i][j][strength] > es0[i + 1][j + 1][strength])
								   ? es0[i][j][strength] : 0;break;
			case vertical:
				In[i - 1][j - 1] = (es0[i][j - 1][strength] < es0[i][j][strength]
									&& es0[i][j][strength] > es0[i][j + 1][strength])
								   ? es0[i][j][strength] : 0;break;
			case oblique135:
				In[i - 1][j - 1] = (es0[i + 1][j - 1][strength] < es0[i][j][strength]
									&& es0[i][j][strength] > es0[i + 1][j + 1][strength])
								   ? es0[i][j][strength] : 0;break;
			}
		}
}
void matrics::doubleTholdNlink(double th, double tl)
{
	enum direction {horizenal, oblique45, vertical, oblique135};
	double tmp,tangen[4];
	int stepx,stepy;
	int rows=In.shape()[0],cols=In.shape()[1];
	Infinal.resize(boost::extents[rows][cols]);
	boost::multi_array<bool, 2> visited(boost::extents[rows][cols]);
	typedef boost::multi_array<bool, 2>::index visitedIndex;
	direction dir;

	for(int i = 0; i < 4; i++)
		tangen[i] = tan(2 * i * oneighthPI + oneighthPI);
	for(visitedIndex i = 0; i < rows; i++)
		for(visitedIndex j = 0; j < cols; j++)
		{
			visited[i][j] = false;
			Infinal[i][j]=0;

		}


	for(thinMat::index i = 0; i < rows; i++)
		for(thinMat::index j = 0; j < cols; j++)
		{
			if(visited[i][j]||In[i][j]<th)
				continue;
			tmp=es0[i][j][tangent];
			dir=(tmp > tangen[3]) ? horizenal : (direction) ((tmp > tangen[2]) + (tmp > tangen[1]) + (tmp > tangen[0]));

			int i_=i,j_=j;
			do{
			switch((int)dir)
			{
				case horizenal:stepx=0;stepy=1;break;
				case oblique45:stepx=1;stepy=1;break;
				case vertical:stepx=1;stepy=0;break;
				case oblique135:stepx=-1;stepy=1;break;
			}
			
			do{
				Infinal[i_][j_]=In[i_][j_];
				j_+=stepx;
				i_+=stepy;
			}while(j_<=0&&In[i_][j_]>=th);
			if(j <= 0)
				continue;
			else{
				

			}
	}while(In[i_][j_]>=tl);

		}

}


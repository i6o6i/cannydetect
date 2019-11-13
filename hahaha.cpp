stack<Point> s;
queue<Point> q;

maxthreshold = ?
minthreshold = ?

bool connected = FALSE;
visited[rows][cols] = 0;

//初始化visited矩阵边界已访问
for(int i = 0; i < rows; i++){
	visited[i][0] = 1;
	visited[i][cols - 1] = 1;
}
for(int j = 0; j < cols; j++){
	visited[0][j] = 1;
	visited[rows - 1][j] = 1;
}
//


for(int i = 1; i < rows - 1; i++){
	for(int j = 1; j < cols - 1; j++){

		if(matrix[i][j] > maxthreshold){
			visited[i][j] = 3;
		}
		else if(matrix[i][j] < minthreshold){
			visited[i][j] = 1;
		}
		else if( minthreshold <= matrix[i][j] && 
            	 matrix[i][j] <= maxthreshold &&
            	 visited[i][j] == 0
           	){

			s.push(point(i, j));
			q.push(point(i, j));
			visited[i][j] = 1;

			while (!s.empty())
            {
            	Point p = s.top();
            	s.pop();
            	x = p.x; 
            	y = p.y;

            	//中上
            	if( minthreshold <= matrix[x - 1][y] && 
            		matrix[x - 1][y] <= maxthreshold &&
            		visited[x - 1][y] == 0
            	){
            		s.push(point(x - 1, y));
					q.push(point(x - 1, y));
					visited[x - 1][y] = 1;
            	}
            	//中下
            	if( minthreshold <= matrix[x + 1][y] && 
            		matrix[x + 1][y] <= maxthreshold &&
            		visited[x + 1][y] == 0
            	){
            		s.push(point(x + 1, y));
					q.push(point(x + 1, y));
					visited[x + 1][y] = 1;
            	}

            	//左上
            	if( minthreshold <= matrix[x - 1][y - 1] && 
            		matrix[x - 1][y - 1] <= maxthreshold &&
            		visited[x - 1][y - 1] == 0
            	){
            		s.push(point(x - 1, y - 1));
					q.push(point(x - 1, y - 1));
					visited[x - 1][y - 1] = 1;
            	}

            	//左中
            	if( minthreshold <= matrix[x][y - 1] && 
            		matrix[x][y - 1] <= maxthreshold &&
            		visited[x][y - 1] == 0
            	){
            		s.push(point(x, y - 1));
					q.push(point(x, y - 1));
					visited[x][y - 1] = 1;
            	}

            	//左下
            	if( minthreshold <= matrix[x + 1][y - 1] && 
            		matrix[x + 1][y - 1] <= maxthreshold &&
            		visited[x + 1][y - 1] == 0
            	){
            		s.push(point(x + 1, y - 1));
					q.push(point(x + 1, y - 1));
					visited[x + 1][y - 1] = 1;
            	}


            	//右上
            	if( minthreshold <= matrix[x - 1][y + 1] && 
            		matrix[x - 1][y + 1] <= maxthreshold &&
            		visited[x - 1][y + 1] == 0
            	){
            		s.push(point(x - 1, y + 1));
					q.push(point(x - 1, y + 1));
					visited[x - 1][y + 1] = 1;
            	}

            	//右中
            	if( minthreshold <= matrix[x][y + 1] && 
            		matrix[x][y + 1] <= maxthreshold &&
            		visited[x][y + 1] == 0
            	){
            		s.push(point(x, y + 1));
					q.push(point(x, y + 1));
					visited[x][y + 1] = 1;
            	}
            	
            	//右下
            	if( minthreshold <= matrix[x - 1][y + 1] && 
            		matrix[x - 1][y + 1] <= maxthreshold &&
            		visited[x - 1][y + 1] == 0
            	){
            		s.push(point(x - 1, y + 1));
					q.push(point(x - 1, y + 1));
					visited[x - 1][y + 1] = 1;
            	}


            	//判断是否与强边界点连通
            	if (connected == FALSE)
                {
                    for (int m = -1; m <= 1; m++)
                    {
                        for (int n = -1; n <= 1; n++)
                        {
                            if (matrix[x + m][y + n] > threshold)
                            {
                                connected = TRUE;
                            }
                        }
                    }
                }
            }//while循环体
            if (connected == TRUE)
            {
            	while (!q.empty()) {
            		Point p = q.front();
                    q.pop();
            		x = p.x; 
            		y = p.y;

            		visited[x][y] = 2;
            	}
                connected = FALSE;
            }
		}//弱边界判断体

	}
}
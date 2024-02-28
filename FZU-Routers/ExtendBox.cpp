/************************************************************************/
/* connect the rest nodes, which in the extend_unconnect                */
/* use the bfs                                                              */
/************************************************************************/

typedef struct CTRNode {
	double cost;
	Point p_now;
	vector<int> path;
	bool operator< (const CTRNode& rhs) const {
		return cost > rhs.cost;
	}
} CTRNode;

bool visited[X_MAX + 3][Y_MAX + 3][4];
int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
int dy[] = { 1, 1, 1, 0, -1, -1, -1, 0 };
int dir[] = { 3, 2, 1, 0, 3, 2, 1, 0 };

FILE * error_info;

bool Check(CTRNode& nt, const Point& pt, const int& dd, const int& net_id) { //if can be connected then return true
	if (nt.p_now.x < 0 || nt.p_now.x >= X_MAX || nt.p_now.y < 0 || nt.p_now.y >= Y_MAX)
		return false;
	//fprintf(error_info, "dd = %d, pt: %d,%d; %d\n", dd, pt.x, pt.y, visited[pt.x + 1][pt.y + 1][dd]);
	if (visited[pt.x + 1][pt.y + 1][dd])
		return false;
	visited[pt.x + 1][pt.y + 1][dd] = true;
	int num = pt.x * Y_MAX + pt.y + dd * X_MAX * Y_MAX;
	if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
		nt.cost += (dd % 2 ? 1 : sqrt(2));
		nt.cost += 10.0 * (record_p[pt.x * Y_MAX + pt.y][dd] + 1) / maxline[pt.x * Y_MAX + pt.y][dd];
		//fprintf(error_info, "======%d,%d\n", record_p[pt.x * Y_MAX + pt.y][dd], max_line[dd]);
		if (record_p[pt.x * Y_MAX + pt.y][dd] + 1 > maxline[pt.x * Y_MAX + pt.y][dd])
			return false;
		nt.path.push_back(num);
	}
	return true;
}

bool bfs(const Point& start_point, const Point& end_point, const int& net_id)
{
	int i, j;
	int test3 = 0;
	int judge=-1;
	memset(visited, false, sizeof(visited));
	for (i = 0; i < X_MAX + 3; ++i) {
		for (j = 0; j < 4; ++j) {
			visited[i][0][j] = visited[i][Y_MAX + 1][j] = true;
		}
		visited[i][1][0] = visited[i][1][1] = true;
		visited[i][Y_MAX][3] = true;
	}
	for (i = 0; i < Y_MAX + 3; ++i) {
		for (j = 0; j < 4; ++j) {
			visited[0][i][j] = visited[X_MAX + 1][i][j] = true;
		}
		visited[1][i][1] = visited[1][i][2] = visited[1][i][3] = true;
	}
	int step = 0;//11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
	priority_queue<CTRNode> pri_que;
	CTRNode nt, nt_top, nt_top2;
	nt.cost = 0;
	nt.p_now = start_point;
	nt.path.clear();
	//visited[s.x + 1][s.y + 1] = true;
	pri_que.push(nt);
	//while (!pri_que.empty()) {
	while (!pri_que.empty()&&step<5000) {//2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222
		//printf("bfs of test1 %d: %d\n", test1, test3++);
		nt_top = pri_que.top();
		nt_top2 = nt_top;
		nt_top2.path.clear();
		pri_que.pop();
		pri_que.push(nt_top2);
		pri_que.pop();
		//fprintf(error_info, "nt_top: x = %d, y = %d; \n", nt_top.p_now.x, nt_top.p_now.y);
		for (i = 0; i < 8; ++i) { //search from 8 directions
			//fprintf(error_info, "  i = %d: ", i);
			nt = nt_top;
			nt.p_now.x = nt_top.p_now.x + dx[i];
			nt.p_now.y = nt_top.p_now.y + dy[i];
			if (i < 4 && Check(nt, nt.p_now, dir[i], net_id)) {
				//visited[nt.p_now.x + 1][nt.p_now.y + 1][dir[i]] = true;
				pri_que.push(nt);
			}
			else if (Check(nt, nt_top.p_now, dir[i], net_id)) {
				//visited[nt_top.p_now.x + 1][nt_top.p_now.y + 1][dir[i]] = true;
				pri_que.push(nt);
			}
			else {
				continue;
			}
			if (nt.p_now == end_point) { //find the objective-point
				for (j = 0; j < nt.path.size(); ++j) { //add the cost of path
					line_net[net_id].point_edge.insert(nt.path[j]);
					++record_p[nt.path[j] % (X_MAX * Y_MAX)][nt.path[j] / (X_MAX * Y_MAX)];
					if ((judge != 0) && nt.path[j] / (X_MAX * Y_MAX) == 0){
						nethnum++;
						if (judge == -1){
							judge = 0;
						}
					}
					if ((judge == 0 || judge == 2) && nt.path[j] / (X_MAX * Y_MAX) == 1){
						netx45num++;
						if (judge == -1){
							judge = 1;
						}
					}
					if ((judge != 2) && nt.path[j] / (X_MAX * Y_MAX) == 2){
						netvnum++;
						if (judge == -1){
							judge = 2;
						}
					}
					if ((judge == 0 || judge == 2) && nt.path[j] / (X_MAX * Y_MAX) == 3){
						netx135num++;
						if (judge == -1){
							judge = 3;
						}
					}
				}
				while (!pri_que.empty()) {
					nt_top2 = pri_que.top();
					nt_top2.path.clear();
					pri_que.pop();
					pri_que.push(nt_top2);
					pri_que.pop();
				}
				return true;
			}
		}
		step++;//333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333
	}
	return false;
}

void ConnectTheRest()
{
	/*
	if (error_info = fopen("error_info.txt", "w")) {
		//printf("error_info.txt open success\n");
	}
	else {
		printf("error_info.txt open fail\n");
	}
	*/
	int i = 0;
	set<ExpandNode>::iterator it;
	for (it = extend_unconnect.begin(); it != extend_unconnect.end();) {
		Point p1, p2;
		int net_id = it->net_id;
		p1.x = line_net[net_id].pin[it->pa_id][0];
		p1.y = line_net[net_id].pin[it->pa_id][1];
		p2.x = line_net[net_id].pin[it->pb_id][0];
		p2.y = line_net[net_id].pin[it->pb_id][1];
		if (p2 < p1)	swap(p1, p2);
		if (bfs(p1, p2, net_id)) {
			it = extend_unconnect.erase(it);
			//extend_unconnect.erase(it++);
			//printf("bfs successed, %d\n", i++);
			/*fclose(error_info);
			if (error_info = fopen("error_info.txt", "w")) {
				//printf("error_info.txt open success\n");
			}
			else {
				printf("error_info.txt open fail\n");
			}
			*/
		}
		else {
			it++;
			//printf("bfs failed, %d\n", i++);
		}

	}
}

inline bool PointInBox(const int& x, const int& y) {
    return x >= box[3] && x <= box[1] && y >= box[2] && y <= box[0];
}

void ExtendBox() {
    extend_unconnect.clear();
    int i, j;
    int temp_max, temp;
	int a, b;
    int p_max; //record the pin(p) with the maximal congestion
    for (i = p_max = temp_max = 0; i < record_p_num; ++i) {//拥挤度计算
        for (j = temp = 0; j < 4; ++j) {
            temp += record_p[i][j];
        }
        if (temp > temp_max) {
            temp_max = temp;
            p_max = i;
        } else if (temp == temp_max) {
            if (fabs((double)(i/X_MAX - Y_MAX/2)) + fabs((double)(i%X_MAX - X_MAX/2)) <
                fabs((double)(p_max/X_MAX - Y_MAX/2)) + fabs((double)(p_max%X_MAX - X_MAX/2))) {
                temp_max = temp;
                p_max = i;
            }
        }
    }
    box[0] = box[2] = p_max / X_MAX;
    box[1] = box[3] = p_max % X_MAX;
    printf("p_max = %d\n", p_max);
    //fflush(stdout);
    int extend_to_bound = 0; //represnt the number of directions which extend to the bound of box
	bool to_bound[4];
	memset(to_bound, 0, sizeof(to_bound));
	int cnt = 0;
    while (extend_to_bound < 4) {
        if (!to_bound[0] && (box[0] += 1) >= Y_MAX) { //top
            box[0] = Y_MAX - 1;
			to_bound[0] = true;
            ++extend_to_bound;
        }
        if (!to_bound[1] && (box[1] += 1) >= X_MAX) {//right
            box[1] = X_MAX - 1;
			to_bound[1] = true;
            ++extend_to_bound;
        }
        if (!to_bound[2] && (box[2] -= 1) < 0) { //bottom
            box[2] = 0;
			to_bound[2] = true;
            ++extend_to_bound;
        }
        if (!to_bound[3] && (box[3] -= 1) < 0) {//left
            box[3] = 0;
			to_bound[3] = true;
            ++extend_to_bound;
        }
        set< pair<int, int> >::iterator spit;
        ilp_extend_point_vec.clear();
		//ilp_extend_point_vec2.clear();
		//ilp_extend_point_vec3.clear();
        ExpandNode xn;
		int __cnt = 0;
        for (i = 1; i <= net_num; ++i) {
            for (spit = line_net[i].unconnected.begin(); spit != line_net[i].unconnected.end(); ) {
                if (PointInBox(line_net[i].pin[spit->first][0], line_net[i].pin[spit->second][1])) {
                    xn.pa_id = spit->first;
                    xn.pb_id = spit->second;
                    xn.net_id = i;
					a = line_net[i].pin[spit->first][0] - line_net[i].pin[spit->second][0];
					b = line_net[i].pin[spit->first][1] - line_net[i].pin[spit->second][1];
					//printf("%d %d\n", line_net[i].pin[spit->first][0], line_net[i].pin[spit->first][1]);
					//printf("%d %d\n\n\n", line_net[i].pin[spit->second][0], line_net[i].pin[spit->second][1]);
					if (line_net[i].pin[spit->first][0] == line_net[i].pin[spit->second][0] || line_net[i].pin[spit->first][1] == line_net[i].pin[spit->second][1]){
						xn.cnt = 2;
						//printf("%d\n", xn.cnt);       //直角
					}
					else if (a == b || a == (-b)){
						xn.cnt = 3;
						//printf("%d\n", xn.cnt);        //X结构
					}
					else{
						xn.cnt = 1;                      //其他
					}
					ilp_extend_point_vec.push_back(xn);
                    //line_net[i].unconnected.erase(spit++);
                    spit=line_net[i].unconnected.erase(spit);
                } else {
                    spit++;
					++__cnt;
                }
            }
        }
		/*for (i = 0; i < ilp_extend_point_vec.size(); i++){
			printf("%d ", ilp_extend_point_vec[i].cnt);
		}
		printf("\n");*/
//		printf("box[1-4] = %d, %d, %d, %d\n", box[0], box[1], box[2], box[3]);
//        printf("ilp_extend_point_vec = %d\n", ilp_extend_point_vec.size());
        //fflush(stdout);
		++cnt;
		//printf("%d, ilp_extend_point_vec.size() = %d\n", cnt, ilp_extend_point_vec.size());
        /*if (ilp_extend_point_vec.size()) {
            ILP_PSO();
            ILP_Connect();
        }
		if (ilp_extend_point_vec2.size()){
			ILP_PSO2();
			ILP_Connect2();
		}
		if (ilp_extend_point_vec3.size()){
			ILP_PSO3();
			ILP_Connect3();
		}*/
		if (ilp_extend_point_vec.size()) {
			//printf("1\n");
			ILP_PSO4();
			//printf("2\n");
			ILP_Connect4();
			//printf("3\n");
		}
//		printf("===ilp_extend_point_vec.size() = %d\n", ilp_extend_point_vec.size());
		if (!__cnt) {
			//printf("ILP-PSO --- END \n");
/*			double std_deviation = CalcStandardDeviation()/10000;
			printf("std_deviation = %lf\n", std_deviation);
			fprintf(out_file_p, "std_deviation = %lf\n", std_deviation);*/
		}
		if (extend_unconnect.size()){
			ConnectTheRest();
		}
    }
}

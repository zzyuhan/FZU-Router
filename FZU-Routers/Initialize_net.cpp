void Initialize_net(int& cnt1, int& cnt2)
{
	int i, j = 1, p, q, jj = 1;
	memset(record_p, 0, sizeof(record_p)); //全部初始化为0
	FILE *fin;
	fin = fopen(INPUT_FILE, "r");
	char str[5];
	for (i = 0; i < 4; ++i) { //read the maximal overlappings of 4 direciton
		fscanf(fin, "%s", str);
		switch (str[0]) {
		case 'H':
			fscanf(fin, "%d", &max_h);
			max_line[0] = max_h;
			break;
		case 'V':
			fscanf(fin, "%d", &max_v);
			max_line[2] = max_v;
			break;
		case 'X':
			if (str[1] == '4') {
				fscanf(fin, "%d", &max_x45);
				max_line[1] = max_x45;
			}
			else {
				fscanf(fin, "%d", &max_x135);
				max_line[3] = max_x135;
			}
			break;
		}
	}
	for (i = 0; i <= Y_MAX; i++) {
		for (j = 0; j <= X_MAX; j++) {
			maxline[i*X_MAX + j][0] = max_h;
			maxline[i*X_MAX + j][1] = max_x45;
			maxline[i*X_MAX + j][2] = max_v;
			maxline[i*X_MAX + j][3] = max_x135;
		}
	}
	j = 1;
	printf("H:%d,X45:%d,V:%d,X135:%d\n", max_h, max_x45, max_v, max_x135);
	printf("H:%d,X45:%d,V:%d,X135:%d\n", max_line[0], max_line[1], max_line[2], max_line[3]);
	fprintf(out_file_p, "H:%d,X45:%d,V:%d,X135:%d\n", max_line[0], max_line[1], max_line[2], max_line[3]);
	set<Point> point_set;
	fscanf(fin, "%d", &net_num);
	printf("%d\n", net_num);
	fprintf(out_file_p, "%d\n", net_num);
	Point pt;
	int layer_val;
	big_net_num = 0;
	Net bignet;
	int judge;
	//int judge=0;
	for (i = 1; i <= net_num; i++) //	input the coordinate of each pin into the array graph
	{
		fscanf(fin, "%s", bignet.name);
		fscanf(fin, "%d%d%d%d", &bignet.serial_num, &bignet.pin_sum, &bignet.layer, &judge);
		//fscanf(fin, "%d%d%d", &bignet.serial_num, &bignet.pin_sum, &bignet.layer);
		if (judge == 0){
			line_net[i - big_net_num].serial_num = bignet.serial_num;
			line_net[i - big_net_num].pin_sum = bignet.pin_sum;
			line_net[i - big_net_num].layer = bignet.layer;
		}
		else{
		    //cout<<bignet.serial_num<<" "<<judge<<endl;
		    int aa,bb,cc;
		    for (j = 0; j < bignet.pin_sum; ++j) {
                fscanf(fin, "%d%d%d", &aa, &bb, &cc);
            }
			big_net_num++;
			continue;
		}
		//		line_net[i].serial_num = i-1;
		//		printf("%d \n", line_net[i].serial_num);
		//		printf("%s \n", line_net[i].name);
		point_set.clear();

		for (j = 0; j < line_net[i - big_net_num].pin_sum; ++j) {
			fscanf(fin, "%d%d%d", &pt.x, &pt.y, &layer_val);
			//printf("%d,%d,%d\n", pt.x, pt.y, layer_val);
			point_set.insert(pt);
		}
		vector<int> int_vec;
		int_vec.push_back(0);
		line_net[i - big_net_num].pin.push_back(int_vec);
		//printf("=front=%d,%d\n", point_set.begin()->x, point_set.begin()->y);
		set<Point>::iterator psit;
		for (psit = point_set.begin(), j = 0; psit != point_set.end(); ++psit, ++j) {
			//printf("=%d,%d\n", psit->x, psit->y);
			int_vec.clear();
			int_vec.push_back(psit->x);
			int_vec.push_back(psit->y);
			int_vec.push_back(layer_val);
			line_net[i - big_net_num].pin.push_back(int_vec);
		}
		point_set.clear();
		line_net[i - big_net_num].pin_sum = j;
		/*for (j = 1; j <= line_net[i].pin_sum; ++j) {
		printf("==%lf,%lf,%lf\n", line_net[i].pin[j][0], line_net[i].pin[j][1], line_net[i].pin[j][2]);
		}*/
		/*for(j=1;j<=line_net[i].pin_sum;j++) {
		//fscanf(fin,"%lf%lf%lf",&line_net[i].pin[j][0],&line_net[i].pin[j][1],&line_net[i].pin[j][2]);
		dou_vec.clear();
		for (int kk = 0; kk < 3; ++kk) {
		fscanf(fin, "%lf", &dou_temp);
		dou_vec.push_back(dou_temp);
		}
		line_net[i].pin.push_back(dou_vec);
		}*/

		line_net[i - big_net_num].graphw.clear();
		vector<double> dou_vec;
		double dou_temp;
		dou_vec.clear();
		dou_vec.push_back(0.0);
		line_net[i - big_net_num].graphw.push_back(dou_vec);
		for (p = 1; p <= line_net[i - big_net_num].pin_sum; p++) { // generate the distance matrix between each pin pair
			dou_vec.clear();
			dou_vec.push_back(0.0);
			for (q = 1; q <= line_net[i - big_net_num].pin_sum; q++) {
				//line_net[i].graphw[p][q]=fabs(line_net[i].pin[p][0]-line_net[i].pin[q][0])+fabs(line_net[i].pin[p][1]-line_net[i].pin[q][1]);
				dou_vec.push_back(fabs((double)(line_net[i - big_net_num].pin[p][0] - line_net[i - big_net_num].pin[q][0])) + fabs((double)(line_net[i - big_net_num].pin[p][1] - line_net[i - big_net_num].pin[q][1])));
			}
			line_net[i - big_net_num].graphw.push_back(dou_vec);
		}
	}
	net_num = net_num - big_net_num;
	fscanf(fin, "%d", &changenum);
	printf("----------------%d",changenum);
	//changenum=0;
	for (i = 1; i <= changenum; i++) {
		int layer1, layer2, x1, x2, y1, y2, change;
		int m1, m2, m3, m0;
		fscanf(fin, "%d%d%d%d%d%d%d", &x1, &y1, &layer1, &x2, &y2, &layer2, &change);
		if (y1 == y2){
			if (x1 < x2){
				maxline[y1*X_MAX + x1][3] = (int)(((double)change * 2) / (max_x45 + max_h + max_v + max_x135)*max_x135);
				maxline[y2*X_MAX + x2][0] = (int)(((double)change * 2) / (max_x45 + max_h + max_v + max_x135)*max_h);
				maxline[y2*X_MAX + x2][1] = (int)(((double)change * 2) / (max_x45 + max_h + max_v + max_x135)*max_x45);
			}
			else{
				maxline[y2*X_MAX + x2][3] = (int)(((double)change * 2) / (max_x45 + max_h + max_v + max_x135)*max_x135);
				maxline[y1*X_MAX + x1][0] = (int)(((double)change * 2) / (max_x45 + max_h + max_v + max_x135)*max_h);
				maxline[y1*X_MAX + x1][1] = (int)(((double)change * 2) / (max_x45 + max_h + max_v + max_x135)*max_x45);
			}
		}
		if (x1 == x2){
			if (y1 > y2){
				maxline[y2*X_MAX + x2][3] = (int)(((double)change * 2) / (max_x45 + max_h + max_v + max_x135)*max_x135);
				maxline[y2*X_MAX + x2][2] = (int)(((double)change * 2) / (max_x45 + max_h + max_v + max_x135)*max_v);
				maxline[y2*X_MAX + x2 + 1][1] = (int)(((double)change * 2) / (max_x45 + max_h + max_v + max_x135)*max_x45);
			}
			else{
				maxline[y1*X_MAX + x1][3] = (int)(((double)change * 2) / (max_x45 + max_h + max_v + max_x135)*max_x135);
				maxline[y1*X_MAX + x1][2] = (int)(((double)change * 2) / (max_x45 + max_h + max_v + max_x135)*max_v);
				maxline[y1*X_MAX + x1 + 1][1] = (int)(((double)change * 2) / (max_x45 + max_h + max_v + max_x135)*max_x45);
			}
		}
	}
	for (i = 0; i <= X_MAX; i++){
		maxline[i][0] = maxline[i][0] + maxline[i][1] + maxline[i][2] + maxline[i][3];

	}
	for (i = 1; i <= Y_MAX; i++){
		maxline[i*X_MAX + 1][2] = maxline[i*X_MAX + 1][0] + maxline[i*X_MAX + 1][1] + maxline[i*X_MAX + 1][2];
		maxline[i*X_MAX][2] = maxline[i*X_MAX][3] + maxline[i*X_MAX][2];
	}
	for (i = 1; i <= net_num; i++)
	{
		int cnt = 0;//aps test

		ver = i;//选择当前线网
		vertice = line_net[i].pin_sum;
		line_net[i].point_edge.clear();
		line_net[i].unconnected.clear();
		if (vertice == 2) { //the net has only two pins
			Point p1, p2;
			p1.x = line_net[i].pin[1][0]; //数组从1开始
			p1.y = line_net[i].pin[1][1];
			p2.x = line_net[i].pin[2][0];
			p2.y = line_net[i].pin[2][1];
			if (p2 < p1)
				swap(p1, p2);
			if (p1.x == p2.x || p1.y == p2.y || p2.y - p1.y == p2.x - p1.x
				|| p1.x - p2.x == p2.y - p1.y) { //	two pins in the same rectilinear lines.
				if (CheckP2P(i, p1, p2)) {             //通道满了
					ConnectP2P(i, p1, p2);
					++cnt1;
				}
				else {
					line_net[i].unconnected.insert(make_pair(1, 2));
					++cnt2;
				}
			}
			else { //two pins are not in the same rectilinear lines.          //一格之内到达不了
				srand((unsigned)time(NULL));
				line_net[i].unconnected.insert(make_pair(1, 2));
				++cnt2;
			}
		}
		else if (vertice > 2) { //	the net has more than two pins
			//利用pso生成最小生成树
			osmt(); //construct the OSMT by PSO
			//		printf("%d : %f\n",line_net[i].serial_num,line_net[i].fit_value);
			//totalwl=totalwl+line_net[i].fit_value;
			totalwl += gbest.fit_value;
			//		printf("%f\n",totalwl);
			line_net[i].point_edge.clear();
			line_net[i].unconnected.clear();
			Point p1, p2;
			for (j = 1; j < line_net[i].osmt.size(); j += 3) {
				p1.x = line_net[i].pin[line_net[i].osmt[j]][0];
				p1.y = line_net[i].pin[line_net[i].osmt[j]][1];
				p2.x = line_net[i].pin[line_net[i].osmt[j + 1]][0];
				p2.y = line_net[i].pin[line_net[i].osmt[j + 1]][1];
				if (p2 < p1) {
					swap(p1, p2);
				}
				if (p1.x == p2.x || p1.y == p2.y || p2.y - p1.y == p2.x - p1.x
					|| p1.x - p2.x == p2.y - p1.y) { //two pins in the same rectilinear lines
					if (CheckP2P(i, p1, p2)) {
						ConnectP2P(i, p1, p2, 0);
						++cnt1;
					}
					else {
						line_net[i].unconnected.insert(make_pair(line_net[i].osmt[j], line_net[i].osmt[j + 1]));
						++cnt; // aps test
						++cnt2;
					}
				}
				else { //two pins are not in the same rectilinear lines.
					line_net[i].unconnected.insert(make_pair(line_net[i].osmt[j], line_net[i].osmt[j + 1]));
					++cnt; // aps test
					++cnt2;
				}
			}
			//line_net[i].osmt.clear(); //清clear the storage of OSMT
			//printf("i = %d, unconnected size = %d\n", i, cnt);
		}
		//		if(i==686801)
		//			printf("i=%d\n",i);
		//		printf("i=%d\n",i);
	}
	fclose(fin);
}

#include "Header.h"
#include "Generate_mst.cpp"
#include "Getfitness.cpp"
#include "InitializePop.cpp"
#include "GetMutation.cpp"
#include "GetCrossover_self.cpp"
#include "GetCrossover_global.cpp"
#include "Osmt.cpp"
#include "CheckP2P.cpp"
#include "ConnectP2P.cpp"
#include "Initialize_net.cpp"
//#include "CalcStandardDeviation.cpp"
#include "ILP_CheckConnect.cpp"
#include "ILP_Connect.cpp"
#include "ILP_GetFitness.cpp"
#include "ILP_GetFitness2_std.cpp" //consider std
#include "ILP_Initialize.cpp"
#include "ILP_GetMutation.cpp"
#include "ILP_GetCrossover_self.cpp"
#include "ILP_GetCrossover_global.cpp"
#include "ILP_PSO.cpp"
#include "ExtendBox.cpp"
//#include "ConnectTheRest.cpp"
//#include "CalcStandardDeviationOnly.cpp"
//   Ox10000000
int work();
int main() {
	sprintf(INPUT_FILE, "%d.txt", test_num);

	int i;
	for (i = 1; i <= 5; ++i) {//为了测试将i<10改为i<1
		totalwl = 0;
		netvnum = 0;
		nethnum = 0;
		netx45num = 0;
		netx135num = 0;
		alltime = 0;
		sprintf(OUTPUT_FILE, "20230417/std_out_%d_%d.txt", test_num, i);             //i是迭代次数吗？应该是
		work();
		printf("=======================================================\n");
		printf("end of the %d iteration\n", i);
		printf("=======================================================\n");
	}
	return 0;
}

/////////////////////////////////////////////////

int work()
{
	//freopen(OUTPUT_FILE, "w", stdout);
	out_file_p = fopen(OUTPUT_FILE, "w");
	printf("X_MAX = %d, Y_MAX = %d\n", X_MAX, Y_MAX);
	fprintf(out_file_p, "X_MAX = %d, Y_MAX = %d\n", X_MAX, Y_MAX);
	printf("OSMT: popsize = %d, evaluations = %d\n", popsize, evaluations);
	fprintf(out_file_p, "OSMT: popsize = %d, evaluations = %d\n", popsize, evaluations);
	printf("ILP-PSO: popsize = %d, evaluations = %d\n", popsize_ilp, evaluations_ilp);
	fprintf(out_file_p, "ILP-PSO: popsize = %d, evaluations = %d\n", popsize_ilp, evaluations_ilp);

	printf("consider the std ?: %d\n", calc_std);
	fprintf(out_file_p, "consider the std ?: %d\n", calc_std);

	int i, j;
	int cnt1 = 0; //count of Rectilinear line
	int cnt2 = 0; //count of Octilinear line
	xnum = 0;
	lnum = 0;

	clock_t start = clock();
	srand(time(NULL));
	Initialize_net(cnt1, cnt2);
	printf("the number of 2-pin nets: %d, the failed connections: %d\n", cnt1 + cnt2, cnt2);
	fprintf(out_file_p, "the number of 2-pin nets: %d, the failed connections: %d\n", cnt1 + cnt2, cnt2);

	for (cnt1 = cnt2 = i = 0; i < X_MAX * Y_MAX; ++i) {
		cnt1 += record_p[i][0] + record_p[i][2];
		cnt2 += record_p[i][1] + record_p[i][3];
		for (j = 0; j < 4; ++j) {
			if (record_p[i][j] > maxline[i][j]) {
				printf("%d,%d: %d,%d,%d,%d\n", i / Y_MAX, i % Y_MAX, record_p[i][0], record_p[i][1], record_p[i][2], record_p[i][3]);
				fprintf(out_file_p, "%d,%d: %d,%d,%d,%d\n", i / Y_MAX, i % Y_MAX, record_p[i][0], record_p[i][1], record_p[i][2], record_p[i][3]);
			}
		}
	}
	printf("after Initialize_net...cnt1 = %d, cnt2 = %d\n", cnt1, cnt2);
	fprintf(out_file_p, "after Initialize_net...cnt1 = %d, cnt2 = %d\n", cnt1, cnt2);
	printf("totalwl = %lf\n", totalwl);
	fprintf(out_file_p, "totalwl = %lf\n", totalwl);
	clock_t finish = clock();
	printf("Initialize_net, running time: %lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
	fprintf(out_file_p, "Initialize_net, running time: %lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
	alltime += (double)(finish - start) / CLOCKS_PER_SEC;
	start = finish;
	//	fprintf(out_file_p, "==std_deviation = %lf\n", CalcStandardDeviationOnly()/10000);
	//fflush(stdout);
	ExtendBox();
	cnt1 = 0;
	cnt2 = 0;
	for (i = 0; i < X_MAX * Y_MAX; ++i) {
		cnt1 += record_p[i][0] + record_p[i][2];
		cnt2 += record_p[i][1] + record_p[i][3];
		for (j = 0; j < 4; ++j) {
			if (record_p[i][j] > maxline[i][j]) {
				printf("%d,%d: %d,%d,%d,%d\n", i / Y_MAX, i % Y_MAX, record_p[i][0], record_p[i][1], record_p[i][2], record_p[i][3]);
				fprintf(out_file_p, "%d,%d: %d,%d,%d,%d\n", i / Y_MAX, i % Y_MAX, record_p[i][0], record_p[i][1], record_p[i][2], record_p[i][3]);
			}
		}
	}
	printf("after ExtendBox...cnt1 = %d, cnt2 = %d\n", cnt1, cnt2);
	fprintf(out_file_p, "after ExtendBox...cnt1 = %d, cnt2 = %d\n", cnt1, cnt2);

	set<ExpandNode>::iterator it;
	for (cnt1 = 0, it = extend_unconnect.begin(); it != extend_unconnect.end(); ++it) {
		++cnt1;
		/*Point p1, p2;
		int net_id = it->net_id;
		p1.x = line_net[net_id].pin[it->pa_id][0];
		p1.y = line_net[net_id].pin[it->pa_id][1];
		p2.x = line_net[net_id].pin[it->pb_id][0];
		p2.y = line_net[net_id].pin[it->pb_id][1];
		printf("%d,%d to %d,%d\n", p1.x, p1.y, p2.x, p2.y);*/
	}
	printf("extend_unconnect size() = %d\n", cnt1);
	fprintf(out_file_p, "extend_unconnect size() = %d\n", cnt1);
	finish = clock();
	printf("ExtendBox, running time:%lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
	fprintf(out_file_p, "ExtendBox, running time:%lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
	alltime += (double)(finish - start) / CLOCKS_PER_SEC;

	for (i = 1; i <= net_num; ++i) {
		cnt1 = 0;
		set< pair<int, int> >::iterator spit;
		for (spit = line_net[i].unconnected.begin(); spit != line_net[i].unconnected.end(); ++spit) {
			++cnt1;
		}
		/*		if (cnt1) {
		printf("==line_net[%d].unconnected.size() = %d\n", i, cnt1);
		fprintf(out_file_p, "==line_net[%d].unconnected.size() = %d\n", i, cnt1);
		}
		*/
	}
	start = finish;
	//ConnectTheRest();
	printf("end\n");

	finish = clock();
	printf("ConnectTheRest, running time:%lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
	fprintf(out_file_p, "ConnectTheRest, running time:%lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
	alltime += (double)(finish - start) / CLOCKS_PER_SEC;

	for (cnt1 = 0, it = extend_unconnect.begin(); it != extend_unconnect.end(); ++it) {
		++cnt1;
		Point p1, p2;
		int net_id = it->net_id;
		p1.x = line_net[net_id].pin[it->pa_id][0];
		p1.y = line_net[net_id].pin[it->pa_id][1];
		p2.x = line_net[net_id].pin[it->pb_id][0];

		p2.y = line_net[net_id].pin[it->pb_id][1];
		//printf("%d,%d to %d,%d\n", p1.x, p1.y, p2.x, p2.y);
		//fprintf(out_file_p, "%d,%d to %d,%d\n", p1.x, p1.y, p2.x, p2.y);
	}
	printf("after ConnectTheRest extend_unconnect size() = %d\n", cnt1);
	fprintf(out_file_p, "after ConnectTheRest extend_unconnect size() = %d\n", cnt1);

	/*FILE *fstm;
	if (fstm = fopen(RECORD_FILE, "w")) {
	printf("record_file open success");
	} else {
	printf("record_file open fail");
	}*/

	cnt1 = 0;
	cnt2 = 0;
	for (i = 0; i < X_MAX * Y_MAX; ++i) {
		cnt1 += record_p[i][0] + record_p[i][2];
		cnt2 += record_p[i][1] + record_p[i][3];
		for (j = 0; j < 4; ++j) {
			if (record_p[i][j] > maxline[i][j]) {
				printf("%d,%d: %d,%d,%d,%d\n", i / Y_MAX, i % Y_MAX, record_p[i][0], record_p[i][1], record_p[i][2], record_p[i][3]);
				fprintf(out_file_p, "%d,%d: %d,%d,%d,%d\n", i / Y_MAX, i % Y_MAX, record_p[i][0], record_p[i][1], record_p[i][2], record_p[i][3]);
			}
		}
		//fprintf(fstm, "%d,%d: %d,%d,%d,%d\n", i / Y_MAX, i % Y_MAX, record_p[i][0], record_p[i][1], record_p[i][2], record_p[i][3]);
	}
	printf("after ConnectTheRest...cnt1 = %d, cnt2 = %d\n", cnt1, cnt2);
	fprintf(out_file_p, "after ConnectTheRest...cnt1 = %d, cnt2 = %d\n", cnt1, cnt2);
	double ans = 0.0;
	ans = (double)cnt1 + cnt2 * sqrt(2);
	printf("total length = %lf\n", ans);
	fprintf(out_file_p, "total length = %lf\n", ans);

	printf("number of horizontal = %d\n", nethnum);
	fprintf(out_file_p, "number of horizontal = %d\n", nethnum);

	printf("number of vertical = %d\n", netvnum);
	fprintf(out_file_p, "number of vertical = %d\n", netvnum);

	printf("number of x45 = %d\n", netx45num);
	fprintf(out_file_p, "number of x45 = %d\n", netx45num);

	printf("number of x135 = %d\n", netx135num);
	fprintf(out_file_p, "number of x135 = %d\n", netx135num);

	printf("number of xpsorouting = %d\n", xnum);
	fprintf(out_file_p, "number of xpsorouting = %d\n", xnum);

	printf("number of linearpsorouting = %d\n", lnum);
	fprintf(out_file_p, "number of linearpsorouting = %d\n", lnum);

	printf("number of via = %d\n", (netx45num + netx135num) * 2);
	fprintf(out_file_p, "number of via = %d\n", (netx45num + netx135num) * 2);

	printf("wl = %lf\n", (netx45num + netx135num) * 6 + ans);
	fprintf(out_file_p, "wl = %lf\n", (netx45num + netx135num) * 6 + ans);

	printf("time = %lf\n", alltime);
	fprintf(out_file_p, "time = %lf\n", alltime);

	//fprintf(out_file_p, "==std_deviation = %lf\n", CalcStandardDeviationOnly()/10000);

	fclose(out_file_p);

	return 0;
}


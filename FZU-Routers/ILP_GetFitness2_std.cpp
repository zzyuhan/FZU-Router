//consider the standard deviation
double ILP_GetFitness2(const int& pop_ind) {
	int penalty = 1; //record the violations of capacity constraints
    set< pair<int, int> > ilp_connect; //the first demension represents the name of net, the second one represents the number and the direction
    map<int, int> ilp_connect_count; //record the connections of one pin at one direction in one solution of ILP
    double len = 0.0; // the length to be added????
    const double sq2 = sqrt(2.0);
    Point p1, p2, pt;
    int i;
    for (i = 0; i < pop_ilp[pop_ind].sol.size(); ++i) {
        int net_id = ilp_extend_point_vec[i].net_id;
        p1.x = line_net[net_id].pin[ilp_extend_point_vec[i].pa_id][0];
        p1.y = line_net[net_id].pin[ilp_extend_point_vec[i].pa_id][1];
        p2.x = line_net[net_id].pin[ilp_extend_point_vec[i].pb_id][0];
        p2.y = line_net[net_id].pin[ilp_extend_point_vec[i].pb_id][1];
        if (p2 < p1)
            swap(p1, p2);
        if (pop_ilp[pop_ind].sol[i]) { // 1 represents first rectilinear then X-architecture
            if (p2.x > p1.x) { //right-top direction
                pt = p2;
                if (p2.x - p1.x < p2.y - p1.y) {
                    for ( ; pt.x > p1.x; --pt.x, --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 1 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            len += sq2;
                        }
                    }
                    for ( ; pt.y > p1.y; --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 2 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            len += 1;
                        }
                    }
                } else {
                    for ( ; pt.y > p1.y; --pt.x, --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 1 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            len += sq2;
                        }
                    }
                    for ( ; pt.x > p1.x; --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 0 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            len += 1;
                        }
                    }
                }
            } else { //left-top direction
                pt = p2;
                if (p2.y - p1.y < p1.x - p2.x) {
                    for ( ; pt.y > p1.y; ++pt.x, --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 3 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            len += sq2;
                        }
                    }
                    for (pt.x = p1.x; pt.x > p2.x + (p2.y - p1.y); --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 0 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            len += 1;
                        }
                    }
                } else {
                    for (; pt.x < p1.x; --pt.y, ++pt.x) {
                        int num = pt.y * X_MAX + pt.x + 3 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            len += sq2;
                        }
                    }
                    for ( ; pt.y > p1.y; --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 2 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            len += 1;
                        }
                    }
                }
            }
        } else { // 0 repsents first X-architecture then rectilineaer
            if (p2.x > p1.x) { //right-top direction
                pt = p2;
                if (p2.y - p1.y < p2.x - p1.x) {
                    for ( ; pt.x > p1.x + p2.y - p1.y; --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 0 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            len += 1;
                            ++ilp_connect_count[num];
                        }
                    }
                    for ( ; pt.y > p1.y; --pt.y, --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 1 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            len += sq2;
                            ++ilp_connect_count[num];
                        }
                    }
                } else {
                    for ( ; pt.y > p1.y + p2.x - p1.x; --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 2 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            len += 1;
                            ++ilp_connect_count[num];
                        }
                    }
                    for ( ; pt.y > p1.y; --pt.y, --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 1 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            len += sq2;
                            ++ilp_connect_count[num];
                        }
                    }
                }
            } else { //left-top direction
                if (p2.y - p1.y < p1.x - p2.x) {
                    pt.y = p2.y;
                    pt.x = p1.x - (p2.y - p1.y);
                    for ( ; pt.x > p2.x; --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 0 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            len += 1;
                            ++ilp_connect_count[num];
                        }
                    }
                    pt.y = p2.y;
                    pt.x = p1.x - (p2.y - p1.y);
                    for ( ; pt.x < p1.x ; ++pt.x, --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 3 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            len += sq2;
                            ++ilp_connect_count[num];
                        }
                    }
                } else {
                    for (pt = p2; pt.y > p1.y + p1.x - p2.x; --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 2 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            len += 1;
                            ++ilp_connect_count[num];
                        }
                    }
                    for (; pt.y > p1.y; --pt.y, ++pt.x) {
                        int num = pt.y * X_MAX + pt.x + 3 * XYMAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            len += sq2;
                            ++ilp_connect_count[num];
                        }
                    }
                    
                }
            }
        }

    }
	double ret;
	if (calc_std) {
		int record_p_compute[XYMAX * 4 + 3];
		
		for (i = 0; i < XYMAX * 4 + 2; ++i) {
			record_p_compute[i] = record_p[i % XYMAX][i / XYMAX];
		}
		map<int, int>::iterator itm;
		for (itm = ilp_connect_count.begin(); itm == ilp_connect_count.end(); ++itm) {
			int tmp = itm->second + record_p[itm->first % XYMAX][itm->first / XYMAX] - max_line[itm->first / XYMAX];
			penalty += tmp > 0 ? tmp : 0;
			record_p_compute[itm->first] += itm->second;
		}
		vector< vector<double> > calc_std_deviation; //store the routes?? of the calculated edge //use to calculate the std
		int j;
		for (j = 0; j < 4; ++j) {
			vector<double> db_vec;
			db_vec.clear();
			calc_std_deviation.push_back(db_vec);
		}
		for (pt.x = box[1], pt.y = box[2]; pt.x > box[3]; --pt.x) { //the edge in the bottom of box
			calc_std_deviation[0].push_back(record_p_compute[pt.y * X_MAX + pt.x + 0 * XYMAX] / max_line[0]);
		}
		for (pt.x = box[3], pt.y = box[0]; pt.y > box[2]; --pt.y) { //the edge in the left of box
			calc_std_deviation[2].push_back(record_p_compute[pt.y * X_MAX + pt.x + 2 * XYMAX] / max_line[2]);
			calc_std_deviation[3].push_back(record_p_compute[pt.y * X_MAX + pt.x + 3 * XYMAX] / max_line[3]);
		}
		for (pt.x = box[1], pt.y = box[0]; pt.y > box[2]; --pt.y) { //the edge in the right of box
			calc_std_deviation[0].push_back(record_p_compute[pt.y * X_MAX + pt.x + 0 * XYMAX] / max_line[0]);
			calc_std_deviation[1].push_back(record_p_compute[pt.y * X_MAX + pt.x + 1 * XYMAX] / max_line[1]);
			calc_std_deviation[2].push_back(record_p_compute[pt.y * X_MAX + pt.x + 2 * XYMAX] / max_line[2]);
		}
		for (pt.x = box[1] - 1; pt.x > box[3]; --pt.x) {
			for (pt.y = box[0] - 1; pt.y > box[2]; --pt.y) {
				calc_std_deviation[0].push_back(record_p_compute[pt.y * X_MAX + pt.x + 0 * XYMAX] / max_line[0]);
				calc_std_deviation[1].push_back(record_p_compute[pt.y * X_MAX + pt.x + 1 * XYMAX] / max_line[1]);
				calc_std_deviation[2].push_back(record_p_compute[pt.y * X_MAX + pt.x + 2 * XYMAX] / max_line[2]);
				calc_std_deviation[3].push_back(record_p_compute[pt.y * X_MAX + pt.x + 3 * XYMAX] / max_line[3]);
			}
		}
		double std_deviation[4]; //std
		double ave[4];
		fill(std_deviation, std_deviation + 4, 0.0);
		fill(ave, ave + 4, 0.0);
		for (j = 0; j < 4; ++j) {
			for (i = 0; i < calc_std_deviation.size(); ++i) {
				ave[j] += (double) calc_std_deviation[j][i];
			}
		}
		for (j = 0; j < 4; ++j) {
			ave[j] /= calc_std_deviation[j].size();
		}
		for (j = 0; j < 4; ++j) {
			for (i = 0; i < calc_std_deviation.size(); ++i) {
				std_deviation[j] += (calc_std_deviation[j][i] - ave[j]) * (calc_std_deviation[j][i] - ave[j]);
			}
		}
		for (j = 0; j < 4; ++j) {
			std_deviation[j] /= calc_std_deviation[j].size();
		}
		ret = len;
		for (j = 0; j < 4; ++j) {
			std_deviation[j] = sqrt(std_deviation[j]);
			len += std_deviation[j] * 10000;
		}
		
		//ret = len + std_deviation * 1000;
	} else {
		map<int, int>::iterator itm;
		for (itm = ilp_connect_count.begin(); itm == ilp_connect_count.end(); ++itm) {
			int tmp = itm->second + record_p[itm->first % XYMAX][itm->first / XYMAX] - max_line[itm->first / XYMAX];
			penalty += tmp > 0 ? tmp : 0;
			//record_p_compute[itm->first] += itm->second;
		}
		ret = len;
	}

	
	ret *= pow(1.01, penalty); //penalty
    return ret;
}
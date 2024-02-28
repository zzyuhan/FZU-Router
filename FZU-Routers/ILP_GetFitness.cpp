double ILP_GetFitness(const int& pop_ind) {
	int penalty = 1; // record the violations of capacity constraints
    set< pair<int, int> > ilp_connect; //	the first demension represents the name of net, the second one represents the number and the direction
    map<int, int> ilp_connect_count; //	record the connections of one pin at one direction in one solution of ILP
    double ret = 0.0;
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
                        int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            ret += sq2;
                        }
                    }
                    for ( ; pt.y > p1.y; --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            ret += 1;
                        }
                    }
                } else {
                    for ( ; pt.y > p1.y; --pt.x, --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            ret += sq2;
                        }
                    }
                    for ( ; pt.x > p1.x; --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            ret += 1;
                        }
                    }
                }
            } else { //left-top direction
                pt = p2;
                if (p2.y - p1.y < p1.x - p2.x) {
                    for ( ; pt.y > p1.y; ++pt.x, --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            ret += sq2;
                        }
                    }
                    for (pt.x = p1.x; pt.x > p2.x + (p2.y - p1.y); --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            ret += 1;
                        }
                    }
                } else {
                    for (; pt.x < p1.x; --pt.y, ++pt.x) {
                        int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            ret += sq2;
                        }
                    }
                    for ( ; pt.y > p1.y; --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ++ilp_connect_count[num];
                            ret += 1;
                        }
                    }
                }
            }
        } else { // 0 repsents first X-architecture then rectilineaer
            if (p2.x > p1.x) { //right-top direction
                pt = p2;
                if (p2.y - p1.y < p2.x - p1.x) {
                    for ( ; pt.x > p1.x + p2.y - p1.y; --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ret += 1;
                            ++ilp_connect_count[num];
                        }
                    }
                    for ( ; pt.y > p1.y; --pt.y, --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ret += sq2;
                            ++ilp_connect_count[num];
                        }
                    }
                } else {
                    for ( ; pt.y > p1.y + p2.x - p1.x; --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ret += 1;
                            ++ilp_connect_count[num];
                        }
                    }
                    for ( ; pt.y > p1.y; --pt.y, --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ret += sq2;
                            ++ilp_connect_count[num];
                        }
                    }
                }
            } else { //left-top direction
                if (p2.y - p1.y < p1.x - p2.x) {
                    pt.y = p2.y;
                    pt.x = p1.x - (p2.y - p1.y);
                    for ( ; pt.x > p2.x; --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ret += 1;
                            ++ilp_connect_count[num];
                        }
                    }
                    pt.y = p2.y;
                    pt.x = p1.x - (p2.y - p1.y);
                    for ( ; pt.x < p1.x ; ++pt.x, --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ret += sq2;
                            ++ilp_connect_count[num];
                        }
                    }
                } else {
                    for (pt = p2; pt.y > p1.y + p1.x - p2.x; --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ret += 1;
                            ++ilp_connect_count[num];
                        }
                    }
                    for (; pt.y > p1.y; --pt.y, ++pt.x) {
                        int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
                            && ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
                            ilp_connect.insert(make_pair(net_id, num));
                            ret += sq2;
                            ++ilp_connect_count[num];
                        }
                    }

                }
            }
        }

    }
    map<int, int>::iterator itm;
    for (itm = ilp_connect_count.begin(); itm == ilp_connect_count.end(); ++itm) {
        switch(itm->first / (X_MAX * Y_MAX)) {
        case 0:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][0] > maxline[itm->first % (X_MAX * Y_MAX)][0])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][0] - maxline[itm->first % (X_MAX * Y_MAX)][0];
            break;
        case 1:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][1] > maxline[itm->first % (X_MAX * Y_MAX)][1])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][1] - maxline[itm->first % (X_MAX * Y_MAX)][1];
            break;
        case 2:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][2] > maxline[itm->first % (X_MAX * Y_MAX)][2])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][2] - maxline[itm->first % (X_MAX * Y_MAX)][2];
            break;
        case 3:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][3] > maxline[itm->first % (X_MAX * Y_MAX)][3])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][3] - maxline[itm->first % (X_MAX * Y_MAX)][3];
            break;
        }
    }
	ret *= pow(1.01, penalty); //	penalty the fitness function
    return ret;
}
double ILP_GetFitness22(const int& pop_ind) {
	int penalty = 1; // record the violations of capacity constraints
	set< pair<int, int> > ilp_connect; //	the first demension represents the name of net, the second one represents the number and the direction
	map<int, int> ilp_connect_count; //	record the connections of one pin at one direction in one solution of ILP
	double ret = 0.0;
	const double sq2 = sqrt(2.0);
	Point p1, p2, pt, pt1, pt2;
	int i;
	for (i = 0; i < pop_ilp[pop_ind].sol.size(); ++i) {
		int net_id = ilp_extend_point_vec2[i].net_id;
		p1.x = line_net[net_id].pin[ilp_extend_point_vec2[i].pa_id][0];
		p1.y = line_net[net_id].pin[ilp_extend_point_vec2[i].pa_id][1];
		p2.x = line_net[net_id].pin[ilp_extend_point_vec2[i].pb_id][0];
		p2.y = line_net[net_id].pin[ilp_extend_point_vec2[i].pb_id][1];
		if (p2 < p1)
			swap(p1, p2);
		if (pop_ilp[pop_ind].sol[i]) { // 1 represents down or left
			if (p2.x == p1.x) { //left direction
				if ((p1.y + p2.y) % 2 == 0){
					if ((p1.x - (p2.y - p1.y) / 2) >= 0){
						pt = p1;
						for (; pt.x > (p1.x - (p2.y - p1.y) / 2); --pt.x, ++pt.y) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt = p2;
						for (; pt.x > (p1.x - (p2.y - p1.y) / 2); --pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
					}
					else{
						pt1 = p1;
						for (; pt1.x > 0; --pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt2 = p2;
						for (; pt2.x > 0; --pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt1.y < p2.y; ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
				}
				else{
					if ((p1.x - (p2.y - p1.y) / 2) >= 0){
						pt1 = p1;
						for (; pt1.x > (p1.x - (p2.y - p1.y) / 2); --pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt2 = p2;
						for (; pt2.x > (p1.x - (p2.y - p1.y) / 2); --pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt1.y < p2.y; ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
					else{
						pt1 = p1;
						for (; pt1.x > 0; --pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt2 = p2;
						for (; pt2.x > 0; --pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt1.y < p2.y; ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
				}
			}
			else { //down direction
				if ((p1.x + p2.x) % 2 == 0){
					if ((p1.y - (p2.x - p1.x) / 2) >= 0){
						pt = p1;
						for (; pt.y > (p1.y - (p2.x - p1.x) / 2); --pt.y, ++pt.x) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt = p2;
						for (; pt.y > (p1.y - (p2.x - p1.x) / 2); --pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
					}
					else{
						pt1 = p1;
						for (; pt1.y > 0; --pt1.y, ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt2 = p2;
						for (; pt2.y > 0; --pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt1.x < p2.x; ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
				}
				else{
					if ((p1.y - (p2.x - p1.x) / 2) >= 0){
						pt1 = p1;
						for (; pt1.y > (p1.y - (p2.x - p1.x) / 2); --pt1.y, ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt2 = p2;
						for (; pt2.y > (p1.y - (p2.x - p1.x) / 2); --pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt1.x < p2.x; ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
					else{
						pt1 = p1;
						for (; pt1.y > 0; --pt1.y, ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt2 = p2;
						for (; pt2.y > 0; --pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt1.x < p2.x; ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
				}
			}
		}
		else { // 0 repsents up or right
			if (p2.x == p1.x) { //right direction
				if ((p1.y + p2.y) % 2 == 0){
					if ((p1.x + (p2.y - p1.y) / 2) <= X_MAX){
						pt = p1;
						for (; pt.x < (p1.x + (p2.y - p1.y) / 2); ++pt.x, ++pt.y) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt = p2;
						for (; pt.x < (p1.x + (p2.y - p1.y) / 2); ++pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
					}
					else{
						pt1 = p1;
						for (; pt1.x < X_MAX; ++pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt2 = p2;
						for (; pt2.x < X_MAX; ++pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt1.y < p2.y; ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
				}
				else{
					if ((p1.x + (p2.y - p1.y) / 2) <= X_MAX){
						pt1 = p1;
						for (; pt1.x < (p1.x + (p2.y - p1.y) / 2); ++pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt2 = p2;
						for (; pt2.x < (p1.x + (p2.y - p1.y) / 2); ++pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt1.y < p2.y; ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
					else{
						pt1 = p1;
						for (; pt1.x < X_MAX; ++pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt2 = p2;
						for (; pt2.x < X_MAX; ++pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt1.y < p2.y; ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
				}
			}
			else { //up direction
				if ((p1.x + p2.x) % 2 == 0){
					if ((p1.y + (p2.x - p1.x) / 2) <= Y_MAX){
						pt = p1;
						for (; pt.y < (p1.y + (p2.x - p1.x) / 2); ++pt.x, ++pt.y) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt = p2;
						for (; pt.y < (p1.y + (p2.x - p1.x) / 2); ++pt.y, --pt.x) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
					}
					else{
						pt1 = p1;
						for (; pt1.y < Y_MAX; ++pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt2 = p2;
						for (; pt2.y < Y_MAX; ++pt2.y, --pt2.x) {
							int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt1.x < p2.x; ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
				}
				else{
					if ((p1.y + (p2.x - p1.x) / 2) <= Y_MAX){
						pt1 = p1;
						for (; pt1.y < (p1.y + (p2.x - p1.x) / 2); ++pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt2 = p2;
						for (; pt2.y < (p1.y + (p2.x - p1.x) / 2); ++pt2.y, --pt2.x) {
							int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt1.x < p2.x; ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
					else{
						pt1 = p1;
						for (; pt1.y < Y_MAX; ++pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						pt2 = p2;
						for (; pt2.y < Y_MAX; ++pt2.y, --pt2.x) {
							int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt1.x < p2.x; ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
				}
			}
		}

	}
	map<int, int>::iterator itm;
	for (itm = ilp_connect_count.begin(); itm == ilp_connect_count.end(); ++itm) {
		switch (itm->first / (X_MAX * Y_MAX)) {
		case 0:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][0] > maxline[itm->first % (X_MAX * Y_MAX)][0])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][0] - maxline[itm->first % (X_MAX * Y_MAX)][0];
			break;
		case 1:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][1] > maxline[itm->first % (X_MAX * Y_MAX)][1])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][1] - maxline[itm->first % (X_MAX * Y_MAX)][1];
			break;
		case 2:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][2] > maxline[itm->first % (X_MAX * Y_MAX)][2])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][2] - maxline[itm->first % (X_MAX * Y_MAX)][2];
			break;
		case 3:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][3] > maxline[itm->first % (X_MAX * Y_MAX)][3])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][3] - maxline[itm->first % (X_MAX * Y_MAX)][3];
			break;
		}
	}
	ret *= pow(1.01, penalty); //	penalty the fitness function
	return ret;
}
double ILP_GetFitness3(const int& pop_ind) {
	int penalty = 1; // record the violations of capacity constraints
	set< pair<int, int> > ilp_connect; //	the first demension represents the name of net, the second one represents the number and the direction
	map<int, int> ilp_connect_count; //	record the connections of one pin at one direction in one solution of ILP
	double ret = 0.0;
	const double sq2 = sqrt(2.0);
	Point p1, p2, pt;
	int i;
	for (i = 0; i < pop_ilp[pop_ind].sol.size(); ++i) {
		int net_id = ilp_extend_point_vec3[i].net_id;
		p1.x = line_net[net_id].pin[ilp_extend_point_vec3[i].pa_id][0];
		p1.y = line_net[net_id].pin[ilp_extend_point_vec3[i].pa_id][1];
		p2.x = line_net[net_id].pin[ilp_extend_point_vec3[i].pb_id][0];
		p2.y = line_net[net_id].pin[ilp_extend_point_vec3[i].pb_id][1];
		if (p2 < p1)
			swap(p1, p2);
		pt = p2;
		if (pop_ilp[pop_ind].sol[i]) { // 1 represents first horizontal then vertical
			if (p1.x < p2.x){//right-top
				for (; pt.y > p1.y; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret += 1;
					}
				}
				for (; pt.x > p1.x; --pt.x) {
					int num = pt.y * X_MAX + pt.x;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret += 1;
					}
				}
			}
			else{//left-top
				for (; pt.y > p1.y; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret += 1;
					}
				}
				for (; pt.x < p1.x; ++pt.x) {
					int num = pt.y * X_MAX + pt.x;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret += 1;
					}
				}
			}
		}
		else { // 0 repsents first vertical then horizontal
			if (p1.x < p2.x){//right-top
				for (; pt.x > p1.x; --pt.x) {
					int num = pt.y * X_MAX + pt.x;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret += 1;
					}
				}
				for (; pt.y > p1.y; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret += 1;
					}
				}
			}
			else{//left-top
				for (; pt.x < p1.x; ++pt.x) {
					int num = pt.y * X_MAX + pt.x;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret += 1;
					}
				}
				for (; pt.y > p1.y; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret += 1;
					}
				}

			}
		}

	}
	map<int, int>::iterator itm;
	for (itm = ilp_connect_count.begin(); itm == ilp_connect_count.end(); ++itm) {
		switch (itm->first / (X_MAX * Y_MAX)) {
		case 0:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][0] > maxline[itm->first % (X_MAX * Y_MAX)][0])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][0] - maxline[itm->first % (X_MAX * Y_MAX)][0];
			break;
		case 1:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][1] > maxline[itm->first % (X_MAX * Y_MAX)][1])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][1] - maxline[itm->first % (X_MAX * Y_MAX)][1];
			break;
		case 2:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][2] > maxline[itm->first % (X_MAX * Y_MAX)][2])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][2] - maxline[itm->first % (X_MAX * Y_MAX)][2];
			break;
		case 3:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][3] > maxline[itm->first % (X_MAX * Y_MAX)][3])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][3] - maxline[itm->first % (X_MAX * Y_MAX)][3];
			break;
		}
	}
	ret *= pow(1.01, penalty); //	penalty the fitness function
	return ret;
}
double GetRet1(bool flag, int net_id, Point p1, Point p2, Point pt, double sq2, set< pair<int, int> >& ilp_connect, map<int, int>& ilp_connect_count){
	double ret1 = 0.0;
	if (flag) { // 1 represents first rectilinear then X-architecture
		if (p2.x > p1.x) { //right-top direction
			pt = p2;
			if (p2.x - p1.x < p2.y - p1.y) {
				for (; pt.x > p1.x; --pt.x, --pt.y) {
					int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret1 += sq2;
					}
				}
				for (; pt.y > p1.y; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret1 += 1;
					}
				}
			}
			else {
				for (; pt.y > p1.y; --pt.x, --pt.y) {
					int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret1 += sq2;
					}
				}
				for (; pt.x > p1.x; --pt.x) {
					int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret1 += 1;
					}
				}
			}
		}
		else { //left-top direction
			pt = p2;
			if (p2.y - p1.y < p1.x - p2.x) {
				for (; pt.y > p1.y; ++pt.x, --pt.y) {
					int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret1 += sq2;
					}
				}
				for (pt.x = p1.x; pt.x > p2.x + (p2.y - p1.y); --pt.x) {
					int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret1 += 1;
					}
				}
			}
			else {
				for (; pt.x < p1.x; --pt.y, ++pt.x) {
					int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret1 += sq2;
					}
				}
				for (; pt.y > p1.y; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						++ilp_connect_count[num];
						ret1 += 1;
					}
				}
			}
		}
	}
	else { // 0 repsents first X-architecture then rectilineaer
		if (p2.x > p1.x) { //right-top direction
			pt = p2;
			if (p2.y - p1.y < p2.x - p1.x) {
				for (; pt.x > p1.x + p2.y - p1.y; --pt.x) {
					int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						ret1 += 1;
						++ilp_connect_count[num];
					}
				}
				for (; pt.y > p1.y; --pt.y, --pt.x) {
					int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						ret1 += sq2;
						++ilp_connect_count[num];
					}
				}
			}
			else {
				for (; pt.y > p1.y + p2.x - p1.x; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						ret1 += 1;
						++ilp_connect_count[num];
					}
				}
				for (; pt.y > p1.y; --pt.y, --pt.x) {
					int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						ret1 += sq2;
						++ilp_connect_count[num];
					}
				}
			}
		}
		else { //left-top direction
			if (p2.y - p1.y < p1.x - p2.x) {
				pt.y = p2.y;
				pt.x = p1.x - (p2.y - p1.y);
				for (; pt.x > p2.x; --pt.x) {
					int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						ret1 += 1;
						++ilp_connect_count[num];
					}
				}
				pt.y = p2.y;
				pt.x = p1.x - (p2.y - p1.y);
				for (; pt.x < p1.x; ++pt.x, --pt.y) {
					int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						ret1 += sq2;
						++ilp_connect_count[num];
					}
				}
			}
			else {
				for (pt = p2; pt.y > p1.y + p1.x - p2.x; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						ret1 += 1;
						++ilp_connect_count[num];
					}
				}
				for (; pt.y > p1.y; --pt.y, ++pt.x) {
					int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
						ilp_connect.insert(make_pair(net_id, num));
						ret1 += sq2;
						++ilp_connect_count[num];
					}
				}

			}
		}
	}
	return ret1;
}
double GetRet2(bool flag, int net_id, Point p1, Point p2, Point pt, Point pt1, Point pt2, double sq2, set< pair<int, int> >& ilp_connect, map<int, int>& ilp_connect_count){
	double ret2 = 0.0;
	if (flag) { // 1 represents down or left
		if (p2.x == p1.x) { //left direction
			if ((p1.y + p2.y) % 2 == 0){
				if ((p1.x - (p2.y - p1.y) / 2) >= 0){
					pt = p1;
					for (; pt.x > (p1.x - (p2.y - p1.y) / 2); --pt.x, ++pt.y) {
						int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt = p2;
					for (; pt.x > (p1.x - (p2.y - p1.y) / 2); --pt.x, --pt.y) {
						int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.x > 0; --pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt2 = p2;
					for (; pt2.x > 0; --pt2.x, --pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					for (; pt1.y < p2.y; ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += 1;
						}
					}
				}
			}
			else{
				if ((p1.x - (p2.y - p1.y) / 2) >= 0){
					pt1 = p1;
					for (; pt1.x > (p1.x - (p2.y - p1.y) / 2); --pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt2 = p2;
					for (; pt2.x > (p1.x - (p2.y - p1.y) / 2); --pt2.x, --pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					for (; pt1.y < p2.y; ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += 1;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.x > 0; --pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt2 = p2;
					for (; pt2.x > 0; --pt2.x, --pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					for (; pt1.y < p2.y; ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += 1;
						}
					}
				}
			}
		}
		else { //down direction
			if ((p1.x + p2.x) % 2 == 0){
				if ((p1.y - (p2.x - p1.x) / 2) >= 0){
					pt = p1;
					for (; pt.y > (p1.y - (p2.x - p1.x) / 2); --pt.y, ++pt.x) {
						int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt = p2;
					for (; pt.y > (p1.y - (p2.x - p1.x) / 2); --pt.x, --pt.y) {
						int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.y > 0; --pt1.y, ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt2 = p2;
					for (; pt2.y > 0; --pt2.x, --pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					for (; pt1.x < p2.x; ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += 1;
						}
					}
				}
			}
			else{
				if ((p1.y - (p2.x - p1.x) / 2) >= 0){
					pt1 = p1;
					for (; pt1.y > (p1.y - (p2.x - p1.x) / 2); --pt1.y, ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt2 = p2;
					for (; pt2.y > (p1.y - (p2.x - p1.x) / 2); --pt2.x, --pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					for (; pt1.x < p2.x; ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += 1;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.y > 0; --pt1.y, ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt2 = p2;
					for (; pt2.y > 0; --pt2.x, --pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					for (; pt1.x < p2.x; ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += 1;
						}
					}
				}
			}
		}
	}
	else { // 0 repsents up or right
		if (p2.x == p1.x) { //right direction
			if ((p1.y + p2.y) % 2 == 0){
				if ((p1.x + (p2.y - p1.y) / 2) <= X_MAX){
					pt = p1;
					for (; pt.x < (p1.x + (p2.y - p1.y) / 2); ++pt.x, ++pt.y) {
						int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt = p2;
					for (; pt.x < (p1.x + (p2.y - p1.y) / 2); ++pt.x, --pt.y) {
						int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.x < X_MAX; ++pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt2 = p2;
					for (; pt2.x < X_MAX; ++pt2.x, --pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					for (; pt1.y < p2.y; ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += 1;
						}
					}
				}
			}
			else{
				if ((p1.x + (p2.y - p1.y) / 2) <= X_MAX){
					pt1 = p1;
					for (; pt1.x < (p1.x + (p2.y - p1.y) / 2); ++pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt2 = p2;
					for (; pt2.x < (p1.x + (p2.y - p1.y) / 2); ++pt2.x, --pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					for (; pt1.y < p2.y; ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += 1;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.x < X_MAX; ++pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt2 = p2;
					for (; pt2.x < X_MAX; ++pt2.x, --pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					for (; pt1.y < p2.y; ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += 1;
						}
					}
				}
			}
		}
		else { //up direction
			if ((p1.x + p2.x) % 2 == 0){
				if ((p1.y + (p2.x - p1.x) / 2) <= Y_MAX){
					pt = p1;
					for (; pt.y < (p1.y + (p2.x - p1.x) / 2); ++pt.x, ++pt.y) {
						int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt = p2;
					for (; pt.y < (p1.y + (p2.x - p1.x) / 2); ++pt.y, --pt.x) {
						int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.y < Y_MAX; ++pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt2 = p2;
					for (; pt2.y < Y_MAX; ++pt2.y, --pt2.x) {
						int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					for (; pt1.x < p2.x; ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += 1;
						}
					}
				}
			}
			else{
				if ((p1.y + (p2.x - p1.x) / 2) <= Y_MAX){
					pt1 = p1;
					for (; pt1.y < (p1.y + (p2.x - p1.x) / 2); ++pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt2 = p2;
					for (; pt2.y < (p1.y + (p2.x - p1.x) / 2); ++pt2.y, --pt2.x) {
						int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					for (; pt1.x < p2.x; ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += 1;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.y < Y_MAX; ++pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					pt2 = p2;
					for (; pt2.y < Y_MAX; ++pt2.y, --pt2.x) {
						int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += sq2;
						}
					}
					for (; pt1.x < p2.x; ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret2 += 1;
						}
					}
				}
			}
		}
	}
	return ret2;
}
double GetRet3(bool flag, int net_id, Point p1, Point p2, Point pt, double sq2, set< pair<int, int> >& ilp_connect, map<int, int>& ilp_connect_count){
	double ret3 = 0.0;
	if (flag) { // 1 represents first horizontal then vertical
		if (p1.x < p2.x){//right-top
			for (; pt.y > p1.y; --pt.y) {
				int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
					ilp_connect.insert(make_pair(net_id, num));
					++ilp_connect_count[num];
					ret3 += 1;
				}
			}
			for (; pt.x > p1.x; --pt.x) {
				int num = pt.y * X_MAX + pt.x;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
					ilp_connect.insert(make_pair(net_id, num));
					++ilp_connect_count[num];
					ret3 += 1;
				}
			}
		}
		else{//left-top
			for (; pt.y > p1.y; --pt.y) {
				int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
					ilp_connect.insert(make_pair(net_id, num));
					++ilp_connect_count[num];
					ret3 += 1;
				}
			}
			for (; pt.x < p1.x; ++pt.x) {
				int num = pt.y * X_MAX + pt.x;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
					ilp_connect.insert(make_pair(net_id, num));
					++ilp_connect_count[num];
					ret3 += 1;
				}
			}
		}
	}
	else { // 0 repsents first vertical then horizontal
		if (p1.x < p2.x){//right-top
			for (; pt.x > p1.x; --pt.x) {
				int num = pt.y * X_MAX + pt.x;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
					ilp_connect.insert(make_pair(net_id, num));
					++ilp_connect_count[num];
					ret3 += 1;
				}
			}
			for (; pt.y > p1.y; --pt.y) {
				int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
					ilp_connect.insert(make_pair(net_id, num));
					++ilp_connect_count[num];
					ret3 += 1;
				}
			}
		}
		else{//left-top
			for (; pt.x < p1.x; ++pt.x) {
				int num = pt.y * X_MAX + pt.x;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
					ilp_connect.insert(make_pair(net_id, num));
					++ilp_connect_count[num];
					ret3 += 1;
				}
			}
			for (; pt.y > p1.y; --pt.y) {
				int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
					ilp_connect.insert(make_pair(net_id, num));
					++ilp_connect_count[num];
					ret3 += 1;
				}
			}

		}
	}
	return ret3;
}
double ILP_GetFitness4(const int& pop_ind){
	int penalty = 1; // record the violations of capacity constraints
	set< pair<int, int> > ilp_connect; //	the first demension represents the name of net, the second one represents the number and the direction
	map<int, int> ilp_connect_count; //	record the connections of one pin at one direction in one solution of ILP
	double ret = 0.0;
	const double sq2 = sqrt(2.0);
	Point p1, p2, pt, pt1, pt2;
	int i;
	for (i = 0; i < pop_ilp[pop_ind].sol.size(); ++i) {
		int net_id = ilp_extend_point_vec[i].net_id;
		p1.x = line_net[net_id].pin[ilp_extend_point_vec[i].pa_id][0];
		p1.y = line_net[net_id].pin[ilp_extend_point_vec[i].pa_id][1];
		p2.x = line_net[net_id].pin[ilp_extend_point_vec[i].pb_id][0];
		p2.y = line_net[net_id].pin[ilp_extend_point_vec[i].pb_id][1];
		if (p2 < p1)
			swap(p1, p2);
		pt = p2;
		//printf("%d%d\n", pop_ilp[pop_ind].cnt[i], pop_ilp[pop_ind].cnt[i]);
		if (pop_ilp[pop_ind].cnt[i] == 1){
			if (pop_ilp[pop_ind].sol[i]) { // 1 represents first rectilinear then X-architecture
				if (p2.x > p1.x) { //right-top direction
					pt = p2;
					if (p2.x - p1.x < p2.y - p1.y) {
						for (; pt.x > p1.x; --pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt.y > p1.y; --pt.y) {
							int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
					else {
						for (; pt.y > p1.y; --pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt.x > p1.x; --pt.x) {
							int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
				}
				else { //left-top direction
					pt = p2;
					if (p2.y - p1.y < p1.x - p2.x) {
						for (; pt.y > p1.y; ++pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (pt.x = p1.x; pt.x > p2.x + (p2.y - p1.y); --pt.x) {
							int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
					else {
						for (; pt.x < p1.x; --pt.y, ++pt.x) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += sq2;
							}
						}
						for (; pt.y > p1.y; --pt.y) {
							int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								++ilp_connect_count[num];
								ret += 1;
							}
						}
					}
				}
			}
			else { // 0 repsents first X-architecture then rectilineaer
				if (p2.x > p1.x) { //right-top direction
					pt = p2;
					if (p2.y - p1.y < p2.x - p1.x) {
						for (; pt.x > p1.x + p2.y - p1.y; --pt.x) {
							int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								ret += 1;
								++ilp_connect_count[num];
							}
						}
						for (; pt.y > p1.y; --pt.y, --pt.x) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								ret += sq2;
								++ilp_connect_count[num];
							}
						}
					}
					else {
						for (; pt.y > p1.y + p2.x - p1.x; --pt.y) {
							int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								ret += 1;
								++ilp_connect_count[num];
							}
						}
						for (; pt.y > p1.y; --pt.y, --pt.x) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								ret += sq2;
								++ilp_connect_count[num];
							}
						}
					}
				}
				else { //left-top direction
					if (p2.y - p1.y < p1.x - p2.x) {
						pt.y = p2.y;
						pt.x = p1.x - (p2.y - p1.y);
						for (; pt.x > p2.x; --pt.x) {
							int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								ret += 1;
								++ilp_connect_count[num];
							}
						}
						pt.y = p2.y;
						pt.x = p1.x - (p2.y - p1.y);
						for (; pt.x < p1.x; ++pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								ret += sq2;
								++ilp_connect_count[num];
							}
						}
					}
					else {
						for (pt = p2; pt.y > p1.y + p1.x - p2.x; --pt.y) {
							int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								ret += 1;
								++ilp_connect_count[num];
							}
						}
						for (; pt.y > p1.y; --pt.y, ++pt.x) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
								&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
								ilp_connect.insert(make_pair(net_id, num));
								ret += sq2;
								++ilp_connect_count[num];
							}
						}

					}
				}
			}
		}
		if (pop_ilp[pop_ind].cnt[i] == 2){
			//printf("22\n");
			if (pop_ilp[pop_ind].sol[i]) { // 1 represents down or left
				if (p2.x == p1.x) { //left direction
					if ((p1.y + p2.y) % 2 == 0){
						if ((p1.x - (p2.y - p1.y) / 2) >= 0){
							pt = p1;
							for (; pt.x > (p1.x - (p2.y - p1.y) / 2); --pt.x, ++pt.y) {
								int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt = p2;
							for (; pt.x > (p1.x - (p2.y - p1.y) / 2); --pt.x, --pt.y) {
								int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
						}
						else{
							pt1 = p1;
							for (; pt1.x > 0; --pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt2 = pt1;
							for (; pt2.x < p1.x; ++pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt1 = pt2;
							for (; pt1.y < p2.y; ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += 1;
								}
							}
						}
					}
					else{
						if ((p1.x - (p2.y - p1.y) / 2) >= 0){
							pt1 = p1;
							for (; pt1.x > (p1.x - (p2.y - p1.y) / 2); --pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt2 = pt1;
							for (; pt2.x < p1.x; ++pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt1 = pt2;
							for (; pt1.y < p2.y; ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += 1;
								}
							}
						}
						else{
							pt1 = p1;
							for (; pt1.x > 0; --pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt2 = pt1;
							for (; pt2.x < p1.x; ++pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt1 = pt2;
							for (; pt1.y < p2.y; ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += 1;
								}
							}
						}
					}
				}
				else { //down direction
					if ((p1.x + p2.x) % 2 == 0){
						if ((p1.y - (p2.x - p1.x) / 2) >= 0){
							pt = p1;
							for (; pt.y > (p1.y - (p2.x - p1.x) / 2); --pt.y, ++pt.x) {
								int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt = p2;
							for (; pt.y > (p1.y - (p2.x - p1.x) / 2); --pt.x, --pt.y) {
								int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
						}
						else{
							pt1 = p1;
							for (; pt1.y > 0; --pt1.y, ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt2 = pt1;
							for (; pt2.y < p1.y; ++pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt1 = pt2;
							for (; pt1.x < p2.x; ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += 1;
								}
							}
						}
					}
					else{
						if ((p1.y - (p2.x - p1.x) / 2) >= 0){
							pt1 = p1;
							for (; pt1.y > (p1.y - (p2.x - p1.x) / 2); --pt1.y, ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt2 = pt1;
							for (; pt2.y < p1.y; ++pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt1 = pt2;
							for (; pt1.x < p2.x; ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += 1;
								}
							}
						}
						else{
							pt1 = p1;
							for (; pt1.y > 0; --pt1.y, ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt2 = pt1;
							for (; pt2.y < pt.y; ++pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt1 = pt2;
							for (; pt1.x < p2.x; ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += 1;
								}
							}
						}
					}
				}
			}
			else { // 0 repsents up or right
				if (p2.x == p1.x) { //right direction
					if ((p1.y + p2.y) % 2 == 0){
						if ((p1.x + (p2.y - p1.y) / 2) <= X_MAX){
							pt = p1;
							for (; pt.x < (p1.x + (p2.y - p1.y) / 2); ++pt.x, ++pt.y) {
								int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt = p2;
							for (; pt.x < (p1.x + (p2.y - p1.y) / 2); ++pt.x, --pt.y) {
								int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
						}
						else{
							pt1 = p1;
							for (; pt1.x < X_MAX; ++pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt2 = pt1;
							for (; pt2.x > p1.x; --pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt1 = pt2;
							for (; pt1.y < p2.y; ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += 1;
								}
							}
						}
					}
					else{
						if ((p1.x + (p2.y - p1.y) / 2) <= X_MAX){
							pt1 = p1;
							for (; pt1.x < (p1.x + (p2.y - p1.y) / 2); ++pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt2 = pt1;
							for (; pt2.x > p1.x; --pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt1 = pt2;
							for (; pt1.y < p2.y; ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += 1;
								}
							}
						}
						else{
							pt1 = p1;
							for (; pt1.x < X_MAX; ++pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt2 = pt1;
							for (; pt2.x > pt.x; --pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt1 = pt2;
							for (; pt1.y < p2.y; ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += 1;
								}
							}
						}
					}
				}
				else { //up direction
					if ((p1.x + p2.x) % 2 == 0){
						if ((p1.y + (p2.x - p1.x) / 2) <= Y_MAX){
							pt = p1;
							for (; pt.y < (p1.y + (p2.x - p1.x) / 2); ++pt.x, ++pt.y) {
								int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt = p2;
							for (; pt.y < (p1.y + (p2.x - p1.x) / 2); ++pt.y, --pt.x) {
								int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
						}
						else{
							pt1 = p1;
							for (; pt1.y < Y_MAX; ++pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt2 = pt1;
							for (; pt2.y > p1.y; --pt2.y, ++pt2.x) {
								int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt1 = pt2;
							for (; pt1.x < p2.x; ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += 1;
								}
							}
						}
					}
					else{
						if ((p1.y + (p2.x - p1.x) / 2) <= Y_MAX){
							pt1 = p1;
							for (; pt1.y < (p1.y + (p2.x - p1.x) / 2); ++pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt2 = pt1;
							for (; pt2.y > p1.y; --pt2.y, ++pt2.x) {
								int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt1 = pt2;
							for (; pt1.x < p2.x; ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += 1;
								}
							}
						}
						else{
							pt1 = p1;
							for (; pt1.y < Y_MAX; ++pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt2 = pt1;
							for (; pt2.y > p1.y; --pt2.y, ++pt2.x) {
								int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += sq2;
								}
							}
							pt1 = pt2;
							for (; pt1.x < p2.x; ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
									&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
									ilp_connect.insert(make_pair(net_id, num));
									++ilp_connect_count[num];
									ret += 1;
								}
							}
						}
					}
				}
			}
		}
		if (pop_ilp[pop_ind].cnt[i] == 3){
			if (pop_ilp[pop_ind].sol[i]) { // 1 represents first horizontal then vertical
				if (p1.x < p2.x){//right-top
					for (; pt.y > p1.y; --pt.y) {
						int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret += 1;
						}
					}
					for (; pt.x > p1.x; --pt.x) {
						int num = pt.y * X_MAX + pt.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret += 1;
						}
					}
				}
				else{//left-top
					for (; pt.y > p1.y; --pt.y) {
						int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret += 1;
						}
					}
					for (; pt.x < p1.x; ++pt.x) {
						int num = pt.y * X_MAX + pt.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret += 1;
						}
					}
				}
			}
			else { // 0 repsents first vertical then horizontal
				if (p1.x < p2.x){//right-top
					for (; pt.x > p1.x; --pt.x) {
						int num = pt.y * X_MAX + pt.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret += 1;
						}
					}
					for (; pt.y > p1.y; --pt.y) {
						int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret += 1;
						}
					}
				}
				else{//left-top
					for (; pt.x < p1.x; ++pt.x) {
						int num = pt.y * X_MAX + pt.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret += 1;
						}
					}
					for (; pt.y > p1.y; --pt.y) {
						int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& ilp_connect.find(make_pair(net_id, num)) == ilp_connect.end()) {
							ilp_connect.insert(make_pair(net_id, num));
							++ilp_connect_count[num];
							ret += 1;
						}
					}

				}
			}
		}

	}
	map<int, int>::iterator itm;
	for (itm = ilp_connect_count.begin(); itm != ilp_connect_count.end(); ++itm) {
		switch (itm->first / (X_MAX * Y_MAX)) {
		case 0:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][0] > maxline[itm->first % (X_MAX * Y_MAX)][0])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][0] - maxline[itm->first % (X_MAX * Y_MAX)][0];
			break;
		case 1:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][1] > maxline[itm->first % (X_MAX * Y_MAX)][1])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][1] - maxline[itm->first % (X_MAX * Y_MAX)][1];
			break;
		case 2:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][2] > maxline[itm->first % (X_MAX * Y_MAX)][2])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][2] - maxline[itm->first % (X_MAX * Y_MAX)][2];
			break;
		case 3:
			if (itm->second + record_p[itm->first % (X_MAX * Y_MAX)][3] > maxline[itm->first % (X_MAX * Y_MAX)][3])
				penalty += itm->second + record_p[itm->first % (X_MAX * Y_MAX)][3] - maxline[itm->first % (X_MAX * Y_MAX)][3];
			break;
		}
	}
	ret *= pow(1.01, penalty); //	penalty the fitness function
	return ret;
}

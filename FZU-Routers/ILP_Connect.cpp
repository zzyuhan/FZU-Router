void ILP_Connect() { //connect the extended 2-pin net
    Point p1, p2, pt;
    int i;
    for (i = 0; i < gbest_ilp.sol.size(); ++i) {
        int net_id = ilp_extend_point_vec[i].net_id;
        p1.x = line_net[net_id].pin[ilp_extend_point_vec[i].pa_id][0];
        p1.y = line_net[net_id].pin[ilp_extend_point_vec[i].pa_id][1];
        p2.x = line_net[net_id].pin[ilp_extend_point_vec[i].pb_id][0];
        p2.y = line_net[net_id].pin[ilp_extend_point_vec[i].pb_id][1];
        if (p2 < p1)
            swap(p1, p2);
        if (!ILP_CheckConnect(p1, p2, gbest_ilp.sol[i], net_id)) {
            ExpandNode nt;
            nt.net_id = net_id;
            nt.pa_id = ilp_extend_point_vec[i].pa_id;
            nt.pb_id = ilp_extend_point_vec[i].pb_id;
            extend_unconnect.insert(nt);
            continue;
        }
        if (gbest_ilp.sol[i]) { // 1 represents first rectilinear then X-architecture
            if (p2.x > p1.x) { //	right_top direction
                pt = p2;
                if (p2.x - p1.x < p2.y - p1.y) {
                    for ( ; pt.x > p1.x; --pt.x, --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                            ++record_p[pt.y * X_MAX + pt.x][1];
                            line_net[net_id].point_edge.insert(num);
							
                        }
                    }netx45num++;
                    for ( ; pt.y > p1.y; --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                            ++record_p[pt.y * X_MAX + pt.x][2];
                            line_net[net_id].point_edge.insert(num);
							
                        }
                    }netvnum++;
                } else {
                    for ( ; pt.y > p1.y; --pt.x, --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                            ++record_p[pt.y * X_MAX + pt.x][1];
                            line_net[net_id].point_edge.insert(num);
							
                        }
                    }netx45num++;
                    for ( ; pt.x > p1.x; --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                            ++record_p[pt.y * X_MAX + pt.x][0];
                            line_net[net_id].point_edge.insert(num);
							
                        }
                    }nethnum++;
                }
            } else { //	left_top direction
                pt = p2;
                if (p2.y - p1.y < p1.x - p2.x) {
                    for ( ; pt.y > p1.y; ++pt.x, --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                            ++record_p[pt.y * X_MAX + pt.x][3];
                            line_net[net_id].point_edge.insert(num);
							
                        }
                    }netx135num++;
                    for (pt.x = p1.x; pt.x > p2.x + p2.y - p1.y; --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                            ++record_p[pt.y * X_MAX + pt.x][0];
                            line_net[net_id].point_edge.insert(num);
							
                        }
                    }nethnum++;
                } else {
                    for (; pt.x < p1.x; --pt.y, ++pt.x) {
                        int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                            ++record_p[pt.y * X_MAX + pt.x][3];
                            line_net[net_id].point_edge.insert(num);
							
                        }
                    }netx135num++;
                    for ( ; pt.y > p1.y; --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                            ++record_p[pt.y * X_MAX + pt.x][2];
                            line_net[net_id].point_edge.insert(num);
							
                        }
                    }netvnum++;
                }
            }
        } else { //	0 represents first X-architecture then rectilinear
            if (p2.x > p1.x) { //	right_top direction
                pt = p2;
                if (p2.x - p1.x < p2.y - p1.y) {
                    for ( ; pt.y > p1.y + p2.x - p1.x; --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                             ++record_p[pt.y * X_MAX + pt.x][2];
                             line_net[net_id].point_edge.insert(num);
							 
                        }
                    }netvnum++;
                    for ( ; pt.y > p1.y; --pt.y, --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                             ++record_p[pt.y * X_MAX + pt.x][1];
                             line_net[net_id].point_edge.insert(num);
							 
                        }
                    }netx45num++;
                } else {
                    for ( ; pt.x > p1.x + p2.y - p1.y; --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                             ++record_p[pt.y * X_MAX + pt.x][0];
                             line_net[net_id].point_edge.insert(num);
							 
                        }
                    }nethnum++;
                    for ( ; pt.y > p1.y; --pt.y, --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                             ++record_p[pt.y * X_MAX + pt.x][1];
                             line_net[net_id].point_edge.insert(num);
							 
                        }
                    }netx45num++;
                }
            } else { //	left_top direction
                if (p2.y - p1.y < p1.x - p2.x) {
                    pt.y = p2.y;
                    pt.x = p1.x - (p2.y - p1.y);
                    for ( ; pt.x > p2.x; --pt.x) {
                        int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                             ++record_p[pt.y * X_MAX + pt.x][0];
                             line_net[net_id].point_edge.insert(num);
							 
                        }
                    }nethnum++;
                    pt.y = p2.y;
                    pt.x = p1.x - (p2.y - p1.y);
                    for ( ; pt.x < p1.x ; ++pt.x, --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                             ++record_p[pt.y * X_MAX + pt.x][3];
                             line_net[net_id].point_edge.insert(num);
							 
                        }
                    }netx135num++;
                } else {
                    for (pt = p2; pt.y > p1.y + p1.x - p2.x; --pt.y) {
                        int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                             ++record_p[pt.y * X_MAX + pt.x][2];
                             line_net[net_id].point_edge.insert(num);
							 
                        }
                    }netvnum++;
                    for (; pt.y > p1.y; --pt.y, ++pt.x) {
                        int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
                        if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
                             ++record_p[pt.y * X_MAX + pt.x][3];
                             line_net[net_id].point_edge.insert(num);
							 
                        }
                    }netx135num++;
                    
                }
            }
        }
    }
}
void ILP_Connect2() { //connect the extended 2-pin net
	Point p1, p2, pt, pt1, pt2;
	int i;
	for (i = 0; i < gbest_ilp.sol.size(); ++i) {
		int net_id = ilp_extend_point_vec2[i].net_id;
		p1.x = line_net[net_id].pin[ilp_extend_point_vec2[i].pa_id][0];
		p1.y = line_net[net_id].pin[ilp_extend_point_vec2[i].pa_id][1];
		p2.x = line_net[net_id].pin[ilp_extend_point_vec2[i].pb_id][0];
		p2.y = line_net[net_id].pin[ilp_extend_point_vec2[i].pb_id][1];
		if (p2 < p1)
			swap(p1, p2);
		if (!ILP_CheckConnect2(p1, p2, gbest_ilp.sol[i], net_id)) {
			ExpandNode nt;
			nt.net_id = net_id;
			nt.pa_id = ilp_extend_point_vec2[i].pa_id;
			nt.pb_id = ilp_extend_point_vec2[i].pb_id;
			extend_unconnect.insert(nt);
			continue;
		}
		if (gbest_ilp.sol[i]) { // 1 represents down or left
			if (p2.x == p1.x) { //left direction
				if ((p1.y + p2.y) % 2 == 0){
					if ((p1.x - (p2.y - p1.y) / 2) >= 0){
						pt = p1;
						for (; pt.x > (p1.x - (p2.y - p1.y) / 2); --pt.x, ++pt.y) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						pt = p2;
						for (; pt.x > (p1.x - (p2.y - p1.y) / 2); --pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}//netx135num++;
					}
					else{
						pt1 = p1;
						for (; pt1.x > 0; --pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						pt2 = p2;
						for (; pt2.x > 0; --pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt2.y * X_MAX + pt2.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						for (; pt1.y < p2.y; ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][2];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netvnum++;
					}
				}
				else{
					if ((p1.x - (p2.y - p1.y) / 2) >= 0){
						pt1 = p1;
						for (; pt1.x > (p1.x - (p2.y - p1.y) / 2); --pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						pt2 = p2;
						for (; pt2.x > (p1.x - (p2.y - p1.y) / 2); --pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt2.y * X_MAX + pt2.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						for (; pt1.y < p2.y; ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][2];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netvnum++;
					}
					else{
						pt1 = p1;
						for (; pt1.x > 0; --pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						pt2 = p2;
						for (; pt2.x > 0; --pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt2.y * X_MAX + pt2.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						for (; pt1.y < p2.y; ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][2];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netvnum++;
					}
				}
			}
			else { //down direction
				if ((p1.x + p2.x) % 2 == 0){
					if ((p1.y - (p2.x - p1.x) / 2) >= 0){
						pt = p1;
						for (; pt.y > (p1.y - (p2.x - p1.x) / 2); --pt.y, ++pt.x) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						pt = p2;
						for (; pt.y > (p1.y - (p2.x - p1.x) / 2); --pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}//netx135num++;
					}
					else{
						pt1 = p1;
						for (; pt1.y > 0; --pt1.y, ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						pt2 = p2;
						for (; pt2.y > 0; --pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt2.y * X_MAX + pt2.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						for (; pt1.x < p2.x; ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][0];
								line_net[net_id].point_edge.insert(num);
								
							}
						}nethnum++;
					}
				}
				else{
					if ((p1.y - (p2.x - p1.x) / 2) >= 0){
						pt1 = p1;
						for (; pt1.y > (p1.y - (p2.x - p1.x) / 2); --pt1.y, ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						pt2 = p2;
						for (; pt2.y > (p1.y - (p2.x - p1.x) / 2); --pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt2.y * X_MAX + pt2.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						for (; pt1.x < p2.x; ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][0];
								line_net[net_id].point_edge.insert(num);
								
							}
						}nethnum++;
					}
					else{
						pt1 = p1;
						for (; pt1.y > 0; --pt1.y, ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						pt2 = p2;
						for (; pt2.y > 0; --pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt2.y * X_MAX + pt2.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						for (; pt1.x < p2.x; ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][0];
								line_net[net_id].point_edge.insert(num);
								
							}
						}nethnum++;
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
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						pt = p2;
						for (; pt.x < (p1.x + (p2.y - p1.y) / 2); ++pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}//netx45num++;
					}
					else{
						pt1 = p1;
						for (; pt1.x < X_MAX; ++pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						pt2 = p2;
						for (; pt2.x < X_MAX; ++pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt2.y * X_MAX + pt2.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						for (; pt1.y < p2.y; ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][2];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netvnum++;
					}
				}
				else{
					if ((p1.x + (p2.y - p1.y) / 2) <= X_MAX){
						pt1 = p1;
						for (; pt1.x < (p1.x + (p2.y - p1.y) / 2); ++pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						pt2 = p2;
						for (; pt2.x < (p1.x + (p2.y - p1.y) / 2); ++pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt2.y * X_MAX + pt2.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						for (; pt1.y < p2.y; ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][2];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netvnum;
					}
					else{
						pt1 = p1;
						for (; pt1.x < X_MAX; ++pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						pt2 = p2;
						for (; pt2.x < X_MAX; ++pt2.x, --pt2.y) {
							int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt2.y * X_MAX + pt2.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						for (; pt1.y < p2.y; ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][2];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netvnum++;
					}
				}
			}
			else { //up direction
				if ((p1.x + p2.x) % 2 == 0){
					if ((p1.y + (p2.x - p1.x) / 2) <= Y_MAX){
						pt = p1;
						for (; pt.y < (p1.y + (p2.x - p1.x) / 2); ++pt.x, ++pt.y) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						pt = p2;
						for (; pt.y < (p1.y + (p2.x - p1.x) / 2); ++pt.y, --pt.x) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}//netx45num++;
					}
					else{
						pt1 = p1;
						for (; pt1.y < Y_MAX; ++pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						pt2 = p2;
						for (; pt2.y < Y_MAX; ++pt2.y, --pt2.x) {
							int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt2.y * X_MAX + pt2.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						for (; pt1.x < p2.x; ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][0];
								line_net[net_id].point_edge.insert(num);
								
							}
						}nethnum++;
					}
				}
				else{
					if ((p1.y + (p2.x - p1.x) / 2) <= Y_MAX){
						pt1 = p1;
						for (; pt1.y < (p1.y + (p2.x - p1.x) / 2); ++pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						pt2 = p2;
						for (; pt2.y < (p1.y + (p2.x - p1.x) / 2); ++pt2.y, --pt2.x) {
							int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt2.y * X_MAX + pt2.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						for (; pt1.x < p2.x; ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][0];
								line_net[net_id].point_edge.insert(num);
								
							}
						}nethnum++;
					}
					else{
						pt1 = p1;
						for (; pt1.y < Y_MAX; ++pt1.x, ++pt1.y) {
							int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][3];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx135num++;
						pt2 = p2;
						for (; pt2.y < Y_MAX; ++pt2.y, --pt2.x) {
							int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt2.y * X_MAX + pt2.x][1];
								line_net[net_id].point_edge.insert(num);
								
							}
						}netx45num++;
						for (; pt1.x < p2.x; ++pt1.x) {
							int num = pt1.y * X_MAX + pt1.x;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt1.y * X_MAX + pt1.x][0];
								line_net[net_id].point_edge.insert(num);
								
							}
						}nethnum++;
					}
				}
			}
		}
	}
}
void ILP_Connect3() { //connect the extended 2-pin net
	Point p1, p2, pt;
	int i;
	for (i = 0; i < gbest_ilp.sol.size(); ++i) {
		int net_id = ilp_extend_point_vec3[i].net_id;
		p1.x = line_net[net_id].pin[ilp_extend_point_vec3[i].pa_id][0];
		p1.y = line_net[net_id].pin[ilp_extend_point_vec3[i].pa_id][1];
		p2.x = line_net[net_id].pin[ilp_extend_point_vec3[i].pb_id][0];
		p2.y = line_net[net_id].pin[ilp_extend_point_vec3[i].pb_id][1];
		if (p2 < p1)
			swap(p1, p2);
		if (!ILP_CheckConnect3(p1, p2, gbest_ilp.sol[i], net_id)) {
			ExpandNode nt;
			nt.net_id = net_id;
			nt.pa_id = ilp_extend_point_vec3[i].pa_id;
			nt.pb_id = ilp_extend_point_vec3[i].pb_id;
			extend_unconnect.insert(nt);
			continue;
		}
		if (gbest_ilp.sol[i]) { // 1  represents horizontal then vertical
			if (p1.x < p2.x){//right-top
				for (; pt.y > p1.y; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
						++record_p[pt.y * X_MAX + pt.x][2];
						line_net[net_id].point_edge.insert(num);
						
					}
				}netvnum++;
				for (; pt.x > p1.x; --pt.x) {
					int num = pt.y * X_MAX + pt.x;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
						++record_p[pt.y * X_MAX + pt.x][0];
						line_net[net_id].point_edge.insert(num);
						
					}
				}nethnum++;
			}
			else{//left-top
				for (; pt.y > p1.y; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
						++record_p[pt.y * X_MAX + pt.x][2];
						line_net[net_id].point_edge.insert(num);
						
					}
				}netvnum++;
				for (; pt.x < p1.x; ++pt.x) {
					int num = pt.y * X_MAX + pt.x;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
						++record_p[pt.y * X_MAX + pt.x][0];
						line_net[net_id].point_edge.insert(num);
						
					}
				}nethnum++;
			}
		}
		else { // 0 represents first vertical then horizontal
			if (p1.x < p2.x){//right-top
				for (; pt.x > p1.x; --pt.x) {
					int num = pt.y * X_MAX + pt.x;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
						++record_p[pt.y * X_MAX + pt.x][0];
						line_net[net_id].point_edge.insert(num);
						
					}
				}nethnum++;
				for (; pt.y > p1.y; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
						++record_p[pt.y * X_MAX + pt.x][2];
						line_net[net_id].point_edge.insert(num);
						
					}
				}netvnum++;
			}
			else{//left-top
				for (; pt.x < p1.x; ++pt.x) {
					int num = pt.y * X_MAX + pt.x;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
						++record_p[pt.y * X_MAX + pt.x][0];
						line_net[net_id].point_edge.insert(num);
						
					}
				}nethnum++;
				for (; pt.y > p1.y; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
						++record_p[pt.y * X_MAX + pt.x][2];
						line_net[net_id].point_edge.insert(num);
						
					}
				}netvnum++;

			}
		}
	}
}
void ILP_Connect4() { //connect the extended 2-pin net
	Point p1, p2, pt, pt1, pt2;
	int i;
	for (i = 0; i < gbest_ilp.sol.size(); ++i) {
		int net_id = ilp_extend_point_vec[i].net_id;
		p1.x = line_net[net_id].pin[ilp_extend_point_vec[i].pa_id][0];
		p1.y = line_net[net_id].pin[ilp_extend_point_vec[i].pa_id][1];
		p2.x = line_net[net_id].pin[ilp_extend_point_vec[i].pb_id][0];
		p2.y = line_net[net_id].pin[ilp_extend_point_vec[i].pb_id][1];
		if (p2 < p1)
			swap(p1, p2);
		if (gbest_ilp.cnt[i] == 1){
			//printf("5\n");
			if (!ILP_CheckConnect(p1, p2, gbest_ilp.sol[i], net_id)) {
				ExpandNode nt;
				nt.net_id = net_id;
				nt.pa_id = ilp_extend_point_vec[i].pa_id;
				nt.pb_id = ilp_extend_point_vec[i].pb_id;
				extend_unconnect.insert(nt);
				continue;
			}
			//printf("6\n");
			if (gbest_ilp.sol[i]) { // 1 represents first rectilinear then X-architecture
				if (p2.x > p1.x) { //	right_top direction
					pt = p2;
					if (p2.x - p1.x < p2.y - p1.y) {
						for (; pt.x > p1.x; --pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][1];
								if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
									maxline[pt.y * X_MAX + pt.x][1] += 2;
									maxline[pt.y * X_MAX + pt.x][0] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}netx45num++;
						for (; pt.y > p1.y; --pt.y) {
							int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][2];
								if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
									maxline[pt.y * X_MAX + pt.x][2] += 2;
									maxline[pt.y * X_MAX + pt.x][3] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}netvnum++;
						//printf("7\n");
					}
					else {
						for (; pt.y > p1.y; --pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][1];
								if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
									maxline[pt.y * X_MAX + pt.x][1] += 2;
									maxline[pt.y * X_MAX + pt.x][0] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}netx45num++;
						for (; pt.x > p1.x; --pt.x) {
							int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][0];
								if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
									maxline[pt.y * X_MAX + pt.x][0] += 2;
									maxline[pt.y * X_MAX + pt.x][1] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}nethnum++;
						//printf("7\n");
					}
				}
				else { //	left_top direction
					pt = p2;
					if (p2.y - p1.y < p1.x - p2.x) {
						for (; pt.y > p1.y; ++pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][3];
								if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
									maxline[pt.y * X_MAX + pt.x][3] += 2;
									maxline[pt.y * X_MAX + pt.x][2] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}netx135num++;
						for (pt.x = p1.x; pt.x > p2.x + p2.y - p1.y; --pt.x) {
							int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][0];
								if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
									maxline[pt.y * X_MAX + pt.x][0] += 2;
									maxline[pt.y * X_MAX + pt.x][1] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}nethnum++;
						//printf("7\n");
					}
					else {
						for (; pt.x < p1.x; --pt.y, ++pt.x) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][3];
								if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
									maxline[pt.y * X_MAX + pt.x][3] += 2;
									maxline[pt.y * X_MAX + pt.x][2] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}netx135num++;
						for (; pt.y > p1.y; --pt.y) {
							int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][2];
								if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
									maxline[pt.y * X_MAX + pt.x][2] += 2;
									maxline[pt.y * X_MAX + pt.x][3] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}netvnum++;
						//printf("7\n");
					}
				}
			}
			else { //	0 represents first X-architecture then rectilinear
				if (p2.x > p1.x) { //	right_top direction
					pt = p2;
					if (p2.x - p1.x < p2.y - p1.y) {
						for (; pt.y > p1.y + p2.x - p1.x; --pt.y) {
							int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][2];
								if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
									maxline[pt.y * X_MAX + pt.x][2] += 2;
									maxline[pt.y * X_MAX + pt.x][3] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}netvnum++;
						for (; pt.y > p1.y; --pt.y, --pt.x) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][1];
								if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
									maxline[pt.y * X_MAX + pt.x][1] += 2;
									maxline[pt.y * X_MAX + pt.x][0] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}netx45num++;
						//printf("7\n");
					}
					else {
						for (; pt.x > p1.x + p2.y - p1.y; --pt.x) {
							int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][0];
								if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
									maxline[pt.y * X_MAX + pt.x][0] += 2;
									maxline[pt.y * X_MAX + pt.x][1] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}nethnum++;
						for (; pt.y > p1.y; --pt.y, --pt.x) {
							int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][1];
								if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
									maxline[pt.y * X_MAX + pt.x][1] += 2;
									maxline[pt.y * X_MAX + pt.x][0] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}netx45num++;
						//printf("7\n");
					}
				}
				else { //	left_top direction
					if (p2.y - p1.y < p1.x - p2.x) {
						pt.y = p2.y;
						pt.x = p1.x - (p2.y - p1.y);
						for (; pt.x > p2.x; --pt.x) {
							int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][0];
								if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
									maxline[pt.y * X_MAX + pt.x][0] += 2;
									maxline[pt.y * X_MAX + pt.x][1] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}nethnum++;
						pt.y = p2.y;
						pt.x = p1.x - (p2.y - p1.y);
						for (; pt.x < p1.x; ++pt.x, --pt.y) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][3];
								if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
									maxline[pt.y * X_MAX + pt.x][3] += 2;
									maxline[pt.y * X_MAX + pt.x][2] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}netx135num++;
						//printf("7\n");
					}
					else {
						for (pt = p2; pt.y > p1.y + p1.x - p2.x; --pt.y) {
							int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][2];
								if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
									maxline[pt.y * X_MAX + pt.x][2] += 2;
									maxline[pt.y * X_MAX + pt.x][3] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}netvnum++;
						for (; pt.y > p1.y; --pt.y, ++pt.x) {
							int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
							if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
								++record_p[pt.y * X_MAX + pt.x][3];
								if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
									maxline[pt.y * X_MAX + pt.x][3] += 2;
									maxline[pt.y * X_MAX + pt.x][2] -= 2;
								}
								line_net[net_id].point_edge.insert(num);

							}
						}netx135num++;
						//printf("7\n");
					}
				}
			}
		}
		else if (gbest_ilp.cnt[i] == 2){
			xnum++;
			if (!ILP_CheckConnect2(p1, p2, gbest_ilp.sol[i], net_id)) {
				ExpandNode nt;
				nt.net_id = net_id;
				nt.pa_id = ilp_extend_point_vec[i].pa_id;
				nt.pb_id = ilp_extend_point_vec[i].pb_id;
				extend_unconnect.insert(nt);
				continue;
			}
			if (gbest_ilp.sol[i]) { // 1 represents down or left
				if (p2.x == p1.x) { //left direction
					if ((p1.y + p2.y) % 2 == 0){
						if ((p1.x - (p2.y - p1.y) / 2) >= 0){
							pt = p1;
							for (; pt.x > (p1.x - (p2.y - p1.y) / 2); --pt.x, ++pt.y) {
								int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt.y * X_MAX + pt.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx45num++;
							pt = p2;
							for (; pt.x > (p1.x - (p2.y - p1.y) / 2); --pt.x, --pt.y) {
								int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt.y * X_MAX + pt.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx135num++;
						}
						else{
							pt1 = p1;
							for (; pt1.x > 0; --pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx45num++;
							pt2 = pt1;
							for (; pt2.x < p1.x; ++pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt2.y * X_MAX + pt2.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx135num++;
							pt1 = pt2;
							for (; pt1.y < p2.y; ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][2];
									if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
										maxline[pt.y * X_MAX + pt.x][2] += 2;
										maxline[pt.y * X_MAX + pt.x][3] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netvnum++;
						}
					}
					else{
						if ((p1.x - (p2.y - p1.y) / 2) >= 0){
							pt1 = p1;
							for (; pt1.x > (p1.x - (p2.y - p1.y) / 2); --pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx45num++;
							pt2 = pt1;
							for (; pt2.x < p1.x; ++pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt2.y * X_MAX + pt2.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx135num++;
							pt1 = pt2;
							for (; pt1.y < p2.y; ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][2];
									if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
										maxline[pt.y * X_MAX + pt.x][2] += 2;
										maxline[pt.y * X_MAX + pt.x][3] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netvnum++;
						}
						else{
							pt1 = p1;
							for (; pt1.x > 0; --pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx45num++;
							pt2 = pt1;
							for (; pt2.x < p1.x; ++pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt2.y * X_MAX + pt2.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx135num++;
							pt1 = pt2;
							for (; pt1.y < p2.y; ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][2];
									if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
										maxline[pt.y * X_MAX + pt.x][2] += 2;
										maxline[pt.y * X_MAX + pt.x][3] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netvnum++;
						}
					}
				}
				else { //down direction
					if ((p1.x + p2.x) % 2 == 0){
						if ((p1.y - (p2.x - p1.x) / 2) >= 0){
							pt = p1;
							for (; pt.y > (p1.y - (p2.x - p1.x) / 2); --pt.y, ++pt.x) {
								int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt.y * X_MAX + pt.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx45num++;
							pt = p2;
							for (; pt.y > (p1.y - (p2.x - p1.x) / 2); --pt.x, --pt.y) {
								int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt.y * X_MAX + pt.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx135num++;
						}
						else{
							pt1 = p1;
							for (; pt1.y > 0; --pt1.y, ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx45num++;
							pt2 = pt1;
							for (; pt2.y < p1.y; ++pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt2.y * X_MAX + pt2.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx135num++;
							pt1 = pt2;
							for (; pt1.x < p2.x; ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][0];
									if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
										maxline[pt.y * X_MAX + pt.x][0] += 2;
										maxline[pt.y * X_MAX + pt.x][1] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}nethnum++;
						}
					}
					else{
						if ((p1.y - (p2.x - p1.x) / 2) >= 0){
							pt1 = p1;
							for (; pt1.y > (p1.y - (p2.x - p1.x) / 2); --pt1.y, ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx45num++;
							pt2 = pt1;
							for (; pt2.y < p1.y; ++pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt2.y * X_MAX + pt2.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx135num++;
							pt1 = pt2;
							for (; pt1.x < p2.x; ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][0];
									if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
										maxline[pt.y * X_MAX + pt.x][0] += 2;
										maxline[pt.y * X_MAX + pt.x][1] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}nethnum++;
						}
						else{
							pt1 = p1;
							for (; pt1.y > 0; --pt1.y, ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx45num++;
							pt2 = pt1;
							for (; pt2.y < p1.y; ++pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt2.y * X_MAX + pt2.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx135num++;
							pt1 = pt2;
							for (; pt1.x < p2.x; ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][0];
									if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
										maxline[pt.y * X_MAX + pt.x][0] += 2;
										maxline[pt.y * X_MAX + pt.x][1] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}nethnum++;
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
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt.y * X_MAX + pt.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx135num++;
							pt = p2;
							for (; pt.x < (p1.x + (p2.y - p1.y) / 2); ++pt.x, --pt.y) {
								int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt.y * X_MAX + pt.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx45num++;
						}
						else{
							pt1 = p1;
							for (; pt1.x < X_MAX; ++pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx135num++;
							pt2 = pt1;
							for (; pt2.x > p1.x; --pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt2.y * X_MAX + pt2.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx45num++;
							pt1 = pt2;
							for (; pt1.y < p2.y; ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][2];
									if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
										maxline[pt.y * X_MAX + pt.x][2] += 2;
										maxline[pt.y * X_MAX + pt.x][3] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netvnum++;
						}
					}
					else{
						if ((p1.x + (p2.y - p1.y) / 2) <= X_MAX){
							pt1 = p1;
							for (; pt1.x < (p1.x + (p2.y - p1.y) / 2); ++pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx135num++;
							pt2 = pt1;
							for (; pt2.x > p1.x; --pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt2.y * X_MAX + pt2.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx45num++;
							pt1 = pt2;
							for (; pt1.y < p2.y; ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][2];
									if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
										maxline[pt.y * X_MAX + pt.x][2] += 2;
										maxline[pt.y * X_MAX + pt.x][3] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netvnum;
						}
						else{
							pt1 = p1;
							for (; pt1.x < X_MAX; ++pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx135num++;
							pt2 = pt1;
							for (; pt2.x > p1.x; --pt2.x, ++pt2.y) {
								int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt2.y * X_MAX + pt2.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx45num++;
							pt1 = pt2;
							for (; pt1.y < p2.y; ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][2];
									if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
										maxline[pt.y * X_MAX + pt.x][2] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netvnum++;
						}
					}
				}
				else { //up direction
					if ((p1.x + p2.x) % 2 == 0){
						if ((p1.y + (p2.x - p1.x) / 2) <= Y_MAX){
							pt = p1;
							for (; pt.y < (p1.y + (p2.x - p1.x) / 2); ++pt.x, ++pt.y) {
								int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt.y * X_MAX + pt.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx135num++;
							pt = p2;
							for (; pt.y < (p1.y + (p2.x - p1.x) / 2); ++pt.y, --pt.x) {
								int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt.y * X_MAX + pt.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx45num++;
						}
						else{
							pt1 = p1;
							for (; pt1.y < Y_MAX; ++pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx135num++;
							pt2 = pt1;
							for (; pt2.y > p1.y; --pt2.y, ++pt2.x) {
								int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt2.y * X_MAX + pt2.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx45num++;
							pt1 = pt2;
							for (; pt1.x < p2.x; ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][0];
									if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
										maxline[pt.y * X_MAX + pt.x][0] += 2;
										maxline[pt.y * X_MAX + pt.x][1] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}nethnum++;
						}
					}
					else{
						if ((p1.y + (p2.x - p1.x) / 2) <= Y_MAX){
							pt1 = p1;
							for (; pt1.y < (p1.y + (p2.x - p1.x) / 2); ++pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx135num++;
							pt2 = pt1;
							for (; pt2.y > p1.y; --pt2.y, ++pt2.x) {
								int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt2.y * X_MAX + pt2.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx45num++;
							pt1 = pt2;
							for (; pt1.x < p2.x; ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][0];
									if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
										maxline[pt.y * X_MAX + pt.x][0] += 2;
										maxline[pt.y * X_MAX + pt.x][1] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}nethnum++;
						}
						else{
							pt1 = p1;
							for (; pt1.y < Y_MAX; ++pt1.x, ++pt1.y) {
								int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][3];
									if (maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] <= 2 && maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] > 4){
										maxline[pt.y * X_MAX + pt.x][3] += 2;
										maxline[pt.y * X_MAX + pt.x][2] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}netx135num++;
							pt2 = pt1;
							for (; pt2.y > p1.y; --pt2.y, ++pt2.x) {
								int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt2.y * X_MAX + pt2.x][1];
									if (maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] <= 2 && maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] > 4){
										maxline[pt.y * X_MAX + pt.x][1] += 2;
										maxline[pt.y * X_MAX + pt.x][0] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}//netx45num++;
							pt1 = pt2;
							for (; pt1.x < p2.x; ++pt1.x) {
								int num = pt1.y * X_MAX + pt1.x;
								if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
									++record_p[pt1.y * X_MAX + pt1.x][0];
									if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
										maxline[pt.y * X_MAX + pt.x][0] += 2;
										maxline[pt.y * X_MAX + pt.x][1] -= 2;
									}
									line_net[net_id].point_edge.insert(num);

								}
							}nethnum++;
						}
					}
				}
			}
		}
		else if (gbest_ilp.cnt[i] == 3){
			lnum++;
			if (!ILP_CheckConnect3(p1, p2, gbest_ilp.sol[i], net_id)) {
				ExpandNode nt;
				nt.net_id = net_id;
				nt.pa_id = ilp_extend_point_vec[i].pa_id;
				nt.pb_id = ilp_extend_point_vec[i].pb_id;
				extend_unconnect.insert(nt);
				continue;
			}
			if (gbest_ilp.sol[i]) { // 1  represents horizontal then vertical
				if (p1.x < p2.x){//right-top
					for (; pt.y > p1.y; --pt.y) {
						int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
							++record_p[pt.y * X_MAX + pt.x][2];
							if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
								maxline[pt.y * X_MAX + pt.x][2] += 2;
								maxline[pt.y * X_MAX + pt.x][3] -= 2;
							}
							line_net[net_id].point_edge.insert(num);

						}
					}netvnum++;
					for (; pt.x > p1.x; --pt.x) {
						int num = pt.y * X_MAX + pt.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
							++record_p[pt.y * X_MAX + pt.x][0];
							if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
								maxline[pt.y * X_MAX + pt.x][0] += 2;
								maxline[pt.y * X_MAX + pt.x][1] -= 2;
							}
							line_net[net_id].point_edge.insert(num);

						}
					}nethnum++;
				}
				else{//left-top
					for (; pt.y > p1.y; --pt.y) {
						int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
							++record_p[pt.y * X_MAX + pt.x][2];
							if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
								maxline[pt.y * X_MAX + pt.x][2] += 2;
								maxline[pt.y * X_MAX + pt.x][3] -= 2;
							}
							line_net[net_id].point_edge.insert(num);

						}
					}netvnum++;
					for (; pt.x < p1.x; ++pt.x) {
						int num = pt.y * X_MAX + pt.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
							++record_p[pt.y * X_MAX + pt.x][0];
							if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
								maxline[pt.y * X_MAX + pt.x][0] += 2;
								maxline[pt.y * X_MAX + pt.x][1] -= 2;
							}
							line_net[net_id].point_edge.insert(num);

						}
					}nethnum++;
				}
			}
			else { // 0 represents first vertical then horizontal
				if (p1.x < p2.x){//right-top
					for (; pt.x > p1.x; --pt.x) {
						int num = pt.y * X_MAX + pt.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
							++record_p[pt.y * X_MAX + pt.x][0];
							if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
								maxline[pt.y * X_MAX + pt.x][0] += 2;
								maxline[pt.y * X_MAX + pt.x][1] -= 2;
							}
							line_net[net_id].point_edge.insert(num);

						}
					}nethnum++;
					for (; pt.y > p1.y; --pt.y) {
						int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
							++record_p[pt.y * X_MAX + pt.x][2];
							if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
								maxline[pt.y * X_MAX + pt.x][2] += 2;
								maxline[pt.y * X_MAX + pt.x][3] -= 2;
							}
							line_net[net_id].point_edge.insert(num);

						}
					}netvnum++;
				}
				else{//left-top
					for (; pt.x < p1.x; ++pt.x) {
						int num = pt.y * X_MAX + pt.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
							++record_p[pt.y * X_MAX + pt.x][0];
							if (maxline[pt.y * X_MAX + pt.x][0] - record_p[pt.y * X_MAX + pt.x][0] <= 2 && maxline[pt.y * X_MAX + pt.x][1] - record_p[pt.y * X_MAX + pt.x][1] > 4){
								maxline[pt.y * X_MAX + pt.x][0] += 2;
								maxline[pt.y * X_MAX + pt.x][1] -= 2;
							}
							line_net[net_id].point_edge.insert(num);

						}
					}nethnum++;
					for (; pt.y > p1.y; --pt.y) {
						int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()) {
							++record_p[pt.y * X_MAX + pt.x][2];
							if (maxline[pt.y * X_MAX + pt.x][2] - record_p[pt.y * X_MAX + pt.x][2] <= 2 && maxline[pt.y * X_MAX + pt.x][3] - record_p[pt.y * X_MAX + pt.x][3] > 4){
								maxline[pt.y * X_MAX + pt.x][2] += 2;
								maxline[pt.y * X_MAX + pt.x][3] -= 2;
							}
							line_net[net_id].point_edge.insert(num);

						}
					}netvnum++;

				}
			}
		}
	}
}
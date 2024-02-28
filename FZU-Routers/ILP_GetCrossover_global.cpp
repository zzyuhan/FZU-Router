void ILP_GetCrossover_global(const int& pop_ind)  //
{
    srand((unsigned)time(NULL));
    int sol_size = pop_ilp[pop_ind].sol.size();
    double c = rand() / (RAND_MAX + 1.0);
    if (c < c1_now_ilp) {
        int r1 = rand() % sol_size;
        int r2 = rand() % sol_size;
 //       while (r2 == r1) {
 //           r2 = rand() % sol_size;
  //      }
        if (r1 > r2)
            swap(r1, r2);
        int i;
        Point p1, p2;
        for (i = r1; i <= r2; ++i) {
            if (pop_ilp[pop_ind].sol[i] != gbest_ilp.sol[i]) { //???? study carefully the process????
                p1.x = line_net[ilp_extend_point_vec[i].net_id].pin[ilp_extend_point_vec[i].pa_id][0];
                p1.y = line_net[ilp_extend_point_vec[i].net_id].pin[ilp_extend_point_vec[i].pa_id][1];
                p2.x = line_net[ilp_extend_point_vec[i].net_id].pin[ilp_extend_point_vec[i].pb_id][0];
                p2.y = line_net[ilp_extend_point_vec[i].net_id].pin[ilp_extend_point_vec[i].pb_id][1];
                if (pop_ilp[pop_ind].sol[i]) { // if value 1 then become 0
                    pop_ilp[pop_ind].sol[i] = 0;
                    //pop_ilp[pop_ind].fit_value -= ILP_CalcLineLen(p1, p2);
                } else { // 0 --> 1
                    pop_ilp[pop_ind].sol[i] = 1;
                    //pop_ilp[pop_ind].fit_value += ILP_CalcLineLen(p1, p2);
                }
            }
        }
    }
}
void ILP_GetCrossover_global2(const int& pop_ind)  //
{
	srand((unsigned)time(NULL));
	int sol_size = pop_ilp[pop_ind].sol.size();
	double c = rand() / (RAND_MAX + 1.0);
	if (c < c1_now_ilp) {
		int r1 = rand() % sol_size;
		int r2 = rand() % sol_size;
		//       while (r2 == r1) {
		//           r2 = rand() % sol_size;
		//      }
		if (r1 > r2)
			swap(r1, r2);
		int i;
		Point p1, p2;
		for (i = r1; i <= r2; ++i) {
			if (pop_ilp[pop_ind].sol[i] != gbest_ilp.sol[i]) { //???? study carefully the process????
				p1.x = line_net[ilp_extend_point_vec2[i].net_id].pin[ilp_extend_point_vec2[i].pa_id][0];
				p1.y = line_net[ilp_extend_point_vec2[i].net_id].pin[ilp_extend_point_vec2[i].pa_id][1];
				p2.x = line_net[ilp_extend_point_vec2[i].net_id].pin[ilp_extend_point_vec2[i].pb_id][0];
				p2.y = line_net[ilp_extend_point_vec2[i].net_id].pin[ilp_extend_point_vec2[i].pb_id][1];
				if (pop_ilp[pop_ind].sol[i]) { // if value 1 then become 0
					pop_ilp[pop_ind].sol[i] = 0;
					//pop_ilp[pop_ind].fit_value -= ILP_CalcLineLen(p1, p2);
				}
				else { // 0 --> 1
					pop_ilp[pop_ind].sol[i] = 1;
					//pop_ilp[pop_ind].fit_value += ILP_CalcLineLen(p1, p2);
				}
			}
		}
	}
}
void ILP_GetCrossover_global3(const int& pop_ind)  //
{
	srand((unsigned)time(NULL));
	int sol_size = pop_ilp[pop_ind].sol.size();
	double c = rand() / (RAND_MAX + 1.0);
	if (c < c1_now_ilp) {
		int r1 = rand() % sol_size;
		int r2 = rand() % sol_size;
		//       while (r2 == r1) {
		//           r2 = rand() % sol_size;
		//      }
		if (r1 > r2)
			swap(r1, r2);
		int i;
		Point p1, p2;
		for (i = r1; i <= r2; ++i) {
			if (pop_ilp[pop_ind].sol[i] != gbest_ilp.sol[i]) { //???? study carefully the process????
				p1.x = line_net[ilp_extend_point_vec3[i].net_id].pin[ilp_extend_point_vec3[i].pa_id][0];
				p1.y = line_net[ilp_extend_point_vec3[i].net_id].pin[ilp_extend_point_vec3[i].pa_id][1];
				p2.x = line_net[ilp_extend_point_vec3[i].net_id].pin[ilp_extend_point_vec3[i].pb_id][0];
				p2.y = line_net[ilp_extend_point_vec3[i].net_id].pin[ilp_extend_point_vec3[i].pb_id][1];
				if (pop_ilp[pop_ind].sol[i]) { // if value 1 then become 0
					pop_ilp[pop_ind].sol[i] = 0;
					//pop_ilp[pop_ind].fit_value -= ILP_CalcLineLen(p1, p2);
				}
				else { // 0 --> 1
					pop_ilp[pop_ind].sol[i] = 1;
					//pop_ilp[pop_ind].fit_value += ILP_CalcLineLen(p1, p2);
				}
			}
		}
	}
}
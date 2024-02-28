void ILP_PSO() {
    ILP_Initialize();
    int flag;
    int i, j, ind;
    int eval = evaluations_ilp;
    int sol_size = ilp_extend_point_vec.size();
    double min_fitness = gbest_ilp.fit_value;
    while (eval--) {
        flag = 0;
        c2_now_ilp = c1_now_ilp - c1_dec_ilp;
        for (i = 0; i < popsize_ilp; ++i) { //update the velocity and position of each particle
            ILP_GetMutation(i);
            ILP_GetCrossover_self(i);
            ILP_GetCrossover_global(i);
            pop_ilp[i].fit_value = ILP_GetFitness(i);
            if (pbest_ilp[i].fit_value > pop_ilp[i].fit_value) { //update the pbest
                for (j = 0; j < sol_size; ++j) {
                    pbest_ilp[i].sol[j] = pop_ilp[i].sol[j];
                }
                pbest_ilp[i].fit_value = pop_ilp[i].fit_value;
            }
            if (pop_ilp[i].fit_value < min_fitness) {
                flag = 1;
                ind = i;
                min_fitness = pop_ilp[i].fit_value;
            }
        }
        if (flag) { //update the gbest
            for (j = 0; j < sol_size; ++j) {
                gbest_ilp.sol[j] = pop_ilp[ind].sol[j];
            }
            gbest_ilp.fit_value = pop_ilp[ind].fit_value;
        }
        w_now_ilp -= inerdec_ilp;//
        c1_now_ilp -= c1_dec_ilp;//
    }

}
void ILP_PSO2() {
	ILP_Initialize2();
	int flag;
	int i, j, ind;
	int eval = evaluations_ilp;
	int sol_size = ilp_extend_point_vec2.size();
	double min_fitness = gbest_ilp.fit_value;
	while (eval--) {
		flag = 0;
		c2_now_ilp = c1_now_ilp - c1_dec_ilp;
		for (i = 0; i < popsize_ilp; ++i) { //update the velocity and position of each particle
			ILP_GetMutation2(i);
			ILP_GetCrossover_self2(i);
			ILP_GetCrossover_global2(i);
			pop_ilp[i].fit_value = ILP_GetFitness22(i);
			if (pbest_ilp[i].fit_value > pop_ilp[i].fit_value) { //update the pbest
				for (j = 0; j < sol_size; ++j) {
					pbest_ilp[i].sol[j] = pop_ilp[i].sol[j];
				}
				pbest_ilp[i].fit_value = pop_ilp[i].fit_value;
			}
			if (pop_ilp[i].fit_value < min_fitness) {
				flag = 1;
				ind = i;
				min_fitness = pop_ilp[i].fit_value;
			}
		}
		if (flag) { //update the gbest
			for (j = 0; j < sol_size; ++j) {
				gbest_ilp.sol[j] = pop_ilp[ind].sol[j];
			}
			gbest_ilp.fit_value = pop_ilp[ind].fit_value;
		}
		w_now_ilp -= inerdec_ilp;//
		c1_now_ilp -= c1_dec_ilp;//
	}

}
void ILP_PSO3() {
	ILP_Initialize3();
	int flag;
	int i, j, ind;
	int eval = evaluations_ilp;
	int sol_size = ilp_extend_point_vec3.size();
	double min_fitness = gbest_ilp.fit_value;
	while (eval--) {
		flag = 0;
		c2_now_ilp = c1_now_ilp - c1_dec_ilp;
		for (i = 0; i < popsize_ilp; ++i) { //update the velocity and position of each particle
			ILP_GetMutation3(i);
			ILP_GetCrossover_self3(i);
			ILP_GetCrossover_global3(i);
			pop_ilp[i].fit_value = ILP_GetFitness3(i);
			if (pbest_ilp[i].fit_value > pop_ilp[i].fit_value) { //update the pbest
				for (j = 0; j < sol_size; ++j) {
					pbest_ilp[i].sol[j] = pop_ilp[i].sol[j];
				}
				pbest_ilp[i].fit_value = pop_ilp[i].fit_value;
			}
			if (pop_ilp[i].fit_value < min_fitness) {
				flag = 1;
				ind = i;
				min_fitness = pop_ilp[i].fit_value;
			}
		}
		if (flag) { //update the gbest
			for (j = 0; j < sol_size; ++j) {
				gbest_ilp.sol[j] = pop_ilp[ind].sol[j];
			}
			gbest_ilp.fit_value = pop_ilp[ind].fit_value;
		}
		w_now_ilp -= inerdec_ilp;//
		c1_now_ilp -= c1_dec_ilp;//
	}

}
void ILP_PSO4() {
	ILP_Initialize4();
	int flag;
	int i, j, ind;
	int eval = evaluations_ilp;
	int sol_size = ilp_extend_point_vec.size();
	double min_fitness = gbest_ilp.fit_value;
	while (eval--) {
		flag = 0;
		c2_now_ilp = c1_now_ilp - c1_dec_ilp;
		for (i = 0; i < popsize_ilp; ++i) { //update the velocity and position of each particle
			ILP_GetMutation(i);
			ILP_GetCrossover_self(i);
			ILP_GetCrossover_global(i);
			pop_ilp[i].fit_value = ILP_GetFitness4(i);
			if (pbest_ilp[i].fit_value > pop_ilp[i].fit_value) { //update the pbest
				for (j = 0; j < sol_size; ++j) {
					pbest_ilp[i].sol[j] = pop_ilp[i].sol[j];
				}
				pbest_ilp[i].fit_value = pop_ilp[i].fit_value;
			}
			if (pop_ilp[i].fit_value < min_fitness) {
				flag = 1;
				ind = i;
				min_fitness = pop_ilp[i].fit_value;
			}
		}
		if (flag) { //update the gbest
			for (j = 0; j < sol_size; ++j) {
				gbest_ilp.sol[j] = pop_ilp[ind].sol[j];
			}
			gbest_ilp.fit_value = pop_ilp[ind].fit_value;
		}
		w_now_ilp -= inerdec_ilp;//
		c1_now_ilp -= c1_dec_ilp;//
	}

}

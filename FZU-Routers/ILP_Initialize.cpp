void ILP_Initialize() { // Initialize of ILP
    int i, j;
    int sol_size = ilp_extend_point_vec.size();
    for (i = 0; i < popsize_ilp; ++i) {
        pop_ilp[i].sol.clear();
        pop_ilp[i].sol.resize(sol_size);
        pbest_ilp[i].sol.clear();
        pbest_ilp[i].sol.resize(sol_size);
    }
    gbest_ilp.sol.clear();
    gbest_ilp.sol.resize(sol_size);
    srand((unsigned)time(NULL));
    //randomly generate the string 01
    for (i = 0; i < popsize_ilp; ++i) {
        for (j = 0; j < sol_size; ++j) {
            pop_ilp[i].sol[j] = rand() % 2;
        }
        pop_ilp[i].fit_value = ILP_GetFitness(i);
    }
    sort(pop_ilp, pop_ilp + popsize_ilp);
    for (i = 0; i < popsize_ilp; ++i) {
        for (j = 0; j < sol_size; ++j) {
            pbest_ilp[i].sol[j] = pop_ilp[i].sol[j];
            pbest_ilp[i].fit_value = pop_ilp[i].fit_value;
        }
    }
    for (j = 0; j < sol_size; ++j) {
        gbest_ilp.sol[j] = pop_ilp[0].sol[j];
        gbest_ilp.fit_value = pop_ilp[0].fit_value;
    }
}
void ILP_Initialize2() { // Initialize of ILP
	int i, j;
	int sol_size = ilp_extend_point_vec2.size();
	for (i = 0; i < popsize_ilp; ++i) {
		pop_ilp[i].sol.clear();
		pop_ilp[i].sol.resize(sol_size);
		pbest_ilp[i].sol.clear();
		pbest_ilp[i].sol.resize(sol_size);
	}
	gbest_ilp.sol.clear();
	gbest_ilp.sol.resize(sol_size);
	srand((unsigned)time(NULL));
	//randomly generate the string 01
	for (i = 0; i < popsize_ilp; ++i) {
		for (j = 0; j < sol_size; ++j) {
			pop_ilp[i].sol[j] = rand() % 2;
		}
		pop_ilp[i].fit_value = ILP_GetFitness22(i);
	}
	sort(pop_ilp, pop_ilp + popsize_ilp);
	for (i = 0; i < popsize_ilp; ++i) {
		for (j = 0; j < sol_size; ++j) {
			pbest_ilp[i].sol[j] = pop_ilp[i].sol[j];
			pbest_ilp[i].fit_value = pop_ilp[i].fit_value;
		}
	}
	for (j = 0; j < sol_size; ++j) {
		gbest_ilp.sol[j] = pop_ilp[0].sol[j];
		gbest_ilp.fit_value = pop_ilp[0].fit_value;
	}
}
void ILP_Initialize3() { // Initialize of ILP
	int i, j;
	int sol_size = ilp_extend_point_vec3.size();
	for (i = 0; i < popsize_ilp; ++i) {
		pop_ilp[i].sol.clear();
		pop_ilp[i].sol.resize(sol_size);
		pbest_ilp[i].sol.clear();
		pbest_ilp[i].sol.resize(sol_size);
	}
	gbest_ilp.sol.clear();
	gbest_ilp.sol.resize(sol_size);
	srand((unsigned)time(NULL));
	//randomly generate the string 01
	for (i = 0; i < popsize_ilp; ++i) {
		for (j = 0; j < sol_size; ++j) {
			pop_ilp[i].sol[j] = rand() % 2;
		}
		pop_ilp[i].fit_value = ILP_GetFitness3(i);
	}
	sort(pop_ilp, pop_ilp + popsize_ilp);
	for (i = 0; i < popsize_ilp; ++i) {
		for (j = 0; j < sol_size; ++j) {
			pbest_ilp[i].sol[j] = pop_ilp[i].sol[j];
			pbest_ilp[i].fit_value = pop_ilp[i].fit_value;
		}
	}
	for (j = 0; j < sol_size; ++j) {
		gbest_ilp.sol[j] = pop_ilp[0].sol[j];
		gbest_ilp.fit_value = pop_ilp[0].fit_value;
	}
}
void ILP_Initialize4() { // Initialize of ILP
	int i, j;
	int sol_size = ilp_extend_point_vec.size();
	for (i = 0; i < popsize_ilp; ++i) {
		pop_ilp[i].sol.clear();
		pop_ilp[i].sol.resize(sol_size);
		pop_ilp[i].cnt.clear();
		pop_ilp[i].cnt.resize(sol_size);
		pbest_ilp[i].sol.clear();
		pbest_ilp[i].sol.resize(sol_size);
		pbest_ilp[i].cnt.clear();
		pbest_ilp[i].cnt.resize(sol_size);
	}
	gbest_ilp.sol.clear();
	gbest_ilp.sol.resize(sol_size);
	gbest_ilp.cnt.clear();
	gbest_ilp.cnt.resize(sol_size);
	srand((unsigned)time(NULL));
	//randomly generate the string 01
	for (i = 0; i < popsize_ilp; ++i) {
		for (j = 0; j < sol_size; ++j) {
			pop_ilp[i].sol[j] = rand() % 2;
			pop_ilp[i].cnt[j] = ilp_extend_point_vec[j].cnt;
		}
		pop_ilp[i].fit_value = ILP_GetFitness4(i);
	}
	sort(pop_ilp, pop_ilp + popsize_ilp);
	for (i = 0; i < popsize_ilp; ++i) {
		for (j = 0; j < sol_size; ++j) {
			pbest_ilp[i].sol[j] = pop_ilp[i].sol[j];
			pbest_ilp[i].cnt[j] = pop_ilp[i].cnt[j];
			pbest_ilp[i].fit_value = pop_ilp[i].fit_value;
		}
	}
	for (j = 0; j < sol_size; ++j) {
		gbest_ilp.sol[j] = pop_ilp[0].sol[j];
		gbest_ilp.cnt[j] = pop_ilp[0].cnt[j];
		gbest_ilp.fit_value = pop_ilp[0].fit_value;
	}
}
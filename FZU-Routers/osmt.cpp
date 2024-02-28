void osmt()
{
    int eval,i,j,index,flag;
    double min_fitness;
	w_now=w_start;
	c1_now=c1_start;
	InitializePop();
	index=1;//	the serial number of gbest is initialized as 1 
	min_fitness=pop_osmt[1].fit_value;
	eval=1;
	while(eval<=evaluations)
	{
        flag=0;
		if(eval>1)
		{
			w_now=w_now-inerdec; // 
            c1_now=c1_now-c1_dec;//
		}
		c2_now=1-c1_now;
		for(i=1;i<=popsize;i++) //
		{
 //           printf("%d evaluation %d particle mu:\n",eval,i); //
			  GetMutation(i); //
//			  printf("%d evaluation %d particle cs:\n",eval,i); //
			  GetCrossover_self(i); //
//			  printf("%d evaluation %d particle cg:\n",eval,i); //
			  GetCrossover_global(i); //
			  if(pbest[i].fit_value>pop_osmt[i].fit_value) //
			  {
				  for(j=1;j<=3*(line_net[ver].pin_sum-1);j++)
					  pbest[i].edge[j]=pop_osmt[i].edge[j];
                  pbest[i].fit_value=pop_osmt[i].fit_value;
			  }
			  if(pop_osmt[i].fit_value<min_fitness)//
			  {
				  flag=1;
				  index=i;
//				  pp=eval;
				  min_fitness=pop_osmt[i].fit_value;
			  }
		}
        if(flag)
		{
		  for(j=1;j<=3*(line_net[ver].pin_sum-1);j++)
		    	gbest.edge[j]=pop_osmt[index].edge[j];
          gbest.fit_value=min_fitness;
		}
		eval++;
	}
	line_net[ver].osmt.clear();
	line_net[ver].osmt.push_back(0);
	for(j=1;j<=3*(line_net[ver].pin_sum-1);j++)
		//line_net[ver].osmt[j]=gbest.edge[j];
		line_net[ver].osmt.push_back(gbest.edge[j]);
	line_net[ver].fit_value=gbest.fit_value;
}
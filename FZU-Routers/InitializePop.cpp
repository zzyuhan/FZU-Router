bool cmp(struct Pop_osmt a,struct Pop_osmt b)
{
	if(a.fit_value<b.fit_value)
	  return true;
	else 
	  return false ;
 }
void InitializePop()
{
	int i,j;
	for(i=1;i<=popsize;i++)
	{
        Generate_mst();  //	randomly generate the particles with the number of popsize
		for(j=1;j<=3*(line_net[ver].pin_sum-1);j++)
          pop_osmt[i].edge[j]=min_tree[j];  //	store into the array pop_osmt
		pop_osmt[i].fit_value=Getfitness(); //	calculte the fitness
//         printf("%lf\n",pop_osmt[i].fit_value);
	}
//	printf("\n");
	sort(pop_osmt+1,pop_osmt+popsize+1,cmp); //sort the initial population by their fitness values
	for(i=1;i<=popsize;i++)
	{
		for(j=1;j<=3*(line_net[ver].pin_sum-1);j++)
		{
			if(i==1) //ȡupdate the global best
			{
				gbest.edge[j]=pop_osmt[i].edge[j];
				gbest.fit_value=pop_osmt[i].fit_value;
			}
            pbest[i].edge[j]=pop_osmt[i].edge[j]; //	initialize each particle as its pbest 
		}
        pbest[i].fit_value=pop_osmt[i].fit_value;
	}
}
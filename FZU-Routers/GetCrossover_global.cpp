 void GetCrossover_global(int cur)
 {
	double c;
	int i,r1,r2,mid=0;
	c=rand()/(RAND_MAX+1.0);
    if(c<c2_now)
	{
	  r1=(int)((rand()/(RAND_MAX+1.0))*(line_net[ver].pin_sum-1))+1;//randomly select two positions of [1 to vertice-1]
	  r2=(int)((rand()/(RAND_MAX+1.0))*(line_net[ver].pin_sum-1))+1;
//	  while(r1==r2)
//		r2=(int)((rand()/(RAND_MAX+1.0))*line_net[ver].pin_sum)+1;
      if(r1>r2)
      {
		  mid=r1;
		  r1=r2;
		  r2=mid;
	  }
	  for(i=r1;i<=r2;i++)
         pop_osmt[cur].edge[i*3]=gbest.edge[i*3];
	  for(i=1;i<=3*(line_net[ver].pin_sum-1);i++)
		  min_tree[i]=pop_osmt[cur].edge[i];
	  pop_osmt[cur].fit_value=Getfitness(); 
	}
 }
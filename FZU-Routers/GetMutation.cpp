void GetMutation(int cur)
{
    double w=rand()/(RAND_MAX+1.0); //	randomly generate w (if w <w_now then mutation)
	int p1,p2,m1,m2,t,j;
	double f1=0,f2=0;
	if(w<w_now)
	{
	  p1=(int)((rand()/(RAND_MAX+1.0))*(line_net[ver].pin_sum-1))+1;//	randomly generate two positions to be mutated
	  p2=(int)((rand()/(RAND_MAX+1.0))*(line_net[ver].pin_sum-1))+1;
//	  while(p1==p2)
//		p2=(int)((rand()/(RAND_MAX+1.0))*line_net[ver].pin_sum)+1;
	  m1=pop_osmt[cur].edge[3*p1];//ȡget the pSteiner Choice bit of two mutated positions
	  m2=pop_osmt[cur].edge[3*p2];
      t=m1;
	  while(t==m1) //	mutate the first position
	  {
          f1=rand()/(RAND_MAX+1.0);
		  if(f1<0.1)
			  m1=2;
		  else if(f1>0.1&&f1<0.5)
			  m1=0;
		  else if(f1>=0.5&&f1<=0.9)
			  m1=1;
		  else m1=3;
	  }
	  pop_osmt[cur].edge[3*p1]=m1;
      t=m2;
	  while(t==m2) //	mutate the second position
	  {
          f2=rand()/(RAND_MAX+1.0);
		  if(f2<0.1)
			  m2=2;
		  else if(f2>0.1&&f2<0.5)
			  m2=0;
		  else if(f2>=0.5&&f2<=0.9)
			  m2=1;
		  else m2=3;
	  }
	  pop_osmt[cur].edge[3*p2]=m2;
      for(j=1;j<=3*(line_net[ver].pin_sum-1);j++)
		  min_tree[j]=pop_osmt[cur].edge[j];
	  pop_osmt[cur].fit_value=Getfitness(); 
	}
}
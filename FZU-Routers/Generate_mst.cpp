void Generate_mst()
{
   int start_point;
   start_point=(int)((rand()/(RAND_MAX+1.0))*line_net[ver].pin_sum)+1;//randomly generate the source point of minimal spanning tree
   double lowcost[20000]={0},min;
   int tree[20000][3]={0},adjvex[20000]={0},sign[20000],i,j,index=0;
   for(i=1;i<=line_net[ver].pin_sum;i++)
   {
	   lowcost[i]=line_net[ver].graphw[start_point][i];//initialize the nearest distance of each sink to be the distance with the source
       adjvex[i]=start_point;//initialize the nearest point of each sink to be the source
	   sign[i]=0;
   }
   sign[start_point]=1; //mark the source to be added in the minimal spanning tree
   for(i=1;i<line_net[ver].pin_sum;i++)
   {
         min=99999999;
		 for(j=1;j<=line_net[ver].pin_sum;j++)  //get the edge with the minimal distance
			 if(lowcost[j]<min&&!sign[j])
			 {
                 index=j;
				 min=lowcost[j];
			 }
		 sign[index]=1; //mark the new added point
		 tree[i][1]=adjvex[index]; //store the new added edge
		 tree[i][2]=index;
		 for(j=1;j<=line_net[ver].pin_sum;j++) //update the distance record
			 if(lowcost[j]>line_net[ver].graphw[j][index]&&!sign[j])
			 {
				 lowcost[j]=line_net[ver].graphw[j][index];
				 adjvex[j]=index;
			 }
   }
   for(i=1;i<=(line_net[ver].pin_sum-1);i++) //particle
   {
	   min_tree[i*3-2]=tree[i][1]; //the number of start point
	   min_tree[i*3-1]=tree[i][2]; //the number of end point
	   min_tree[i*3]=(int)((rand()/(RAND_MAX+1.0))*4); //connectted method£¬Î±SteinerµãÑ¡Ôñ
   }
}

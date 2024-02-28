struct node1
{
	double pos;
	double s;
	double e;
}xsegment[20000],ysegment[20000],r_x[20000],r_y[20000];//horizontal segment[y_coordinate left_point right_endpoint], vertical segment[x_coordinate bottom_point top_endpoint]
struct node2
{
	double sx;
	double sy;
	double ex;
	double ey;
}x45[20000],x135[20000];//X-architecture segment[start_point_xy_coordinate, endpoint_xy_coordinate]
bool cmp1(struct node1 a,struct node1 b)
{
	if(a.pos<b.pos) return true;
	else return false;
}
bool cmp2(struct node1 a,struct node1 b)
{
	if(a.s<b.s) return true;
	else return false;
}
double Getfitness()
{
    int i,k,sp,xt=0,yt=0,x45t=0,x135t=0,rxt=0,ryt=0;
	double x1,x2,y1,y2,fx,fy,fitness=0,midx,midy;
	for(i=1;i<vertice;i++)
	{
        x1=line_net[ver].pin[min_tree[i*3-2]][0]; //Æðstart_point_x
		y1=line_net[ver].pin[min_tree[i*3-2]][1]; //Æðstart_point_y
		x2=line_net[ver].pin[min_tree[i*3-1]][0]; //  endpoint_x
		y2=line_net[ver].pin[min_tree[i*3-1]][1]; //  endpoint_y
		sp=min_tree[i*3]; // pSteiner choice
		fx=fabs(x1-x2);  //	 horizontal distance
		fy=fabs(y1-y2);  //  vertical distance
        if(sp==2||sp==3)  // pSteiner choice is manhattan architecture
		{
			if(sp==2)
			{
				xsegment[xt].pos=y2; //y_coordinate of horizontal segment
				ysegment[yt].pos=x1; //vx_coordinate of vertical segment
			}
			else 
			{
			    xsegment[xt].pos=y1;
				ysegment[yt].pos=x2;
			}
			if(x1>x2)
			{
				xsegment[xt].s=x2; //x_coordinate of left_point in horizontal segment
				xsegment[xt++].e=x1; //x_coordinate of right_endpoint in horizontal segment
			}
			else
			{
                xsegment[xt].s=x1;
				xsegment[xt++].e=x2;
			}
			if(y1>y2)
			{
				ysegment[yt].s=y2; //y_coordinate of bottom_point in vertical segment
				ysegment[yt++].e=y1; //y_coordinate of top_endpoint in vertical segment
			}
			else 
			{
                ysegment[yt].s=y1;
				ysegment[yt++].e=y2;
			}
		}
		if(sp==0||sp==1) // pSteiner choice is X-architecture
		{
           if(fx==0||fy==0) //two points in the same rectilinear line
		   {
			   if(sp==0)
			   {
                  xsegment[xt].pos=y1; 
				  ysegment[yt].pos=x1;
			   }
			   else
			   {
				   xsegment[xt].pos=y2;
				   ysegment[yt].pos=x2;
			   }
			   	if(x1>x2)
				{
				   xsegment[xt].s=x2; //	x_coordinate of left_point in horizontal segment	
				   xsegment[xt++].e=x1; //	x_coordinate of right_endpoint in horizontal segment
				}
			    else
				{
                   xsegment[xt].s=x1;
				   xsegment[xt++].e=x2;
				}
			    if(y1>y2)
				{
				   ysegment[yt].s=y2; //	y_coordinate of bottom_point in vertical segment
				   ysegment[yt++].e=y1; //	y_coordinate of top_endpoint in vertical segment
				}
			    else 
				{
                   ysegment[yt].s=y1;
			  	   ysegment[yt++].e=y2;
				}
		   }
		   else //	two points are not in the same rectilinear line
		   {
                if(x1>x2) //Èçif start point is in the right of endpoint then exchange their positions
				{
					midx=x1;
					midy=y1;
					x1=x2;
					y1=y2;
					x2=midx;
                    y2=midy;
					sp=!sp;
				}
                if(fx>fy) //	horizontal distance is larger than vertical distance
				{
				  if(sp==0) // 0 Choice
				  {
					xsegment[xt].pos=y1;
					xsegment[xt].s=x1;
					xsegment[xt++].e=x2-fy;
					if(y1<y2) //	record the two points of 45¢X segment
					{
						x45[x45t].sx=x2-fy;
						x45[x45t].sy=y1;
						x45[x45t].ex=x2;
						x45[x45t++].ey=y2;
					}
					else  //	record the two points of 135¢X segment
					{
                        x135[x135t].sx=x2-fy;
						x135[x135t].sy=y1;
						x135[x135t].ex=x2;
						x135[x135t++].ey=y2;
					}
				  }
				  else //	1 Choice
				  {
					xsegment[xt].pos=y2;
					xsegment[xt].s=x1+fy;
					xsegment[xt++].e=x2;
					if(y1<y2)
					{
                      	x45[x45t].sx=x1;
						x45[x45t].sy=y1;
						x45[x45t].ex=x1+fy;
						x45[x45t++].ey=y2;
					}
					else
					{
                        x135[x135t].sx=x1;
						x135[x135t].sy=y1;
						x135[x135t].ex=x1+fy;
						x135[x135t++].ey=y2;
					}
				  }
				}
				else //	horizontal distance is not larger than vertical distance
				{
                  if(sp==0) 
				  {
					ysegment[yt].pos=x1;
					if(y1<y2)
					{
						x45[x45t].sx=x1;
						x45[x45t].sy=y2-fx;
						x45[x45t].ex=x2;
						x45[x45t++].ey=y2;
						ysegment[yt].s=y1;
					    ysegment[yt++].e=y2-fx;
					}
					else
					{
                        x135[x135t].sx=x1;
						x135[x135t].sy=y2+fx;
						x135[x135t].ex=x2;
						x135[x135t++].ey=y2;
					 	ysegment[yt].s=y1;
					    ysegment[yt++].e=y2+fx;
					}
				  }
				  else
				  {
					ysegment[yt].pos=x2;
					if(y1<y2)
					{
                      	x45[x45t].sx=x1;
						x45[x45t].sy=y1;
						x45[x45t].ex=x2;
						x45[x45t++].ey=y1+fx;
						ysegment[yt].s=y1+fx;
				   	    ysegment[yt++].e=y2;
					}
					else
					{
                        x135[x135t].sx=x1;
						x135[x135t].sy=y1;
						x135[x135t].ex=x2;
						x135[x135t++].ey=y1-fx;
						ysegment[yt].s=y1-fx;
					    ysegment[yt++].e=y2;
					}
				  }
				}
		   }
		} 
	}
	for(i=0;i<x45t;i++) //	rotate the 45¢X segment clockwise with 45¢X and become the horizontal, then add it into xsegment
	{
		r_x[rxt].pos=P*(x45[i].sy-x45[i].sx); //	y_coordinate after rotation
		r_x[rxt].s=P*(x45[i].sx+x45[i].sy);   //	start_point after rotation
		r_x[rxt++].e=P*(x45[i].ex+x45[i].ey); //	endpoint after rotation
	}
	for(i=0;i<x135t;i++)//	rotate the 135¢X segment clockwise with 45¢X and become the vertical, then add it into ysegment
	{
        r_y[ryt].pos=P*(x135[i].sx+x135[i].sy); 
		r_y[ryt].s=P*(x135[i].sy-x135[i].sx);
		r_y[ryt++].e=P*(x135[i].ey-x135[i].ex);
	}
	for(i=0;i<xt;i++) //	adjust the horizontal to make that the start_point is in the left of endpoint
	{
		if(xsegment[i].s>xsegment[i].e)
		{
			midx=xsegment[i].s;
			xsegment[i].s=xsegment[i].e;
			xsegment[i].e=midx;
		}
	}
	for(i=0;i<yt;i++)
	{
       if(ysegment[i].s>ysegment[i].e)
	   {
		   midy=ysegment[i].s;
		   ysegment[i].s=ysegment[i].e;
		   ysegment[i].e=midy;
	   }
	}
	for(i=0;i<rxt;i++)
	{
		if(r_x[i].s>r_x[i].e)
		{
			midx=r_x[i].s;
			r_x[i].s=r_x[i].e;
			r_x[i].e=midx;
		}
	}
	for(i=0;i<ryt;i++)
	{
		if(r_y[i].s>r_y[i].e)
		{
			midx=r_y[i].s;
			r_y[i].s=r_y[i].e;
			r_y[i].e=midx;
		}
	}
	sort(xsegment,xsegment+xt,cmp1);  //	sort by the first column
	sort(ysegment,ysegment+yt,cmp1);
	sort(r_x,r_x+rxt,cmp1);
	sort(r_y,r_y+ryt,cmp1);
	for(i=1;i<xt;i++)//	sort xsegment by the first column then sort by the second column
	{
        k=i-1;
		while(i<xt&&xsegment[i].pos==xsegment[i-1].pos)
			i++;
		sort(xsegment+k,xsegment+i,cmp2);
	}
	for(i=1;i<yt;i++)//	sort ysegment by the first column then sort by the second column
	{
        k=i-1;
		while(i<yt&&ysegment[i].pos==ysegment[i-1].pos)
			i++;
		sort(ysegment+k,ysegment+i,cmp2);
	}
	for(i=1;i<rxt;i++)//	sort the rotated xsegment by the first column then sort by the second column
	{
        k=i-1;
		while(i<rxt&&r_x[i].pos==r_x[i-1].pos)
			i++;
		sort(r_x+k,r_x+i,cmp2);
	}
    for(i=1;i<ryt;i++)//	sort the rotated ysegment by the first column then sort by the second column
	{
        k=i-1;
		while(i<ryt&&r_y[i].pos==r_y[i-1].pos)
			i++;
		sort(r_y+k,r_y+i,cmp2);
	}
	for(i=1;i<xt;i++) //	merge the overlapped xsegment
	{
		if(xsegment[i].pos==xsegment[i-1].pos)
			if(xsegment[i].s==xsegment[i-1].s)
			{
				if(xsegment[i].e<xsegment[i-1].e)
					xsegment[i].e=xsegment[i-1].e;
				xsegment[i-1].pos=0;
				xsegment[i-1].s=0;
				xsegment[i-1].e=0;
			}
			else 
			{
				if(xsegment[i].s<xsegment[i-1].e)
				{
				   xsegment[i].s=xsegment[i-1].s;
			   	   if(xsegment[i].e<xsegment[i-1].e)
				  	 xsegment[i].e=xsegment[i-1].e;
				   xsegment[i-1].pos=0;
			 	   xsegment[i-1].s=0;
				   xsegment[i-1].e=0;
				}
			}
	}
	for(i=1;i<yt;i++) //	merge the overlapped ysegment
	{
		if(ysegment[i].pos==ysegment[i-1].pos)
			if(ysegment[i].s==ysegment[i-1].s)
			{
				if(ysegment[i].e<ysegment[i-1].e)
					ysegment[i].e=ysegment[i-1].e;
				ysegment[i-1].pos=0;
				ysegment[i-1].s=0;
				ysegment[i-1].e=0;
			}
			else 
			{
				if(ysegment[i].s<ysegment[i-1].e)
				{
					ysegment[i].s=ysegment[i-1].s;
			    	if(ysegment[i].e<ysegment[i-1].e)
					  ysegment[i].e=ysegment[i-1].e;
				    ysegment[i-1].pos=0;
				    ysegment[i-1].s=0;
				    ysegment[i-1].e=0;
				}
			}
	}
	for(i=1;i<rxt;i++) //	merge the overlapped rotated_xsegment
	{
		if(r_x[i].pos==r_x[i-1].pos)
			if(r_x[i].s==r_x[i-1].s)
			{
				if(r_x[i].e<r_x[i-1].e)
					r_x[i].e=r_x[i-1].e;
				r_x[i-1].pos=0;
				r_x[i-1].s=0;
				r_x[i-1].e=0;
			}
			else 
			{
				if(r_x[i].s<r_x[i-1].e)
				{
					r_x[i].s=r_x[i-1].s;
				    if(r_x[i].e<r_x[i-1].e)
					  r_x[i].e=r_x[i-1].e;
				    r_x[i-1].pos=0;
				    r_x[i-1].s=0;
				    r_x[i-1].e=0;
				}
			}
	}
	for(i=1;i<ryt;i++) //	merge the overlapped rotated_ysegment
	{
		if(r_y[i].pos==r_y[i-1].pos)
			if(r_y[i].s==r_y[i-1].s)
			{
				if(r_y[i].e<r_y[i-1].e)
					r_y[i].e=r_y[i-1].e;
				r_y[i-1].pos=0;
				r_y[i-1].s=0;
				r_y[i-1].e=0;
			}
			else 
			{
				if(r_y[i].s<r_y[i-1].e)
				{
					r_y[i].s=r_y[i-1].s;
				    if(r_y[i].e<r_y[i-1].e)
				  	  r_y[i].e=r_y[i-1].e;
			    	r_y[i-1].pos=0;
			    	r_y[i-1].s=0;
				    r_y[i-1].e=0;
				}
			}
	}
	for(i=0;i<xt;i++)
	  fitness+=(xsegment[i].e-xsegment[i].s);
	for(i=0;i<yt;i++)
	  fitness+=(ysegment[i].e-ysegment[i].s);
	for(i=0;i<rxt;i++)
	  fitness+=(r_x[i].e-r_x[i].s);
	for(i=0;i<ryt;i++)
	  fitness+=(r_y[i].e-r_y[i].s);
	return fitness;
}                 
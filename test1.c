void phods_motion_estimation(int current[N][M],int previous[N][M],int
vectors_x[N/B][M/B],int vectors_y[N/B][M/B])
{
	int x,y,k,l,p1,p2,q2,distx=0,disty=0,S,min1,min2,bestx,besty;
	for(x=0;x<N/B;x++) /* For all blocks in the current frame */
	for(y=0;y<M/B;y++)
	{
		vectors_x[x][y]=0;
		vectors_y[x][y]=0;
		S=4;
		while(S>0)
		{
			min1=255*B*B;
			min2=255*B*B;
			for(i=-S;i<S+1;i+=S) /* For all candidate blocks in X dimension */
			{
				distx=0;
				disty=0;
				for(k=0;k<B;k++) /* For all pixels in the block */
				for(l=0;l<B;l++)
				{
					p1=current[B*x+k][B*y+l];
					if((B*x+vectors_x[x][y]+i+k)<0 || (B*x+vectors_x[x][y]+i+k)>(N-1) ||
							(B*y+vectors_y[x][y]+l)<0 || (B*y+vectors_y[x][y]+l)>(M-1))
					p2=0;
					else
					p2=previous[B*x+vectors_x[x][y]+i+k][B*y+vectors_y[x][y]+l];
					if((B*x+vectors_x[x][y]+k)<0 || (B*x+vectors_x[x][y]+k)>(N-1) ||
							(B*y+vectors_y[x][y]+i+l)<0 || (B*y+vectors_y[x][y]+i+l)>(M-1))
					q2=0;
					else
					q2=previous[B*x+vectors_x[x][y]+k][B*y+vectors_y[x][y]+i+l];
					distx+=abs(p1-p2);
					disty+=abs(p1-q2);
				}
				if(distx<min1)
				{
					min1=distx;
					bestx=i;
					if(disty<min2)
					{
						min2=disty;
						besty=i;
					}
				}
				S=S/2;
				vectors_x[x][y]+=bestx;
				vectors_y[x][y]+=besty;
			}
		}
	}
}

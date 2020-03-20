#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <climits>

class Grain{
	public:
		int **kcell;
		double Xa[2],Xb[2],Xc[2],dx[2];
		double Wd[2];
		int Ndiv[2];
		int ncell;
		void init(int nx, int ny);
		void print();
		void fprint(char fn[128]);
		void set_size(double wx, double wy);
		void set_pos(double x0, double y0);
		void star();
		int *far;
		int *known;
		int *trial;
		int nfr,nkw,ntr;
	private:
};

void Grain::init(int nx, int ny){
	Ndiv[0]=nx;
	Ndiv[1]=ny;
	ncell=nx*ny;
	int *pt=(int *)malloc(sizeof(int)*ncell);
	kcell=(int **)malloc(sizeof(int*)*nx);

	far=(int *)malloc(sizeof(int)*ncell);
	trial=(int *)malloc(sizeof(int)*ncell);
	known=(int *)malloc(sizeof(int)*ncell);

	int i;
	for(i=0;i<ncell;i++){
		pt[i]=0;
		far[i]=-1;
		trial[i]=-1;
		known[i]=-1;
	};
	for(i=0;i<nx;i++) kcell[i]=pt+i*ny;
};
void Grain::print(){
	int i,j;
	for(i=0;i<Ndiv[0];i++){
	for(j=0;j<Ndiv[1];j++){
		printf("%d ",kcell[i][j]);
	}
	printf("\n");
	}
};
void Grain::fprint(char fn[128]){
	FILE *fp=fopen(fn,"w");
	int i,j;
	fprintf(fp,"# Xa[0:2],Xb[0:2]\n");
	fprintf(fp,"%lf, %lf\n",Xa[0],Xa[1]);
	fprintf(fp,"%lf, %lf\n",Xb[0],Xb[1]);
	fprintf(fp,"# Ndat[0:2]\n");
	fprintf(fp,"%d, %d\n",Ndiv[0],Ndiv[1]);
	fprintf(fp,"# val\n");
	for(i=0;i<Ndiv[0];i++){
	for(j=0;j<Ndiv[1];j++){
		fprintf(fp,"%d\n",kcell[i][j]);
	}
	}
	fclose(fp);
};
void Grain::set_size(double wx, double wy){
	Wd[0]=wx;
	Wd[1]=wy;
	wx*=0.5;
	wy*=0.5;
	Xa[0]=Xc[0]-wx;
	Xa[1]=Xc[1]-wy;
	Xb[0]=Xc[0]+wx;
	Xb[1]=Xc[1]+wy;
	dx[0]=Wd[0]/Ndiv[0];
	dx[1]=Wd[1]/Ndiv[1];
};
void Grain::set_pos(double x0, double y0){
	Xc[0]=x0;
	Xc[1]=y0;
};
void Grain::star(){
	double pi=4.0*atan(1.0);
	int Nth=180;
	double rr,th,dth=2.*pi/Nth;
	int i,j,ix,iy;
	double r0=0.2,r1=0.6;
	double xx,yy;
	for(i=0;i<Nth;i++){
		th=dth*i;
		rr=(r1-r0)*cos(2.*th)*cos(2.*th)+r0;
		xx=Xc[0]+rr*cos(th);
		yy=Xc[0]+rr*sin(th);
		ix=int((xx-Xa[0])/dx[0]);
		iy=int((yy-Xa[1])/dx[1]);
		if(ix<0) continue;
		if(ix>=Ndiv[0]) continue;
		if(iy<0) continue;
		if(iy>=Ndiv[1]) continue;
		kcell[ix][iy]=1;
	}

	int I,J;
	for(i=0;i<Ndiv[0];i++){
	for(j=0;j<Ndiv[1];j++){
		//if(kcell[i][j]==0) kcell[i][j]=INT_MAX;
		if(kcell[i][j]==1){
			I=i+1;
			J=j+1;
			if(I>=Ndiv[0]) I=i;
			if(J>=Ndiv[1]) J=j;
			if(kcell[I][j]!=1)kcell[I][j]=2;
			if(kcell[i][J]!=1) kcell[i][J]=2;
			I=i-1;
			J=j-1;
			if(I<0) I=i;
			if(J<0) J=j;
			if(kcell[I][j]!=1) kcell[I][j]=2;
			if(kcell[i][J]!=1) kcell[i][J]=2;

		}
	}
	}

	nkw=0;
	ntr=0;
	nfr=0;
	for(i=0;i<Ndiv[0];i++){
	for(j=0;j<Ndiv[1];j++){
		I=i*Ndiv[1]+j;
		if(kcell[i][j]==0) far[nfr++]=I;
		if(kcell[i][j]==1) known[nkw++]=I;
		if(kcell[i][j]==2) trial[ntr++]=I;

	}
	}
	printf("nkw=%d, ntr=%d, nfr=%d (n=%d)\n",nkw,ntr,nfr,nkw+ntr+nfr);
};
int main(){
	Grain gr;

	gr.init(40,40);
	gr.set_size(2.0,2.0);
	gr.set_pos(0.0,0.0);
	gr.star();
	gr.print();
	char fname[128]="kcell.dat";
	gr.fprint(fname);

	return(0);
};

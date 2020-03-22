#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <climits>


double Eikonal(
		double phi[4],
		double F,
		double h,
		double sol
);
int main(){
	double h=1.0;
	double F=1.0;
	double Phi[3][3];
	int i0=1;
	int j0=1;

	Phi[i0+1][j0]=INT_MAX;
	Phi[i0][j0+1]=INT_MAX;
	Phi[i0-1][j0]=1.0;
	Phi[i0][j0-1]=3.0;

	double phi[4];
	phi[0]=Phi[i0][j0-1];
	phi[1]=Phi[i0+1][j0];
	phi[2]=Phi[i0][j0+1];
	phi[3]=Phi[i0-1][j0];


	double sol[3];
	double t24,t13;

	t24=phi[1];
	if(t24 > phi[3]) t24=phi[3];
	sol[0]=h/F+t24;

	t13=phi[0];
	if(t13 > phi[2]) t13=phi[2];
	sol[1]=h/F+t13;

	double a,b,c,D;
	t24=phi[1];
	if(t24 > phi[3]) t24=phi[3];
	t13=phi[0];
	if(t13 > phi[2]) t13=phi[2];
	a=2.0;
	b=-(t24+t13);
	c=t24*t24+t13*t13-h*h/F*F;
	D=b*b-a*c;
	if(D<0.0){
		sol[2]=INT_MAX;
	}else{
		sol[2]=(-b+sqrt(D))/a;
	}

	double res;
	for(int j=0;j<3;j++){
		res=Eikonal(phi,F,h,sol[j]);
		printf("sol[0]=%lf res=%lf\n",sol[j],res);
	}

	// Substitution into Eikonal Euqation
	double Dx,Dy;
	//double t0=1.0+1./sqrt(2.0);
	double t0=4.0;
	int i;
	double tmpx,tmpy;
	Dx=0.0;
	Dy=0.0;
	for(i=0;i<2;i++){
		tmpx=t0-phi[2*i+1];
		tmpy=t0-phi[2*i];
		if(tmpx>Dx) Dx=tmpx;
		if(tmpy>Dy) Dy=tmpy;
	}
	Dx/=h;
	Dy/=h;
	res=sqrt(Dx*Dx+Dy*Dy)*F-1.0;
	printf("res=%lf\n",res);
	
	return(1);
};

double Eikonal(
		double phi[4],
		double F,
		double h,
		double sol
){
	// Substitution into Eikonal Euqation
	double Dx,Dy;
	//double t0=4.0;
	int i;
	double tmpx,tmpy,res;
	Dx=0.0;
	Dy=0.0;
	for(i=0;i<2;i++){
		tmpx=sol-phi[2*i+1];
		tmpy=sol-phi[2*i];
		if(tmpx>Dx) Dx=tmpx;
		if(tmpy>Dy) Dy=tmpy;
	}
	Dx/=h;
	Dy/=h;
	res=sqrt(Dx*Dx+Dy*Dy)*F-1.0;
	//printf("res=%lf\n",res);
	return(res);
};

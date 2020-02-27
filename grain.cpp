#include <stdio.h>
#include <stdlib.h>

class Grain{
	public:
		int **kcell;
		double Xa[2],Xb[2],Xc[2];
		double Wd[2];
		double Ndiv[2];
		int ncell;
		void init(int nx, int ny);
		void print();
		void set_size(double wx, double wy);
		void set_pos(double x0, double y0);
	private:
};

void Grain::init(int nx, int ny){
	Ndiv[0]=nx;
	Ndiv[1]=ny;
	ncell=nx*ny;
	int *pt=(int *)malloc(sizeof(int)*ncell);
	kcell=(int **)malloc(sizeof(int*)*nx);

	int i;
	for(i=0;i<ncell;i++) pt[i]=i;
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
void Grain::set_size(double wx, double wy){
	Wd[0]=wx;
	Wd[1]=wy;
};
void Grain::set_pos(double x0, double y0){
	Xc[0]=x0;
	Xc[1]=y0;
};
int main(){
	Grain gr;

	gr.init(20,20);
	gr.set_size(2.0,2.0);
	gr.set_pos(0.0,0.0);
	gr.print();

	return(0);
};

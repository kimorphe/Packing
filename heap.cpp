#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class Heap{
	public:
		double *dat;	// data 
		double *hp;	// heap 
		int *indx;	// index
		int nsize;	// array size
		int ndat;	// number of data
		void init(int n); 
		void print();
		void heap();
		void sort();
		double pop(int *i0);
		void  add2heap(double val);
	private:

};
//-------------------------------------------
void Heap::init(int n){
	nsize=n;
	ndat=0;
	dat=(double *)malloc(sizeof(double)*nsize);
	hp=(double *)malloc(sizeof(double)*nsize);
	indx=(int *)malloc(sizeof(int)*nsize);
	for(int i=0;i<nsize;i++){
		dat[i]=0.0;
		hp[i]=0.0;
		indx[i]=i;
	}
};
void Heap::heap(){
	int i,c,p;
	double tmp;
	int itmp;
	for(i=0;i<ndat;i++){
		hp[i]=dat[i];
		c=i+1;
		p=c/2;
		while(hp[p-1]>hp[c-1]){
			tmp=hp[p-1];
			hp[p-1]=hp[c-1];
			hp[c-1]=tmp;

			itmp=indx[p-1];
			indx[p-1]=indx[c-1];
			indx[c-1]=itmp;
			c=p;
			p=c/2;
			if(p==0) break;
		};
	};
};

void Heap::add2heap(double val){
	ndat++;
	if(ndat>nsize){
		printf(" Error!!: number of data exceeds array size !\n");
		printf(" ndat=%d nsize=%d\n",ndat,nsize);
		printf(" --> abort process.");
		ndat--;
		exit(-1);
	};
	dat[ndat-1]=val;
	hp[ndat-1]=val;
	indx[ndat-1]=ndat-1;
	double tmp;
	int c=ndat;
	int p=ndat/2;
	int itmp;
	while(hp[p-1]>hp[c-1]){
		tmp=hp[p-1];
		hp[p-1]=hp[c-1];
		hp[c-1]=tmp;

		itmp=indx[p-1];
		indx[p-1]=indx[c-1];
		indx[c-1]=itmp;
		c=p;
		p=c/2;
		if(p==0) break;
	};
};

double Heap::pop(int *i0){
	double tmp,dat0=hp[0];
	hp[0]=hp[ndat-1];
	ndat--;
	*i0=indx[0];

	int c,c1,c2,p=1;
	c1=p*2;
	int itmp;
	while(c1<=ndat){
		c2=c1+1;
		c=c1;
		if(c2<=ndat){
			if(hp[c2-1]<hp[c1-1]) c=c2;
		};
		if(hp[p-1] < hp[c-1]) break;
		tmp=hp[p-1];
		hp[p-1]=hp[c-1];
		hp[c-1]=tmp;

		itmp=indx[p-1];
		indx[p-1]=indx[c-1];
		indx[c-1]=itmp;
		p=c;
		c1=p*2;
	};
	return(dat0);
};

void Heap::sort(){
	int i,p,c,c1,c2;
	int n=ndat;
	double tmp;
	int itmp;

	Heap::heap();
	for(i=0;i<ndat;i++){
		tmp=hp[0];
		hp[0]=hp[n-1];
		hp[n-1]=tmp;

		itmp=indx[0];
		indx[0]=indx[n-1];
		indx[n-1]=itmp;
		n--;

		p=1;
		c1=p*2;
		while(c1<=n){
			c2=c1+1;
			c=c1;
			if(c2 <= n){
				if(hp[c2-1]<hp[c1-1]) c=c2;
			};
			if(hp[p-1]<hp[c-1]) break;
			tmp=hp[p-1];
			hp[p-1]=hp[c-1];
			hp[c-1]=tmp;

			itmp=indx[p-1];
			indx[p-1]=indx[c-1];
			indx[c-1]=itmp;
			p=c;
			c1=p*2;
		}
	};		
};
void Heap::print(){
	//for(int i=0;i<nsize;i++) printf("%d %lf %lf\n",i,dat[i],hp[i]);
	for(int i=0;i<ndat;i++) printf("%d %lf %d %lf\n",i,dat[i],indx[i],hp[i]);
	puts("----------------------------");
};
int main(){
	Heap hp;
	int i,nsize=22,ndat=21;
	hp.init(nsize);
	hp.ndat=ndat;
	for(i=0;i<ndat;i++){
		hp.dat[i]=sin(double(i));
	};
	hp.heap();
	hp.print();
	hp.add2heap(0.3);
	hp.print();

	int i0;
	double dat0;
	for(i=0;i<ndat;i++){
		dat0=hp.pop(&i0);
	       	printf("%lf %lf\n",dat0,hp.dat[i0]);
	}
	puts("-------------------");


	hp.ndat=ndat;
	for(i=0;i<ndat;i++){
		hp.dat[i]=sin(double(i));
	};

	hp.heap();
	hp.add2heap(0.3);
	hp.print();
	puts("-------------------");
	hp.sort();
	hp.print();

	return(0);
};

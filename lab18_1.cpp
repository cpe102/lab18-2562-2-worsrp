#include<iostream>
#include<cmath>
using namespace std;

struct Rect{
	double x,y,w,h;
};

double overlap(Rect,Rect);

int main(){
	double x,y,w,h;
	cout << "Please input Rect 1 (x y w h): ";
	cin >> x >> y >> w >> h;
	Rect data1 = {x,y,w,h}; 
	cout << "Please input Rect 2 (x y w h): ";
	cin >> x >> y >> w >> h;
	Rect data2 = {x,y,w,h}; 
	cout << "Overlap area = " << overlap(data1,data2) << "\n";	
	return 0;
}

double overlap(Rect data1,Rect data2){
	 double xdif,ydif,wmax,hmax,wmin,hmin;
    xdif=abs((data1.x)-(data2.x));
    ydif=abs((data1.y)-(data2.y));
    if(data1.w>data2.w){
        wmax=data1.w;
        wmin=data2.w;
    }else{
        wmax=data2.w;
        wmin=data1.w;
    }
    if(data1.h>data2.h){
        hmax=data1.h;
        hmin=data2.h;
    }else{
        hmax=data2.h;
        hmin=data1.h;
    }
    if(xdif>wmax||ydif>hmax){
        return 0;
    }else{
         if(xdif<abs((data1.w)-(data2.w))||ydif<abs((data1.h)-(data2.h))){
             return wmin*hmin;
         }else {
             return ((wmax - xdif) * (hmax - ydif));
         }
    }
}
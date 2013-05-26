#include <iostream>
#include <math.h>

const double PI = 3.1415926;
const double vint = 2 * PI;
const int STEP = 50000;

double *x_sun = NULL;
double *y_sun = NULL;
double *x_planet = NULL;
double *y_planet = NULL;

using namespace std;

void evolv(double gammma)
{
	double delta_t = 0.002;
	double x_p, y_p, x_s, y_s, r;
	double vx_p, vy_p, vx_s, vy_s;

	x_p = 1;
	vy_p = vint;
	vy_s = gammma * vy_p;

	x_sun =new double[STEP];
	y_sun =new double[STEP];
	x_planet =new double[STEP];
	y_planet =new double[STEP];


	for (int i = 0; i < STEP; ++i)
	{
		r = sqrt((x_p-x_s) * (x_p-x_s) + (y_p-y_s) * (y_p-y_s));
		x_sun[i] = x_s;
		y_sun[i] = y_s;
		x_planet[i] = x_p;
		y_planet[i] = y_p;

		vx_p -= 4 * PI * PI * (x_p - x_s) * delta_t / pow(r,3);
		vy_p -= 4 * PI * PI * (y_p - y_s) * delta_t / pow(r,3);
		vx_s = - gammma * vx_p;
		vy_s = - gammma * vy_p;

		x_p += vx_p * delta_t;
		y_p += vy_p * delta_t;
		x_s += vx_s * delta_t;
		y_s += vy_s * delta_t;
	//	cout<<x_sun[i]<<"   "<<y_sun[i]<<endl;
	//	cout<<x_planet[i]<<"   "<<y_planet[i]<<endl;
	}
}
/*int main()
{
	evolv(500);
	return 0;
}*/

void two_body()
{
	gSystem->Unlink("GRanim.gif"); // delete old file
	
	c1 = new TCanvas("c1","The Special Solar System",200,10,600,400);

	for (int i = 0; i < 100; ++i)
	{
	double gammma = (i + 1) * 0.01;
 	evolv(gammma);

	TGraph* gr1 = new TGraph(STEP, x_sun, y_sun);
	TGraph* gr2 = new TGraph(STEP, x_planet, y_planet);
	gr1->GetXaxis()->SetTitle("X (AU/yr)");
	gr1->GetYaxis()->SetTitle("Y (AU/yr");
	gr1->SetTitle("The Special Solar System");
	gr1->GetXaxis()->SetLimits(-20,20);
	gr1->GetYaxis()->SetRangeUser(-20,20);
	gr1->SetMarkerStyle(1);
	gr1->SetMarkerSize(1);
	gr1->SetMarkerColor(2);
	gr1->Draw("AP");

	gr2->SetLineWidth(3);
	gr2->SetMarkerStyle(1);
	gr2->SetLineColor(2);
	gr2->SetMarkerColor(30);
	gr2->Draw("P");

	//c1->Modified();
    c1->Update();
    if (gROOT->IsBatch()) 
    {
        c1->Print("GRanim.gif+");
       // printf("i = %d\n", i);
    }

	}
  c1->Modified();
  // make infinite animation by adding "++" to the file name
  if (gROOT->IsBatch()) 
  c1->Print("GRanim.gif++");




}
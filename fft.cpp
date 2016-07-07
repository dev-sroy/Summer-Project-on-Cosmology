#include<iostream>
#include<fftw3.h>
#include<complex.h>
#include<fstream>
#include<cmath>
#include <malloc.h>

using namespace std;
const float pi = 3.1415923;

void arrange(fftw_complex *arr, int n)
{
  for(int i=0;i<n/2;i++)
  {
    float temp0 = arr[i][0];
    float temp1 = arr[i][1];
    arr[i][0]=arr[n/2+i][0];
    arr[i][1]=arr[n/2+i][1];
    arr[n/2+i][0]=temp0;
    arr[n/2+i][1]=temp1;
  }
}
double max(double *arr, int n)
{
  double m=arr[0];
  for(int i=1;i<n;i++)
  {
    if(arr[i]>m)
    {
      m=arr[i];
    }
  }
  return m;
}
int deviate(double *arr, int n)
{
  int pos=-1;
  double hmax=0.5*max(arr,n);
  for(int i=n/2;i<n;i++)
  {
    if(arr[i]<hmax)
    {
      pos=i;
      break;
    }
  }
  int dev=abs(n-2*pos);
  return dev;
}
int main()
{
  ofstream ofile,ofilep;
  ofstream ifile;
  ofile.open("output.txt");
  ofilep.open("power.txt");
  ifile.open("input.txt");
  fftw_complex *in, *out;
  double *out_abs,*p;
  fftw_plan p1;
  int n;
  char c;
  float beg,end,step,mean,stdev,range;
  cout<<"Enter the number of elements: ";
  cin>>n;
  cout<<"Enter starting element: ";
  cin>>beg;
  cout<<"Enter ending element: ";
  cin>>end;
  cout<<"Enter mean: ";
  cin>>mean;
  cout<<"Enter standard deviation: ";
  cin>>stdev;
  in=(fftw_complex *) fftw_malloc(sizeof(fftw_complex)*n);
  out=(fftw_complex *) fftw_malloc(sizeof(fftw_complex)*n);
  out_abs=(double *) malloc(sizeof(double)*n);
  p=(double *) malloc(sizeof(double)*n);
  range=end-beg;
  step=range/float(n);
  for(int i=0; i<n; i++)
  {
    float elt=beg+step*i;
    in[i][0] = exp((-1)*pow(elt-mean,2)/(2*pow(stdev,2)))*(1/sqrt(n));
    in[i][1] =0;
  }
  p1=fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p1);
  cout<<"Input array: ";
  for(int i=0;i<n;i++)
  {
    cout<<i<<" "<<in[i][0]<<" "<<in[i][1]<<endl;
    ifile<<i<<" "<<in[i][0]<<endl;
  }
  fftw_free(in);
  cout<<endl;
  cin>>c;

  arrange(out,n);
  cout<<"Output array: ";
  for(int i=0;i<n;i++)
  {
    double norm = sqrt(pow(out[i][0],2)+pow(out[i][1],2));
    out_abs[i]=norm;
    cout<<i<<" "<<out[i][0]<<" "<<out[i][1]<<" "<<norm<<endl;
    ofile<<i<<" "<<out[i][0]<<" "<<out[i][1]<<" "<<norm<<endl;
  }

  cout<<"Absolute values: ";
  for(int i=0;i<n;i++)
  {
    cout<<i<<" "<<out_abs[i]<<endl;
  }

  cout<<endl;
  int hmax=deviate(out_abs,n);
  cout<<hmax<<endl;
  for(int i=0;i<n;i++)
  {
    p[i] = pow(out_abs[i],2)+pow(out_abs[n-1-i],2);
    ofilep<<i<<" "<<p[i]<<endl;
  }
  ofile.close();
  ifile.close();
  ofilep.close();
  fftw_destroy_plan(p1);
  fftw_free(out);
  delete out_abs;
  delete p;
  return 0;
}

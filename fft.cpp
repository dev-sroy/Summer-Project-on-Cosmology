#include<iostream>
#include<fftw3.h>
#include<complex.h>
#include<fstream>
#include<cmath>

using namespace std;

int main()
{
  ofstream ofile;
  ofstream ifile;
  ofile.open("output.txt");
  ifile.open("input.txt");
  fftw_complex *in, *out, *in_check;
  fftw_plan p1, p2;
  int n,beg_out, end_out, freq;
  char c;
  float beg,end,step,mean,stdev;
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
  cout<<"Enter beginning range for output array: ";
  cin>>beg_out;
  cout<<"Enter ending range for output array: ";
  cin>>end_out;
  cout<<"Enter sampling frequency: ";
  cin>>freq;
  in=(fftw_complex *) fftw_malloc(sizeof(fftw_complex)*n);
  out=(fftw_complex *) fftw_malloc(sizeof(fftw_complex)*n);
  in_check = (fftw_complex *) fftw_malloc(sizeof(fftw_complex)*n);
  step=(end-beg)/float(n);
  for(int i=0; i<n; i++)
  {
    float elt=beg+step*i;
    in[i][0]=exp(-1*(elt-mean)*(elt-mean));
    //in[i][0] = exp((-1)*pow(elt-mean,2)/(2*pow(stdev,2)))*(1/sqrt(n));
    in[i][1] =0;
  }
  p1=fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  p2=fftw_plan_dft_1d(n, out, in_check, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p1);
  fftw_execute(p2);
  cout<<"Input array: ";
  for(int i=0;i<n;i++)
  {
    cout<<i<<" "<<in[i][0]<<" "<<in[i][1]<<endl;
    ifile<<i<<" "<<in[i][0]<<endl;
  }
  fftw_free(in);
  cout<<endl;
  cin>>c;
  cout<<"Output array: ";
  for(int i=beg_out;i<=end_out;i+=freq)
  {
    {
    double norm = sqrt(pow(out[i][0],2)+pow(out[i][1],2));
    cout<<i<<" "<<out[i][0]<<" "<<out[i][1]<<" "<<norm<<endl;
    ofile<<i<<" "<<out[i][0]<<" "<<out[i][1]<<" "<<norm<<endl;
  }
  }
  cin>>c;
  cout<<"Backward transform: ";
  for(int i=0;i<n;i++)
  {
    cout<<i<<" "<<in_check[i][0]<<" "<<in_check[i][1]<<endl;
  }
  ofile.close();
  ifile.close();
  fftw_destroy_plan(p1);
  fftw_destroy_plan(p2);

  fftw_free(out);
  fftw_free(in_check);
  return 0;
}

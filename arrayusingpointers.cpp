#include<iostream>
using namespace std;
int main(){
  int arr[5],i;
  cout<<"Enter elements: ";
  for(i=0;i<5;i++)
    cin>>*(arr+i);
  cout<<"You entered: ";
  for(i=0;i<5;i++)
    cout<<*(arr+i)<<endl;
  return 0;
}

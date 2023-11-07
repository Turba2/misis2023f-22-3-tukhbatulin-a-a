#include <iostream> 
#include <algorithm> 
using namespace std; 
  
#define in long long 
const in MAX_SIZE=1e6+10; 
in test_cases, n, arr[MAX_SIZE]; 
in i, j, sum1, sum2, answer; 
  
  
int main(){ 
 cin>>test_cases; 
 for(i=0;i<test_cases;i++){ 
  cin>>n; 
  sum1=0; 
  for(j=0;j<n;j++){ 
   cin>>arr[j]; 
   sum1+=arr[j]; 
  } 
  sort(arr,arr+n); 
  j=0,sum2=0; 
  while(sum2<sum1/2){ 
   sum2+=arr[n-1-j]; 
   j++; 
  } 
  answer=(sum1+1)/2+j; 
  cout<<answer<<endl;  
 } 
 return 0; 
}
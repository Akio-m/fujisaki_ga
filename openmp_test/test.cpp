#include <iostream> 
#include <chrono>
#include <omp.h>

using namespace std; 

int main(int argc, char const *argv[]){
  
  double j[100001];

  auto start = chrono::system_clock::now(); //計測開始

  #ifdef _OPENMP
    //cout << "The number of processors is " << omp_get_num_procs() << endl;
    //cout << "The number of processors is " << omp_get_num_threads() << endl;
    #pragma omp parallel num_threads(5)
      #pragma omp for
  #endif
    for(int i=0; i < 100000; i++){
      j[i] = i;
    }
    

  auto end = chrono::system_clock::now(); //計測終了
  auto dur = end - start;
  auto msec = chrono::duration_cast<chrono::microseconds>(dur).count();//要した時間をミリ秒(1/1000秒)に変換
  cout << msec << " msec" << endl;

  return 0;
}
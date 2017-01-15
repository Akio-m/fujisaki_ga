/**
 * @file sort_ga.cpp
 * @brief Fuji_GAクラスのsort_ga関数の実装です。
 * @detail 個体の適合度の昇順にソートする。
 * @date 2016-10-16
 * @author Akichika HIGA, Tomio Takara
 */

#include "Fuji_GA.hpp" // Fuji_GAクラスの定義

using namespace std;

/**
 * @fn
 * sort_ga
 * @brief ソートを行う。
 * @detail 個体の適合度の昇順にソートする。
 */
void Fuji_GA::sort_ga(){

  // vectorにFuji_Para構造体を借り置きして、sortしやすくする
  Fuji_Para param_temp[ GA_SIZE ]; // ga_listのコピー
  vector< pair< double, int > > temp;

  // 仮のga_listに全てコピーする
  for( int i = 0; i < GA_SIZE; ++i ){
    for (int j = 0; j < MORA_SIZE; ++j){
      param_temp[ i ].F_min[ j ] = ga_list[ i ]->F_min[ j ];
      param_temp[ i ].tau[ j ] = ga_list[ i ]->tau[ j ];
      param_temp[ i ].fitness = ga_list[ i ]->fitness;
      param_temp[ i ].fitness_relative = ga_list[ i ]->fitness_relative;
    }
    // pairで個体適応度と構造体番号を入れるから、sortしたあとでも呼び出せる
    temp.push_back( pair< double, int > ( ga_list[ i ]->fitness, i ) ); // 個体適応度, 構造体番号 
  }

  // tempをソート
  sort( temp.begin(), temp.end() );

  //ga_listに変更を書き込む
  for(int i = 0; i < GA_SIZE; ++i){
    for (int j = 0; j < MORA_SIZE; ++j){
      ga_list[ i ]->F_min[ j ] = param_temp[ temp[ i ].second ].F_min[ j ];
      ga_list[ i ]->tau[ j ] = param_temp[ temp[ i ].second ].tau[ j ];
    }
    ga_list[ i ]->fitness = param_temp[ temp[ i ].second ].fitness;
    ga_list[ i ]->fitness_relative = param_temp[ temp[ i ].second ].fitness_relative;
  }
  
}
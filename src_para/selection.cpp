/**
 * @file selection.cpp
 * @brief Fuji_GAクラスのselection関数の実装です。
 * @detail GAオペレータの選択を行う。ここではエリート選択とランキング選択をしている。
 * @date 2016-10-16
 * @author Akichika HIGA, Tomio Takara
 */

#include "Fuji_GA.hpp" // Fuji_GAクラスの定義

using namespace std;

/**
 * @fn
 * selection
 * @brief 選択を行う。
 * @detail GAオペレータの選択を行う。ここではエリート選択とランキング選択をしている。
 */
void Fuji_GA::selection(){

  // ga_listを適応度昇順にsortしておく
  sort_ga();

  // ga_listのコピーを作って、直接影響を与えないようにする
  Fuji_Para param_temp[ GA_SIZE ]; // ga_listのコピー 
  vector< pair< double, int > > temp;

  int i = 0;
  int j = 0;
  //#ifdef _OPENMP
  //#pragma omp parallel for private(j) num_threads(2)
  //#endif 
  for(i = 0; i < GA_SIZE; ++i ){
    for(j = 0; j < MORA_SIZE; ++j){
      param_temp[ i ].F_min[ j ] = ga_list[ i ]->F_min[ j ];
      param_temp[ i ].tau[ j ] = ga_list[ i ]->tau[ j ];
      param_temp[ i ].fitness = ga_list[ i ]->fitness;
      param_temp[ i ].fitness_relative = ga_list[ i ]->fitness_relative;
    }
    temp.push_back( pair< double, int > ( ga_list[ i ]->fitness, i ) );
  }
  /*
  for(i = 0; i < GA_SIZE; ++i){
    temp.push_back( pair< double, int > ( ga_list[ i ]->fitness, i ) );
  }
  */

  // エリート戦略
  //! エリート個体数を得る
  int elite_num = ( int )( GA_SIZE * ELITE_COPY ); // エリート数を決める
  //! 残り個体数をカウントする
  int capacity = elite_num; 
  for(i = 0; i < elite_num; ++i ){
    for (j = 0; j < MORA_SIZE; ++j){
      param_temp[ i ].F_min[ j ] = ga_list[ temp[ i ].second ]->F_min[ j ];
      param_temp[ i ].tau[ j ] = ga_list[ temp[ i ].second ]->tau[ j ];
      param_temp[ i ].fitness = ga_list[ temp[ i ].second ]->fitness;
      param_temp[ i ].fitness_relative = ga_list[ temp[ i ].second ]->fitness_relative;
    }
  }

  //ランク戦略 
  mt19937_64 engine( seed );
  uniform_real_distribution< double > real_Distribution( 0.0, 1.0 );

  for (i = capacity; i < GA_SIZE; ++i){
    //! 乱数を得る
    double dice = real_Distribution( engine );
    if( dice <= RANK_1 ){
      
      for (j = 0; j < MORA_SIZE; ++j){
        param_temp[ i ].F_min[ j ] = ga_list[ temp[ 0 ].second ]->F_min[ j ];
        param_temp[ i ].tau[ j ] = ga_list[ temp[ 0 ].second ]->tau[ j ];
      }
      param_temp[ i ].fitness = ga_list[ temp[ 0 ].second ]->fitness;
      param_temp[ i ].fitness_relative = ga_list[ temp[0].second ]->fitness_relative;
      ++capacity;

    }else if( dice <= RANK_1 + RANK_2 ){

      for (j = 0; j < MORA_SIZE; ++j){
        param_temp[ i ].F_min[ j ] = ga_list[ temp[ 1 ].second ]->F_min[ j ];
        param_temp[ i ].tau[ j ] = ga_list[ temp[ 1 ].second ]->tau[ j ];
      }
      param_temp[ i ].fitness = ga_list[ temp[ 1 ].second ]->fitness;
      param_temp[ i ].fitness_relative = ga_list[ temp[ 1 ].second ]->fitness_relative;
      ++capacity;

    }else if( dice <= RANK_1 + RANK_2 + RANK_3 ){

      for (j = 0; j < MORA_SIZE; ++j){
        param_temp[ i ].F_min[ j ] = ga_list[ temp[ 2 ].second ]->F_min[ j ];
        param_temp[ i ].tau[ j ] = ga_list[ temp[ 3 ].second ]->tau[ j ];
      }
      param_temp[ i ].fitness = ga_list[ temp[ 3 ].second ]->fitness;
      param_temp[ i ].fitness_relative = ga_list[ temp[ 3 ].second ]->fitness_relative;
      ++capacity;
    
    }else if( dice <= RANK_1 + RANK_2 + RANK_3 + RANK_4 ){

      for (j = 0; j < MORA_SIZE; ++j){
        param_temp[ i ].F_min[ j ] = ga_list[ temp[ 4 ].second ]->F_min[ j ];
        param_temp[ i ].tau[ j ] = ga_list[ temp[ 4 ].second ]->tau[ j ];
      }
      param_temp[ i ].fitness = ga_list[ temp[ 4 ].second ]->fitness;
      param_temp[ i ].fitness_relative = ga_list[ temp[ 4 ].second ]->fitness_relative;
      ++capacity;

    }else{
    
      for (j = 0; j < MORA_SIZE; ++j){
        param_temp[ i ].F_min[ j ] = ga_list[ temp[ 5 ].second ]->F_min[ j ];
        param_temp[ i ].tau[ j ] = ga_list[ temp[ 5 ].second ]->tau[ j ];
      }
      param_temp[ i ].fitness = ga_list[ temp[ 5 ].second ]->fitness;
      param_temp[ i ].fitness_relative = ga_list[ temp[ 5 ].second ]->fitness_relative;
      ++capacity;
    }
  }

  //ga_listに変更を書き込む
  for(i = 0; i < GA_SIZE; ++i){
    for (j = 0; j < MORA_SIZE; ++j){
      ga_list[ i ]->F_min[ j ] = param_temp[ i ].F_min[ j ];
      ga_list[ i ]->tau[ j ] = param_temp[ i ].tau[ j ];
    }
    ga_list[ i ]->fitness = param_temp[ i ].fitness;
    ga_list[ i ]->fitness_relative = param_temp[ i ].fitness_relative;
  }

}
/**
 * @file calc_fitness.cpp
 * @brief Fuji_GAクラスのメンバ関数calc_fitnessの実装。
 * @date 2016-10-16
 * @author Akichika HIGA, Tomio Takara
 */

#include "Fuji_GA.hpp"

using namespace std;

/**
 * @fn
 * calc_fitness
 * @brief フレーム間の誤差を計算する関数です。
 * @param (gene_num) 個体番号
 * @param (frame_size) フレームサイズ
 * @param (*target) ターゲットの配列
 * @detail ターゲットファイルとのフレーム間誤差を藤崎モデルに基づいて計算する。計算した後、それを適応度としてFuji_Para.fitnessに格納する。
 */
void Fuji_GA::calc_fitness( const int gene_num, const int frame_size, const double *target ){

  double F_min[ MORA_SIZE + 1 ]; //! F_minを格納する
  double tau[ MORA_SIZE + 1]; //! tauを格納しておく

  // 最初の値を固定する。これで安定する。
  F_min[ 0 ] = 0.0; // F_min固定
  tau[ 0 ] = 7; // tau固定

  // ga_listに影響がないようにコピーしておく
  for(int i = 0; i < MORA_SIZE; ++i){
    F_min[ i + 1 ] = ga_list[ gene_num ]->F_min[ i ]; 
    tau[ i + 1 ] = ga_list[ gene_num ]->tau[ i ] + 10; // 最初に10秒を置く
  }

  double F_diff[ MORA_SIZE ]; //! F_min差を格納しておく

  for(int i = 0; i < MORA_SIZE; ++i){
    F_diff[ i ] = F_min[ i + 1 ] - F_min[ i ];
  }

  double accumuler = 0.0; //! 累積誤差
  double temp_time = 0.0; //! 時間を一時保存
  double temp = 0.0; //! 途中式の結果
  double unit_step = 0.0; //! ユニットステップ関数の出力を保持
  double F_result[ frame_size + 10 ]; //! 藤崎モデルの出力を保持
  double result = 0.0; //! 藤崎モデルの出力とターゲットとの誤差を保持
  double result_show = 0.0;

  for(int s = 1; s < frame_size + 10; ++s){
    
    accumuler = 0.0;
    for(int i = 0; i < MORA_SIZE; ++i){
    
      temp_time = ( s - tau[ i ] ) / 100.0;

      temp = 1 - ( 1 + BETA * temp_time ) * exp( -1 * BETA * temp_time );

      if( temp_time >= 0.0 ){
        unit_step = 1.0;
      }else{
        unit_step = 0.0;
      }

      accumuler += F_diff[ i ] * temp * unit_step;
    }

    F_result[ s ] = F_min[ 0 ] + accumuler; // ここのF_minを出力したら藤崎モデルの出力を見ることができる
  }


  #ifdef _OPENMP
    #pragma omp parallel sections num_threads(2)
    {
      #pragma omp section
      {
        for(int s = 11; s < frame_size + 10; ++s){
          result += fabs( target[ s - 11 ] - F_result[ s ] ); //誤差の絶対値累積
        }
      }
      #pragma omp section
      {
        for(int s = 11; s < frame_size + 10; ++s){
          result_show += fabs( (target[ s - 11 ] - F_result[ s ]) / target[ s - 11 ] ); //誤差の相対値累積
        }
      }
    }
  #endif

  ga_list[ gene_num ]->fitness = result; //誤差の絶対値累積
  //ga_list[ gene_num ]->fitness = result / frame_size; //誤差の相対値累積(結果が悪かったので無し)
  ga_list[ gene_num ]->fitness_relative = result_show / frame_size;
}
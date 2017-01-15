/**
 * @file crossover.cpp
 * @brief Fuji_GAクラスのcrossocer関数の実装です。
 * @detail ブレンド交叉を行います。個体間の値を取り出し、その間から乱数で値を得る。 tau値については平均をとる。
 * @date 2016-10-16
 * @author Akichika HIGA, Tomio Takara
 */

#include "Fuji_GA.hpp"

using namespace std;

/**
 * @fn
 * crossover
 * @brief 交叉を行う。
 * @detail ブレンド交叉を行う。個体間の値を取り出し、その間から乱数で値を得る。 tau値については平均をとる。
 */
void Fuji_GA::crossover(){

  // 交叉位置決定
  double temp_1 = 0.0; //! F値の交叉値を保持する
  double temp_2 = 0.0; //! F値の交叉値を保持する
  int temp_1_tau = 0; //! tau値の交叉値を保持する
  int temp_2_tau = 0; //! tau値の交叉値を保持する
  int list_temp = 0; //! 交叉位置を保持する
  double value_temp = 0.0; //! ブレンド交叉値を保持する
  int value_temp_tau = 0; //! tauの交叉値を保持する

  // 乱数オブジェクト生成
  mt19937_64 engine( seed ); // MT法による乱数生成
  uniform_int_distribution< int > int_Distribution( 0, (MORA_SIZE - 1) );

  for (int i = 1; i < GA_SIZE; ++i){

    // F_min交叉位置決定
    list_temp = int_Distribution( engine );
    temp_1 = ga_list[ i - 1 ]->F_min[ list_temp ]; // if 5.4
    temp_2 = ga_list[ i ]->F_min[ list_temp ]; // if 9.0

    // F_min値決定
    uniform_real_distribution< double > real_Distribution( temp_1, temp_2 ); // 5.4 ~ 9.0の間で乱数マスク 
    value_temp = real_Distribution( engine );
    ga_list[ i ]->F_min[ list_temp ] = value_temp;

    // tau交叉位置決定
    list_temp = int_Distribution( engine );
    temp_1_tau = ga_list[ i - 1 ]->tau[ list_temp ]; // if 34 or 59
    temp_2_tau = ga_list[ i ]->tau[ list_temp ]; // if 59 or 32
    
    // tau値決定

    // 平均値を取る
    value_temp_tau = ( temp_1_tau + temp_2_tau ) / 2;

    ga_list[ i ]->tau[ list_temp ] = value_temp_tau;
  } 

}
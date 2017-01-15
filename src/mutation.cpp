/**
 * @file mutation.cpp
 * @brief Fuji_GAクラスのmutation関数の実装です。
 * @detail 突然変異を行います。F値は現在の値の+-20%を探索範囲として乱数を割り当てます。tau値は探索範囲を均等に割り振り、そこから乱数を割り当てます。
 * @date 2016-10-16
 * @author Akichika HIGA, Tomio Takara
 */

#include "Fuji_GA.hpp"// Fuji_GAクラスの定義å

using namespace std;

/**
 * @fn
 * mutation
 * @brief 突然変異を行う。
 * @param (frame_size) フレーム数
 * @detail 突然変異を行います。F値は現在の値の+-20%を探索範囲として乱数を割り当てます。tau値は探索範囲を均等に割り振り、そこから乱数を割り当てます。
 */
void Fuji_GA::mutation( const int frame_size ){

  double mute_num = 0.0; //! 突然変異乱数を保持する
  double temp_Fmin1 = 0.0; //! 突然変異中のF値を保持
  double temp_Fmin2 = 0.0; //! 突然変異中のF値を保持 temp
  int temp_tau1 = 0; //! 突然変異中のtau値を保持
  int temp_tau2 = 0; //! 突然変異中のtau値を保持 temp
  int temp_1 = 0; //! 突然変異tau値場合分け用
  //! 探索範囲を保持する
  int search_range = frame_size / MORA_SIZE; // 60 / 6 = 10, 65 / 6 = 10
  //int search_range = ( frame_size - 1 ) / MORA_SIZE;
  // 乱数オブジェクト生成
  mt19937_64 engine( seed );
  uniform_real_distribution< double > real_Distribution_Fmin( 0.0, 1.0 );
  uniform_real_distribution< double > real_Distribution_tau( 0.0, 1.0 );

  for( int i = 1; i < GA_SIZE; ++i ){
    for( int j = 0; j < MORA_SIZE; ++j ){

      // 0.0 ~ 1.0までのサイコロを振る
      mute_num = real_Distribution_Fmin( engine );

      // MUTE_RATE以下なら突然変異
      if( mute_num <= MUTE_RATE ){
        // +-20%を探索範囲とする
        temp_Fmin1 = ga_list[ i ]->F_min[ j ];
	temp_Fmin2 = ga_list[ i-1 ]->F_min[ j ];// temp
        //uniform_real_distribution< double > real_Distribution_Fmin_value( ( temp_Fmin1 * 0.8 ), ( temp_Fmin1 * 1.2 ) );
	uniform_real_distribution< double > real_Distribution_Fmin_value( ( temp_Fmin1 ), ( temp_Fmin2 ) );
        ga_list[ i ]->F_min[ j ] = real_Distribution_Fmin_value( engine );
      }

      // 0.0 ~ 1.0までのサイコロを振る
      mute_num = real_Distribution_tau( engine );

      // MUTE_RATE以下なら突然変異
      if( mute_num <= MUTE_RATE ){

        if(j != (MORA_SIZE - 1)){ // 最終音素以外

          // そのtauの範囲内からtau値を割り当てる方式
          temp_tau1 = ga_list[ i ]->tau[ j ];
          uniform_int_distribution< int > int_Distribution_tau_value( 0, search_range );
          temp_1 = int_Distribution_tau_value( engine ) + ( search_range * j );
	  ga_list[ i ]->tau[ j ] = temp_1; 

          // +-20%を探索範囲とする方式 
          /*
          uniform_int_distribution< int > int_Distribution_tau_value( int( temp_tau1 * 0.8 ), int( temp_tau1 * 1.2 ) );
          temp_1 = int_Distribution_tau_value( engine );
          
          if(temp_1 > frame_size - 1){
            ga_list[ i ]->tau[ j ] = frame_size - 1; // ここ要検討
          }else{
            ga_list[ i ]->tau[ j ] = temp_1;
          }
          */

        }else{ // 最終音素のとき、最後の数を超える可能性がある

          // そのtauの範囲内からtau値を割り当てる方式
          temp_tau1 = ga_list[ i ]->tau[ j ];
          uniform_int_distribution< int > int_Distribution_tau_value( 0, search_range );
          temp_1 = int_Distribution_tau_value( engine ) + ( search_range * j );

          if( temp_1 >= frame_size ){ // もしtemp_1がフレーム数以上だったとき
            while( temp_1 >= frame_size ){
              temp_1--; // temp_1をフレーム数以下にする。
            }
          }

          ga_list[ i ]->tau[ j ] = temp_1; 

          /*
          // 最大tau位置から1 ~ 10までの乱数を引いて調整
          temp_tau1 = ga_list[ i ]->tau[ j ];
          uniform_int_distribution< int > int_Distribution_tau_value( int( temp_tau1 * 0.8), frame_size );
          temp_1 = int_Distribution_tau_value( engine ) ;
          ga_list[ i ]->tau[ j ] = temp_1;
          */
        }

      }

    }
  }

}

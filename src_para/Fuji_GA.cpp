/**
 * @file Fuji_GA.cpp
 * @brief 藤崎GAを行うときに必要な関数とパラメータを定義したクラスの実装です。
 * @detail フレーム数とseed値をコンストラクタに渡すとオブジェクトが作られます。
 * @date 2016-10-16
 * @author Akichika HIGA, Tomio Takara
 */

#include "Fuji_GA.hpp" // Fuji_GAクラスの定義

using namespace std;

/** コンストラクタ
 * @param (frame_size) フレーム数
 * @param (seed) seed値
 */
Fuji_GA::Fuji_GA( const int frame_size, const int seed_arg ){

  cout << "##### GA is initializing..." << endl;
  
  seed = seed_arg; // メンバ変数に格納
  //! 探索範囲を格納
  int search_range = frame_size / MORA_SIZE;

  // 仮の構造体を利用して、それをmapに格納していく
  Fuji_Para *param_gene_pointer = NULL; // メモリリーク阻止のためNULL

  int i = 0;
  int j = 0;
  #ifdef _OPENMP
  #pragma omp prallel for private(j, search_range, seed) num_threads(2)
  for(i = 0; i < GA_SIZE; ++i){
    // 乱数生成オブジェクト生成
    mt19937_64 engine( seed + i ); // 乱数を個体ごとに変更するためseed + i
    uniform_real_distribution< double > real_Distribution( -15.0, 15.0 );// F値上限を実数で-15.0 ~ 15.0まで
    uniform_int_distribution< int > int_Distribution( 1, search_range );// tau値探索範囲を整数で1 ~ 15まで

    // Fuji_Para構造体の初期化
    for(j = 0; j < MORA_SIZE; ++j){

      // F値の初期化
      param_gene[ i ].F_min[ j ] = real_Distribution( engine );
      
      // tau値の初期化
      int temp = int_Distribution( engine ) + ( search_range * j ); // 1 ~ 7, 8 ~ 14, ...のように範囲選択 

      // tau値の境界設定
      if( temp > frame_size ){ // frame_sizeより小さくなるまで振りなおす
        while(temp > frame_size){
          temp = int_Distribution( engine ) + ( search_range * j ); // これうまくいくか？
        }

      }else{ // 問題がないときは格納する
        param_gene[ i ].tau[ j ] = temp;
      }
    }

    // fitnessの初期化
    param_gene[ i ].fitness = 0.0;
    param_gene[ i ].fitness_relative = 0.0;

    // Fuji_GAオブジェクトでは関数で値変更をすることが多々あるため、アドレス渡しをする
    param_gene_pointer = &param_gene[ i ];

    // mapに初期化した構造体を渡す
    ga_list[ i ] = param_gene_pointer;
  }
  #endif
}

/** デストラクタ
 * プログラムが正常終了すると表示する。
 */
Fuji_GA::~Fuji_GA(){
  cout << "##### Deleat GA ... bye!" << endl;
}

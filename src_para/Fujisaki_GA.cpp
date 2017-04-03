/**
 * @file Fujisaki_GA.cpp
 * @brief 藤崎GAのmain関数です。
 * @detail 使い方は、まずmakeします。./Fujisaki_GA.exe $seed $trial_times $target_fileです。スクリプトを使うと楽になります。
 * @date 2016-10-16
 * @author Akichika HIGA, Tomio Takara
 */

#include "parameter.h" //! GAパラメータ
#include "Fuji_GA.hpp" //! Fuji_GAクラス

#include <iostream>
#include <fstream>

#include <chrono>

using namespace std; // stdを先頭につける必要がなくなる

/**
 * @fn
 * main関数
 * @brief 最初に動く関数です。
 * @param (argv[1]) seed値
 * @param (argv[2]) 試行世代数
 * @param (argv[3]) ターゲットファイル名
 * @sa Fuji_GA
 * @sa calc_fitness
 * @sa selection
 * @sa crossover
 * @sa mutation
 * @sa sort_ga
 * @sa show_gene
 * @detail ターゲットファイルを正解として、GAによる模倣を行う。模倣の操作はこのファイル内から逐次行われる。
 */
int main(int argc, char const *argv[]){

  //! 引数サイズを固定
  int arg_size = 4;

  // 引数チェック
  if( argc != arg_size ){ // 指定引数サイズでないと異常終了
    cout << "Usage : ./Fujisaki_GA.exe $seed_value $target_file " << endl;
    exit(1);
  }

  // 引数読み込み
  //! seed値を格納
  int seed = stoi( argv[1] );
  //! 試行世代数を格納
  int trial_times = stoi( argv[2] );
  // ファイル名でreading_fileをコンストラクト
  ifstream reading_file( argv[3] );

  // ファイル読み込みチェック
  if( reading_file.fail() ){ // ファイル名が存在しない場合は異常終了
    cout << "Target file Open failer." << endl;
    exit(1);
  }

  // ファイル読み込み開始
  // frame数読み込み
  //! ファイルの1行を格納する
  string str;
  //! frame_sizeを格納する
  int frame_size = 0;
  getline( reading_file, str ); // ファイルから1行をstrに格納
  frame_size = stoi( str ); // strをint化してframe_sizeに格納

  // target読み込み
  //! ターゲットファイルの中身を格納
  double target[ frame_size ]; // targetは0 ~ frame_size-1まで
  for (int i = 0; i < frame_size; ++i){
    getline( reading_file, str );
    target[ i ] = stod( str ); // strの中身をdouble化してtargetに格納
  }

  auto start = chrono::system_clock::now(); //計測開始

    // GA開始
    // Fuji_GAオブジェクト生成
    Fuji_GA *ga;
    ga = new Fuji_GA( frame_size, seed ); // frame_sizeとseedでFuji_GAをコンストラクト

    //#pragma omp parallel
    //{
      //#pragma omp for
      //誤差計算
      for( int i = 0; i < GA_SIZE; ++i){
        ga->calc_fitness( i, frame_size, target ); // ターゲットファイルと生成されたファイルとの1フレーム間誤差を計算
      }
    //}
    
      for (int k = 0; k < trial_times; ++k){
        ga->selection(); // 選択を行う

        ga->crossover(); // 交叉を行う
        ga->mutation( frame_size ); // 突然変異を行う

        for( int i = 0; i < GA_SIZE; ++i){
          ga->calc_fitness( i, frame_size, target ); // 個体集団ソートのための誤差計算
        }
        ga->sort_ga(); // 個体集団を誤差の昇順にソート
      }
    
    //ga->show_gene(); // 個体集団の最終結果を表示する

  auto end = chrono::system_clock::now(); //計測終了
  auto dur = end - start;
  auto msec = chrono::duration_cast<chrono::microseconds>(dur).count();//要した時間をミリ秒(1/1000秒)に変換
  cout << msec << " micro sec" << endl;

  delete ga; // 生成したFuji_GAオブジェクトを消去
  return 0;
}
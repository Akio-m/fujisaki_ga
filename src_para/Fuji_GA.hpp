/**
 * @file Fuji_GA.hpp
 * @brief 藤崎GAを行うときに必要な関数とパラメータを定義したクラスです。
 * @detail フレーム数とseed値をコンストラクタに渡すとオブジェクトが作られます。
 * @date 2016-10-16
 * @author Akichika HIGA, Tomio Takara
 */

// includeガードで多重includeを防止
#ifndef _INCLUDE_Fuji_GA
#define _INCLUDE_Fuji_GA

// includeリスト
#include <algorithm> // ソートするときに必要
#include <iostream> // ioに必要
#include <stdio.h> // 特にいらない？
#include <random> // 乱数生成に必要
#include <vector> // コンテナ(無限配列)を使うために必要
#include <iterator> // コンテナの位置を示すために必要
#include <stdint.h> // 特にいらない？
#include <map> // 辞書を作るときに必要
#include <cmath> // 数学系で必要
#include <math.h> // 数学系で必要

#include <omp.h> // openMPの関数を利用するため

#include "parameter.h" // GAのパラメータ

using namespace std; 

/** @struct Fuji_Para 
 *  @brief 個体が保持するパラメータ群。藤崎モデルを作る際に使用。
 */
typedef struct{
  double F_min[ MORA_SIZE ]; //! 基底の高さ(F値)。ただし、開始前の0番目は含めない。
  int tau[ MORA_SIZE ]; //! 立ち上がり時間(tau値)を格納
  double fitness; //! 適応度を格納
  double fitness_relative; //相対誤差
}Fuji_Para;

/** @class Fuji_GA 
 *  @brief 藤崎GAを行うクラス。
 *  @sa Fuji_GA
 *  @sa ~Fuji_GA
 *  @sa calc_fitness
 *  @sa selection
 *  @sa crossover
 *  @sa mutation
 *  @sa sort_ga
 *  @sa show_gene
 */
class Fuji_GA{
public:
  /** コンストラクタ
   * @param (frame_size) フレーム数
   * @param (seed) seed値
   */
  Fuji_GA( const int frame_size, const int seed );
  ~Fuji_GA();

private:
  Fuji_Para param_gene[ GA_SIZE ]; //! Fuji_Para構造体の配列
  map< int , Fuji_Para* > ga_list; //! Fuji_Para構造体のソートと探索を簡単かつ高速にする(ここが難しいと思う)
  int seed; //! seed値を保存しておく

public:
  void calc_fitness( const int gene_num, const int frame_size, const double *target ); //評価値の計算を行う
  void selection(); //選択を起こす
  void crossover(); //交叉を起こす
  void mutation( const int frame_size ); //突然変異を起こす
  void show_gene(); //個体を見せる
  void show_fitness(); //評価値を見せる
  void sort_ga(); //個体値順にソートする

};

#endif //_INCLUDE_Fuji_GA
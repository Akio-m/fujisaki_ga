/**
 * @file show.cpp
 * @brief Fuji_GAクラスのshow_gene関数とshow_fitness関数の実装。
 * @detail Fuji_GAクラスのshow_gene関数とshow_fitness関数の実装。
 * @date 2016-10-16
 * @author Akichika HIGA, Tomio Takara
 */

#include "Fuji_GA.hpp" // Fuji_GAクラスの定義

using namespace std;

/**
 * @fn
 * show_gene
 * @brief 個体のパラメータを表示する。
 * @detail 個体のパラメータを全て標準出力する。
 */
void Fuji_GA::show_gene(){
  cout << "##### Show GA genes..." << endl;

  for( int i = 0; i < GA_SIZE; ++i ){
  
    for(int j = 0; j < MORA_SIZE; ++j){
      if( j == 0 ){
        cout << "F_min" << endl;
      }
      cout << ga_list[ i ]->F_min[ j ] << endl;
    }

    for(int j = 0; j < MORA_SIZE; ++j){
      if( j == 0 ){
        cout << "tau" << endl;
      }
      cout << ga_list[ i ]->tau[ j ] << endl;
    }

    cout << "ga[" << i << "].fitness = "<< ga_list[ i ]->fitness << endl;
    cout << "ga[" << i << "].fitness_relative = "<< ga_list[ i ]->fitness_relative << endl;
  }

  cout << "End." << endl;
}

/**
 * @fn
 * show_fitness
 * @brief 未実装
 * @detail 未実装
 */
void Fuji_GA::show_fitness(){
  cout << "##### Show GA gene's fitnesses..." << endl;


}
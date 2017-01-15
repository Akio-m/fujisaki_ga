/**
 * @file parameter.h
 * @brief GAのパラメータ。
 * @detail GAに関するパラメータと音声のパラメータのマクロを記述しています。設定を変えるときはここを変えてください。
 * @date 2016-10-16
 * @author Akichika HIGA, Tomio Takara
 */

//音声に関するパラメータ
/** @def
 * 音素長
 */
#define MORA_SIZE 10
 /** @def
 * 角速度
 */
#define BETA 20.0

//GAに関するパラメータ
/** @def
 * 個体集団の数
 */
#define GA_SIZE 100
/** @def
 * エリートコピー率
 * ELITE_COPY * GA_SIZE = 1にしなければならない。
 */
#define ELITE_COPY 0.025
/** @def
 * 突然変異確率
 */
#define MUTE_RATE 0.4

//ランキング戦略の選択確率
/** @def
 * ランキング選択のランク1の選択確率
 */
#define RANK_1 0.4
/** @def
 * ランキング選択のランク2の選択確率
 */
#define RANK_2 0.3
/** @def
 * ランキング選択のランク3の選択確率
 */
#define RANK_3 0.2
/** @def
 * ランキング選択のランク4の選択確率
 */
#define RANK_4 0.07
/** @def
 * ランキング選択のランク5の選択確率
 */
#define RANK_5 0.03

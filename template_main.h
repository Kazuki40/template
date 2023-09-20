#ifndef TEMPLATE_MAIN_H
#define TEMPLATE_MAIN_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>
#include <numeric>
#include <tuple>
#include <array>
#include <iomanip>

// 先定義
template <typename T>
void swap(T &, T &);

// マクロ

// デバック用
#define debug(x) std::cerr << "\033[33m(line:" << __LINE__ << ") " << #x << ": " << x << "\033[m" << std::endl;

// 型定義
#define ULLI unsigned long long int
#define LLD long double

// ループ
#define rep(i, n) for (i = 0; i < n; i++)

// 2次元配列の定義
#define v2_T(T) std::vector<v_T(T)>
// 1次元配列の定義
#define v_T(T) std::vector<T>

// 全て選択
#define v_all(v) (v).begin(), (v).end()

// π(C++20 が使える時は numbers から取得する方がいいい）
#define PI std::acos(-1)

#define write_fixed(n, x) cout << std::fixed << std::setprecision(n) << x << endl // 有効数字

// 行列の表示用関数
template <typename T>
void printMatrix(const std::vector<std::vector<T>> &matrix)
{
	for (const auto &row : matrix)
	{
		for (const auto &val : row)
		{
			std::cout << val << " ";
		}
		std::cout << std::endl;
	}
}

// 関数
// Σ(0からk)x
template <typename T>
T siguma_func_one(T k)
{
	return (k * (k + 1)) / 2;
}
// Σ(0からk)x^2
template <typename T>
T siguma_func_two(T k)
{
	return (k * (k + 1) * (2 * k + 1)) / 6;
}
// Σ(0からk)x^3
template <typename T>
T siguma_func_three(T k)
{
	return powl(siguma_func_one(k), 2);
}

// 積分
// 台形法
template <typename T, typename U, typename Fn>
T integral_trapezoid(Fn func, U min, U max, U n)
{
	T pitch;
	pitch = (max - min) / n;
	T x = min;
	T ans1 = func(x);
	T ans2;
	T ans_re = 0;
	while (x < max)
	{
		x += pitch;
		ans2 = func(x);
		ans_re += ((ans1 / ans2) / (double)2) * pitch;
		ans1 = ans2;
	}
	return ans_re;
}
// MC
template <typename T, typename U, typename Fn>
T integral_rand(Fn func, T min, T max, U n)
{
	T ans = 0;
	U i;
	std::random_device seed1;
	std::uniform_real_distribution<> dist(min, max);
	rep(i, n)
	{
		ans += (func(dist(seed1)));
	}
	return ((max - min) * ans / n);
}
// 長方形法
template <typename T, typename U, typename Fn>
T integral_rectangle(Fn func, T min, T max, U n)
{
	T pitch;
	pitch = (max - min) / n;
	T x = min;
	T ans1;
	T ans_re = 0;
	while (x < max)
	{
		x += (pitch / 2);
		ans1 = func(x);
		ans_re += (ans1 * pitch);
		x += (pitch / 2);
	}
	return ans_re;
}

// 文字列の分割
template <typename T,typename U>
std::vector<T> split(T str, U sep)
{
	ULLI first = 0;
	ULLI last = str.find_first_of(sep); // 最初に現れたデリミタの位置を取得

	typename std::vector<T> result;

	while (first < str.size())
	{
		T subStr(str, first, last - first); // 前から数えて文字の場所まで取り出す

		result.push_back(subStr); // 書き込み

		first = last + 1;					  // 対象の文字から１文字ずらす
		last = str.find_first_of(sep, first); // 次のデリミタまでの長さを取得

		// もし見つからなければ，最後にする
		if (last == std::string::npos)
		{
			last = str.size();
		}
	}

	return result;
}

// ファイル読み込み用
template <typename Fn>
void read_csv_line(std::string filename, char sep, Fn lamde_func)
{

	std::ifstream readcsv(filename, std::ios::in);
	std::string temp_line;
	std::vector<std::string> temp_cell;

	// データの１行
	while (getline(readcsv, temp_line))
	{

		// 分割
		temp_cell = split(temp_line, sep);

		/*
		ラムダ式

		{}(引数)void {処理}
		[]:キャプチャリスト [&] は参照渡し [=} は値渡し [this] はメンバ変数を使う時
		():引数
		->
		void 返り値
		{}:処理
		() 即時実行
		*/

		// 関数の実行
		lamde_func(temp_cell);
	}

	return;
}

// 行列を作成するクラス（標準のみ）
template <typename T>
class make_matrix
{
private:
	ULLI loop_i;
	std::string temp_line;
	std::string temp_cell;
	ULLI data_col;
	ULLI data_row;

public:
	make_matrix();
	v2_T(T) getter_diag(T data_num = 1);		  // 単位行列関数
	v2_T(T) getter_matrix0(T row = 1, T col = 1); // 0の行列関数
};

template <typename T>
make_matrix<T>::make_matrix()
{
	this->loop_i = 0;
	this->temp_line = "";
	this->temp_cell = "";
	this->data_col = 0;
	this->data_row = 0;
};

// 単位行列の作成
template <typename T>
v2_T(T) make_matrix<T>::getter_diag(T data_num)
{
	v2_T(T) ans = this->make_matrix<T>::getter_matrix0(data_num, data_num); // 定義
	rep(loop_i, data_num) ans[loop_i][loop_i] = 1;							// 対角成分を1にする

	return ans;
};

// 全てが0の行列を作成
template <typename T>
v2_T(T) make_matrix<T>::getter_matrix0(T row, T col)
{
	v2_T(T) ans(row, std::vector<T>(col, 0)); // 定義

	return ans;
};

// 行列
template <typename T>
std::vector<std::vector<T>> diag_func(std::vector<T> &data)
{
	unsigned long long int temp = data.size();
	typename std::vector<std::vector<T>> ans(temp, std::vector<T>(temp, 0));

	for (temp = 0; temp < data.size(); temp++)
	{
		ans[temp][temp] = data[temp];
	}
	return ans;
}

// 行列
template <typename T>
std::vector<T> diag_func(std::vector<std::vector<T>> &data)
{
	unsigned long long int temp = data.size();
	typename std::vector<T> ans(temp, 0);

	for (temp = 0; temp < data.size(); temp++)
	{
		ans[temp] = data[temp][temp];
	}
	return ans;
}

// 行列計算
template <typename T>
std::vector<std::vector<T>> matrix_sum_func(std::vector<std::vector<T>> data_a, std::vector<std::vector<T>> data_b)
{
	// 同じかどうか
	if (data_a.size() != data_b.size() || data_a[0].size() != data_b[0].size())
	{
		std::cout << "error" << std::endl;
		exit(-250);
	}

	unsigned long long int temp_i, temp_j;
	// 和
	std::vector<std::vector<T>> ans(data_a.size(), std::vector<T>(data_a[0].size(), 0));

	for (temp_i = 0; temp_i < data_a.size(); temp_i++)
	{
		for (temp_j = 0; temp_j < data_a[0].size(); temp_j++)
		{
			// 和
			ans[temp_i][temp_j] = data_a[temp_i][temp_j] + data_b[temp_i][temp_j];
		}
	}
	return ans;
}

// 行列計算
template <typename T>
std::vector<std::vector<T>> matrix_difference_func(std::vector<std::vector<T>> data_a, std::vector<std::vector<T>> data_b)
{
	// 同じかどうか
	if (data_a.size() != data_b.size() || data_a[0].size() != data_b[0].size())
	{
		std::cout << "error" << std::endl;
		exit(-280);
	}

	unsigned long long int temp_i, temp_j;
	// 差
	std::vector<std::vector<T>> ans(data_a.size(), std::vector<T>(data_a[0].size(), 0));

	for (temp_i = 0; temp_i < data_a.size(); temp_i++)
	{
		for (temp_j = 0; temp_j < data_a[0].size(); temp_j++)
		{
			// 差
			ans[temp_i][temp_j] = data_a[temp_i][temp_j] - data_b[temp_i][temp_j];
		}
	}
	return ans;
}

// 行列計算
template <typename T, typename U>
std::vector<std::vector<T>> matrix_times_func(std::vector<std::vector<T>> data_a, U times)
{
	unsigned long long int temp_i, temp_j;
	// 答え
	std::vector<std::vector<T>> ans(data_a.size(), std::vector<T>(data_a[0].size(), 0));

	//
	for (temp_i = 0; temp_i < data_a.size(); temp_i++)
	{
		for (temp_j = 0; temp_j < data_a[0].size(); temp_j++)
		{
			// 差
			ans[temp_i][temp_j] = times * data_a[temp_i][temp_j];
		}
	}
	return ans;
}

// 行列計算 転置
template <typename T>
void matrix_transposed_func(std::vector<std::vector<T>> &data)
{
	// 正則行列判定
	if (data.size() != data[0].size())
	{
		std::cout << "error" << std::endl;
		exit(-330);
	}

	unsigned long long int temp_i, temp_j;

	// 答え
	for (temp_i = 0; temp_i < data.size(); temp_i++)
	{
		for (temp_j = (temp_i + 1); temp_j < data[0].size(); temp_j++)
		{

			// 入れ替え
			swap(data[temp_i][temp_j], data[temp_j][temp_i]);
		}
	}
	return;
}

// 行列計算
template <typename T>
std::vector<std::vector<T>> matrix_product(std::vector<std::vector<T>> data_a, std::vector<std::vector<T>> data_b)
{
	unsigned long long int temp_am, temp_an, temp_bm, temp_bn;

	// 行列のサイズ
	temp_am = data_a.size();
	temp_an = data_a[0].size();
	temp_bm = data_b.size();
	temp_bn = data_b[0].size();

	// 答えのサイズ
	unsigned long long int temp_ans_m, temp_ans_n;
	temp_ans_m = temp_am;
	temp_ans_n = temp_bn;

	if (temp_an != temp_bm)
	{
		std::cout << "error" << std::endl;
		exit(-372);
	}

	// 答え
	typename std::vector<std::vector<T>> ans(temp_ans_m, std::vector<T>(temp_ans_n, 0));
	unsigned long long int loop_am, loop_bn;

	// 計算

	// 行
	for (loop_am = 0; loop_am < temp_am; loop_am++)
	{

		// 列
		for (loop_bn = 0; loop_bn < temp_bn; loop_bn++)
		{
			// 計算

			for (unsigned long long int temp = 0; temp < temp_an; temp++)
			{
				ans[loop_am][loop_bn] += data_a[loop_am][temp] * data_b[temp][loop_bn];
			}
		}
	}

	return ans;
}

// 行列の計算　逆行列
template <typename T>
std::vector<std::vector<T>> solve_func(std::vector<std::vector<T>> &data)
{
	if (data.size() != data[0].size())
	{
		std::cout << "error" << std::endl;
		exit(-370);
	}

	// 行列の記入
	class make_matrix<T> matrix_e;
	typename std::vector<std::vector<T>> matrix_ans = matrix_e.getter_diag(data.size());
	typename std::vector<std::vector<T>> matrix_data = data;

	// 計算機イプシロンの定義
	LLD data_eps = std::numeric_limits<T>::epsilon();
	unsigned long long int temp_i, temp_j;

	// 全体
	for (unsigned long long int temp_now = 0; temp_now < matrix_data.size(); temp_now++)
	{

		// 0の時は別
		if (abs(matrix_data[temp_now][temp_now]) <= data_eps)
		{
			for (temp_i = temp_now; temp_i < matrix_data.size(); temp_i++)
			{
				if (matrix_data[temp_i][temp_now] != 0)
				{

					for (temp_j = 0; temp_j < matrix_data.size(); temp_j++)
					{

						// 行の入れ替え
						swap(matrix_data[temp_now][temp_j], matrix_data[temp_i][temp_j]);
						// 答えもいれかえ
						swap(matrix_ans[temp_now][temp_j], matrix_ans[temp_i][temp_j]);
					}
					break;
				}
			}
		}

		// 計算
		// 1行目を1にする
		// 仮変数
		long double temp_now_data;

		temp_now_data = matrix_data[temp_now][temp_now];
		for (temp_i = 0; temp_i < matrix_data[temp_now].size(); temp_i++)
		{
			matrix_data[temp_now][temp_i] /= temp_now_data;
			matrix_ans[temp_now][temp_i] /= temp_now_data;
		}

		// 2行目移行の計算
		for (temp_i = 0; temp_i < matrix_data.size(); temp_i++)
		{
			if (temp_i != temp_now)
			{
				// 2列目（定数倍の定義）
				temp_now_data = matrix_data[temp_i][temp_now];
				for (temp_j = 0; temp_j < matrix_data[0].size(); temp_j++)
				{
					// 答え
					// 定数倍 ×　値　
					matrix_ans[temp_i][temp_j] -= temp_now_data * matrix_ans[temp_now][temp_j];
					matrix_data[temp_i][temp_j] -= temp_now_data * matrix_data[temp_now][temp_j];
				}
			}
		}
	}

	return matrix_ans;
}

//  csvファイルを読み込むクラス
class read_csv
{
private:
	bool the_first_line;
	ULLI temp_cell_num;
	std::string temp_line, temp_cell;

public:
	read_csv();

	void setter(std::string file = "a.csv", bool header = true, char sep = ',', short row_name = 0);
	std::unordered_map<std::string, ULLI> getter_hearder_name();
	std::unordered_map<std::string, ULLI> getter_row_name();
	v2_T(std::string) getter_data_matrix();

protected:
	std::unordered_map<std::string, ULLI> hearder_name;
	std::unordered_map<std::string, ULLI> row_name;
	v2_T(std::string) data_matrix;
	void function(std::string &, bool &, char &, short &);
};

read_csv::read_csv()
{
	this->temp_cell_num = 0;
	this->temp_line = "";
	this->temp_cell = "";
	this->the_first_line = false;
}

void read_csv::setter(std::string file, bool header, char sep, short row_name_num)
{
	this->function(file, header, sep, row_name_num);
	return;
}

// ゲッター
std::unordered_map<std::string, ULLI> read_csv::getter_hearder_name()
{
	return this->hearder_name;
}

std::unordered_map<std::string, ULLI> read_csv::getter_row_name()
{
	return this->row_name;
}

v2_T(std::string) read_csv::getter_data_matrix()
{
	return this->data_matrix;
}

void read_csv::function(std::string &file, bool &header, char &sep, short &row_name_num)
{
	// ファイルを開く
	std::ifstream read_csv_file(file, std::ios::in);

	// エラーの時の処理
	if (!read_csv_file.is_open())
	{
		std::cout << "Failed to open the csv file. Please check the file name and try again.\n";
		return;
	}

	// １行目の処理
	this->the_first_line = true;

	// ループ
	while (getline(read_csv_file, this->temp_line))
	{
		// 変数定義
		// 格納するデータ
		v_T(std::string) temp_data;

		// 文字列を分割する
		std::stringstream split(this->temp_line);

		// 0列目の処理
		this->temp_cell_num = 0;

		// 列の処理
		while (getline(split, this->temp_cell, sep))
		{
			// 不要な記号を削除
			if (this->temp_cell.at(0) == '\"')
			{
				this->temp_cell.pop_back();						// 最後の1文字を削除
				this->temp_cell.erase(this->temp_cell.begin()); // 1文字目を削除
			}

			// 1行目の時の処理
			if ((the_first_line == true) && (header == true))
			{
				// ヘッダーの名前と番号を格納
				this->hearder_name.emplace(temp_cell, temp_cell_num);
			}
			else
			{
				// 1列目が名前の時かつ今１列目の時の処理
				if ((row_name_num == 1) && (temp_cell_num == 0))
				{
					// 1列目が名前の時の処理
					row_name.emplace(temp_cell, row_name.size());
				}
				else
				{
					// データを導入
					temp_data.push_back(temp_cell);
				}
			}

			// 列番号を増やす
			temp_cell_num++;
		}

		// ヘッダーがある

		if (!((header == true) && (the_first_line == true)))
		{
			// データを格納
			this->data_matrix.push_back(temp_data);
		}

		the_first_line = false;
	}
	return;
};

// csvファイルを書き込む関数
// オーバーロード
// データのみ
template <typename T>
void write_csv(v2_T(T) data, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{
	// ファイル出力
	std::ofstream write(filename, mode);
	ULLI row, col; // 仮変数

	// ループ
	rep(row, data.size())
	{
		// ループ
		rep(col, ((data[0].size()) - 1))
		{
			// 書き込み
			write << data[row][col] << sep;
		}
		// 最後の列の処理
		write << data[row][((data.size()) - 1)] << std::endl;
	}

	return;
}

// ヘッダーとデータ
template <typename T, typename U>
void write_csv(v2_T(T) data, std::unordered_map<std::string, ULLI> hearder_name, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{
	// ヘッダーの名前を格納するイテレータ
	std::unordered_map<std::string, ULLI>::iterator hearder_iter;
	hearder_iter = hearder_name.begin();

	// ファイル
	std::ofstream write(filename, mode);
	ULLI now_cell_num = 0;

	// ヘッダーの名前を書き込む
	while (hearder_iter != hearder_name.end())
	{
		// 書き込み
		write << hearder_iter->first;

		// 最後の列の処理など
		if (now_cell_num == (hearder_name.size() - 1))
		{
			write << std::endl;
		}
		else
		{
			write << sep;
		}
		// 値を更新
		now_cell_num++;
		hearder_iter++;
	}

	// 以降は同じ
	write_csv(data, filename, std::ios::ate, sep);

	return;
}

// データと行名の時
template <typename T>
void write_csv(v2_T(T) data, std::unordered_map<std::string, ULLI> row_name, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{
	// イテレータ
	std::unordered_map<std::string, ULLI>::iterator row_name_iter;
	row_name_iter = row_name.begin();

	// 出力ファイルの定義
	std::ofstream write(filename, mode);
	ULLI row, col;

	rep(row, data.size())
	{
		// １列目がrow_nameの時の処理
		write << row_name_iter->first << sep;

		// データの書き込み
		rep(col, ((data.size()) - 1))
		{
			// 出力
			write << data[row][col] << sep;
		}
		// 最後の列の処理
		write << data[row][((data.size()) - 1)] << std::endl;
		row_name_iter++;
	}

	return;
}

// ヘッダー，行名，データがあるとき
template <typename T>
void write_csv(v2_T(T) data, std::unordered_map<std::string, ULLI> hearder_name, std::unordered_map<std::string, ULLI> row_name, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{
	// ヘッダーの名前を格納するイテレータ
	std::unordered_map<std::string, ULLI>::iterator hearder_iter;
	hearder_iter = hearder_name.begin();

	// 出力ファイルの定義
	std::ofstream write(filename, mode);
	ULLI now_cell_num = 0;

	// ヘッダーの書き込み
	while (hearder_iter != hearder_name.end())
	{
		// 書き込み
		write << hearder_iter->first;

		// 文字の判定
		if (now_cell_num == (hearder_name.size() - 1))
		{
			write << std::endl;
		}
		else
		{
			write << sep;
		}
		// 更新
		now_cell_num++;
		hearder_iter++;
	}

	// ヘッダーは書いたのでそれ以外の処理
	write_csv(data, row_name, filename, std::ios::ate, sep);

	return;
}

// マップの時
template <typename T, typename U>
void write_csv(std::unordered_map<T, U> &ans_map, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{

	// ファイル出力
	std::ofstream write(filename, mode);
	typename std::unordered_map<T, U>::iterator map_iter;
	map_iter = ans_map.begin();

	while (map_iter != ans_map.end())
	{
		// 出力
		write << map_iter->first << sep << map_iter->second << std::endl;

		// 更新
		map_iter++;
	}

	return;
}

template <typename T, typename U>
void write_csv(std::unordered_map<T, std::vector<U>> ans_map, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{

	// ファイル出力
	std::ofstream write(filename, mode);

	typename std::unordered_map<T, std::vector<U>>::iterator map_iter;
	map_iter = ans_map.begin();

	typename std::vector<U>::iterator vec_iter;

	while (map_iter != ans_map.end())
	{
		// debug(map_iter->first)
		// 出力
		vec_iter = map_iter->second.begin();

		write << map_iter->first;

		while (vec_iter != map_iter->second.end())
		{
			// 出力
			write << sep << *vec_iter;

			// 更新
			vec_iter++;
		}

		write << std::endl;
		// 更新
		map_iter++;
	}

	return;
}

// ファウル出力　ベクトル
template <typename T>
void write_csv(std::vector<T> &data, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{

	// ファイル出力
	std::ofstream write(filename, mode);

	typename std::vector<T>::iterator vec_iter;

	for (vec_iter = data.begin(); vec_iter != data.end(); ++vec_iter)
	{
		if (vec_iter != data.begin())
		{
			write << sep;
		}
		write << *vec_iter;
	}

	write << std::endl;

	return;
}

// 曜日の計算（ツェラーの公式）
int day_of_the_week(int year = 0000, int month = 1, int day = 1)
{
	// 1月と2月は前年の13月と14月として計算する
	if (month == 1 || month == 2)
	{
		year--;
		month += 12;
	}
	return (year + year / 4 - year / 100 + year / 400 + (13 * month + 8) / 5 + day) % 7;
}

// うるう年判定
bool is_leap_year(int year)
{
	if (year % 400 == 0)
	{
		return true;
	}
	else if (year % 100 == 0)
	{
		return false;
	}
	else if (year % 4 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// yyyy/mm/ddのA日からB日まで日付をマップとして返す
// A日からB日までの経過日数を計算する
std::unordered_map<std::string, ULLI> day_map_age(int start_year, int start_month, int start_day, int end_year, int end_month, int end_day, char sep = '/')
{

	// 答えの定義
	std::unordered_map<std::string, ULLI> day_map;

	int now_year, now_month, now_day, long_days;
	long_days = 0;

	// 年のループ
	for (now_year = start_year; now_year <= end_year; ++now_year)
	{

		// 終了する曜日の定義
		int month_limit;
		if (now_year < end_year)
		{

			// 基本的には年末まで
			month_limit = 12;
		}
		else
		{

			// 最終年のみ月が終わる日が異なる
			month_limit = end_month;
		}

		// 月のループ
		for (now_month = 1; now_month <= month_limit; ++now_month)
		{

			// 最終の日付の判定
			int day_limit;
			if (now_year < end_year || now_month < end_month)
			{

				// 最終日の判定
				// うるう年判定
				if (now_month == 2)
				{

					// うるう年判定は上の式
					if (is_leap_year(now_year))
					{
						day_limit = 29;
					}
					else
					{
						day_limit = 28;
					}
				}
				// 30日の月のみ抽出
				else if (now_month == 4 || now_month == 6 || now_month == 9 || now_month == 11)
				{
					day_limit = 30;
				}
				else
				{
					day_limit = 31;
				}
			}
			else
			{
				// 最終年かつ最終日のみ異なる
				day_limit = end_day;
			}

			// 日付のループ
			for (now_day = 1; now_day <= day_limit; ++now_day)
			{
				// create the date string in format yyyy/mm/dd
				std::ostringstream string_year, string_month, string_day;

				string_year << std::setfill('0') << std::setw(4) << now_year;
				string_month << std::setfill('0') << std::setw(2) << now_month;
				string_day << std::setfill('0') << std::setw(2) << now_day;


				std::string date = string_year.str() + sep + string_month.str() + sep + string_day.str();
				// increment long_days and add to map
				day_map[date] = long_days;
				++long_days;
			}
		}
	}

	// 答えを返す
	return day_map;
}

//(T) year, (T) month, (T) dayを yyyy/mm/dd の形式に変換する
template <typename T>
std::string T_to_date_trans_func(T &year, T &month, T &day, char sep = '/')
{
	std::string ans;
	ans = std::to_string(year) + sep + std::to_string(month) + sep + std::to_string(day);

	return ans;
}

// yyyy/mm/dd の形式を (int) year, (int) month, (int) day に変換する
class date_to_int
{
public:
	date_to_int();
	int year;
	int month;
	int day;
	void function(std::string, char sep = '/');
};

date_to_int::date_to_int()
{
	this->year = 0;
	this->month = 0;
	this->day = 0;
}

void date_to_int::function(std::string date_s, char sep)
{
	// 日付の分割
	std::vector<std::string> date_split = split(date_s, '/');

	// 日付の変換
	year = std::stoi(date_split[0]);
	month = std::stoi(date_split[1]);
	day = std::stoi(date_split[2]);

	return;
}

// スワップ
template <typename T>
void swap(T &a, T &b)
{ // 返り値がないからポインターなどでする必要がある
	// 一時変数
	T temp = a;

	// 入れ替え
	a = b;
	b = temp;
	return;
}

// 小さいデータの比較
template <typename T>
bool data_comparison(T &data_x, T &data_y)
{

	// 計算機イプシロンの定義
	LLD data_eps = std::numeric_limits<T>::epsilon();

	// 2つのデータの差がeps以下ならばtrueを返す
	if (std::abs(data_x - data_y) < data_eps)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// データの基本統計量を算出
template <typename T>
class data_statistics
{
private:
	LLD mode = -1;
	ULLI max_count = 0;
	std::unordered_map<T, ULLI> data_map;

public:
	data_statistics();
	void setter(v_T(T) & data);
	LLD get_max();
	LLD get_min();
	LLD get_mean();
	LLD get_median();
	LLD get_mode();
	LLD get_variance();
	LLD get_sd();
	LLD get_sum();

protected:
	void function(v_T(T) data);
	LLD max_value, min_value, mean_value, median_value, mode_value, variance_value, sd_value, sum_value;
};

template <typename T>
data_statistics<T>::data_statistics()
{
	this->max_value = 0;
	this->min_value = 0;
	this->mean_value = 0;
	this->median_value = 0;
	this->mode_value = 0;
	this->variance_value = 0;
	this->sd_value = 0;
	this->sum_value = 0;
}

template <typename T>
void data_statistics<T>::setter(v_T(T) & data)
{
	// コンストラクタの中身
	function(data);
};

template <typename T>
void data_statistics<T>::function(v_T(T) data)
{
	sum_value = fast_sum(data);
	max_value = std::max_element(v_all(data));
	min_value = std::min_element(v_all(data));
	this->mean_value = sum_value / data.size();

	// 分散の計算
	//  最初1　最後1　最初2　初期値
	auto variance_func1 = [this](LLD acc, LLD a)
	{
		return (acc + std::pow(a - this->mean_value, 2));
	};

	variance_value = std::accumulate(data.begin(), data.end(), 0.0, variance_func1) / data.size();

	// 標準偏差の計算
	sd_value = std::sqrt(variance_value);

	// 中央値
	std::sort(data); // ソートをする
	median_value = ((data.size() % 2 == 0) ? (data[data.size() / 2 - 1] + data[data.size() / 2]) / 2 : data[data.size() / 2]);

	// 最頻値
	for (auto itr = data.begin(); itr != data.end(); ++itr)
	{
		data_map[*itr]++;
	}

	// Find the mode by looping through the map
	for (const auto &kv : data_map)
	{
		if (kv.second > max_count)
		{
			max_count = kv.second;
			mode = kv.first;
		}
	}
	mode_value = mode;
	return;
};

// 出力
template <typename T>
LLD data_statistics<T>::get_max()
{
	return max_value;
};
template <typename T>
LLD data_statistics<T>::get_min()
{
	return min_value;
};
template <typename T>
LLD data_statistics<T>::get_mean()
{
	return mean_value;
};
template <typename T>
LLD data_statistics<T>::get_median()
{
	return median_value;
};
template <typename T>
LLD data_statistics<T>::get_mode()
{
	return mode_value;
};
template <typename T>
LLD data_statistics<T>::get_variance()
{
	return variance_value;
};
template <typename T>
LLD data_statistics<T>::get_sd()
{
	return sd_value;
};
template <typename T>
LLD data_statistics<T>::get_sum()
{
	return sum_value;
};

// データの基本統計量を算出（行列用）
template <typename T>
class data_statistics_vector : protected data_statistics<std::vector<T>>
{

private:
	ULLI now_temp, now_col;
	v_T(T) now_data;

public:
	void setter(v2_T(T) datas);
	v_T(LLD) get_max();
	v_T(LLD) get_min();
	v_T(LLD) get_mean();
	v_T(LLD) get_median();
	v_T(LLD) get_mode();
	v_T(LLD) get_variance();
	v_T(LLD) get_sd();
	v_T(LLD) get_sum();

protected:
	data_statistics_vector();
	v_T(LLD) max_vector, min_vector, mean_vector, median_vector, mode_vector, variance_vector, sd_vector, sum_vector;
};

template <typename T>
data_statistics_vector<T>::data_statistics_vector() : data_statistics<std::vector<T>>()
{
	this->now_temp = 0;
	this->now_col = 0;
	this->max_vector = {};
	this->min_vector = {};
	this->mean_vector = {};
	this->median_vector = {};
	this->mode_vector = {};
	this->variance_vector = {};
	this->sd_vector = {};
	this->sum_vector = {};
}

template <typename T>
void data_statistics_vector<T>::setter(v2_T(T) datas)
{

	// 列数を取得

	rep(now_temp, datas[0].size())
	{
		now_data.resize(datas.size());

		// 分析データのみ取得　列固定
		rep(now_col, datas.size())
		{
			now_data[now_col] = datas[now_col][now_temp];
		}

		// データの基本統計量を算出
		data_statistics<T>::function(now_data);

		// 答えを格納
		max_vector.push_back(data_statistics<T>::max_value);
		min_vector.push_back(data_statistics<T>::min_value);
		mean_vector.push_back(data_statistics<T>::mean_value);
		median_vector.push_back(data_statistics<T>::median_value);
		mode_vector.push_back(data_statistics<T>::mode_value);
		variance_vector.push_back(data_statistics<T>::variance_value);
		sd_vector.push_back(data_statistics<T>::sd_value);
		sum_vector.push_back(data_statistics<T>::sum_value);
	}

	return;
}

// 出力
template <typename T>
v_T(LLD) data_statistics_vector<T>::get_max()
{
	return max_vector;
};
template <typename T>
v_T(LLD) data_statistics_vector<T>::get_min()
{
	return min_vector;
};
template <typename T>
v_T(LLD) data_statistics_vector<T>::get_mean()
{
	return mean_vector;
};
template <typename T>
v_T(LLD) data_statistics_vector<T>::get_median()
{
	return median_vector;
};
template <typename T>
v_T(LLD) data_statistics_vector<T>::get_mode()
{
	return mode_vector;
};
template <typename T>
v_T(LLD) data_statistics_vector<T>::get_variance()
{
	return variance_vector;
};
template <typename T>
v_T(LLD) data_statistics_vector<T>::get_sd()
{
	return sd_vector;
};
template <typename T>
v_T(LLD) data_statistics_vector<T>::get_sum()
{
	return sum_vector;
};

// テキストファイルにカンマを入れる
template<typename T>
void text_comma(T filename = "a.txt", T byte_file = "byte.csv", T output_file = "a.csv")
{
	std::cout << "byteなどが書かれたcsv は，　項目,文字数, バイト数　で記入して\n";
	v2_T(std::string) byte_data;

	// csv読み込む用
	class read_csv read_csv1;
	read_csv1.setter(byte_file, true, ',', 1);

	// テキストファイルを読み込み
	std::ifstream read_txt(filename, std::ios::in);

	if (!read_txt.is_open())
	{
		std::cout << "Failed to open the text file. Please check the file name and try again.\n";
		return;
	}

	// 出力ファイルの定義
	std::ofstream write_csv(output_file, std::ios::out);

	// 仮変数
	std::string temp_line;
	std::string temp_ans;
	ULLI csv_length;
	std::vector<std::vector<std::string>> data = read_csv1.getter_data_matrix();

	while (getline(read_txt, temp_line))
	{

		temp_ans = "";
		rep(csv_length, data.size())
		{
			// 文字の操作
			// substr　（開始位置-1（0スタート），文字数）
			temp_ans += temp_line.substr(std::stoull(data[csv_length][0]) - 1, std::stoull(data[csv_length][1])) + ",";
		}
		// カンマが1つ多いので削除
		temp_ans.pop_back();
		write_csv << temp_ans << "\n";
	}

	return;
}

// 日付の型をそろえる
template<typename T>T remove_zero_form_date(T &date, char sep = '/')
{
	// 日付の共通化
	typename std::vector<T> date_int = split(date, sep);
	int now_y = std::stoi(date_int[0]);
	int now_m = std::stoi(date_int[1]);
	int now_d = std::stoi(date_int[2]);
	T now_date = T_to_date_trans_func(now_y, now_m, now_d, sep);
	return now_date;
}

// 二分木探索
template <typename T, typename Fn>
T binary_search_tree(T &data_a, T &data_b, Fn &func)
{

	T mean = (data_a + data_b) / 2.0;

	if (data_comparison(data_a, data_b))
	{
		return mean;
	}

	T ans;

	T ans_a = func(data_a);
	T ans_b = func(data_b);

	if (ans_a < ans_b)
	{
		ans = binary_search_tree(data_a, mean, func);
	}
	else
	{
		ans = binary_search_tree(data_b, mean, func);
	}

	return ans;
}

// 二分木探索(配列)
template <typename T, typename U, typename Fn>
U binary_search_tree(std::vector<T> &data_v, U data_a, U data_b, Fn &func)
{

	U ans;
	T ans_a = func(data_a);
	T ans_b = func(data_b);

	if (abs(data_a - data_b) == 1)
	{

		ans = (ans_a < ans_b) ? data_a : data_b;

		return ans;
	}

	U ans_now = (data_a + data_b) / 2;

	if (ans_a < ans_b)
	{

		ans = binary_search_tree(data_v, data_a, ans_now, func);
	}
	else
	{

		ans = binary_search_tree(data_v, ans_now, data_b, func);
	}

	return ans;
}

// log sum exp
template <typename T>
T log_sum_exp(std::vector<T> data)
{
	// 最大値を取得
	T max_value = *std::max_element(data.begin(), data.end());
	T sum = 0;

	// 最大値を引いて，expをとる
	for (T value : data)
	{
		sum += std::exp(value - max_value);
	}

	// logをとる
	return max_value + std::log(sum);
}

// 全て足す
template <typename T>
T sum(std::vector<T> data)
{

	std::sort(data.begin(), data.end());

	T ans;
	ans = std::accumulate(data.begin(), data.end(), (T)0);

	return ans;
}

template <typename T>
T fast_sum(std::vector<T> data)
{

	T ans;
	ans = std::reduce(data.begin(), data.end(), (T)0);

	return ans;
}

// 全てかける
template <typename T>
T product(std::vector<T> data)
{

	T ans;
	ans = std::accumulate(data.begin(), data.end(), (T)1, std::multiplies<T>());

	return ans;
}
template <typename T>
T fast_product(std::vector<T> data)
{
	T ans;
	ans = std::reduce(data.begin(), data.end(), (T)1, std::multiplies<T>());
	return ans;
}

// データの条件抽出
template <typename T>
std::vector<T> condition_extraction(std::vector<T> data, T conditions)
{
	typename std::vector<T>::iterator data_iter;
	typename std::vector<T> ans;

	for (data_iter = data.begin(); data_iter != data.end(); data_iter++)
	{
		if (*data_iter == conditions)
		{
			ans.push_back(*data_iter);
		}
	}
	return ans;
}

// データの条件抽出 配列
template <typename T>
std::vector<T> condition_extraction(std::vector<T> data, std::vector<T> conditions)
{
	typename std::vector<T>::iterator data_iter;
	typename std::vector<T>::iterator conditions_iter;
	typename std::vector<T> ans;

	if (conditions.size() == 0)
	{
		std::cout << "条件の数が0です\n"
				  << std::endl;
		exit(-1097);
	}

	for (data_iter = data.begin(); data_iter != data.end(); data_iter++)
	{
		for (conditions_iter = conditions.begin(); conditions_iter != conditions.end(); conditions_iter++)
		{
			if (*data_iter == *conditions_iter)
			{
				ans.push_back(*data_iter);
			}
		}
	}
	return ans;
}

// データの条件抽出
template <typename T, typename... Args>
std::vector<T> condition_extraction(std::vector<T> data, Args... args)
{
	typename std::vector<T> ans;
	typename std::vector<T> conditions = {args...};

	ans = condition_extraction(data, conditions);

	return ans;
}

// 多次元
template <typename T, typename... Args>
std::vector<std::vector<T>> condition_extraction(std::vector<std::vector<T>> data, Args... args)
{
	std::tuple<Args...> conditions = std::make_tuple(args...);
	std::vector<std::vector<T>> result;

	for (const auto &row : data)
	{
		bool satisfiesConditions = true;

		// もとの形
		//   std::make_tuple([](const std::string& s) { return s == "A" || s == "B"; }, 2),

		// std::applyを使用して、各タプルの要素に対してラムダを適用
		std::apply([&](auto &&...condition)
				   {
			// 各条件と対応する列のインデックスを展開

			//get<0>は条件式
			//get<1> は対象のセル
			//row [get<1>]でアクセス　const std::string& s
			//（）の部分でラムダ式の引数を指定

			//Ture＆＆（判定） どちらもture の時のみTureを返す

			((satisfiesConditions = satisfiesConditions && std::get<0>(condition)(row[std::get<1>(condition)])), ...); },
				   conditions); // 2つめ　セルを返す

		if (satisfiesConditions)
		{
			result.push_back(row);
		}
	}

	return result;
}

// １行ごとに判定
template <typename... Args>
bool condition_extraction(std::string data, char sep, Args... args)
{
	std::vector<std::string> temp_data = split(data, sep);
	std::tuple<Args...> conditions = std::make_tuple(args...);

	// 判定
	bool satisfiesConditions = true;

	// 関数　引数（タプル型）
	std::apply([&](auto &&...condition)
			   { ((satisfiesConditions = satisfiesConditions && std::get<0>(condition)(temp_data[std::get<1>(condition)])), ...); },
			   conditions);

	return satisfiesConditions;
}

// 出力
// 0の時
template <typename T>
void print()
{
	std::cout << std::endl;
};
// 1つ以上の時
template <typename T, typename... Args>
void print(T &output, Args... args)
{
	std::cout << output << " ";
	print(args...);

	return;
}

// 連立方程式を解く
template <typename T>
std::vector<T> simultaneous_equation(std::vector<std::vector<T>> &data, std::vector<T> &data_ans)
{
	if (data.size() != data_ans.size())
	{
		std::cout << "error" << std::endl;
		exit(-1593);
	}

	// 行列の記入
	typename std::vector<std::vector<T>> matrix_data = data;
	typename std::vector<T> ans = data_ans;

	// 計算機イプシロンの定義
	LLD data_eps = std::numeric_limits<T>::epsilon();
	unsigned long long int temp_i, temp_j;

	// 全体
	for (unsigned long long int temp_now = 0; temp_now < matrix_data.size(); temp_now++)
	{

		// 0の時は別
		if (abs(matrix_data[temp_now][temp_now]) <= data_eps)
		{
			for (temp_i = temp_now; temp_i < matrix_data.size(); temp_i++)
			{
				if (matrix_data[temp_i][temp_now] != 0)
				{

					for (temp_j = 0; temp_j < matrix_data.size(); temp_j++)
					{

						// 行の入れ替え
						swap(matrix_data[temp_now][temp_j], matrix_data[temp_i][temp_j]);
					}

					// 答えもいれかえ
					swap(ans[temp_now], ans[temp_i]);
					break;
				}
			}
		}

		// 計算
		// 1行目を1にする
		// 仮変数
		long double temp_now_data;

		temp_now_data = matrix_data[temp_now][temp_now];
		for (temp_i = 0; temp_i < matrix_data[temp_now].size(); temp_i++)
		{
			matrix_data[temp_now][temp_i] /= temp_now_data;
		}
		ans[temp_now] /= temp_now_data;

		// 2行目移行の計算
		for (temp_i = 0; temp_i < matrix_data.size(); temp_i++)
		{
			if (temp_i != temp_now)
			{
				// 2列目（定数倍の定義）
				temp_now_data = matrix_data[temp_i][temp_now];
				for (temp_j = 0; temp_j < matrix_data[0].size(); temp_j++)
				{

					// 定数倍 ×　値　
					matrix_data[temp_i][temp_j] -= temp_now_data * matrix_data[temp_now][temp_j];
				}
				// 答え
				ans[temp_i] -= temp_now_data * ans[temp_now];
			}
		}
	}

	return ans;
}

// 固有値を求める2×2
template <typename T>
T det_func2(std::vector<std::vector<T>> &data)
{

	// 判定
	if (data.size() != 2)
	{
		std::cout << "error" << std::endl;
		exit(-1667);
	}

	if (data[0].size() != 2)
	{
		std::cout << "error" << std::endl;
		exit(-1672);
	}

	T ans;

	ans = data[0][0] * data[1][1] - data[0][1] * data[1][0];

	return ans;
}

// 固有値を求める
template <typename T>
T det_func(std::vector<std::vector<T>> &data)
{
	T ans = 0;
	unsigned long long int temp_i, temp_j, temp;

	if (data.size() == 2)
	{
		ans = det_func2(data);
		return ans;
	}
	else
	{

		// 判定
		for (temp = 0; temp < data.size(); temp++)
		{
			typename std::vector<std::vector<T>> data_next;

			// 余因子
			for (temp_i = 1; temp_i < data.size(); temp_i++)
			{

				typename std::vector<T> data_next_temp;
				// 行
				for (temp_j = 0; temp_j < data.size(); temp_j++)
				{

					if (temp_j != temp)
					{
						data_next_temp.push_back(data[temp_i][temp_j]);
					}
				}
				data_next.push_back(data_next_temp);
			}

			ans += std::pow(-1, temp) * data[0][temp] * det_func(data_next);
		}
	}

	return ans;
}




#endif // !TEMPLATE_MAIN_H

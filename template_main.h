#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include<cmath>
#include <numeric>
#include<algorithm>

//マクロ

//デバック用
#define debug(x) std::cerr << "\033[33m(line:" << __LINE__ << ") " << #x << ": " << x << "\033[m" << std::endl;

//型定義
#define ULLI unsigned long long int
#define LLD long double

//ループ
#define rep(i, n) for (i = 0; i < n; i++)

//2次元配列の定義
#define v2_T(T) std::vector<v_T(T)>
//1次元配列の定義
#define v_T(T) std::vector<T>

//全て選択
#define v_all(v) (v).begin(), (v).end()

//π(C++20 が使える時は numbers から取得する方がいいい）
#define PI std::acos(-1) 

//文字列の分割
std::vector<std::string> split(std::string str, char sep) {
	ULLI first = 0;
	ULLI last = str.find_first_of(sep); // 最初に現れたデリミタの位置を取得

	std::vector<std::string> result;

	while (first < str.size()) {
		std::string subStr(str, first, last - first);//前から数えて文字の場所まで取り出す

		result.push_back(subStr);//書き込み

		first = last + 1;//　対象の文字から１文字ずらす
		last = str.find_first_of(sep, first);// 次のデリミタまでの長さを取得

		//もし見つからなければ，最後にする
		if (last == std::string::npos) {
			last = str.size();
		}
	}

	return result;
}


//ファイル読み込み用
template <typename Fn>void read_csv_line(std::string filename, char sep, Fn lamde_func) {

	std::ifstream read_csv(filename, std::ios::in);
	std::string temp_line;
	std::vector<std::string> temp_cell;

	//データの１行
	while (getline(read_csv, temp_line)) {

		//分割
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

		//関数の実行
		lamde_func(temp_cell);

	}

	return;
}



//行列を作成するクラス（標準のみ）
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
	v2_T(T) diag(T data_num = 1);//単位行列関数
	v2_T(T) matrix0(T row = 1, T col = 1);//0の行列関数
};

//単位行列の作成
template <typename T>
v2_T(T) make_matrix<T>::diag(T data_num)
{
	v2_T(T) ans = make_matrix(data_num, data_num);//定義
	rep(loop_i, data_num) ans[loop_i][loop_i] = 1;//対角成分を1にする

	return ans;
};

//全てが0の行列を作成
template <typename T>
v2_T(T) make_matrix<T>::matrix0(T row, T col)
{
	v2_T(T) ans(row, std::vector<T>(col, 0));//定義

	return ans;
};

//csvファイルを読み込むクラス
class read_csv
{
private:
	bool the_first_line;
	ULLI temp_cell_num;
	std::string temp_line, temp_cell;

public:
	read_csv();
	~read_csv();
	std::unordered_map<std::string, ULLI> hearder_name;
	std::unordered_map<std::string, ULLI> row_name;
	v2_T(std::string) data_matrix;
	void function(std::string file = "a.csv", bool header = true, char  sep = ',', short row_name = 0);
};

read_csv::read_csv() {

	this->temp_cell_num = 0;
	this->temp_line = "";
	this->temp_cell = "";
	this->the_first_line = false;
}

read_csv::~read_csv() {

	std::cout << "削除" << std::endl;

}
void read_csv::function(std::string file, bool header, char sep, short row_name_num)
{
	//ファイルを開く
	std::ifstream read_csv_file(file, std::ios::in);

	//エラーの時の処理
	if (!read_csv_file.is_open()) {
		std::cout << "Failed to open the csv file. Please check the file name and try again.\n";
		return;
	}

	//１行目の処理
	this->the_first_line = true;

	//ループ
	while (getline(read_csv_file, temp_line))
	{
		//変数定義
		//格納するデータ
		v_T(std::string) temp_data;

		//文字列を分割する
		std::stringstream split(temp_line);

		//0列目の処理
		temp_cell_num = 0;

		//列の処理
		while (getline(split, temp_cell, sep))
		{
			// 不要な記号を削除
			if (temp_cell.at(0) == '\"')
			{
				temp_cell.pop_back();//最後の1文字を削除
				temp_cell.erase(temp_cell.begin());//1文字目を削除
			}

			//1行目の時の処理
			if ((the_first_line == true) && (header == true))
			{
				//ヘッダーの名前と番号を格納
				hearder_name.emplace(temp_cell, temp_cell_num);
			}
			else
			{
				//1列目が名前の時かつ今１列目の時の処理
				if ((row_name_num == 1) && (temp_cell_num == 0))
				{
					//1列目が名前の時の処理
					row_name.emplace(temp_cell, row_name.size());
				}
				else
				{
					//データを導入
					temp_data.push_back(temp_cell);
				}
			}

			//列番号を増やす
			temp_cell_num++;
		}

		//ヘッダーがある

		if (!((header == true) && (the_first_line == true))) {
			//データを格納
			data_matrix.push_back(temp_data);

		}

		the_first_line = false;

	}
	return;
};

//csvファイルを書き込む関数
//オーバーロード
//データのみ
template <typename T>
void write_csv(v2_T(T) data, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{
	//ファイル出力
	std::ofstream write(filename, mode);
	ULLI row, col;//仮変数

	//ループ
	rep(row, data.size())
	{
		//ループ
		rep(col, ((data.size()) - 1))
		{
			//書き込み
			write << data[row][col] << sep;
		}
		//最後の列の処理
		write << data[row][((data.size()) - 1)] << std::endl;
	}

	return;

}

//ヘッダーとデータ
template <typename T, typename U>
void write_csv(v2_T(T) data, std::unordered_map<std::string, ULLI> hearder_name, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{
	//ヘッダーの名前を格納するイテレータ
	std::unordered_map<std::string, ULLI>::iterator hearder_iter;
	hearder_iter = hearder_name.begin();

	//ファイル
	std::ofstream write(filename, mode);
	ULLI now_cell_num = 0;

	//ヘッダーの名前を書き込む
	while (hearder_iter != hearder_name.end())
	{
		//書き込み
		write << hearder_iter->first;

		//最後の列の処理など
		if (now_cell_num == (hearder_name.size() - 1))
		{
			write << std::endl;
		}
		else
		{
			write << sep;
		}
		//値を更新
		now_cell_num++;
		hearder_iter++;
	}

	//以降は同じ
	write_csv(data, filename, std::ios::ate, sep);

	return;
}

//データと行名の時
template <typename T>
void write_csv(v2_T(T) data, std::unordered_map<std::string, ULLI> row_name, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{
	//イテレータ
	std::unordered_map<std::string, ULLI>::iterator row_name_iter;
	row_name_iter = row_name.begin();

	//出力ファイルの定義
	std::ofstream write(filename, mode);
	ULLI row, col;

	rep(row, data.size())
	{
		//１列目がrow_nameの時の処理
		write << row_name_iter->first << sep;

		//データの書き込み
		rep(col, ((data.size()) - 1))
		{
			//出力
			write << data[row][col] << sep;
		}
		//最後の列の処理
		write << data[row][((data.size()) - 1)] << std::endl;
		row_name_iter++;
	}

	return;
}

//ヘッダー，行名，データがあるとき
template <typename T>
void write_csv(v2_T(T) data, std::unordered_map<std::string, ULLI> hearder_name, std::unordered_map<std::string, ULLI> row_name, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{
	//ヘッダーの名前を格納するイテレータ
	std::unordered_map<std::string, ULLI>::iterator hearder_iter;
	hearder_iter = hearder_name.begin();

	//出力ファイルの定義
	std::ofstream write(filename, mode);
	ULLI now_cell_num = 0;

	//ヘッダーの書き込み
	while (hearder_iter != hearder_name.end())
	{
		//書き込み
		write << hearder_iter->first;


		//文字の判定
		if (now_cell_num == (hearder_name.size() - 1))
		{
			write << std::endl;
		}
		else
		{
			write << sep;
		}
		//更新
		now_cell_num++;
		hearder_iter++;
	}

	//ヘッダーは書いたのでそれ以外の処理
	write_csv(data, row_name, filename, std::ios::ate, sep);

	return;
}

//マップの時
template <typename T, typename U> void write_csv(std::unordered_map<T, U>& ans_map, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',') {

	//ファイル出力
	std::ofstream write(filename, mode);
	typename std::unordered_map<T, U>::iterator map_iter;
	map_iter = ans_map.begin();

	while (map_iter != ans_map.end())
	{
		//出力
		write << map_iter->first << sep << map_iter->second << std::endl;

		//更新
		map_iter++;
	}

	return;

}

template <typename T, typename U> void write_csv(std::unordered_map<T, std::vector<U>> ans_map, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',') {

	//ファイル出力
	std::ofstream write(filename, mode);

	typename std::unordered_map<T, std::vector<U>>::iterator map_iter;
	map_iter = ans_map.begin();

	typename std::vector<U>::iterator vec_iter;

	while (map_iter != ans_map.end())
	{
		//debug(map_iter->first)
		//出力
		vec_iter = map_iter->second.begin();

		write << map_iter->first;

		while (vec_iter != map_iter->second.end())
		{
			//出力
			write << sep << *vec_iter;


			//更新
			vec_iter++;
		}

		write << std::endl;
		//更新
		map_iter++;
	}

	return;

}

//曜日の計算（ツェラーの公式）
int day_of_the_week(int year = 0000, int month = 1, int day = 1)
{
	//1月と2月は前年の13月と14月として計算する
	if (month == 1 || month == 2)
	{
		year--;
		month += 12;
	}
	return (year + year / 4 - year / 100 + year / 400 + (13 * month + 8) / 5 + day) % 7;
}

//うるう年判定
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


//yyyy/mm/ddのA日からB日まで日付をマップとして返す
//A日からB日までの経過日数を計算する
std::unordered_map<std::string, ULLI> day_map_age(int start_year, int start_month, int start_day, int end_year, int end_month, int end_day, char sep = '/') {

	//答えの定義
	std::unordered_map<std::string, ULLI> day_map;

	int now_year, now_month, now_day, long_days;
	long_days = 0;

	//年のループ
	for (now_year = start_year; now_year <= end_year; ++now_year) {

		//終了する曜日の定義
		int month_limit;
		if (now_year < end_year) {

			// 基本的には年末まで
			month_limit = 12;
		}
		else {

			//最終年のみ月が終わる日が異なる
			month_limit = end_month;
		}

		// 月のループ
		for (now_month = 1; now_month <= month_limit; ++now_month) {

			//最終の日付の判定
			int day_limit;
			if (now_year < end_year || now_month < end_month) {

				//最終日の判定
				//うるう年判定
				if (now_month == 2) {

					//うるう年判定は上の式
					if (is_leap_year(now_year)) {
						day_limit = 29;
					}
					else {
						day_limit = 28;
					}
				}
				//30日の月のみ抽出
				else if (now_month == 4 || now_month == 6 || now_month == 9 || now_month == 11) {
					day_limit = 30;
				}
				else {
					day_limit = 31;
				}
			}
			else {
				//最終年かつ最終日のみ異なる
				day_limit = end_day;
			}

			// 日付のループ
			for (now_day = 1; now_day <= day_limit; ++now_day) {
				// create the date string in format yyyy/mm/dd
				std::string date = std::to_string(now_year) + sep
					+ std::to_string(now_month) + sep
					+ std::to_string(now_day);
				// increment long_days and add to map
				day_map[date] = long_days;
				++long_days;
			}
		}
	}

	//答えを返す
	return day_map;
}

//(T) year, (T) month, (T) dayを yyyy/mm/dd の形式に変換する
template <typename T> std::string T_to_date_trans_func(T& year, T& month, T& day, char sep = '/') {
	std::string ans;
	ans = std::to_string(year) + sep + std::to_string(month) + sep + std::to_string(day);

	return ans;
}


//yyyy/mm/dd の形式を (int) year, (int) month, (int) day に変換する
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

void date_to_int::function(std::string date_s, char sep) {
	//日付の分割
	std::vector<std::string> date_split = split(date_s, '/');

	//日付の変換
	year = std::stoi(date_split[0]);
	month = std::stoi(date_split[1]);
	day = std::stoi(date_split[2]);

	return;
}

//スワップ
template <typename T>
void swap(T& a, T& b) { //返り値がないからポインターなどでする必要がある
	//一時変数
	T temp = a;

	//入れ替え
	a = b;
	b = temp;
	return;
}

//小さいデータの比較
template<typename T>bool data_comparison(T& data_x, T& data_y) {

	//計算機イプシロンの定義
	LLD data_eps = std::numeric_limits<T>::epsilon();

	//2つのデータの差がeps以下ならばtrueを返す
	if (std::abs(data_x - data_y) < data_eps) {
		return true;
	}
	else {
		return false;
	}
}

//データの基本統計量を算出
template <typename T>
class data_statistics
{
private:
	LLD mode = -1;
	ULLI max_count = 0;
	std::unordered_map<T, ULLI> data_map;

public:
	data_statistics(v_T(T)& data);
	void function(v_T(T) data);
	LLD max_value, min_value, mean_value, median_value, mode_value, variance_value, sd_value, sum_value;
};

template <typename T>
data_statistics<T>::data_statistics(v_T(T)& data)
{
	// コンストラクタの中身
	function(data);

};

template <typename T>
void data_statistics<T>::function(v_T(T) data) {
	sum_value = std::accumulate(v_all(data), (T)0);
	max_value = std::max_element(v_all(data));
	min_value = std::min_element(v_all(data));
	mean_value = sum_value / data.size();

	//分散の計算
	// 最初1　最後1　最初2　初期値
	auto variance_func1 = [mean_value](LLD acc, LLD a) {
		return (acc + std::pow(a - mean_value, 2));
	};
	variance_value = std::accumulate(data.begin(), data.end(), 0.0, variance_func1) / data.size();

	//標準偏差の計算
	sd_value = std::sqrt(variance_value);

	//中央値
	std::sort(data);//ソートをする
	median_value = ((data.size() % 2 == 0) ? (data[data.size() / 2 - 1] + data[data.size() / 2]) / 2 : data[data.size() / 2]);

	//最頻値
	for (auto itr = data.begin(); itr != data.end(); ++itr) {
		data_map[*itr]++;
	}

	// Find the mode by looping through the map
	for (const auto& kv : data_map) {
		if (kv.second > max_count) {
			max_count = kv.second;
			mode = kv.first;
		}
	}
	mode_value = mode;
	return;
};


//データの基本統計量を算出（行列用）
template <typename T>class  data_statistics_vector :protected data_statistics<std::vector<T>> {

private:
	ULLI  now_temp, now_col;
	v_T(T) now_data;
public:
	data_statistics_vector(v2_T(T) datas);
	v_T(LLD) max_vector, min_vector, mean_vector, median_vector, mode_vector, variance_vector, sd_vector, sum_vector;
};



template<typename T>data_statistics_vector<T>::data_statistics_vector(v2_T(T) datas) :data_statistics(datas) {

	//列数を取得

	rep(now_temp, datas[0].size()) {
		now_data.resize(datas.size());

		//分析データのみ取得　列固定
		rep(now_col, datas.size()) {
			now_data[now_col] = datas[now_col][now_temp];

		}

		//データの基本統計量を算出
		data_statistics<T>::function(now_data);

		//答えを格納
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

//テキストファイルにカンマを入れる
void text_comma(std::string filename = "a.txt", std::string byte_file = "byte.csv", std::string output_file = "a.csv") {

	std::cout << "byteなどが書かれたcsv は，　項目,文字数, バイト数　で記入して\n";
	v2_T(std::string) byte_data;

	//csv読み込む用
	class read_csv read_csv1;
	read_csv1.function(byte_file, true, ',', 1);

	//テキストファイルを読み込み
	std::ifstream read_txt(filename, std::ios::in);


	if (!read_txt.is_open()) {
		std::cout << "Failed to open the text file. Please check the file name and try again.\n";
		return;
	}

	//出力ファイルの定義
	std::ofstream write_csv(output_file, std::ios::out);

	//仮変数
	std::string temp_line;
	std::string temp_ans;
	ULLI csv_length;

	while (getline(read_txt, temp_line)) {

		temp_ans = "";
		rep(csv_length, read_csv1.data_matrix.size())
		{
			//文字の操作
			//substr　（開始位置-1（0スタート），文字数）
			temp_ans += temp_line.substr(std::stoull(read_csv1.data_matrix[csv_length][0]) - 1, std::stoull(read_csv1.data_matrix[csv_length][1])) + ",";

		}
		//カンマが1つ多いので削除
		temp_ans.pop_back();
		write_csv << temp_ans << "\n";

	}

	return;

}

//日付の型をそろえる
std::string remove_zero_form_date(std::string& date, char sep = '/') {
	//日付の共通化
	std::vector<std::string> date_int = split(date, sep);
	int now_y = std::stoi(date_int[0]);
	int now_m = std::stoi(date_int[1]);
	int now_d = std::stoi(date_int[2]);
	std::string now_date = T_to_date_trans_func(now_y, now_m, now_d, sep);
	return now_date;
}

//二分木探索
template<typename T, typename Fn>T binary_search_tree(T& data_a, T data_b, Fn& func) {

	T mean = (data_a + data_b) / 2.0;

	if (data_comparison(data_a, data_b)) {
		return mean;
	}

	T ans;

	T ans_a = func(data_a);
	T ans_b = func(data_b);

	if (data_comparison(ans_a, ans_b)) {
		ans = binary_search_tree(data_a, mean, func);
	}
	else {
		ans = binary_search_tree(data_b, mean, func);

	}

	return ans;

}


// log sum exp
template<typename T> T log_sum_exp(std::vector<T>data) {
	//最大値を取得
	T max_value = *std::max_element(data.begin(), data.end());
	T sum = 0;

	//最大値を引いて，expをとる
	for (T value : data) {
		sum += std::exp(value - max_value);
	}

	//logをとる
	return max_value + std::log(sum);
}

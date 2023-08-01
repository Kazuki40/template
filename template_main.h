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

// �}�N��

// �f�o�b�N�p
#define debug(x) std::cerr << "\033[33m(line:" << __LINE__ << ") " << #x << ": " << x << "\033[m" << std::endl;

// �^��`
#define ULLI unsigned long long int
#define LLD long double

// ���[�v
#define rep(i, n) for (i = 0; i < n; i++)

// 2�����z��̒�`
#define v2_T(T) std::vector<v_T(T)>
// 1�����z��̒�`
#define v_T(T) std::vector<T>

// �S�đI��
#define v_all(v) (v).begin(), (v).end()

// ��(C++20 ���g���鎞�� numbers ����擾��������������j
#define PI std::acos(-1)

// �֐�

// ������̕���
std::vector<std::string> split(std::string str, char sep)
{
	ULLI first = 0;
	ULLI last = str.find_first_of(sep); // �ŏ��Ɍ��ꂽ�f���~�^�̈ʒu���擾

	std::vector<std::string> result;

	while (first < str.size())
	{
		std::string subStr(str, first, last - first); // �O���琔���ĕ����̏ꏊ�܂Ŏ��o��

		result.push_back(subStr); // ��������

		first = last + 1;					  // �Ώۂ̕�������P�������炷
		last = str.find_first_of(sep, first); // ���̃f���~�^�܂ł̒������擾

		// ����������Ȃ���΁C�Ō�ɂ���
		if (last == std::string::npos)
		{
			last = str.size();
		}
	}

	return result;
}

// �t�@�C���ǂݍ��ݗp
template <typename Fn>
void read_csv_line(std::string filename, char sep, Fn lamde_func)
{

	std::ifstream read_csv(filename, std::ios::in);
	std::string temp_line;
	std::vector<std::string> temp_cell;

	// �f�[�^�̂P�s
	while (getline(read_csv, temp_line))
	{

		// ����
		temp_cell = split(temp_line, sep);

		/*
		�����_��

		{}(����)void {����}
		[]:�L���v�`�����X�g [&] �͎Q�Ɠn�� [=} �͒l�n�� [this] �̓����o�ϐ����g����
		():����
		->
		void �Ԃ�l
		{}:����
		() �������s
		*/

		// �֐��̎��s
		lamde_func(temp_cell);
	}

	return;
}

// �s����쐬����N���X�i�W���̂݁j
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
	v2_T(T) getter_diag(T data_num = 1);		  // �P�ʍs��֐�
	v2_T(T) getter_matrix0(T row = 1, T col = 1); // 0�̍s��֐�
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

// �P�ʍs��̍쐬
template <typename T>
v2_T(T) make_matrix<T>::getter_diag(T data_num)
{
	v2_T(T) ans = make_matrix(data_num, data_num); // ��`
	rep(loop_i, data_num) ans[loop_i][loop_i] = 1; // �Ίp������1�ɂ���

	return ans;
};

// �S�Ă�0�̍s����쐬
template <typename T>
v2_T(T) make_matrix<T>::getter_matrix0(T row, T col)
{
	v2_T(T) ans(row, std::vector<T>(col, 0)); // ��`

	return ans;
};

// csv�t�@�C����ǂݍ��ރN���X
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

// �Q�b�^�[
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
	// �t�@�C�����J��
	std::ifstream read_csv_file(file, std::ios::in);

	// �G���[�̎��̏���
	if (!read_csv_file.is_open())
	{
		std::cout << "Failed to open the csv file. Please check the file name and try again.\n";
		return;
	}

	// �P�s�ڂ̏���
	this->the_first_line = true;

	// ���[�v
	while (getline(read_csv_file, this->temp_line))
	{
		// �ϐ���`
		// �i�[����f�[�^
		v_T(std::string) temp_data;

		// ������𕪊�����
		std::stringstream split(this->temp_line);

		// 0��ڂ̏���
		this->temp_cell_num = 0;

		// ��̏���
		while (getline(split, this->temp_cell, sep))
		{
			// �s�v�ȋL�����폜
			if (this->temp_cell.at(0) == '\"')
			{
				this->temp_cell.pop_back();						// �Ō��1�������폜
				this->temp_cell.erase(this->temp_cell.begin()); // 1�����ڂ��폜
			}

			// 1�s�ڂ̎��̏���
			if ((the_first_line == true) && (header == true))
			{
				// �w�b�_�[�̖��O�Ɣԍ����i�[
				this->hearder_name.emplace(temp_cell, temp_cell_num);
			}
			else
			{
				// 1��ڂ����O�̎������P��ڂ̎��̏���
				if ((row_name_num == 1) && (temp_cell_num == 0))
				{
					// 1��ڂ����O�̎��̏���
					row_name.emplace(temp_cell, row_name.size());
				}
				else
				{
					// �f�[�^�𓱓�
					temp_data.push_back(temp_cell);
				}
			}

			// ��ԍ��𑝂₷
			temp_cell_num++;
		}

		// �w�b�_�[������

		if (!((header == true) && (the_first_line == true)))
		{
			// �f�[�^���i�[
			this->data_matrix.push_back(temp_data);
		}

		the_first_line = false;
	}
	return;
};

// csv�t�@�C�����������ފ֐�
// �I�[�o�[���[�h
// �f�[�^�̂�
template <typename T>
void write_csv(v2_T(T) data, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{
	// �t�@�C���o��
	std::ofstream write(filename, mode);
	ULLI row, col; // ���ϐ�

	// ���[�v
	rep(row, data.size())
	{
		// ���[�v
		rep(col, ((data.size()) - 1))
		{
			// ��������
			write << data[row][col] << sep;
		}
		// �Ō�̗�̏���
		write << data[row][((data.size()) - 1)] << std::endl;
	}

	return;
}

// �w�b�_�[�ƃf�[�^
template <typename T, typename U>
void write_csv(v2_T(T) data, std::unordered_map<std::string, ULLI> hearder_name, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{
	// �w�b�_�[�̖��O���i�[����C�e���[�^
	std::unordered_map<std::string, ULLI>::iterator hearder_iter;
	hearder_iter = hearder_name.begin();

	// �t�@�C��
	std::ofstream write(filename, mode);
	ULLI now_cell_num = 0;

	// �w�b�_�[�̖��O����������
	while (hearder_iter != hearder_name.end())
	{
		// ��������
		write << hearder_iter->first;

		// �Ō�̗�̏����Ȃ�
		if (now_cell_num == (hearder_name.size() - 1))
		{
			write << std::endl;
		}
		else
		{
			write << sep;
		}
		// �l���X�V
		now_cell_num++;
		hearder_iter++;
	}

	// �ȍ~�͓���
	write_csv(data, filename, std::ios::ate, sep);

	return;
}

// �f�[�^�ƍs���̎�
template <typename T>
void write_csv(v2_T(T) data, std::unordered_map<std::string, ULLI> row_name, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{
	// �C�e���[�^
	std::unordered_map<std::string, ULLI>::iterator row_name_iter;
	row_name_iter = row_name.begin();

	// �o�̓t�@�C���̒�`
	std::ofstream write(filename, mode);
	ULLI row, col;

	rep(row, data.size())
	{
		// �P��ڂ�row_name�̎��̏���
		write << row_name_iter->first << sep;

		// �f�[�^�̏�������
		rep(col, ((data.size()) - 1))
		{
			// �o��
			write << data[row][col] << sep;
		}
		// �Ō�̗�̏���
		write << data[row][((data.size()) - 1)] << std::endl;
		row_name_iter++;
	}

	return;
}

// �w�b�_�[�C�s���C�f�[�^������Ƃ�
template <typename T>
void write_csv(v2_T(T) data, std::unordered_map<std::string, ULLI> hearder_name, std::unordered_map<std::string, ULLI> row_name, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{
	// �w�b�_�[�̖��O���i�[����C�e���[�^
	std::unordered_map<std::string, ULLI>::iterator hearder_iter;
	hearder_iter = hearder_name.begin();

	// �o�̓t�@�C���̒�`
	std::ofstream write(filename, mode);
	ULLI now_cell_num = 0;

	// �w�b�_�[�̏�������
	while (hearder_iter != hearder_name.end())
	{
		// ��������
		write << hearder_iter->first;

		// �����̔���
		if (now_cell_num == (hearder_name.size() - 1))
		{
			write << std::endl;
		}
		else
		{
			write << sep;
		}
		// �X�V
		now_cell_num++;
		hearder_iter++;
	}

	// �w�b�_�[�͏������̂ł���ȊO�̏���
	write_csv(data, row_name, filename, std::ios::ate, sep);

	return;
}

// �}�b�v�̎�
template <typename T, typename U>
void write_csv(std::unordered_map<T, U> &ans_map, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{

	// �t�@�C���o��
	std::ofstream write(filename, mode);
	typename std::unordered_map<T, U>::iterator map_iter;
	map_iter = ans_map.begin();

	while (map_iter != ans_map.end())
	{
		// �o��
		write << map_iter->first << sep << map_iter->second << std::endl;

		// �X�V
		map_iter++;
	}

	return;
}

template <typename T, typename U>
void write_csv(std::unordered_map<T, std::vector<U>> ans_map, std::string filename = "a.csv", std::ios_base::openmode mode = std::ios::out, char sep = ',')
{

	// �t�@�C���o��
	std::ofstream write(filename, mode);

	typename std::unordered_map<T, std::vector<U>>::iterator map_iter;
	map_iter = ans_map.begin();

	typename std::vector<U>::iterator vec_iter;

	while (map_iter != ans_map.end())
	{
		// debug(map_iter->first)
		// �o��
		vec_iter = map_iter->second.begin();

		write << map_iter->first;

		while (vec_iter != map_iter->second.end())
		{
			// �o��
			write << sep << *vec_iter;

			// �X�V
			vec_iter++;
		}

		write << std::endl;
		// �X�V
		map_iter++;
	}

	return;
}

// �j���̌v�Z�i�c�F���[�̌����j
int day_of_the_week(int year = 0000, int month = 1, int day = 1)
{
	// 1����2���͑O�N��13����14���Ƃ��Čv�Z����
	if (month == 1 || month == 2)
	{
		year--;
		month += 12;
	}
	return (year + year / 4 - year / 100 + year / 400 + (13 * month + 8) / 5 + day) % 7;
}

// ���邤�N����
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

// yyyy/mm/dd��A������B���܂œ��t���}�b�v�Ƃ��ĕԂ�
// A������B���܂ł̌o�ߓ������v�Z����
std::unordered_map<std::string, ULLI> day_map_age(int start_year, int start_month, int start_day, int end_year, int end_month, int end_day, char sep = '/')
{

	// �����̒�`
	std::unordered_map<std::string, ULLI> day_map;

	int now_year, now_month, now_day, long_days;
	long_days = 0;

	// �N�̃��[�v
	for (now_year = start_year; now_year <= end_year; ++now_year)
	{

		// �I������j���̒�`
		int month_limit;
		if (now_year < end_year)
		{

			// ��{�I�ɂ͔N���܂�
			month_limit = 12;
		}
		else
		{

			// �ŏI�N�̂݌����I�������قȂ�
			month_limit = end_month;
		}

		// ���̃��[�v
		for (now_month = 1; now_month <= month_limit; ++now_month)
		{

			// �ŏI�̓��t�̔���
			int day_limit;
			if (now_year < end_year || now_month < end_month)
			{

				// �ŏI���̔���
				// ���邤�N����
				if (now_month == 2)
				{

					// ���邤�N����͏�̎�
					if (is_leap_year(now_year))
					{
						day_limit = 29;
					}
					else
					{
						day_limit = 28;
					}
				}
				// 30���̌��̂ݒ��o
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
				// �ŏI�N���ŏI���݈̂قȂ�
				day_limit = end_day;
			}

			// ���t�̃��[�v
			for (now_day = 1; now_day <= day_limit; ++now_day)
			{
				// create the date string in format yyyy/mm/dd
				std::string date = std::to_string(now_year) + sep + std::to_string(now_month) + sep + std::to_string(now_day);
				// increment long_days and add to map
				day_map[date] = long_days;
				++long_days;
			}
		}
	}

	// ������Ԃ�
	return day_map;
}

//(T) year, (T) month, (T) day�� yyyy/mm/dd �̌`���ɕϊ�����
template <typename T>
std::string T_to_date_trans_func(T &year, T &month, T &day, char sep = '/')
{
	std::string ans;
	ans = std::to_string(year) + sep + std::to_string(month) + sep + std::to_string(day);

	return ans;
}

// yyyy/mm/dd �̌`���� (int) year, (int) month, (int) day �ɕϊ�����
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
	// ���t�̕���
	std::vector<std::string> date_split = split(date_s, '/');

	// ���t�̕ϊ�
	year = std::stoi(date_split[0]);
	month = std::stoi(date_split[1]);
	day = std::stoi(date_split[2]);

	return;
}

// �X���b�v
template <typename T>
void swap(T &a, T &b)
{ // �Ԃ�l���Ȃ�����|�C���^�[�Ȃǂł���K�v������
	// �ꎞ�ϐ�
	T temp = a;

	// ����ւ�
	a = b;
	b = temp;
	return;
}

// �������f�[�^�̔�r
template <typename T>
bool data_comparison(T &data_x, T &data_y)
{

	// �v�Z�@�C�v�V�����̒�`
	LLD data_eps = std::numeric_limits<T>::epsilon();

	// 2�̃f�[�^�̍���eps�ȉ��Ȃ��true��Ԃ�
	if (std::abs(data_x - data_y) < data_eps)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// �f�[�^�̊�{���v�ʂ��Z�o
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
	// �R���X�g���N�^�̒��g
	function(data);
};

template <typename T>
void data_statistics<T>::function(v_T(T) data)
{
	sum_value = std::accumulate(v_all(data), (T)0);
	max_value = std::max_element(v_all(data));
	min_value = std::min_element(v_all(data));
	this->mean_value = sum_value / data.size();

	// ���U�̌v�Z
	//  �ŏ�1�@�Ō�1�@�ŏ�2�@�����l
auto variance_func1 = [this](LLD acc, LLD a)
{
    return (acc + std::pow(a - this->mean_value, 2));
};


	variance_value = std::accumulate(data.begin(), data.end(), 0.0, variance_func1) / data.size();

	// �W���΍��̌v�Z
	sd_value = std::sqrt(variance_value);

	// �����l
	std::sort(data); // �\�[�g������
	median_value = ((data.size() % 2 == 0) ? (data[data.size() / 2 - 1] + data[data.size() / 2]) / 2 : data[data.size() / 2]);

	// �ŕp�l
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

// �o��
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

// �f�[�^�̊�{���v�ʂ��Z�o�i�s��p�j
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
this->now_temp=0;
 this->now_col=0;
	this->max_vector = {};
	this->min_vector = {};
	this->mean_vector = {};
	this->median_vector = {};
	this->mode_vector = {};
	this->variance_vector = {};
	this->sd_vector = {};
	this->sum_vector = {};
}

template <typename T> void data_statistics_vector<T>::setter(v2_T(T) datas)
{

	// �񐔂��擾

	rep(now_temp, datas[0].size())
	{
		now_data.resize(datas.size());

		// ���̓f�[�^�̂ݎ擾�@��Œ�
		rep(now_col, datas.size())
		{
			now_data[now_col] = datas[now_col][now_temp];
		}

		// �f�[�^�̊�{���v�ʂ��Z�o
		data_statistics<T>::function(now_data);

		// �������i�[
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

// �o��
template <typename T> v_T(LLD) data_statistics_vector<T>::get_max()
{
	return max_vector;
};
template <typename T> v_T(LLD) data_statistics_vector<T>::get_min()
{
	return min_vector;
};
template <typename T> v_T(LLD) data_statistics_vector<T>::get_mean()
{
	return mean_vector;
};
template <typename T> v_T(LLD) data_statistics_vector<T>::get_median()
{
	return median_vector;
};
template <typename T> v_T(LLD) data_statistics_vector<T>::get_mode()
{
	return mode_vector;
};
template <typename T> v_T(LLD) data_statistics_vector<T>::get_variance()
{
	return variance_vector;
};
template <typename T> v_T(LLD) data_statistics_vector<T>::get_sd()
{
	return sd_vector;
};
template <typename T> v_T(LLD) data_statistics_vector<T>::get_sum()
{
	return sum_vector;
};


// �e�L�X�g�t�@�C���ɃJ���}������
void text_comma(std::string filename = "a.txt", std::string byte_file = "byte.csv", std::string output_file = "a.csv")
{
	std::cout << "byte�Ȃǂ������ꂽcsv �́C�@����,������, �o�C�g���@�ŋL������\n";
	v2_T(std::string) byte_data;

	// csv�ǂݍ��ޗp
	class read_csv read_csv1;
	read_csv1.setter(byte_file, true, ',', 1);

	// �e�L�X�g�t�@�C����ǂݍ���
	std::ifstream read_txt(filename, std::ios::in);

	if (!read_txt.is_open())
	{
		std::cout << "Failed to open the text file. Please check the file name and try again.\n";
		return;
	}

	// �o�̓t�@�C���̒�`
	std::ofstream write_csv(output_file, std::ios::out);

	// ���ϐ�
	std::string temp_line;
	std::string temp_ans;
	ULLI csv_length;
	std::vector<std::vector<std::string>> data = read_csv1.getter_data_matrix();

	while (getline(read_txt, temp_line))
	{

		temp_ans = "";
		rep(csv_length, data.size())
		{
			// �����̑���
			// substr�@�i�J�n�ʒu-1�i0�X�^�[�g�j�C�������j
			temp_ans += temp_line.substr(std::stoull(data[csv_length][0]) - 1, std::stoull(data[csv_length][1])) + ",";
		}
		// �J���}��1�����̂ō폜
		temp_ans.pop_back();
		write_csv << temp_ans << "\n";
	}

	return;
}

// ���t�̌^�����낦��
std::string remove_zero_form_date(std::string &date, char sep = '/')
{
	// ���t�̋��ʉ�
	std::vector<std::string> date_int = split(date, sep);
	int now_y = std::stoi(date_int[0]);
	int now_m = std::stoi(date_int[1]);
	int now_d = std::stoi(date_int[2]);
	std::string now_date = T_to_date_trans_func(now_y, now_m, now_d, sep);
	return now_date;
}

// �񕪖ؒT��
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

	if (ans_a<ans_b)
	{
		ans = binary_search_tree(data_a, mean, func);
	}
	else
	{
		ans = binary_search_tree(data_b, mean, func);
	}

	return ans;
}

// �񕪖ؒT��(�z��)
template <typename T, typename U,typename Fn>
U binary_search_tree(std::vector<T> &data_v,U data_a, U data_b, Fn &func)
{

U ans;
T ans_a = func(data_a);
T ans_b = func(data_b);

if(abs(data_a-data_b)==1){

ans = (ans_a<ans_b)? data_a:data_b;

return ans;

}


U ans_now = (data_a + data_b) / 2;


if(ans_a<ans_b){

ans = binary_search_tree(data_v,data_a,ans_now,func);

}else{

ans = binary_search_tree(data_v,ans_now,data_b,func);

}

	return ans;

}



// log sum exp
template <typename T>
T log_sum_exp(std::vector<T> data)
{
	// �ő�l���擾
	T max_value = *std::max_element(data.begin(), data.end());
	T sum = 0;

	// �ő�l�������āCexp���Ƃ�
	for (T value : data)
	{
		sum += std::exp(value - max_value);
	}

	// log���Ƃ�
	return max_value + std::log(sum);
}


#include <map>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <Windows.h>



uintmax_t sum(std::map<std::string, uintmax_t>& t) {//求和
	uintmax_t a = 0;

	for (auto& i : t) {
		a += i.second;
	}

	return a;
}



int main() {
	std::vector<std::string> ts = { "java","h","cpp" };//需要统计的文件后缀
	std::map<std::string, uintmax_t> row;//行数大小
	std::map<std::string, uintmax_t> size;//文件大小
	std::map<std::string, uintmax_t> count;//文件总数



	char exe[MAX_PATH];
	GetModuleFileName(NULL, exe, MAX_PATH);

	for (auto& i : std::filesystem::recursive_directory_iterator(std::filesystem::path(exe).parent_path(), std::filesystem::directory_options::skip_permission_denied)) {
		if (!i.path().has_extension()) {
			continue;
		}

		auto t = i.path().extension().string().substr(1);

		if (std::find(ts.begin(), ts.end(), t) == ts.end()) {
			continue;
		}

		std::cout << i.path().string() << std::endl;

		size_t len;
		char buff[8192];

		std::ifstream is(i.path(), std::ios::in | std::ios::binary);

		while ((len = is.read(buff, sizeof(buff)).gcount()) > 0) {
			for (int i = 0; i < len; i++) {
				if (buff[i] == '\n') {
					row[t]++;
				}
			}
		}

		is.close();

		size[t] += i.file_size();
		count[t]++;





	}



	for (auto& i : row) {
		std::cout << "行数数量   " << i.first << "   " << i.second << " 行" << std::endl;
	}

	std::cout << "总计行数   " << sum(row) << " 行" << std::endl;
	std::cout << std::endl;

	for (auto& i : size) {
		std::cout << "文件大小   " << i.first << "   " << i.second << " 字节" << std::endl;
	}

	std::cout << "总计大小   " << sum(size) << " 字节" << std::endl;
	std::cout << std::endl;

	for (auto& i : count) {
		std::cout << "文件数量   " << i.first << "   " << i.second << " 个" << std::endl;
	}

	std::cout << "总计数量   " << sum(count) << " 个" << std::endl;
	std::cout << std::endl;









	system("pause");





}




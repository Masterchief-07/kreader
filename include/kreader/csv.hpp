#pragma once
#include <vector>
#include <fstream>
#include <filesystem>
namespace kreader{
    class CSV{
        private:
        std::filesystem::path m_filepath;
        std::ifstream m_file;
        std::vector<std::vector<std::string>> m_data;
        std::pair<int, int> m_size; //first = width, second = height

        public:
        // CSV(const std::string& file_path);
        explicit CSV(std::filesystem::path& file_path);
        CSV(const CSV&) = delete;
        CSV& operator=(const CSV&) = delete;
        CSV(const CSV&&) noexcept = delete;
        CSV& operator=(const CSV&&) noexcept = delete;
        ~CSV();
        std::pair<int, int> Size();

    };

    void HelloWorld();
}
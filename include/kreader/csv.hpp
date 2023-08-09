#pragma once
#include <vector>
#include <fstream>
#include <filesystem>
#include <cassert>
#include <iterator>
namespace kreader{
    class CSV{
        private:
        std::filesystem::path m_filepath;
        std::ifstream m_file;
        std::vector<std::string> m_header;
        std::pair<size_t, size_t> m_size; //first = width, second = height
        bool m_has_header;
        std::stringstream getDataIndex(size_t  index);
        static std::pair<size_t, size_t> getFileSize(const std::filesystem::path& path, std::vector<std::string>* header = nullptr);

        public:
        // CSV(const std::string& file_path);
        explicit CSV(const std::string& file_path, bool has_header=true);
        CSV(const CSV&) = delete;
        CSV operator=(const CSV&) = delete;
        CSV(const CSV&&) = delete;
        CSV operator=(const CSV&&) = delete;
        ~CSV();
        void open(const std::string& file_path, bool has_header=true);
        inline std::pair<size_t, size_t> Size() { return m_size;};
        inline std::vector<std::string> Header() {return m_header;};
        template<typename T>
        std::vector<T> Get(size_t index){
            auto content = getDataIndex(index);
            size_t nb_content = m_header.size() > 0 ? m_size.second-1 : m_size.second;
            std::vector<T> result(nb_content);
            for (size_t i=0; i < nb_content; i++)
            {
                content >> result[i];
            }
            return result;
        }
        template<>
        std::vector<std::string> Get<std::string>(size_t index)
        {
            auto content = getDataIndex(index);
            std::vector<std::string> result{};
            for(std::string data; std::getline(content, data, '\n');)
            {
                result.push_back(data);
            }
            return result;
        }

    };

    void HelloWorld();
}
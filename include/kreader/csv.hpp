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
        std::fstream m_file;
        std::vector<std::string> m_header;
        std::pair<size_t, size_t> m_size; //first = width, second = height
        bool m_has_header;
        std::stringstream getDataIndex(size_t  index);

        public:
        // CSV(const std::string& file_path);
        explicit CSV(std::filesystem::path& file_path, bool has_header=true);
        CSV(const CSV&) = delete;
        CSV operator=(const CSV&) = delete;
        CSV(const CSV&&) = delete;
        CSV operator=(const CSV&&) = delete;
        ~CSV();
        inline std::pair<size_t, size_t> Size() { return m_size;};
        inline std::vector<std::string> Header() {return m_header;};
        template<typename T>
        std::vector<T> Get(size_t index){
            auto content = getDataIndex(index);
            std::vector<T> result;
            std::copy(std::insert_iterator<T>(content),
                        std::insert_iterator<T>(),
                        std::back_inserter(result));
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
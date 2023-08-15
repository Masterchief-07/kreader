#pragma once
#include <vector>
#include <fstream>
#include <filesystem>
#include <cassert>
#include <iterator>
// #include <type_traits>
#include <concepts>

namespace kreader{
    template <typename T>
    concept StringOrSizeT = std::is_same_v<T, std::string>||std::is_integral_v<T>;
    class CSV{
        private:
        std::filesystem::path m_filepath;
        std::ifstream m_file;
        std::vector<std::string> m_header;
        std::pair<size_t, size_t> m_size; //first = width, second = height
        bool m_has_header;
        std::stringstream getDataIndex(const size_t&  index);
        std::size_t getIndexFromString(std::string_view index_name);
        std::vector<std::size_t> getIndexFromString(const std::vector<std::string_view>& indexes_name);
        static std::pair<size_t, size_t> getFileSize(const std::filesystem::path& path, std::vector<std::string>* header = nullptr);
        static void verifyPath(const std::filesystem::path& path);

        public:
        // CSV(const std::string& file_path);
        explicit CSV(const std::string& file_path, bool has_header=true);
        CSV(const CSV&) = delete;
        CSV operator=(const CSV&) = delete;
        CSV(const CSV&&) = delete;
        CSV operator=(const CSV&&) = delete;
        ~CSV();
        void Open(const std::string& file_path, bool has_header=true);
        void Close();
        inline std::pair<size_t, size_t> Size() const { return m_size;};
        inline std::vector<std::string> Header() const {return m_header;};
        
        template<typename T>
        std::vector<T> Get(const size_t& index){
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
        std::vector<std::string> Get<std::string>(const size_t& index)
        {
            auto content = getDataIndex(index);
            std::vector<std::string> result{};
            for(std::string data; std::getline(content, data, '\n');)
            {
                result.push_back(data);
            }
            return result;
        }
        template<typename T>
        std::vector<T> Get(std::string_view index_str){
            auto index = getIndexFromString(index_str);
            auto result = Get<T>(index);
            return result;
        }
        template<typename T, typename ...Args>
        std::vector<std::vector<T>> Get(const size_t& value1, const size_t& value2, Args ... args)
        {
            return {Get<T>(value1), Get<T>(value2), Get<T>(args)...};
        }
        template<typename T, typename ...Args>
        std::vector<std::vector<T>> Get(std::string_view value1, std::string_view value2, Args ... args)
        {
            return {Get<T>(value1), Get<T>(value2), Get<T>(args)...};
        }

        // //get all data
        // template<typename T>
        // std::vector<std::vector<T>> GetAll()
        // {
        //     std::vector<std::vector<T>> result;
        //     result.reserve(m_size.second);
        //     std::stringstream ssresult;
        //     std::ifstream file{m_filepath};
        //     bool first = true;
        //     for (std::string line; std::getline(file, line, '\n');)
        //     {
        //         if(m_has_header && first)
        //         {
        //             first = false;
        //             continue;
        //         }
        //         std::istringstream datastream{line};
        //         size_t count=0;
        //         for(std::string data; getline(datastream, data, ','); count++)
        //         {
        //             ssresult << data <<"\n";
        //         }
        //     }
        //     for (size_t i=0; i < m_size.second; i++)
        //     {
        //         std::vector<T> row(m_size.first);
        //         for(size_t y = 0; y < m_size.first; i++)
        //         {
        //             ssresult>>row[y];
        //         }
        //         result.push_back(std::move(row));
        //     }
        //     file.close();
        //     return result;
        // }
        //WRITE A CSV FILE
        template<typename T>
        static void Write(const std::filesystem::path& path, const std::vector<std::vector<T>>& data, const std::vector<std::string>*headers=nullptr){
            assert(std::string{path.extension()} == "csv");
            assert(data.size() > 0);
            if (headers != nullptr)
            {
                assert(data.size() == (*headers).size());
            }
            std::ofstream writer{path};
            assert(writer.is_open() == true);
            if (headers != nullptr)
            {
                const size_t HEADER_SIZE = headers->size();
                for(size_t i=0; i < HEADER_SIZE; i++)
                {
                    if( i == HEADER_SIZE-1)
                    {
                        writer<<(*headers)[i];
                        continue;
                    }
                    writer<<(*headers)[i]<<',';
                }
                writer<<'\n';
            }
            for (auto const& row : data)
            {
                for(size_t i=0; i < row.size(); i++)
                {
                    if(i == row.size()-1)
                    {
                        writer<<row[i];
                        continue;
                    }
                    writer<<row[i]<<',';
                }
                writer<<'\n';
            }
            writer.close();
        }
    };

    void HelloWorld();
}
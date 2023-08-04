#include <kreader/csv.hpp>
#include <iostream>
#include <cassert>

namespace kreader{
    // CSV::CSV(const std::string& file_path):CSV(std::move(std::filesystem::path{file_path}))
    // {
        
    // }
    CSV::CSV(std::filesystem::path& file_path): m_filepath{file_path}
        ,m_file{m_filepath, std::ios::in}
        ,m_size{std::make_pair(0, 0)}
    {
        assert(m_file.is_open() == false);
        std::string data;
        while(std::getline(m_file, data))
        {
            m_size.second++;
        }
    }

    std::pair<int, int> CSV::Size(){
        return m_size;
    }

    CSV::~CSV(){
        m_file.close();
    }
}

void kreader::HelloWorld(){
    std::cout<<"hello world"<<"\n";
}
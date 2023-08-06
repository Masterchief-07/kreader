#include <kreader/csv.hpp>
#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include <algorithm>

namespace kreader{
    // CSV::CSV(const std::string& file_path):CSV(std::move(std::filesystem::path{file_path}))
    // {
        
    // }
    CSV::CSV(std::filesystem::path& file_path, 
            bool has_header): 
        m_filepath{file_path}
        ,m_file{m_filepath, std::ios::in} 
        ,m_size{std::make_pair(0, 0)}
        ,m_has_header{has_header}
    {
        assert(m_file.is_open() == true);
        bool first = true;
        for(std::string data; std::getline(m_file, data); m_size.second++)
        {
            if (first && m_has_header)
            {
                std::istringstream streamdata{data};
                for(std::string content; std::getline(streamdata, content, ','); )
                {
                    m_header.push_back(content);
                }
                m_size.first = m_header.size();
                first=false;
            }
        }
        // m_file.seekg(0, std::ios::beg);
        m_file.close();
    }

    CSV::~CSV(){
        m_file.close();
    }

    std::stringstream CSV::getDataIndex(size_t index)
    {
        assert(index < m_header.size());
        std::stringstream result;
        m_file.open(m_filepath);
        bool first = true;
        for (std::string line; std::getline(m_file, line, '\n');)
        {
            if(m_has_header && first)
            {
                first = false;
                continue;
            }
            // std::cout<<line<<"\n";
            
            std::istringstream datastream{line};
            size_t count=0;
            for(std::string data; getline(datastream, data, ','); count++)
            {
                if (count > index)
                {
                    break;
                }
                if (count != index)
                {
                    continue;
                }
                // std::cout<<data<<"\n";
                result << data <<"\n";
            }
        }
        m_file.close();
        return result;
    }

    // template<>
    // std::vector<std::string> CSV::operator[](size_t index)
    // {
    //     auto content = getDataIndex(index);
    //     std::vector<std::string> result{};
    //     for(std::string data; std::getline(content, data, '\n');)
    //     {
    //         result.push_back(data);
    //     }
    //     // for (auto const& x: result)
    //     // {
    //     //     std::cout<<x<<"\n";
    //     // }
    //     return result;
    // }
}

void kreader::HelloWorld(){
    std::cout<<"hello world"<<"\n";
}
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
    CSV::CSV(const std::string& file_path, 
            bool has_header): 
        m_filepath{file_path}
        ,m_file{m_filepath, std::ios::in} 
        ,m_size{std::make_pair(0, 0)}
        ,m_has_header{has_header}
    {
        if (has_header)
        {
            m_size = getFileSize(m_filepath, &m_header); 
        }
        else
        {
            m_size = getFileSize(m_filepath); 
        }
        // m_file.seekg(0, std::ios::beg);
        m_file.close();
    }

    CSV::~CSV(){
        m_file.close();
    }

    // void CSV::open(const std::string& file_path, bool has_header)
    // {
    //     m_filepath.

    // }

    std::pair<size_t, size_t> CSV::getFileSize(const std::filesystem::path& path, std::vector<std::string>* header)
    {
        std::pair<size_t, size_t> size;
        std::ifstream file{path};
        assert(file.is_open() == true);
        bool first = true;
        for(std::string data; std::getline(file, data); size.second++)
        {
            if (first && header!=nullptr)
            {
                std::istringstream streamdata{data};
                (*header).clear();
                for(std::string content; std::getline(streamdata, content, ','); size.first++)
                {
                    (*header).push_back(content);
                }
                first=false;
            }
        }
        return size;
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
}

void kreader::HelloWorld(){
    std::cout<<"hello world"<<"\n";
}
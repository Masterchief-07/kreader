#include <kreader/csv.hpp>
#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <format>

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

    CSV::~CSV()
    {
        Close();
    }

    void CSV::Open(const std::string& file_path, bool has_header)
    {
        m_filepath = std::filesystem::path{file_path};
        m_file.open(m_filepath);
        assert(m_file.is_open() == true);
        m_has_header=has_header;
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
    void CSV::Close()
    {
        if (m_file.is_open())
        {
            m_file.close();
        }

    }
    void CSV::verifyPath(const std::filesystem::path& path)
    {
        if(! std::filesystem::exists(path))
        {
            throw std::runtime_error("file doesnt exist");
        }
    }

    std::pair<size_t, size_t> CSV::getFileSize(const std::filesystem::path& path, std::vector<std::string>* header)
    {
        std::pair<size_t, size_t> size;
        verifyPath(path);
        std::ifstream file{path};
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
    std::stringstream CSV::getDataIndex(const size_t& index)
    {
        assert(index < m_size.first);
        std::stringstream result;
        std::ifstream file{m_filepath};
        bool first = true;
        for (std::string line; std::getline(file, line, '\n');)
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
        file.close();
        return result;
    }

    size_t CSV::getIndexFromString(std::string_view index_name){
        if (!m_has_header)
        {
            throw std::runtime_error("file has no header");
        }
        auto finded = std::find(m_header.begin(), m_header.end(), index_name);
        if (finded == m_header.end())
        {
            auto message = std::format("{} not find in header", index_name);
            throw std::runtime_error(message);
        }
        auto dist = std::distance(m_header.begin(), finded);
        return static_cast<size_t>(dist);

    }
    std::vector<std::size_t> CSV::getIndexFromString(const std::vector<std::string_view>& indexes_name)
    {
        if (!m_has_header)
        {
            throw std::runtime_error("file has no header");
        }
        std::vector<std::size_t> result;
        std::for_each(indexes_name.begin(), indexes_name.end(), 
                [this, &result](std::string_view name){
                    result.push_back(getIndexFromString(name));
                }
            );
        return result;
    }
}

void kreader::HelloWorld(){
    std::cout<<"hello world"<<"\n";
}
#include <kreader/csv.hpp>
#include <iostream>

int main(){

    std::filesystem::path path{"/home/jonathan/PROGRAMMING/PROJECTS/kreader/src/kreader_test_sample/test.csv"};
    auto csv = kreader::CSV{path};
    std::cout<<csv.Size().second<<"\n";
    std::cout<<csv[0].size()<<"\n";

    return 0;
}
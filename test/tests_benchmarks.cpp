#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>


// #include <myproject/sample_library.hpp>
#include <kreader/csv.hpp>
#include <iostream>

TEST_CASE("BENCHMARKING", "[KREADER]")
{
    const std::string PATH{"/home/jonathan/PROGRAMMING/PROJECTS/kreader/test/test.csv"};
    auto csv = kreader::CSV{PATH};
    BENCHMARK("READING STR_0"){
        return csv.Get<std::string>(0);
    };
    BENCHMARK("READING STR_1"){
        return csv.Get<std::string>(1);
    };
    BENCHMARK("READING STR_2"){
        return csv.Get<std::string>(2);
    };
    BENCHMARK("READING STR_3"){
        return csv.Get<std::string>(3);
    };
    BENCHMARK("READING STR_4"){
        return csv.Get<std::string>(4);
    };
    BENCHMARK("READING INT_0"){
        return csv.Get<int>(1);
    };
    BENCHMARK("READING INT_1"){
        return csv.Get<int>(4);
    };
    BENCHMARK("READING FLOAT_0"){
        return csv.Get<float>(1);
    };
    BENCHMARK("READING FLOAT_1"){
        return csv.Get<float>(4);
    };
    BENCHMARK("READING DOUBLE_0"){
        return csv.Get<double>(1);
    };
    BENCHMARK("READING DOUBLE_1"){
        return csv.Get<double>(4);
    };
}
TEST_CASE("BENCHMARKING  RETURN VECTOR<VECTOR<>>", "[KREADER]")
{
    const std::string PATH{"/home/jonathan/PROGRAMMING/PROJECTS/kreader/test/test.csv"};
    auto csv = kreader::CSV{PATH};
    BENCHMARK("READING STR"){
        return csv.Get<std::string>("Name","Position", "Department", "Age", "Salary");
    };
    BENCHMARK("READING INT"){
        return csv.Get<int>("Age", "Salary");
    };
    BENCHMARK("READING FLOAT"){
        return csv.Get<float>("Age", "Salary");
    };
    BENCHMARK("READING DOUBLE"){
        return csv.Get<double>("Age", "Salary");
    };
}

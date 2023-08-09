#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>


// #include <myproject/sample_library.hpp>
#include <kreader/csv.hpp>
#include <iostream>


TEST_CASE("Reading CSV with header", "[KREADER]")
{

    const std::string PATH{"/home/jonathan/PROGRAMMING/PROJECTS/kreader/test/test.csv"};
    auto csv = kreader::CSV{PATH};
    REQUIRE(csv.Size().second == 6);
    auto header = csv.Header();
    REQUIRE(header.size() == 5);
    REQUIRE(header[0] == "Name");
    REQUIRE(header[1] == "Age");
    REQUIRE(header[2] == "Position");
    REQUIRE(header[3] == "Department");
    REQUIRE(header[4] == "Salary");

 
}
TEST_CASE("Reading CSV content", "[KREADER]")
{
    const std::string PATH{"/home/jonathan/PROGRAMMING/PROJECTS/kreader/test/test.csv"};
    auto csv = kreader::CSV{PATH};
    auto result = csv.Get<std::string>(0);
    REQUIRE(result.size() == 5);
    REQUIRE(result[0] == "John Doe");
    REQUIRE(result[1] == "Jane Smith");
    REQUIRE(result[2] == "Michael Johnson");
    REQUIRE(result[3] == "Emily Williams");
    REQUIRE(result[4] == "David Lee");
    auto resultint = csv.Get<int>(1);
    REQUIRE(resultint.size() == 5);
    REQUIRE(resultint[0] == 35);
    REQUIRE(resultint[1] == 28);
    REQUIRE(resultint[2] == 42);
    REQUIRE(resultint[3] == 30);
    REQUIRE(resultint[4] == 25);
    result = csv.Get<std::string>(2);
    REQUIRE(result.size() == 5);
    REQUIRE(result[0] == "Software Engineer");
    REQUIRE(result[1] == "Data Analyst");
    REQUIRE(result[2] == "Project Manager");
    REQUIRE(result[3] == "UX Designer");
    REQUIRE(result[4] == "Quality Assurance");
    result = csv.Get<std::string>(3);
    REQUIRE(result.size() == 5);
    REQUIRE(result[0] == "Engineering");
    REQUIRE(result[1] == "Analytics");
    REQUIRE(result[2] == "Management");
    REQUIRE(result[3] == "Design");
    REQUIRE(result[4] == "Engineering");
    auto resultfloat = csv.Get<float>(4);
    const size_t EXPECTED_SIZE{5};
    // std::array<float, EXPECTED_SIZE> EXPECTED{75000.F, 60000.F, 90000.f, 80000.f, 55000.f};
    const float EXPECTED_0 = 75000.F;
    const float EXPECTED_1 = 60000.F;
    const float EXPECTED_2 = 90000.F;
    const float EXPECTED_3 = 80000.F;
    const float EXPECTED_4 = 55000.F;
    const float eps=0.001F;
    REQUIRE(resultfloat.size() == EXPECTED_SIZE);
    REQUIRE_THAT(resultfloat[0], Catch::Matchers::WithinRel(EXPECTED_0, eps));
    REQUIRE_THAT(resultfloat[1], Catch::Matchers::WithinRel(EXPECTED_1, eps));
    REQUIRE_THAT(resultfloat[2], Catch::Matchers::WithinRel(EXPECTED_2, eps));
    REQUIRE_THAT(resultfloat[3], Catch::Matchers::WithinRel(EXPECTED_3, eps));
    REQUIRE_THAT(resultfloat[4], Catch::Matchers::WithinRel(EXPECTED_4, eps));
}

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
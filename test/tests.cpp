#include <catch2/catch_test_macros.hpp>


// #include <myproject/sample_library.hpp>
#include <kreader/csv.hpp>
#include <iostream>


TEST_CASE("Reading CSV with header", "[KREADER]")
{

    std::filesystem::path path{"/home/jonathan/PROGRAMMING/PROJECTS/kreader/test/test.csv"};
    auto csv = kreader::CSV{path};
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
    std::filesystem::path path{"/home/jonathan/PROGRAMMING/PROJECTS/kreader/test/test.csv"};
    auto csv = kreader::CSV{path};
    auto result = csv.Get<std::string>(0);
    REQUIRE(result.size() == 5);
    REQUIRE(result[0] == "John Doe");
    REQUIRE(result[1] == "Jane Smith");
    REQUIRE(result[2] == "Michael Johnson");
    REQUIRE(result[3] == "Emily Williams");
    REQUIRE(result[4] == "David Lee");
    auto resultint = csv.Get<int>(1);
    REQUIRE(resultint.size() == 6);
    REQUIRE(resultint[0] == 35);
    REQUIRE(resultint[1] == 28);
    REQUIRE(resultint[2] == 42);
    REQUIRE(resultint[3] == 30);
    REQUIRE(resultint[4] == 25);
    result = csv.Get<std::string>(2);
    REQUIRE(result.size() == 6);
    REQUIRE(result[0] == "Software Engineer");
    REQUIRE(result[1] == "Data Analyst");
    REQUIRE(result[2] == "Project Manager");
    REQUIRE(result[3] == "UX Designer");
    REQUIRE(result[4] == "Quality Assurance");
    result = csv.Get<std::string>(3);
    REQUIRE(result.size() == 6);
    REQUIRE(result[0] == "Engineering");
    REQUIRE(result[1] == "Analytics");
    REQUIRE(result[2] == "Management");
    REQUIRE(result[3] == "Design");
    REQUIRE(result[4] == "Engineering");
    auto resultfloat = csv.Get<float>(4);
    const std::array<float, 5> expected{
        75000,
        60000,
        90000,
        80000,
        55000
    };
    REQUIRE(resultfloat.size() == 6);
    // REQUIRE(resultfloat[0] >= 75000.f);
    // REQUIRE(resultfloat[1] >= 60000.f);
    // REQUIRE(resultfloat[2] >= 90000.f);
    // REQUIRE(resultfloat[3] >= 80000.f);
    // REQUIRE(resultfloat[4] >= 55000.f);
}

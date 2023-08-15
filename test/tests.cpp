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

TEST_CASE("Reading CSV content to vector<vector>", "[KREADER]")
{
    const std::string PATH{"/home/jonathan/PROGRAMMING/PROJECTS/kreader/test/test.csv"};
    auto csv = kreader::CSV{PATH};
    auto result = csv.Get<std::string>(2, 3);
    REQUIRE(result.size() == 2);
    REQUIRE(result[0].size() == 5);
    REQUIRE(result[1].size() == 5);
    REQUIRE(result[0][0] == "Software Engineer");
    REQUIRE(result[0][1] == "Data Analyst");
    REQUIRE(result[0][2] == "Project Manager");
    REQUIRE(result[0][3] == "UX Designer");
    REQUIRE(result[0][4] == "Quality Assurance");
    REQUIRE(result[1][0] == "Engineering");
    REQUIRE(result[1][1] == "Analytics");
    REQUIRE(result[1][2] == "Management");
    REQUIRE(result[1][3] == "Design");
    REQUIRE(result[1][4] == "Engineering");
    auto resultint = csv.Get<int>(1, 4);
    REQUIRE(resultint.size() == 2);
    REQUIRE(resultint[0].size() == 5);
    REQUIRE(resultint[1].size() == 5);
    REQUIRE(resultint[0][0] == 35);
    REQUIRE(resultint[0][1] == 28);
    REQUIRE(resultint[0][2] == 42);
    REQUIRE(resultint[0][3] == 30);
    REQUIRE(resultint[0][4] == 25);
    REQUIRE(resultint[1][0] == 75000);
    REQUIRE(resultint[1][1] == 60000);
    REQUIRE(resultint[1][2] == 90000);
    REQUIRE(resultint[1][3] == 80000);
    REQUIRE(resultint[1][4] == 55000);
}

TEST_CASE("Reading CSV content using header name", "[KREADER]")
{
    const std::string PATH{"/home/jonathan/PROGRAMMING/PROJECTS/kreader/test/test.csv"};
    auto csv = kreader::CSV{PATH};
    auto result = csv.Get<std::string>("Name");
    REQUIRE(result.size() == 5);
    REQUIRE(result[0] == "John Doe");
    REQUIRE(result[1] == "Jane Smith");
    REQUIRE(result[2] == "Michael Johnson");
    REQUIRE(result[3] == "Emily Williams");
    REQUIRE(result[4] == "David Lee");
    auto resultint = csv.Get<int>("Age");
    REQUIRE(resultint.size() == 5);
    REQUIRE(resultint[0] == 35);
    REQUIRE(resultint[1] == 28);
    REQUIRE(resultint[2] == 42);
    REQUIRE(resultint[3] == 30);
    REQUIRE(resultint[4] == 25);
    result = csv.Get<std::string>("Position");
    REQUIRE(result.size() == 5);
    REQUIRE(result[0] == "Software Engineer");
    REQUIRE(result[1] == "Data Analyst");
    REQUIRE(result[2] == "Project Manager");
    REQUIRE(result[3] == "UX Designer");
    REQUIRE(result[4] == "Quality Assurance");
    result = csv.Get<std::string>("Department");
    REQUIRE(result.size() == 5);
    REQUIRE(result[0] == "Engineering");
    REQUIRE(result[1] == "Analytics");
    REQUIRE(result[2] == "Management");
    REQUIRE(result[3] == "Design");
    REQUIRE(result[4] == "Engineering");
    auto resultfloat = csv.Get<float>("Salary");
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

TEST_CASE("Reading CSV content to vector<vector> using header name", "[KREADER]")
{
    const std::string PATH{"/home/jonathan/PROGRAMMING/PROJECTS/kreader/test/test.csv"};
    auto csv = kreader::CSV{PATH};
    auto result = csv.Get<std::string>("Position","Department");
    REQUIRE(result.size() == 2);
    REQUIRE(result[0].size() == 5);
    REQUIRE(result[1].size() == 5);
    REQUIRE(result[0][0] == "Software Engineer");
    REQUIRE(result[0][1] == "Data Analyst");
    REQUIRE(result[0][2] == "Project Manager");
    REQUIRE(result[0][3] == "UX Designer");
    REQUIRE(result[0][4] == "Quality Assurance");
    REQUIRE(result[1][0] == "Engineering");
    REQUIRE(result[1][1] == "Analytics");
    REQUIRE(result[1][2] == "Management");
    REQUIRE(result[1][3] == "Design");
    REQUIRE(result[1][4] == "Engineering");
    auto resultint = csv.Get<int>("Age", "Salary");
    REQUIRE(resultint.size() == 2);
    REQUIRE(resultint[0].size() == 5);
    REQUIRE(resultint[1].size() == 5);
    REQUIRE(resultint[0][0] == 35);
    REQUIRE(resultint[0][1] == 28);
    REQUIRE(resultint[0][2] == 42);
    REQUIRE(resultint[0][3] == 30);
    REQUIRE(resultint[0][4] == 25);
    REQUIRE(resultint[1][0] == 75000);
    REQUIRE(resultint[1][1] == 60000);
    REQUIRE(resultint[1][2] == 90000);
    REQUIRE(resultint[1][3] == 80000);
    REQUIRE(resultint[1][4] == 55000);
}

// TEST_CASE("Reading CSV content to vector<vector> using header name", "[KREADER]")
// {
//     const std::string PATH{"/home/jonathan/PROGRAMMING/PROJECTS/kreader/test/test.csv"};
//     auto csv = kreader::CSV{PATH};
//     auto result = csv.GetAll<int>();
//     REQUIRE(result.size() == csv.Size().second);
//     REQUIRE(result[0].size() == csv.Size().first);

// }
TEST_CASE("WRITING/READING A CSV FILE", "[KREADER]")
{
    const std::vector<std::string> headers = {
        "a", "b", "c", "e"
    };
    const std::vector<std::vector<float>>data = {
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };
    kreader::CSV::Write("atest.csv", data, &headers);
    auto file =  kreader::CSV{"atest.csv"};
    auto all_header = file.Header();
    REQUIRE(all_header.size() == headers.size());
    for(size_t i = 0; i < all_header.size(); i++)
    {
        REQUIRE(all_header[i] == headers[i]);
    }

}
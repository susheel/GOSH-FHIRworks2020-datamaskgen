//
// Created by Patrick Wu on 06/03/2020.
//

#include <catch2/catch.hpp>
#include <api/api.hh>

TEST_CASE("API should download and read data", "[api]") {
    auto download_result = api::refresh_patients_json();
    REQUIRE(download_result.second);
    auto read_result = api::read_patients_json();
    REQUIRE(read_result.second);
    auto parse_download = nlohmann::json::parse(download_result.first);
    auto parse_read = nlohmann::json::parse(read_result.first);
    REQUIRE(parse_download.dump() == parse_read.dump());
}

TEST_CASE("API should parse patient data correctly", "[api]") {
    auto read_result = api::read_patients_json();
    REQUIRE(read_result.second);
    REQUIRE_NOTHROW(api::parse_raw_patients(read_result.first));
}
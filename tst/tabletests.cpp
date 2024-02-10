#include <Wordset.hpp>
#include <catch2/catch_amalgamated.hpp>
#include <convert.hpp>
#include <string>

namespace {
namespace proj3 = shindler::ics46::project3;

// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.

TEST_CASE("Hash:dbc:Expect5553", "[Required][Hash]") {
    const static unsigned int BASE = 37;
    const static unsigned int MOD = 100000;
    auto hashValue = proj3::polynomialHashFunction("dbc", BASE, MOD);
    size_t shouldBe = 4 * BASE * BASE + 2 * BASE + 3;
    REQUIRE(hashValue == shouldBe);
}

TEST_CASE("Table:SingleInsert:ExpectInTableAndUnchangedCapacity",
          "[Required][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("dbc");
    REQUIRE(wordSet.contains("dbc"));
    REQUIRE(wordSet.capacity() == 11);
}

TEST_CASE("Table:MultiInsert:ExpectInTableAndUnchangedCapacity",
          "[Required][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    REQUIRE(wordSet.capacity() == 11);
}

// this test case is not required, in the sense
// that it is not a prerequisite to grading part 1.
// However, I am providing it in hopes that it helps
// you to test your code.
// The functionality is still needed for full credit!
TEST_CASE("Table:MultiInsertWithResize:ExpectInTableAndResizedTable",
          "[Sample][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    wordSet.insert("salsa");
    wordSet.insert("sloth");
    wordSet.insert("colossus");
    wordSet.insert("synergize");
    wordSet.insert("monday");
    wordSet.insert("tuesday");
    wordSet.insert("wednesday");
    wordSet.insert("thursday");
    wordSet.insert("friday");
    wordSet.insert("saturday");
    wordSet.insert("sunday");
    REQUIRE(wordSet.contains("monday"));
    REQUIRE(wordSet.contains("sunday"));
    REQUIRE(wordSet.capacity() == 23);
    REQUIRE(wordSet.size() == 19);
}

TEST_CASE("Table:FalseContain",
          "[Sample][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    REQUIRE_FALSE(wordSet.contains("icsclass"));
}
TEST_CASE("Table:EraseAndSize",
          "[Sample][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    REQUIRE(wordSet.size() == 8);
    wordSet.erase("sleepy");
    wordSet.erase("happy");
    REQUIRE(wordSet.size() == 6);
    REQUIRE(wordSet.capacity() == 11);
}
TEST_CASE("Table:InsertDuplicateWord",
          "[Sample][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");

    wordSet.insert("happy");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));

    REQUIRE(wordSet.size() == 8);
}
TEST_CASE("Table:EraseNotExistWord",
          "[Sample][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");

    wordSet.erase("uciics");
    REQUIRE_FALSE(wordSet.contains("uciics"));
    REQUIRE(wordSet.size() == 8);
}

TEST_CASE("Table:ResizeWord",
          "[Sample][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    wordSet.insert("salsa");
    wordSet.insert("sloth");
    wordSet.insert("colossus");
    wordSet.insert("synergize");
    wordSet.insert("monday");
    wordSet.insert("tuesday");
    
    REQUIRE(wordSet.contains("sleepy"));
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    REQUIRE(wordSet.contains("sneezy"));
    REQUIRE(wordSet.contains("datalink"));
    REQUIRE(wordSet.contains("australia"));
    REQUIRE(wordSet.contains("guacamole"));
    REQUIRE(wordSet.contains("phylum"));
    REQUIRE(wordSet.contains("salsa"));
    REQUIRE(wordSet.contains("sloth"));
    REQUIRE(wordSet.contains("colossus"));
    REQUIRE(wordSet.contains("synergize"));
    REQUIRE(wordSet.contains("monday"));
    REQUIRE(wordSet.contains("tuesday"));
    
    REQUIRE(wordSet.size() == 14);
    REQUIRE(wordSet.capacity() == 23);
}

TEST_CASE("Table:ResizeWord2",
          "[Sample][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::BaseWordSet<37, 41, 3> wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");

    REQUIRE(wordSet.contains("sleepy"));
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    REQUIRE(wordSet.contains("sneezy"));
    REQUIRE(wordSet.contains("datalink"));
    REQUIRE(wordSet.contains("australia"));
    REQUIRE(wordSet.contains("guacamole"));

    REQUIRE(wordSet.capacity() == 23);
    REQUIRE(wordSet.size() == 7);

    wordSet.erase("australia");
    wordSet.erase("guacamole");
    REQUIRE(wordSet.capacity() == 23);
    REQUIRE(wordSet.size() == 5);
    wordSet.erase("sleepy");
    wordSet.erase("happy");
    wordSet.erase("dopey");
    wordSet.erase("sneezy");
    wordSet.erase("datalink");
    REQUIRE(wordSet.capacity() == 23);
    REQUIRE(wordSet.size() == 0);
}

}  // namespace

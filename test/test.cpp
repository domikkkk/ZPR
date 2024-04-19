#include <gtest/gtest.h>
#include <CompareFiles>


TEST(KMPTest, BasicTest) {
    std::string text = "ababcababcabcabc";
    std::string pattern = "abc";
    std::vector<int> expected_indexes = {2, 7, 10, 13};
    std::vector<int> result_indexes = kmpSearch(text, pattern);

    // Sprawdzenie czy wyniki są zgodne z oczekiwaniami
    ASSERT_EQ(expected_indexes.size(), result_indexes.size());
    for (size_t i = 0; i < expected_indexes.size(); ++i) {
        ASSERT_EQ(expected_indexes[i], result_indexes[i]);
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

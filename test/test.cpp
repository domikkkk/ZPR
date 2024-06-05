// Author: Dominik Sidorczuk i Fedir Tsupin

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


TEST(KMPTest, ExtendedTest) {
    std::string text = "Bylo sobie bardzo zimno albo bardzo cieplo, to zalezalo od punktu widzenia bardzo";
    std::string pattern = "bardzo";
    std::vector<int> expected_indexes = {11, 29, 75};
    std::vector<int> result_indexes = kmpSearch(text, pattern);

    ASSERT_EQ(expected_indexes.size(), result_indexes.size());
    for (size_t i = 0; i < expected_indexes.size(); ++i) {
        ASSERT_EQ(expected_indexes[i], result_indexes[i]);
    }
}


TEST(FileTest, ReadFile) {
    File file = File(fs::path("./test/text_files/test_file.txt"));
    file.read();
    std::string expected = "This is a file for testing file operations";
    ASSERT_EQ(expected, file.getText());
}


TEST(FileTest, SplitByParagraphs) {
    File file = File(fs::path("./test/text_files/par.txt"));
    file.read();
    file.splitByParagraphs();
    Block first = Block("First", 0, 4, 0);
    Block second = Block("Second", 6, 12, 0);
    Block third = Block("Third", 14, 19, 0);
    ASSERT_EQ(first.getText(), file[0].getText());
    ASSERT_EQ(second.getText(), file[1].getText());
    ASSERT_EQ(third.getText(), file[2].getText());
}


TEST(NWTest, computeMatchValue) {
    const std::vector<std::string> s1 = {"The", "quick", "brown", "fox"};
    const std::vector<std::string> s2 = {"The", "quick", "red", "fox"};
    NeedlemanWunsch alg = NeedlemanWunsch();
    auto v1 = alg.computeMatchValue(s1, s2);
    auto v2 = alg.computeMatchValue(s1, s1);
    ASSERT_LT(v1, v2);
}


TEST(ComparatorTest, detectChanges) {
    std::string text1 = "The quick brown fox";
    std::string text2 = "The quick red fox";
    Comparator comparator = Comparator();
    std::vector<Change> changes = comparator.detectChanges(text1, text2, 0, 0, 0, 0);
    ASSERT_EQ(changes[0].getType(), ChangeType::Deletion);
    ASSERT_EQ(changes[0].getText(), "brown");
    ASSERT_EQ(changes[1].getType(), ChangeType::Addition);
    ASSERT_EQ(changes[1].getText(), "red");
}


TEST(ComparatorTest, detectChangesSpaces) {
    std::string text1 = "The    quick brown fox";
    std::string text2 = "The quick brown fox";
    Comparator comparator = Comparator();
    std::vector<Change> changes = comparator.detectChanges(text1, text2, 0, 0, 0, 0);
    ASSERT_EQ(changes[0].getType(), ChangeType::Deletion);
    ASSERT_EQ(changes[0].getText(), "    ");
    ASSERT_EQ(changes[1].getType(), ChangeType::Addition);
    ASSERT_EQ(changes[1].getText(), " ");
}

TEST(ComparatorTest, splitIntoTokens) {
    std::string text = "The    quick brown fox";
    Comparator comparator = Comparator();
    auto tokens = comparator.splitIntoTokens(text);
    ASSERT_EQ(tokens[0], "The");
    ASSERT_EQ(tokens[1], "    ");
    ASSERT_EQ(tokens[2], "quick");
    ASSERT_EQ(tokens[3], " ");
    ASSERT_EQ(tokens[4], "brown");
    ASSERT_EQ(tokens[5], " ");
    ASSERT_EQ(tokens[6], "fox");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

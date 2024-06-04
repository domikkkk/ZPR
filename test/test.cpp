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


TEST(FileTest, Split) {
    File file = File(fs::path("./test/text_files/test_file.txt"));
    file.read();
    file.split(" ");
    Block first = Block("This", 0, 4);
    Block second = Block("is", 5, 7);
    ASSERT_EQ(first.getText(), file[0].getText());
    ASSERT_EQ(second.getText(), file[1].getText());
}


TEST(FileTest, SplitByParagraphs) {
    File file = File(fs::path("./test/text_files/par.txt"));
    file.read();
    file.splitByParagraphs();
    Block first = Block("First", 0, 4);
    Block second = Block("Second", 6, 12);
    Block third = Block("Third", 14, 19);
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


TEST(NWTest, computeMatchValueOneAddition) {
    const std::vector<std::string> s1 = {"First", "b"};
    const std::vector<std::string> s2 = {"b", "First"};
    NeedlemanWunsch alg = NeedlemanWunsch();
    auto v1 = alg.computeMatchValue(s1, s2);
    std::cout << v1 << std::endl;
}


TEST(ComparatorTest, detectChanges) {
    std::string text1 = "The quick brown fox";
    std::string text2 = "The quick red fox";
    Comparator comparator = Comparator();
    std::vector<Change> changes = comparator.detectChanges(text1, text2, 0, 0);
    ASSERT_EQ(changes[0].getType(), ChangeType::Deletion);
    ASSERT_EQ(changes[0].getText(), "brown");
    ASSERT_EQ(changes[1].getType(), ChangeType::Addition);
    ASSERT_EQ(changes[1].getText(), "red");
}


TEST(ComparatorTest, detectChangesSpaces) {
    std::string text1 = "The    quick brown fox";
    std::string text2 = "The quick brown fox";
    Comparator comparator = Comparator();
    std::vector<Change> changes = comparator.detectChanges(text1, text2, 0, 0);
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


TEST(AppTest, compareBasicTest) {
    File f1 = File(fs::path("./test/text_files/paragraphs.txt"));
    File f2 = File(fs::path("./test/text_files/paragraphs_v2.txt"));
    f1.read(); f2.read();
    f1.splitByParagraphs(); f2.splitByParagraphs();
    App app = App(f1, f2);
    auto changes = app.compare();
    for (auto change : changes) {
        std::cout << "Original:[" + change.getOriginal().getText() + "] " << change.getOriginal().getStartPos() << " " << change.getOriginal().getEndPos() << std::endl;
        std::cout << "Modified:[" + change.getModified().getText() + "]" << change.getModified().getStartPos() << " " << change.getModified().getEndPos() << std::endl;
        for (auto c : change.getChanges()) {
            switch(c.getType()) {
                case ChangeType::Addition:
                    std::cout << "Addition: ";
                    break;
                case ChangeType::Deletion:
                    std::cout << "Deletion: ";
                    break;
            }
            std::cout << "[" + c.getText() + "] ";
            std::cout << c.getPosition() << std::endl;
        }
    }
}


TEST(AppTest, compareTest) {
    File f1 = File(fs::path("./test/text_files/paragraphs.txt"));
    File f2 = File(fs::path("./test/text_files/paragraphs_v2.txt"));
    App app = App(f1, f2);
    auto changes = app.compare();
    for (auto change : changes) {
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

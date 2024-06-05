// Author: Fedir Tsupin
#include <compare_files/textdiff.hpp>


Block TextDiff::getOriginal() const {
    return original;
}


Block TextDiff::getModified() const {
    return modified;
}


std::vector<Change> TextDiff::getChanges() const {
    return changes;
}
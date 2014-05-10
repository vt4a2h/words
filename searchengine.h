#pragma once

#include <vector>
#include <string>

namespace words_search {

    using StringVector = std::vector<std::string>;

    class SearchEngine
    {
    public:
        void loadDataFromFile(const std::string &fname);
        void loadWords(const StringVector &words);
        void searchSentences();

        StringVector result() const;

    private:
        void splitDataIntoSentences();

        static const std::string kRegexSplitter_;
        static const std::string kRegexWord_;

        StringVector result_;
        StringVector sentences_;
        StringVector words_;
        std::string  dataBuf_;
    };

}

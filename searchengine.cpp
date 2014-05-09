#include "searchengine.h"

#include <fstream>
#include <streambuf>
#include <boost/format.hpp>
#include <boost/regex.hpp>

namespace words_search {

    // for simple sentences without "Vasya I. Petrov", "Mr. Ivanov", "Nov. 13" etc.
    const std::string SearchEngine::kRegexSplitter_ =
            "(?<=[\\.|\\!|\\?])+\\s(?=[A-Z])";

    // %s for insert word
    const std::string SearchEngine::kRegexWord_ =
            ".*([^[:alnum:]-]|^)%s(?=[^[:alnum:]-]|$).*";

    void SearchEngine::loadDataFromFile(const std::string &fname)
    {
        std::ifstream f(fname);
        if (f) {
            f.seekg(0, std::ios::end);
            dataBuf_.reserve(f.tellg());
            f.seekg(0, std::ios::beg);
            dataBuf_.assign(std::istreambuf_iterator<char>(f),
                            std::istreambuf_iterator<char>());

            splitDataIntoSentences();

            dataBuf_.clear();
        } else {
            throw std::logic_error("can't open file");
        }
    }

    void SearchEngine::loadWords(const StringVector &words)
    {
        words_.clear();
        words_.assign(words.begin(), words.end());
    }

    void SearchEngine::searchWords()
    {
        using namespace boost;

        result_.clear();

        regex word;
        bool wflag(true);
        for (auto s : sentences_) {
            for (auto w : words_) {
                word  = (format(kRegexWord_) % w).str();
                wflag = regex_match(s, word);
                if (!wflag) break;
            }
            if (wflag) result_.push_back(s);
        }
    }

    StringVector SearchEngine::getSearchResult() const
    {
        return result_;
    }

    void SearchEngine::splitDataIntoSentences()
    {
        using namespace boost;

        regex splitter(kRegexSplitter_);
        sregex_token_iterator first(dataBuf_.begin(), dataBuf_.end(), splitter, -1);
        sregex_token_iterator end;

        sentences_.clear();
        sentences_.assign(first, end);
    }
}

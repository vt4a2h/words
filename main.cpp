#include <iostream>
#include <vector>
#include <exception>
#include <boost/algorithm/string.hpp>

#include "searchengine.h"

int main(int argc, char **argv)
{
    (void)argc;
    if (argv[1]) {
        try {
            words_search::SearchEngine engine;
            engine.loadDataFromFile(argv[1]);

            std::string s;
            words_search::StringVector v;
            words_search::StringVector result;

            std::cout << "Enter words separated by spaces:\n> ";
            while (std::getline(std::cin, s)) {
                boost::split(v, s, boost::is_any_of(" "), boost::token_compress_on);

                engine.loadWords(v);
                engine.searchSentences();

                result = std::move(engine.result());
                if (!result.empty()) {
                    std::copy(begin(result), end(result),
                              std::ostream_iterator<std::string>(std::cout, "\n"));
                } else {
                    std::cout << "Sentences not found." << std::endl;
                }

                std::cout << "\nEnter words separated by spaces:\n> ";

                s.clear();
                v.clear();
            }
        } catch (std::logic_error &e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (std::exception &e) {
            std::cout << "Unknown error: " << e.what() << std::endl;
        }

        return 0;
    }

    std::cout << "First argument must be file path.\n"
                 "For example: ./words foo.txt"
              << std::endl;
    return -1;
}


# include "../includes/Utils/Utils.hpp"

void WebServer::Utils::signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    exit(signum); 
}

std::vector<string> WebServer::Utils::splitString(const string& s, const string&del = " ")
{
    std::vector<string> tokens;
    size_t start = 0;
    size_t end = s.find(del);

    while (end != string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    tokens.push_back(s.substr(start, end - start)); // Add the last token

    return tokens;
}

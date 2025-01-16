#pragma once

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <iostream>
# include <unistd.h>
# include <csignal>
# include <vector>

using std::cout;
using std::endl;
using std::string;

namespace WebServer
{
    class Utils
    {
        public:
            static  void signalHandler(int signum);
            static  std::vector<string> splitString(const string& s, const string&del);
    };
} // namespace WebServer

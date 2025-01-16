#pragma once

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <iostream>
# include <unistd.h>
# include <csignal>
# include <vector>

# include "../../includes/Logger/Logger.hpp"

using std::cout;
using std::endl;
using std::string;

/**
 * @namespace WebServer
 * @brief Contains all components related to the web server.
 */
namespace WebServer
{
       /**
     * @class Utils
     * @brief A utility class providing static helper functions for common tasks.
     *
     * The Utils class offers utility functions for tasks such as handling signals and
     * splitting strings. All methods are static, and the class cannot be instantiated.
     *
     * Key features include:
     * - Signal handling for the server.
     * - String manipulation utilities.
     */
    class Utils
    {
        private:
            Utils();
            ~Utils();
            Utils(const Utils& other);
            Utils& operator=(const Utils& other);
        public:
            static  void signalHandler(int signum);
            static  std::vector<string> splitString(const string& s, const string&del);
    };
} // namespace WebServer

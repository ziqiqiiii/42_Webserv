/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyap <jyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:42:36 by jyap              #+#    #+#             */
/*   Updated: 2025/01/16 12:54:23 by jyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
#define LOGGER_HPP

# include <pthread.h>
# include <iostream>
# include <cstdarg>
# include <stdio.h>
using std::cout;
using std::endl;
using std::cerr;
using std::string;

#define RESET			"\x1B[0m"
#define RED				"\x1B[31m"
#define LIGHT_RED		"\x1B[91m"
#define WHITE			"\x1B[37m"
#define BLINK			"\x1b[5m"
#define YELLOW			"\x1B[33m"
#define LIGHT_BLUE		"\x1B[94m"
#define CYAN			"\x1B[36m"
#define DARK_GREY		"\x1B[90m"
#define LIGHTMAGENTA	"\x1B[95m"
#define GST				8; //GMT+8 is Malaysia time offset

class Logger
{
	public:
		static void		logMsg(const char *color, const char *msg, ...);
		static string	getCurrTime();
	private:
		Logger();
		Logger(const Logger &other);
		Logger &operator=(const Logger &rhs);
};

#endif

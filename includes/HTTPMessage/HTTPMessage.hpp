#pragma once

# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h> // for functions like socket, bind, listen, accept and others
# include <netinet/in.h> // some macros for socket
# include <netdb.h> // getaddrinfo
# include <string.h> // strerror
# include <fcntl.h>
# include <iostream>
# include <unistd.h>
# include <csignal>
# include <vector>

# include "../Utils/Utils.hpp"

using std::cout;
using std::endl;
using std::string;

//MACROS 
# define CRLF "\r\n"
# define FIELD_LINE_SEPARATOR "\r\n\r\n"

/**<Struct for Key-Value pair*/
struct KeyValue {
    string key;
    string value;

    //Struct Constructor 
    KeyValue(string key, string value): key(key), value(value) {}
};

/**
 * Represents an HTTP message.
 *
 * Attributes:
 *     _start_line (string): The start line of the HTTP message (e.g., request line or status line).
 *     _headers (std::vector<KeyValue>): A collection of key-value pairs representing the HTTP headers.
 *     _body (string): The body content of the HTTP message.
 */
class HTTPMessage
{
    protected:
        string						_start_line; /**< The start line of the HTTP message. */
        std::vector<KeyValue>		_headers;  /**< A collection of key-value pairs representing the HTTP headers. */
        string						_body; /**< The body content of the HTTP message. */

	private:
        void    					_parseStartline(const string& start_line);
        void    					_parseHeaders(const string& headers);
        void    					_parseBody(const string& body);
		
    public:
        HTTPMessage();
        ~HTTPMessage();
        HTTPMessage(const HTTPMessage& src);
        HTTPMessage& operator=(const HTTPMessage& src);
        HTTPMessage(const string& message);

        //Setters
        void						setHeader(const string& name, const string& value);
        void						setBody(string body);

        //Getters
        string						getFieldName(const string& name) const;
        const std::vector<KeyValue>	getHeaders() const;
        string						getBody() const;
        string						getMessage() const;
		string						getStarline() const;

		void    					parseMessage(const string& message);

        //Exceptions
        /**
         * Exception for cases where headers are missing in the HTTP message.
         */
        class HeadersDoNotExist: public std::exception
        {
            public:
                virtual const char* what() const throw()
                {
                    return "Headers doesn't exits in HTTP message";
                }
        };

        // Abstract Method(s)
        /**
         * Abstract method for additional validation or checks.
         * Must be implemented by derived classes.
         */
        virtual void checker() = 0;
};

std::ostream&	operator<<(std::ostream& os, const std::vector<KeyValue>& headers);

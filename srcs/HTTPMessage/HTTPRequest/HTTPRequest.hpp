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
# include <cstring>
# include <typeinfo>

# include "HTTPMessage.hpp"
# include "Utils.hpp"
# include "IState.hpp"
# include "IdleState.hpp"
# include "MethodState.hpp"
# include "UriState.hpp"
# include "HttpVersionState.hpp"
# include "HeaderState.hpp"
# include "BodyState.hpp"
# include "ErrorState.hpp"
# include "DoneState.hpp"

using std::cout;
using std::endl;
using std::string;

//MACROS 
# define SP " "
#define MAX_METHOD_LEN 8
#define MAX_URI_LEN 2048
#define MAX_VERSION_LEN 16
#define MAX_HEADER_LEN 1024
#define MAX_BODY_LEN 4096
#define BUFFER_SIZE 1

class IState;

//Enum
// enum State
// {
//     idle,
//     space,
//     crlf,
//     crlfcrlf,
//     method,
//     uri,
//     httpVersion,
//     headerKey,
//     headerValue,
//     semicolon,
//     body,
//     error
// };

// const std::map<State, State> Transitions = {
//     {idle, method},
//     {method, space},
//     {uri, space},
//     {httpVersion, crlf},
//     {headerKey, semicolon},
//     {semicolon, space},
//     {headerValue, crlf},
//     {crlfcrlf, body},
//     {body, crlf}
// };

/**
 * @class HTTPRequest
 * @brief A class representing an HTTP request message.
 *
 * The HTTPRequest class is derived from the HTTPMessage class and provides additional
 * functionality specific to HTTP requests. It includes attributes and methods for handling
 * the HTTP method, request target, and HTTP version of the request message.
 */
class HTTPRequest: public HTTPMessage
{
    private:
		IState						*_current_state;
        char						_method[MAX_METHOD_LEN];  /**< The HTTP method of the request (e.g., GET, POST). */
		char						_request_target[MAX_URI_LEN]; /**< The target resource of the HTTP request (e.g., "/index.html"). */
		char						_http_version[MAX_VERSION_LEN]; /**< The HTTP version used in the request (e.g., "HTTP/1.1"). */
        char						_body[MAX_METHOD_LEN];
		char						_currentHeader[MAX_HEADER_LEN];
		size_t 						_methodIdx, _uriIdx, _versionIdx, _headerIdx, _bodyIdx;
		size_t						_fd;
		size_t						_error_code;
		size_t						_state_enum;

    public:
        HTTPRequest();
        ~HTTPRequest();
        HTTPRequest(const HTTPRequest& src);
        HTTPRequest& operator=(const HTTPRequest& src);

		void						TransitionTo(IState* state);
    	void						feedFromFd(int fd);
    	void						appendToBuffer(char* buffer, size_t& index, size_t maxLen, char c);

        //Getters
		string						getRequestMethod()	const;
		string						getRequestTarget()	const;
		string						getHttpVersion()	const;	
        string						getBody()           const;
		std::map<string, string>	getHeaders()		const;
		size_t						getFd()				const;
		size_t						getStatusEnum()		const;
		string						getCurrentHeader()	const;

		string						getStateString(int state);
		IState*						getCurrentState()	const;

		// Setters
		void							appendToMethod(char c);
		void						appendToUri(char c);
		void						appendToVersion(char c);
		void						appendToCurrentHeader(char c);
		void						appendToBody(char c);
		void						storeHeader();
		void						setErrorCode(int error_code);
		void						setStateEnum(int state);

        // Abstract Method(s)
        /**
         * Abstract method for additional validation or checks specific to HTTP requests.
         * Must be implemented by derived classes.
         */
		void						checker();
};

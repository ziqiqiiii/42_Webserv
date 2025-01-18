/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pringles <pringles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:25:41 by amaligno          #+#    #+#             */
/*   Updated: 2025/01/18 17:12:03 by pringles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPResponse.hpp"

HTTPResponse::HTTPResponse()
{
}

HTTPResponse::HTTPResponse(HTTPResponse &copy) : HTTPMessage(copy)
{
	*this = copy;
}

HTTPResponse::~HTTPResponse()
{
}

HTTPResponse	&HTTPResponse::operator=(HTTPResponse &copy)
{
	HTTPMessage::operator=(copy);
	return *this;
}

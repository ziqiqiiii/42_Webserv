# include "HeaderState.hpp"

HeaderState::HeaderState() {}

HeaderState::~HeaderState() {}

HeaderState::HeaderState(const HeaderState& tmp) { *this = tmp; }

HeaderState& HeaderState::operator=(const HeaderState& tmp)
{
    if (this != &tmp)
        *this = tmp;
    return *this;
}

void HeaderState::handle(HTTPRequest& httpRequest, char c)
{
    if (c == '\n') {
        if (httpRequest.getHeaders().empty() && httpRequest.getBody()[0] == '\0') {
            httpRequest.TransitionTo(new BodyState()); // Empty line indicates end of headers
        } else {
            httpRequest.storeHeader();
        }
    } else if (c != '\r') {
        httpRequest.appendToCurrentHeader(c);
    }
}
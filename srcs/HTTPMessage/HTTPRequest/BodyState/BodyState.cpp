# include "BodyState.hpp"

BodyState::BodyState() {}

BodyState::~BodyState() {}

BodyState::BodyState(const BodyState& tmp) { *this = tmp; }

BodyState& BodyState::operator=(const BodyState& tmp)
{
    if (this != &tmp)
        *this = tmp;
    return *this;
}

void BodyState::handle(HTTPRequest& httpRequest, char c)
{
    cout << "weeeeeeeeee" << endl;
    std::map<std::string, std::string>::const_iterator search = httpRequest.getHeaders().find("Content-Length");
    if (search == httpRequest.getHeaders().end()) {
        cout << "no body" << endl;
        return ;
    }
    if (httpRequest.getBody()[MAX_BODY_LEN - 2] != '\0') {
         // Check for body completion
        cout << "Ello " << endl;
        httpRequest.appendToBody(c);
    } else {
        httpRequest.TransitionTo(new DoneState()); // Transition to DoneState when body is complete
    }
}

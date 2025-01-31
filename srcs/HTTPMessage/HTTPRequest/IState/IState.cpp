# include "IState.hpp"

IState::~IState() {}

void    IState::setRequestContext(HTTPRequest *request) { this->_request = request; }
#if !defined(__CORE_EXT_OSTREAM_HXX__)
#define __CORE_EXT_OSTREAM_HXX__

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

std::ostream& operator<<(std::ostream& stream, const struct in_addr& v4addr);
std::ostream& operator<<(std::ostream& stream, const struct in6_addr& v6addr);

#endif

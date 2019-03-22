#include "ostream.hxx"

std::ostream& operator<<(std::ostream& stream, const struct in_addr& v4addr) {
	char buffer[16];
	inet_ntop(AF_INET, &v4addr, buffer, sizeof(buffer));

	return stream << buffer;
};

std::ostream& operator<<(std::ostream& stream, const struct in6_addr& v6addr) {
	char buffer[40];
	inet_ntop(AF_INET6, &v6addr, buffer, sizeof(buffer));

	return stream << buffer;
};


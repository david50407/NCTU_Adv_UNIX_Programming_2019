#if !defined(__NETSTAT_CONNECTION_HXX__)
#define __NETSTAT_CONNECTION_HXX__

#include <bits/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

namespace Netstat {
	template <typename T>
	struct Connection {
		T local_addr;
		int local_port;
		T remote_addr;
		int remote_port;
		pid_t pid;
		::std::string program;
	};

	struct ConnectionV4 : Connection<struct ::in_addr> {};
	struct ConnectionV6 : Connection<struct ::in6_addr> {};
}

#endif

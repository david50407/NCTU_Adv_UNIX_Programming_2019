#if !defined(__NETSTAT_OPTIONS_HXX__)
#define __NETSTAT_OPTIONS_HXX__

#include <string>
#include <optional>

namespace Netstat {
	struct Options {
		bool help = false;
		bool only_tcp = false;
		bool only_udp = false;
		::std::optional<::std::string> search_command = ::std::nullopt;
	};
}

#endif

#if !defined(__NETSTAT_APPLICATION_HXX__)
#define __NETSTAT_APPLICATION_HXX__

#include "options.hxx"
#include "connection_parser.hxx"

namespace Netstat {
	class Application {
	private:
		struct Options options;
	
	public:
		void run(int, char **);

	private:
		void print_help();
		void parse_args(int, char **);
		template <typename T>
		void list_connection(ConnectionParser<T> &, const char *);
	};
}

#endif

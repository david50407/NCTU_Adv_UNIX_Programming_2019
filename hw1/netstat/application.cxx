#include <getopt.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <regex>
#include "application.hxx"
#include "connection.hxx"
#include "connection_iterator.hxx"

const int ADDR_LENGTH = 30;

namespace Netstat {
	void Application::run(int argc, char **argv) {
		parse_args(argc, argv);

		if (options.help) {
			print_help();

			return;
		}

#define render($, $$) { \
		if (options.only_##$) { \
			::std::cout << "List of " #$$ " connections:" << ::std::endl; \
			::std::cout << ::std::setw(7) << ::std::left << "Proto" \
				<< ::std::setw(ADDR_LENGTH) << ::std::left << "Local Address" \
				<< ::std::setw(ADDR_LENGTH) << ::std::left << "Foreign Address" \
				<< "PID/Program" \
				<< ::std::endl; \
			ConnectionV4Iterator $##v4("/proc/net/" #$); \
			ConnectionV6Iterator $##v6("/proc/net/" #$ "6"); \
			list_connection($##v4, #$); \
			list_connection($##v6, #$ "6"); \
			::std::cout << ::std::endl; \
		} \
}
		render(tcp, TCP);
		render(udp, UDP);
#undef render
	}

	void Application::print_help() {
		::std::cout << "Usage: ./hw1 [-t|--tcp] [-u|--udp] [filter-string]" << ::std::endl;
		::std::cout << "    -t, --tcp    List only TCP connections" << ::std::endl;
		::std::cout << "    -u, --udp    List only UDP connections" << ::std::endl;
		::std::cout << "    -h, --help   Show this message" << ::std::endl;
		::std::cout << ::std::endl;
	}

	void Application::parse_args(int argc, char **argv) {
		const char *short_opts = "tuh";
		const struct ::option long_opts[] = {
			{ "tcp", 0, nullptr, 't' },
			{ "udp", 0, nullptr, 'u' },
			{ "help", 0, nullptr, 'h' },
			{ nullptr, 0, nullptr, 0 }
		};

		while (true) {
			const auto opt = ::getopt_long(argc, argv, short_opts, long_opts, nullptr);

			if (opt == -1) {
				break;
			}

			switch (opt) {
				case 't':
					options.only_tcp = true;
					break;
				case 'u':
					options.only_udp = true;
					break;
				case 'h':
				case '?':
				default:
					options.help = true;
			}
		}

		if (!options.only_tcp && !options.only_udp) {
			options.only_tcp = options.only_udp = true;
		}

		if (::optind != argc) {
			options.search_command = ::std::string(argv[optind]);
		}
	}

 	template <typename T>
	void Application::list_connection(ConnectionIterator<T> &iter, const char *type) {
		for (; !iter.eof(); ++iter) {
			auto connection = *iter;

			if (options.search_command) {
				if (connection.pid == 0) {
					continue;
				}

				if (!::std::regex_search(connection.program, ::std::regex{*options.search_command})) {
					continue;
				}
			}

			auto local_builder = ::std::stringstream(),
					 remote_builder = ::std::stringstream();
#define build($) { \
			$##_builder << connection.$##_addr << ':'; \
			if (connection.$##_port == 0) { \
				$##_builder << '*'; \
			} else { \
				$##_builder << connection.$##_port; \
			} \
}
			build(local);
			build(remote);
#undef build

			::std::cout << ::std::setw(7) << ::std::left << type
				<< ::std::setw(ADDR_LENGTH) << ::std::left << local_builder.str()
				<< ::std::setw(ADDR_LENGTH) << ::std::left << remote_builder.str();
			if (connection.pid == 0) {
				::std::cout << '-';
			} else {
				::std::cout << connection.pid << '/' << connection.program;
			}
			::std::cout << ::std::endl;
		}
	}
}

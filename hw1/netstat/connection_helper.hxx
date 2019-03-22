#if !defined(__NETSTAT_CONNECTION_HELPER_HXX__)
#define __NETSTAT_CONNECTION_HELPER_HXX__

#include <bits/types.h>
#include <cctype>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace fs = ::std::filesystem;

namespace Netstat {
	class ConnectionHelper {
	private:
		static bool check_proc_pid(const ::std::string filename) {
			return ::std::all_of(filename.begin(), filename.end(),
					[](char c) { return ::std::isdigit(c); });
		}

	public:
		static ::pid_t get_pid_from_inode(const int inode) {
			for (auto &proc : fs::directory_iterator("/proc")) {
				const auto proc_name = proc.path().filename().string();
				if (!proc.is_directory() || !check_proc_pid(proc_name)) {
					continue;
				}

				try {
					for (auto &fd : fs::directory_iterator(proc.path() / "fd")) {
						if (!fd.is_symlink()) {
							continue;
						}

						auto fd_real = fs::read_symlink(fd.path());
						if (fd_real.string().compare(0, 8, "socket:[") == 0) { // socket:[inode]
							int fd_inode;
							::sscanf(fd_real.c_str() + 8, "%d", &fd_inode);

							if (fd_inode == inode) {
								return ::std::stoi(proc_name);
							}
						}
					}
				} catch (const fs::filesystem_error err) {
				}
			}

			return 0;
		}

		static ::std::string get_program_from_pid(const pid_t pid) {
			if (pid == 0) {
				return "";
			}

			const fs::path proc = "/proc";
			::std::ifstream stream(proc / ::std::to_string(pid) / "cmdline");
			::std::string program(::std::istreambuf_iterator<char>{stream}, {});

			auto endIt = program.end();
			for (auto it = program.begin(); it != program.end(); ++it) {
				if (*it == '\0') {
					if (endIt == program.end()) {
						endIt = it;
					}
					*it = ' ';
				}
			}
			program.replace(
					program.begin(), endIt,
					(fs::path{program.begin(), endIt}).filename()
			);

			return program;
		}
	};
}

#endif

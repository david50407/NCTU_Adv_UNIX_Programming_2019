#include <cstdio>
#include "connection_parser.hxx"
#include "connection_helper.hxx"

namespace Netstat {
	using Helper = ConnectionHelper;

	template<>
	void ConnectionParser<ConnectionV4>::parse() {
		if (connection != nullptr) {
			delete connection;
		}
		connection = new ConnectionV4();

		char buffer[4096 + 1];
		stream.getline(buffer, sizeof(buffer));

		int inode;
		::sscanf(buffer, "%*s%x:%x%x:%x%*s%*s%*s%*s%*s%*s%d",
				&connection->local_addr.s_addr, &connection->local_port,
				&connection->remote_addr.s_addr, &connection->remote_port,
				&inode);

		connection->pid = Helper::get_pid_from_inode(inode);
		connection->program = Helper::get_program_from_pid(connection->pid);
	}

	template<>
	void ConnectionParser<ConnectionV6>::parse() {
		if (connection != nullptr) {
			delete connection;
		}
		connection = new ConnectionV6();

		char buffer[4096 + 1];
		stream.getline(buffer, sizeof(buffer));

		char local_address[40], remote_address[40];
		int inode;
		::sscanf(buffer, "%*s%s%s%*s%*s%*s%*s%*s%*s%d",
				local_address, remote_address, &inode);
		local_address[32] = remote_address[32] = '\0';
		for (int i = 24; i >= 0; i -= 8) {
			::sscanf(&local_address[i], "%x", &connection->local_addr.s6_addr32[i / 8]);
			::sscanf(&remote_address[i], "%x", &connection->remote_addr.s6_addr32[i / 8]);
			local_address[i] = remote_address[i] = '\0';
		}
		::sscanf(local_address + 33, "%x", &connection->local_port);
		::sscanf(remote_address + 33, "%x", &connection->remote_port);

		connection->pid = Helper::get_pid_from_inode(inode);
		connection->program = Helper::get_program_from_pid(connection->pid);
	}
}

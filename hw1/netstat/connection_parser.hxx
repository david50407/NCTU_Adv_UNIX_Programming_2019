#if !defined(__NETSTAT_CONNECTION_ITERATOR_HXX__)
#define __NETSTAT_CONNECTION_ITERATOR_HXX__

#include <iterator>
#include <filesystem>
#include <fstream>
#include <string>
#include <limits>
#include "connection.hxx"

namespace Netstat {
	template <typename T>
	class ConnectionParser {
	public:
		class iterator {
			using iterator_category = ::std::input_iterator_tag;
			using value_type = T;
			using difference_type = int;
			using pointer = T*;
			using reference = T&;
		private:
			ConnectionParser *parser = nullptr;
		public:
			explicit iterator(ConnectionParser *_parser = nullptr) : parser(_parser) {}
			iterator& operator++() { parser->parse(); return *this; }
			iterator operator++(int) { parser->parse(); return this; }
			bool operator==(iterator other) const {
				if (parser == nullptr && other.parser == nullptr)
					return true;
				if (parser == nullptr && other.parser->eof())
					return false;
				return other.parser == nullptr && parser->eof();
			}
			bool operator!=(iterator other) const { return !(*this == other); }
			reference operator*() const { return *parser->connection; }
		};

	private:
		const iterator always_eof{nullptr};
		::std::ifstream stream;
		T *connection = nullptr;

	private:
		void parse();
	public:
		ConnectionParser(const char *filename) : ConnectionParser(::std::filesystem::path{filename}) {}
		ConnectionParser(const ::std::string filename) : ConnectionParser(::std::filesystem::path{filename}) {}
		ConnectionParser(const ::std::filesystem::path filename) : stream(filename) {
			stream.ignore(::std::numeric_limits<::std::streamsize>::max(), stream.widen('\n'));
			parse();
		}
		iterator begin() { return iterator(this); }
		iterator end() { return always_eof; }
		bool eof() { return stream.eof(); }
	};

	typedef ConnectionParser<ConnectionV4> ConnectionV4Parser;
	typedef ConnectionParser<ConnectionV6> ConnectionV6Parser;
}

#endif

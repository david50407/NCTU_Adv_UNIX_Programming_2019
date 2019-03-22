#if !defined(__NETSTAT_CONNECTION_ITERATOR_HXX__)
#define __NETSTAT_CONNECTION_ITERATOR_HXX__

#include <iterator>
#include <fstream>
#include <string>
#include <limits>
#include "connection.hxx"

namespace Netstat {
	template <typename T>
	class ConnectionIterator : ::std::iterator<::std::input_iterator_tag, T> {
	private:
		::std::ifstream stream;
		T *connection = nullptr;

	private:
		void parse();
	public:
		explicit ConnectionIterator(const ::std::string filename) : ConnectionIterator(filename.c_str()) {}
		explicit ConnectionIterator(const char *filename) {
			stream.open(filename);
			stream.ignore(::std::numeric_limits<::std::streamsize>::max(), stream.widen('\n'));
			parse();
		}

		ConnectionIterator& operator++() { parse();	return *this;	}
		ConnectionIterator operator++(int) { parse(); return this; }
		bool operator==(ConnectionIterator other) const { return false; }
		bool operator!=(ConnectionIterator other) const { return !(*this == other); }
		T operator*() const { return *connection; }
		bool eof() const { return stream.eof(); }
	};

	typedef ConnectionIterator<ConnectionV4> ConnectionV4Iterator;
	typedef ConnectionIterator<ConnectionV6> ConnectionV6Iterator;
}

#endif

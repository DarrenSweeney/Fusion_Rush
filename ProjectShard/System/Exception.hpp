#ifndef _GAMESPARKSRT_EXCEPTION_HPP_
#define _GAMESPARKSRT_EXCEPTION_HPP_

#include <stdexcept>
#include <string>
#include <list>
#include <ostream>
#include <iostream>
#include <sstream>

namespace System {

	class Exception : public std::runtime_error
	{
		public:
			Exception(const std::string& what) : std::runtime_error(what), typeName("System.Exception") {}
			Exception(const std::string& what, const std::string& typeName_) : std::runtime_error(what), typeName(typeName_) {}

			void PushFrame(const std::string& file, int line, const std::string& function)
			{
				callStack.push_back(Frame(file, line, function));
			}

			friend std::ostream& operator << (std::ostream& os, const Exception& e)
			{
				os << "Traceback (most recent call last):" << std::endl;
				for(const auto& frame : e.callStack)
				{
					os << "  " << frame << std::endl;
				}
				os << e.typeName << ": " << e.what() << std::endl;

				return os;
			}

			std::string Format() const
			{
				std::stringstream ss;
				ss << *this;
				return ss.str();
			}
		private:
			const std::string typeName;

			struct Frame
			{
				Frame(const std::string& file_, const int line_, const std::string function_)
				:file(file_), line(line_), function(function_) {}

				const std::string file;
				const int line = -1;
				const std::string function;

				friend std::ostream& operator << (std::ostream& os, const Frame& frame)
				{
					os << frame.file << ":" << frame.line << " in " << frame.function;
					return os;
				}
			};
			typedef std::list<Frame> CallStack;
			CallStack callStack;
	};

} /* namespace System */

#endif /* _GAMESPARKSRT_EXCEPTION_HPP_ */

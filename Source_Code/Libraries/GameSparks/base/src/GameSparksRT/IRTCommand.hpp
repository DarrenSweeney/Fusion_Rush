#ifndef _GAMESPARKSRT_IRTCOMMAND_HPP_
#define _GAMESPARKSRT_IRTCOMMAND_HPP_

namespace GameSparks { namespace RT {

	class IRTCommand
	{
		public:
			virtual void Execute () =0;
			virtual ~IRTCommand() {}

			virtual class AbstractResult* asAbstractResult() { return nullptr; }
		private:
	};

}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_IRTCOMMAND_HPP_ */

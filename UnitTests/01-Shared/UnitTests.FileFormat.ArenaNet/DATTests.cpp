#include "CppUnitTest.h"
#include "../../../Libraries/01-Shared/Elysium.FileFormat.ArenaNet.GuildWars/DATStream.hpp"

using namespace Elysium::FileFormat::ArenaNet::GuildWars::DAT;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsFileFormatArenaNet
{
	TEST_CLASS(DATTests)
	{
	public:

		TEST_METHOD(ReadFullFile)
		{
			DATStream Stream = DATStream(u8"");
		}
	};
}

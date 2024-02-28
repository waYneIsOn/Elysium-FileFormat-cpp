#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.FileFormat.ArenaNet.GuildWars/DATStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.FileFormat.ArenaNet.GuildWars/MFTEntry.hpp"
#include "../../../Libraries/01-Shared/Elysium.FileFormat.ArenaNet.GuildWars/MFTHeader.hpp"
#include "../../../Libraries/01-Shared/Elysium.FileFormat.ArenaNet.GuildWars/Root.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.IO/IOException.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"

using namespace Elysium::FileFormat::ArenaNet::GuildWars::DAT;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsFileFormatArenaNet
{
	TEST_CLASS(DATTests)
	{
	public:
		TEST_METHOD(ValidateSizes)
		{
			if (sizeof(Root) != 0x20)
			{
				Assert::Fail();
			}

			if (sizeof(MFTHeader) != 0x18)
			{
				Assert::Fail();
			}

			if (sizeof(MFTEntry) != 0x18)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(ReadNewFile)
		{
			Assert::Fail();
		}

		TEST_METHOD(ReadImageFile)
		{
			Assert::Fail();
		}

		TEST_METHOD(ReadFullFile)
		{
			try
			{
				DATStream Stream = DATStream(u8"TestFiles\\UnitTests.FileFormat.ArenaNet\\Gw.dat");
				const bool ReadRootBlockResult = Stream.ReadRootBlock();
				if (!ReadRootBlockResult)
				{
					Assert::Fail(L"Input is not a valid Guild Wars data-file!");
				}

				const bool ReadMainFileTableHeaderResult = Stream.ReadMainFileTableHeader();
				if (!ReadMainFileTableHeaderResult)
				{
					Assert::Fail(L"Main file table is not valid!");
				}

				const bool ReadMainFileTableEntriesResult = Stream.ReadMainFileTableEntries();
				if (!ReadMainFileTableEntriesResult)
				{
					Assert::Fail(L"Main file table entries are not valid!");
				}
				
				Elysium::Core::uint32_t Index = 0;
				const Elysium::Core::Template::Container::Vector<Elysium::FileFormat::ArenaNet::GuildWars::DAT::MFTEntry>& Entries =
					Stream.GetEntries();
				for (Elysium::Core::Template::Container::Vector<Elysium::FileFormat::ArenaNet::GuildWars::DAT::MFTEntry>::ConstIterator Iterator = Entries.GetBegin();
					Iterator != Entries.GetEnd(); ++Iterator, ++Index)
				{
					// skip all "reserved" blocks for now
					if (Index < 15)
					{
						continue;
					}

					Stream.ReadEntryContent(*Iterator, Index);
				}
			}
			catch (const Elysium::Core::IO::IOException& ex)
			{
				Elysium::Core::String ErrorCode = Elysium::Core::Template::Text::Convert<char>::ToString(ex.GetErrorCode());

				Logger::WriteMessage((char*)&ex.GetExceptionMessage()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage(&ErrorCode[0]);
				Logger::WriteMessage("\r\n");
				Logger::WriteMessage((char*)&ex.GetStackTrace()[0]);
				Logger::WriteMessage("\r\n");
				Assert::Fail();
			}
		}
	};
}

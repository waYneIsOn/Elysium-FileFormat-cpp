#include "CppUnitTest.h"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.FileFormat.Imaging.Jpg/JpgReader.hpp"

using namespace Elysium::Core::IO;
using namespace Elysium::FileFormat::Imaging::Jpg;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::FileFormat::Imaging
{
	TEST_CLASS(JpgTests)
	{
	public:

		TEST_METHOD(ReadSomeFile)
		{
			FileStream InputStream = FileStream(u8"TestFiles\\Elysium.FileFormat.Imaging\\Some Image.jpg", FileMode::Open, FileAccess::Read, FileShare::None);
			JpgReader Reader = JpgReader(InputStream);

			while (Reader.ReadSegment())
			{
				int lksjdf = 45;
			}
		}
	};
}

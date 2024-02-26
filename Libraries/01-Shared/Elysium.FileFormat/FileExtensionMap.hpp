/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_FILEEXTENSIONMAP
#define ELYSIUM_FILEFORMAT_FILEEXTENSIONMAP

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_FILEFORMAT_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_FILEFORMAT_FILECATEGORY
#include "FileCategory.hpp"
#endif

namespace Elysium::FileFormat
{
	class ELYSIUM_FILE_FORMAT_API FileExtensionMap final
	{
	public:
		FileExtensionMap() = delete;
		FileExtensionMap(const FileExtensionMap& Source) = delete;
		FileExtensionMap(FileExtensionMap&& Right) = delete;
		~FileExtensionMap() = delete;
	private:
		//static const map<string, FileCategory> _ExtensionCategoryMap;
	};
}
#endif

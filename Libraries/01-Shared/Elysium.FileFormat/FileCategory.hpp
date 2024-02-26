/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_FILECATEGORY
#define ELYSIUM_FILEFORMAT_FILECATEGORY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Integer.hpp"
#endif

namespace Elysium::FileFormat
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class FileCategory : Elysium::Core::uint32_t
#elif defined(__ANDROID__)
	enum class FileCategory
#else
#error "undefined os"
#endif
	{
		/*
		// https://fileinfo.com/filetypes/common

		Text,

		Data,

		Audio,

		Video,

		3dImage,

		RasterImage,

		VectorImage,

		PageLayout,

		Spreadsheet,

		Database,

		Executable,

		Game,

		Cad,

		Gis,

		Web,

		Plugin,

		Font,

		System,

		Settings,

		Encoded,

		Compressed,

		DiskImage,

		Developer,

		Backup,

		Misc/Unspecified,
		*/
		/*
		// https://en.wikipedia.org/wiki/List_of_file_formats

		Archive = 0,

		CeramicsGlazeRecipes = 1,

		ComputerAidedDesign = 2,

		Database = 3,

		DesktopPublishing = 4,

		Document = 5,

		FinancialRecord = 6,

		Font = 7,

		GeographicInformationSystem = 8,

		GeographicInformationOrganizer = 9,

		Graphics = 10,
		ColorPalette,
		ColorManagement,
		RasterGraphics,
		VectorGraphics,
		3dGraphics,

		Link,

		Mathematical,

		ObjectCode,

		Executable,

		DynamicLinkedLibrary,

		PageDescription,

		PersonalInformationManager,

		Presentation,

		ProjectManagement,

		ReferenceManagement,

		ScientificData,

		ProgrammingLanguageAndScript,

		Security,

		SingleData,

		SoundAndMusic,

		Playlist,

		AudioEditingAndMusicProduction,

		RecordedTelevisionFormat,

		SourceCode,

		Spreadsheet,

		TabulatedData,

		Video,

		VideoGameData,

		VideoGameStorageMedia,

		VirtualMachine,

		WebPage,

		MarkupLanguage,

		Other,
		Cursor,
		*/
	};
}
#endif

#pragma once

using namespace System;

namespace tex_conv_core {
	
	public ref class environment {
	public:
		static const bool init( System::String^ path );
		static const bool free();

		static void enum_formats( System::Collections::Generic::IList<System::String^>^ formats );
	};

	public ref class cWSFileDesc {
	protected:
		System::String^ m_name;
		System::String^ m_path;
	public:
		
	};

	public ref class workspace {
	public:
		static void clear();
		static const bool load( System::String^ path );
		static const bool save( System::String^ path );

		static const bool is_new();
		static const bool is_loaded();
		static const bool is_saved();

		static System::String^ root_path();

		static const int enum_files( System::Collections::Generic::IList<cWSFileDesc^>^ files );
		static void enum_formats( System::Collections::Generic::IList<System::String^>^ formats );
	};
}; 
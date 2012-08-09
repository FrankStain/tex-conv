#pragma once

using namespace System;

struct sFileDesc;

namespace tex_conv_core {
	
	public ref class environment {
	public:
		static const bool init( System::String^ path );
		static const bool free();

		static void enum_formats( System::Collections::Generic::IList<System::String^>^ formats );
	};

	public ref class cWSFileDesc {
	protected:
		sFileDesc* m_file_desc;

	public:
		cWSFileDesc( sFileDesc* );
		~cWSFileDesc();

		System::String^ name();
		System::String^ formated_name( System::String^ format );

		System::String^ file_name();
		System::String^ formated_file_name( System::String^ format );
		
		const bool enabled( System::String^ format );
		void set_enabled( System::String^ format, const bool flag );
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
		static const bool add_file( System::String^ file_path );
		static const bool remove_file( System::String^ file_path );
		
		static void enum_formats( System::Collections::Generic::IList<System::String^>^ formats );
		static const bool add_format( System::String^ format );
		static const bool remove_format( System::String^ format );
	};
}; 
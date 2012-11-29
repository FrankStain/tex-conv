#include "file_system.h"

namespace file_system {
	const bool file_exists( const string& file_name ){
		return INVALID_FILE_ATTRIBUTES != GetFileAttributes( file_name.c_str() );
	};

	const bool path_exists( const string& path_name ){
		const DWORD attr = GetFileAttributes( path_name.c_str() );
		return ( INVALID_FILE_ATTRIBUTES != attr ) && ( FILE_ATTRIBUTE_DIRECTORY & attr );
	};

	const bool delete_file( const string& path_name ){
		return NULL != DeleteFile( path_name.c_str() );
	};

	const bool delete_path( const string& path_name ){
		return NULL != RemoveDirectory( path_name.c_str() );
	};

	void find_files( const string& path, files_t* files, dirs_t* dirs, const bool sub_dirs, const bool abs_path ){
		string base_dir = "";
	
		WIN32_FIND_DATA file_data;
		HANDLE files_handle = FindFirstFile( path.c_str(), &file_data );
		if( INVALID_HANDLE_VALUE == files_handle ){
			return;
		};

		if( abs_path ){
			path_t fd = path;
			base_dir = fd.path();
			if( !base_dir.size() ){
				char tmp_path[MAX_PATH];
				GetCurrentDirectory( MAX_PATH, tmp_path );
				base_dir = tmp_path;
			};
			base_dir += "\\";
		};

		do{
			if( !strcmp( file_data.cFileName, "." ) || !strcmp( file_data.cFileName, ".." ) )
			{
				continue;
			};

			if( FILE_ATTRIBUTE_DIRECTORY & file_data.dwFileAttributes ){
				if( dirs ){
					dirs->push_back( ( abs_path )? base_dir + file_data.cFileName : file_data.cFileName );
				};

				if( sub_dirs ){
					path_t fd = path;
					find_files( fd.path() + path_separator + file_data.cFileName + path_separator + fd.file_name(), files, dirs, sub_dirs, abs_path );
				};
			}else if( files ){
				files->push_back( ( abs_path )? base_dir + file_data.cFileName : file_data.cFileName );
			};
		}while( FindNextFile( files_handle, &file_data ) );
		FindClose( files_handle );
	};

	void find( files_t& files, const string& path, const bool sub_dirs, const bool absolute_path ){
		find_files( path, &files, NULL, sub_dirs, absolute_path );
	};

	void find( dirs_t& dirs, const string& path, const bool sub_dirs, const bool absolute_path ){
		find_files( path, NULL, &dirs, sub_dirs, absolute_path );
	};
};

#include "file_system.h"

namespace file_system {
	const bool file_exists( const string& file_name ){
		return INVALID_FILE_ATTRIBUTES != GetFileAttributes( file_name.c_str() );
	};

	const bool path_exists( const string& path_name ){
		const DWORD attr = GetFileAttributes( path_name.c_str() );
		return ( INVALID_FILE_ATTRIBUTES != attr ) && ( FILE_ATTRIBUTE_DIRECTORY & attr );
	};

	const bool make_folder( const string& path_name ){
		list<string> names;
		string base_folder;
		string path	= path_name;
		
		if( path_separator[0] == path_name.back() )
		{
			path.erase( path.size() - 1 );
		};

		size_t lpos	= 0;
		size_t pos	= path.find( path_separator );
		while( string::npos != pos ){
			names.push_back( path.substr( lpos, pos - lpos ) );
			lpos	= pos + 1;
			pos		= path.find( path_separator, lpos );
		};

		if( lpos < path.size() ){
			names.push_back( path.substr( lpos ) );
		};

		if( !names.size() ){
			return false;
		};

		if( 0 < strchr( names.front().c_str(), ':' ) ){
			base_folder = names.front() + path_separator;
			names.pop_front();
		}else{
			char tmp_path[MAX_PATH];
			GetCurrentDirectory( MAX_PATH, tmp_path );
			base_folder = tmp_path;
			base_folder += path_separator;
		};

		if( !path_exists( base_folder ) ){
			return false;
		};

		while( names.size() ){
			base_folder += names.front();
			switch( CreateDirectory( base_folder.c_str(), NULL ) ){
				case ERROR_PATH_NOT_FOUND: return false;
			};

			base_folder += path_separator;
			names.pop_front();
		};

		return true;
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

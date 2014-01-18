#include "core.h"
#include "operator.h"
#include "file_system.h"

extern "C"
{
	#include "png.h"
};

#define PNG_BYTES_TO_CHECK 8

namespace dll {
	const char					op_name[]		= "PNG";
	const char					op_desc[]		= "Portable Network Graphics";
	const char					op_ext[]		= "png";
	plugin::operator_options_t	op_type			= plugin::OPER_IMPORT | plugin::OPER_EXPORT;

	plugin::options_desc_t		op_imp_desc			= {
		NULL, 0
	};

	plugin::options_desc_t		op_exp_desc			= {
		NULL, 0
	};
		
	png_operator_t::png_operator_t(){
	
	};

	png_operator_t::~png_operator_t(){
	
	};

	const char* png_operator_t::name(){
		return op_name;
	};

	const plugin::operator_options_t png_operator_t::type(){
		return op_type;
	};
	
	const char* png_operator_t::file_ext(){
		return op_ext;
	};

	const char* png_operator_t::file_desc(){
		return op_desc;
	};

	const bool png_operator_t::validate_file( const char* file_name ){
		if( !file_name || !*file_name || !file_system::file_exists( file_name ) ){
			return false;
		};

		file_system::file_mapping_t file;
		if( !file.construct( file_name ) ){
			return false;
		};

		png_byte* file_sign;
		if( !file.map_view( file_sign, 0, PNG_BYTES_TO_CHECK ) ){
			return false;
		};

		if( png_sig_cmp( file_sign, 0, PNG_BYTES_TO_CHECK ) ){
			return false;
		};

		return true;
	};

	void* png_image_alloc( png_struct* png, size_t size ){
		return new char[size];
	};

	void png_image_free( png_struct* png, void * ptr ){
		delete[] (char*)ptr;
	};

	void png_image_warn( png_structp png_ptr, png_const_charp message ) {};
	void png_image_error( png_structp png_ptr, png_const_charp message ) {};

	struct sPngFileStruct {
		char*					m_memory;
		file_system::size64_t	m_size;
		file_system::size64_t	m_position;
	};

	void png_image_read( png_struct* png, png_byte* ptr, png_size_t size ){
		sPngFileStruct& stream = *(sPngFileStruct*)png_get_io_ptr( png );
		const size_t str_size = ( size > ( stream.m_size - stream.m_position ) )? stream.m_size - stream.m_position : size;
		memcpy( ptr, &(stream.m_memory[ stream.m_position ]), str_size );
		stream.m_position += str_size;
	};

	void png_image_write( png_struct* png, png_byte* ptr, png_size_t size ){
		file_system::file_t* fd = (file_system::file_t*)png_get_io_ptr( png );
		fd->write( ptr, size );
	};

	void png_image_flush( png_struct* png ){
		//((file_system::file_t*)png_get_io_ptr( png ))->resize( 0 );
	};

	const bool png_operator_t::load( const char* file_name, plugin::image_desc_t* dest, plugin::option_t* options ){
		if( !file_name || !*file_name || !file_system::file_exists( file_name ) ){
			return false;
		};

		file_system::file_mapping_t file;
		if( !file.construct( file_name ) ){
			return false;
		}else{
			png_byte* file_sign;
			if( !file.map_view( file_sign, 0, PNG_BYTES_TO_CHECK ) ){
				return false;
			};

			if( png_sig_cmp( file_sign, 0, PNG_BYTES_TO_CHECK ) ){
				return false;
			};

			file.close_view( file_sign );
		};

		png_structp png_ptr = png_create_read_struct_2(
			PNG_LIBPNG_VER_STRING, NULL, 
			png_image_error, png_image_warn,
			NULL, png_image_alloc, png_image_free
		);

		if( !png_ptr ){
			return false;
		};

		png_infop info_ptr = png_create_info_struct( png_ptr );
		if( info_ptr == NULL ){
			png_destroy_read_struct( &png_ptr, 0, 0 );
			return false;
		};

		sPngFileStruct file_memory;
		file.map_view( file_memory.m_memory, 0, 0 );
		file_memory.m_position = 0;
		file_memory.m_size = file.size();

		png_set_read_fn( png_ptr, (void*)&file_memory, png_image_read );
		png_read_png( png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING, 0 );

		png_uint_32	png_width;
		png_uint_32	png_height;
		int			png_bit_type;
		int			png_color_type;
		int			png_interlace_type;

		png_get_IHDR(
			png_ptr, info_ptr,
			&png_width, &png_height, &png_bit_type, &png_color_type, &png_interlace_type,
			0, 0
		);

		png_byte** png_buf = png_get_rows( png_ptr, info_ptr );
		const png_uint_32 row_length = png_get_rowbytes( png_ptr, info_ptr );
		bool result = false;

		switch( png_bit_type ){
			case 8:{
				dest->set_sizes( png_width, png_height );
				for( png_uint_32 row_id = 0; png_height > row_id; row_id++ ){
					switch( info_ptr->channels ){
						case 3:{
							plugin::pixel_desc_t* dst_pix = dest->row( row_id );
							for( png_byte* png_pix = png_buf[ row_id ]; ( png_buf[ row_id ] + row_length ) > png_pix; png_pix += 3, dst_pix++ ){
								dst_pix->m_alpha		= 255;
								dst_pix->m_red		= png_pix[0];
								dst_pix->m_green		= png_pix[1];
								dst_pix->m_blue		= png_pix[2];
							};
						}break;
						default:
							memcpy( dest->row( row_id ), png_buf[ row_id ], row_length );
					};
				};

				result = true;
			}break;
		};

		png_destroy_read_struct( &png_ptr, &info_ptr, 0 );

		return true;
	};

	const bool png_operator_t::save( const char* file_name, plugin::image_desc_t* source, plugin::option_t* options ){
		file_system::file_t file;

		file.construct( file_name, GENERIC_WRITE, CREATE_ALWAYS );
		if( !file.is_ready() ){
			return false;
		};

		png_structp png_ptr = png_create_read_struct_2(
			PNG_LIBPNG_VER_STRING, NULL, 
			png_image_error, png_image_warn,
			NULL, png_image_alloc, png_image_free
		);

		if( !png_ptr ){
			return false;
		};

		png_infop info_ptr = png_create_info_struct( png_ptr );
		if( info_ptr == NULL ){
			png_destroy_read_struct( &png_ptr, 0, 0 );
			return false;
		};

		png_set_write_fn( png_ptr, (void*)&file, png_image_write, png_image_flush );

		png_set_IHDR(
			png_ptr, info_ptr,
			source->width(), source->height(), 8,
			PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, 
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE
		);

		png_write_info( png_ptr, info_ptr );

		png_byte** rows = new png_byte*[ source->height() ];
		for( int rd = 0; source->height() > rd; rd++ ){
			rows[ rd ] = (png_byte*)source->row( rd );
		};

		png_write_image( png_ptr, rows );
		delete[] rows;

		png_write_end( png_ptr, NULL );

		file.close();
		return true;
	};

	const plugin::options_desc_t* png_operator_t::import_options() const {
		return &op_imp_desc;
	};

	const plugin::options_desc_t* png_operator_t::export_options() const {
		return &op_exp_desc;
	};
};

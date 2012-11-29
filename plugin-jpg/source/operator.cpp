#include "operator.h"
#include "file_system.h"

extern "C"
{	
	#define XMD_H 1
	#define HAVE_BOOLEAN 1

	#include "jpeglib.h"
	#include "jinclude.h"
	#include "jerror.h"
};

struct jpeg_jump_error_mgr 
{
    struct jpeg_error_mgr manager;
    jmp_buf jumpers;
};

METHODDEF(void) jpg_error_exit( j_common_ptr cinfo )
{
	(*cinfo->err->output_message)( cinfo );
	jpeg_destroy( cinfo );
	longjmp( ( (jpeg_jump_error_mgr*)cinfo->err )->jumpers, 1 );
};

METHODDEF(void) jpg_output_message( j_common_ptr cinfo )
{
	char buffer[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message)( cinfo, buffer );
};

namespace dll {
	const char					op_name[]		= "JPEG";
	const char					op_desc[]		= "Jpeg image";
	const char					op_ext[]		= "jpg";
	plugin::operator_options_t	op_type			= plugin::OPER_IMPORT;

	plugin::options_desc_t		op_imp_desc			= {
		NULL, 0
	};

	plugin::options_desc_t		op_exp_desc			= {
		NULL, 0
	};
		
	jpg_operator_t::jpg_operator_t(){

	};

	jpg_operator_t::~jpg_operator_t(){
	
	};

	const char* jpg_operator_t::name(){
		return op_name;
	};

	const plugin::operator_options_t jpg_operator_t::type(){
		return op_type;
	};
	
	const char* jpg_operator_t::file_ext(){
		return op_ext;
	};

	const char* jpg_operator_t::file_desc(){
		return op_desc;
	};

	const bool jpg_operator_t::validate_file( const char* file_name ){
		if( !file_name || !*file_name || !file_system::file_exists( file_name ) ){
			return false;
		};

		file_system::file_mapping_t file;
		if( !file.construct( file_name ) ){
			return false;
		};

		uint8_t* file_memory = NULL;
		if( !file.map_view( file_memory, 0, 0 ) ){
			return false;
		};
		
		jpeg_decompress_struct cinfo = { 0 };
		jpeg_jump_error_mgr jerr;

		if( setjmp( jerr.jumpers ) )
		{
			jpeg_destroy_decompress( &cinfo );
			return false;
		};

		cinfo.err = jpeg_std_error( (jpeg_error_mgr*)&jerr );
		jerr.manager.error_exit = jpg_error_exit;
		jerr.manager.output_message = jpg_output_message;

		jpeg_create_decompress( &cinfo );
		jpeg_mem_src( &cinfo, file_memory, file.size() );

		const bool result = JPEG_HEADER_OK == jpeg_read_header( &cinfo, true );

		jpeg_destroy_decompress( &cinfo );
		return result;
	};

	const bool jpg_operator_t::load( const char* file_name, plugin::image_desc_t* dest, plugin::option_t* options ){
		if( !file_name || !*file_name || !file_system::file_exists( file_name ) ){
			return false;
		};

		file_system::file_mapping_t file;
		if( !file.construct( file_name ) ){
			return false;
		};

		uint8_t* file_memory = NULL;
		if( !file.map_view( file_memory, 0, 0 ) ){
			return false;
		};
		
		bool result = false;
		uint32_t row_stride;
		uint32_t pixelcount;
		uint32_t memcount;
		uint8_t* buf;
		JSAMPARRAY buffer = &buf;
		jpeg_decompress_struct cinfo = { 0 };
		jpeg_jump_error_mgr jerr;

		if( setjmp( jerr.jumpers ) )
		{
			jpeg_destroy_decompress( &cinfo );
			return false;
		};

		cinfo.err = jpeg_std_error( (jpeg_error_mgr*)&jerr );
		jerr.manager.error_exit = jpg_error_exit;
		jerr.manager.output_message = jpg_output_message;

		jpeg_create_decompress( &cinfo );
		jpeg_mem_src( &cinfo, file_memory, file.size() );

		result = JPEG_HEADER_OK == jpeg_read_header( &cinfo, true );

		if( !result ){
			jpeg_destroy_decompress( &cinfo );
			return false;
		};

		jpeg_start_decompress( &cinfo );

		if( !( cinfo.output_width && cinfo.output_height ) )
		{
			jpeg_finish_decompress( &cinfo );
			jpeg_destroy_decompress( &cinfo );
			return false;
		};

		pixelcount	= cinfo.output_width * cinfo.output_height;
		memcount	= 4 * pixelcount;
		row_stride	= cinfo.output_width * cinfo.output_components;

		if( ( 0x1FFFFFFF < pixelcount ) || ( 4 < cinfo.output_components ) ||
			( cinfo.output_height != ( ( ( pixelcount * 4 ) / cinfo.output_width ) / 4 ) ) )
		{
			jpeg_finish_decompress( &cinfo );
			jpeg_destroy_decompress( &cinfo );
			return false;
		};

		dest->set_sizes( cinfo.output_width, cinfo.output_height );

		while( cinfo.output_height > cinfo.output_scanline )
		{
			buf = ((uint8_t*)dest->memory()) + row_stride * cinfo.output_scanline;
			jpeg_read_scanlines( &cinfo, buffer, 1 );
		};

		buf = (uint8_t*)dest->memory();
		if( 1 == cinfo.output_components )
		{
			int32_t sindex = pixelcount;
			int32_t dindex = memcount;
			uint8_t greyshade;

			do
			{
				greyshade = buf[ --sindex ];

				buf[ --dindex ] = 255;
				buf[ --dindex ] = greyshade;
				buf[ --dindex ] = greyshade;
				buf[ --dindex ] = greyshade;
			}while( sindex );
		}else
		{
			int32_t sindex = pixelcount * 3;
			int32_t dindex = memcount;

			do
			{								
				buf[ --dindex ] = 255;
				buf[ --dindex ] = buf[ --sindex ];
				buf[ --dindex ] = buf[ --sindex ];
				buf[ --dindex ] = buf[ --sindex ];
			}while( sindex );
		};

		jpeg_finish_decompress( &cinfo );
		jpeg_destroy_decompress( &cinfo );
		return result;
	};

	const bool jpg_operator_t::save( const char* file_name, plugin::image_desc_t* source, plugin::option_t* options ){
		return false;
	};

	const plugin::options_desc_t* jpg_operator_t::import_options() const {
		return &op_imp_desc;
	};

	const plugin::options_desc_t* jpg_operator_t::export_options() const {
		return &op_exp_desc;
	};
};

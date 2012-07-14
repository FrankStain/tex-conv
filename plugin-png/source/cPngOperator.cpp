#include "core.h"
#include "cPngOperator.h"
#include "cFileMapping.h"

extern "C"
{
	#include "png.h"
};

#define PNG_BYTES_TO_CHECK 8

namespace {
	char					op_desc[]	= "Portable Network Graphics";
	char					op_ext[]	= "png";
	sPluginOperatorType		op_type		= sPluginOperatorType::OT_EXPORTER | sPluginOperatorType::OT_IMPORTER;
};

cPngOperator::cPngOperator()
{

};

cPngOperator::~cPngOperator()
{

};

const char* cPngOperator::get_name()
{
	return op_ext;
};

const char* cPngOperator::get_file_ext()
{
	return op_ext;
};

const char* cPngOperator::get_file_desc()
{
	return op_desc;
};

const sPluginOperatorType cPngOperator::get_type()
{
	return op_type;
};

const bool cPngOperator::is_file_valid( const char* file_name )
{
	if( !file_name || !*file_name || !cFileMapping::file_exists( file_name ) )
	{
		return false;
	};

	cFileMapping file;
	if( !file.construct( file_name ) )
	{
		return false;
	};

	png_byte* file_sign;
	if( !file.map_view( file_sign, 0, PNG_BYTES_TO_CHECK ) )
	{
		return false;
	};

	if( png_sig_cmp( file_sign, 0, PNG_BYTES_TO_CHECK ) )
	{
		return false;
	};

	return true;
};

void* png_image_alloc( png_struct* png, size_t size )
{
	return new char[size];
};

void png_image_free( png_struct* png, void * ptr )
{
	delete[] (char*)ptr;
};

void png_image_warn( png_structp png_ptr, png_const_charp message ) {};
void png_image_error( png_structp png_ptr, png_const_charp message ) {};

struct sPngFileStruct
{
	char*		m_memory;
	size64_t	m_size;
	size64_t	m_position;
};

void png_image_read( png_struct* png, png_byte* ptr, png_size_t size )
{
	sPngFileStruct& stream = *(sPngFileStruct*)png_get_io_ptr( png );
	const size_t str_size = ( size > ( stream.m_size - stream.m_position ) )? stream.m_size - stream.m_position : size;
	memcpy( ptr, &(stream.m_memory[ stream.m_position ]), str_size );
	stream.m_position += str_size;
};

const bool cPngOperator::load( cImageDesc* desc, const cOperatorProperties* props, const char* file_name )
{
	if( !file_name || !*file_name || !cFileMapping::file_exists( file_name ) )
	{
		return false;
	};

	cFileMapping file;
	if( !file.construct( file_name ) )
	{
		return false;
	}
	else
	{
		png_byte* file_sign;
		if( file.map_view( file_sign, 0, PNG_BYTES_TO_CHECK ) )
		{
			return false;
		};

		if( png_sig_cmp( file_sign, 0, PNG_BYTES_TO_CHECK ) )
		{
			return false;
		};

		file.close_view( file_sign );
	};

	png_structp png_ptr = png_create_read_struct_2(
		PNG_LIBPNG_VER_STRING, NULL, 
		png_image_error, png_image_warn,
		NULL, png_image_alloc, png_image_free
	);

	if( !png_ptr )
	{
		return false;
	};

	png_infop info_ptr = png_create_info_struct( png_ptr );
	if( info_ptr == NULL )
	{
		png_destroy_read_struct( &png_ptr, 0, 0 );
		return false;
	};

	sPngFileStruct file_memory;
	file.map_view( file_memory.m_memory, 0, 0 );
	file_memory.m_position = 0;
	file_memory.m_size = file.size() - PNG_BYTES_TO_CHECK;

	png_set_read_fn( png_ptr, (void*)&file_memory, png_image_read );
	png_read_png( png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, 0 );

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

	desc->set_sizes( png_width, png_height );
	png_byte** png_buf = png_get_rows( png_ptr, info_ptr );
	const png_uint_32 row_length = png_get_rowbytes( png_ptr, info_ptr );

	for( png_uint_32 row_id = 0; png_height > row_id; row_id++ )
	{
		memcpy( desc->row( row_id ), png_buf[row_id], row_length );
	};

	png_destroy_read_struct( &png_ptr, &info_ptr, 0 );

	return true;
};

cOperatorProperties* cPngOperator::create_importer_properties()
{
	return NULL;
};

void cPngOperator::remove_importer_properties( cOperatorProperties*& props )
{

};

const bool cPngOperator::save( cImageDesc* desc, const cOperatorProperties* props, const char* file_name )
{
	return true;
};

cOperatorProperties* cPngOperator::create_exporter_properties()
{
	return NULL;
};

void cPngOperator::remove_exporter_properties( cOperatorProperties*& props )
{

};

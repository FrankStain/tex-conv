#include "core.h"
#include "operator.h"
#include "targa.h"

namespace dll {
	const char					op_name[]		= "TGA";
	const char					op_desc[]		= "TARGA Image";
	const char					op_ext[]		= "tga";
	plugin::operator_options_t	op_type			= plugin::OPER_IMPORT | plugin::OPER_EXPORT;

	plugin::options_desc_t		op_imp_desc			= {
		NULL, 0
	};

	char*						op_format_names[]	= {
		"BGRA 8888 32bpp", "BGR 888 24bpp", "BGRA 5551 16bpp", 0
	};

	plugin::option_desc_t		op_exp_options[]	= {
		{ "Image format",	0,	plugin::ot_enum,	0,	0,	2,	op_format_names },
		{ "Save Alpha",		1,	plugin::ot_bool,	1,	0,	1,	NULL },
	};

	plugin::options_desc_t		op_exp_desc			= {
		op_exp_options, sizeof( op_exp_options ) / sizeof( plugin::option_desc_t )
	};
		
	tga_operator_t::tga_operator_t(){
	
	};

	tga_operator_t::~tga_operator_t(){
	
	};

	const char* tga_operator_t::name(){
		return op_name;
	};

	const plugin::operator_options_t tga_operator_t::type(){
		return op_type;
	};
	
	const char* tga_operator_t::file_ext(){
		return op_ext;
	};

	const char* tga_operator_t::file_desc(){
		return op_desc;
	};

	const bool tga_operator_t::validate_file( const char* file_name ){
		return tga::validate( file_name );
	};

	const bool tga_operator_t::load( const char* file_name, plugin::image_desc_t* dest, plugin::option_t* options ){
		if( tga::load( file_name, dest ) ){
			const size_t row_size = 4 * dest->width();
			plugin::pixel_desc_t* row_buf = new plugin::pixel_desc_t[ dest->width() ];

			for( int32_t rid = 0; ( dest->height() / 2 ) > rid; rid++ ){
				plugin::pixel_desc_t* cs = dest->row( rid );
				plugin::pixel_desc_t* ds = dest->row( dest->height() - rid - 1 );

				memcpy( row_buf, cs, row_size );
				memcpy( cs, ds, row_size );
				memcpy( ds, row_buf, row_size );
			};

			delete[] row_buf;
			return true;
		};

		return false;
	};
	
	const bool tga_operator_t::save( const char* file_name, plugin::image_desc_t* source, plugin::option_t* options ){
		static const uint16_t format_table[] = { 32, 24, 16 };
		const uint16_t format = ( options )? format_table[ options[0].m_as_int % 3 ] : 32;
		const bool use_alpha = ( options )? options[1].m_as_bool : true;
				
		return tga::save( file_name, source, format, use_alpha );
	};

	const plugin::options_desc_t* tga_operator_t::import_options() const {
		return &op_imp_desc;
	};

	const plugin::options_desc_t* tga_operator_t::export_options() const {
		return &op_exp_desc;
	};
};

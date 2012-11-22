#pragma once

#include "native-core.h"
#include "object_id.h"
#include "plugin_client_api.h"

namespace dll {
	class image_file_t : public plugin::image_desc_t {
	private:
		int32_t					m_width;
		int32_t					m_height;
		plugin::pixel_desc_t*	m_data;

	public:
		image_file_t();
		image_file_t( const image_file_t& origin );
		virtual ~image_file_t();

		virtual const int width() const { return m_width; };
		virtual const int height() const { return m_height; };

		virtual void clear();
		virtual void free();
		virtual const bool set_sizes( const int width, const int height );

		virtual plugin::pixel_desc_t* memory() const { return m_data; };
		virtual plugin::pixel_desc_t* row( const int index ) const;
	};
};

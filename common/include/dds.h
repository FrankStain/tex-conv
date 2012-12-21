#pragma once

#include "common_defs.h"

#pragma pack( push, 1 )
namespace dds {
	extern const uint32_t	header_magic;
	extern const size_t		header_size;
	extern const size_t		pixel_format_size;
	extern const size_t		header_file_size;

	enum format_t {
		atc_rgb				= FOURCC( 'A', 'T', 'C', ' ' ),
		atc_rgba_expl		= FOURCC( 'A', 'T', 'C', 'A' ),
		atc_rgba_interp		= FOURCC( 'A', 'T', 'C', 'I' ),
		etc_rgb				= FOURCC( 'E', 'T', 'C', ' ' ),

		s3c_dxt1			= FOURCC( 'D', 'X', 'T', '1' ),
		s3c_dxt3			= FOURCC( 'D', 'X', 'T', '3' ),
		s3c_dxt5			= FOURCC( 'D', 'X', 'T', '5' ),
	};

	enum {
		hf_caps			= 0x00000001U,
		hf_height		= 0x00000002U,
		hf_width		= 0x00000004U,
		hf_pitch		= 0x00000008U,
		hf_pixel_format	= 0x00001000U,
		hf_mip_count	= 0x00020000U,
		hf_linear_size	= 0x00080000U,
		hf_depth		= 0x00800000U,
	};

	union header_flags_t {
		uint32_t		m_flags;
		struct {
			uint32_t	m_caps : 1;
			uint32_t	m_height : 1;
			uint32_t	m_width : 1;
			uint32_t	m_pitch : 1;
			uint32_t	m_reserved_1 : 8;
			uint32_t	m_pixel_format : 1;
			uint32_t	m_reserved_2 : 4;
			uint32_t	m_mip_count : 1;
			uint32_t	m_reserved_3 : 1;
			uint32_t	m_linear_size : 1;
			uint32_t	m_reserved_4 : 3;
			uint32_t	m_depth : 1;
		};
	};

	enum {
		pf_alpha		= 0x00000001,
		pf_format		= 0x00000004,
		pf_idexed		= 0x00000020,
		pf_rgb			= 0x00000040,
	};

	enum {
		dc1_complex		= 0x00000008U,
		dc1_texture		= 0x00001000U,
		dc1_mipmap		= 0x00400000U,
		dc2_cubemap		= 0x00000200U,
		dc2_cubemap_px	= 0x00000400U,
		dc2_cubemap_nx	= 0x00000800U,
		dc2_cubemap_py	= 0x00001000U,
		dc2_cubemap_ny	= 0x00002000U,
		dc2_cubemap_pz	= 0x00004000U,
		dc2_cubemap_nz	= 0x00008000U,
		dc2_volume		= 0x00200000U,
	};

	union pixel_format_flags_t {
		uint32_t		m_flags;
		struct {
			uint8_t		m_alpha : 1;
			uint8_t		m_resedved_1 : 1;
			uint8_t		m_format : 1;
			uint8_t		m_resedved_2 : 2;
			uint8_t		m_indexed : 1;
			uint8_t		m_rgb : 1;
		};
	};

	struct pixel_format_t {
		uint32_t				m_size;
		pixel_format_flags_t	m_flags;
		uint32_t				m_format;
		uint32_t				m_bit_depth;
		uint32_t				m_red_mask;
		uint32_t				m_grn_mask;
		uint32_t				m_blu_mask;
		uint32_t				m_alpha_mask;
	};

	union header_t {
		uint8_t							m_raw_data[128];
		struct {
			uint32_t					m_magic;
			uint32_t					m_size;
			header_flags_t				m_flags;
			uint32_t					m_height;
			uint32_t					m_width;
			uint32_t					m_line_pitch;
			uint32_t					m_bit_depth;
			uint32_t					m_mip_count;
			uint32_t					m_reserved[11];

			pixel_format_t				m_pixel_format;

			struct
			{
				uint32_t				m_caps[2];
				uint32_t				m_dds_x;
				uint32_t				m_reserved;
			}							m_caps;
		
			int32_t						m_reserved_2;
		};

		const bool is_valid() const { return ( header_magic == m_magic ) && ( header_file_size == m_size ) && ( m_flags.m_pixel_format || m_flags.m_caps ); };
	};
};
#pragma pack( pop )

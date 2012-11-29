#pragma once

#include "common_defs.h"

#pragma pack( push, 1 )
namespace pvr {
	namespace v2 {
		extern const uint32_t	header_magic;
		extern const size_t		header_size;
		extern const size_t		header_file_size;

		enum {
			MGLPT_ARGB_4444		= 0x00U,
			MGLPT_ARGB_1555,
			MGLPT_RGB_565,
			MGLPT_RGB_555,
			MGLPT_RGB_888,
			MGLPT_ARGB_8888,
			MGLPT_ARGB_8332,
			MGLPT_I_8,
			MGLPT_AI_88,
			MGLPT_1_BPP,
			MGLPT_VY1UY0,
			MGLPT_Y1VY0U,
			MGLPT_PVRTC2,
			MGLPT_PVRTC4,
			MGLPT_PVRTC2_2,
			MGLPT_PVRTC2_4,

			OGL_RGBA_4444		= 0x10U,
			OGL_RGBA_5551,
			OGL_RGBA_8888,
			OGL_RGB_565,
			OGL_RGB_555,
			OGL_RGB_888,
			OGL_I_8,
			OGL_AI_88,
			OGL_PVRTC2,
			OGL_PVRTC4,
			OGL_PVRTC2_2,
			OGL_PVRTC2_4,

			D3D_DXT1			= 0x20U,
			D3D_DXT2,
			D3D_DXT3,
			D3D_DXT4,
			D3D_DXT5,

			D3D_RGB_332,
			D3D_AI_44,
			D3D_LVU_655,
			D3D_XLVU_8888,
			D3D_QWVU_8888,

			//10 bits per channel
			D3D_ABGR_2101010,
			D3D_ARGB_2101010,
			D3D_AWVU_2101010,

			//16 bits per channel
			D3D_GR_1616,
			D3D_VU_1616,
			D3D_ABGR_16161616,

			//HDR formats
			D3D_R16F,
			D3D_GR_1616F,
			D3D_ABGR_16161616F,

			//32 bits per channel
			D3D_R32F,
			D3D_GR_3232F,
			D3D_ABGR_32323232F,

			// Ericsson
			ETC_RGB_4BPP,
			ETC_RGBA_EXPLICIT,
			ETC_RGBA_INTERPOLATED,

			MGLPT_NOTYPE		= 0xff
		};

		enum {
			pf_use_mips			= 0x00000100U,
			pf_twiddled			= 0x00000200U,
			pf_use_normals		= 0x00000400U,
			pf_use_border		= 0x00000800U,
			pf_is_cube_map		= 0x00001000U,
			pf_use_false_mips	= 0x00002000U,
			pf_is_volume		= 0x00004000U,
			pf_use_alpha		= 0x00008000U,
			pf_vertical_flip	= 0x00010000U,
		};

		struct pix_format_t {
			union {
				uint32_t		m_flags;
				struct {
					uint8_t		m_format : 8;
					uint8_t		m_mipmaps : 1;
					uint8_t		m_twiddled : 1;
					uint8_t		m_normals : 1;
					uint8_t		m_border : 1;
					uint8_t		m_cubemap : 1;
					uint8_t		m_false_mips : 1;
					uint8_t		m_volume : 1;
					uint8_t		m_use_alpha : 1;
					uint8_t		m_vert_flip : 1;
				};
			};

			inline operator uint32_t& () { return m_flags; };
			inline operator const uint32_t& () const { return m_flags; };
		};

		struct header_t {
			uint32_t			m_size;
			uint32_t			m_height;
			uint32_t			m_width;
			uint32_t			m_mips_count;
			pix_format_t		m_flags;
			uint32_t			m_data_size;
			uint32_t			m_bit_depth;
			struct {
				uint32_t		m_red;
				uint32_t		m_green;
				uint32_t		m_blue;
				uint32_t		m_alpha;
			}					m_mask;
			uint32_t			m_magic;
			uint32_t			m_surface_count;

			const bool is_valid() const { return ( header_file_size == m_size ) && ( header_magic == m_magic ) && m_width && m_height && m_data_size; };
		};
	};

	namespace v3 {
		extern const uint32_t	header_version;
		extern const size_t		header_size;
		extern const size_t		header_file_size;

		enum {
			cs_lrgb,
			cs_srgb
		};
		
		struct pix_format_t {
			union {
				uint64_t		m_value;
				uint8_t			m_cars[8];
				struct {
					uint32_t	m_lvalue;
					uint32_t	m_hvalue;
				};
			};

			inline operator uint64_t& () { return m_value; };
			inline operator const uint64_t& () const { return m_value; };
		};

		struct hdr_flags_t {
			union {
				uint32_t		m_value;
				struct {
					uint8_t		m_pvrtexlib_used : 1;
					uint8_t		m_premultiply : 1;
				};
			};
		};

		struct header_t {
			uint32_t			m_version;
			hdr_flags_t			m_flags;
			pix_format_t		m_format;
			uint32_t			m_color_space;
			uint32_t			m_channel_type;
			uint32_t			m_height;
			uint32_t			m_width;
			uint32_t			m_surface_count;
			uint32_t			m_face_count;
			uint32_t			m_mip_count;
			uint32_t			m_meta_size;

			const bool is_valid() const { return ( header_version == m_version ) && m_width && m_height; };
		};

		struct texture_data_t {
			uint32_t			m_dx;
			uint32_t			m_dy;
			uint32_t			m_width;
			uint32_t			m_height;
		};

		struct meta_data_t {
			uint32_t			m_format;
			uint32_t			m_key;
			uint32_t			m_size;
			union {
				texture_data_t	m_texture_desc;

				struct {
					float		m_weight;
					uint8_t		m_axies[4];
				}				m_normal_map;

				struct {
					uint8_t		m_faces[6];
				}				m_cube_map;

				struct {
					uint8_t		m_direction[3];
				}				m_orient;

				struct {
					uint32_t	m_x;
					uint32_t	m_y;
					uint32_t	m_z;
				}				m_border;
			};
		};
	};

	struct header_t {
		union {
			v2::header_t		m_v2;
			v3::header_t		m_v3;
		};

		const bool is_valid() const { return m_v3.is_valid() || m_v2.is_valid(); };
	};
};
#pragma pack( pop )

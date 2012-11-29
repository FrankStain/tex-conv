#pragma once

#pragma pack( push, 1 )
namespace plugin {
	enum option_type_t {
		ot_uint		= 0x01U,
		ot_sint,
		ot_bool,
		ot_enum,
		ot_string
	};
	
	struct option_desc_t {
		char*			m_name;
		int				m_id;
		option_type_t	m_type;
		int				m_def_value;
		int				m_min_value;
		int				m_max_value;
		char**			m_value_names;
	};

	struct options_desc_t {
		option_desc_t*	m_desc;
		int				m_count;
	};

	struct option_t {
		int				m_id;
		union {
			int			m_as_int;
			char*		m_as_string;
			bool		m_as_bool;
		};
	};
};
#pragma pack( pop )
#include "core.h"
#include "cWorkspace.h"

string		dll::g_ws_file	= "";
cWorkspace	dll::g_workspace;

cWorkspace::cWorkspace() : m_ready(false), m_new(true), m_saved(true) {
	m_root = dll::g_base_dir;
};

cWorkspace::~cWorkspace(){

};

const bool cWorkspace::load( const string& file_name ){
	return false;
};

const bool cWorkspace::save( const string& file_name ){
	return false;
};

void cWorkspace::clear(){
	
	m_root = dll::g_base_dir;
};

const string& cWorkspace::base_dir(){
	return m_root;
};

const bool cWorkspace::add_file( const string& name ){
	return false;
};

const bool cWorkspace::remove_file( const string& name ){
	return false;
};

const bool cWorkspace::change_file( const int index, const string& new_name ){
	return false;
};

const int cWorkspace::writers_count() const {
	return 0;
};

const string& cWorkspace::writer_name( const int index ) const {
	static string str = "";
	return str;
};

const bool cWorkspace::add_writer( const string& name ){
	return false;
};

const bool cWorkspace::remove_writer( const string& name ){
	return false;
};

#include "config.h"

#ifndef _PLUGINS_H
#define _PLUGINS_H

#include <pthread.h>

#include "utils.h"
#include "core.h"

typedef enum __supported_plugins_t {
#ifdef _C_PLUGIN
	_C_,
#endif

#ifdef _PYTHON_PLUGIN
	_PYTHON_,
#endif

#ifdef _RUBY_PLUGIN
	_RUBY_,
#endif

#ifdef _PERL_PLUGIN
	_PERL_,
#endif

#ifdef _LUA_PLUGIN
	_LUA_,
#endif

#ifdef _TCL_PLUGIN
	_TCL_,
#endif

#ifdef _JAVA_PLUGIN
	_JAVA_,
#endif
  END_VALUE
} supported_plugins_t;


static const UNUSED char* supported_plugins_str[] = {
#ifdef _C_PLUGIN
	"C",
#endif

#ifdef _PYTHON_PLUGIN
	_PYTHON_VERSION_,
#endif

#ifdef _RUBY_PLUGIN
        _RUBY_VERSION_,
#endif

#ifdef _PERL_PLUGIN
	_PERL_VERSION_,
#endif

#ifdef _LUA_PLUGIN
	_LUA_VERSION_,
#endif

#ifdef _TCL_PLUGIN
	_TCL_VERSION_,
#endif

#ifdef _JAVA_PLUGIN
	_JAVA_VERSION_,
#endif

  NULL
};


static const UNUSED char* plugins_extensions_str[] = {
#ifdef _C_PLUGIN
	".so",
#endif

#ifdef _PYTHON_PLUGIN
	".py",
#endif

#ifdef _RUBY_PLUGIN
	".rb",
#endif

#ifdef _PERL_PLUGIN
	".pl",
#endif

#ifdef _LUA_PLUGIN
	".lua",
#endif

#ifdef _TCL_PLUGIN
	".tcl",
#endif

#ifdef _JAVA_PLUGIN
	".class",
#endif

  NULL
};

#define MAX_VMS 10

typedef struct _http_request_fields
{
                char* method;
                char* proto;
                bool is_ssl;
                bool do_intercept;
                char* hostname;
                unsigned short port;
                char* path;
                char* version;
} http_request_t ;

typedef enum {
	REQUEST	 = 0,
	RESPONSE = 1
} req_t;

typedef struct _request_type {
		long id;
		req_t type;
		char* data;
		size_t size;
                char* uri;
		http_request_t http_infos;
} request_t;

typedef struct _interpreter_type {
		unsigned short id;
		supported_plugins_t type;
		pthread_mutex_t mutex;
		void *vm;
		bool ready;
} interpreter_t;

interpreter_t vms[MAX_VMS];


typedef struct _plugin_type {
		unsigned short id;
                char fullpath[PATH_MAX];                  // full absolute path (ex. /path/to/MyPlugin.py)
		char filename[PATH_MAX];                  // full file name (ex. MyPlugin.py)
		char name[PATH_MAX];                      // name as seen by VM (ex. MyPlugin)

		supported_plugins_t type;
		unsigned short priority;
		struct _plugin_type* next;
		proxenet_state state;

		interpreter_t *interpreter;
		void *pre_function;
		void *post_function;
                void *class;
} plugin_t;

#include "http.h"

unsigned int 		proxenet_plugin_list_size();
unsigned int		count_plugins_by_type(supported_plugins_t);
unsigned int		count_initialized_plugins_by_type(supported_plugins_t);
int			proxenet_add_new_plugins(char*, char*);
void			proxenet_remove_plugin(plugin_t*);
void 			proxenet_remove_all_plugins();
void 			proxenet_print_plugins_list();
void 			proxenet_print_all_plugins();
char*			get_plugin_path(char*);

#endif /* _PLUGINS_H */

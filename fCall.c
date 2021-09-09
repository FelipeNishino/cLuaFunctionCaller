// https://www.lua.org/pil/25.2.html

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERBOSE 1

/* function declaration */
void f (lua_State* L, const char* functionName, int argCount, const char** args);
void error (lua_State *L, const char *fmt, ...);

int main(int argc, const char* argv[]){
	if (argc < 4) {
		printf("Quantidade invalida de argumentos.\n");
		return 1;
	}

	if (VERBOSE) {
		printf("funcName: %s, argCount: %d, ", argv[1], atoi(argv[2]));
		int i = 0;
		for (i = 0; i < argc - 3; ++i) {
			printf("arg %d: %s ", i, argv[i + 3]);
		}
		printf("\n");
	}

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "luaFunctions.lua");
	
	f(L, argv[1], atoi(argv[2]), &argv[3]);
	
	lua_close(L);
	return 0;
}

void f(lua_State* L, const char* functionName, int argCount, const char** args) {
	/* push functions and arguments */
	lua_getglobal(L, functionName);  /* function to be called */
	int i = 0;
	for (i = 0; i < argCount; ++i) {
		printf("pushed Value: %f\n", atof(args[i]));
		lua_pushnumber(L, atof(args[i]));   /* push i-th argument */
	}

	/* do the call (2 arguments, 1 result) */
	if (lua_pcall(L, argCount, 1, 0) != 0)
	error(L, "error running function `%s': %s\n Certifique-se de que a função chamada existe no arquivo luaFunctions.lua\n", functionName,
	          lua_tostring(L, -1));
	
	/* retrieve result */

	if (lua_isnumber(L, -1)){
		double z = lua_tonumber(L, -1);
		lua_pop(L, 1);  /* pop returned value */
		printf("Valor de resultado %f\n", z);
	}
	else {
        const char* res = lua_tostring(L, -1);
        lua_pop(L, 1);  /* pop returned value */

        printf("Valor de resultado: %s\n", res);
    }
}

// https://www.lua.org/pil/24.1.html#first-ex
void error (lua_State *L, const char *fmt, ...) {
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	lua_close(L);
	exit(EXIT_FAILURE);
}
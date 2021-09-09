// https://www.lua.org/pil/25.2.html

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERBOSE 1

void f (lua_State* L, const char* functionName, int argCount, const char** args);
void error (lua_State *L, const char *fmt, ...);

int main(int argc, const char* argv[]){
	// Checks the validity of args
	if (argc < 4) {
		printf("Quantidade invalida de argumentos.\n");
		return 1;
	}

	// Prints received values
	if (VERBOSE) {
		printf("------------------------------------\n");
		printf("funcName: %s, argCount: %d, ", argv[1], atoi(argv[2]));
		int i = 0;
		for (i = 0; i < argc - 3; ++i) {
			printf("arg %d: %s ", i+1, argv[i+3]);
		}
		printf("\n");
	}
	printf("------------------------------------\n");

	if (argc < 3 + atoi(argv[2])) {
		printf("Inconsistencia entre a quantidade de argumentos declarada e os argumentos passados.\n");
		printf("------------------------------------\n");
		return 1;
	}
	

	// Initializes and opens de lua file
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "luaFunctions.lua");
	
	// Runs the function passed as parameters
	f(L, argv[1], atoi(argv[2]), &argv[3]);
	
	// Closes the lua file
	lua_close(L);
	return 0;
}

void f(lua_State* L, const char* functionName, int argCount, const char** args) {
	// Push function and arguments
	lua_getglobal(L, functionName);  // Function to be called
	int i = 0;
	for (i = 0; i < argCount; ++i) {
		printf("pushed Value: %f\n", atof(args[i]));
		lua_pushnumber(L, atof(args[i]));   // push i-th argument
	}

	// Calls the function
	if (lua_pcall(L, argCount, 1, 0) != 0)
	error(L, "error running function `%s': %s\n Certifique-se de que a função chamada existe no arquivo luaFunctions.lua\n", functionName,
	          lua_tostring(L, -1));
	
	// Get/treat results
	if (lua_isnumber(L, -1)){
		double z = lua_tonumber(L, -1);
		printf("result: %f\n", z);
	}
	else {
        const char* returnedVal = lua_tostring(L, -1);

        printf("result: %s\n", returnedVal);
    }
    printf("------------------------------------\n");
    lua_pop(L, 1);  /* pop returned value */
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
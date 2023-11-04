#pragma once







typedef enum {
	SUCCESS = 0,
} error_t;


#define EXIT_FUNC(_res) do{	\
	res = _res;		\
	goto cleanup;		\
}while(0)

#define ASSERT(_cond, _res) do{		\
	if(!(_cond)) {			\
		EXIT_FUNC(_res);	\
	}				\
}while(0)

#define VERIFY_SUCCESS() ASSERT(res == 0, res)
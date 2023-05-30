#include "Lab3_enclave_t.h"
#include <string.h>
#include "sgx_trts.h"



const char table[6][41] = {//тестовые данные
	"9917963ADF715E64F41F6E454C20372B43134245",
	"02C461E74C66148AC30DA6352E18DD8B75BBDC85",
	"93127E33E00109235021840AED8B43F29DBF5868",
	"ACC836EE83E39A0105B593CE3440A6F060F41167",
	"E7E493C579B6D5B24C5DD7D4574E27A1351938FF"
};

void foo(char* buf, size_t len, size_t idx)
{
	if (idx < 5) {
		const char* data_ptr = data_ptr = table[idx];
		memcpy(buf, data_ptr, strlen(data_ptr + 1));
	}
	else {
		memset(buf, 0, strlen(table[0]));
	}
	return;
}
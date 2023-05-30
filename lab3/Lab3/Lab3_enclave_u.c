#include "Lab3_enclave_u.h"
#include <errno.h>

typedef struct ms_foo_t {
	char* ms_buf;
	size_t ms_len;
	size_t ms_idx;
} ms_foo_t;

static const struct {
	size_t nr_ocall;
	void * func_addr[1];
} ocall_table_Lab3_enclave = {
	0,
	{ NULL },
};

sgx_status_t foo(sgx_enclave_id_t eid, char* buf, size_t len, size_t idx)
{
	sgx_status_t status;
	ms_foo_t ms;
	ms.ms_buf = buf;
	ms.ms_len = len;
	ms.ms_idx = idx;
	status = sgx_ecall(eid, 0, &ocall_table_Lab3_enclave, &ms); //Эта функция позволяет безопасно вызывать функции из SGX-защищенного контейнера, предоставляя доступ к его функционалу из небезопасного окружения
	//идентификатор запущенного экземпляра "eid", номером функции внутри экземпляра "0", 
	//указателm на структуру "ocall_table_Lab3_enclave" и указателем на переменную "ms".
	return status;
}

